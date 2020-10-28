#ifndef C_KALMANONCUDA_H
#define C_KALMANONCUDA_H

#include "opencv2/opencv.hpp"
#include <opencv2/video/tracking.hpp>
#include <opencv4/opencv2/core.hpp>

#define print(string, matrix) std::cout << string << ": " << std::endl << matrix << std::endl;

namespace kalmanOnCuda
  {
  class C_kalmanOnCuda
    {
  public:
    C_kalmanOnCuda();
    C_kalmanOnCuda(int dynamParams, int measureParams, int controlParams, int type);
    ~C_kalmanOnCuda();


    cv::cuda::GpuMat* statePre;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
    cv::cuda::GpuMat* statePost;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    cv::cuda::GpuMat* transitionMatrix;   //!< state transition matrix (A)
    cv::cuda::GpuMat* controlMatrix;      //!< control matrix (B) (not used if there is no control)
    cv::cuda::GpuMat* measurementMatrix;  //!< measurement matrix (H)
    cv::cuda::GpuMat* processNoiseCov;    //!< process noise covariance matrix (Q)
    cv::cuda::GpuMat* measurementNoiseCov;//!< measurement noise covariance matrix (R)
    cv::cuda::GpuMat* errorCovPre;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
    cv::cuda::GpuMat* gain;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
    cv::cuda::GpuMat* errorCovPost;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

    // temporary matrices
    cv::cuda::GpuMat* temp1;
    cv::cuda::GpuMat* temp2;
    cv::cuda::GpuMat* temp3;
    cv::cuda::GpuMat* temp4;
    cv::cuda::GpuMat* temp5;
    cv::cuda::GpuMat* transitionMatrix_temp;
    cv::cuda::GpuMat* controlMatrix_temp;
    cv::cuda::GpuMat* measurementMatrix_temp;
    cv::cuda::GpuMat* gain_temp;

    void init( int dynamParams, int measureParams, int controlParams = 0, int type = CV_32FC1 );
    const cv::cuda::GpuMat& predict(const cv::cuda::GpuMat& control = cv::cuda::GpuMat());
    cv::cuda::GpuMat& correct( const cv::cuda::GpuMat& measurement  = cv::cuda::GpuMat());
    void processKalman(const cv::cuda::GpuMat& control = cv::cuda::GpuMat(), const cv::cuda::GpuMat& measurement = cv::cuda::GpuMat());

    };
  }

#endif // C_KALMANONCUDA_H
