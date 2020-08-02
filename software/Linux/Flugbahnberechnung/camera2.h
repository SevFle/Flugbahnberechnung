#ifndef CAMERA2_H
#define CAMERA2_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>

#include "headers/GlobalObjects.h"


using namespace GlobalObjects;

namespace Camera
  {
  class C_Camera2
    {
    public:
    C_Camera2();
    ~C_Camera2();

    C_GlobalObjects* GlobalObjects;


    cv::VideoCapture* cap;
    cv::Mat* CpuSrc;
    cv::Mat* DistCoeffs;
    cv::Mat* Intrinsic;

    cv::cuda::GpuMat* GpuSrc;
    cv::cuda::GpuMat* map1;
    cv::cuda::GpuMat* map2;

    std::string Pipeline;

    int cameraID;


    bool open                         ();
    bool close                        ();
    void savePicture                  (int camera_id, int photo_id, std::string definition);
    void initRectifyMap               ();

    void setCalibrationParameter      (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]);
    void getCalibrationParameter      (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const;
    void setPipeline                  (std::string Pipeline);
    void setROI                       (int &width, int &height);
    int  getROI                       ();
    void setCameraID                  (int &cameraID);
    int  getCameraID                  ();
    };

  }


#endif // CAMERA2_H
