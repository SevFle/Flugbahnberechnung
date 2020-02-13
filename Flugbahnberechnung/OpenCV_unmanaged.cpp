#pragma once
/**** Includes ****************************************************************/
#pragma region Includes
#include "OpenCV_unmanaged.h"

/**** Include OpenCV ****************************************************************/
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
/**** Include TBB *******************************************************************/
#include <tbb/concurrent_queue.h>
#include <tbb/pipeline.h>
#include <tbb/tbb.h>

#pragma endregion

/**** Namespaces***************************************************************/
using namespace nmsp_open_cv_unmanaged;


c_opencv_unmanaged::c_opencv_unmanaged()
  {
  }

c_opencv_unmanaged::~c_opencv_unmanaged()
  {
  }


bool c_opencv_unmanaged::apply_filter (cv::Mat& cpu_src, cv::Mat& cpu_dst)
  {
  return false;
  }

bool c_opencv_unmanaged::create_camera_vector ()
  {
  for (int i =0; i<= this->cameras_in_use; i++)
    {
    camera_vector.push_back(camera_capture(i, capture_api_));
    return false;
    }
  return false;
  }
  
bool c_opencv_unmanaged::tbb_camera_pipeline (size_t ntoken)
  {
  /*tbb::parallel_pipeline
    (
    ntoken,
    tbb::make_filter<void, cv::Mat>
      (
  tbb::filter::serial_in_order,[&](tbb::flow_control& fc)-> cv::Mat
        {
        grabbed_frame = camera_vector[current_pipeline_camera_grab].grab;
        current_pipeline_camera_grab++;
        if (current_pipeline_camera_grab > cameras_in_use-1)
          {
          current_pipeline_camera_grab = 0;
          }
        return grabbed_frame;
        }
      ) &
    tbb::make_filter<cv::Mat, cv::Mat>
      (
  tbb::filter::parallel, [](cv::Mat)
        {
    
        }
      )
      
    )*/
  
  }

bool c_opencv_unmanaged::create_camera_threads_objectcalibration()
  {
  for (int i=0; i<6; i++)
    {
    //create_camera_thread;
    }
  return false;
  }

bool c_opencv_unmanaged::state_machine()
  {
  switch (statemachine_state)
    {
      case 1:

        statemachine_state = 2;

      case 2:

        statemachine_state = 3;

      case 3:

        statemachine_state = 4;

      case 4:

        statemachine_state = 5;

      case 5:

        statemachine_state = 6;

      case 6:

        statemachine_state = 1;

    }
  return false;
  }


bool c_opencv_unmanaged::grab_frame(cv::Mat& cpu_dst)
  {

  return false;
  }

void c_opencv_unmanaged::push_to_gpu(cv::Mat& cpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  }

void c_opencv_unmanaged::pull_from_gpu(cv::cuda::GpuMat& gpu_src, cv::Mat& cpu_dst)
  {
  }

void c_opencv_unmanaged::to_hsv(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  }

void c_opencv_unmanaged::to_hsv_threshold(cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& hue_min, int& hue_max, int& saturation_min, int& saturation_max, int& value_min, int& value_max)
  {
  }

void c_opencv_unmanaged::to_resize(cv::Mat& cpu_src, cv::Mat& cpu_dst, int& size_x, int& size_y)
  {
  }

void c_opencv_unmanaged::erosion(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& erosion_kernel_size, int& erosion_iterations)
  {
  }

void c_opencv_unmanaged::dilation(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& dilation_kernel_size, int& dilation_iterations)
  {
  }

void c_opencv_unmanaged::opening(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& opening_kernel_size)
  {
  }

void c_opencv_unmanaged::closing(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& closing_kernel_size)
  {
  }

void c_opencv_unmanaged::bilateral(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& bilateral_kernel_size, float& bilateral_sigma_color, float& bilateral_sigma_space)
  {
  }

void c_opencv_unmanaged::gaussian_bluring(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& gaussian_kernel_size, double& gaussian_sigma)
  {
  }

void c_opencv_unmanaged::find_contours(cv::Mat & cpu_src, cv::Mat & cpu_dst)
  {
  }
