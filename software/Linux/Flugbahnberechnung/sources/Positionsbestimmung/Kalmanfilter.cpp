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
  this->measurement   = new cv::Mat_<float>(dynamParams,1);
  this->state_post    = new cv::Mat;
  this->state_pre     = new cv::Mat;

  this->kf->statePost.copyTo  (*this->state_post);
  this->kf->statePre.copyTo   (*this->state_pre);
  }
void C_kalmanFilter::reset()
  {
  std::cout << "##################### KALMAN RESET PHASE ######################" << std::endl;
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
    std::cout << "##################### KALMAN PREDICT PHASE ######################" << std::endl;
    //STACHNISS METHODE

    this->kf->transitionMatrix.at<float>(2) = dtSeconds;
    this->kf->transitionMatrix.at<float>(4) = 0.5*(dtSeconds*dtSeconds);
    this->kf->transitionMatrix.at<float>(13) = dtSeconds;
    this->kf->transitionMatrix.at<float>(16) = 0.5*(dtSeconds*dtSeconds);
    this->kf->transitionMatrix.at<float>(23) = dtSeconds;
    this->kf->transitionMatrix.at<float>(26) = 0.5*(dtSeconds*dtSeconds);
    this->kf->transitionMatrix.at<float>(33) = dtSeconds;
    this->kf->transitionMatrix.at<float>(43) = dtSeconds;
    this->kf->transitionMatrix.at<float>(53) = dtSeconds;


    //this->kalmanOnCuda->transitionMatrix->upload(*this->transitionMatrix);
    std::cout << "Kalmanfilter->transitionMatrix [A] at " << dtSeconds << ": " << std::endl << this->kf->transitionMatrix <<std::endl;


    *this->state_pre = this->kf->predict();
    std::cout << "Kalmanfilter->Prediction at " << dtSeconds << ": " << std::endl << this->state_pre<<std::endl;
    }


  }
void C_kalmanFilter::correct(float x, float y, float z)
  {
  std::cout << "##################### KALMAN CORRECTION PHASE ######################" << std::endl;
  this->measurement->at<float>(0) = x;
  this->measurement->at<float>(1) = y;
  this->measurement->at<float>(2) = z;
  std::cout << "Kalmanfilter->measurement "<< std::endl << *this->measurement <<std::endl;

  this->kf->correct(*this->measurement);
  }
void C_kalmanFilter::initFirstPosition(float x, float y, float z, float vx, float vy, float vz)
  {
  std::cout << "##################### KALMAN INIT FIRST POSITION PHASE ######################" << std::endl;
  this->kf->statePost.at<float>(0)         = x;
  this->kf->statePost.at<float>(1)         = y;
  this->kf->statePost.at<float>(2)         = z;
  this->kf->statePost.at<float>(3)         = vx;
  this->kf->statePost.at<float>(4)         = vy;
  this->kf->statePost.at<float>(5)         = vz;
  this->kf->statePost.at<float>(8)         = -9.807;

  cv::setIdentity(this->kf->errorCovPre, cv::Scalar(1e-1));
  //this->kalmanOnCuda->errorCovPre->upload(*this->errorCovPre);

  }

cv::Scalar C_kalmanFilter::getGainMean()
  {
  cv::Scalar gainMean = cv::mean(this->kf->gain);
  return gainMean;
  }

