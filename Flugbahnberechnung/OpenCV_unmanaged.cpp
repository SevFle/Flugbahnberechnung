#pragma once
/****************************************************************** Includes ****************************************************************/
#include "opencv_unmanaged.h"
/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_opencv_unmanaged;
/*************************************************************** Konstruktoren **************************************************************/
c_opencv_unmanaged::c_opencv_unmanaged                                  (int camera_id) :
anchor                      (-1,-1),
gaussian_kernel_size        (0)
  {
  hue_min                     = 0;
  hue_max                     = 0;
  saturation_min              = 0;
  saturation_max              = 0;
  value_min                   = 0;
  value_max                   = 0;
  target_size_height          = 0;
  target_size_width           = 0;
  erosion_iterations          = 0;
  dilation_iterations         = 0;
  opening_iterations          = 0;
  closing_iterations          = 0;
  bordertype                  = cv::BORDER_DEFAULT;
  gaussian_sigma              = 0;

  erosion_kernel_size         = 1;
  dilation_kernel_size        = 1;
  opening_kernel_size         = 1;
  morph_kernel_size           = 1;
  closing_kernel_size         = 1;
  gaussian_kernel_size        = 1;

  bilateral_kernel_size       = 1;
  bilateral_sigma_color       = 0;
  bilateral_sigma_space       = 0;

  statemachine_state          = 0;

  capture_api = cv::CAP_DSHOW;
  this->camera_id = camera_id;

//  std::thread t1(&c_opencv_unmanaged::camera_thread, this);
  }

/**************************************************************** Destruktor ****************************************************************/
c_opencv_unmanaged::~c_opencv_unmanaged()
  {
  hue_min                     = 0;
  hue_max                     = 0;
  saturation_min              = 0;
  saturation_max              = 0;
  value_min                   = 0;
  value_max                   = 0;
  target_size_height          = 0;
  target_size_width           = 0;
  erosion_iterations          = 0;
  dilation_iterations         = 0;
  opening_iterations          = 0;
  closing_iterations          = 0;
  bordertype                  = cv::BORDER_DEFAULT;
  gaussian_sigma              = 0;

  erosion_kernel_size         = 0;
  dilation_kernel_size        = 0;
  opening_kernel_size         = 0;
  morph_kernel_size           = 0;
  closing_kernel_size         = 0;

  bilateral_kernel_size       = 0;
  bilateral_sigma_color       = 0;
  bilateral_sigma_space       = 0;

  statemachine_state          = 0;

  capture_api = cv::CAP_DSHOW;
  camera_id = 0;

  }

/**** Öffentliche Klassenmethoden*************************************************/
void c_opencv_unmanaged::init                                           (int camera_id)
  {
  cap.open(camera_id, capture_api);
  }

void c_opencv_unmanaged::cpu_grab_frame                                 (cv::Mat& cpu_dst_img)
  {
  cap.read(cpu_dst_img);
  }

void c_opencv_unmanaged::cpu_img_show                                   (cv::Mat& processed_img, cv::Mat& original_img)
  {
  cv::imshow            ("original", original_img);
  cv::imshow            ("processed", processed_img);
  }

void c_opencv_unmanaged::camera_thread                                  ()
  {
  while (true)
    {
    switch (statemachine_state)
      {
        case 0:
          std::cout<< "State 0 \n\n";

          init(camera_id);
          statemachine_state = 1;


        case 1:
          std::cout<< "State 1 \n\n";
          
          cpu_grab_frame(cpu_src_img);
          statemachine_state = 2;


        case 2:
          std::cout<< "State 2 \n\n";

          apply_filter(cpu_src_img, cpu_mid_img);
          statemachine_state = 3;


        case 3:
          std::cout<< "State 3 \n\n";

          cpu_mask_img(cpu_mid_img, cpu_masked_img);
          statemachine_state = 4;


        case 4:
          std::cout<< "State 4 \n\n";

          cpu_img_show(cpu_masked_img, cpu_src_img);
          if (cv::waitKey(5)>=0)
            break;

          statemachine_state = 1;

      }
    }
  }

void c_opencv_unmanaged::cpu_mask_img                                   (cv::Mat& hsv_cpu_src, cv::Mat& cpu_masked_dst)
  {
  cv::inRange(hsv_cpu_src, cv::Scalar(this->hue_min, this->saturation_min, this->value_min), cv::Scalar(this->hue_max, this->saturation_max, this->value_max), cpu_masked_dst);
  }

void c_opencv_unmanaged::create_img_vectors                             ()
  {
  cpu_src_vector.push_back        (this->cpu_img);
  cpu_dst_vector.push_back        (this->cpu_img);
  cpu_mid_vector.push_back        (this->cpu_img);
  cpu_masked_vector.push_back     (this->cpu_img);
  gpu_src_vector.push_back        (this->gpu_img);
  gpu_dst_vector.push_back        (this->gpu_img);
  gpu_mid_vector.push_back        (this->gpu_img);
  }

void c_opencv_unmanaged::apply_filter                                   (cv::Mat  &cpu_src, cv::Mat &cpu_dst)
  {
  cpu_to_4channel_colour          (cpu_src, cpu_mid_img);
  gpu_src_img.upload              (cpu_mid_img);
  gpu_erode                       (gpu_src_img, gpu_mid_img, bordertype, anchor, erosion_iterations);
  gpu_dilate                      (gpu_mid_img, gpu_dst_img, anchor, dilation_iterations);
  gpu_open                        (gpu_dst_img, gpu_mid_img, anchor, opening_iterations);
  gpu_close                       (gpu_mid_img, gpu_dst_img, anchor, closing_iterations);
  gpu_gaussian_filter             (gpu_dst_img, gpu_mid_img, gaussian_kernel_size, gaussian_sigma);
  gpu_to_hsv                      (gpu_mid_img, gpu_dst_img);
  gpu_dst_img.download            (cpu_dst);

  }

