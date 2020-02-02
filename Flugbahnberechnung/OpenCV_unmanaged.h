#pragma once
#include "OpenCV_unmanaged.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>



#include <thread>
#include <tbb/tbb.h>
#include <tbb/pipeline.h>
#include <tbb/concurrent_queue.h>


namespace NmSp_OpenCV_unmanaged
  {
  class C_OpenCV_unmanaged
    {
      public:
      C_OpenCV_unmanaged();

      ~C_OpenCV_unmanaged();


      int                   CameraID;
      int                   HueMin;
      int                   HueMax;
      int                   SaturationMin;
      int                   SaturationMax;
      int                   ValueMin;
      int                   ValueMax;

      int                   Target_Size_X;     //Resizing the image to the wanted Values
      int                   Target_Size_Y;


      int                   ErosionKernelSize;
      int                   ErosionIterations;
      int                   DilationKernelSize;
      int                   DilationIterations;

      int                   BilateralKernelSize;
      float                 BilateralSigmaColor;
      float                 BilateralSigmaSpace;
      int                   GaussianKernelSize;
      double                GaussianSigma;
      int                   OpeningKernelSize;
      int                   ClosingKernelSize;
      int                   MorphKernelSize;

      cv::Mat                original_frame;
      cv::Mat                processed_frame;
      cv::Mat                HSV_frame;
      cv::Mat                Gaussian_frame;
      cv::Mat                Bilateral_frame;

      cv::cuda::GpuMat       gpu_original_frame;
      cv::cuda::GpuMat       gpu_processed_frame;
      cv::cuda::GpuMat       gpu_HSV_frame;
      cv::cuda::GpuMat       gpu_Gaussian_frame;
      cv::cuda::GpuMat       gpu_Bilateral_frame;
      cv::cuda::GpuMat       gpu_src_img;
      cv::cuda::GpuMat       gpu_temp_img;
      cv::cuda::GpuMat       gpu_dst_img;




      bool  Open_Cam            (int& WebCam_Nr, int Width, int Height);
      bool  Close_Cam           (int& WebCam_Nr);
      bool  Grab_Frame          (cv::Mat& cpu_dst);


      void  PushToGPU           (cv::Mat& src, cv::cuda::GpuMat& gpu_dst);
      void  PullfromGPU         (cv::cuda::GpuMat& gpu_src, cv::Mat& dst);


      void  ToHSV               (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst);
      void  ToHSV_Threshold     (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& HueMin, int& HueMax, int& SaturationMin, int& SaturationMax, int& ValueMin, int& ValueMax);
      void  ToResize            (cv::Mat& cpu_src, cv::Mat& cpu_dst, int& Size_X, int& Size_Y);
      void  Erosion             (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& ErosionKernelSize, int& ErosionIterations);
      void  Dilation            (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& DilationKernelSize, int& DilationIterations);

      void  Opening             (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& OpeningKernelSize);
      void  Closing             (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& ClosingKernelSize);
      void  Bilateral           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& BilateralKernelSize, float& BilateralSigmaColor, float& BilateralSigmaSpace);
      void  GaussianBluring     (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& GaussianKernelSize, double& GaussianSigma);

      void  findContours        (cv::Mat& cpu_src, cv::Mat& cpu_dst);


        

    };

  }


