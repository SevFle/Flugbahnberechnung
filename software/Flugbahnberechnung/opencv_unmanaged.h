#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//#include <ipp.h>
#include "CudaKernels.cuh"
#include <chrono>

//#include "posen.h"


namespace nmsp_posen
  {
  struct S_Positionsvektor;
  }

namespace nmsp_opencv_unmanaged
  {
  class c_opencv_unmanaged
    {
    public:
    /*************************************************************** Konstruktoren *************************************************************/
    c_opencv_unmanaged (int camera_id);
    /*************************************************************** Destruktor ****************************************************************/
    ~c_opencv_unmanaged ();
    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    cv::cuda::GpuMat* gpu_src_img;
    cv::cuda::GpuMat* gpu_thresholded;
    cv::cuda::GpuMat* gpu_filtered;


    //HSV-Filtering
    cv::cuda::GpuMat* gpu_src2color;
    cv::cuda::GpuMat* gpu_color_threshold;
    cv::cuda::GpuMat* gpu_bgr_threshold;
    cv::cuda::GpuMat* gpu_temp;

    //Maps for undistorting
    cv::cuda::GpuMat* gpu_map1;
    cv::cuda::GpuMat* gpu_map2;
    cv::cuda::GpuMat* gpu_gaussian_kernel_size;


    /**************************************************** Öffentliche Klassenobjekte ********************************************************/
    cv::VideoCapture* cap;
    cv::Mat*          cpu_src_img;
    cv::Mat*          cpu_temp;
    cv::Mat*          cpu_masked_img;
    cv::Mat*          cpu_hsv_filtered;
    cv::Mat*          cpu_contoured;
    cv::Mat*          cpu_undistorted;
    cv::Mat*          cpu_cropped_img;

    cv::Mat* DistCoeffs;
    cv::Mat* Intrinsic;


    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    private:
    int  camera_id;
    bool thread_running;

    bool filtering_active;
    bool filtering_hsv_active;
    bool filtering_bgr_active;
    bool filtering_gray_active;
    bool contours_active;
    bool undistord_active;
    bool contour_found;
    bool image_prepared;
    bool show_cropped_image;

    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    int capture_api;

    /******************************************************************************Zeit Management**********************************************/
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    milliseconds frametime;
  public:
    milliseconds get_frametime() const;
    double get_fps() const;
  private:
    Clock::time_point start;
    Clock::time_point start_alt;

    Clock::time_point end;
    Clock::time_point end_alt;
    double fps;


    /******************************Find_Contours**********************************************/
    int objekt_anzahl;
    int KonturIndex;
    int Objekt_Anzahl;

    cv::Rect RoI;

    double  Vec_Object[3];
    int offset[2];
    
    double max_Moment_m00;
    double Ist_x;
    double Ist_y;
    double Soll_x;
    double Soll_y;
    double Delta_x;
    double Delta_y;
    double Moment_0_Ordnung;
    double Moment_1_Ordnung_x;
    double Moment_1_Ordnung_y;
    double Schwerpunkt_x;
    double Schwerpunkt_y;
    double Mittelpunkt_x;
    double Mittelpunkt_y;
    double x_Kamera_KS;
    double y_Kamera_KS;
    double cx;
    double cy;
    double fx;
    double fy;
    double f;
    double Vec_Object_Abs;

    float Radius;


    //cv::Moments Image_Moments;
    //cv::Point2f Center;
    std::string S_x;
    std::string S_y;
    std::string Delta_x_str;
    std::string Delta_y_str;
    cv::Rect    rect_roi;

  //Background subtractor object für die spätere verwendung. Lernendes Modul, deswegen muss es frühzeitig und scopebasiert initialisiert werden.
    cv::Ptr<cv::BackgroundSubtractor> background_subtractor_gpu;


    /*********************************************************** Öffentliche OpenCV-Variablen  **************************************************/
      #pragma region Öfffentliche OpenCV-Variablen
    uchar hue_min;
    uchar hue_max;
    uchar saturation_min;
    uchar saturation_max;
    uchar value_min;
    uchar value_max;

    int erosion_iterations;
    int dilation_iterations;
    int opening_iterations;
    int closing_iterations;
    int morph_iterations;

    int erosion_kernel_size;
    int dilation_kernel_size;
    int bilateral_kernel_size;
    int opening_kernel_size;
    int closing_kernel_size;
    int morph_kernel_size;
    int gaussian_kernel_size;

    int resize_width;
    int resize_height;

    int frame_width;
    int frame_height;

    double gaussian_sigma;
    int    Object_Size_min;
    int    Object_Size_max;


    float bilateral_sigma_color;
    float bilateral_sigma_spatial;

    bool erode_active;
    bool dilate_active;
    bool gaussian_active;
    bool morph_active;
    bool bilateral_active;

    bool show_contoured;

    bool idle;


      #pragma endregion

    /********************************************************* Öffentliche Klassenmethoden*******************************************************/
    public:

    void camera_thread ();

    /***************************Getter-Setter Funktionen*****************************/
    void set_calibration_parameter (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]);
    void get_calibration_parameter (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const;
    void get_camera_settings ();

    void         get_objectPosition_2D_Pixel (bool& Contour_Found, nmsp_posen::S_Positionsvektor& Vec_Object);
    cv::Mat*&    get_cpu_src_img ();
    void         set_cpu_src_img (cv::Mat* cpu_src_img);
    cv::Mat*&    get_cpu_temp ();
    void         set_cpu_temp (cv::Mat* cpu_temp);
    cv::Mat*&    get_cpu_masked_img ();
    void         set_cpu_masked_img (cv::Mat* cpu_masked_img);
    cv::Mat*&    get_cpu_hsv_filtered ();
    void         set_cpu_hsv_filtered (cv::Mat* cpu_hsv_filtered);
    cv::Mat*&    get_cpu_contoured ();
    void         set_cpu_contoured (cv::Mat* cpu_contoured);
    cv::Mat*&    get_cpu_undistorted ();
    void         set_cpu_undistorted (cv::Mat* cpu_undistorted);
    cv::Mat*&    get_cpu_cropped_img ();
    void         set_cpu_cropped_img (cv::Mat* cpu_cropped_img);
    cv::Mat*&    get_dist_coeffs ();
    void         set_dist_coeffs (cv::Mat* dist_coeffs);
    cv::Mat*&    get_intrinsic ();
    void         set_intrinsic (cv::Mat* intrinsic);
    int&         get_camera_id ();
    void         set_camera_id (int camera_id);
    bool&        is_thread_running ();
    void         set_thread_running (bool thread_running);
    bool&        is_filtering_active ();
    void         set_filtering_active (bool filtering_active);
    bool&        is_filtering_hsv_active ();
    void         set_filtering_hsv_active (bool filtering_hsv_active);
    bool&        is_filtering_bgr_active ();
    void         set_filtering_bgr_active (bool filtering_bgr_active);
    bool&        is_filtering_gray_active ();
    void         set_filtering_gray_active (bool filtering_gray_active);
    bool&        is_contours_active ();
    void         set_contours_active (bool contours_active);
    bool&        is_undistord_active ();
    void         set_undistord_active (bool undistord_active);
    bool&        is_contour_found ();
    void         set_contour_found (bool contour_found);
    bool&        is_image_prepared ();
    void         set_image_prepared (bool image_prepared);
    bool&        is_show_cropped_image ();
    void         set_show_cropped_image (bool show_cropped_image);
    int&         get_capture_api ();
    void         set_capture_api (int capture_api);
    int&         get_objekt_anzahl ();
    void         set_objekt_anzahl (int objekt_anzahl);
    int&         get_kontur_index ();
    void         set_kontur_index (int kontur_index);
    double&      get_max_moment_m00 ();
    void         set_max_moment_m00 (double max_moment_m00);
    double&      get_ist_x ();
    void         set_ist_x (double ist_x);
    double&      get_ist_y ();
    void         set_ist_y (double ist_y);
    double&      get_soll_x ();
    void         set_soll_x (double soll_x);
    double&      get_soll_y ();
    void         set_soll_y (double soll_y);
    double&      get_delta_x ();
    void         set_delta_x (double delta_x);
    double&      get_delta_y ();
    void         set_delta_y (double delta_y);
    double&      get_moment_0_ordnung ();
    void         set_moment_0_ordnung (double moment_0_ordnung);
    double&      get_moment_1_ordnung_x ();
    void         set_moment_1_ordnung_x (double moment_1_ordnung_x);
    double&      get_moment_1_ordnung_y ();
    void         set_moment_1_ordnung_y (double moment_1_ordnung_y);
    double&      get_schwerpunkt_x ();
    void         set_schwerpunkt_x (double schwerpunkt_x);
    double&      get_schwerpunkt_y ();
    void         set_schwerpunkt_y (double schwerpunkt_y);
    double&      get_mittelpunkt_x ();
    void         set_mittelpunkt_x (double mittelpunkt_x);
    double&      get_mittelpunkt_y ();
    void         set_mittelpunkt_y (double mittelpunkt_y);
    double&      get_x_kamera_ks ();
    void         set_x_kamera_ks (double kamera_ks);
    double&      get_y_kamera_ks ();
    void         set_y_kamera_ks (double kamera_ks);
    double&      get_cx ();
    void         set_cx (double cx);
    double&      get_cy ();
    void         set_cy (double cy);
    double&      get_fx ();
    void         set_fx (double fx);
    double&      get_fy ();
    void         set_fy (double fy);
    double&      get_f ();
    void         set_f (double f);
    double&      get_vec_object_abs ();
    void         set_vec_object_abs (double vec_object_abs);
    float&       get_radius ();
    void         set_radius (float radius);
    cv::Moments& get_image_moments ();
    void         set_image_moments (const cv::Moments& image_moments);
    cv::Point2f& get_center ();
    void         set_center (const cv::Point2f& center);
    std::string& get_s_x ();
    void         set_s_x (const std::string& cs);
    std::string& get_s_y ();
    void         set_s_y (const std::string& cs);
    std::string& get_delta_x_str ();
    void         set_delta_x_str (const std::string& delta_x_str);
    std::string& get_delta_y_str ();
    void         set_delta_y_str (const std::string& delta_y_str);
    cv::Rect&    get_rect_roi ();
    void         set_rect_roi (const cv::Rect& rect_roi);
    uchar&       get_hue_min ();
    void         set_hue_min (uchar hue_min);
    uchar&       get_hue_max ();
    void         set_hue_max (uchar hue_max);
    uchar&       get_saturation_min ();
    void         set_saturation_min (uchar saturation_min);
    uchar&       get_saturation_max ();
    void         set_saturation_max (uchar saturation_max);
    uchar&       get_value_min ();
    void         set_value_min (uchar value_min);
    uchar&       get_value_max ();
    void         set_value_max (uchar value_max);
    int&         get_erosion_iterations ();
    void         set_erosion_iterations (int erosion_iterations);
    int&         get_dilation_iterations ();
    void         set_dilation_iterations (int dilation_iterations);
    int&         get_opening_iterations ();
    void         set_opening_iterations (int opening_iterations);
    int&         get_closing_iterations ();
    void         set_closing_iterations (int closing_iterations);
    int&         get_morph_iterations ();
    void         set_morph_iterations (int morph_iterations);
    int&         get_erosion_kernel_size ();
    void         set_erosion_kernel_size (int erosion_kernel_size);
    int&         get_dilation_kernel_size ();
    void         set_dilation_kernel_size (int dilation_kernel_size);
    int&         get_bilateral_kernel_size ();
    void         set_bilateral_kernel_size (int bilateral_kernel_size);
    int&         get_opening_kernel_size ();
    void         set_opening_kernel_size (int opening_kernel_size);
    int&         get_closing_kernel_size ();
    void         set_closing_kernel_size (int closing_kernel_size);
    int&         get_morph_kernel_size ();
    void         set_morph_kernel_size (int morph_kernel_size);
    int&         get_gaussian_kernel_size ();
    void         set_gaussian_kernel_size (int gaussian_kernel_size);
    int&         get_resize_width ();
    void         set_resize_width (int resize_width);
    int&         get_resize_height ();
    void         set_resize_height (int resize_height);
    double&      get_gaussian_sigma ();
    void         set_gaussian_sigma (double gaussian_sigma);
    int&         get_object_size_min ();
    void         set_object_size_min (int object_size_min);
    int&         get_object_size_max ();
    void         set_object_size_max (int object_size_max);
    float&       get_bilateral_sigma_color ();
    void         set_bilateral_sigma_color (float bilateral_sigma_color);
    float&       get_bilateral_sigma_spatial ();
    void         set_bilateral_sigma_spatial (float bilateral_sigma_spatial);
    bool&        is_erode_active ();
    void         set_erode_active (bool erode_active);
    bool&        is_dilate_active ();
    void         set_dilate_active (bool dilate_active);
    bool&        is_gaussian_active ();
    void         set_gaussian_active (bool gaussian_active);
    bool&        is_morph_active ();
    void         set_morph_active (bool morph_active);
    bool&        is_bilateral_active ();
    void         set_bilateral_active (bool bilateral_active);
    bool& is_show_contoured_active();
    void set_show_contoured_active(bool show_contoured);
    bool&        is_idle ();
    void         set_idle (bool idle);


    void set_aspect_ratio (int Height, int width);
    void set_framerate (int framerate);

    void init_rectify_map ();
    void gpu_filter_background();
    void save_picture (int camera_id, int photo_id, std::string definition);
    void crop_image (cv::Mat* undistorted_img, cv::Mat* crop_undist_img);

    /******************************************************* Private Klassenmethoden***************************************************************/
    private:
    void init (int camera_id);
    void cpu_grab_frame (cv::Mat* cpu_dst_img);
    void apply_filter (cv::Mat* cpu_src, cv::Mat* cpu_dst);


    void gpu_erode (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, int borderType);
    void gpu_dilate (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void gpu_open (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void gpu_close (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

    void gpu_bilateral_filter (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void gpu_gaussian_filter (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void get_gaussian_kernel ();
    void gpu_morph_gradient (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

    void gpu_filter_hsv (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void gpu_filter_bgr (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
    void gpu_filter_gray (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

    void find_contours (cv::Mat* thresholded_source_image, cv::Mat* dst_contoured_image, int offset[2]);

    void undistord_img (cv::Mat* cpu_src, cv::Mat* cpu_dst);
    };
  }
