#include "OpenCV_unmanaged.h"

using namespace NmSp_OpenCV_unmanaged;



C_OpenCV_unmanaged::C_OpenCV_unmanaged()
  {
  }

C_OpenCV_unmanaged::~C_OpenCV_unmanaged()
  {
  }


bool C_OpenCV_unmanaged::Open_Cam(int& WebCam_Nr, int Width, int Height)
  {
  return false;
  }

bool C_OpenCV_unmanaged::Close_Cam(int& WebCam_Nr)
  {
  return false;
  }

bool C_OpenCV_unmanaged::Grab_Frame(cv::Mat& cpu_dst)
  {
  return false;
  }

void C_OpenCV_unmanaged::PushToGPU(cv::Mat& cpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  gpu_dst.upload(cpu_src);
  }

void C_OpenCV_unmanaged::PullfromGPU(cv::cuda::GpuMat& gpu_src, cv::Mat& cpu_dst)
  {
  cpu_dst.download(gpu_src);
  }

void C_OpenCV_unmanaged::ToHSV(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  }

void C_OpenCV_unmanaged::ToHSV_Threshold(cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& HueMin, int& HueMax, int& SaturationMin, int& SaturationMax, int& ValueMin, int& ValueMax)
  {
  }

void C_OpenCV_unmanaged::ToResize(cv::Mat& cpu_src, cv::Mat& cpu_dst, int& Size_X, int& Size_Y)
  {
  }

void C_OpenCV_unmanaged::Erosion(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& ErosionKernelSize, int& ErosionIterations)
  {
  }

void C_OpenCV_unmanaged::Dilation(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& DilationKernelSize, int& DilationIterations)
  {
  }

void C_OpenCV_unmanaged::Opening(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& OpeningKernelSize)
  {
  }

void C_OpenCV_unmanaged::Closing(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& ClosingKernelSize)
  {
  }

void C_OpenCV_unmanaged::Bilateral(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& BilateralKernelSize, float& BilateralSigmaColor, float& BilateralSigmaSpace)
  {
  }

void C_OpenCV_unmanaged::GaussianBluring(cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& GaussianKernelSize, double& GaussianSigma)
  {
  }

void C_OpenCV_unmanaged::findContours(cv::Mat & cpu_src, cv::Mat & cpu_dst)
  {
  }
