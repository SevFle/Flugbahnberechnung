#pragma once

#include <vector>
#include <opencv2/core/cuda.hpp>

/**** Vorwärtsdeklaration der unmanaged OpenCV Klassen ***************************/
namespace cv
  {
  class VideoCapture;
  class Mat;
    namespace cuda
    {
      GpuMat;
    }using namespace cuda;
  } using namespace cv;
/**** Vorwärtsdeklaration der unmanaged TBB Klassen ******************************/
namespace tbb
  {
  class pipeline;
  }using namespace tbb;



namespace nmsp_open_cv_unmanaged
  {
  class c_opencv_unmanaged
    {
      
      public:
/**** Konstruktor ****************************************************************/
      c_opencv_unmanaged ();
/**** Dekonstruktor **************************************************************/
      ~c_opencv_unmanaged ();
/**** Öffentliche Variablen  *****************************************************/
      #pragma region Öffentliche Variablen

      int                                     cameras_in_use;
      int                                     current_pipeline_camera_grab;

      volatile bool                           done;
      #pragma endregion 
/**** Öffentliche Klassenvariablen  **********************************************/
      int                                     camera_id;
/**** Öffentliche OpenCV-Variablen  **********************************************/
      #pragma region Öfffentliche OpenCV-Variablen
      int                                     hue_min,
                                              hue_max,
                                              saturation_min,
                                              saturation_max,
                                              value_min,
                                              value_max;

       int                                    target_size_x,     //Resizing the image to the wanted Values
                                              target_size_y;


      int                                     erosion_kernel_size,
                                              erosion_iterations,
                                              dilation_kernel_size,
                                              dilation_iterations;

      int                                     bilateral_kernel_size,
                                              gaussian_kernel_size,
                                              opening_kernel_size,
                                              closing_kernel_size,
                                              morph_kernel_size;

      double                                  gaussian_sigma;


      float                                   bilateral_sigma_color,
                                              bilateral_sigma_space;

      #pragma endregion
/**** Öffentliche OpenCV-Objekte  ************************************************/
      #pragma region  Öffentliche OpenCV-Objekte

      cv::Mat^                                original_frame,
                                              processed_frame,
                                              grabbed_frame;

      #pragma endregion


      private:
/**** Private OpenCV-Objekte  ****************************************************/
      #pragma region  Private OpenCV-Objekte

      cv::VideoCapture^                       camera_capture;
       
      cv::Mat^                                hsv_frame,
                                              gaussian_frame,
                                              bilateral_frame;

      cv::cuda::GpuMat^                       gpu_original_frame,
                                              gpu_processed_frame,
                                              gpu_HSV_frame,
                                              gpu_Gaussian_frame,
                                              gpu_Bilateral_frame,
                                              gpu_src_img,
                                              gpu_temp_img,
                                              gpu_dst_img;
      #pragma endregion 
/**** Private OpenCV-Variablen  **************************************************/
      #pragma region Private OpenCV-Variablen

      #pragma endregion
/**** Private Variablen  *********************************************************/
      #pragma region Variablen

      std::vector<cv::VideoCapture>           camera_vector;
      std::vector<std::vector<cv::Mat>>       camera_captured_vector;

      int                                     camera_vector_count;
      int                                     capture_api_;
      int                                     statemachine_state;
      #pragma endregion
/**** Private TBB-Objekte ********************************************************/
      #pragma region TBB-Objekte

      tbb::pipeline^                          pipeline;

      #pragma endregion



/**** Öffentliche Klassenmethoden*************************************************/
      #pragma region Öffentliche Klassenmethoden
      public:

      bool            apply_filter                                    (cv::Mat& cpu_src, cv::Mat& cpu_dst);
      bool            start_camera_thread                             ();
      bool            create_camera_vector                            ();
      bool            tbb_camera_pipeline                             (size_t ntoken);
      bool            create_camera_threads_objectcalibration         ();

      #pragma endregion

/**** Private Klassenmethoden*****************************************************/
      #pragma region Private Klassenmethoden
      private:

      bool            grab_frame                                      (cv::Mat& cpu_dst);
      bool            state_machine                                   ();


      void            push_to_gpu                                     (cv::Mat& src, cv::cuda::GpuMat& gpu_dst);
      void            pull_from_gpu                                   (cv::cuda::GpuMat& gpu_src, cv::Mat& dst);
      #pragma region Filtermethoden
      void            to_hsv                                          (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst);
      void            to_hsv_threshold                                (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& hue_min, int& hue_max, int& saturation_min, int& saturation_max, int& value_min, int& value_max);
      void            to_resize                                       (cv::Mat& cpu_src, cv::Mat& cpu_dst, int& size_x, int& size_y);
      void            erosion                                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& erosion_kernel_size, int& erosion_iterations);
      void            dilation                                        (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& dilation_kernel_size, int& dilation_iterations);

      void            opening                                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& opening_kernel_size);
      void            closing                                         (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& closing_kernel_size);
      void            bilateral                                       (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& bilateral_kernel_size, float& bilateral_sigma_color, float& bilateral_sigma_space);
      void            gaussian_bluring                                (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& gaussian_kernel_size, double& gaussian_sigma);

      void            find_contours                                   (cv::Mat& cpu_src, cv::Mat& cpu_dst);
      #pragma endregion
      #pragma endregion
    };// c_opencv_unmanaged
  }//nmsp_open_cv_unmanaged

