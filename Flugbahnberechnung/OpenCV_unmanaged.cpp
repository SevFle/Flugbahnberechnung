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
  hue_max                     = 179;
  saturation_min              = 0;
  saturation_max              = 255;
  value_min                   = 0;
  value_max                   = 255;

  target_size_height          = 0;
  target_size_width           = 0;
  erosion_iterations          = 0;
  dilation_iterations         = 0;
  opening_iterations          = 0;
  closing_iterations          = 0;
  bordertype                  = cv::BORDER_DEFAULT;
  gaussian_sigma              = 1;

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

  capture_api                 = cv::CAP_DSHOW;
  this->camera_id             = camera_id;

  thread_running              = true;
  filtering_active            = false;

  filtering_hsv_active        = true;
  filtering_bgr_active        = false;
  filtering_gray_active       = false;

  contours_active             = false;

  this->gpu_src_img           = new cv::cuda::GpuMat();
  this->gpu_thresholded       = new cv::cuda::GpuMat();
  this->gpu_filtered          = new cv::cuda::GpuMat();
  this->gpu_gray              = new cv::cuda::GpuMat();
  this->gpu_src2color         = new cv::cuda::GpuMat();
  this->gpu_color_threshold   = new cv::cuda::GpuMat();
  this->gpu_bgr_threshold     = new cv::cuda::GpuMat();
  this->gpu_temp              = new cv::cuda::GpuMat();

  this->cpu_temp              = new cv::Mat();
  this->cpu_temp3             = new cv::Mat();
  this->cpu_src_img           = new cv::Mat();
  this->cpu_mid_img           = new cv::Mat();
  this->cpu_masked_img        = new cv::Mat();
  this->cpu_filtered          = new cv::Mat();
  this->cpu_contoured         = new cv::Mat();
  this->contoure_img          = new cv::Mat();




  this->cap                   = new cv::VideoCapture;

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

  delete (gpu_src_img);
  delete(gpu_thresholded);
  delete(gpu_filtered);
  delete(gpu_gray);
  delete(gpu_src2color);
  delete(gpu_color_threshold);
  delete(gpu_bgr_threshold);
  delete(gpu_temp);

  delete(cpu_temp);
  delete(cpu_temp3);
  delete(cpu_src_img);
  delete(cpu_mid_img);
  delete(cpu_masked_img);
  delete(cpu_filtered);
  delete(cpu_contoured);


  delete(cap);


  }

/************************************************************* Öffentliche Klassenmethoden*************************************************/

void c_opencv_unmanaged::apply_filter                                   (cv::Mat* cpu_src, cv::Mat* cpu_dst)
  {
  if (filtering_hsv_active == true)
    {
    gpu_src_img->upload                                    (*cpu_src);
    gpu_filter_hsv                                        (gpu_src_img, gpu_thresholded);
    }
  if (filtering_bgr_active == true)
    {
    gpu_src_img->upload                                    (*cpu_src);
    gpu_filter_bgr                                        (gpu_src_img, gpu_thresholded);
    }
  if (filtering_gray_active == true)
    {
    gpu_src_img->upload                                    (*cpu_src);
    gpu_filter_gray                                       (gpu_src_img, gpu_thresholded);
    }

  gpu_thresholded->download                                (*cpu_dst);
  }

void c_opencv_unmanaged::cpu_mask_img                                   (cv::Mat* hsv_cpu_src, cv::Mat* cpu_masked_dst)
  {
  cv::cvtColor(*hsv_cpu_src, *cpu_mid_img, cv::COLOR_BGR2HSV);
  cv::inRange(*cpu_mid_img, cv::Scalar(this->hue_min, this->saturation_min, this->value_min), cv::Scalar(this->hue_max, this->saturation_max, this->value_max), *cpu_temp);
  cv::cvtColor(*cpu_temp, *cpu_temp3, cv::COLOR_GRAY2BGR);
  cv::bitwise_and(*hsv_cpu_src, *cpu_temp3, *cpu_masked_dst);

  }

void c_opencv_unmanaged::camera_thread                                  ()
  {
  while (thread_running == true)
    {
    switch (statemachine_state)
      {
        case 0:
          std::cout<< "Thread " << this->camera_id +1 << " running." << std::endl<< std::endl<< std::endl;

          init(camera_id);
          statemachine_state = 1;


        case 1:
          cpu_grab_frame(cpu_src_img);
          statemachine_state = 2;


        case 2:  //Image Processing
          if (filtering_active == true)
            {
            apply_filter(cpu_src_img, cpu_masked_img);
            contours_active = true;
            gpu_filtered->download(*cpu_filtered);
            find_contours(cpu_filtered, cpu_contoured);
            }
          statemachine_state = 3;


        case 3:
          if (cv::waitKey(33)>=0)
            break;

          statemachine_state = 1;

      }
    }
  }
