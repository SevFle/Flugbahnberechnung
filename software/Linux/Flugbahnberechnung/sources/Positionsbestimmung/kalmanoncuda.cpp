#include "headers/Positionsbestimmung/kalmanoncuda.h"
using namespace kalmanOnCuda;

C_kalmanOnCuda::C_kalmanOnCuda()
  {

  }
C_kalmanOnCuda::C_kalmanOnCuda(int dynamParams, int measureParams, int controlParams, int type)
  {
  init(dynamParams, measureParams, controlParams, type);
  }
C_kalmanOnCuda::~C_kalmanOnCuda()
  {

  }


void C_kalmanOnCuda::init(int DP, int MP, int CP, int type)
  {
  CV_Assert( DP > 0 && MP > 0 );
  CV_Assert( type == CV_32F || type == CV_64F );
  CP = std::max(CP, 0);

  cv::Mat temp;
  temp = cv::Mat::zeros(DP, 1, type);
  statePre.upload(temp);
  statePost.upload(temp);

  temp = cv::Mat::eye(DP, DP, type);
  transitionMatrix.upload(temp);
  transitionMatrix_temp.upload(temp);
  processNoiseCov.upload(temp);

  temp = cv::Mat::zeros(MP, DP, type);
  measurementMatrix.upload(temp);
  measurementMatrix_temp.upload(temp);

  temp = cv::Mat::eye(MP, MP, type);
  measurementNoiseCov.upload(temp);

  temp = cv::Mat::zeros(DP, DP, type);
  errorCovPre.upload(temp);
  errorCovPost.upload(temp);

  temp = cv::Mat::zeros(DP, MP, type);
  gain.upload(temp);
  gain_temp.upload(temp);
  if( CP > 0 )
    {
    temp = cv::Mat::zeros(DP, CP, type);
    controlMatrix.upload(temp);
    controlMatrix_temp.upload(temp);
    }

  else
      controlMatrix.release();

  temp1.create(DP, DP, type);
  temp2.create(MP, DP, type);
  temp3.create(MP, MP, type);
  temp4.create(MP, DP, type);
  temp5.create(MP, 1, type);
  }

const cv::cuda::GpuMat& C_kalmanOnCuda::predict(const cv::cuda::GpuMat& control)
  {
  // update the state: x'(k) = A*x(k)
  //statePre = transitionMatrix*statePost;
  //cv::cuda::multiply(transitionMatrix, statePost, statePre);
  cv::cuda::gemm(transitionMatrix, statePost, 1, cv::Mat() , 0 , statePre);

  if( !control.empty() )
    {
    // x'(k) = x'(k) + B*u(k)
    //statePre += controlMatrix*control;
    cv::cuda::gemm(controlMatrix, control, 1, cv::Mat() , 0 , controlMatrix_temp);
    //cv::cuda::multiply(controlMatrix,control, controlMatrix_temp);

    cv::cuda::add(statePre, controlMatrix_temp, statePre);
    }
  // update error covariance matrices: temp1 = A*P(k)
  //temp1 = transitionMatrix*errorCovPost;
  cv::cuda::multiply(transitionMatrix,errorCovPost, temp1);

  // P'(k) = temp1*At + Q
  //gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, GEMM_2_T);
  cv::cuda::gemm(temp1, transitionMatrix, 1, processNoiseCov, 1, errorCovPre, cv::GEMM_2_T);

  // handle the case when there will be measurement before the next predict.
  statePre.copyTo(statePost);
  errorCovPre.copyTo(errorCovPost);

  return statePre;
  }

const cv::cuda::GpuMat& C_kalmanOnCuda::correct( const cv::cuda::GpuMat& measurement )
{

    // temp2 = H*P'(k)
   // cv::cuda::multiply(measurementMatrix,errorCovPre, temp2);
    cv::cuda::gemm(measurementMatrix, errorCovPre, 1, cv::Mat(), 0, temp2);
    //cv::cuda::gemm(measurementMatrix, errorCovPre, 1, cv::Mat() , 0 , temp2);
    // temp3 = temp2*Ht + R
    //gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, GEMM_2_T);
    cv::cuda::gemm(temp2, measurementMatrix, 1, measurementNoiseCov, 1, temp3, cv::GEMM_2_T);

    // temp4 = inv(temp3)*temp2 = Kt(k)
    cv::Mat cputemp4;
    cv::Mat cputemp2;
    cv::Mat cputemp3;

    temp3.download(cputemp3);
    temp2.download(cputemp2);
    temp4.download(cputemp4);

    cv::solve(cputemp3, cputemp2, cputemp4, cv::DECOMP_SVD);

    temp4.upload(cputemp4);

    // K(k)
    //gain = temp4.t();
    cv::cuda::transpose(temp4, gain);

    // temp5 = z(k) - H*x'(k)
    //temp5 = measurement - measurementMatrix*statePre;
    //cv::cuda::multiply(measurementMatrix,statePre, temp1);
    //cv::multiply(measurementMatrix, statePre, measurementMatrix_temp);
    cv::cuda::gemm(measurementMatrix, statePre, 1, cv::Mat() , 0 , measurementMatrix_temp);

    cv::cuda::subtract(measurement, measurementMatrix_temp, temp5);


    // x(k) = x'(k) + K(k)*temp5
    //statePost = statePre + gain*temp5;
    //cv::cuda::multiply(gain, temp5, gain_temp);
    cv::cuda::gemm(gain, temp5, 1, cv::Mat() , 0 , gain_temp);

    cv::cuda::add(statePre, gain_temp, statePost);

    // P(k) = P'(k) - K(k)*temp2
    //errorCovPost = errorCovPre - gain*temp2;
    //cv::cuda::multiply(gain, temp2, gain_temp);
    cv::cuda::gemm(gain, temp2, 1, cv::Mat() , 0 , gain_temp);

    cv::cuda::subtract(errorCovPre, gain_temp, errorCovPost);

    return statePost;
}


