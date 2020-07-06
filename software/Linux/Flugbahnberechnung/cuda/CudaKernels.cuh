#pragma once
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
    void inRange_gpu (cv::cuda::GpuMat& src, cv::Scalar& lowerb, cv::Scalar& upperb,
                      cv::cuda::GpuMat& dst);
  }
