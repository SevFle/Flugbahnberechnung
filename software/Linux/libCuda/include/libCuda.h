#pragma once
#ifndef __libCuda_H
#define __libCuda_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <math.h>
#include <iostream>

#include "cuda_runtime.h"
#include "cuda.h"
#include "device_launch_parameters.h"

#include <cublas_v2.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/core/cuda.hpp"
//CUDA Code ist immer C bzw subclass von C! Keine OO Programmierung möglich.


namespace onCuda
  {
  namespace imageProcessing
    {
    extern "C" void inRange (cv::cuda::GpuMat& src, cv::Scalar& lowerb, cv::Scalar& upperb,
                               cv::cuda::GpuMat& dst);
    }
  namespace KalmanFilter
    {
    class C_kalman
    {
    C_kalman();
    ~C_kalman();

    /*************************************** Variable declarations ************************************************/

    private:
    cublasStatus_t* stat;
    cublasHandle_t* handle;

    int ns = 10, no = 5;
    int dev = 0;

    float *X;//Estimate
    float *h_X;//Estimate
    float *P;//Uncertainity Covariance t
    float *F;//State transition Matrix
    float *Z;//Measurement
    float *S;//Intermediate value
    float *s;//Intermediate value
    float *si;//Intermediate value
    float *K;//Kalman gain
    float *H;//Measurement function
    float *E;//Measurement noise
    float *Ft;//F transpose
    float *Ht;//H transpose
    float *Si;//Inverse of S
    float *Y; //error
    float I;//Identity Matrix
    float *Hint;//for intermediate calculations
    float *Sint;//for intermediate calculations
    float *Kint;//for intermediate calculations
    float *Xint;// for intermediate calculations
    float *Pint;// for intermediate calculations
    float *Pint2;// for intermediate calculations
    float *Ztemp;//to  store temporarily
    int meslen = 1;//number of iterations

    //Device Variable declarations
     float *d_X;//Estimate
     float *d_P;//Uncertainity Covariance
     float *d_F;//State transition Matrix
     float *d_Z;//Measurement
     float *d_S;//Intermediate value
     float *d_s;//Intermediate value
     float *d_K;//Kalman gain
     float *d_H;//Measurement function
     float *d_E;//Measurement noise
     float *d_Ft;//F transpose
     float *d_Ht;//H transpose
     float *d_Si;//Inverse of S
     float *d_Y; //error
     float *d_I;//Identity Matrix


    float *d_Hint;//for intermediate calculations
    float *d_Sint;//for intermediate calculations
    float *d_Kint;//for intermediate calculations
    float *d_Xint;// for intermediate calculations
    float *d_Pint;// for intermediate calculations
    float *d_Pint2;// for intermediate calculations
    float *d_Ztemp;//to  store temporarily


    float *A;
    int lda;

    int threadsPerBlock;
    int Nos;
    int Ns;
    int No;
    int Ns2;
    int No2;
    int blocksPerGridNos;
    int blocksPerGridNs;
    int blocksPerGridNo;
    int blocksPerGridNs2;
    int blocksPerGridNo2;

    /*************************************** Function declarations ************************************************/
    public:
    void allocateMemory ();

    private:
    void initialize     (float *F_stateTransitionModel, float *H_observationModel,float *E,float *s, int ns, int no);
    void correct        (float *measurement);
    float predict       ();
    void setTimePoint   (int time);
    void cleanup        ();

    };//class Kalman
    }//namespace Kalmanfilter
  namespace KalmanFilter2
    {
    class C_kalman
      {
      C_kalman(float* h_A,int rowsA, int colsA, float* B, int measurementsB, float*H, int rowsH, int colsH);
      ~C_kalman();

      cublasStatus_t* stat;
      cublasHandle_t* handle;

    private:
      int init(float* h_A,int rowsA, int colsA, float* B, int measurementsB, float*H, int rowsH, int colsH);
      void rowToColumnMajor(float* Input, float* Output, int rows, int cols);
      int allocateFloat(float* devPtrA, int m, int n);
    public:
      int setQ(float* h_Q, int rowsQ, int colsQ);
      int setR(float* h_R, int rowsR, int colsR);
      void predict_single(float* predict, float* covD, float* new_predict, float* new_covD, int point_num, float delta_t);
      void update_single(float* data, float* predict, float* covD, float* new_predict, float* new_covD, int point_num, float delta_t, int ite_num);
      };
    }
}//namespace onCuda

#endif