void c_opencv_unmanaged::operator                                       ()() 
  {
  while (true)
    {
    switch (statemachine_state)
      {
        case 0:
          std::cout<< "State 0 \n\n";

          init(camera_id);
          statemachine_state = 1;


        case 1:
          std::cout<< "State 1 \n\n";

          cpu_grab_frame(cpu_src_img);
          statemachine_state = 2;


        case 2:
          std::cout<< "State 2 \n\n";

          apply_filter(cpu_src_img, cpu_mid_img);
          statemachine_state = 3;


        case 3:
          std::cout<< "State 3 \n\n";

          cpu_mask_img(cpu_mid_img, cpu_masked_img);
          statemachine_state = 4;


        case 4:
          std::cout<< "State 4 \n\n";

          cpu_img_show(cpu_masked_img, cpu_src_img);
          if (cv::waitKey(5)>=0)
            break;

          statemachine_state = 1;

      }
    }
  }

/*************************************************************** Private Klassenmethoden*****************************************************/
void c_opencv_unmanaged::cpu_to_4channel_colour                         (cv::Mat& cpu_src, cv::Mat& cpu_dst)
  {
  cv::Mat src4ch;
  cv::cvtColor(cpu_src, cpu_dst, cv::COLOR_BGR2BGRA);
  }

void c_opencv_unmanaged::gpu_to_hsv                                     (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  cv::cuda::cvtColor(gpu_src, gpu_dst, cv::COLOR_BGR2HSV);
  std::cout<<"CPU to HSV \n\n";

  }

void c_opencv_unmanaged::gpu_to_hsv_threshold                           (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int hue_min, int hue_max, int saturation_min, int saturation_max, int value_min, int value_max)
  {
  }

void c_opencv_unmanaged::gpu_erode                                      (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int borderType, cv::Point anchor, int erosion_iterations)
  {
  cv::Mat   erode_structuring_element  =cv::getStructuringElement (cv::MORPH_ELLIPSE, cv::Size (2*erosion_kernel_size, 2*erosion_kernel_size));

  cv::Ptr<cv::cuda::Filter> erode = cv::cuda::createMorphologyFilter(cv::MORPH_ERODE, gpu_src.type(), erode_structuring_element, anchor, erosion_iterations);
  erode->apply(gpu_src, gpu_dst);
  std::cout<<"GPU Erode \n\n";
  }

void c_opencv_unmanaged::gpu_dilate                                     (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int dilation_iterations)
  {
  cv::Mat   dilate_structuring_element  =cv::getStructuringElement (cv::MORPH_ELLIPSE, cv::Size (2*dilation_kernel_size, 2*dilation_kernel_size));

  cv::Ptr<cv::cuda::Filter> dilate = cv::cuda::createMorphologyFilter(cv::MORPH_DILATE, gpu_src.type(), dilate_structuring_element, anchor, dilation_iterations);
  dilate->apply(gpu_src, gpu_dst);
  std::cout<<"GPU Dilate \n\n";

  }

void c_opencv_unmanaged::gpu_open                                       (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int opening_iterations)
  {
  cv::Mat   opening_structuring_element  =cv::getStructuringElement (cv::MORPH_ELLIPSE, cv::Size (2*opening_kernel_size, 2*opening_kernel_size));

  cv::Ptr<cv::cuda::Filter> opening = cv::cuda::createMorphologyFilter(cv::MORPH_OPEN, gpu_src.type(), opening_structuring_element, anchor, opening_iterations);
  opening->apply(gpu_src, gpu_dst);
  std::cout<<"GPU Opening \n\n";

  }

void c_opencv_unmanaged::gpu_close                                      (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int closing_iterations)
  {
  cv::Mat   closing_structuring_element  =cv::getStructuringElement (cv::MORPH_ELLIPSE, cv::Size (2*closing_kernel_size, 2*closing_kernel_size));

  cv::Ptr<cv::cuda::Filter> closing = cv::cuda::createMorphologyFilter(cv::MORPH_CLOSE, gpu_src.type(), closing_structuring_element, anchor, closing_iterations);
  closing->apply(gpu_src, gpu_dst);
  std::cout<<"GPU Closing \n\n";

  }

void c_opencv_unmanaged::gpu_bilateral_filter                           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int bilateral_kernel_size, float bilateral_sigma_color, float bilateral_sigma_spatial)
  {
  cv::cuda::bilateralFilter(gpu_src, gpu_dst, bilateral_kernel_size, bilateral_sigma_color, bilateral_sigma_spatial, cv::BORDER_DEFAULT);
  }

void c_opencv_unmanaged::gpu_gaussian_filter                            (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int gaussian_kernel_size, double gaussian_sigma)
  {
  cv::Ptr<cv::cuda::Filter> gauss = cv::cuda::createGaussianFilter(gpu_src.type(), -1, cv::Size(gaussian_kernel_size, gaussian_kernel_size), gaussian_sigma, gaussian_sigma, cv::BORDER_DEFAULT);
  gauss->apply(gpu_src, gpu_dst);
  std::cout<<"GPU Gaussian \n\n";
  }

void c_opencv_unmanaged::cpu_find_contours                              (cv::Mat& cpu_src, cv::Mat& cpu_dst)
  {
  }





     