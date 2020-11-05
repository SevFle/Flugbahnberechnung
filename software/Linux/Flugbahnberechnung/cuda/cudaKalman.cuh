#ifndef __cudaKalman_H
#define __cudaKalman_H



#include <math.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>


#define IDX2C(i,j,ld) (((j)*(ld))+(i))


namespace cudaKalman
  {
  class C_cudaKalman
    {
  public:
    C_cudaKalman();
    ~C_cudaKalman();

    cudaError_t            cudaStat;
    cublasStatus_t         stat;
    cublasHandle_t         handle;
    cudaStream_t           streamkalman;

    float* statePre;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
    float* statePost;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    float* transitionMatrix;   //!< state transition matrix (A)
    float* controlMatrix;      //!< control matrix (B) (not used if there is no control)
    float* controlVector;      //!< control vector (u) (not used if there is no control)
    float* measurementMatrix;  //!< measurement matrix (H)
    float* measurement;       //!< measurement (x)
    float* processNoiseCov;    //!< process noise covariance matrix (Q)
    float* measurementNoiseCov;//!< measurement noise covariance matrix (R)
    float* errorCovPre;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
    float* gain;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
    float* errorCovPost;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

    // temporary matrices
    float* temp1;
    float* temp2;
    float* temp3;
    float* temp4;
    float* temp5;
    float* transitionMatrix_temp;
    float* controlMatrix_temp;
    float* measurementMatrix_temp;
    float* gain_temp;


    float* statePre_devPtr;           //!< predicted state (x'(k)): x(k)=A*x(k-1)+B*u(k)
    float* statePost_devPtr;          //!< corrected state (x(k)): x(k)=x'(k)+K(k)*(z(k)-H*x'(k))
    float* transitionMatrix_devPtr;   //!< state transition matrix (A)
    float* controlMatrix_devPtr;      //!< control matrix (B) (not used if there is no control)
    float* measurementMatrix_devPtr;  //!< measurement matrix (H)
    float* processNoiseCov_devPtr;    //!< process noise covariance matrix (Q)
    float* measurementNoiseCov_devPtr;//!< measurement noise covariance matrix (R)
    float* errorCovPre_devPtr;        //!< priori error estimate covariance matrix (P'(k)): P'(k)=A*P(k-1)*At + Q)*/
    float* gain_devPtr;               //!< Kalman gain matrix (K(k)): K(k)=P'(k)*Ht*inv(H*P'(k)*Ht+R)
    float* errorCovPost_devPtr;       //!< posteriori error estimate covariance matrix (P(k)): P(k)=(I-K(k)*H)*P'(k)

    // temporary matrices
    float* temp1_devPtr;
    float* temp2_devPtr;
    float* temp3_devPtr;
    float* temp4_devPtr;
    float* temp5_devPtr;
    float* transitionMatrix_temp_devPtr;
    float* controlMatrix_temp_devPtr;
    float* measurementMatrix_temp_devPtr;
    float* gain_temp_devPtr;


    void correct            ();
    void predict            ();
    void firstMeasurement   ();

    void init               ();
    bool initMatrix         (int dynamParams, int measureParams, int controlParams);
    void deinit             ();
    bool deleteMatrix       ();
    };//class C_cudaKalman
  }

#endif
