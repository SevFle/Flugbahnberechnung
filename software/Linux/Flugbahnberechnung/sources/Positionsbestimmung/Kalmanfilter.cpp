#include "headers/Positionsbestimmung/Kalmanfilter.h"
using namespace kalmanFilter;

C_kalmanFilter::C_kalmanFilter ()
  {
  this->kalmanOnCuda          = new kalmanOnCuda::C_kalmanOnCuda;
  this->statePre              = new cv::Mat;        //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
  this->statePost             = new cv::Mat;        //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
  this->transitionMatrix      = new cv::Mat;        //!< state transition matrix (A)
  this->controlMatrix         = new cv::Mat;        //!< control matrix (B) (not used if there is no control)
  this->measurementMatrix     = new cv::Mat;        //!< measurement matrix (H)
  this->processNoiseCov       = new cv::Mat;        //!< process noise covariance matrix (Q)
  this->measurementNoiseCov   = new cv::Mat;        //!< measurement noise covariance matrix (R)
  this->errorCovPre           = new cv::Mat;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
  this->gain                  = new cv::Mat;        //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
  this->errorCovPost          = new cv::Mat;        //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

  this->predictedState        = new cv::Mat;
  this->gpuState              = new cv::cuda::GpuMat;
  this->measurement           = new cv::Mat;
  this->gpuMeasurement        = new cv::cuda::GpuMat;
  this->controllvector        = new cv::Mat;
  this->gpuControllvector     = new cv::cuda::GpuMat;

  }
C_kalmanFilter::~C_kalmanFilter ()
  {
  delete (gpuControllvector);
  delete (controllvector);
  delete (gpuMeasurement);
  delete (measurement);
  delete (gpuState);
  delete (predictedState);
  delete (this->errorCovPost);
  delete (this->gain);
  delete (this->errorCovPre);
  delete (this->measurementNoiseCov);
  delete (this->processNoiseCov);
  delete (this->measurementMatrix);
  delete (this->controlMatrix);
  delete (this->transitionMatrix);
  delete (this->statePost);
  delete (this->statePre);
  delete (this->kalmanOnCuda);
  }

void C_kalmanFilter::create(int dynamParams, int measureParams, int controlParams, int type)
  {
  std::cout << "##################### KALMAN CREATE PHASE ######################" << std::endl;
  CV_Assert( dynamParams > 0 && measureParams > 0 );
  CV_Assert( type == CV_32F || type == CV_64F );

  this->kalmanOnCuda            = new kalmanOnCuda::C_kalmanOnCuda(dynamParams, measureParams, controlParams, type);
  controlParams                 = std::max        (controlParams, 0);

  *this->statePre               = cv::Mat::zeros  (dynamParams, 1, type);
  *this->statePost              = cv::Mat::zeros  (dynamParams, 1, type);

  *this->transitionMatrix       = cv::Mat::eye    (dynamParams, dynamParams, type);
  *this->processNoiseCov        = cv::Mat::eye    (dynamParams, dynamParams, type);

  *this->measurementMatrix      = cv::Mat::zeros  (measureParams, dynamParams, type);
  *this->measurementNoiseCov    = cv::Mat::eye    (measureParams, measureParams, type);
  *this->measurement            = cv::Mat::zeros  (measureParams, 1, type);

  *this->errorCovPre            = cv::Mat::zeros  (dynamParams, dynamParams, type);
  *this->errorCovPost           = cv::Mat::zeros  (dynamParams, dynamParams, type);

  *this->gain                   = cv::Mat::zeros  (dynamParams, measureParams, type);
  if( controlParams > 0 )
    {
    *this->controlMatrix        = cv::Mat::zeros  (dynamParams, controlParams, type);
    *this->controllvector       = cv::Mat::zeros  (controlParams,1, type);
    }
  else
      controlMatrix->release();

  *this->predictedState         = cv::Mat::zeros  (dynamParams, 1, type);
  *this->gpuState               = cv::cuda::GpuMat(dynamParams, 1, type);


  std::cout << "Kalmanfilter->statePre [predicted]: " << std::endl << *this->statePre <<std::endl;
  std::cout << "Kalmanfilter->statePost [corrected]: " << std::endl << *this->statePost <<std::endl;
  std::cout << "Kalmanfilter->transitionMatrix [A]: " << std::endl << *this->transitionMatrix <<std::endl;
  std::cout << "Kalmanfilter->processNoiseCov [Q]: " << std::endl << *this->processNoiseCov <<std::endl;
  std::cout << "Kalmanfilter->measurementMatrix [H]: " << std::endl << *this->measurementMatrix <<std::endl;
  std::cout << "Kalmanfilter->measurementNoiseCov [R]: " << std::endl << *this->measurementNoiseCov <<std::endl;
  std::cout << "Kalmanfilter->errorCovPre [priori P]: " << std::endl << *this->errorCovPre <<std::endl;
  std::cout << "Kalmanfilter->errorCovPost [posteriori P]: " << std::endl << *this->errorCovPost <<std::endl;
  std::cout << "Kalmanfilter->gain [K]: " << std::endl << *this->gain <<std::endl;

  if( controlParams > 0 )
    {
      std::cout << "Kalmanfilter->controlMatrix [B]: " << std::endl << *this->controlMatrix <<std::endl;
      std::cout << "Kalmanfilter->controlvector [u]: " << std::endl << *this->controllvector <<std::endl;

    }

  init();
  }

