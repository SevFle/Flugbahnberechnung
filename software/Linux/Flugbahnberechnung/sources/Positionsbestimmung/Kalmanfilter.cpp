#include "headers/Positionsbestimmung/Kalmanfilter.h"
using namespace kalmanFilter;

C_kalmanFilter::C_kalmanFilter ()
  {
  this->kf              = nullptr; //Wird später erstellt
  this->dynamParams     = 0;
  this->measureParams   = 0;
  this->controlParams   = 0;
  this->type            = 0;
  this->state_post      = nullptr;
  this->state_pre       = nullptr;
  this->measurement       = nullptr;
  }
C_kalmanFilter::~C_kalmanFilter ()
  {
  if(this->measurement != nullptr)
    delete (this->measurement);
  if(this->state_pre != nullptr)
    delete (this->state_pre);
  if(this->state_post != nullptr)
    delete (this->state_post);
  if(this->kf != nullptr)
    delete (this->kf);
  this->type            = 0;
  this->controlParams   = 0;
  this->measureParams   = 0;
  this->dynamParams     = 0;
  }

void C_kalmanFilter::init(int dynamParams, int measureParams, int controlParams, int type)
  {
  this->controlParams = controlParams;
  this->measureParams = measureParams;
  this->dynamParams   = dynamParams;
  this->type          = type;
  this->kf            = new cv::KalmanFilter(this->dynamParams, this->measureParams, this->controlParams, type);
  this->measurement   = new cv::Mat_<float>(measureParams,1, type);
  this->state_post    = new cv::Mat_<float>(dynamParams,1, type);
  this->state_pre     = new cv::Mat_<float>(dynamParams,1, type);

  cv::setIdentity(this->kf->transitionMatrix);
  cv::setIdentity(this->kf->measurementNoiseCov, cv::Scalar(1));
  cv::setIdentity(this->kf->measurementMatrix);
  this->kf->processNoiseCov.at<float>(0,0) = 1e-2;
  this->kf->processNoiseCov.at<float>(1,1) = 1e-2;
  this->kf->processNoiseCov.at<float>(2,2) = 1e-2;
  this->kf->processNoiseCov.at<float>(3,3) = 1e-2;
  this->kf->processNoiseCov.at<float>(4,4) = 1e-2;
  this->kf->processNoiseCov.at<float>(5,5) = 1e-2;
  this->kf->processNoiseCov.at<float>(6,6) = 1e-2;
  this->kf->processNoiseCov.at<float>(7,7) = 1e-2;
  this->kf->processNoiseCov.at<float>(8,8) = 1e-2;
  std::cout << "processNoiseCov: " << std::endl << this->kf->processNoiseCov << std::endl;
  std::cout << "measurementNoiseCov: " << std::endl << this->kf->measurementNoiseCov << std::endl;

  }
void C_kalmanFilter::reset()
  {
  this->kf->init(this->dynamParams, this->measureParams, this->controlParams, this->type);
  }
void C_kalmanFilter::predict(float dT)
  {
  double dtSeconds = dT/1000;
  if(dtSeconds > 1.0)
    {
    std::cout << "dT to high, skipping" << std::endl;
    }
  else
    {
    //STACHNISS METHODE
//      [1, 0, 0, T, 0, 0, T²/2, 0, 0; //8
//       0, 1, 0, 0, T, 0, 0, T²/2, 0; //17
//       0, 0, 1, 0, 0, T, 0, 0, T²/2;
//       0, 0, 0, 1, 0, 0, T, 0, 0;
//       0, 0, 0, 0, 1, 0, 0, T, 0;
//       0, 0, 0, 0, 0, 1, 0, 0, T;
//       0, 0, 0, 0, 0, 0, 1, 0, 0;
//       0, 0, 0, 0, 0, 0, 0, 1, 0;
//       0, 0, 0, 0, 0, 0, 0, 0, 1]

    this->kf->transitionMatrix.at<float>(0,3) = dtSeconds;
    this->kf->transitionMatrix.at<float>(0,6) = (std::pow(dtSeconds, 2)/2);
    this->kf->transitionMatrix.at<float>(1,4) = dtSeconds;
    this->kf->transitionMatrix.at<float>(1,7) = (std::pow(dtSeconds, 2)/2);
    this->kf->transitionMatrix.at<float>(2,5) = dtSeconds;
    this->kf->transitionMatrix.at<float>(2,8) = (std::pow(dtSeconds, 2)/2);
    this->kf->transitionMatrix.at<float>(3,6) = dtSeconds;
    this->kf->transitionMatrix.at<float>(4,7) = dtSeconds;
    this->kf->transitionMatrix.at<float>(5,8) = dtSeconds;
    *this->state_pre = this->kf->predict();
    std::cout << "transitionmatrix: " << std::endl << this->kf->transitionMatrix << std::endl;
    }


  }
void C_kalmanFilter::correct(float x, float y, float z)
  {
  this->measurement->at<float>(0,0) = x;
  this->measurement->at<float>(1,0) = y;
  this->measurement->at<float>(2,0) = z;
  std::cout << "measurement : " << std::endl << *this->measurement << std::endl;
  this->kf->correct(*this->measurement);
  }
void C_kalmanFilter::initFirstPosition(float x, float y, float z, float vx, float vy, float vz)
  {
  this->kf->statePost.at<float>(0,0)         = x;
  this->kf->statePost.at<float>(1,0)         = y;
  this->kf->statePost.at<float>(2,0)         = z;
  this->kf->statePost.at<float>(3,0)         = vx;
  this->kf->statePost.at<float>(4,0)         = vy;
  this->kf->statePost.at<float>(5,0)         = vz;
  this->kf->statePost.at<float>(8,0)         = -9.807;

  cv::setIdentity(this->kf->errorCovPre, cv::Scalar(1));
  std::cout << "gain on first hit: " << std::endl << this->kf->gain << std::endl;
  std::cout << "statePost on first hit: " << std::endl << this->kf->statePost << std::endl;
  std::cout << "errorCovPre on first hit: " << std::endl << this->kf->errorCovPre << std::endl;

  }

cv::Scalar C_kalmanFilter::getGainMean()
  {
  float mean =0;
  cv::Scalar gainMean =
  mean += this->kf->gain.at<float>(0,0);
  mean += this->kf->gain.at<float>(1,1);
  mean += this->kf->gain.at<float>(2,2);
  mean /= 3;
  gainMean[0] = mean;
  std::cout << "gain mean: " << std::endl << this->kf->gain << std::endl;
  return gainMean;
  }

