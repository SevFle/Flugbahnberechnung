#include "cudaKalman.cuh"
#include <stdio.h>
#include <iostream>

#define IDX2C(i,j,ld) (((j)*(ld))+(i))

#define ALERT(cudaStat, message)   if (cudaStat != cudaSuccess){ printf (message); return EXIT_FAILURE;}




using namespace cudaKalman;

C_cudaKalman::C_cudaKalman()
  {
  init();
  initMatrix(9,3,0);
  }
C_cudaKalman::~C_cudaKalman()
  {

  }
void C_cudaKalman::init               ()
  {
  std::cout << "hello from inti" << std::endl;
  cublasCreate(&this->handle);
  cublasSetStream(this->handle, this->streamkalman);

  }
void C_cudaKalman::deinit             ()
  {
  cublasDestroy(this->handle);

  }

__host__ bool C_cudaKalman::initMatrix         (int dynamParams, int measureParams, int controlParams)
  {
  this->dynamParams = dynamParams;
  this->measureParams = measureParams;
  this->controlParams = controlParams;
  //Erzeuge neue Arrays
  std::cout << "Creating Host CUDA Matrices" << std::endl;
  //this->statePre= new float[dynamParams];


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



  this->statePre = (float*)malloc(1*dynamParams*sizeof(this->statePre));
  this->statePost = (float*)malloc(1*dynamParams*sizeof(this->statePre));

  for (int j = 1; j <= dynamParams; j++)
    {
      for (int i = 1; i <= 1; i++)
        {
          this->statePre[IDX2C(i,j,1)] = (float)(i * 1 + j + 1);
          this->statePre[IDX2C(i,j,1)] = (float)(i * 1 + j + 1);
      }
    }
  for (int j = 1; j <= dynamParams; j++)
    {
      for (int i = 1; i <= 1; i++)
        {
          this->statePre[IDX2C(i,j,1)] = 0.0;
          this->statePre[IDX2C(i,j,1)] = 0.0;
      }
    }

  this->transitionMatrix = new float[dynamParams*dynamParams];
  this->transitionMatrix_temp = new float[dynamParams*dynamParams];

  this->transitionMatrix = (float*)malloc(dynamParams*dynamParams*sizeof(this->transitionMatrix));
  this->transitionMatrix_temp = (float*)malloc(dynamParams*dynamParams*sizeof(this->transitionMatrix_temp));


  this->processNoiseCov = new float[dynamParams*dynamParams];
  this->temp1 = new float[dynamParams*dynamParams];

  this->measurementMatrix = new float[measureParams*dynamParams];
  this->temp2 = new float[measureParams*dynamParams];
  this->temp2_temp = new float[measureParams*dynamParams];
  this->temp4 = new float[measureParams*dynamParams];
  for(int i=0;i<measureParams*dynamParams;i++)
    {
    this->measurementMatrix[i]=0.0;
    this->temp2[i]=0.0;
    this->temp4[i]=0.0;
    }

  this->measurementNoiseCov = new float[measureParams*measureParams];
  this->temp3 = new float[measureParams*measureParams];
  for(int i=0;i<measureParams*measureParams;i++)
    {
    this->measurementNoiseCov[i]=0.0;
    this->temp3[i]=0.0;
    }

  this->measurement = new float[measureParams];
  this->temp5 = new float[measureParams];
  for(int i=0;i<measureParams;i++)
    {
    this->measurement[i]=0.0;
    this->temp5[i]=0.0;
    }


  this->errorCovPre = new float[dynamParams*dynamParams];
  this->errorCovPost = new float[dynamParams*dynamParams];
  for(int i=0;i<dynamParams*dynamParams;i++)
    {
    this->errorCovPre[i]=0.0;
    this->errorCovPost[i]=0.0;
    this->transitionMatrix[i]=0.0;
    this->processNoiseCov[i]=0.0;
    }


  this->gain = new float[dynamParams*measureParams];
  if( controlParams > 0 )
    {
    this->controlMatrix = new float[dynamParams*controlParams];
    this->controlVector = new float[controlParams];
    }

  if (!statePre | !statePost |!transitionMatrix | !processNoiseCov |!measurementMatrix | !measurementNoiseCov |!measurement | !errorCovPre |!errorCovPost)
    {
    return false;
    }
  std::cout << "Creation of Host CUDA Matrices successful" << std::endl;


  //Schreibe die Initialwerte in die jeweiligen Matrizen
  std::cout << "Creating Device CUDA Matrices" << std::endl;

  cudaStat = cudaMalloc ((void**)&statePre_devPtr, dynamParams*sizeof(*statePre));
  ALERT(cudaStat, "statePre device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&statePost_devPtr, dynamParams*sizeof(*statePost));
  ALERT(cudaStat, "statePost device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&transitionMatrix_devPtr, dynamParams*dynamParams*sizeof(*transitionMatrix));
  ALERT(cudaStat, "transitionMatrix device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&transitionMatrix_temp_devPtr, dynamParams*dynamParams*sizeof(*transitionMatrix_temp));
  ALERT(cudaStat, "transitionMatrix device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&processNoiseCov_devPtr, dynamParams*dynamParams*sizeof(*processNoiseCov));
  ALERT(cudaStat, "processNoiseCov device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&measurementMatrix_devPtr, measureParams*dynamParams*sizeof(*measurementMatrix));
  ALERT(cudaStat, "measurementMatrix device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&measurementNoiseCov_devPtr, measureParams*measureParams*sizeof(*measurementNoiseCov));
  ALERT(cudaStat, "measurementNoiseCov device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&measurement_devPtr, measureParams*sizeof(*measurement));
  ALERT(cudaStat, "measurement device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&errorCovPre_devPtr, dynamParams*dynamParams*sizeof(*errorCovPre));
  ALERT(cudaStat, "errorCovPre device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&errorCovPost_devPtr, dynamParams*dynamParams*sizeof(*errorCovPost));
  ALERT(cudaStat, "errorCovPost device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&gain_devPtr, dynamParams*measureParams*sizeof(*gain));
  ALERT(cudaStat, "gain device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp1_devPtr, dynamParams*dynamParams*sizeof(*temp1));
  ALERT(cudaStat, "temp1 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp2_devPtr, measureParams*dynamParams*sizeof(*temp2));
  ALERT(cudaStat, "temp2 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp2_temp_devPtr, measureParams*dynamParams*sizeof(*temp2_temp));
  ALERT(cudaStat, "temp2 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp3_devPtr, measureParams*measureParams*sizeof(*temp3));
  ALERT(cudaStat, "temp3 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp4_devPtr, measureParams*dynamParams*sizeof(*temp4));
  ALERT(cudaStat, "temp4 device memory allocation failed");

  cudaStat = cudaMalloc ((void**)&temp5_devPtr, measureParams*sizeof(*temp5));
  ALERT(cudaStat, "temp5 device memory allocation failed");


  if( controlParams > 0 )
    {
    cudaStat = cudaMalloc ((void**)&controlMatrix_devPtr, dynamParams*controlParams*sizeof(*controlMatrix));
    ALERT(cudaStat, "controlMatrix device memory allocation failed");

    cudaStat = cudaMalloc ((void**)&controlVector_devPtr, controlParams*sizeof(*controlVector));
    ALERT(cudaStat, "controlVector device memory allocation failed");
    }
  std::cout << "Creation of Device CUDA Matrices successful" << std::endl;

  set_identity(dynamParams, measureParams, controlParams);
  }

__host__ int C_cudaKalman::set_identity(int dynamParams, int measureParams, int controlParams)
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
    stat =  cublasSetVector(controlParams, sizeof(float), controlVector, 1, controlVector_devPtr, 1);
    ALERT(stat, "cublasSetMatrix gain failed");


    }
  std::cout << "Setting Device CUDA Matrices identity successful" << std::endl;

  }
bool C_cudaKalman::deleteMatrix()
  {
  delete [] this->statePre;
  delete [] this->statePost;

  }
__device__ void C_cudaKalman::correct            ()
  {
  const float* alpha = new float {1.0f};
  const float* beta = new float {0.0f};
  // temp2 = H*P'(k)
  // temp2 = measurementMatrix * errorCovPre;
  cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_N,measureParams,measureParams,measureParams,alpha, this->measurementMatrix_devPtr, measureParams, errorCovPre_devPtr, dynamParams, beta, this->temp2_devPtr, measureParams);

  // temp2_temp = temp2*Ht
  //gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
  // Calculate: c = (alpha*a) * b + (beta*c)
  // MxN = MxK * KxN
  // Signature: handle, operation, operation, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc
  cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_T,measureParams, dynamParams, measureParams, alpha, temp2_devPtr, measureParams, measurementMatrix_devPtr, measureParams, beta, temp2_temp_devPtr, measureParams);

  // temp2 = temp2_temp + R
  cublasSgeam(this->handle, CUBLAS_OP_N, CUBLAS_OP_N, measureParams, measureParams, alpha, this->temp2_temp_devPtr, measureParams, alpha, this->measurementNoiseCov_devPtr, measureParams, this->temp2_devPtr, measureParams);



  }
__device__ void C_cudaKalman::predict            ()
  {
  //CUDA MEMCOPY ALPHA BETA EMPTY
  const float* alpha = new float {1.0f};
  const float* beta = new float {0.0f};
//  This function performs the matrix-matrix multiplication
//  C = ? op ( A ) op ( B ) + ? C
//  where ? and ? are scalars, and A , B and C are matrices stored in column-major format with dimensions op ( A ) m × k , op ( B ) k × n and C m × n , respectively. Also, for matrix A
//  op ( A ) = A if  transa == CUBLAS_OP_N A T if  transa == CUBLAS_OP_T A H if  transa == CUBLAS_OP_C
//  and op ( B ) is defined similarly for matrix B .


//  This function performs the matrix-vector multiplication
//  y = ? op ( A ) x + ? y
//  where A is a m × n matrix stored in column-major format, x and y are vectors, and ? and ? are scalars. Also, for matrix A
//   op ( A ) = A  if transa == CUBLAS_OP_N A T  if transa == CUBLAS_OP_T A H  if transa == CUBLAS_OP_H

  //update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  cublasSgemv_v2(this->handle, CUBLAS_OP_N, dynamParams, dynamParams, alpha, this->transitionMatrix_devPtr, dynamParams, statePost_devPtr, 1, beta, this->statePre_devPtr, 1);
  if(this->controlParams > 0)
    {
    //NICHT GEBRAUCHT FÜR STACHNISS MODELL
    // update error covariance matrices: temp1 = A*P(k)
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    __syncthreads();
    cublasSgemv_v2(this->handle, CUBLAS_OP_N, dynamParams, controlParams, alpha, this->controlMatrix_devPtr, dynamParams, controlMatrix_devPtr, 1, alpha, this->statePre_devPtr, 1);
    }

  // Calculate: c = (alpha*a) * b + (beta*c)
  // MxN = MxK * KxN
  // Signature: handle, operation, operation, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_N,dynamParams,dynamParams,dynamParams,alpha, this->transitionMatrix_devPtr, dynamParams, errorCovPost_devPtr, dynamParams, beta, this->temp1_devPtr, dynamParams);

  // A_temp = temp1*At
  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  cublasSgemm_v2(this->handle, CUBLAS_OP_N, CUBLAS_OP_T, dynamParams, dynamParams, dynamParams, alpha, this->temp1_devPtr, dynamParams, this->transitionMatrix_devPtr, dynamParams, beta ,this->transitionMatrix_temp_devPtr, dynamParams);

  // P'(k) = A_temp + Q
  cublasSgeam(this->handle, CUBLAS_OP_N, CUBLAS_OP_N, dynamParams, dynamParams, alpha, this->transitionMatrix_temp_devPtr, dynamParams, alpha, processNoiseCov_devPtr, dynamParams, errorCovPre_devPtr, dynamParams);

  // handle the case when there will be measurement before the next predict.
  //statePre.copyTo(statePost);
  //errorCovPre.copyTo(errorCovPost);
  cublasScopy_v2(this->handle, dynamParams, this->statePre_devPtr, 1, this->statePost_devPtr,1);
  cublasScopy_v2(this->handle, dynamParams, this->errorCovPre_devPtr, 1, this->errorCovPost_devPtr,1);

  }
void C_cudaKalman::firstMeasurement   ()
  {

  }
