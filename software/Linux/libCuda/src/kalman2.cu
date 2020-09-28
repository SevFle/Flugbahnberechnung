#include "../include/libCuda.h"


#define gravity 9.807f
#define MeasureSize 6 * sizeof(float)
#define PredictSize  3 * sizeof(float)
#define CovSize 16 * sizeof(float)


using namespace onCuda::KalmanFilter2;


/************************************* Variablendefinition und -deklaration ************************************/

/************************* DEVICE VARIABLEN ***************************/

__device__  float H[18]
{
1.0,   0,   0, 0, 0, 0,
  0, 1.0,   0, 0, 0, 0,
  0,   0, 1.0, 0, 0, 0

};

__device__  float HT[18]    =
  {
  1.0,   0,   0,
    0, 1.0,   0,
    0,   0, 1.0,
    0,   0,   0,
    0,   0,   0,
    0,   0,   0,
  };

__device__  float A[36] =
  {
    1.0,   0,    0,  999,   0,    0,
      0, 1.0,    0,    0, 999,    0,
      0,   0,  1.0,    0,   0,  999,
      0,   0,    0,  1.0,   0,    0,
      0,   0,    0,    0, 1.0,    0,
      0,   0,    0,    0,   0,  1.0
  };

__device__  float AT[36] =
  {
    1.0,   0,    0,    0,   0,    0,
      0, 1.0,    0,    0,   0,    0,
      0,   0,  1.0,    0,   0,    0,
    999,   0,    0,  1.0,   0,    0,
      0, 999,    0,    0, 1.0,    0,
      0,   0,  999,    0,   0,  1.0
  };

__device__  float B[6] =
{
0,
999,
0,
0,
999,
0
};

__device__  float u[1]      = { gravity};

__device__  float Q[16]     =
  {
     0, 0.01,     0,    0,
  0.01,    0,     0,    0,
     0,    0, 0.002, 0.01,
     0,    0,  0.01, 0.001
  };

__device__  float R[4]      =
  {
  0.01, 0.01,
  0.01, 0.01
  };

__device__  float I[16]     =
  {
  1.0, 0, 0, 0,
  0, 1.0, 0, 0,
  0, 0, 1.0, 0,
  0, 0, 0, 1.0
  };

/************************* HOST VARIABLEN ***************************/
float h_A[36]   =
  {
  1.0,   0,    0,  999,   0,    0,
  0, 1.0,    0,    0, 999,    0,
  0,   0,  1.0,    0,   0,  999,
  0,   0,    0,  1.0,   0,    0,
  0,   0,    0,    0, 1.0,    0,
  0,   0,    0,    0,   0,  1.0
  };
float h_AT[36]  =
  {
  1.0,   0,    0,    0,   0,    0,
  0, 1.0,    0,    0,   0,    0,
  0,   0,  1.0,    0,   0,    0,
  999,   0,    0,  1.0,   0,    0,
  0, 999,    0,    0, 1.0,    0,
  0,   0,  999,    0,   0,  1.0
  };
float h_B[36]   =
  {
  0,
  999,
  0,
  0,
  999,
  0
  };

/************************************* KERNEL FUNKTIONEN ************************************/

__device__ float  ele_multi       (float* A,        float* B,    int Awidth,  int Bwidth, int tx, int ty)
  {
  //calculate one element of the product of two matrices
  float Pvalue = 0;
  for (int k = 0; k < Awidth; ++k){
    float Melement = A[ty * Awidth + k];
    float Nelement = B[k * Bwidth + tx];
    Pvalue += Melement * Nelement;
  }
  return Pvalue;
  }
__global__ void   PredictKernel   (float* predictD, float* covD,      float* new_predictD, float* new_covD, int point_num)
  {
  //caculate x_k' = A * x_{k-1} + B*u
  //calculate P_k' = A * P_{k-1} * A^T + Q

  //Kernel function for the first two steps of Kalman Filter
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int bx = blockIdx.x;

    __shared__ float temp[CovSize];
    float value1, value2;

    //caculate x_k' = A * x_{k-1} + B*u
    if (tx < 1){
      value1 = ele_multi(A, predictD + bx * PredictSize, 6, 1, tx, ty);
      value2 = ele_multi(B, u, 1, 1, tx, ty);
      new_predictD[bx * PredictSize + ty] = value1 + value2;
    }

    //calculate P_k' = A * P_{k-1} * A^T + Q
    value1 = ele_multi(A, covD + bx * CovSize, 4, 4, tx, ty);
    temp[ty * 4 + tx] = value1;

    __syncthreads();

    value1 = ele_multi(temp, AT, 4, 4, tx, ty);
    if (bx < point_num)
      new_covD[bx * CovSize + ty * 4 + tx] = value1 + Q[ty * 4 + tx];

    __syncthreads();
  }
