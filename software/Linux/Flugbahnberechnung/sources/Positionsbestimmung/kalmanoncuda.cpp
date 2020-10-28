#include "headers/Positionsbestimmung/kalmanoncuda.h"
using namespace kalmanOnCuda;

C_kalmanOnCuda::C_kalmanOnCuda()
  {
  this->statePre            = new cv::cuda::GpuMat;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
  this->statePost           = new cv::cuda::GpuMat;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
  this->transitionMatrix    = new cv::cuda::GpuMat;   //!< state transition matrix (A)
  this->controlMatrix       = new cv::cuda::GpuMat;      //!< control matrix (B) (not used if there is no control)
  this->measurementMatrix   = new cv::cuda::GpuMat;  //!< measurement matrix (H)
  this->processNoiseCov     = new cv::cuda::GpuMat;    //!< process noise covariance matrix (Q)
  this->measurementNoiseCov = new cv::cuda::GpuMat;//!< measurement noise covariance matrix (R)
  this->errorCovPre         = new cv::cuda::GpuMat;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
  this->gain                = new cv::cuda::GpuMat;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
  this->errorCovPost        = new cv::cuda::GpuMat;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

  // temporary matrices
  this->temp1               = new cv::cuda::GpuMat;
  this->temp2               = new cv::cuda::GpuMat;
  this->temp3               = new cv::cuda::GpuMat;
  this->temp4               = new cv::cuda::GpuMat;
  this->temp5                   = new cv::cuda::GpuMat;
  this->transitionMatrix_temp   = new cv::cuda::GpuMat;
  this->controlMatrix_temp      = new cv::cuda::GpuMat;
  this->measurementMatrix_temp  = new cv::cuda::GpuMat;
  this->gain_temp               = new cv::cuda::GpuMat;

  }
C_kalmanOnCuda::C_kalmanOnCuda(int dynamParams, int measureParams, int controlParams, int type)
  {
  this->statePre            = new cv::cuda::GpuMat;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
  this->statePost           = new cv::cuda::GpuMat;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
  this->transitionMatrix    = new cv::cuda::GpuMat;   //!< state transition matrix (A)
  this->controlMatrix       = new cv::cuda::GpuMat;      //!< control matrix (B) (not used if there is no control)
  this->measurementMatrix   = new cv::cuda::GpuMat;  //!< measurement matrix (H)
  this->processNoiseCov     = new cv::cuda::GpuMat;    //!< process noise covariance matrix (Q)
  this->measurementNoiseCov = new cv::cuda::GpuMat;//!< measurement noise covariance matrix (R)
  this->errorCovPre         = new cv::cuda::GpuMat;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
  this->gain                = new cv::cuda::GpuMat;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
  this->errorCovPost        = new cv::cuda::GpuMat;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

  // temporary matrices
  this->temp1               = new cv::cuda::GpuMat;
  this->temp2               = new cv::cuda::GpuMat;
  this->temp3               = new cv::cuda::GpuMat;
  this->temp4               = new cv::cuda::GpuMat;
  this->temp5                   = new cv::cuda::GpuMat;
  this->transitionMatrix_temp   = new cv::cuda::GpuMat;
  this->controlMatrix_temp      = new cv::cuda::GpuMat;
  this->measurementMatrix_temp  = new cv::cuda::GpuMat;
  this->gain_temp               = new cv::cuda::GpuMat;

  init(dynamParams, measureParams, controlParams, type);
  }
C_kalmanOnCuda::~C_kalmanOnCuda()
  {
  delete (statePre);           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
  delete (statePost);          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
  delete (transitionMatrix);   //!< state transition matrix (A)
  delete (controlMatrix);      //!< control matrix (B) (not used if there is no control)
  delete (measurementMatrix);  //!< measurement matrix (H)
  delete (processNoiseCov);    //!< process noise covariance matrix (Q)
  delete (measurementNoiseCov);//!< measurement noise covariance matrix (R)
  delete (errorCovPre);        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
  delete (gain);               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
  delete (errorCovPost);       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

  // temporary matrices
  delete (temp1);
  delete (temp2);
  delete (temp3);
  delete (temp4);
  delete (temp5);
  delete (transitionMatrix_temp);
  delete (controlMatrix_temp);
  delete (measurementMatrix_temp);
  delete (gain_temp);
  }


