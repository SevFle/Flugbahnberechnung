#include "camera2.h"

using namespace Camera;

C_Camera2::C_Camera2                        ()
  {
  auto cap = new cv::Mat;
  auto cpuSrc = new cv::Mat;
  auto DistCoeffs = new cv::Mat;
  auto Intrinsic = new cv::Mat;
  auto gpuSrc = new cv::cuda::GpuMat;
  auto map1 = new cv::cuda::GpuMat;
  auto map2 = new cv::cuda::GpuMat;
  auto CameraPose = new posen::C_AbsolutePose;
  }
C_Camera2::~C_Camera2                       ()
  {
  delete (CameraPose);
  delete (map1);
  delete (map2);
  delete (GpuSrc);
  delete (Intrinsic);
  delete (DistCoeffs);
  delete (CpuSrc);
  delete (cap);
  }


bool C_Camera2::open                        ()
  {
  this->cap->open(Pipeline, cv::CAP_GSTREAMER);
  if(!this->cap->isOpened()) return false;
  else return true;
  }
bool C_Camera2::close                       ()
  {
  this->cap->release();
  if(!this->cap->isOpened()) return true;
  else return false;
  }
void C_Camera2::savePicture                 (int camera_id, int photo_id, std::string definition)
  {
  imwrite (definition + std::to_string (camera_id) + "_Snapshot_" + std::to_string (photo_id) + ".png",*CpuSrc);
  }
void C_Camera2::initRectifyMap              ()
  {
  cv::Mat cpu_map1;
  cv::Mat cpu_map2;
  initUndistortRectifyMap (*Intrinsic,*DistCoeffs,cv::Mat(),*Intrinsic,cv::Size (CpuSrc->cols,CpuSrc->rows), CV_32FC1,cpu_map1,cpu_map2);

  this->map1->upload (cpu_map1);
  this->map2->upload (cpu_map2);

  }

