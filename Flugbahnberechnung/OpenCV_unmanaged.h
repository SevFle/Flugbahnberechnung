#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
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
      cv::cuda::GpuMat*                        gpu_gray;
      //HSV-Filtering
      cv::cuda::GpuMat*                        gpu_src2color;
      cv::cuda::GpuMat*                        gpu_color_threshold;
      cv::cuda::GpuMat*                        gpu_bgr_threshold;
      cv::cuda::GpuMat*                        gpu_temp;


      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      cv::VideoCapture*                        cap;
      cv::Mat*                                 cpu_temp;
      cv::Mat*                                 cpu_temp3;
      cv::Mat*                                 cpu_src_img;
      cv::Mat*                                 cpu_mid_img;
      cv::Mat*                                 cpu_masked_img;
      cv::Mat*                                 cpu_filtered;
      cv::Mat*                                 cpu_contoured;
      cv::Mat*                                 contoure_img;
      cv::Mat*                                 DistCoeffs;
      cv::Mat*                                 Intrinsic;



      //std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>          camera_vector;
      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                     camera_id;
      bool                                    thread_running;

      bool                                    filtering_active;
      bool                                    filtering_hsv_active;
      bool                                    filtering_bgr_active;
      bool                                    filtering_gray_active;
      bool                                    contours_active;


      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      int                                     statemachine_state;
      int                                     capture_api;



      /*********************************************************** Öffentliche OpenCV-Variablen  **************************************************/
      #pragma region Öfffentliche OpenCV-Variablen
      public:
      uchar                                     hue_min;
      uchar                                     hue_max;
      uchar                                     saturation_min;
      uchar                                     saturation_max;
      uchar                                     value_min;
      uchar                                     value_max;


      int                                     target_size_width;     //Resizing the image to the wanted width Values
      int                                     target_size_height;     //Resizing the image to the wanted height Values


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
      int                                     ksize;
      int                                     objekt_anzahl;

      int                                     bordertype;

      int                                     numBoards;
      int                                     numCornersHor;
      int                                     numcornersVer;

      double                                  gaussian_sigma;

      double                                  Vec_Object[3];
      double                                  max_Moment_m00;


      float                                   bilateral_sigma_color;
      float                                   bilateral_sigma_spatial;

      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hirarchy;

      bool  erode_active;
      bool  dilate_active;
      bool  open_active;
      bool  close_active;
      bool  gaussian_active;
      bool  morph_active;

      bool  contour_found;
      bool  idle;



      cv::Point                               anchor;


      #pragma endregion

      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:
      void            apply_filter                                        (cv::Mat  *cpu_src, cv::Mat *cpu_dst);
      void            cpu_mask_img                                        (cv::Mat* hsv_cpu_src, cv::Mat* cpu_masked_dst);

      void            camera_thread                                       ();

      /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void            init                                                (int camera_id);
      void            cpu_grab_frame                                      (cv::Mat* cpu_dst_img);

      void            gpu_to_hsv_threshold                                (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_inRange                                         (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Scalar minvalue, cv::Scalar maxvalue);

      void            gpu_erode                                           (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, int borderType, cv::Point anchor);
      void            gpu_dilate                                          (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Point anchor);
      void            gpu_open                                            (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst, cv::Point anchor);
      void            gpu_close                                           (cv::cuda::GpuMat* gpu_src,cv::cuda::GpuMat* gpu_dst, cv::Point anchor);

      void            gpu_bilateral_filter                                (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_gaussian_filter                                 (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_morph_gradient                                  (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

      void            gpu_filter_hsv                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_filter_bgr                                      (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);
      void            gpu_filter_gray                                     (cv::cuda::GpuMat* gpu_src, cv::cuda::GpuMat* gpu_dst);

      void            find_contours                                       (cv::Mat* thresholded_source_image, cv::Mat* dst_contoured_image);






    };

  }