void              C_kalmanOnCuda::init                              (int DP, int MP, int CP, int type)
  {
  CV_Assert( DP > 0 && MP > 0 );
  CV_Assert( type == CV_32F || type == CV_64F );
  CP = std::max(CP, 0);

  cv::Mat temp;
  temp = cv::Mat::zeros(DP, 1, type);
  this->statePre->upload(temp);
  this->statePost->upload(temp);

  temp = cv::Mat::eye(DP, DP, type);
  this->transitionMatrix->upload(temp);
  this->transitionMatrix_temp->upload(temp);
  this->processNoiseCov->upload(temp);

  temp = cv::Mat::zeros(MP, DP, type);
  this->measurementMatrix->upload(temp);
  this->measurementMatrix_temp->upload(temp);

  temp = cv::Mat::eye(MP, MP, type);
  this->measurementNoiseCov->upload(temp);

  temp = cv::Mat::zeros(DP, DP, type);
  this->errorCovPre->upload(temp);
  this->errorCovPost->upload(temp);

  temp = cv::Mat::zeros(DP, MP, type);
  this->gain->upload(temp);
  this->gain_temp->upload(temp);
  if( CP > 0 )
    {
    temp = cv::Mat::zeros(DP, CP, type);
    this->controlMatrix->upload(temp);
    this->controlMatrix_temp->upload(temp);
    }

  else
      this->controlMatrix->release();

  this->temp1->create(DP, DP, type);
  this->temp2->create(MP, DP, type);
  this->temp3->create(MP, MP, type);
  this->temp4->create(MP, DP, type);
  this->temp5->create(MP, 1, type);
  }
const             cv::cuda::GpuMat& C_kalmanOnCuda::predict         (const cv::cuda::GpuMat& control)
  {
  cv::Mat temp;
  std::cout <<  "statePre = transitionMatrix*statePost [x'(k) = A*x(k)]" << std::endl;
  //update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  statePost->download(temp);
  printmatrix("statePost", temp);


  cv::cuda::gemm(*transitionMatrix, *statePost, 1, cv::cuda::GpuMat() , 0 , *statePre);

  statePre->download(temp);
  printmatrix("statePre", temp);


  if( !control.empty() )
    {
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    std::cout <<  "controlMatrix_temp = controlMatrix*control [B*u(k)]" << std::endl;

    controlMatrix->download(temp);
    printmatrix("controlMatrix", temp);
    control.download(temp);
    printmatrix("control", temp);

    cv::cuda::gemm(*controlMatrix, control, 1, cv::cuda::GpuMat() , 0 , *controlMatrix_temp);
    //cv::cuda::multiply(controlMatrix,control, controlMatrix_temp);
    controlMatrix_temp->download(temp);
    printmatrix("controlMatrix_temp", temp);

    std::cout <<  "statePre = statePre + controlMatrix_temp [x'(k) = x'(k) + controlMatrix_temp]" << std::endl;
    statePre->download(temp);
    printmatrix("statePre", temp);

    cv::cuda::add(*statePre, *controlMatrix_temp, *statePre);
    statePre->download(temp);
    printmatrix("statePre + controllMatrix_temp", temp);
    }

  std::cout <<  "update error covariance matrices: temp1 = A*P(k) [temp1 = transitionMatrix*errorCovPost]" << std::endl;
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  errorCovPost->download(temp);
  printmatrix("errorCovPost", temp);
  cv::cuda::multiply(*transitionMatrix,*errorCovPost, *temp1);
  temp1->download(temp);
  printmatrix("temp1", temp);


  std::cout <<  "P'(k) = temp1*At + Q" << std::endl;
  // P'(k) = temp1*At + Q
  temp1->download(temp);
  printmatrix("temp1", temp);
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  processNoiseCov->download(temp);
  printmatrix("processNoiseCov", temp);

  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  cv::cuda::gemm(*temp1, *transitionMatrix, 1, *processNoiseCov, 1, *errorCovPre, cv::GEMM_2_T);
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  // handle the case when there will be measurement before the next predict->
  statePre->copyTo(*statePost);
  errorCovPre->copyTo(*errorCovPost);
  return *statePre;
  }
