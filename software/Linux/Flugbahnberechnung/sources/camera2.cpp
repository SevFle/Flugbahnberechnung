#include "headers/camera2.h"

using namespace Camera;

C_Camera2::C_Camera2                        ()
  {
  this->cap           = new cv::VideoCapture;
  this->cpuSrc        = new cv::Mat;
  this->distCoeffs    = new cv::Mat(cv::Mat_<double>(1,5));//new Mat(1, 5, CV_64F);
  this->intrinsic     = new cv::Mat(cv::Mat_<double>(3,3));//new Mat(3, 3, CV_32FC1);;
  this->roi           = new cv::Rect;
  this->gpuSrc        = new cv::cuda::GpuMat;
  this->xMap          = new cv::cuda::GpuMat(CV_32FC1);
  this->yMap          = new cv::cuda::GpuMat(CV_32FC1);
  this->cameraPose    = new posen::C_AbsolutePose;
  this->filterValues  = new C_Camera2::S_filterProperties;
  }
C_Camera2::~C_Camera2                       ()
  {
  delete (filterValues);
  delete (cameraPose);
  delete (xMap);
  delete (yMap);
  delete (gpuSrc);
  delete (intrinsic);
  delete (distCoeffs);
  delete (cpuSrc);
  delete (cap);
    }
std::string C_Camera2::getFPS() const
{
   std::string fps;
   fps = std::to_string(this->cap->get(cv::CAP_PROP_FPS));
   return fps;
}

int C_Camera2::getFrameHeight() const
    {
    return frameHeight;
    }

void C_Camera2::setFrameHeight(int value)
    {
    frameHeight = value;
    }

int C_Camera2::getFrameWidth() const
    {
    return frameWidth;
    }

void C_Camera2::setFrameWidth(int value)
    {
    frameWidth = value;
    }


bool C_Camera2::open                        ()
    {
    this->cap->open(pipeline, cv::CAP_GSTREAMER);
    this->initialize();
    if(!this->cap->isOpened()) return false;
    else return true;
    }
bool C_Camera2::close                       ()
  {
  this->cap->release();
  if(!this->cap->isOpened()) return true;
  else return false;
  }
void C_Camera2::initialize                  ()
  {
  this->cap->set(cv::CAP_PROP_BUFFERSIZE, 20);
  this->frameWidth = cap->get(cv::CAP_PROP_FRAME_WIDTH);
  this->frameHeight = cap->get(cv::CAP_PROP_FRAME_HEIGHT);
  this->roi->x = 1;
  this->roi->y = 1;
  this->roi->height = frameHeight-1;
  this->roi->width = frameWidth-1;
  }
void C_Camera2::initRectifyMap              ()
  {
  cv::Mat cpuXMap;
  cv::Mat cpuYMap;
  initUndistortRectifyMap (*intrinsic,*distCoeffs,cv::Mat(),*intrinsic,cv::Size (frameWidth,frameHeight), CV_32FC1,cpuXMap,cpuYMap);

  this->xMap->upload (cpuXMap);
  this->yMap->upload (cpuYMap);

  }
void C_Camera2::retrieveImg                      (cv::Mat &dstImg)
  {
  //auto cpuSrc = new cv::Mat;
  //this->cap->retrieve(*cpuSrc);
  //dstImg= cpuSrc->operator()(*roi);
  //cpuSrc->copyTo(dstImg);
  //delete (cpuSrc);
  this->cap->retrieve(dstImg, 0);
//dstImg= cpuSrc->operator()(*roi);
}

bool C_Camera2::grabImg                      ()
  {
  if(this->cap->grab()) return true;
  return false;
  }
