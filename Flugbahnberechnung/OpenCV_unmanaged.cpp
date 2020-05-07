#pragma once
/****************************************************************** Includes ****************************************************************/
#include "opencv_unmanaged.h"
#include "posen.h"
/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_opencv_unmanaged;
/*************************************************************** Konstruktoren **************************************************************/
c_opencv_unmanaged::c_opencv_unmanaged (int camera_id)
  {
  hue_min        = 0;
  hue_max        = 179;
  saturation_min = 0;
  saturation_max = 255;
  value_min      = 0;
  value_max      = 255;

  erosion_iterations  = 1;
  dilation_iterations = 1;
  opening_iterations  = 1;
  closing_iterations  = 1;
  morph_iterations    = 1;
  gaussian_sigma      = 0.1;

  erosion_kernel_size  = 1;
  dilation_kernel_size = 1;
  opening_kernel_size  = 1;
  morph_kernel_size    = 1;
  closing_kernel_size  = 1;
  gaussian_kernel_size = 1;

  bilateral_kernel_size   = 1;
  bilateral_sigma_color   = 0;
  bilateral_sigma_spatial = 0;

  fx              = 0;
  fy              = 0;
  f               = 0;
  Vec_Object_Abs  = 0;
  Object_Size_min = 0;
  Object_Size_max = 0;
  resize_height   = 400;
  resize_width    = 400;
  gaussian_active = false;

  erode_active     = false;
  dilate_active    = false;
  morph_active     = false;
  bilateral_active = false;


  capture_api     = cv::CAP_DSHOW;
  this->camera_id = camera_id;

  thread_running   = true;
  filtering_active = false;

  filtering_hsv_active  = true;
  filtering_bgr_active  = false;
  filtering_gray_active = false;


  idle = false;

  undistord_active = true;


  this->gpu_src_img         = new cv::cuda::GpuMat();
  this->gpu_thresholded     = new cv::cuda::GpuMat();
  this->gpu_filtered        = new cv::cuda::GpuMat();
  this->gpu_src2color       = new cv::cuda::GpuMat();
  this->gpu_color_threshold = new cv::cuda::GpuMat();
  this->gpu_bgr_threshold   = new cv::cuda::GpuMat();
  this->gpu_temp            = new cv::cuda::GpuMat();

  this->gpu_map1 = new cv::cuda::GpuMat();
  this->gpu_map2 = new cv::cuda::GpuMat();


  this->cpu_src_img = new cv::Mat();
  this->cpu_temp    = new cv::Mat();

  this->cpu_masked_img   = new cv::Mat();
  this->cpu_hsv_filtered = new cv::Mat();
  this->cpu_contoured    = new cv::Mat();
  this->cpu_undistorted  = new cv::Mat();
  this->cpu_cropped_img  = new cv::Mat();


  this->DistCoeffs = new cv::Mat (cv::Mat_<double> (1,5));
  this->Intrinsic  = new cv::Mat (cv::Mat_<double> (3,3));

  this->gpu_gaussian_kernel_size = new cv::cuda::GpuMat();
  /**************************************************************** Contour variablen ****************************************************************/
  objekt_anzahl = 0;
  KonturIndex   = 0;
  Objekt_Anzahl = 0;

  Vec_Object[0] = 0;
  Vec_Object[1] = 0;
  Vec_Object[2] = 0;

  max_Moment_m00     = 0.0;
  Ist_x              = 0.0;
  Ist_y              = 0.0;
  Soll_x             = 0.0;
  Soll_y             = 0.0;
  Delta_x            = 0.0;
  Delta_y            = 0.0;
  Moment_0_Ordnung   = 0.0;
  Moment_1_Ordnung_x = 0.0;
  Moment_1_Ordnung_y = 0.0;
  Schwerpunkt_x      = 0.0;
  Schwerpunkt_y      = 0.0;
  Mittelpunkt_x      = 0.0;
  Mittelpunkt_y      = 0.0;
  x_Kamera_KS        = 0.0;
  y_Kamera_KS        = 0.0;
  cx                 = 0.0;
  cy                 = 0.0;

  contour_found = false;
  Radius        = 0.0f;

  this->cap = new cv::VideoCapture;
  }