cv::cuda::GpuMat& C_kalmanOnCuda::correct                           ( const cv::cuda::GpuMat& measurement )
  {
  cv::Mat temp;

  std::cout <<  "temp2 = H*P'(k)" << std::endl;
  // temp2 = H*P'(k)
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  cv::cuda::gemm(*measurementMatrix, *errorCovPre, 1, cv::cuda::GpuMat() , 0 , *temp2);
  temp2->download(temp);
  printmatrix("temp2", temp);

  std::cout <<  "temp3 = temp2*Ht + R" << std::endl;
  // temp3 = temp2*Ht + R
  //gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
  temp2->download(temp);
  printmatrix("temp2", temp);
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  measurementNoiseCov->download(temp);
  printmatrix("measurementNoiseCov", temp);

  cv::cuda::gemm(*temp2, *measurementMatrix, 1, *measurementNoiseCov, 1, *temp3, cv::GEMM_2_T);
  temp3->download(temp);
  printmatrix("temp3", temp);

  std::cout <<  "temp4 = inv(temp3)*temp2 = Kt(k)" << std::endl;
  // temp4 = inv(temp3)*temp2 = Kt(k)
  cv::Mat cputemp4;
  cv::Mat cputemp2;
  cv::Mat cputemp3;

  temp3->download(cputemp3);
  temp2->download(cputemp2);
  temp4->download(cputemp4);

  printmatrix("cputemp3", cputemp3);
  printmatrix("cputemp2", cputemp2);

  cv::solve(cputemp3, cputemp2, cputemp4, cv::DECOMP_SVD);
  printmatrix("cputemp4", cputemp4);

  temp4->upload(cputemp4);

  std::cout <<  "gain = temp4.t()" << std::endl;

  // K(k)
  //gain = temp4.t();
  cv::cuda::transpose(*temp4, *gain);

  gain->download(temp);
  printmatrix("gain", temp);

  std::cout <<  "measurementMatrix_temp = measurementMatrix*statePre [measurementMatrix_temp = H*x'(k)]" << std::endl;
  // temp5 = z(k) - H*x'(k)
  //temp5 = measurement - measurementMatrix*statePre;
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  statePre->download(temp);
  printmatrix("statePre", temp);

  cv::cuda::gemm(*measurementMatrix, *statePre, 1, cv::Mat() , 0 , *measurementMatrix_temp);
  measurementMatrix_temp->download(temp);
  printmatrix("measurementMatrix_temp", temp);

  std::cout <<  "temp5 = measurement - measurementMatrix_temp [temp5 = z(k) - measurementMatrix_temp]" << std::endl;
  measurement.download(temp);
  printmatrix("measurement", temp);

  cv::cuda::subtract(measurement, *measurementMatrix_temp, *temp5);
  temp5->download(temp);
  printmatrix("temp5", temp);



  // x(k) = x'(k) + K(k)*temp5
  //statePost = statePre + gain*temp5;
  //cv::cuda::multiply(gain, temp5, gain_temp);
  std::cout <<  "gain_temp = gain*temp5 [gain_temp = K(k)*temp5]" << std::endl;
  gain->download(temp);
  printmatrix("gain", temp);
  temp5->download(temp);
  printmatrix("temp5", temp);

  cv::cuda::gemm(*gain, *temp5, 1, cv::Mat() , 0 , *gain_temp);
  gain_temp->download(temp);
  printmatrix("gain_temp", temp);

  std::cout <<  "statePost = statePre + gain_temp [x(k) = x'(k) + gain_temp]" << std::endl;
  statePre->download(temp);
  printmatrix("statePre", temp);

  cv::cuda::add(*statePre, *gain_temp, *statePost);
  statePost->download(temp);
  printmatrix("statePost", temp);


  // P(k) = P'(k) - K(k)*temp2
  //errorCovPost = errorCovPre - gain*temp2;
  //cv::cuda::multiply(gain, temp2, gain_temp);
  std::cout <<  "gain_temp =  K(k)*temp2 [gain_temp = K(k)*temp2]" << std::endl;
  gain->download(temp);
  printmatrix("gain", temp);
  temp2->download(temp);
  printmatrix("temp2", temp);
  cv::cuda::gemm(*gain, *temp2, 1, cv::Mat() , 0 , *gain_temp);
  gain_temp->download(temp);
  printmatrix("gain_temp", temp);

  std::cout <<  "errorCovPost = errorCovPre - gain_temp [P(k) = P'(k) - gain_temp]" << std::endl;
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  cv::cuda::subtract(*errorCovPre, *gain_temp, *errorCovPost);
  errorCovPost->download(temp);
  printmatrix("errorCovPost", temp);

  return *statePost;
  }
