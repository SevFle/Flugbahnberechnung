#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

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
      cv::Mat                                 cpu_img;

      cv::cuda::GpuMat                        gpu_img;
      cv::cuda::GpuMat                        gpu_mid_img;
      cv::cuda::GpuMat                        gpu_src_img;
      cv::cuda::GpuMat                        gpu_dst_img;

      std::vector<cv::cuda::GpuMat>           gpu_src_vector;
      std::vector<cv::cuda::GpuMat>           gpu_mid_vector;
      std::vector<cv::cuda::GpuMat>           gpu_dst_vector;

      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      cv::VideoCapture                        cap;
      cv::Mat                                 cpu_src_img;
      cv::Mat                                 cpu_mid_img;
      cv::Mat                                 cpu_dst_img;
      cv::Mat                                 cpu_masked_img;
      cv::Mat                                 Mat2Bitmap;
      std::vector<cv::Mat>                    cpu_src_vector;
      std::vector<cv::Mat>                    cpu_mid_vector;
      std::vector<cv::Mat>                    cpu_dst_vector;
      std::vector<cv::Mat>                    cpu_masked_vector;

      std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>          camera_vector;
      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                     camera_id;
      int                                     capture_api;

      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      int                                     statemachine_state;




      /*********************************************************** Öffentliche OpenCV-Variablen  **************************************************/
      #pragma region Öfffentliche OpenCV-Variablen
      int                                     hue_min;
      int                                     hue_max;
      int                                     saturation_min;
      int                                     saturation_max;
      int                                     value_min;
      int                                     value_max;
      int                                     target_size_width;     //Resizing the image to the wanted width Values
      int                                     target_size_height;     //Resizing the image to the wanted height Values


      int                                     erosion_iterations;
      int                                     dilation_iterations;
      int                                     opening_iterations;
      int                                     closing_iterations;

      int                                     erosion_kernel_size;
      int                                     dilation_kernel_size;
      int                                     bilateral_kernel_size;
      int                                     opening_kernel_size;
      int                                     closing_kernel_size;
      int                                     morph_kernel_size;
      int                                     gaussian_kernel_size;
      int                                     ksize;

      int                                     bordertype;

      int                                     numBoards;
      int                                     numCornersHor;
      int                                     numcornersVer;

      double                                  gaussian_sigma;


      float                                   bilateral_sigma_color;
      float                                   bilateral_sigma_space;

      cv::Point                               anchor;

      #pragma endregion

      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:
      void            init                                                (int camera_id);
      void            create_videocapture_vector                          (int camera_id);
      void            create_img_vectors                                  ();
      void            cpu_grab_frame                                      (cv::Mat& cpu_dst_img);
      void            apply_filter                                        (cv::Mat  &cpu_src, cv::Mat &cpu_dst);
      void            cpu_mask_img                                        (cv::Mat& hsv_cpu_src, cv::Mat& cpu_masked_dst);
      void            cpu_img_show                                        (cv::Mat& processed_img, cv::Mat& original_img);

      void            camera_thread                                       ();
      /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void            gpu_to_hsv                                          (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst);
      void            gpu_to_hsv_threshold                                (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int hue_min, int hue_max, int saturation_min, int saturation_max, int value_min, int value_max);
      void            cpu_to_4channel_colour                              (cv::Mat& cpu_src, cv::Mat& cpu_dst);
      void            gpu_erode                                           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int borderType, cv::Point anchor, int erosion_iterations);
      void            gpu_dilate                                          (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int dilation_iterations);
      void            gpu_open                                            (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int opening_iterations);
      void            gpu_close                                           (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, cv::Point anchor, int closing_iterations);
      void            gpu_bilateral_filter                                (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int bilateral_kernel_size, float bilateral_sigma_color, float bilateral_sigma_spatial);
      void            gpu_gaussian_filter                                 (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int gaussian_kernel_size, double gaussian_sigma);
      void            cpu_find_contours                                   (cv::Mat& cpu_src, cv::Mat& cpu_dst);






    };

  }