__global__ void   UpdateKernel    (float* dataD,    float* predictD,  float* covD, float* new_predictD, float* new_covD, int point_num, int ite_num)
  {
  //kernel functino for the left three steps of Kalman Filter
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int bx = blockIdx.x;

    float value;

    __shared__ float temp[CovSize];

    //calculate H*P
    if (ty < 2){
      value = ele_multi(H, covD + bx*CovSize, 4, 4, tx, ty);
      temp[ty * 4 + tx] = value;
    }

    __syncthreads();

    //calculate H*P_k*H^T + R
    __shared__ float temp2[PredictSize];
    if (ty < 2 && tx < 2){
      value = ele_multi(temp, HT, 4, 2, tx, ty);
      temp2[ty * 2 + tx] = value + R[ty * 2 + tx];
    }

    //calculate P_k* H^T
    __shared__ float temp3[8];
    if (tx < 2){
      value = ele_multi(covD + bx*CovSize, HT, 4, 2, tx, ty);
      temp3[ty * 2 + tx] = value;
    }

    __syncthreads();

    //calculate K
    __shared__ float K[8];
    float det = temp2[0] * temp2[3] - temp2[2] * temp2[1];
    __shared__ float temp2_inv[4];
    temp2_inv[0] = 1.0f / det * temp2[3];
    temp2_inv[1] = -1.0f / det * temp2[1];
    temp2_inv[2] = -1.0f / det * temp2[2];
    temp2_inv[3] = 1.0f / det * temp2[0];
    if (tx < 2){
      value = ele_multi(temp3, temp2_inv, 2, 2, tx, ty);
      K[ty * 2 + tx] = value;
    }

    //calculate z_k - H*x_k'
    __shared__ float temp4[8];
    if (tx < 1 && ty < 2){
      value = ele_multi(H, predictD + bx * PredictSize, 4, 1, tx, ty);
      temp4[ty] = dataD[MeasureSize * bx + ty] - value;
    }

    __syncthreads();
    //calculate x_k
    if (tx < 1){
      value = ele_multi(K, temp4, 2, 1, tx, ty);
      new_predictD[bx * PredictSize + ty] = predictD[bx * PredictSize + ty] + value;
    }

    //caculate I-K*H
    __shared__ float temp5[CovSize];
    value = ele_multi(K, H, 2, 4, tx, ty);
    temp5[ty * 4 + tx] = I[ty * 4 + tx] - value;
    __syncthreads();

    //calculate P_k
    value = ele_multi(temp5, covD + bx*CovSize, 4, 4, tx, ty);
    new_covD[bx * PredictSize + ty * 4 + tx] = value;

    __syncthreads();
  }
__global__ void   initIdentityGPU (int **devMatrix, int numR, int numC)
  {
  int x = blockDim.x*blockIdx.x + threadIdx.x;
  int y = blockDim.y*blockIdx.y + threadIdx.y;
  if(y < numR && x < numC)
    {
    if(x == y)
      devMatrix[y][x] = 1;
    else
      devMatrix[y][x] = 0;
    }
  }
/************************************* KONSTRUKTOR - DESTRUKTOR  ************************************/
C_kalman::C_kalman                (float* h_A,int rowsA, int colsA, float* h_B, int measurementsB, float*h_H, int rowsH, int colsH)
  {
  //H = observationModel
  //A = stateTransitionModel
  //Q = CovarianceProcessNoise

  //R = CovarianceObservationNoise
  //CUBLAS INIT
  this->stat    = new cublasStatus_t;
  this->handle  = new cublasHandle_t;
  cublasCreate  (this->handle);
  init          (h_A, rowsA, colsA, h_B, measurementsB, h_H, rowsH, colsH);
  }
C_kalman::~C_kalman               ()
  {
  cublasDestroy(*handle);
  delete(handle);
  delete(stat);
  }
/************************************* CPU METHODEN ************************************/
int C_kalman::init                (float* h_A,int rowsA, int colsA, float* h_B, int measurementsB, float*h_H, int rowsH, int colsH)
  {
  allocateFloat(A, rowsA, colsA);
  allocateFloat(B, measurementsB, 1);
  allocateFloat(H, rowsH, colsH);

  //SET A
  *stat = cublasSetMatrix (rowsA, colsA, sizeof(float), &(h_A[0]), colsA, A, colsA);
  if (*stat != CUBLAS_STATUS_SUCCESS)
    {
    printf ("Cublas set Matrix A failed");
    cudaFree (A);
    cublasDestroy(*handle);
    return EXIT_FAILURE;
    }

  //SET B
  *stat = cublasSetVector(measurementsB,sizeof(float) ,&(h_B[0]), 1, B, 1);
  if (*stat != CUBLAS_STATUS_SUCCESS)
    {
    printf ("Cublas set Matrix A failed");
    cudaFree (B);
    cublasDestroy(*handle);
    return EXIT_FAILURE;
    }

  //SET H
  *stat = cublasSetMatrix (rowsH, colsH, sizeof(float), &(h_H[0]), colsH, H, colsH);
  if (*stat != CUBLAS_STATUS_SUCCESS)
    {
    printf ("Cublas set Matrix A failed");
    cudaFree (H);
    cublasDestroy(*handle);
    return EXIT_FAILURE;
    }

    float const alpha(1.0);
    float const beta(0.0);

    //Transpose matrix AT + HT
    cublasSgeam(*handle, CUBLAS_OP_T, CUBLAS_OP_N, rowsA, colsA, &alpha, &(A[0]), colsA, &beta, &(A[0]), rowsA, &(AT[0]), rowsA );
    cublasSgeam(*handle, CUBLAS_OP_T, CUBLAS_OP_N, rowsH, colsH, &alpha, &(H[0]), colsH, &beta, &(H[0]), rowsH, &(HT[0]), rowsH );

 }
