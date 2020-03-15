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
  bilateral_sigma_spatial     = 0;

  statemachine_state          = 0;

  capture_api = cv::CAP_DSHOW;
  this->camera_id = camera_id;

  thread_running = true;

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
  bilateral_sigma_spatial       = 0;

  statemachine_state          = 0;

  capture_api = cv::CAP_DSHOW;
  camera_id = 0;

  thread_running = true;

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
  while (thread_running == true)
    {
    switch (statemachine_state)
      {
        case 0:
          std::cout<< "Thread " << this->camera_id << " running." << std::endl;

          init(camera_id);
          statemachine_state = 1;


        case 1:
          
          cpu_grab_frame(cpu_src_img);
          statemachine_state = 2;


        case 2:
          cpu_src_img_test = cpu_src_img;
          apply_filter(cpu_src_img, cpu_mid_img);
          cpu_mask_img(cpu_src_img_test, cpu_dst_img_test);
          statemachine_state = 3;


        case 3:
          if (cv::waitKey(5)>=0)
            break;

          statemachine_state = 1;

      }
    }
  }

void c_opencv_unmanaged::cpu_mask_img                                   (cv::Mat& hsv_cpu_src, cv::Mat& cpu_masked_dst)
  {
  cv::cvtColor(cpu_src_img_test, cpu_mid_img, cv::COLOR_BGR2HSV);
  cv::inRange(cpu_mid_img, cv::Scalar(this->hue_min, this->saturation_min, this->value_min), cv::Scalar(this->hue_max, this->saturation_max, this->value_max), cpu_masked_dst);
  }

void c_opencv_unmanaged::apply_filter                                   (cv::Mat  &cpu_src, cv::Mat &cpu_dst)
  {
  //cpu_to_4channel_colour          (cpu_src, cpu_4channel);
  gpu_src_img.upload                                  (cpu_src);
  gpu_filter_hsv(gpu_src_img, gpu_thresholded);
  if (erode_active)   gpu_erode                       (gpu_thresholded, gpu_thresholded, bordertype, anchor);
  if (dilate_active)  gpu_dilate                      (gpu_thresholded, gpu_thresholded, anchor);
  if(open_active)     gpu_open                        (gpu_thresholded, anchor);
  if(close_active)    gpu_close                       (gpu_thresholded, anchor);
  if(gaussian_active) gpu_gaussian_filter             (gpu_thresholded);
  if(morph_active)    gpu_morph_gradient              (gpu_thresholded, gpu_thresholded);

  gpu_thresholded.download                  (cpu_masked_img);


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
void            gpu_inRange                                         (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, cv::Scalar minvalue, cv::Scalar maxvalue)
{
 // cv::inRange()
}

void c_opencv_unmanaged::cpu_to_4channel_colour                         (cv::Mat& cpu_src, cv::Mat& cpu_dst)
  {
  cv::cvtColor(cpu_src, cpu_dst, cv::COLOR_BGR2BGRA);
  }

void c_opencv_unmanaged::gpu_to_hsv_threshold                           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {

  cv::Scalar hsv_low(hue_min, saturation_min, value_min);
  cv::Scalar hsv_high(hue_max, saturation_max, value_max);

  cv::cuda::split(gpu_src, mat_parts);

//find range between high and low values of H
  cv::cuda::threshold(mat_parts[0], mat_parts_low[0], hsv_low[0], UCHAR_MAX, cv::THRESH_BINARY);
  cv::cuda::threshold(mat_parts[0], mat_parts_high[0], hsv_high[0], UCHAR_MAX, cv::THRESH_BINARY_INV);
  cv::cuda::bitwise_and(mat_parts_high[0], mat_parts_low[0], mat_parts[0]);

  //find range between high and low values of S
  cv::cuda::threshold(mat_parts[1], mat_parts_low[1], hsv_low[1], UCHAR_MAX, cv::THRESH_BINARY);
  cv::cuda::threshold(mat_parts[1], mat_parts_high[1], hsv_high[1], UCHAR_MAX, cv::THRESH_BINARY_INV);
  cv::cuda::bitwise_and(mat_parts_high[1], mat_parts_low[1], mat_parts[1]);

  //find range between high and low values of V
  cv::cuda::threshold(mat_parts[2], mat_parts_low[2], hsv_low[2], UCHAR_MAX, cv::THRESH_BINARY);
  cv::cuda::threshold(mat_parts[2], mat_parts_high[2], hsv_high[2], UCHAR_MAX, cv::THRESH_BINARY_INV);
  cv::cuda::bitwise_and(mat_parts_high[2], mat_parts_low[2], mat_parts[2]);

 
  //bitwise AND all channels.
  cv::cuda::bitwise_and(mat_parts[0], mat_parts[1], gpu_temp);
  cv::cuda::bitwise_and(gpu_temp, mat_parts[2], gpu_dst);

  //cv::Mat img_final(final_result);
  //cv::cuda::cvtColor      (gpu_src, gpu_temp, cv::COLOR_BGR2HSV);
  //cv::cuda::split         (gpu_temp, gpu_shsv);
  //cv::cuda::threshold     (gpu_shsv[0], gpu_thresc[0], hue_min, hue_max, cv::THRESH_BINARY);
  //cv::cuda::threshold     (gpu_shsv[1], gpu_thresc[1], saturation_min, saturation_max, cv::THRESH_BINARY);
  //cv::cuda::threshold     (gpu_shsv[2], gpu_thresc[2], value_min, value_max, cv::THRESH_BINARY);
  //cv::cuda::bitwise_and   (gpu_thresc[0], gpu_thresc[1], gpu_temp);
  //cv::cuda::bitwise_and   (gpu_temp, gpu_thresc[2], gpu_dst);
  }

void c_opencv_unmanaged::gpu_erode                                      (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int borderType, cv::Point anchor)  //
  {
  cv::Mat                     erode_structuring_element   =  cv::getStructuringElement            (cv::MORPH_ELLIPSE, cv::Size (2*erosion_kernel_size, 2*erosion_kernel_size));
  cv::Ptr<cv::cuda::Filter>   erode                       =  cv::cuda::createMorphologyFilter     (cv::MORPH_ERODE, gpu_src.type(), erode_structuring_element, anchor, erosion_iterations);
                              erode->apply                                                        (gpu_src, gpu_dst);
  }

void c_opencv_unmanaged::gpu_morph_gradient                             (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  cv::Mat                     morph_structuring_element  =  cv::getStructuringElement           (cv::MORPH_ELLIPSE, cv::Size (2*morph_kernel_size, 2*morph_kernel_size));
  cv::Ptr<cv::cuda::Filter>   morph                      =  cv::cuda::createMorphologyFilter    (cv::MORPH_GRADIENT, gpu_src.type(), morph_structuring_element, anchor, morph_iterations);
  morph->apply                                                      (gpu_src, gpu_dst);

  }

void c_opencv_unmanaged::gpu_dilate                                     (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor)   //
  {
  cv::Mat                     dilate_structuring_element  = cv::getStructuringElement             (cv::MORPH_ELLIPSE, cv::Size (2*dilation_kernel_size, 2*dilation_kernel_size));
  cv::Ptr<cv::cuda::Filter>   dilate                      = cv::cuda::createMorphologyFilter      (cv::MORPH_DILATE, gpu_src.type(), dilate_structuring_element, anchor, dilation_iterations);
                              dilate->apply                                                       (gpu_src, gpu_dst);

  }

void c_opencv_unmanaged::gpu_open                                       (cv::cuda::GpuMat& gpu_src, cv::Point anchor)
  {
  cv::Mat                     opening_structuring_element  =  cv::getStructuringElement           (cv::MORPH_ELLIPSE, cv::Size (2*opening_kernel_size, 2*opening_kernel_size));
  cv::Ptr<cv::cuda::Filter>   opening                      =  cv::cuda::createMorphologyFilter    (cv::MORPH_OPEN, gpu_src.type(), opening_structuring_element, anchor, opening_iterations);
                              opening->apply                                                      (gpu_src, gpu_src);

  }

void c_opencv_unmanaged::gpu_close                                      (cv::cuda::GpuMat& gpu_src, cv::Point anchor)
  {
  cv::Mat                     closing_structuring_element  =cv::getStructuringElement (cv::MORPH_ELLIPSE, cv::Size (2*closing_kernel_size, 2*closing_kernel_size));

  cv::Ptr<cv::cuda::Filter> closing = cv::cuda::createMorphologyFilter(cv::MORPH_CLOSE, gpu_src.type(), closing_structuring_element, anchor, closing_iterations);
  closing->apply(gpu_src, gpu_src);

  }

void c_opencv_unmanaged::gpu_bilateral_filter                           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  cv::cuda::bilateralFilter(gpu_src, gpu_dst, bilateral_kernel_size, bilateral_sigma_color, bilateral_sigma_spatial, cv::BORDER_DEFAULT);
  }

