#include "camera2.h"

using namespace Camera;

C_Camera2::C_Camera2()
  {
  auto cap = new cv::Mat;
  auto cpuSrc = new cv::Mat;
  auto DistCoeffs = new cv::Mat;
  auto Intrinsic = new cv::Mat;
  auto gpuSrc = new cv::cuda::GpuMat;
  auto map1 = new cv::cuda::GpuMat;
  auto map2 = new cv::cuda::GpuMat;
  }
C_Camera2::~C_Camera2()
  {
  delete (map1);
  delete (map2);
  delete (GpuSrc);
  delete (Intrinsic);
  delete (DistCoeffs);
  delete (CpuSrc);
  delete (cap);
  }

bool C_Camera2::open()
  {
  this->cap->open(Pipeline, cv::CAP_GSTREAMER);
  if(!this->cap->isOpened()) return false;
  else return true;
  }
bool C_Camera2::close()
  {
  this->cap->release();
  if(!this->cap->isOpened()) return true;
  else return false;
  }
void C_Camera2::savePicture (int camera_id, int photo_id, std::string definition)
  {
  imwrite (definition + std::to_string (camera_id) + "_Snapshot_" + std::to_string (photo_id) + ".png",*CpuSrc);
  }
void C_Camera2::initRectifyMap()
  {
  cv::Mat cpu_map1;
  cv::Mat cpu_map2;
  initUndistortRectifyMap (*Intrinsic,*DistCoeffs,cv::Mat(),*Intrinsic,cv::Size (CpuSrc->cols,CpuSrc->rows), CV_32FC1,cpu_map1,cpu_map2);

  this->map1->upload (cpu_map1);
  this->map2->upload (cpu_map2);

  }

void C_Camera2::setCalibrationParameter    (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3])
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
void C_Camera2::getCalibrationParameter    (double (&DistCoeffs)[1][5], double (&Intrinsic)[3][3]) const
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

void C_Camera2::setPipeline(std::string Pipeline)
  {
  this->Pipeline = Pipeline;
  }
void C_Camera2::setROI(int &width, int &height)
  {

  }
int C_Camera2::getROI()
  {

  }
void setCameraID                  (int &cameraID)
  {

  }
int  getCameraID                  ()
  {

  }