void C_kalmanFilter::init()
  {
  std::cout << "##################### KALMAN INIT PHASE ######################" << std::endl;
  cv::setIdentity(*this->transitionMatrix);
  this->kalmanOnCuda->transitionMatrix->upload(*this->transitionMatrix);
  std::cout << "Kalmanfilter->transitionMatrix [A]: " << std::endl << *this->transitionMatrix <<std::endl;

  cv::setIdentity(*this->measurementMatrix);
  this->kalmanOnCuda->measurementMatrix->upload(*this->measurementMatrix);
  std::cout << "Kalmanfilter->measurementMatrix [H]: " << std::endl << *this->measurementMatrix <<std::endl;

  cv::setIdentity(*this->processNoiseCov, cv::Scalar(1e-2));
  this->kalmanOnCuda->processNoiseCov->upload(*this->processNoiseCov);
  std::cout << "Kalmanfilter->processNoiseCov [Q]: " << std::endl << *this->processNoiseCov <<std::endl;

  cv::setIdentity(*this->measurementNoiseCov, cv::Scalar(1e-2));
  this->kalmanOnCuda->measurementNoiseCov->upload(*this->measurementNoiseCov);
  std::cout << "Kalmanfilter->measurementNoiseCov [R]: " << std::endl << *this->measurementNoiseCov <<std::endl;

  cv::setIdentity(*this->gain);
  this->kalmanOnCuda->gain->upload(*this->gain);
  std::cout << "Kalmanfilter->gain [K]: " << std::endl << *this->gain <<std::endl;

  if(controllvector)
    {
    for(int i = 0; i < 6; i++)
      {
      this->controllvector->at<float>(i) = -9.807f;
      }
    this->gpuControllvector->upload(*this->controllvector);
    std::cout << "Kalmanfilter->controllvector [u]: " << std::endl << *this->controllvector <<std::endl;
    }
  }