void c_opencv_unmanaged::gpu_gaussian_filter                            (cv::cuda::GpuMat& gpu_src)
  {
  cv::Ptr<cv::cuda::Filter> gauss = cv::cuda::createGaussianFilter(gpu_src.type(), -1, cv::Size(gaussian_kernel_size, gaussian_kernel_size), gaussian_sigma, gaussian_sigma, cv::BORDER_DEFAULT);
  gauss->apply(gpu_src, gpu_src);
  }

void c_opencv_unmanaged::gpu_hsv2grayscale                              (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
  {
  //cv::cuda::cvtColor      (gpu_src, gpu_dst, cv::COLOR_BGR2GRAY);

  }

void c_opencv_unmanaged::gpu_filter_hsv                                 (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
{
  cv::cuda::cvtColor(gpu_src, gpu_src2color, cv::COLOR_BGR2HSV);

  gpu_gaussian_filter(gpu_src2color);

  gpu_to_hsv_threshold(gpu_src2color, gpu_color_threshold);

  gpu_open(gpu_color_threshold, anchor);

  gpu_close(gpu_color_threshold, anchor);

  cv::cuda::cvtColor(gpu_color_threshold, gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  cv::cuda::bitwise_and(gpu_src, gpu_bgr_threshold, gpu_dst);
}

void c_opencv_unmanaged::gpu_filter_bgr                                          (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
{
  gpu_src.copyTo(gpu_src2color);

  gpu_gaussian_filter(gpu_src2color);

  gpu_to_hsv_threshold(gpu_src2color, gpu_color_threshold);

  gpu_open(gpu_color_threshold, anchor);

  gpu_close(gpu_color_threshold, anchor);

  cv::cuda::cvtColor(gpu_color_threshold, gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  cv::cuda::bitwise_and(gpu_src, gpu_bgr_threshold, gpu_dst);

}
void c_opencv_unmanaged::gpu_filter_gray                                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst)
{
  cv::cuda::cvtColor(gpu_src, gpu_src2color, cv::COLOR_BGR2HSV);

  gpu_gaussian_filter(gpu_src2color);

  gpu_to_hsv_threshold(gpu_src2color, gpu_color_threshold);

  gpu_open(gpu_color_threshold, anchor);

  gpu_close(gpu_color_threshold, anchor);

  cv::cuda::cvtColor(gpu_color_threshold, gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  cv::cuda::bitwise_and(gpu_src, gpu_bgr_threshold, gpu_dst);


}






     