/*************************************************************** Private Klassenmethoden*****************************************************/

void c_opencv_unmanaged::init                                           (int camera_id)
  {
  cap->set(cv::CAP_PROP_FRAME_HEIGHT, 600);
  cap->set(cv::CAP_PROP_FRAME_WIDTH, 800);
  cap->set(cv::CAP_PROP_FPS, 60);
  cap->open(camera_id, capture_api);

  //Redifinition der zwei GpuMat Arrays für die Verwendung in der Cuda-InRange Funktion. 
  gpu_src2color->create(480, 640, CV_8UC1);
  gpu_color_threshold->create(480, 640, CV_8UC1);
  }
void c_opencv_unmanaged::cpu_grab_frame                                 (cv::Mat* cpu_dst_img)
  {
  cap->read(*cpu_dst_img);
  }

void c_opencv_unmanaged::gpu_erode                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, int borderType, cv::Point anchor)  //
  {
  cv::Mat                     erode_structuring_element   =  cv::getStructuringElement            (cv::MORPH_ELLIPSE, cv::Size (2*erosion_kernel_size, 2*erosion_kernel_size));
  cv::Ptr<cv::cuda::Filter>   erode                       =  cv::cuda::createMorphologyFilter     (cv::MORPH_ERODE, gpu_src->type(), erode_structuring_element, anchor, erosion_iterations);
                              erode->apply                                                        (*gpu_src, *gpu_dst);
  }
void c_opencv_unmanaged::gpu_dilate                                     (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Point anchor)   //
  {
  cv::Mat                     dilate_structuring_element  = cv::getStructuringElement             (cv::MORPH_ELLIPSE, cv::Size (2*dilation_kernel_size, 2*dilation_kernel_size));
  cv::Ptr<cv::cuda::Filter>   dilate                      = cv::cuda::createMorphologyFilter      (cv::MORPH_DILATE, gpu_src->type(), dilate_structuring_element, anchor, dilation_iterations);
                              dilate->apply                                                       (*gpu_src, *gpu_dst);
  }
void c_opencv_unmanaged::gpu_open                                       (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Point anchor)
  {
  cv::Mat                     opening_structuring_element  =  cv::getStructuringElement           (cv::MORPH_ELLIPSE, cv::Size (2*opening_kernel_size, 2*opening_kernel_size));
  cv::Ptr<cv::cuda::Filter>   opening                      =  cv::cuda::createMorphologyFilter    (cv::MORPH_OPEN, gpu_src->type(), opening_structuring_element, anchor, opening_iterations);
                              opening->apply                                                      (*gpu_src, *gpu_dst);
  }
void c_opencv_unmanaged::gpu_close                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Point anchor)
  {
  cv::Mat                     closing_structuring_element  =  cv::getStructuringElement           (cv::MORPH_ELLIPSE, cv::Size (2*closing_kernel_size, 2*closing_kernel_size));
  cv::Ptr<cv::cuda::Filter>   closing                      =  cv::cuda::createMorphologyFilter    (cv::MORPH_CLOSE, gpu_src->type(), closing_structuring_element, anchor, closing_iterations);
  closing->apply(*gpu_src, *gpu_dst);
  }

void c_opencv_unmanaged::gpu_bilateral_filter                           (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::cuda::bilateralFilter                                                                       (*gpu_src, *gpu_dst, bilateral_kernel_size, bilateral_sigma_color, bilateral_sigma_spatial, cv::BORDER_DEFAULT);
  }
void c_opencv_unmanaged::gpu_gaussian_filter                            (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::Ptr<cv::cuda::Filter>   gauss                       = cv::cuda::createGaussianFilter        (gpu_src->type(), -1, cv::Size(gaussian_kernel_size, gaussian_kernel_size), gaussian_sigma, gaussian_sigma, cv::BORDER_DEFAULT);
  gauss->apply(*gpu_src, *gpu_dst);
  }
void c_opencv_unmanaged::gpu_morph_gradient                             (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::Mat                     morph_structuring_element   =  cv::getStructuringElement            (cv::MORPH_ELLIPSE, cv::Size (2*morph_kernel_size, 2*morph_kernel_size));
  cv::Ptr<cv::cuda::Filter>   morph                       =  cv::cuda::createMorphologyFilter     (cv::MORPH_GRADIENT, gpu_src->type(), morph_structuring_element, anchor, morph_iterations);
  morph->apply                                                                                    (*gpu_src, *gpu_dst);

  }