int C_kalman::allocateFloat       (float* devPtrA, int m/*column*/, int n/*row*/)
  {
  cudaMalloc((void**)devPtrA, m*n*sizeof(float));
  }
void C_kalman::rowToColumnMajor   (float* Input, float* Output, int rows, int cols)
  {
  for (int row = 0; row < rows; row++)
    {
    for (int col = 0; col < cols; col++)
      {
      /* Column-major order */
      float d = Input[col*rows +row];

      if (d < 0) { d = 0; }

      /* Row-major order */
      /* Map from x=0,y=0 at buttom left corner to
         0,0 at top left corner */
      Output[cols*(rows-1 -row) + col] = d;
      }
    }
  }

int C_kalman::setQ               (float* h_Q, int rowsQ, int colsQ)
  {
  *stat = cublasSetMatrix (rowsQ, colsQ, sizeof(float), &(h_Q[0]), colsQ, Q, colsQ);
  if (*stat != CUBLAS_STATUS_SUCCESS)
    {
    printf ("Cublas set Matrix A failed");
    cudaFree (Q);
    cublasDestroy(*handle);
    return EXIT_FAILURE;
    }
  }
int C_kalman::setR               (float* h_R, int rowsR, int colsR)
  {
  *stat = cublasSetMatrix (rowsR, colsR, sizeof(float), &(h_R[0]), colsR, R, colsR);
  if (*stat != CUBLAS_STATUS_SUCCESS)
    {
    printf ("Cublas set Matrix A failed");
    cudaFree (R);
    cublasDestroy(*handle);
    return EXIT_FAILURE;
    }
  }


void C_kalman::predict_single     (float* predict, float* covD, float* new_predict, float* new_covD, int point_num, float delta_t)
  {
  //x_k' = A * x_{k-1} + B*u
  //P_k' = A * P_{k-1} * A^T + Q

  float* predictD, *new_predictD;

  for(int i=0; i < 36; i++)
    {
      if(h_A[i] == 999)
        h_A[i] = delta_t;
      if(h_AT[i] == 999)
        h_AT[i] = delta_t;

    }
  h_B[1] = 0.5f*(delta_t*delta_t);
  h_B[4] = delta_t;

  cudaMemcpy(A, h_A, 36 * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(AT, h_AT, 36 * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(B, h_B, 36 * sizeof(float), cudaMemcpyHostToDevice);

  cudaMalloc(&predictD, point_num* PredictSize* sizeof(float));
  cudaMalloc(&new_predictD, point_num* PredictSize* sizeof(float));

  cudaMemcpy(predictD, predict, point_num*PredictSize*sizeof(float), cudaMemcpyHostToDevice);
  dim3 dimBlock(4, 4);
  dim3 dimGrid(point_num, 1);

  PredictKernel<<<dimGrid,dimBlock >>>(predictD, covD, new_predictD, new_covD, point_num);

  // After this step, data in PredictData is x', data in Covariance is P'
  cudaMemcpy(new_predict, new_predictD, point_num*PredictSize*sizeof(float), cudaMemcpyDeviceToHost);
  cudaFree(predictD);
  cudaFree(new_predictD);
  }
void C_kalman::update_single      (float* data, float* predict, float* covD, float* new_predict, float* new_covD, int point_num, float delta_t, int ite_num)
  {
  //the left three steps of Kalman Filter
  // H*P
  // H*P_k*H^T + R
  //calculate P_k* H^T
  //calculate K
  //calculate z_k - H*x_k'
  //calculate x_k
  //caculate I-K*H
  //calculate P_k

  float* predictD,  *new_predictD, *dataD;

  cudaMalloc(&predictD, point_num* PredictSize* sizeof(float));
  cudaMalloc(&new_predictD, point_num* PredictSize* sizeof(float));
  cudaMalloc(&dataD, point_num * 2 * sizeof(float));

  cudaMemcpy(predictD, predict, point_num*PredictSize*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dataD, data, point_num * 2 * sizeof(float), cudaMemcpyHostToDevice);

  dim3 dimBlock(4, 4);
  dim3 dimGrid(point_num, 1);
  UpdateKernel << <dimGrid, dimBlock >> >(dataD, predictD, covD, new_predictD, new_covD, point_num, ite_num);

  // After this step, data in PredictData is x, data in Covariance is P
  cudaMemcpy(new_predict, new_predictD, point_num*PredictSize*sizeof(float), cudaMemcpyDeviceToHost);

  cudaFree(predictD);
  cudaFree(new_predictD);
  cudaFree(dataD);
  }




