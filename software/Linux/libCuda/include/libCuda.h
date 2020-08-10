#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <math.h>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"
#include "opencv2/cudaarithm.hpp"
#include "opencv2/core/cuda.hpp"

namespace cudaKernel
  {
    //float timing;
    const int CovSize = 5;
    const int PredictSize = 5;
    const int MeasureSize = 5;

   extern "C" void inRange_gpu (cv::cuda::GpuMat& src, cv::Scalar& lowerb, cv::Scalar& upperb,
                                cv::cuda::GpuMat& dst);

   extern "C" void predict_single (float* predict, float* cov, float* new_predict, float* new_cov, 						int point_num, float delta_t);

   extern "C" void update_single (float* data, float* predict, float* cov, float* new_predict, 						float* new_cov, int point_num, float delta_t, int ite_nem);

  }
