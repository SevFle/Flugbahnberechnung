#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//#include <ipp.h>
#include "CudaKernels.cuh"


namespace nmsp_opencv_unmanaged
  {
  class c_opencv_unmanaged
    {
      public:
      /*************************************************************** Konstruktoren *************************************************************/
      c_opencv_unmanaged                      (int camera_id);
      /*************************************************************** Destruktor ****************************************************************/
      ~c_opencv_unmanaged                     ();
      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      cv::cuda::GpuMat*                        gpu_src_img;
      cv::cuda::GpuMat*                        gpu_thresholded;
      cv::cuda::GpuMat*                        gpu_filtered;


      //HSV-Filtering
      cv::cuda::GpuMat*                        gpu_src2color;
      cv::cuda::GpuMat*                        gpu_color_threshold;
      cv::cuda::GpuMat*                        gpu_bgr_threshold;
      cv::cuda::GpuMat*                        gpu_temp;


      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      cv::VideoCapture*                        cap;
      cv::Mat*                                 cpu_src_img;
      cv::Mat*                                 cpu_masked_img;
      cv::Mat*                                 cpu_filtered;
      cv::Mat*                                 cpu_contoured;
      cv::Mat*                                 cpu_undistorted;
      cv::Mat*                                 DistCoeffs;
      cv::Mat*                                 Intrinsic;



      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                     camera_id;
      bool                                    thread_running;

      bool                                    filtering_active;
      bool                                    filtering_hsv_active;
      bool                                    filtering_bgr_active;
      bool                                    filtering_gray_active;
      bool                                    contours_active;
      bool                                    undistord_active;


      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      int                                     statemachine_state;
      int                                     capture_api;

      

      /*********************************************************** Öffentliche OpenCV-Variablen  **************************************************/
      #pragma region Öfffentliche OpenCV-Variablen
      public:
      uchar                                   hue_min;
      uchar                                   hue_max;
      uchar                                   saturation_min;
      uchar                                   saturation_max;
      uchar                                   value_min;
      uchar                                   value_max;

      int                                     erosion_iterations;
      int                                     dilation_iterations;
      int                                     opening_iterations;
      int                                     closing_iterations;
      int                                     morph_iterations;

      int                                     erosion_kernel_size;
      int                                     dilation_kernel_size;
      int                                     bilateral_kernel_size;
      int                                     opening_kernel_size;
      int                                     closing_kernel_size;
      int                                     morph_kernel_size;
      int                                     gaussian_kernel_size;

      double                                  gaussian_sigma;



      float                                   bilateral_sigma_color;
      float                                   bilateral_sigma_spatial;


      bool                                    erode_active;
      bool                                    dilate_active;
      bool                                    gaussian_active;
      bool                                    morph_active;

      bool                                    idle;




      #pragma endregion

      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:

      void            camera_thread                                       ();


      void            set_calibration_parameter                           (double           (&DistCoeffs)[1][5], double  (&Intrinsic)[3][3]);
      void            get_calibration_parameter                           (double           (&DistCoeffs)[1][5], double  (&Intrinsic)[3][3]) const;
      void            set_aspect_ratio                                    (int              Height,   int width);
      void            set_framerate                                       (int              framerate);


      /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void            init                                                (int              camera_id);
      void            cpu_grab_frame                                      (cv::Mat*         cpu_dst_img);
      void            apply_filter                                        (cv::Mat*         cpu_src, cv::Mat *cpu_dst);


      void            gpu_erode                                           (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, int borderType);
      void            gpu_dilate                                          (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_open                                            (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_close                                           (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

      void            gpu_bilateral_filter                                (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_gaussian_filter                                 (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_morph_gradient                                  (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

      void            gpu_filter_hsv                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_filter_bgr                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_filter_gray                                     (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

      void            find_contours                                       (cv::Mat* thresholded_source_image, cv::Mat* dst_contoured_image); 
      void            undistord_img                                       (cv::Mat* cpu_src, cv::Mat* cpu_dst);







    };

  }

