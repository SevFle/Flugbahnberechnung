#include "cudaKalman.cuh"
#include <stdio.h>
#include <iostream>
#define IDX2C(i,j,ld) (((j)*(ld))+(i))

#define ALERT(cudaStat, message) \
  if (cudaStat != cudaSuccess){ \
    printf("\n");\
    printf(message);\
    printf("\n");\
    return EXIT_FAILURE;\
    }
#define PERR(call) \
  if (call) {\
   fprintf(stderr, "%s:%d Error [%s] on "#call"\n", __FILE__, __LINE__,\
      cudaGetErrorString(cudaGetLastError()));\
   exit(1);\
  }
#define ERRCHECK \
  if (cudaPeekAtLastError()) { \
    fprintf(stderr, "%s:%d Error [%s]\n", __FILE__, __LINE__,\
       cudaGetErrorString(cudaGetLastError()));\
    exit(1);\
  }

__global__ void MatSubt                 (float* A,    float* B,   float* C)
  {
  int x = threadIdx.x;
  int y = threadIdx.y;
  int id = blockDim.x*y+x;
  C[id]=A[id]-B[id];
  }
__global__ void inv_kernel              (float *a_i,  float *c_o, int n)
{
  int *p = (int *)malloc(3*sizeof(int));
  int *info = (int *)malloc(sizeof(int));
  int batch;
  cublasHandle_t hdl;
  cublasStatus_t status = cublasCreate_v2(&hdl);
  printf("handle %d n = %d\n", status, n);

  info[0] = 0;
  batch = 1;
  float **a = (float **)malloc(sizeof(float *));
  *a = a_i;
  const float **aconst = (const float **)a;
  float **c = (float **)malloc(sizeof(float *));
  *c = c_o;
  // See
  // http://docs.nvidia.com/cuda/pdf/CUDA_Dynamic_Parallelism_Programming_Guide.pdf
  //http://stackoverflow.com/questions/27094612/cublas-matrix-inversion-from-device
  status = cublasSgetrfBatched(hdl, n, a, n, p, info, batch);
  __syncthreads();
  printf("rf %d info %d\n", status, info[0]);
  status = cublasSgetriBatched(hdl, n, aconst, n, p,
      c, n, info, batch);
  __syncthreads();
  printf("ri %d info %d\n", status, info[0]);
  cublasDestroy_v2(hdl);
  printf("done\n");
}


using namespace cudaKalman;

C_cudaKalman::C_cudaKalman              (int dynamParams, int measureParams, int controlParams)
  {
  this->dynamParams = dynamParams;
  this->measureParams = measureParams;
  this->controlParams = controlParams;
  this->init();
  this->initMatrix(dynamParams,measureParams,controlParams);
  this->set_identity(dynamParams,measureParams,controlParams);

  }
C_cudaKalman::~C_cudaKalman             ()
  {
  deinit();
  deleteMatrix();
  }
void  C_cudaKalman::init                ()
  {
  cublasCreate(&this->handle);
  cublasSetStream(this->handle, this->streamkalman);
  }
void  C_cudaKalman::deinit              ()
  {
  cublasDestroy(this->handle);

  }