/**************************************************************** Destruktor ****************************************************************/
c_opencv_unmanaged::~c_opencv_unmanaged ()
  {
  hue_min             = 0;
  hue_max             = 0;
  saturation_min      = 0;
  saturation_max      = 0;
  value_min           = 0;
  value_max           = 0;
  erosion_iterations  = 0;
  dilation_iterations = 0;
  opening_iterations  = 0;
  closing_iterations  = 0;
  gaussian_sigma      = 0;

  erosion_kernel_size  = 0;
  dilation_kernel_size = 0;
  opening_kernel_size  = 0;
  morph_kernel_size    = 0;
  closing_kernel_size  = 0;

  bilateral_kernel_size   = 0;
  bilateral_sigma_color   = 0;
  bilateral_sigma_spatial = 0;


  erode_active       = false;
  dilate_active      = false;
  morph_active       = false;
  bilateral_active   = false;
  show_cropped_image = false;


  capture_api = cv::CAP_DSHOW;
  camera_id   = 0;

  thread_running = true;

  idle = false;


  delete (gpu_src_img);
  delete (gpu_thresholded);
  delete (gpu_filtered);
  delete (gpu_src2color);
  delete (gpu_color_threshold);
  delete (gpu_bgr_threshold);
  delete (gpu_temp);

  delete (gpu_map1);
  delete (gpu_map2);

  delete (cpu_src_img);
  delete (cpu_temp);
  delete (cpu_masked_img);
  delete (cpu_hsv_filtered);
  delete (cpu_contoured);
  delete (cpu_cropped_img);

  delete (cap);

  objekt_anzahl = 0;
  KonturIndex   = 0;
  Objekt_Anzahl = 0;

  Vec_Object[0] = 0;
  Vec_Object[1] = 0;
  Vec_Object[2] = 0;

  max_Moment_m00     = 0.0;
  Ist_x              = 0.0;
  Ist_y              = 0.0;
  Soll_x             = 0.0;
  Soll_y             = 0.0;
  Delta_x            = 0.0;
  Delta_y            = 0.0;
  Moment_0_Ordnung   = 0.0;
  Moment_1_Ordnung_x = 0.0;
  Moment_1_Ordnung_y = 0.0;
  Schwerpunkt_x      = 0.0;
  Schwerpunkt_y      = 0.0;
  Mittelpunkt_x      = 0.0;
  Mittelpunkt_y      = 0.0;
  x_Kamera_KS        = 0.0;
  y_Kamera_KS        = 0.0;
  cx                 = 0.0;
  cy                 = 0.0;

  contour_found = false;
  Radius        = 0.0f;
  }

/************************************************************* Öffentliche Klassenmethoden*************************************************/

