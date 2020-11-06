#include "cudaKalman.cuh"
#include <stdio.h>
#include <iostream>


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

bool C_cudaKalman::initMatrix         (int dynamParams, int measureParams, int controlParams)
  {
  //Erzeuge neue Arrays
  std::cout << "Creating Host CUDA Matrices" << std::endl;
  this->statePre= new float[dynamParams];
  this->statePost= new float[dynamParams];
  for(int i=0;i<dynamParams;i++)
    {
    this->statePre[i]=0.0;
    this->statePost[i]=0.0;
    }

  this->transitionMatrix = new float[dynamParams*dynamParams];
  this->processNoiseCov = new float[dynamParams*dynamParams];

  this->measurementMatrix = new float[measureParams*dynamParams];
  for(int i=0;i<measureParams*dynamParams;i++)
    {
    this->measurementMatrix[i]=0.0;
    }

  this->measurementNoiseCov = new float[measureParams*measureParams];
  for(int i=0;i<measureParams*measureParams;i++)
    {
    this->measurementNoiseCov[i]=0.0;
    }

  this->measurement = new float[measureParams];
  for(int i=0;i<measureParams;i++)
    {
    this->measurement[i]=0.0;
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
  if (cudaStat != cudaSuccess)
    {
    printf ("statePre device memory allocation failed");
    return EXIT_FAILURE;
    }
  cudaStat = cudaMalloc ((void**)&statePost_devPtr, dynamParams*sizeof(*statePost));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }

  cudaStat = cudaMalloc ((void**)&transitionMatrix_devPtr, dynamParams*dynamParams*sizeof(*transitionMatrix));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePre device memory allocation failed");
    return EXIT_FAILURE;
    }
  cudaStat = cudaMalloc ((void**)&processNoiseCov_devPtr, dynamParams*dynamParams*sizeof(*processNoiseCov));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }

  cudaStat = cudaMalloc ((void**)&measurementMatrix_devPtr, measureParams*dynamParams*sizeof(*measurementMatrix));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePre device memory allocation failed");
    return EXIT_FAILURE;
    }
  cudaStat = cudaMalloc ((void**)&measurementNoiseCov_devPtr, measureParams*measureParams*sizeof(*measurementNoiseCov));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }
  cudaStat = cudaMalloc ((void**)&measurement_devPtr, measureParams*sizeof(*measurement));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }

  cudaStat = cudaMalloc ((void**)&errorCovPre_devPtr, dynamParams*dynamParams*sizeof(*errorCovPre));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePre device memory allocation failed");
    return EXIT_FAILURE;
    }
  cudaStat = cudaMalloc ((void**)&errorCovPost_devPtr, dynamParams*dynamParams*sizeof(*errorCovPost));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }

  cudaStat = cudaMalloc ((void**)&gain_devPtr, dynamParams*measureParams*sizeof(*gain));
  if (cudaStat != cudaSuccess)
    {
    printf ("statePost device memory allocation failed");
    return EXIT_FAILURE;
    }


  if( controlParams > 0 )
    {
    cudaStat = cudaMalloc ((void**)&controlMatrix_devPtr, dynamParams*controlParams*sizeof(*controlMatrix));
    if (cudaStat != cudaSuccess)
      {
      printf ("statePre device memory allocation failed");
      return EXIT_FAILURE;
      }
    cudaStat = cudaMalloc ((void**)&controlVector_devPtr, controlParams*sizeof(*controlVector));
    if (cudaStat != cudaSuccess)
      {
      printf ("statePost device memory allocation failed");
      return EXIT_FAILURE;
      }
    }
  std::cout << "Creation of Device CUDA Matrices successful" << std::endl;

  set_identity(dynamParams, measureParams, controlParams);
  }

void C_cudaKalman::set_identity(int dynamParams, int measureParams, int controlParams)
  {
  for(int i=0;i<dynamParams*dynamParams;i++)
    {
    if(i%dynamParams+1==0)
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
    if(i%measureParams+1==0)
      {
      this->measurementNoiseCov[i] = 1.0;
      }
    else
      {
      this->measurementNoiseCov[i] = 0.0;
      }
    }


  }
bool C_cudaKalman::deleteMatrix()
  {
  delete [] this->statePre;
  delete [] this->statePost;

  }
void C_cudaKalman::correct            ()
  {

  }
void C_cudaKalman::predict            ()
  {
  //CUDA MEMCOPY ALPHA BETA EMPTY
  float* empty = new float[1];
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

  cublasSgemv_v2(this->handle, CUBLAS_OP_N, dynamParams, dynamParams, alpha, this->transitionMatrix, dynamParams, statePost, 1, beta, empty, 1);



  }
void C_cudaKalman::firstMeasurement   ()
  {

  }
