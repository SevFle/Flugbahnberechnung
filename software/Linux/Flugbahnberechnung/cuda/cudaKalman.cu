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
  this->statePre= new float[dynamParams];
  this->statePost= new float[dynamParams];

  this->transitionMatrix = new float[dynamParams*dynamParams];
  this->processNoiseCov = new float[dynamParams*dynamParams];

  this->measurementMatrix = new float[measureParams*dynamParams];
  this->measurementNoiseCov = new float[measureParams*measureParams];
  this->measurement = new float[measureParams];

  this->errorCovPre = new float[dynamParams*dynamParams];
  this->errorCovPost = new float[dynamParams*dynamParams];

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

  //Schreibe die Initialwerte in die jeweiligen Matrizen



//  for (j = 0; j < dynamParams; j++)
//    {
//    a[IDX2C(i,j,M)] = (float)(i * M + j + 1);
//    }

//  cudaStat = cudaMalloc ((void**)&devPtrA, M*N*sizeof(*a));
//  if (cudaStat != cudaSuccess) {
//      printf ("device memory allocation failed");
//      return EXIT_FAILURE;
//  }

  }
bool C_cudaKalman::deleteMatrix()
  {
  delete [] this->statePre;
  delete [] this->statePost;

  }