void              C_kalmanOnCuda::processKalman                     (const cv::cuda::GpuMat &control, const cv::cuda::GpuMat &measurement)
  {
  std::cout << "##################### KALMAN PREDICT PHASE ######################" << std::endl;

  cv::Mat temp;
  std::cout <<  "statePre = transitionMatrix*statePost [x'(k) = A*x(k)]" << std::endl;
  //update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  statePost->download(temp);
  printmatrix("statePost", temp);


  cv::cuda::gemm(*transitionMatrix, *statePost, 1, cv::cuda::GpuMat() , 0 , *statePre);

  statePre->download(temp);
  printmatrix("statePre", temp);


  if( !control.empty() )
    {
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    std::cout <<  "controlMatrix_temp = controlMatrix*control [B*u(k)]" << std::endl;

    controlMatrix->download(temp);
    printmatrix("controlMatrix", temp);
    control.download(temp);
    printmatrix("control", temp);

    cv::cuda::gemm(*controlMatrix, control, 1, cv::cuda::GpuMat() , 0 , *controlMatrix_temp);
    //cv::cuda::multiply(controlMatrix,control, controlMatrix_temp);
    controlMatrix_temp->download(temp);
    printmatrix("controlMatrix_temp", temp);

    std::cout <<  "statePre = statePre + controlMatrix_temp [x'(k) = x'(k) + controlMatrix_temp]" << std::endl;
    statePre->download(temp);
    printmatrix("statePre", temp);

    cv::cuda::add(*statePre, *controlMatrix_temp, *statePre);
    statePre->download(temp);
    printmatrix("statePre + controllMatrix_temp", temp);
    }

  std::cout <<  "update error covariance matrices: temp1 = A*P(k) [temp1 = transitionMatrix*errorCovPost]" << std::endl;
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  errorCovPost->download(temp);
  printmatrix("errorCovPost", temp);
  cv::cuda::multiply(*transitionMatrix,*errorCovPost, *temp1);
  temp1->download(temp);
  printmatrix("temp1", temp);


  std::cout <<  "P'(k) = temp1*At + Q" << std::endl;
  // P'(k) = temp1*At + Q
  temp1->download(temp);
  printmatrix("temp1", temp);
  transitionMatrix->download(temp);
  printmatrix("transitionMatrix", temp);
  processNoiseCov->download(temp);
  printmatrix("processNoiseCov", temp);

  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  cv::cuda::gemm(*temp1, *transitionMatrix, 1, *processNoiseCov, 1, *errorCovPre, cv::GEMM_2_T);
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  // handle the case when there will be measurement before the next predict->
  statePre->copyTo(*statePost);
  errorCovPre->copyTo(*errorCovPost);

  std::cout << "##################### KALMAN CORRECT PHASE ######################" << std::endl;


  std::cout <<  "temp2 = H*P'(k)" << std::endl;
  // temp2 = H*P'(k)
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  cv::cuda::gemm(*measurementMatrix, *errorCovPre, 1, cv::cuda::GpuMat() , 0 , *temp2);
  temp2->download(temp);
  printmatrix("temp2", temp);

  std::cout <<  "temp3 = temp2*Ht + R" << std::endl;
  // temp3 = temp2*Ht + R
  //gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
  temp2->download(temp);
  printmatrix("temp2", temp);
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  measurementNoiseCov->download(temp);
  printmatrix("measurementNoiseCov", temp);

  cv::cuda::gemm(*temp2, *measurementMatrix, 1, *measurementNoiseCov, 1, *temp3, cv::GEMM_2_T);
  temp3->download(temp);
  printmatrix("temp3", temp);

  std::cout <<  "temp4 = inv(temp3)*temp2 = Kt(k)" << std::endl;
  // temp4 = inv(temp3)*temp2 = Kt(k)
  cv::Mat cputemp4;
  cv::Mat cputemp2;
  cv::Mat cputemp3;

  temp3->download(cputemp3);
  temp2->download(cputemp2);
  temp4->download(cputemp4);

  printmatrix("cputemp3", cputemp3);
  printmatrix("cputemp2", cputemp2);

  cv::solve(cputemp3, cputemp2, cputemp4, cv::DECOMP_SVD);
  printmatrix("cputemp4", cputemp4);

  temp4->upload(cputemp4);

  std::cout <<  "gain = temp4.t()" << std::endl;

  // K(k)
  //gain = temp4.t();
  cv::cuda::transpose(*temp4, *gain);

  gain->download(temp);
  printmatrix("gain", temp);

  std::cout <<  "measurementMatrix_temp = measurementMatrix*statePre [measurementMatrix_temp = H*x'(k)]" << std::endl;
  // temp5 = z(k) - H*x'(k)
  //temp5 = measurement - measurementMatrix*statePre;
  measurementMatrix->download(temp);
  printmatrix("measurementMatrix", temp);
  statePre->download(temp);
  printmatrix("statePre", temp);

  cv::cuda::gemm(*measurementMatrix, *statePre, 1, cv::Mat() , 0 , *measurementMatrix_temp);
  measurementMatrix_temp->download(temp);
  printmatrix("measurementMatrix_temp", temp);

  std::cout <<  "temp5 = measurement - measurementMatrix_temp [temp5 = z(k) - measurementMatrix_temp]" << std::endl;
  measurement.download(temp);
  printmatrix("measurement", temp);

  cv::cuda::subtract(measurement, *measurementMatrix_temp, *temp5);
  temp5->download(temp);
  printmatrix("temp5", temp);



  // x(k) = x'(k) + K(k)*temp5
  //statePost = statePre + gain*temp5;
  //cv::cuda::multiply(gain, temp5, gain_temp);
  std::cout <<  "gain_temp = gain*temp5 [gain_temp = K(k)*temp5]" << std::endl;
  gain->download(temp);
  printmatrix("gain", temp);
  temp5->download(temp);
  printmatrix("temp5", temp);

  cv::cuda::gemm(*gain, *temp5, 1, cv::Mat() , 0 , *gain_temp);
  gain_temp->download(temp);
  printmatrix("gain_temp", temp);

  std::cout <<  "statePost = statePre + gain_temp [x(k) = x'(k) + gain_temp]" << std::endl;
  statePre->download(temp);
  printmatrix("statePre", temp);

  cv::cuda::add(*statePre, *gain_temp, *statePost);
  statePost->download(temp);
  printmatrix("statePost", temp);


  // P(k) = P'(k) - K(k)*temp2
  //errorCovPost = errorCovPre - gain*temp2;
  //cv::cuda::multiply(gain, temp2, gain_temp);
  std::cout <<  "gain_temp =  K(k)*temp2 [gain_temp = K(k)*temp2]" << std::endl;
  gain->download(temp);
  printmatrix("gain", temp);
  temp2->download(temp);
  printmatrix("temp2", temp);
  cv::cuda::gemm(*gain, *temp2, 1, cv::Mat() , 0 , *gain_temp);
  gain_temp->download(temp);
  printmatrix("gain_temp", temp);

  std::cout <<  "errorCovPost = errorCovPre - gain_temp [P(k) = P'(k) - gain_temp]" << std::endl;
  errorCovPre->download(temp);
  printmatrix("errorCovPre", temp);
  cv::cuda::subtract(*errorCovPre, *gain_temp, *errorCovPost);
  errorCovPost->download(temp);
  printmatrix("errorCovPost", temp);


  }