void c_opencv_unmanaged::camera_thread ()
  {
  int      statemachine_state = 0;
  cv::Rect RoI;

  while (thread_running == true)
    {
    switch (statemachine_state)
      {
      case 0:
        std::cout << "Thread " << this->camera_id + 1 << " running with ID: " << std::this_thread::get_id() << std::endl << std::endl << std::endl;

        init (camera_id);


        statemachine_state = 1;
        break;

        //used for keeping Threads in idle mode. Increases CPU usage to max through switching too fast in the statemachine.
      case 1:
        if (idle)
          {
          std::this_thread::sleep_for (std::chrono::milliseconds (200));
          break;
          }
        statemachine_state = 2;
        break;

        //STEP2: Grab a new frame from Videocapture object
      case 2:
        this->cpu_grab_frame (cpu_src_img);

        if (undistord_active == true)
          {
          statemachine_state = 3;
          break;
          }
        //Proceed to imshow
        statemachine_state = 8;
        break;

        //STEP 3: Undistort and remap the source image if needed. Remaping via GPU
      case 3:
        this->undistord_img (this->cpu_src_img,this->cpu_undistorted);
        this->image_prepared = false;
        statemachine_state   = 4;
        break;

        //STEP 4: Crop image to remove black corners
      case 4:
        //cv::resize(*cpu_undistorted, *cpu_temp, cpu_src_img->size(),0,0, cv::INTER_CUBIC);
        this->crop_image (cpu_undistorted,cpu_cropped_img);
        if (show_cropped_image) imshow ("cropped" + std::to_string (camera_id),*cpu_cropped_img);

        if (filtering_active)
          {
          statemachine_state = 5;
          break;
          }
        //Proceed to imshow
        statemachine_state = 8;
        break;


        //STEP 4: Apply chosen filter to cpu_undistorted image
      case 5:
        {
        if (filtering_hsv_active)
          {
          gpu_src_img->upload (*cpu_undistorted);
          gpu_filter_hsv (gpu_src_img,gpu_thresholded);
          }
        if (filtering_bgr_active)
          {
          gpu_src_img->upload (*cpu_undistorted);
          gpu_filter_bgr (gpu_src_img,gpu_thresholded);
          }
        if (filtering_gray_active)
          {
          gpu_src_img->upload (*cpu_undistorted);
          gpu_filter_gray (gpu_src_img,gpu_thresholded);
          }

        gpu_thresholded->download (*cpu_masked_img);


        //gpu_filtered stellt das gefilterte HSV Bild dar.
        this->gpu_filtered->download (*cpu_hsv_filtered);

        RoI = boundingRect (*cpu_hsv_filtered);

        statemachine_state = 6;
        break;

        //STEP 5: Find Contours and draw them onto cpu_contoured
      case 6:
        this->cpu_undistorted->copyTo (*cpu_contoured);

        this->find_contours (cpu_hsv_filtered,cpu_contoured);
        rectangle (*cpu_contoured,RoI,cv::Scalar (0,255,0),2,8,0);
        imshow ("contoured" + std::to_string (camera_id),*cpu_contoured);
        //Proceed to imshow
        statemachine_state = 8;
        break;

      case 8:
        if (cv::waitKey (1) >= 0) break;

        statemachine_state = 1;
        }
      }
    }
  std::cout << std::endl << "Thread " << std::this_thread::get_id() << " ending." << std::endl;
  }

/********************************************************Öffentlich Get and Set methods for Cameras************************/
void c_opencv_unmanaged::get_calibration_parameter (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const
  {
  for (int i = 0; i < 1; i++)
    {
    for (int j = 0; j < 5; j++)
      {
      //temp = this->DistCoeffs->at<double>(i, j);
      //temp.replace(temp.begin(), temp.end(), );
      DistCoeffs[i][j] = this->DistCoeffs->at<double> (i,j);
      }
    }

  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      Intrinsic[i][j] = this->Intrinsic->at<double> (i,j);
      }
    }
  }
void c_opencv_unmanaged::get_camera_settings ()
  {
  }
void c_opencv_unmanaged::get_objectPosition_2D_Pixel (bool& Contour_Found, S_Positionsvektor& Vec_Object)
  {
  Contour_Found = this->contour_found;
  Vec_Object.X  = this->Vec_Object[0];
  Vec_Object.Y  = this->Vec_Object[1];
  Vec_Object.Z  = this->Vec_Object[2];
  }

void c_opencv_unmanaged::set_calibration_parameter (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3])
  {
  for (int i = 0; i < 1; i++)
    {
    for (int j = 0; j < 5; j++)
      {
      this->DistCoeffs->at<double> (i,j) = DistCoeffs[i][j];
      }
    }

  for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
      {
      this->Intrinsic->at<double> (i,j) = Intrinsic[i][j];
      }
    }
  }
void c_opencv_unmanaged::set_aspect_ratio (int Height, int width)
  {
  this->cap->set (cv::CAP_PROP_FRAME_HEIGHT,Height);
  this->cap->set (cv::CAP_PROP_FRAME_WIDTH,width);
  }
void c_opencv_unmanaged::set_framerate (int framerate)
  {
  this->cap->set (cv::CAP_PROP_FPS,framerate);
  }
/*************************************************************** Private Klassenmethoden*****************************************************/

