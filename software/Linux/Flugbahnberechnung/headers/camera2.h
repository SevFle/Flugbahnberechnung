#ifndef CAMERA2_H
#define CAMERA2_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>

#include "headers/GlobalObjects.h"
#include "headers/posen.h"


using namespace GlobalObjects;

namespace Camera
  {
  class C_Camera2
    {
  public:
    struct S_filterProperties
      {
      int   hue_min = 0;
      int   hue_max = 0;
      int   saturation_min = 0;
      int   saturation_max = 0;
      int   value_min = 0;
      int   value_max = 0;

      int     erosion_iterations = 0;
      int     dilation_iterations = 0;
      int     opening_iterations = 0;
      int     closing_iterations = 0;
      int     morph_iterations = 0;

      int     erosion_kernel_size = 0;
      int     dilation_kernel_size = 0;
      int     bilateral_kernel_size = 0;
      int     opening_kernel_size = 0;
      int     closing_kernel_size = 0;
      int     morph_kernel_size = 0;
      int     gaussian_kernel_size = 0;
      int     Object_Size_min = 0;
      int     Object_Size_max = 0;
      int     offset[2] = { 0, 0};
      double  gaussian_sigma = 0.0;

      float   bilateral_sigma_color = 0.0f;
      float   bilateral_sigma_spatial = 0.0f;

      bool    erode_active =  false;
      bool    dilate_active =  false;
      bool    gaussian_active =  false;
      bool    morph_active =  false;
      bool    bilateral_active =  false;


    public:
      S_filterProperties();
      ~S_filterProperties();
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
      int getOffset(int* offset) const;
      void setOffset(int arg1, int arg2);
      int getErodeIterations() const;
      void setErosion_iterations(int value);
      int getDilateIterations() const;
      void setDilation_iterations(int value);
      int getOpenIterations() const;
      void setOpening_iterations(int value);
      int getCloseIterations() const;
      void setClosing_iterations(int value);
      int getMorphIterations() const;
      void setMorph_iterations(int value);
      int getErodeKernelSize() const;
      void setErosion_kernel_size(int value);
      int getDilateKernelSize() const;
      void setDilation_kernel_size(int value);
      int getBilateralKernelSize() const;
      void setBilateral_kernel_size(int value);
      int getOpenKernelSize() const;
      void setOpening_kernel_size(int value);
      int getCloseKernelSize() const;
      void setClosing_kernel_size(int value);
      int getMorphKernelSize() const;
      void setMorph_kernel_size(int value);
      int getGaussianKernelSize() const;
      void setGaussian_kernel_size(int value);
      int getObject_Size_min() const;
      void setObject_Size_min(int value);
      int getObject_Size_max() const;
      void setObject_Size_max(int value);
      double getGaussianSigma() const;
      void setGaussian_sigma(double value);
      float getBilateralSigmaColor() const;
      void setBilateral_sigma_color(float value);
      float getBilateralSigmaSpatial() const;
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

  private:
    cv::VideoCapture*                 cap;
    cv::Mat*                          cpuSrc;
    cv::Rect*                         roi;
    cv::Mat*                          distCoeffs;
    cv::Mat*                          intrinsic;
    cv::cuda::GpuMat*                 gpuSrc;
    cv::cuda::GpuMat*                 xMap;
    cv::cuda::GpuMat*                 yMap;
    std::string*                       pipeline;
    int                               cameraID;
    int                               frameWidth;
    int                               frameHeight;


  public:
    C_AbsolutePose*                   cameraPose;
    S_filterProperties*               filterValues;
  public:
    bool open                         ();
    bool close                        ();
    bool grabImg                      ();
    bool retrieveImg                  (cv::Mat &dstImg);
    void readImage                     (cv::Mat &dstImg);
    void savePicture                  (int camera_id, int photo_id, std::string definition);
    void initRectifyMap               ();
    void save_picture                 (int photo_id, std::string definition, cv::Mat& srcImg);
  private:
    void fit_to_roi                   (int Radius, int istX, int istY);
    void initialize                   ();
    /********************************************** GETTER & SETTER METHODEN ******************************************************/
public:

    void setCalibrationParameter      (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]);
    void getCalibrationParameter      (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const;
    void setPipeline                  (std::string Pipeline);
    void setTrackingRoi               (int Radius, int istX, int istY);

    void setCameraID                  (int &cameraID);
    int  getCameraID                  () const;
    cv::Mat *getDistCoeffs            () const;
    void setDistCoeffs                (cv::Mat &value);

    cv::Mat *getIntrinsic             () const;
    void setIntrinsic                 (cv::Mat &value);

    C_AbsolutePose *getCameraPose() const;
    void setCameraPose(C_AbsolutePose *value);
    S_filterProperties *getFilterproperties() const;
    void setFilterproperties(S_filterProperties *value);
    cv::cuda::GpuMat *getXMap() const;
    void setXMap(cv::cuda::GpuMat *value);
    cv::cuda::GpuMat *getYMap() const;
    void setYMap(cv::cuda::GpuMat *value);
    void setRoi(cv::Rect *value);
    int getFrameWidth() const;
    void setFrameWidth(int value);
    int getFrameHeight() const;
    void setFrameHeight(int value);
    std::string getFPS() const;

    cv::Rect *getRoi() const;
  };

}


#endif // CAMERA2_H