void C_Camera2::setCalibrationParameter     (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3])
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
void C_Camera2::getCalibrationParameter     (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const
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

void C_Camera2::setPipeline                 (std::string Pipeline)
  {
  this->Pipeline = Pipeline;
  }
void C_Camera2::setROI                      (int &width, int &height)
  {

  }
int  C_Camera2::getROI                      ()
  {

  }
void C_Camera2::setCameraID                 (int &cameraID)
  {

  }
int  C_Camera2::getCameraID                 ()
  {
  return this->cameraID;
  }

cv::Mat *C_Camera2::getDistCoeffs                         () const
  {
  return DistCoeffs;
  }
void C_Camera2::setDistCoeffs                             (cv::Mat &value)
  {
  DistCoeffs = value;
  }

cv::Mat *C_Camera2::getIntrinsic                          () const
  {
  return Intrinsic;
  }
void C_Camera2::setIntrinsic                              (cv::Mat &value)
  {
  Intrinsic = value;
  }

uchar C_Camera2::S_filterProperties::getHue_min           () const
  {
  return hue_min;
  }
void C_Camera2::S_filterProperties::setHue_min            (const uchar &value)
  {
  hue_min = value;
  }

uchar C_Camera2::S_filterProperties::getHue_max           () const
  {
  return hue_max;
  }
void C_Camera2::S_filterProperties::setHue_max            (const uchar &value)
  {
  hue_max = value;
  }

uchar C_Camera2::S_filterProperties::getSaturation_min    () const
  {
  return saturation_min;
  }
void C_Camera2::S_filterProperties::setSaturation_min     (const uchar &value)
  {
  saturation_min = value;
  }

uchar C_Camera2::S_filterProperties::getSaturation_max    () const
  {
  return saturation_max;
  }
void C_Camera2::S_filterProperties::setSaturation_max     (const uchar &value)
  {
  saturation_max = value;
  }

uchar C_Camera2::S_filterProperties::getValue_min() const
  {
  return value_min;
  }
void C_Camera2::S_filterProperties::setValue_min(const uchar &value)
  {
  value_min = value;
  }

uchar C_Camera2::S_filterProperties::getValue_max() const
  {
  return value_max;
  }
void C_Camera2::S_filterProperties::setValue_max(const uchar &value)
  {
  value_max = value;
  }

int C_Camera2::S_filterProperties::getErosion_iterations() const
  {
  return erosion_iterations;
  }
void C_Camera2::S_filterProperties::setErosion_iterations(int value)
  {
  erosion_iterations = value;
  }

int C_Camera2::S_filterProperties::getDilation_iterations() const
  {
  return dilation_iterations;
  }
void C_Camera2::S_filterProperties::setDilation_iterations(int value)
  {
  dilation_iterations = value;
  }

int C_Camera2::S_filterProperties::getOpening_iterations() const
  {
  return opening_iterations;
  }
void C_Camera2::S_filterProperties::setOpening_iterations(int value)
  {
  opening_iterations = value;
  }

int C_Camera2::S_filterProperties::getClosing_iterations() const
  {
  return closing_iterations;
  }
void C_Camera2::S_filterProperties::setClosing_iterations(int value)
  {
  closing_iterations = value;
  }

int C_Camera2::S_filterProperties::getMorph_iterations() const
  {
  return morph_iterations;
  }
void C_Camera2::S_filterProperties::setMorph_iterations(int value)
  {
  morph_iterations = value;
  }

int C_Camera2::S_filterProperties::getErosion_kernel_size() const
  {
  return erosion_kernel_size;
  }
void C_Camera2::S_filterProperties::setErosion_kernel_size(int value)
  {
  erosion_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getDilation_kernel_size() const
  {
  return dilation_kernel_size;
  }
void C_Camera2::S_filterProperties::setDilation_kernel_size(int value)
  {
  dilation_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getBilateral_kernel_size() const
  {
  return bilateral_kernel_size;
  }
void C_Camera2::S_filterProperties::setBilateral_kernel_size(int value)
  {
  bilateral_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getOpening_kernel_size() const
  {
  return opening_kernel_size;
  }
void C_Camera2::S_filterProperties::setOpening_kernel_size(int value)
  {
  opening_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getClosing_kernel_size() const
  {
  return closing_kernel_size;
  }
void C_Camera2::S_filterProperties::setClosing_kernel_size(int value)
  {
  closing_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getMorph_kernel_size() const
  {
  return morph_kernel_size;
  }
void C_Camera2::S_filterProperties::setMorph_kernel_size(int value)
  {
  morph_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getGaussian_kernel_size() const
  {
  return gaussian_kernel_size;
  }
void C_Camera2::S_filterProperties::setGaussian_kernel_size(int value)
  {
  gaussian_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getObject_Size_min() const
  {
  return Object_Size_min;
  }
void C_Camera2::S_filterProperties::setObject_Size_min(int value)
  {
  Object_Size_min = value;
  }

int C_Camera2::S_filterProperties::getObject_Size_max() const
  {
  return Object_Size_max;
  }
void C_Camera2::S_filterProperties::setObject_Size_max(int value)
  {
  Object_Size_max = value;
  }

double C_Camera2::S_filterProperties::getGaussian_sigma() const
  {
  return gaussian_sigma;
  }
void C_Camera2::S_filterProperties::setGaussian_sigma(double value)
  {
  gaussian_sigma = value;
  }

float C_Camera2::S_filterProperties::getBilateral_sigma_color() const
  {
  return bilateral_sigma_color;
  }
void C_Camera2::S_filterProperties::setBilateral_sigma_color(float value)
  {
  bilateral_sigma_color = value;
  }

float C_Camera2::S_filterProperties::getBilateral_sigma_spatial() const
  {
  return bilateral_sigma_spatial;
  }
void C_Camera2::S_filterProperties::setBilateral_sigma_spatial(float value)
  {
  bilateral_sigma_spatial = value;
  }

bool C_Camera2::S_filterProperties::getErode_active() const
  {
  return erode_active;
  }
void C_Camera2::S_filterProperties::setErode_active(bool value)
  {
  erode_active = value;
  }

bool C_Camera2::S_filterProperties::getDilate_active() const
  {
  return dilate_active;
  }
void C_Camera2::S_filterProperties::setDilate_active(bool value)
  {
  dilate_active = value;
  }

bool C_Camera2::S_filterProperties::getGaussian_active() const
  {
  return gaussian_active;
  }
void C_Camera2::S_filterProperties::setGaussian_active(bool value)
  {
  gaussian_active = value;
  }

bool C_Camera2::S_filterProperties::getMorph_active() const
  {
  return morph_active;
  }
void C_Camera2::S_filterProperties::setMorph_active(bool value)
  {
  morph_active = value;
  }

bool C_Camera2::S_filterProperties::getBilateral_active() const
  {
  return bilateral_active;
  }
void C_Camera2::S_filterProperties::setBilateral_active(bool value)
  {
  bilateral_active = value;
  }

C_AbsolutePose *C_Camera2::getCameraPose() const
  {
  return CameraPose;
  }

void C_Camera2::setCameraPose(C_AbsolutePose *value)
  {
  CameraPose = value;
  }