void c_opencv_unmanaged::init (int camera_id)
  {
  //ELP Webcam 5-50 mm USB8MP02G-SFV
  //  1024X768  MJPEG 30fps
  //  800X600   MJPEG 30fps
  //  640X480   MJPEG 30fps

  cap->set (cv::CAP_PROP_FRAME_HEIGHT,600);
  cap->set (cv::CAP_PROP_FRAME_WIDTH,800);
  cap->set (cv::CAP_PROP_FPS,30);
  cap->set (cv::CAP_PROP_BUFFERSIZE,3);
  cap->open (camera_id,capture_api);

  //+--------+----+----+----+----+------+------+------+------+
  //  |        | C1 | C2 | C3 | C4 | C(5) | C(6) | C(7) | C(8) |
  //  +--------+----+----+----+----+------+------+------+------+
  //  | CV_8U  |  0 |  8 | 16 | 24 |   32 |   40 |   48 |   56 |
  //  | CV_8S  |  1 |  9 | 17 | 25 |   33 |   41 |   49 |   57 |
  //  | CV_16U |  2 | 10 | 18 | 26 |   34 |   42 |   50 |   58 |
  //  | CV_16S |  3 | 11 | 19 | 27 |   35 |   43 |   51 |   59 |
  //  | CV_32S |  4 | 12 | 20 | 28 |   36 |   44 |   52 |   60 |
  //  | CV_32F |  5 | 13 | 21 | 29 |   37 |   45 |   53 |   61 |
  //  | CV_64F |  6 | 14 | 22 | 30 |   38 |   46 |   54 |   62 |
  //  +--------+----+----+----+----+------+------+------+------+

  //Redifinition der zwei GpuMat Arrays für die Verwendung in der Cuda-InRange Funktion. 
  gpu_src2color->create (600,800, CV_8UC1);
  gpu_color_threshold->create (600,800, CV_8UC1);
  cpu_undistorted->create (600,800, CV_32FC1);
  cpu_contoured->create (600,800, CV_8UC3);

  this->init_rectify_map();
  }
void c_opencv_unmanaged::cpu_grab_frame (cv::Mat* cpu_dst_img)
  {
  cap->read (*cpu_dst_img);
  }
void c_opencv_unmanaged::apply_filter (cv::Mat* cpu_src, cv::Mat* cpu_dst)
  {
  if (filtering_hsv_active == true)
    {
    gpu_src_img->upload (*cpu_src);
    gpu_filter_hsv (gpu_src_img,gpu_thresholded);
    }
  //if (filtering_bgr_active == true)
  //  {
  //  gpu_src_img->upload                                     (*cpu_src);
  //  gpu_filter_bgr                                          (gpu_src_img, gpu_thresholded);
  //  }
  //if (filtering_gray_active == true)
  //  {
  //  gpu_src_img->upload                                     (*cpu_src);
  //  gpu_filter_gray                                         (gpu_src_img, gpu_thresholded);
  //  }

  gpu_thresholded->download (*cpu_dst);
  }
void c_opencv_unmanaged::init_rectify_map ()
  {
  cv::Mat cpu_map1;
  cv::Mat cpu_map2;


  initUndistortRectifyMap (*Intrinsic,*DistCoeffs,cv::Mat(),*Intrinsic,cv::Size (cpu_undistorted->cols,cpu_undistorted->rows), CV_32FC1,cpu_map1,cpu_map2);

  this->gpu_map1->upload (cpu_map1);
  this->gpu_map2->upload (cpu_map2);
  }

void c_opencv_unmanaged::gpu_erode (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, int borderType)  //
  {
  cv::Mat                   erode_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * erosion_kernel_size,2 * erosion_kernel_size));
  cv::Ptr<cv::cuda::Filter> erode                     = cv::cuda::createMorphologyFilter (cv::MORPH_ERODE,gpu_src->type(),erode_structuring_element,cv::Point (-1,-1),erosion_iterations);
  erode->apply (*gpu_src,*gpu_dst);
  }
void c_opencv_unmanaged::gpu_dilate (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)   //
  {
  cv::Mat                   dilate_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * dilation_kernel_size,2 * dilation_kernel_size));
  cv::Ptr<cv::cuda::Filter> dilate                     = cv::cuda::createMorphologyFilter (cv::MORPH_DILATE,gpu_src->type(),dilate_structuring_element,cv::Point (-1,-1),dilation_iterations);
  dilate->apply (*gpu_src,*gpu_dst);
  }