void c_opencv_unmanaged::gpu_filter_hsv                                 (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
{

  cv::cuda::cvtColor        (*gpu_src, *gpu_src2color, cv::COLOR_BGR2HSV);

  gpu_gaussian_filter       (gpu_src2color, gpu_filtered);

  cudaKernel::inRange_gpu(*gpu_filtered, cv::Scalar(this->hue_min, this->saturation_min, this->value_min),
                          cv::Scalar(this->hue_max, this->saturation_max, this->value_max), *gpu_color_threshold);

  gpu_open                  (gpu_color_threshold, gpu_temp, anchor);

  gpu_close                 (gpu_temp, gpu_filtered, anchor);

  cv::cuda::cvtColor        (*gpu_filtered, *gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  cv::cuda::bitwise_and     (*gpu_src_img, *gpu_bgr_threshold, *gpu_dst);
}
void c_opencv_unmanaged::gpu_filter_bgr                                 (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
{
  //gpu_src.copyTo(gpu_src2color);

  //gpu_gaussian_filter(gpu_src2color);

  //gpu_to_hsv_threshold(gpu_src2color, gpu_color_threshold);

  //gpu_open(gpu_color_threshold, anchor);

  //gpu_close(gpu_color_threshold, anchor);

  //cv::cuda::cvtColor(gpu_color_threshold, gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  //cv::cuda::bitwise_and(gpu_src, gpu_bgr_threshold, gpu_dst);

}
void c_opencv_unmanaged::gpu_filter_gray                                (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
{
  //cv::cuda::cvtColor(gpu_src, gpu_src2color, cv::COLOR_BGR2HSV);

  //gpu_gaussian_filter(gpu_src2color);

  //gpu_to_hsv_threshold(gpu_src2color, gpu_color_threshold);

  //gpu_open(gpu_color_threshold, anchor);

  //gpu_close(gpu_color_threshold, anchor);

  //cv::cuda::cvtColor(gpu_color_threshold, gpu_bgr_threshold, cv::COLOR_GRAY2BGR);

  //cv::cuda::bitwise_and(gpu_src, gpu_bgr_threshold, gpu_dst);


}
void c_opencv_unmanaged::find_contours                                  (cv::Mat* thresholded_source_image, cv::Mat* dst_contoured_image)
  {
  //OpenCV Hirarchy: https://docs.opencv.org/3.4/d9/d8b/tutorial_py_contours_hierarchy.html
  cv::findContours(*thresholded_source_image, contours, hirarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));


  // Zeichne Bildmittelpunkt ein
  double Mittelpunkt_x = dst_contoured_image->cols / 2;
  double Mittelpunkt_y = dst_contoured_image->rows / 2;
  cv::circle(*dst_contoured_image, cv::Point((int)Mittelpunkt_x, (int)Mittelpunkt_y), 2, cv::Scalar(0, 255, 0));

  // Zeichne kalibrierten Bildmittelpunkt ein
  //double cx = this->Intrinsic->at<double>(0, 2);
  //double cy = this->Intrinsic->at<double>(1, 2);
  //cv::circle(image_Output, Point((int)cx, (int)cy), 2, Scalar(255, 255, 0));


  objekt_anzahl = hirarchy.size();

  cv::drawContours(*dst_contoured_image, contours,0, cv::Scalar(0, 255, 0), 10, cv::LINE_AA, hirarchy);

  if (objekt_anzahl > 0)
    {
    // Vorinitialisierung des Abstands des Konturschwerpunktes zum Bildmittelpunkt
    cv::Moments Image_Moments   = cv::moments((cv::Mat)contours[0]);
    int    KonturIndex      = 0;
    double Ist_x            = 0.0;
    double Ist_y            = 0.0;
    double Soll_x           = 0.0;
    double Soll_y           = 0.0;
    double Delta_x          = 0.0;
    double Delta_y          = 0.0;
    this->contour_found     = false;
    this->Vec_Object[0]     = 0.0;
    this->Vec_Object[1]     = 0.0;
    this->Vec_Object[2]     = 0.0;
    this->max_Moment_m00    = 0.0;

    // Größte Kontur anhand der Fläche suchen
    for (int i = 0; i < objekt_anzahl; i++)
      {
      Image_Moments              = cv::moments((cv::Mat)contours[i]);
      double  Moment_0_Ordnung   = Image_Moments.m00;

      if (Moment_0_Ordnung > this->max_Moment_m00)
        {
        this->max_Moment_m00 = Moment_0_Ordnung;
        KonturIndex          = i;
        }
      else
        {
        // tue nichts
        }
      }

    // Bestimmen der Flchenmomente 0. (Flche) und 1. Ordnung (Flche * x bzw. Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    Image_Moments              = cv::moments((cv::Mat)contours[KonturIndex]);
    double  Moment_0_Ordnung   = Image_Moments.m00;

    // Bestimme Flchenmoment 1. Ordnung (Flche * x bzw.Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    double  Moment_1_Ordnung_x = Image_Moments.m10;
    double  Moment_1_Ordnung_y = Image_Moments.m01;
    double  Schwerpunkt_x      = Moment_1_Ordnung_x / Moment_0_Ordnung;
    double  Schwerpunkt_y      = Moment_1_Ordnung_y / Moment_0_Ordnung;

    // Den Radius und den Mittelpunkt des kleinstes Kreises einer gefundenen Kontur ermitteln.
    cv::Point2f Center;
    float   Radius;
    minEnclosingCircle((cv::Mat)contours[KonturIndex], Center, Radius);

    // Mittelpunkt / schwerpunkt der kontur einzeichnen
    cv::circle(*dst_contoured_image, cv::Point((int)Schwerpunkt_x, (int)Schwerpunkt_y), 2, cv::Scalar(0, 255, 255));

    // Konturumfang zeichnen
    cv::circle(*dst_contoured_image, Center, (int)Radius, cv::Scalar(0, 255, 255));

    // Schwerpunktkoordinaten als Text im Bild darstellen
    std::string S_x = std::to_string(Schwerpunkt_x);
    std::string S_y = std::to_string(Schwerpunkt_y);
    cv::putText(*dst_contoured_image, "S_x: " + S_x, cv::Point(0, 20), 1, 1, cv::Scalar(255, 255, 255), 2);
    cv::putText(*dst_contoured_image, "S_y: " + S_y, cv::Point(0, 50), 1, 1, cv::Scalar(255, 255, 255), 2);

    // Bestimme den Abstand des Mittelpunktes der gefundenen Kontur zum Bildmittelpunkt
    this->contour_found  = true;
    Ist_x                = Schwerpunkt_x;
    Ist_y                = Schwerpunkt_y;
    //Soll_x               = cx;
    //Soll_y               = cy;
    Delta_x              = Ist_x - Soll_x;
    Delta_y              = Ist_y - Soll_y;

    // Bestimme den Lichtstrahlvektor der Kontur bezogen auf das Kamera-KS
    double x_Kamera_KS       = Delta_x;
    double y_Kamera_KS       = Delta_y;
    //double fx                = this->Intrinsic->at<double>(0, 0);
    //double fy                = this->Intrinsic->at<double>(1, 1);
    //double f                 = (fx + fy) / 2.0; // Mittelwert der Brennweite
    this->Vec_Object[0]      = x_Kamera_KS;
    this->Vec_Object[1]      = y_Kamera_KS;
    //this->Vec_Object[2]      = f;
    //double Vec_Object_Abs    = sqrt(x_Kamera_KS * x_Kamera_KS + y_Kamera_KS * y_Kamera_KS + f * f);
    //this->Vec_Object[0]     /= Vec_Object_Abs;
    //this->Vec_Object[1]     /= Vec_Object_Abs;
    //this->Vec_Object[2]     /= Vec_Object_Abs;


    // Schreibe die Delta-Werte auf das Bild
    std::string Delta_x_str   = std::to_string(Delta_x);
    std::string Delta_y_str   = std::to_string(Delta_y);
    cv::putText(*dst_contoured_image, "Delta_x: " + Delta_x_str, cv::Point(0, 80), 1, 1, cv::Scalar(255, 255, 255), 2);
    cv::putText(*dst_contoured_image, "Delta_y: " + Delta_y_str, cv::Point(0, 110), 1, 1, cv::Scalar(255, 255, 255), 2);

    // Zeichne eine Linie zwischen kalibriertem Bildmittelpunkt und dem Objektschwerpunkt
    cv::line(*dst_contoured_image, cv::Point((int)Ist_x, (int)Ist_y), cv::Point((int)Soll_x, (int)Soll_y), cv::Scalar(0, 0, 255), 4, 8, 0);

    }
  else
    {
    this->contour_found     = false;
//    this->Vec_Object[0]     = 0.0;
//    this->Vec_Object[1]     = 0.0;
//    this->Vec_Object[2]     = 0.0;
    this->max_Moment_m00    = 0.0;

    cv::putText(*dst_contoured_image, "S_x:     Object not found", cv::Point(0, 20), 1, 1, cv::Scalar(255, 255, 255), 2);
    cv::putText(*dst_contoured_image, "S_y:     Object not found", cv::Point(0, 50), 1, 1, cv::Scalar(255, 255, 255), 2);
    cv::putText(*dst_contoured_image, "Delta_x: Object not found", cv::Point(0, 80), 1, 1, cv::Scalar(255, 255, 255), 2);
    cv::putText(*dst_contoured_image, "Delta_y: Object not found", cv::Point(0, 110), 1, 1, cv::Scalar(255, 255, 255), 2);
    }
  }






     