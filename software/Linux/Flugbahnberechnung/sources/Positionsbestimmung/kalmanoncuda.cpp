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


void C_kalmanOnCuda::init(int DP, int MP, int CP, int type)
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
  this->temp2->upload(temp);

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
  this->temp3->create(MP, MP, type);
  this->temp4->create(MP, DP, type);
  this->temp5->create(MP, 1, type);
  }

const cv::cuda::GpuMat& C_kalmanOnCuda::predict(const cv::cuda::GpuMat& control)
  {
  cv::Mat temp;
  // update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  cv::cuda::gemm(*transitionMatrix, *statePost, 1, cv::cuda::GpuMat() , 0 , *statePre);

      statePre->download(temp);
      std::cout << "statePre " << temp << std::endl;

  if( !control.empty() )
    {
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    cv::cuda::gemm(*controlMatrix, control, 1, cv::cuda::GpuMat() , 0 , *controlMatrix_temp);
    //cv::cuda::multiply(controlMatrix,control, controlMatrix_temp);
        controlMatrix_temp->download(temp);
        std::cout << "controlMatrix_temp " << temp << std::endl;

    cv::cuda::add(*statePre, *controlMatrix_temp, *statePre);
        statePre->download(temp);
        std::cout << "statePre " << temp << std::endl;
    }
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  cv::cuda::multiply(*transitionMatrix,*errorCovPost, *temp1);
      temp1->download(temp);
      std::cout << "temp1 " << temp << std::endl;


  // P'(k) = temp1*At + Q
  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  cv::cuda::gemm(*temp1, *transitionMatrix, 1, *processNoiseCov, 1, *errorCovPre, cv::GEMM_2_T);
      errorCovPre->download(temp);
      std::cout << "errorCovPre " << temp << std::endl;



  // handle the case when there will be measurement before the next predict->
  statePre->copyTo(*statePost);
  errorCovPre->copyTo(*errorCovPost);

  return *statePre;
  }

const cv::cuda::GpuMat& C_kalmanOnCuda::correct( const cv::cuda::GpuMat& measurement )
  {
  // temp2 = H*P'(k)
     // cv::cuda::multiply(measurementMatrix,errorCovPre, temp2);
      cv::cuda::gemm(*measurementMatrix, *errorCovPre, 1, cv::Mat(), 0, *temp2);
      //cv::cuda::gemm(measurementMatrix, errorCovPre, 1, cv::Mat() , 0 , temp2);
      // temp3 = temp2*Ht + R
      //gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
      cv::cuda::gemm(*temp2, *measurementMatrix, 1, *measurementNoiseCov, 1, *temp3, cv::GEMM_2_T);

      // temp4 = inv(temp3)*temp2 = Kt(k)
      cv::Mat cputemp4;
      cv::Mat cputemp2;
      cv::Mat cputemp3;

      temp3->download(cputemp3);
      temp2->download(cputemp2);
      temp4->download(cputemp4);

      cv::solve(cputemp3, cputemp2, cputemp4, cv::DECOMP_SVD);

      temp4->upload(cputemp4);

      // K(k)
      //gain = temp4.t();
      cv::cuda::transpose(*temp4, *gain);

      // temp5 = z(k) - H*x'(k)
      //temp5 = measurement - measurementMatrix*statePre;
      //cv::cuda::multiply(measurementMatrix,statePre, temp1);
      //cv::multiply(measurementMatrix, statePre, measurementMatrix_temp);
      cv::cuda::gemm(*measurementMatrix, *statePre, 1, cv::Mat() , 0 , *measurementMatrix_temp);

      cv::cuda::subtract(measurement, *measurementMatrix_temp, *temp5);


      // x(k) = x'(k) + K(k)*temp5
      //statePost = statePre + gain*temp5;
      //cv::cuda::multiply(gain, temp5, gain_temp);
      cv::cuda::gemm(*gain, *temp5, 1, cv::Mat() , 0 , *gain_temp);

      cv::cuda::add(*statePre, *gain_temp, *statePost);

      // P(k) = P'(k) - K(k)*temp2
      //errorCovPost = errorCovPre - gain*temp2;
      //cv::cuda::multiply(gain, temp2, gain_temp);
      cv::cuda::gemm(*gain, *temp2, 1, cv::Mat() , 0 , *gain_temp);

      cv::cuda::subtract(*errorCovPre, *gain_temp, *errorCovPost);

      return *statePost;
  }


