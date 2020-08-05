#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/highgui.hpp"
#include "cuda/CudaKernels.cuh"

#include "camera2.h"

namespace imagefilter
  {
  class C_ImageFilter
    {
  public:
    C_ImageFilter();
    ~C_ImageFilter();

    void gpufErode                        (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufDilate                       (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufOpen                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufClose                        (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufBilateral                    (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufHSV                          (cv::cuda::GpuMat& gpu_src, cv::Mat&           cpu_dst,Camera::C_Camera2 &Camera);
    void gpufGaussian                     (cv::cuda::GpuMat &gpuSrc,  cv::cuda::GpuMat &gpuDst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufMorphGradient                (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufHSV                          (cv::cuda::GpuMat &gpu_src, cv::Mat           &cpu_dst,Camera::C_Camera2::S_filterProperties &Filter);
    void findContours                     (cv::Mat& cpuSrc,           cv::Mat& dst_contoured_image, int offset[2], Camera::C_Camera2 &Camera);
    void gpufUnidstord                    (cv::Mat &cpuSrc,           cv::cuda::GpuMat &gpuDst, cv::cuda::GpuMat &gpuMap1, cv::cuda::GpuMat &gpuMap2);

  private:
    cv::cuda::GpuMat getfGaussianKernel   (int gaussianKernelSize, double gaussianSigma);


      };

  }


