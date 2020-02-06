#pragma unmanaged
#pragma once

#include "OpenCV_unmanaged.h"

using namespace nmsp_open_cv_unmanaged;



C_opencv_unmanaged::C_opencv_unmanaged()
  {
  }

C_opencv_unmanaged::~C_opencv_unmanaged()
  {
  }


bool C_opencv_unmanaged::apply_filter (cv::Mat& cpu_src, cv::Mat& cpu_dst)
  {
  return false;
  }

bool C_opencv_unmanaged::create_camera_thread ()
  {
  camera_vector.push_back(camera_capture);
  camera_vector_count = camera_vector.size();
  start_camera_thread();
  }

bool C_opencv_unmanaged::start_camera_thread ()
  {



bool C_opencv_unmanaged::create_camera_threads_objectcalibration()
  {
  for (int i=0; i<6; i++)
    {
    create_camera_thread;
    }
  return false;
  }

void  thread_camera_grabbing (int cam_ID)
  {
  while (true)
    {

    }
  }

bool C_opencv_unmanaged::grab_frame(cv::Mat& cpu_dst)
  {

  return false;
  }

void C_opencv_unmanaged::push_to_gpu(cv::Mat& cpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  gpu_dst.upload(cpu_src);
  }

void C_opencv_unmanaged::pull_from_gpu(cv::cuda::GpuMat& gpu_src, cv::Mat& cpu_dst)
  {
  //cpu_dst.download(gpu_src);
  }

void C_opencv_unmanaged::to_hsv(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  }

void C_opencv_unmanaged::to_hsv_threshold(cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& hue_min, int& hue_max, int& saturation_min, int& saturation_max, int& value_min, int& value_max)
  {
  }

void C_opencv_unmanaged::to_resize(cv::Mat& cpu_src, cv::Mat& cpu_dst, int& size_x, int& size_y)
  {
  }

void C_opencv_unmanaged::erosion(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& erosion_kernel_size, int& erosion_iterations)
  {
  }

void C_opencv_unmanaged::dilation(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& dilation_kernel_size, int& dilation_iterations)
  {
  }

void C_opencv_unmanaged::opening(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& opening_kernel_size)
  {
  }

void C_opencv_unmanaged::closing(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& closing_kernel_size)
  {
  }

void C_opencv_unmanaged::bilateral(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& bilateral_kernel_size, float& bilateral_sigma_color, float& bilateral_sigma_space)
  {
  }

void C_opencv_unmanaged::gaussian_bluring(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& gaussian_kernel_size, double& gaussian_sigma)
  {
  }

void C_opencv_unmanaged::find_contours(cv::Mat & cpu_src, cv::Mat & cpu_dst)
  {
  }
