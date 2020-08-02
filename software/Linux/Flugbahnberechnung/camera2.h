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

    struct S_filterProperties
      {
      uchar   hue_min;
      uchar   hue_max;
      uchar   saturation_min;
      uchar   saturation_max;
      uchar   value_min;
      uchar   value_max;

      int     erosion_iterations;
      int     dilation_iterations;
      int     opening_iterations;
      int     closing_iterations;
      int     morph_iterations;

      int     erosion_kernel_size;
      int     dilation_kernel_size;
      int     bilateral_kernel_size;
      int     opening_kernel_size;
      int     closing_kernel_size;
      int     morph_kernel_size;
      int     gaussian_kernel_size;
      int     Object_Size_min;
      int     Object_Size_max;
      double  gaussian_sigma;

      float   bilateral_sigma_color;
      float   bilateral_sigma_spatial;

      bool    erode_active;
      bool    dilate_active;
      bool    gaussian_active;
      bool    morph_active;
      bool    bilateral_active;


    public:
      uchar getHue_min() const;
      void setHue_min(const uchar &value);
      uchar getHue_max() const;
      void setHue_max(const uchar &value);
      uchar getSaturation_min() const;
      void setSaturation_min(const uchar &value);
      uchar getSaturation_max() const;
      void setSaturation_max(const uchar &value);
      uchar getValue_min() const;
      void setValue_min(const uchar &value);
      uchar getValue_max() const;
      void setValue_max(const uchar &value);
      int getErosion_iterations() const;
      void setErosion_iterations(int value);
      int getDilation_iterations() const;
      void setDilation_iterations(int value);
      int getOpening_iterations() const;
      void setOpening_iterations(int value);
      int getClosing_iterations() const;
      void setClosing_iterations(int value);
      int getMorph_iterations() const;
      void setMorph_iterations(int value);
      int getErosion_kernel_size() const;
      void setErosion_kernel_size(int value);
      int getDilation_kernel_size() const;
      void setDilation_kernel_size(int value);
      int getBilateral_kernel_size() const;
      void setBilateral_kernel_size(int value);
      int getOpening_kernel_size() const;
      void setOpening_kernel_size(int value);
      int getClosing_kernel_size() const;
      void setClosing_kernel_size(int value);
      int getMorph_kernel_size() const;
      void setMorph_kernel_size(int value);
      int getGaussian_kernel_size() const;
      void setGaussian_kernel_size(int value);
      int getObject_Size_min() const;
      void setObject_Size_min(int value);
      int getObject_Size_max() const;
      void setObject_Size_max(int value);
      double getGaussian_sigma() const;
      void setGaussian_sigma(double value);
      float getBilateral_sigma_color() const;
      void setBilateral_sigma_color(float value);
      float getBilateral_sigma_spatial() const;
      void setBilateral_sigma_spatial(float value);
      bool getErode_active() const;
      void setErode_active(bool value);
      bool getDilate_active() const;
      void setDilate_active(bool value);
      bool getGaussian_active() const;
      void setGaussian_active(bool value);
      bool getMorph_active() const;
      void setMorph_active(bool value);
      bool getBilateral_active() const;
      void setBilateral_active(bool value);
      };

  public:
    C_Camera2();
    ~C_Camera2();

    C_GlobalObjects* GlobalObjects;
    S_filterProperties* Filterproperties;


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