void c_opencv_unmanaged::gpu_open (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::Mat                   opening_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * opening_kernel_size,2 * opening_kernel_size));
  cv::Ptr<cv::cuda::Filter> opening                     = cv::cuda::createMorphologyFilter (cv::MORPH_OPEN,gpu_src->type(),opening_structuring_element,cv::Point (-1,-1),opening_iterations);
  opening->apply (*gpu_src,*gpu_dst);
  }
void c_opencv_unmanaged::gpu_close (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::Mat                   closing_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * closing_kernel_size,2 * closing_kernel_size));
  cv::Ptr<cv::cuda::Filter> closing                     = cv::cuda::createMorphologyFilter (cv::MORPH_CLOSE,gpu_src->type(),closing_structuring_element,cv::Point (-1,-1),closing_iterations);
  closing->apply (*gpu_src,*gpu_dst);
  }

void c_opencv_unmanaged::gpu_bilateral_filter (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::cuda::bilateralFilter (*gpu_src,*gpu_dst,bilateral_kernel_size,bilateral_sigma_color,bilateral_sigma_spatial,cv::BORDER_DEFAULT);
  }
void c_opencv_unmanaged::gpu_gaussian_filter (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  this->get_gaussian_kernel();
  cv::Ptr<cv::cuda::Filter> gauss = cv::cuda::createGaussianFilter (gpu_src->type(),-1,gpu_gaussian_kernel_size->size(),gaussian_sigma,gaussian_sigma,cv::BORDER_DEFAULT);
  gauss->apply (*gpu_src,*gpu_dst);
  }
void c_opencv_unmanaged::gpu_morph_gradient (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::Mat                   morph_structuring_element = getStructuringElement (cv::MORPH_ELLIPSE,cv::Size (2 * morph_kernel_size,2 * morph_kernel_size));
  cv::Ptr<cv::cuda::Filter> morph                     = cv::cuda::createMorphologyFilter (cv::MORPH_GRADIENT,gpu_src->type(),morph_structuring_element,cv::Point (-1,-1),morph_iterations);
  morph->apply (*gpu_src,*gpu_dst);
  }
void c_opencv_unmanaged::get_gaussian_kernel ()
  {
  cv::Mat cpu_gaussian = cv::getGaussianKernel (gaussian_kernel_size,gaussian_sigma, CV_32F);
  gpu_gaussian_kernel_size->upload (cpu_gaussian);
  }

void c_opencv_unmanaged::gpu_filter_hsv (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  cv::cuda::cvtColor (*gpu_src,*gpu_temp,cv::COLOR_BGR2HSV);

  gpu_gaussian_filter (gpu_temp,gpu_filtered);

  cudaKernel::inRange_gpu (*gpu_filtered,cv::Scalar (this->hue_min,this->saturation_min,this->value_min),
                           cv::Scalar (this->hue_max,this->saturation_max,this->value_max),*gpu_color_threshold);

  gpu_open (gpu_color_threshold,gpu_temp);

  gpu_close (gpu_temp,gpu_filtered);

  cv::cuda::cvtColor (*gpu_filtered,*gpu_temp,cv::COLOR_GRAY2BGR);

  bitwise_and (*gpu_src_img,*gpu_temp,*gpu_dst);
  }

void c_opencv_unmanaged::gpu_filter_bgr (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  }

void c_opencv_unmanaged::gpu_filter_gray (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst)
  {
  }

