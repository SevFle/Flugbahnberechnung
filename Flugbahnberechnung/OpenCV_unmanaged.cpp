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

/********************************GETTER SETTER************/
cv::Mat*& c_opencv_unmanaged::get_cpu_src_img ()
  {
  return cpu_src_img;
  }
void c_opencv_unmanaged::set_cpu_src_img (cv::Mat* cpu_src_img)
  {
  this->cpu_src_img = cpu_src_img;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_temp ()
  {
  return cpu_temp;
  }
void c_opencv_unmanaged::set_cpu_temp (cv::Mat* cpu_temp)
  {
  this->cpu_temp = cpu_temp;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_masked_img ()
  {
  return cpu_masked_img;
  }
void c_opencv_unmanaged::set_cpu_masked_img (cv::Mat* cpu_masked_img)
  {
  this->cpu_masked_img = cpu_masked_img;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_hsv_filtered ()
  {
  return cpu_hsv_filtered;
  }
void c_opencv_unmanaged::set_cpu_hsv_filtered (cv::Mat* cpu_hsv_filtered)
  {
  this->cpu_hsv_filtered = cpu_hsv_filtered;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_contoured ()
  {
  return cpu_contoured;
  }
void c_opencv_unmanaged::set_cpu_contoured (cv::Mat* cpu_contoured)
  {
  this->cpu_contoured = cpu_contoured;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_undistorted ()
  {
  return cpu_undistorted;
  }
void c_opencv_unmanaged::set_cpu_undistorted (cv::Mat* cpu_undistorted)
  {
  this->cpu_undistorted = cpu_undistorted;
  }
cv::Mat*& c_opencv_unmanaged::get_cpu_cropped_img ()
  {
  return cpu_cropped_img;
  }
void c_opencv_unmanaged::set_cpu_cropped_img (cv::Mat* cpu_cropped_img)
  {
  this->cpu_cropped_img = cpu_cropped_img;
  }
cv::Mat*& c_opencv_unmanaged::get_dist_coeffs ()
  {
  return DistCoeffs;
  }
void c_opencv_unmanaged::set_dist_coeffs (cv::Mat* dist_coeffs)
  {
  DistCoeffs = dist_coeffs;
  }
cv::Mat*& c_opencv_unmanaged::get_intrinsic ()
  {
  return Intrinsic;
  }
void c_opencv_unmanaged::set_intrinsic (cv::Mat* intrinsic)
  {
  Intrinsic = intrinsic;
  }
int& c_opencv_unmanaged::get_camera_id ()
  {
  return camera_id;
  }
void c_opencv_unmanaged::set_camera_id (int camera_id)
  {
  this->camera_id = camera_id;
  }
bool& c_opencv_unmanaged::is_thread_running ()
  {
  return thread_running;
  }
void c_opencv_unmanaged::set_thread_running (bool thread_running)
  {
  this->thread_running = thread_running;
  }
bool& c_opencv_unmanaged::is_filtering_active ()
  {
  return filtering_active;
  }
void c_opencv_unmanaged::set_filtering_active (bool filtering_active)
  {
  this->filtering_active = filtering_active;
  }
bool& c_opencv_unmanaged::is_filtering_hsv_active ()
  {
  return filtering_hsv_active;
  }
void c_opencv_unmanaged::set_filtering_hsv_active (bool filtering_hsv_active)
  {
  this->filtering_hsv_active = filtering_hsv_active;
  }
bool& c_opencv_unmanaged::is_filtering_bgr_active ()
  {
  return filtering_bgr_active;
  }
void c_opencv_unmanaged::set_filtering_bgr_active (bool filtering_bgr_active)
  {
  this->filtering_bgr_active = filtering_bgr_active;
  }
bool& c_opencv_unmanaged::is_filtering_gray_active ()
  {
  return filtering_gray_active;
  }
void c_opencv_unmanaged::set_filtering_gray_active (bool filtering_gray_active)
  {
  this->filtering_gray_active = filtering_gray_active;
  }
bool& c_opencv_unmanaged::is_contours_active ()
  {
  return contours_active;
  }
void c_opencv_unmanaged::set_contours_active (bool contours_active)
  {
  this->contours_active = contours_active;
  }
bool& c_opencv_unmanaged::is_undistord_active ()
  {
  return undistord_active;
  }
void c_opencv_unmanaged::set_undistord_active (bool undistord_active)
  {
  this->undistord_active = undistord_active;
  }
bool& c_opencv_unmanaged::is_contour_found ()
  {
  return contour_found;
  }
void c_opencv_unmanaged::set_contour_found (bool contour_found)
  {
  this->contour_found = contour_found;
  }
bool& c_opencv_unmanaged::is_image_prepared ()
  {
  return image_prepared;
  }
void c_opencv_unmanaged::set_image_prepared (bool image_prepared)
  {
  this->image_prepared = image_prepared;
  }
bool& c_opencv_unmanaged::is_show_cropped_image ()
  {
  return show_cropped_image;
  }
void c_opencv_unmanaged::set_show_cropped_image (bool show_cropped_image)
  {
  this->show_cropped_image = show_cropped_image;
  }
int& c_opencv_unmanaged::get_capture_api ()
  {
  return capture_api;
  }
void c_opencv_unmanaged::set_capture_api (int capture_api)
  {
  this->capture_api = capture_api;
  }
int& c_opencv_unmanaged::get_objekt_anzahl ()
  {
  return objekt_anzahl;
  }
void c_opencv_unmanaged::set_objekt_anzahl (int objekt_anzahl)
  {
  this->objekt_anzahl = objekt_anzahl;
  }
int& c_opencv_unmanaged::get_kontur_index ()
  {
  return KonturIndex;
  }
void c_opencv_unmanaged::set_kontur_index (int kontur_index)
  {
  KonturIndex = kontur_index;
  }
int& c_opencv_unmanaged::get_objekt_anzahl ()
  {
  return Objekt_Anzahl;
  }
void c_opencv_unmanaged::set_objekt_anzahl (int objekt_anzahl)
  {
  Objekt_Anzahl = objekt_anzahl;
  }
double& c_opencv_unmanaged::get_max_moment_m00 ()
  {
  return max_Moment_m00;
  }
void c_opencv_unmanaged::set_max_moment_m00 (double max_moment_m00)
  {
  max_Moment_m00 = max_moment_m00;
  }
double& c_opencv_unmanaged::get_ist_x ()
  {
  return Ist_x;
  }
void c_opencv_unmanaged::set_ist_x (double ist_x)
  {
  Ist_x = ist_x;
  }
double& c_opencv_unmanaged::get_ist_y ()
  {
  return Ist_y;
  }
void c_opencv_unmanaged::set_ist_y (double ist_y)
  {
  Ist_y = ist_y;
  }
double& c_opencv_unmanaged::get_soll_x ()
  {
  return Soll_x;
  }
void c_opencv_unmanaged::set_soll_x (double soll_x)
  {
  Soll_x = soll_x;
  }
double& c_opencv_unmanaged::get_soll_y ()
  {
  return Soll_y;
  }
void c_opencv_unmanaged::set_soll_y (double soll_y)
  {
  Soll_y = soll_y;
  }
double& c_opencv_unmanaged::get_delta_x ()
  {
  return Delta_x;
  }
void c_opencv_unmanaged::set_delta_x (double delta_x)
  {
  Delta_x = delta_x;
  }
double& c_opencv_unmanaged::get_delta_y ()
  {
  return Delta_y;
  }
void c_opencv_unmanaged::set_delta_y (double delta_y)
  {
  Delta_y = delta_y;
  }
double& c_opencv_unmanaged::get_moment_0_ordnung ()
  {
  return Moment_0_Ordnung;
  }
void c_opencv_unmanaged::set_moment_0_ordnung (double moment_0_ordnung)
  {
  Moment_0_Ordnung = moment_0_ordnung;
  }
double& c_opencv_unmanaged::get_moment_1_ordnung_x ()
  {
  return Moment_1_Ordnung_x;
  }
void c_opencv_unmanaged::set_moment_1_ordnung_x (double moment_1_ordnung_x)
  {
  Moment_1_Ordnung_x = moment_1_ordnung_x;
  }
double& c_opencv_unmanaged::get_moment_1_ordnung_y ()
  {
  return Moment_1_Ordnung_y;
  }
void c_opencv_unmanaged::set_moment_1_ordnung_y (double moment_1_ordnung_y)
  {
  Moment_1_Ordnung_y = moment_1_ordnung_y;
  }
double& c_opencv_unmanaged::get_schwerpunkt_x ()
  {
  return Schwerpunkt_x;
  }
void c_opencv_unmanaged::set_schwerpunkt_x (double schwerpunkt_x)
  {
  Schwerpunkt_x = schwerpunkt_x;
  }
double& c_opencv_unmanaged::get_schwerpunkt_y ()
  {
  return Schwerpunkt_y;
  }
void c_opencv_unmanaged::set_schwerpunkt_y (double schwerpunkt_y)
  {
  Schwerpunkt_y = schwerpunkt_y;
  }
double& c_opencv_unmanaged::get_mittelpunkt_x ()
  {
  return Mittelpunkt_x;
  }
void c_opencv_unmanaged::set_mittelpunkt_x (double mittelpunkt_x)
  {
  Mittelpunkt_x = mittelpunkt_x;
  }
double& c_opencv_unmanaged::get_mittelpunkt_y ()
  {
  return Mittelpunkt_y;
  }
void c_opencv_unmanaged::set_mittelpunkt_y (double mittelpunkt_y)
  {
  Mittelpunkt_y = mittelpunkt_y;
  }
double& c_opencv_unmanaged::get_x_kamera_ks ()
  {
  return x_Kamera_KS;
  }
void c_opencv_unmanaged::set_x_kamera_ks (double kamera_ks)
  {
  x_Kamera_KS = kamera_ks;
  }
double& c_opencv_unmanaged::get_y_kamera_ks ()
  {
  return y_Kamera_KS;
  }
void c_opencv_unmanaged::set_y_kamera_ks (double kamera_ks)
  {
  y_Kamera_KS = kamera_ks;
  }
double& c_opencv_unmanaged::get_cx ()
  {
  return cx;
  }
void c_opencv_unmanaged::set_cx (double cx)
  {
  this->cx = cx;
  }
double& c_opencv_unmanaged::get_cy ()
  {
  return cy;
  }
void c_opencv_unmanaged::set_cy (double cy)
  {
  this->cy = cy;
  }
double& c_opencv_unmanaged::get_fx ()
  {
  return fx;
  }
void c_opencv_unmanaged::set_fx (double fx)
  {
  this->fx = fx;
  }
double& c_opencv_unmanaged::get_fy ()
  {
  return fy;
  }
void c_opencv_unmanaged::set_fy (double fy)
  {
  this->fy = fy;
  }
double& c_opencv_unmanaged::get_f ()
  {
  return f;
  }
void c_opencv_unmanaged::set_f (double f)
  {
  this->f = f;
  }
double& c_opencv_unmanaged::get_vec_object_abs ()
  {
  return Vec_Object_Abs;
  }
void c_opencv_unmanaged::set_vec_object_abs (double vec_object_abs)
  {
  Vec_Object_Abs = vec_object_abs;
  }
float& c_opencv_unmanaged::get_radius ()
  {
  return Radius;
  }
void c_opencv_unmanaged::set_radius (float radius)
  {
  Radius = radius;
  }
cv::Moments& c_opencv_unmanaged::get_image_moments ()
  {
  return Image_Moments;
  }
void c_opencv_unmanaged::set_image_moments (const cv::Moments& image_moments)
  {
  Image_Moments = image_moments;
  }
cv::Point2f& c_opencv_unmanaged::get_center ()
  {
  return Center;
  }
void c_opencv_unmanaged::set_center (const cv::Point2f& center)
  {
  Center = center;
  }
std::string& c_opencv_unmanaged::get_s_x ()
  {
  return S_x;
  }
void c_opencv_unmanaged::set_s_x (const std::string& cs)
  {
  S_x = cs;
  }
std::string& c_opencv_unmanaged::get_s_y ()
  {
  return S_y;
  }
void c_opencv_unmanaged::set_s_y (const std::string& cs)
  {
  S_y = cs;
  }
std::string& c_opencv_unmanaged::get_delta_x_str ()
  {
  return Delta_x_str;
  }
void c_opencv_unmanaged::set_delta_x_str (const std::string& delta_x_str)
  {
  Delta_x_str = delta_x_str;
  }
std::string& c_opencv_unmanaged::get_delta_y_str ()
  {
  return Delta_y_str;
  }
void c_opencv_unmanaged::set_delta_y_str (const std::string& delta_y_str)
  {
  Delta_y_str = delta_y_str;
  }
cv::Rect& c_opencv_unmanaged::get_rect_roi ()
  {
  return rect_roi;
  }
void c_opencv_unmanaged::set_rect_roi (const cv::Rect& rect_roi)
  {
  this->rect_roi = rect_roi;
  }
uchar& c_opencv_unmanaged::get_hue_min ()
  {
  return hue_min;
  }
void c_opencv_unmanaged::set_hue_min (uchar hue_min)
  {
  this->hue_min = hue_min;
  }
uchar& c_opencv_unmanaged::get_hue_max ()
  {
  return hue_max;
  }
void c_opencv_unmanaged::set_hue_max (uchar hue_max)
  {
  this->hue_max = hue_max;
  }
uchar& c_opencv_unmanaged::get_saturation_min ()
  {
  return saturation_min;
  }
void c_opencv_unmanaged::set_saturation_min (uchar saturation_min)
  {
  this->saturation_min = saturation_min;
  }
uchar& c_opencv_unmanaged::get_saturation_max ()
  {
  return saturation_max;
  }
void c_opencv_unmanaged::set_saturation_max (uchar saturation_max)
  {
  this->saturation_max = saturation_max;
  }
uchar& c_opencv_unmanaged::get_value_min ()
  {
  return value_min;
  }
void c_opencv_unmanaged::set_value_min (uchar value_min)
  {
  this->value_min = value_min;
  }
uchar& c_opencv_unmanaged::get_value_max ()
  {
  return value_max;
  }
void c_opencv_unmanaged::set_value_max (uchar value_max)
  {
  this->value_max = value_max;
  }
int& c_opencv_unmanaged::get_erosion_iterations ()
  {
  return erosion_iterations;
  }
void c_opencv_unmanaged::set_erosion_iterations (int erosion_iterations)
  {
  this->erosion_iterations = erosion_iterations;
  }
int& c_opencv_unmanaged::get_dilation_iterations ()
  {
  return dilation_iterations;
  }
void c_opencv_unmanaged::set_dilation_iterations (int dilation_iterations)
  {
  this->dilation_iterations = dilation_iterations;
  }
int& c_opencv_unmanaged::get_opening_iterations ()
  {
  return opening_iterations;
  }
void c_opencv_unmanaged::set_opening_iterations (int opening_iterations)
  {
  this->opening_iterations = opening_iterations;
  }
int& c_opencv_unmanaged::get_closing_iterations ()
  {
  return closing_iterations;
  }
void c_opencv_unmanaged::set_closing_iterations (int closing_iterations)
  {
  this->closing_iterations = closing_iterations;
  }
int& c_opencv_unmanaged::get_morph_iterations ()
  {
  return morph_iterations;
  }
void c_opencv_unmanaged::set_morph_iterations (int morph_iterations)
  {
  this->morph_iterations = morph_iterations;
  }
int& c_opencv_unmanaged::get_erosion_kernel_size ()
  {
  return erosion_kernel_size;
  }
void c_opencv_unmanaged::set_erosion_kernel_size (int erosion_kernel_size)
  {
  this->erosion_kernel_size = erosion_kernel_size;
  }
int& c_opencv_unmanaged::get_dilation_kernel_size ()
  {
  return dilation_kernel_size;
  }
void c_opencv_unmanaged::set_dilation_kernel_size (int dilation_kernel_size)
  {
  this->dilation_kernel_size = dilation_kernel_size;
  }
int& c_opencv_unmanaged::get_bilateral_kernel_size ()
  {
  return bilateral_kernel_size;
  }
void c_opencv_unmanaged::set_bilateral_kernel_size (int bilateral_kernel_size)
  {
  this->bilateral_kernel_size = bilateral_kernel_size;
  }
int& c_opencv_unmanaged::get_opening_kernel_size ()
  {
  return opening_kernel_size;
  }
void c_opencv_unmanaged::set_opening_kernel_size (int opening_kernel_size)
  {
  this->opening_kernel_size = opening_kernel_size;
  }
int& c_opencv_unmanaged::get_closing_kernel_size ()
  {
  return closing_kernel_size;
  }
void c_opencv_unmanaged::set_closing_kernel_size (int closing_kernel_size)
  {
  this->closing_kernel_size = closing_kernel_size;
  }
int& c_opencv_unmanaged::get_morph_kernel_size ()
  {
  return morph_kernel_size;
  }
void c_opencv_unmanaged::set_morph_kernel_size (int morph_kernel_size)
  {
  this->morph_kernel_size = morph_kernel_size;
  }
int& c_opencv_unmanaged::get_gaussian_kernel_size ()
  {
  return gaussian_kernel_size;
  }
void c_opencv_unmanaged::set_gaussian_kernel_size (int gaussian_kernel_size)
  {
  this->gaussian_kernel_size = gaussian_kernel_size;
  }
int& c_opencv_unmanaged::get_resize_width ()
  {
  return resize_width;
  }
void c_opencv_unmanaged::set_resize_width (int resize_width)
  {
  this->resize_width = resize_width;
  }
int& c_opencv_unmanaged::get_resize_height ()
  {
  return resize_height;
  }
void c_opencv_unmanaged::set_resize_height (int resize_height)
  {
  this->resize_height = resize_height;
  }
double& c_opencv_unmanaged::get_gaussian_sigma ()
  {
  return gaussian_sigma;
  }
void c_opencv_unmanaged::set_gaussian_sigma (double gaussian_sigma)
  {
  this->gaussian_sigma = gaussian_sigma;
  }
double& c_opencv_unmanaged::get_object_size_min ()
  {
  return Object_Size_min;
  }
void c_opencv_unmanaged::set_object_size_min (double object_size_min)
  {
  Object_Size_min = object_size_min;
  }
double& c_opencv_unmanaged::get_object_size_max ()
  {
  return Object_Size_max;
  }
void c_opencv_unmanaged::set_object_size_max (double object_size_max)
  {
  Object_Size_max = object_size_max;
  }
float& c_opencv_unmanaged::get_bilateral_sigma_color ()
  {
  return bilateral_sigma_color;
  }
void c_opencv_unmanaged::set_bilateral_sigma_color (float bilateral_sigma_color)
  {
  this->bilateral_sigma_color = bilateral_sigma_color;
  }
float& c_opencv_unmanaged::get_bilateral_sigma_spatial ()
  {
  return bilateral_sigma_spatial;
  }
void c_opencv_unmanaged::set_bilateral_sigma_spatial (float bilateral_sigma_spatial)
  {
  this->bilateral_sigma_spatial = bilateral_sigma_spatial;
  }
bool& c_opencv_unmanaged::is_erode_active ()
  {
  return erode_active;
  }
void c_opencv_unmanaged::set_erode_active (bool erode_active)
  {
  this->erode_active = erode_active;
  }
bool& c_opencv_unmanaged::is_dilate_active ()
  {
  return dilate_active;
  }
void c_opencv_unmanaged::set_dilate_active (bool dilate_active)
  {
  this->dilate_active = dilate_active;
  }
bool& c_opencv_unmanaged::is_gaussian_active ()
  {
  return gaussian_active;
  }
void c_opencv_unmanaged::set_gaussian_active (bool gaussian_active)
  {
  this->gaussian_active = gaussian_active;
  }
bool& c_opencv_unmanaged::is_morph_active ()
  {
  return morph_active;
  }
void c_opencv_unmanaged::set_morph_active (bool morph_active)
  {
  this->morph_active = morph_active;
  }
bool& c_opencv_unmanaged::is_bilateral_active ()
  {
  return bilateral_active;
  }
void c_opencv_unmanaged::set_bilateral_active (bool bilateral_active)
  {
  this->bilateral_active = bilateral_active;
  }
bool& c_opencv_unmanaged::is_idle ()
  {
  return idle;
  }
void c_opencv_unmanaged::set_idle (bool idle)
  {
  this->idle = idle;
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

    if (Object_Size_min > Moment_0_Ordnung || Moment_0_Ordnung > Object_Size_max)
      {
      return;
      }

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