bool  C_cudaKalman::initMatrix          (int dynamParams, int measureParams, int controlParams)
  {
  this->dynamParams = dynamParams;
  this->measureParams = measureParams;
  this->controlParams = controlParams;
  //Erzeuge neue Arrays
  std::cout << "Creating Host CUDA Matrices" << std::endl;
//  a = (float *)malloc (M * N * sizeof (*a));
//  if (!a) {
//      printf ("host memory allocation failed");
//      return EXIT_FAILURE;
//  }
//  for (j = 0; j < N; j++) {
//      for (i = 0; i < M; i++) {
//          a[IDX2C(i,j,M)] = (float)(i * M + j + 1);
//      }
//  }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->statePre                = (float*)malloc(1*dynamParams*sizeof(this->statePre));
  this->statePost               = (float*)malloc(1*dynamParams*sizeof(this->statePre));
  for (int j = 1; j <= 1; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
      this->statePre[IDX2C(i,j,dynamParams)]                = (float)(i * dynamParams + j + 1);
      this->statePost[IDX2C(i,j,dynamParams)]               = (float)(i * dynamParams + j + 1);
      }
    }
  for (int j = 1; j <= 1; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
      this->statePre[IDX2C(i,j,dynamParams)]                = 0.0f;
      this->statePre[IDX2C(i,j,dynamParams)]                = 0.0f;
      }
    }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->transitionMatrix        = (float*)malloc(dynamParams*dynamParams*sizeof(this->transitionMatrix));
  this->processNoiseCov         = (float*)malloc(dynamParams*dynamParams*sizeof(this->processNoiseCov));
  this->errorCovPre             = (float*)malloc(dynamParams*dynamParams*sizeof(this->errorCovPre));
  this->errorCovPost            = (float*)malloc(dynamParams*dynamParams*sizeof(this->errorCovPost));
  for (int j = 1; j <= dynamParams; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
      this->transitionMatrix[IDX2C(i,j,dynamParams)]        = (float)(i * dynamParams + j + 1);
      this->processNoiseCov[IDX2C(i,j,dynamParams)]         = (float)(i * dynamParams + j + 1);
      this->errorCovPre[IDX2C(i,j,dynamParams)]             = (float)(i * dynamParams + j + 1);
      this->errorCovPost[IDX2C(i,j,dynamParams)]            = (float)(i * dynamParams + j + 1);
      }
    }
  for (int j = 1; j <= dynamParams; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
        this->transitionMatrix[IDX2C(i,j,dynamParams)]        = 0.0f;
        this->processNoiseCov[IDX2C(i,j,dynamParams)]         = 0.0f;
        this->errorCovPre[IDX2C(i,j,dynamParams)]             = 0.0f;
        this->errorCovPost[IDX2C(i,j,dynamParams)]            = 0.0f;
      }
    }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->measurementMatrix       = (float*)malloc(measureParams*dynamParams*sizeof(this->measurementMatrix));
  for (int j = 1; j <= dynamParams; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
      this->measurementMatrix[IDX2C(i,j,measureParams)]       = (float)(i * measureParams + j + 1);
      }
    }
  for (int j = 1; j <= dynamParams; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
        this->measurementMatrix[IDX2C(i,j,measureParams)]         = 0.0f;
      }
    }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->measurementNoiseCov     = (float*)malloc(measureParams*measureParams*sizeof(this->measurementMatrix));
  for (int j = 1; j <= measureParams; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
      this->measurementNoiseCov[IDX2C(i,j,measureParams)]       = (float)(i * measureParams + j + 1);
      }
    }
  for (int j = 1; j <= measureParams; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
        this->measurementNoiseCov[IDX2C(i,j,measureParams)]         = 0.0f;
      }
    }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->measurement             = (float*)malloc(measureParams*1*sizeof(this->measurement));
  for (int j = 1; j <= 1; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
      this->measurement[IDX2C(i,j,measureParams)]           = (float)(i * measureParams + j + 1);
      }
    }
  for (int j = 1; j <= 1; j++)
    {
    for (int i = 1; i <= measureParams; i++)
      {
      this->measurement[IDX2C(i,j,measureParams)]         = 0.0f;
      }
    }
                                                //ROWS * COLS * SIZEOF(FLOAT)
  this->gain                   = (float*)malloc(dynamParams*measureParams*sizeof(this->gain));
  for (int j = 1; j <= measureParams; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
      this->measurementNoiseCov[IDX2C(i,j,dynamParams)]       = (float)(i * dynamParams + j + 1);
      }
    }
  for (int j = 1; j <= measureParams; j++)
    {
    for (int i = 1; i <= dynamParams; i++)
      {
        this->measurementNoiseCov[IDX2C(i,j,dynamParams)]      = 0.0f;
      }
    }

  if( controlParams > 0 )
    {
    this->controlMatrix = new float[dynamParams*controlParams];
    this->controlVector = new float[controlParams];
    }
  std::cout << "Creation of Host CUDA Matrices successful" << std::endl;


  //Schreibe die Initialwerte in die jeweiligen Matrizen
  std::cout << "Creating Device CUDA Matrices" << std::endl;

  cudaStat = cudaMalloc ((void**)&statePre_devPtr, dynamParams*sizeof(*statePre));
  ALERT(cudaStat, "statePre device memory allocation failed");
  this->print_matrix(statePre, dynamParams, 1, "statePre");

  cudaStat = cudaMalloc ((void**)&statePost_devPtr, dynamParams*sizeof(*statePost));
  ALERT(cudaStat, "statePost device memory allocation failed");
  this->print_matrix(statePost, dynamParams, 1, "statePost");

  cudaStat = cudaMalloc ((void**)&transitionMatrix_devPtr, dynamParams*dynamParams*sizeof(*transitionMatrix));
  ALERT(cudaStat, "transitionMatrix device memory allocation failed");
  this->print_matrix(transitionMatrix, dynamParams, dynamParams, "transitionMatrix");

  cudaStat = cudaMalloc ((void**)&processNoiseCov_devPtr, dynamParams*dynamParams*sizeof(*processNoiseCov));
  ALERT(cudaStat, "processNoiseCov device memory allocation failed");
  this->print_matrix(processNoiseCov, dynamParams, dynamParams, "processNoiseCov");

  cudaStat = cudaMalloc ((void**)&measurementMatrix_devPtr, measureParams*dynamParams*sizeof(*measurementMatrix));
  ALERT(cudaStat, "measurementMatrix device memory allocation failed");
  this->print_matrix(measurementMatrix, measureParams, dynamParams, "measurementMatrix");

  cudaStat = cudaMalloc ((void**)&measurementNoiseCov_devPtr, measureParams*measureParams*sizeof(*measurementNoiseCov));
  ALERT(cudaStat, "measurementNoiseCov device memory allocation failed");
  this->print_matrix(measurementNoiseCov, measureParams, measureParams, "measurementNoiseCov");

  cudaStat = cudaMalloc ((void**)&measurement_devPtr, measureParams*sizeof(*measurement));
  ALERT(cudaStat, "measurement device memory allocation failed");
  this->print_matrix(measurement, measureParams, 1, "measurement");

  cudaStat = cudaMalloc ((void**)&errorCovPre_devPtr, dynamParams*dynamParams*sizeof(*errorCovPre));
  ALERT(cudaStat, "errorCovPre device memory allocation failed");
  this->print_matrix(errorCovPre, dynamParams, dynamParams, "errorCovPre");

  cudaStat = cudaMalloc ((void**)&errorCovPost_devPtr, dynamParams*dynamParams*sizeof(*errorCovPost));
  ALERT(cudaStat, "errorCovPost device memory allocation failed");
  this->print_matrix(errorCovPost, dynamParams, dynamParams, "errorCovPost");

  cudaStat = cudaMalloc ((void**)&gain_devPtr, dynamParams*measureParams*sizeof(*gain));
  ALERT(cudaStat, "gain device memory allocation failed");
  this->print_matrix(gain, dynamParams, measureParams, "gain");

  cudaStat = cudaMalloc ((void**)&temp1_devPtr, dynamParams*dynamParams*sizeof(float));
  ALERT(cudaStat, "temp1 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp2_devPtr, measureParams*dynamParams*sizeof(float));
  ALERT(cudaStat, "temp2 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp3_devPtr, measureParams*measureParams*sizeof(float));
  ALERT(cudaStat, "temp3 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp3_inv_devPtr, measureParams*measureParams*sizeof(float));
  ALERT(cudaStat, "temp3_inv device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp4_devPtr, measureParams*dynamParams*sizeof(float));
  ALERT(cudaStat, "temp4 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp5_devPtr, measureParams*sizeof(float));
  ALERT(cudaStat, "temp5 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp6_devPtr, dynamParams*dynamParams*sizeof(float));
  ALERT(cudaStat, "temp6 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp7_devPtr, measureParams*measureParams*sizeof(float));
  ALERT(cudaStat, "temp7 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp8_devPtr, measureParams*sizeof(float));
  ALERT(cudaStat, "temp8 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp9_devPtr, dynamParams*sizeof(float));
  ALERT(cudaStat, "temp9 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp10_devPtr, dynamParams*dynamParams*sizeof(float));
  ALERT(cudaStat, "temp10 device memory allocation failed");


  if( controlParams !=0 )
    {
    cudaStat = cudaMalloc ((void**)&controlMatrix_devPtr, dynamParams*controlParams*sizeof(*controlMatrix));
    ALERT(cudaStat, "controlMatrix device memory allocation failed");

    cudaStat = cudaMalloc ((void**)&controlValue_devPtr, controlParams*sizeof(*controlVector));
    ALERT(cudaStat, "controlVector device memory allocation failed");

    cudaStat = cudaMalloc ((void**)&temp11_devPtr, dynamParams*dynamParams*sizeof(float));
    ALERT(cudaStat, "temp11 device memory allocation failed");
    }
  std::cout << "Creation of Device CUDA Matrices successful" << std::endl;
  return 0;
  }

int   C_cudaKalman::set_identity        (int dynamParams, int measureParams, int controlParams)
  {
  std::cout << "Setting Device CUDA Matrices identity" << std::endl;

  for(int i=0;i<dynamParams*dynamParams;i++)
    {
    if(i%dynamParams+1==0 | i == 0)
      {
      this->transitionMatrix[i] = 1.0;
      this->processNoiseCov[i] = 1.0;
      }
    else
      {
      this->transitionMatrix[i] = 0.0;
      this->processNoiseCov[i] = 0.0;
      }
    }
  this->print_matrix(transitionMatrix, dynamParams, dynamParams, "transitionMatrix");
  this->print_matrix(processNoiseCov, dynamParams, dynamParams, "processNoiseCov");

  for(int i=0;i<measureParams*measureParams;i++)
    {
    if(i%measureParams+1==0 | i == 0)
      {
      this->measurementNoiseCov[i] = 1.0;
      }
    else
      {
      this->measurementNoiseCov[i] = 0.0;
      }
    }
  this->print_matrix(measurementNoiseCov, measureParams, measureParams, "measurementNoiseCov");

  for(int i=0;i<measureParams*dynamParams;i++)
    {
    if(i%measureParams+1==0 | i == 0)
      {
      this->measurementMatrix[i] = 1.0;
      }
    else
      {
      this->measurementMatrix[i] = 0.0;
      }
    }
  this->print_matrix(measurementMatrix, measureParams, dynamParams, "measurementMatrix");

  for(int i=0;i<dynamParams*measureParams;i++)
    {
    if(i%dynamParams+1==0 | i == 0)
      {
      this->gain[i] = 1.0;
      }
    else
      {
      this->gain[i] = 0.0;
      }
    }
  this->print_matrix(gain, dynamParams, measureParams, "gain");

  stat =  cublasSetMatrix(dynamParams, dynamParams, sizeof(float), transitionMatrix, dynamParams, transitionMatrix_devPtr, dynamParams);
  ALERT(stat, "cublasSetMatrix transitionMatrix failed");

  stat =  cublasSetMatrix(dynamParams, dynamParams, sizeof(float), processNoiseCov, dynamParams, processNoiseCov_devPtr, dynamParams);
  ALERT(stat, "cublasSetMatrix processNoiseCov failed");

  stat =  cublasSetMatrix(measureParams, measureParams, sizeof(float), measurementNoiseCov, measureParams, measurementNoiseCov_devPtr, measureParams);
  ALERT(stat, "cublasSetMatrix measurementNoiseCov failed");

  stat =  cublasSetMatrix(measureParams, dynamParams, sizeof(float), measurementMatrix, measureParams, measurementMatrix_devPtr, measureParams);
  ALERT(stat, "cublasSetMatrix measurementMatrix failed");

  stat =  cublasSetMatrix(dynamParams, measureParams, sizeof(float), gain, dynamParams, gain_devPtr, dynamParams);
  ALERT(stat, "cublasSetMatrix gain failed");

  if(controlParams > 0)
    {
    for(int i = 0; i < controlParams; i++)
      {
      this->controlVector[i] = -9.807f;
      }
    stat =  cublasSetVector(controlParams, sizeof(float), controlVector, 1, controlValue_devPtr, 1);
    ALERT(stat, "cublasSetMatrix gain failed");
    }
  else
    {
    std::cout << "Setting Device CUDA Matrices identity successful" << std::endl;
    }
  return 0;

  }
bool  C_cudaKalman::deleteMatrix        ()
  {
  free(this->statePre);
  free(this->statePost);
  free(this->transitionMatrix);
  free(this->processNoiseCov);
  free(this->errorCovPre);
  free(this->errorCovPost);
  free(this->measurementMatrix);
  free(this->measurementNoiseCov);
  free(this->measurement);
  free(this->gain);

  cudaFree(this->statePre_devPtr);
  cudaFree(this->statePost_devPtr);
  cudaFree(this->transitionMatrix_devPtr);
  cudaFree(this->processNoiseCov_devPtr);
  cudaFree(this->errorCovPre_devPtr);
  cudaFree(this->errorCovPost_devPtr);
  cudaFree(this->measurementMatrix_devPtr);
  cudaFree(this->measurementNoiseCov_devPtr);
  cudaFree(this->measurement_devPtr);
  cudaFree(this->gain_devPtr);
  if(this->controlParams > 0)
    {
    cudaFree(this->controlMatrix_devPtr);
    cudaFree(this->controlValue_devPtr);
    }

  cudaFree(this->temp1_devPtr);
  cudaFree(this->temp2_devPtr);
  cudaFree(this->temp3_devPtr);
  cudaFree(this->temp3_inv_devPtr);
  cudaFree(this->temp4_devPtr);
  cudaFree(this->temp5_devPtr);
  cudaFree(this->temp6_devPtr);
  cudaFree(this->temp7_devPtr);
  cudaFree(this->temp8_devPtr);
  cudaFree(this->temp9_devPtr);
  cudaFree(this->temp10_devPtr);
  cudaFree(this->temp11_devPtr);
  return true;

  }

int   C_cudaKalman::h_firstMeasurement  (float x, float y, float z, float vx, float vy, float vz, float errorCovPre)
  {
  std::cout << "##################################### h_firstMeasurement called ################################" << std::endl;
  this->measurement[0] = x;
  this->measurement[1] = y;
  this->measurement[2] = z;
  this->measurement[3] = vx;
  this->measurement[4] = vy;
  this->measurement[5] = vz;
  this->measurement[8] = -9.807f;

  this->print_matrix(this->measurement, dynamParams, 1, " STEP FIRST HIT - measurement:");

  stat = cublasSetVector(measureParams, sizeof(float), this->measurement, 1, this->measurement_devPtr, 1);
  ALERT(stat, "h_firstMeasurement - cublasSetVector Measurement failed");

  //  a = (float *)malloc (M * N * sizeof (*a));
  //  if (!a) {
  //      printf ("host memory allocation failed");
  //      return EXIT_FAILURE;
  //  }
  for (int j = 0; j < dynamParams; j++)
    {
    for (int i = 0; i < dynamParams; i++)
      {
        if(i ==j)
          {
          this->errorCovPre[IDX2C(i,j,dynamParams)] = errorCovPre;
          }
        else
          {
          this->errorCovPre[IDX2C(i,j,dynamParams)] = 0.0f;
          }
      }
    }

  return 0;
  }
int   C_cudaKalman::h_correct(float x, float y, float z)
  {
  std::cout << "##################################### h_correct called ################################" << std::endl;
  this->measurement[IDX2C(0,1,measureParams)] = x;
  this->measurement[IDX2C(1,1,measureParams)] = y;
  this->measurement[IDX2C(2,1,measureParams)] = z;
  stat = cublasSetVector(measureParams, sizeof(float), this->measurement, 1, this->measurement_devPtr, 1);
  ALERT(stat, "h_correct - cublasSetVector Measurement failed");
  this->d_correct();
  //ALTERNATIVE
  //d_correct<<<1,1>>>();
  return 0;

  }
int   C_cudaKalman::h_predict(float dt)
  {
  std::cout << "##################################### h_predict called ################################" << std::endl;

  //  a = (float *)malloc (M * N * sizeof (*a));
  //Set identity
  for (int j = 0; j < dynamParams; j++)
    {
    for (int i = 0; i < dynamParams; i++)
      {
      if(j == i)
        {
        this->transitionMatrix[IDX2C(i,j,dynamParams)] = 1.0f;
        }
      else
        {
        this->transitionMatrix[IDX2C(i,j,dynamParams)] = 0.0f;
        }
      }
    }

  //set dt
  for (int i = 0; i < dynamParams*dynamParams; i++)
    {
    if(i == 3 | i %10 == 3)
      {
      this->transitionMatrix[i] = dt;
      }
    else if (i == 6 | i %10 == 6 && i << 30)
      {
      this->transitionMatrix[i] = 0.5*(std::pow(dt, 2));
      }
    }

  this->print_matrix(this->transitionMatrix, dynamParams, dynamParams, " STEP CORRECTION - TransitionMatrix:");
  stat = cublasSetMatrix(dynamParams, dynamParams, 1, this->transitionMatrix, dynamParams, this->transitionMatrix_devPtr, dynamParams);
  ALERT(stat, "h_predict - cublasSetMatrix transitionMatrix failed");

  this->d_predict();
  return 0;

  }


int   C_cudaKalman::d_correct           ()
  {
  //############################################## Sgemm_v2 ##############################
  // Calculate: c = (alpha*a) * b + (beta*c)
  // MxN = MxK * KxN
  // Signature: handle, operation, operation, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc
  //############################################## Sgeam ##############################
  //Calculate: c = (alpha*A) + (beta*B)
  // MxN = Mx + xB
  // Signature: handle, operation, operation, M, N, alpha, A, lda, beta, B, ldb, C, ldc
  //############################################## Sgemv_v2 ##############################
  //Calculate: y = (alpha*A)*x + (beta*y)
  // MxN = MxN
  // Signature: handle, operation, operation, M, N, alpha, A, lda, beta, B, ldb, C, ldc
  //######################################################################################
  const float* alpha = new float {1.0f};
  const float* beta = new float {0.0f};
  stat = cublasSgemm_v2   (this->handle, CUBLAS_OP_N, CUBLAS_OP_N,measureParams,dynamParams,dynamParams,
                          alpha, this->measurementMatrix_devPtr, measureParams, errorCovPre_devPtr, dynamParams, beta, this->temp2_devPtr, measureParams);
  ALERT                   (stat, "correct - temp2 = H*P'(k)");


  stat = cublasSgemm_v2   (this->handle, CUBLAS_OP_N, CUBLAS_OP_T,measureParams, measureParams, dynamParams,
                          alpha, temp2_devPtr, measureParams, measurementMatrix_devPtr, dynamParams, beta, this->temp7_devPtr, measureParams);
  ALERT                   (stat, "correct - temp7_devPtr = temp2*Ht");


  stat = cublasSgeam      (this->handle, CUBLAS_OP_N, CUBLAS_OP_N, measureParams, measureParams,
                          alpha, this->temp7_devPtr, measureParams, alpha, this->measurementNoiseCov_devPtr, measureParams, this->temp3_devPtr, measureParams);
  ALERT                   (stat, "correct - temp3 = temp7_devPtr + R failed");


  inv_kernel<<<1, 1>>>(temp3_devPtr, temp3_inv_devPtr, measureParams);


  stat = cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_N,measureParams, dynamParams, measureParams,
                        alpha, temp3_inv_devPtr, measureParams, temp2_devPtr, measureParams, beta, temp4_devPtr, measureParams);
  ALERT(stat, "correct - temp4 = temp3_inv * temp2");


  stat = cublasSgeam(this->handle, CUBLAS_OP_T, CUBLAS_OP_N, dynamParams, measureParams,
                     alpha, temp4_devPtr, measureParams, beta, this->gain_devPtr, dynamParams, this->gain_devPtr, dynamParams);
  ALERT(stat, "correct - K(k)=temp4_transposed");



  stat = cublasSgemv_v2(this->handle, CUBLAS_OP_N, measureParams,dynamParams, alpha, this->measurementMatrix_devPtr, measureParams,
                        this->statePre_devPtr, 1, beta, this->temp8_devPtr, 1);
  ALERT(stat, "correct - temp8 = H * x'(k)");


  MatSubt<<<1,measureParams>>>(measurement_devPtr, temp8_devPtr, temp5_devPtr);


  stat = cublasSgemv_v2(this->handle, CUBLAS_OP_N,dynamParams, measureParams, alpha,
                        this->gain_devPtr, dynamParams, this->temp5_devPtr, 1, beta, this->temp9_devPtr, 1); //y = (alpha*A)*x + (beta*Y)
  ALERT(stat, "correct - temp9 = K(k)* temp5");


  stat = cublasSgeam(this->handle, CUBLAS_OP_N, CUBLAS_OP_N, dynamParams, 1, alpha,
                     this->statePre, dynamParams, alpha, this->temp9_devPtr, dynamParams, this->statePost_devPtr, dynamParams);
  ALERT(stat, "correct - x(k) = x'(k) + temp9");


  stat = cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_N, dynamParams, dynamParams, measureParams, alpha,
                        this->gain_devPtr, dynamParams, temp2_devPtr, measureParams, beta, this->temp10_devPtr, dynamParams);
  ALERT(stat, "correct - temp10 = K(k)* temp2");


  MatSubt<<<1,dynamParams>>>(temp10_devPtr, errorCovPre_devPtr, errorCovPost_devPtr);
  return 0;

  }
int   C_cudaKalman::d_predict           ()
  {
  //CUDA MEMCOPY ALPHA BETA EMPTY
  const float* alpha = new float {1.0f};
  const float* beta = new float {0.0f};

  //update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  stat = cublasSgemv_v2(this->handle, CUBLAS_OP_N, dynamParams, dynamParams, alpha, this->transitionMatrix_devPtr, dynamParams, statePost_devPtr, 1, beta, this->statePre_devPtr, 1); //y = (alpha*A)*x + (beta*Y)
  ALERT(stat, "update - x'(k) = A*x(k)");

  if(this->controlParams > 0)
    {
    printf("Control activated\n");
    //NICHT GEBRAUCHT F�R STACHNISS MODELL
    // update error covariance matrices: temp1 = A*P(k)
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    cublasSgemv_v2(this->handle, CUBLAS_OP_N, dynamParams, controlParams, alpha, this->controlMatrix_devPtr, dynamParams, controlMatrix_devPtr, 1, alpha, this->statePre_devPtr, 1); //y = (alpha*A)*x + (beta*Y)
    //cublasSaxpy_v2(this->handle, dynamParams*dynamParams, controlVector, controlMatrix_devPtr, 1, this->temp11_devPtr, 1);

    }

  // Calculate: c = (alpha*a) * b + (beta*c)
  // MxN = MxK * KxN
  // Signature: handle, operation, operation, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  stat = cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_N,dynamParams,dynamParams,dynamParams,alpha, this->transitionMatrix_devPtr, dynamParams, errorCovPost_devPtr, dynamParams, beta, this->temp1_devPtr, dynamParams);
  ALERT(stat, "update - temp1 = A*P(k)");

  // A_temp = temp1*At
  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  stat = cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_T, dynamParams, dynamParams, dynamParams, alpha, this->temp1_devPtr, dynamParams, this->transitionMatrix_devPtr, dynamParams, beta ,this->temp6_devPtr, dynamParams);
  ALERT(stat, "update - A_temp = temp1*At");

  // P'(k) = A_temp + Q
  stat = cublasSgeam(this->handle, CUBLAS_OP_N, CUBLAS_OP_N, dynamParams, dynamParams, alpha, this->temp6_devPtr, dynamParams, alpha, processNoiseCov_devPtr, dynamParams, errorCovPre_devPtr, dynamParams);
  ALERT(stat, "update - P'(k) = A_temp + Q");


  // handle the case when there will be measurement before the next predict.
  stat = cublasScopy_v2(this->handle, dynamParams, this->statePre_devPtr, 1, this->statePost_devPtr,1);
  ALERT(stat, "update - cublasScopy_v2 statePre");

  stat = cublasScopy_v2(this->handle, dynamParams*dynamParams, this->errorCovPre_devPtr, 1, this->errorCovPost_devPtr,1);
  ALERT(stat, "update - cublasScopy_v2 errorCovPre");
  return 0;

  }
void  C_cudaKalman::print_matrix        (const float *A, int nr_rows_A, int nr_cols_A, std::string Name)
  {//Print matrix A(nr_rows_A, nr_cols_A) storage in column-major format
  std::cout << Name << std::endl;
  for(int i = 0; i < nr_rows_A; ++i)
    {
    for(int j = 0; j < nr_cols_A; ++j)
      {
      std::cout << A[j * nr_rows_A + i] << " ";
      }
    std::cout << std::endl;
    }
  std::cout << std::endl;
  }