void C_kalmanFilter::reset()
  {
  std::cout << "##################### KALMAN RESET PHASE ######################" << std::endl;
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
    this->transitionMatrix->at<float>(3) = dtSeconds;
    this->transitionMatrix->at<float>(10) = dtSeconds;
    this->transitionMatrix->at<float>(17) = dtSeconds;
    this->kalmanOnCuda->transitionMatrix->upload(*this->transitionMatrix);
    std::cout << "Kalmanfilter->transitionMatrix [A] at " << dtSeconds << ": " << std::endl << *this->transitionMatrix <<std::endl;

    this->controlMatrix->at<float>(12) = 0.5*(dtSeconds*dtSeconds);
    this->controlMatrix->at<float>(30) = dtSeconds;
    this->kalmanOnCuda->controlMatrix->upload(*this->controlMatrix);

    std::cout << "Kalmanfilter->controlMatrix [B] at " << dtSeconds << ": " << std::endl << *this->controlMatrix <<std::endl;

    *this->gpuState = this->kalmanOnCuda->predict(*gpuControllvector);
    this->gpuState->download(*this->predictedState);
    std::cout << "Kalmanfilter->Prediction at " << dtSeconds << ": " << std::endl << *this->predictedState <<std::endl;
    }


  }
void C_kalmanFilter::correct(float x, float y, float z)
  {
  std::cout << "##################### KALMAN CORRECTION PHASE ######################" << std::endl;
  this->measurement->at<float>(0) = x;
  this->measurement->at<float>(1) = y;
  this->measurement->at<float>(2) = z;
  std::cout << "Kalmanfilter->measurement "<< std::endl << *this->measurement <<std::endl;

  this->gpuMeasurement->upload          (*this->measurement);
  this->kalmanOnCuda->correct           (*this->gpuMeasurement);
  }
void C_kalmanFilter::initFirstPosition(float x, float y, float z, float vx, float vy, float vz)
  {
  std::cout << "##################### KALMAN INIT FIRST POSITION PHASE ######################" << std::endl;
  this->statePost->at<float>(0)         = x;
  this->statePost->at<float>(1)         = y;
  this->statePost->at<float>(2)         = z;
  this->statePost->at<float>(3)         = vx;
  this->statePost->at<float>(4)         = vy;
  this->statePost->at<float>(5)         = vz;
  this->kalmanOnCuda->statePost->upload(*this->statePost);
  cv::setIdentity(*this->errorCovPre, cv::Scalar(1e-1));
  this->kalmanOnCuda->errorCovPre->upload(*this->errorCovPre);

  }

void C_kalmanFilter::processKalman(float dt, float x, float y, float z)
  {
  this->measurement->at<float>(0) = x;
  this->measurement->at<float>(1) = y;
  this->measurement->at<float>(2) = z;
  std::cout << "Kalmanfilter->measurement "<< std::endl << *this->measurement <<std::endl;

  this->gpuMeasurement->upload          (*this->measurement);

  double dtSeconds = dt/1000;
  if(dtSeconds > 1.0)
    {
    std::cout << "dT to high, skipping" << std::endl;
    }
  else
    {
    this->transitionMatrix->at<float>(3) = dtSeconds;
    this->transitionMatrix->at<float>(10) = dtSeconds;
    this->transitionMatrix->at<float>(17) = dtSeconds;
    this->kalmanOnCuda->transitionMatrix->upload(*this->transitionMatrix);
    std::cout << "Kalmanfilter->transitionMatrix [A] at " << dtSeconds << ": " << std::endl << *this->transitionMatrix <<std::endl;

    this->controlMatrix->at<float>(12) = 0.5*(dtSeconds*dtSeconds);
    this->controlMatrix->at<float>(30) = dtSeconds;
    this->kalmanOnCuda->controlMatrix->upload(*this->controlMatrix);

    std::cout << "Kalmanfilter->controlMatrix [B] at " << dtSeconds << ": " << std::endl << *this->controlMatrix <<std::endl;
    this->kalmanOnCuda->processKalman(*gpuControllvector, *gpuMeasurement);

    this->kalmanOnCuda->statePost->download(*this->predictedState);
    std::cout << "Kalmanfilter->Prediction at " << dtSeconds << ": " << std::endl << *this->predictedState <<std::endl;
    }

  }