void C_Camera2::readImage(cv::Mat &dstImg)
{
    this->cap->read(dstImg);
}
void C_Camera2::fit_to_roi(int Radius, int istX, int istY)
  {
    this->filterValues->offset[0] = istX-Radius*2;
    this->filterValues->offset[1] = istY-Radius*2;

    int breite = Radius*4;
    int hoehe = Radius*4;

    if ((this->filterValues->offset[0] >= 0 && this->filterValues->offset[1] >= 0) && (
         this->filterValues->offset[0]+breite <= this->frameWidth && this->filterValues->offset[1] + hoehe <= this->frameHeight ))
      {
      this->roi->x = this->filterValues->offset[0];
      this->roi->y = this->filterValues->offset[1];

      this->roi->width = Radius*4;
      this->roi->height = Radius*4;
      }
    else
      {
      this->filterValues->offset[0] = 0;
      this->filterValues->offset[1] = 0;

      this->roi->x = 0;
      this->roi->y = 0;

      this->roi->width =   this->frameWidth;
      this->roi->height =  this->frameHeight;

      }
   }
void C_Camera2::setCalibrationParameter     (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3])
{
for (int i = 0; i < 1; i++)
  {
  for (int j = 0; j < 5; j++)
    {
    this->distCoeffs->at<double> (i,j) = DistCoeffs[i][j];
    }
  }

for (int i = 0; i < 3; i++)
  {
  for (int j = 0; j < 3; j++)
    {
    this->intrinsic->at<double> (i,j) = Intrinsic[i][j];
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
    DistCoeffs[i][j] = this->distCoeffs->at<double> (i,j);
    }
  }

for (int i = 0; i < 3; i++)
  {
  for (int j = 0; j < 3; j++)
    {
    Intrinsic[i][j] = this->intrinsic->at<double> (i,j);
    }
  }
}

void C_Camera2::setPipeline                 (std::string Pipeline)
  {
  this->pipeline = Pipeline;
  }
void C_Camera2::setROI                      (int Radius, int istX, int istY)
  {
  this->fit_to_roi( Radius,  istX,  istY);
  }
int  C_Camera2::getROI() const
  {

  }
void C_Camera2::setCameraID                 (int &cameraID)
  {
  this->cameraID = cameraID;
  }
int  C_Camera2::getCameraID                 () const
  {
  return this->cameraID;
  }

void C_Camera2::save_picture (int photo_id, std::string definition, cv::Mat& srcImg)
  {
  cv::imwrite (definition + std::to_string (this->cameraID) + "_Snapshot_" + std::to_string (photo_id) + ".png",srcImg);
  }

/********************************************** GETTER & SETTER METHODEN ******************************************************/

cv::Rect *C_Camera2::getRoi() const
  {
  return roi;
  }

void C_Camera2::setRoi(cv::Rect *value)
  {
  roi = value;
  }

cv::cuda::GpuMat *C_Camera2::getYMap() const
  {
  return yMap;
  }

void C_Camera2::setYMap(cv::cuda::GpuMat *value)
    {
    yMap = value;
    }

cv::cuda::GpuMat *C_Camera2::getXMap() const
    {
    return xMap;
    }

void C_Camera2::setXMap(cv::cuda::GpuMat *value)
    {
    xMap = value;
    }


C_Camera2::S_filterProperties::S_filterProperties()
  {
  this->hue_min = 0;
  this->hue_max= 255;
  this->saturation_min= 0;
  this->saturation_max= 255;
  this->value_min= 0;
  this->value_max= 255;

  this->erosion_iterations= 1;
  this->dilation_iterations= 1;
  this->opening_iterations= 1;
  this->closing_iterations= 1;
  this->morph_iterations= 1;

  this->erosion_kernel_size= 1;
  this->dilation_kernel_size= 1;
  this->bilateral_kernel_size= 1;
  this->opening_kernel_size= 1;
  this->closing_kernel_size= 1;
  this->morph_kernel_size= 1;
  this->gaussian_kernel_size= 1;
  this->Object_Size_min= 0;
  this->Object_Size_max= 10000;
  this->offset[0]= 0;
  this->offset[1]= 0;

  this->gaussian_sigma= 1;

  this->bilateral_sigma_color= 1;
  this->bilateral_sigma_spatial= 1;

  this->erode_active= false;
  this->dilate_active= false;
  this->gaussian_active= false;
  this->morph_active= false;
  this->bilateral_active= false;

  }
C_Camera2::S_filterProperties::~S_filterProperties()
  {

  }

