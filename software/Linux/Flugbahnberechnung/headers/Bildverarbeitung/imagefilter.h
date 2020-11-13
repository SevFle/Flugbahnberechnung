#ifndef __Imagefilter_H
#define __Imagefilter_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/highgui.hpp"

#include "opencv2/opencv_modules.hpp"
#include <opencv2/cudawarping.hpp>
#include "libCuda.h"

#include "camera2.h"


namespace imagefilter
  {
  class C_ImageFilter
    {
  public:
    C_ImageFilter();
    ~C_ImageFilter();

    void gpufErode                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufDilate                       (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufOpen                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufClose                        (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufBilateral                    (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufHSV                          (cv::cuda::GpuMat* gpu_src, cv::Mat*           cpu_dst,Camera::C_Camera2 &Camera);
    void gpufGaussian                     (cv::cuda::GpuMat& gpuSrc,  cv::cuda::GpuMat &gpuDst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufMorphGradient                (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, Camera::C_Camera2::S_filterProperties &Filter);
    void gpufHSV                          (cv::cuda::GpuMat &gpu_src, cv::Mat           &cpu_dst,Camera::C_Camera2::S_filterProperties &Filter);
    bool findContours                     (cv::Mat*         cpuSrc,   cv::Mat* cpuDst, int offset[2], Camera::C_Camera2 &Camera, S_Positionsvektor& vecPosition, int& istX, int& istY, int& radius);
    void gpufUnidstord                    (cv::Mat* cpuSrc,           cv::cuda::GpuMat& gpuDst, cv::cuda::GpuMat& gpuMapX, cv::cuda::GpuMat& gpuMapY);
    void gpuROI                           (cv::cuda::GpuMat& gpuSrc, cv::cuda::GpuMat& gpuDst,cv::Rect& roi);
  private:
    cv::cuda::GpuMat getfGaussianKernel   (int gaussianKernelSize, double gaussianSigma);


      };

  }
#endif // Imagefilter_H

