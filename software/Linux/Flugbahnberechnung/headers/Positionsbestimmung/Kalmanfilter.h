#ifndef __Kalmanfilter_H
#define __Kalmanfilter_H
#include "cuda/cudaKalman.cuh"
#include "opencv2/opencv.hpp"
#include <opencv2/video/tracking.hpp>

#define gravity -9.807

namespace kalmanFilter
  {
  class C_kalmanFilter
    {
  public:
    C_kalmanFilter ();
    ~C_kalmanFilter ();

    private:
    cv::KalmanFilter*     kf;
    cv::Mat*               measurement;

    int dynamParams;
    int measureParams;
    int controlParams;
    int type;
  public:
    cv::Mat*               state_pre;
    cv::Mat*               state_post;
  public:
    void init(int dynamParams, int measureParams, int controlParams, int type);
    void predict(float dT);
    void correct(float x, float y, float z);
    void initFirstPosition(float x, float y, float z, float vx, float vy, float vz);
    void reset();
    cv::Scalar getGainMean();
    };
  }
#endif