C_Camera2::S_filterProperties *C_Camera2::getFilterproperties() const
    {
    return this->filterValues;
    }

void C_Camera2::setFilterproperties(S_filterProperties *value)
    {
    filterValues = value;
    }
cv::Mat *C_Camera2::getDistCoeffs                         () const
  {
  return distCoeffs;
  }
void C_Camera2::setDistCoeffs                             (cv::Mat &value)
  {
  *distCoeffs = value;
  }

cv::Mat *C_Camera2::getIntrinsic                          () const
  {
  return intrinsic;
  }
void C_Camera2::setIntrinsic                              (cv::Mat &value)
  {
  *intrinsic = value;
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
int C_Camera2::S_filterProperties::getOffset(int* offset) const
  {
  offset[0] = this->offset[0];
  offset[1] = this->offset[1];
  };
void C_Camera2::S_filterProperties::setOffset(int arg1, int arg2)
  {
  this->offset[0] = arg1;
  this->offset[1] = arg2;
  }
int C_Camera2::S_filterProperties::getErodeIterations() const
  {
  return erosion_iterations;
  }
void C_Camera2::S_filterProperties::setErosion_iterations(int value)
  {
  erosion_iterations = value;
  }

int C_Camera2::S_filterProperties::getDilateIterations() const
  {
  return dilation_iterations;
  }
void C_Camera2::S_filterProperties::setDilation_iterations(int value)
  {
  dilation_iterations = value;
  }

int C_Camera2::S_filterProperties::getOpenIterations() const
  {
  return opening_iterations;
  }
void C_Camera2::S_filterProperties::setOpening_iterations(int value)
  {
  opening_iterations = value;
  }

int C_Camera2::S_filterProperties::getCloseIterations() const
  {
  return closing_iterations;
  }
void C_Camera2::S_filterProperties::setClosing_iterations(int value)
  {
  closing_iterations = value;
  }

int C_Camera2::S_filterProperties::getMorphIterations() const
  {
  return morph_iterations;
  }
void C_Camera2::S_filterProperties::setMorph_iterations(int value)
  {
  morph_iterations = value;
  }

int C_Camera2::S_filterProperties::getErodeKernelSize() const
  {
  return erosion_kernel_size;
  }
void C_Camera2::S_filterProperties::setErosion_kernel_size(int value)
  {
  erosion_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getDilateKernelSize() const
  {
  return dilation_kernel_size;
  }
void C_Camera2::S_filterProperties::setDilation_kernel_size(int value)
  {
  dilation_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getBilateralKernelSize() const
  {
  return bilateral_kernel_size;
  }
void C_Camera2::S_filterProperties::setBilateral_kernel_size(int value)
  {
  bilateral_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getOpenKernelSize() const
  {
  return opening_kernel_size;
  }
void C_Camera2::S_filterProperties::setOpening_kernel_size(int value)
  {
  opening_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getCloseKernelSize() const
  {
  return closing_kernel_size;
  }
void C_Camera2::S_filterProperties::setClosing_kernel_size(int value)
  {
  closing_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getMorphKernelSize() const
  {
  return morph_kernel_size;
  }
void C_Camera2::S_filterProperties::setMorph_kernel_size(int value)
  {
  morph_kernel_size = value;
  }

int C_Camera2::S_filterProperties::getGaussianKernelSize() const
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

double C_Camera2::S_filterProperties::getGaussianSigma() const
  {
  return gaussian_sigma;
  }
void C_Camera2::S_filterProperties::setGaussian_sigma(double value)
  {
  gaussian_sigma = value;
  }

float C_Camera2::S_filterProperties::getBilateralSigmaColor() const
  {
  return bilateral_sigma_color;
  }
void C_Camera2::S_filterProperties::setBilateral_sigma_color(float value)
  {
  bilateral_sigma_color = value;
  }

float C_Camera2::S_filterProperties::getBilateralSigmaSpatial() const
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
  return cameraPose;
  }

void C_Camera2::setCameraPose(C_AbsolutePose *value)
  {
  cameraPose = value;
  }