//TODO Add Objectsize threshold
void c_opencv_unmanaged::find_contours (cv::Mat* thresholded_source_image, cv::Mat* dst_contoured_image)
  {
  objekt_anzahl = 0;
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i>              hirarchy;
  //dst_contoured_image->copyTo(*dst_contoured_image);
  //*dst_contoured_image = cv::Mat::zeros(dst_contoured_image->rows, dst_contoured_image->cols, dst_contoured_image->type());


  //OpenCV Hirarchy: https://docs.opencv.org/3.4/d9/d8b/tutorial_py_contours_hierarchy.html

// Zeichne Bildmittelpunkt ein
  Mittelpunkt_x = dst_contoured_image->cols / 2;
  Mittelpunkt_y = dst_contoured_image->rows / 2;
  circle (*dst_contoured_image,cv::Point (static_cast<int> (Mittelpunkt_x),static_cast<int> (Mittelpunkt_y)),15,cv::Scalar (0,255,0));

  // Zeichne kalibrierten Bildmittelpunkt ein
  cx = this->Intrinsic->at<double> (0,2);
  cy = this->Intrinsic->at<double> (1,2);
  circle (*dst_contoured_image,cv::Point (static_cast<int> (cx),static_cast<int> (cy)),15,cv::Scalar (255,255,0));


  findContours (*thresholded_source_image,contours,hirarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE,cv::Point (0,0));


  objekt_anzahl = static_cast<int> (hirarchy.size());


  if (objekt_anzahl > 0)
    {
    // Vorinitialisierung des Abstands des Konturschwerpunktes zum Bildmittelpunkt
    Image_Moments = moments (static_cast<cv::Mat> (contours[0]));

    KonturIndex    = 0;
    Ist_x          = 0.0;
    Ist_y          = 0.0;
    Soll_x         = 0.0;
    Soll_y         = 0.0;
    Delta_x        = 0.0;
    Delta_y        = 0.0;
    contour_found  = false;
    Vec_Object[0]  = 0.0;
    Vec_Object[1]  = 0.0;
    Vec_Object[2]  = 0.0;
    max_Moment_m00 = 0.0;

    // Größte Kontur anhand der Fläche suchen
    for (int i = 0; i < objekt_anzahl; i++)
      {
      Image_Moments    = moments (static_cast<cv::Mat> (contours[i]));
      Moment_0_Ordnung = Image_Moments.m00;

      if (Moment_0_Ordnung > max_Moment_m00)
        {
        max_Moment_m00 = Moment_0_Ordnung;
        KonturIndex    = i;
        }
      else
        {
        // tue nichts
        }
      }

    // Bestimmen der Flchenmomente 0. (Flche) und 1. Ordnung (Flche * x bzw. Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    Image_Moments    = moments (static_cast<cv::Mat> (contours[KonturIndex]));
    Moment_0_Ordnung = Image_Moments.m00;

    //if (Object_Size_min > Moment_0_Ordnung ||Moment_0_Ordnung > Object_Size_max)
    //  {
    //  return;
    //  }

    // Bestimme Flchenmoment 1. Ordnung (Flche * x bzw.Flche * y) zur Bestimmung des Flchenschwerpunktes: x_ = summe(m1) / summe(m0);
    Moment_1_Ordnung_x = Image_Moments.m10;
    Moment_1_Ordnung_y = Image_Moments.m01;
    Schwerpunkt_x      = Moment_1_Ordnung_x / Moment_0_Ordnung;
    Schwerpunkt_y      = Moment_1_Ordnung_y / Moment_0_Ordnung;

    // Den Radius und den Mittelpunkt des kleinstes Kreises einer gefundenen Kontur ermitteln.
    minEnclosingCircle (static_cast<cv::Mat> (contours[KonturIndex]),Center,Radius);

    // Mittelpunkt / schwerpunkt der kontur einzeichnen
    circle (*dst_contoured_image,cv::Point (static_cast<int> (Schwerpunkt_x),static_cast<int> (Schwerpunkt_y)),2,cv::Scalar (0,255,255));

    // Konturumfang zeichnen
    circle (*dst_contoured_image,Center,static_cast<int> (Radius),cv::Scalar (0,255,255));

    // Schwerpunktkoordinaten als Text im Bild darstellen
    S_x = std::to_string (Schwerpunkt_x);
    S_y = std::to_string (Schwerpunkt_y);
    putText (*dst_contoured_image,"S_x: " + S_x,cv::Point (0,20),1,1,cv::Scalar (255,255,255),2);
    putText (*dst_contoured_image,"S_y: " + S_y,cv::Point (0,50),1,1,cv::Scalar (255,255,255),2);

    // Bestimme den Abstand des Mittelpunktes der gefundenen Kontur zum Bildmittelpunkt
    contour_found = true;
    Ist_x         = Schwerpunkt_x;
    Ist_y         = Schwerpunkt_y;
    Soll_x        = cx;
    Soll_y        = cy;
    Delta_x       = Ist_x - Soll_x;
    Delta_y       = Ist_y - Soll_y;

    // Bestimme den Lichtstrahlvektor der Kontur bezogen auf das Kamera-KS
    x_Kamera_KS    = Delta_x;
    y_Kamera_KS    = Delta_y;
    fx             = this->Intrinsic->at<double> (0,0);
    fy             = this->Intrinsic->at<double> (1,1);
    f              = (fx + fy) / 2.0; // Mittelwert der Brennweite
    Vec_Object[0]  = x_Kamera_KS;
    Vec_Object[1]  = y_Kamera_KS;
    Vec_Object[2]  = f;
    Vec_Object_Abs = sqrt (x_Kamera_KS * x_Kamera_KS + y_Kamera_KS * y_Kamera_KS + f * f);
    Vec_Object[0] /= Vec_Object_Abs;
    Vec_Object[1] /= Vec_Object_Abs;
    Vec_Object[2] /= Vec_Object_Abs;


    // Schreibe die Delta-Werte auf das Bild
    Delta_x_str = std::to_string (Delta_x);
    Delta_y_str = std::to_string (Delta_y);
    putText (*dst_contoured_image,"Delta_x: " + Delta_x_str,cv::Point (0,80),1,1,cv::Scalar (255,255,255),2);
    putText (*dst_contoured_image,"Delta_y: " + Delta_y_str,cv::Point (0,110),1,1,cv::Scalar (255,255,255),2);

    // Zeichne eine Linie zwischen kalibriertem Bildmittelpunkt und dem Objektschwerpunkt
    line (*dst_contoured_image,cv::Point (static_cast<int> (Ist_x),static_cast<int> (Ist_y)),cv::Point (static_cast<int> (Soll_x),static_cast<int> (Soll_y)),cv::Scalar (0,0,255),4,8,0);
    this->image_prepared = true;
    }
  else
    {
    contour_found       = false;
    this->Vec_Object[0] = 0.0;
    this->Vec_Object[1] = 0.0;
    this->Vec_Object[2] = 0.0;
    max_Moment_m00      = 0.0;

    putText (*dst_contoured_image,"S_x:     Object not found",cv::Point (0,20),1,1,cv::Scalar (255,255,255),2);
    putText (*dst_contoured_image,"S_y:     Object not found",cv::Point (0,50),1,1,cv::Scalar (255,255,255),2);
    putText (*dst_contoured_image,"Delta_x: Object not found",cv::Point (0,80),1,1,cv::Scalar (255,255,255),2);
    putText (*dst_contoured_image,"Delta_y: Object not found",cv::Point (0,110),1,1,cv::Scalar (255,255,255),2);
    }
  }

