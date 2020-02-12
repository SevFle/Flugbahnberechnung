#pragma unmanaged
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <msclr/marshal_cppstd.h>

#include <tbb/concurrent_queue.h>
#include <tbb/pipeline.h>
#include <tbb/tbb.h>

#include <vector>

namespace nmsp_open_cv_unmanaged
  {
  class C_opencv_unmanaged
    {
      public:
      C_opencv_unmanaged();

      ~C_opencv_unmanaged();



      struct ProcessingChainData
        {
        cv::Mat img;
        std::vector<cv::Rect> faces, faces2;
        cv::Mat gray, smallImg;
        };
      
      int                   camera_id;
      int                   hue_min;
      int                   hue_max;
      int                   saturation_min;
      int                   saturation_max;
      int                   value_min;
      int                   value_max;

      int                   target_size_x;     //Resizing the image to the wanted Values
      int                   target_size_y;


      int                   erosion_kernel_size;
      int                   erosion_iterations;
      int                   dilation_kernel_size;
      int                   dilation_iterations;

      int                   bilateral_kernel_size;
      float                 bilateral_sigma_color;
      float                 bilateral_sigma_space;
      int                   gaussian_kernel_size;
      double                gaussian_sigma;
      int                   opening_kernel_size;
      int                   closing_kernel_size;
      int                   morph_kernel_size;
      int                   Cameras_in_use;
      int                   current_pipeline_camera_grab;
      int                   statemachine_state;

      cv::Mat                original_frame;
      cv::Mat                processed_frame;
      cv::Mat               grabbed_frame;

      volatile bool         done;

    private:
      cv::Mat                hsv_frame;
      cv::Mat                gaussian_frame;
      cv::Mat                bilateral_frame;

      cv::cuda::GpuMat       gpu_original_frame;
      cv::cuda::GpuMat       gpu_processed_frame;
      cv::cuda::GpuMat       gpu_HSV_frame;
      cv::cuda::GpuMat       gpu_Gaussian_frame;
      cv::cuda::GpuMat       gpu_Bilateral_frame;
      cv::cuda::GpuMat       gpu_src_img;
      cv::cuda::GpuMat       gpu_temp_img;
      cv::cuda::GpuMat       gpu_dst_img;

      cv::VideoCapture       camera_capture;
      std::vector<cv::VideoCapture> camera_vector;
      std::vector<std::vector<cv::Mat>> camera_captured_vector;

      int                    camera_vector_count;
      int                    capture_api_;



      tbb::pipeline pipeline;


      public:
      bool  apply_filter          (cv::Mat& cpu_src, cv::Mat& cpu_dst);
      bool start_camera_thread    ();
      bool create_camera_vector   ();
      bool create_camera_threads_objectcalibration();
      bool state_machine          ();


      private:
      bool  grab_frame            (cv::Mat& cpu_dst);
      void  push_to_gpu           (cv::Mat& src, cv::cuda::GpuMat& gpu_dst);
      void  pull_from_gpu         (cv::cuda::GpuMat& gpu_src, cv::Mat& dst);


      void  to_hsv                (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst);
      void  to_hsv_threshold      (cv::cuda::GpuMat& img, cv::cuda::GpuMat& gpu_dst, int& hue_min, int& hue_max, int& saturation_min, int& saturation_max, int& value_min, int& value_max);
      void  to_resize             (cv::Mat& cpu_src, cv::Mat& cpu_dst, int& size_x, int& size_y);
      void  erosion               (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& erosion_kernel_size, int& erosion_iterations);
      void  dilation              (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& dilation_kernel_size, int& dilation_iterations);

      void  opening               (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& opening_kernel_size);
      void  closing               (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& closing_kernel_size);
      void  bilateral             (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& bilateral_kernel_size, float& bilateral_sigma_color, float& bilateral_sigma_space);
      void  gaussian_bluring      (cv::cuda::GpuMat& gpu_src, cv::cuda::GpuMat& gpu_dst, int& gaussian_kernel_size, double& gaussian_sigma);

      void  find_contours         (cv::Mat& cpu_src, cv::Mat& cpu_dst);



    };

  }

