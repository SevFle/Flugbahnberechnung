#ifndef __cudaKalman_H
#define __cudaKalman_H



#include <math.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <stdio.h>
#include <iostream>

//for __syncthreads()
#ifndef __CUDACC__
#define __CUDACC__
#endif
#include <device_functions.h>
#include <device_launch_parameters.h>



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



    float* statePre_devPtr;               //!< dynamParams
    float* statePost_devPtr;              //!< dynamParams
    float* transitionMatrix_devPtr;       //!< dynamParams*dynamParams
    float* controlMatrix_devPtr;          //!< dynamParams*controlParams
    float* controlValue_devPtr;          //!< controlParams
    float* measurementMatrix_devPtr;      //!< measureParams*dynamParams
    float* measurement_devPtr;            //!< measureParams
    float* processNoiseCov_devPtr;        //!< dynamParams*dynamParams (Q)
    float* measurementNoiseCov_devPtr;    //!< measureParams*measureParams (R)
    float* errorCovPre_devPtr;            //!< dynamParams*dynamParams
    float* gain_devPtr;                   //!< dynamParams*measureParams
    float* errorCovPost_devPtr;           //!< dynamParams*dynamParams

    // temporary matrices
    float* temp1_devPtr;                  //!< dynamParams*dynamParams
    float* temp2_devPtr;                  //!< measureParams*dynamParams
    float* temp3_devPtr;                  //!< measureParams*measureParams
    float* temp3_inv_devPtr;              //!< measureParams*measureParams
    float* temp4_devPtr;                  //!< measureParams*dynamParams
    float* temp5_devPtr;                  //!< measureParams
    float* temp6_devPtr;                  //!< dynamParams * dynamParams
    float* temp7_devPtr;                  //!< measureParams * measureParams
    float* temp8_devPtr;                  //!< measureParams * 1
    float* temp9_devPtr;                  //!< dynamParams*1
    float* temp10_devPtr;                 //!< dynamParams*dynamParams
    float* temp11_devPtr;                 //!< dynamParams*dynamParams
    int dynamParams;
    int measureParams;
    int controlParams;


  __host__  void h_predict          (float dt);
  __host__  void h_correct          (float dt);
  __host__  int h_firstMeasurement  ();

  private:
  __host__  int d_correct         ();
  __host__  int d_predict         ();
  __host__   void init             ();
  __host__   bool initMatrix       (int dynamParams, int measureParams, int controlParams);
  __host__   void deinit           ();
  __host__   bool deleteMatrix     ();
  __host__   int set_identity      (int dynamParams, int measureParams, int controlParams);
  __host__   void print_matrix     (const float *A, int nr_rows_A, int nr_cols_A, std::string Name) ;


    };//class C_cudaKalman
  }

#endif
