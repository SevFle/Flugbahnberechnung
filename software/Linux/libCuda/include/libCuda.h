#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <math.h>
#include <iostream>

#include "cuda_runtime.h"
#include "cuda.h"
#include "device_launch_parameters.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/core/cuda.hpp"



//CUDA Code ist immer C bzw subclass von C! Keine OO Programmierung möglich.


namespace cudaKernel
  {
    //Variable declarations
    int ns = 10, no = 5;
    int dev = 0;

    float *X;//Estimate - Modellbildung in Form eines mehrdimensionalen Vektors X mit entsprechender Bewegungsgleichung, der sogenannten Zustandsgleichung
    float *h_X;//Estimate
    float *P;//Uncertainity Covariance t
    float *F;//State transition Matrix - Die Matrix F beschreibt die Übergänge zwischen zeitlich aufeinanderfolgenden Zuständen Xk-1 und Xk
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
    float *I;//Identity Matrix
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




   extern "C" void inRange_gpu (cv::cuda::GpuMat& src, cv::Scalar& lowerb, cv::Scalar& upperb,
                                cv::cuda::GpuMat& dst);

   extern "C" void predict_single (float* predict, float* cov, float* new_predict, float* new_cov, 						int point_num, float delta_t);

   extern "C" void update_single (float* data, float* predict, float* cov, float* new_predict, 						float* new_cov, int point_num, float delta_t, int ite_nem);

  }
