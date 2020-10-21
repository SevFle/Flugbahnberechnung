#ifndef __Kalmanfilter_H
#define __Kalmanfilter_H
#include "headers/Positionsbestimmung/kalmanoncuda.h"

namespace kalmanFilter
  {
  class C_kalmanFilter
    {
    protected:
    C_kalmanFilter ();
    ~C_kalmanFilter ();

    private:
    kalmanOnCuda::C_kalmanOnCuda* kalmanOnCuda;

  public:
    cv::Mat* statePre;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
    cv::Mat* statePost;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    cv::Mat* transitionMatrix;   //!< state transition matrix (A)
    cv::Mat* controlMatrix;      //!< control matrix (B) (not used if there is no control)
    cv::Mat* measurementMatrix;  //!< measurement matrix (H)
    cv::Mat* processNoiseCov;    //!< process noise covariance matrix (Q)
    cv::Mat* measurementNoiseCov;//!< measurement noise covariance matrix (R)
    cv::Mat* errorCovPre;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
    cv::Mat* gain;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
    cv::Mat* errorCovPost;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)



    void create(int dynamParams, int measureParams, int controlParams, int type);






    private:
    void init();

    public:
    };
  }
#endif