void c_opencv_unmanaged::undistord_img (cv::Mat* cpu_src, cv::Mat* cpu_dst)
  {
  cv::cuda::GpuMat gpu_temp1;
  cv::cuda::GpuMat gpu_temp2;

  gpu_temp1.upload (*cpu_src);

  cv::cuda::remap (gpu_temp1,gpu_temp2,*gpu_map1,*gpu_map2,cv::INTER_NEAREST,cv::BORDER_CONSTANT,0);

  gpu_temp2.download (*cpu_dst);
  }

void c_opencv_unmanaged::save_picture (int camera_id, int photo_id, std::string definition)
  {
  imwrite (definition + std::to_string (camera_id) + "_Snapshot_" + std::to_string (photo_id) + ".png",*cpu_src_img);
  }

void c_opencv_unmanaged::crop_image (cv::Mat* undistorted_img, cv::Mat* crop_undist_img)
  {
  cv::Mat temp;
  undistorted_img->copyTo (temp);
  cv::Rect cropped_region (0,0,this->resize_width,this->resize_height);

  //cv::rectangle(*undistorted_img, cropped_region, cv::Scalar(255, 255, 0), 2, 8, 0);
  //*crop_undist_img = undistorted_img->(cropped_region);
  auto cropped = temp (cropped_region);

  cropped.copyTo (*crop_undist_img);
  }
