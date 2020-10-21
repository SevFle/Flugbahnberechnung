#ifndef __Camera_Manager_H
#define __Camera_Manager_H



/************************************************************ Includes *******************************************************************/


#include <pthread.h>
#include <thread>
#include <memory>

#include "headers/Bildverarbeitung/camera2.h"
#include "headers/Bildverarbeitung//imagefilter.h"
#include "headers/Positionsbestimmung/trackingManager.h"
#include "headers/Etc/GlobalObjects.h"

#include "gst/gst.h"

#include "opencv2/aruco.hpp"
#include <opencv2/aruco/charuco.hpp>
#include <eigen3/Eigen/Core>
#include "headers/Roboter/posen.h"



#if !defined(Q_MOC_RUN)
#include <tbb/tbb.h>
#include "tbb/pipeline.h"
#include "tbb/concurrent_queue.h"
#endif



using namespace Camera;
using namespace trackingManager;
using namespace posen;
using namespace GlobalObjects;





namespace CameraManager
  {
    struct S_threadPayload
    {
     std::vector<cv::Mat*> srcImg;
     int                   queBuffer;

    };
    struct S_pipelinePayload
      {
      milliseconds                          executionTime[7];
      std::chrono::milliseconds             frametime;

      Clock::time_point                     start;
      Clock::time_point                     timestamp;
      Clock::time_point                     end;
      Clock::time_point                     fpsStart;
      Clock::time_point                     fpsEnd;


     cv::Mat                                cpuSrcImg           [payloadSize];
     cv::Mat                                cpuUndistortedImg   [payloadSize];
     cv::Mat                                cpuGrayImg          [payloadSize];
     cv::Mat                                cpuFinal            [payloadSize];

     cv::cuda::GpuMat                       gpuUndistortedImg   [payloadSize];
     cv::cuda::GpuMat                       gpuFinal            [payloadSize];

     Camera::C_Camera2::S_filterProperties  Filter              [payloadSize];

     S_Positionsvektor                      objektVektor;
     S_Positionsvektor                      Richtungsvektoren   [payloadSize];

     float                                  objectVelocity [3];
     float                                  objectAcceleration [3];


     int                                    cameraID            [payloadSize];
     int                                    ist_X               [payloadSize];
     int                                    ist_Y               [payloadSize];
     int                                    pred_X              [payloadSize];
     int                                    pred_Y              [payloadSize];
     int                                    radius              [payloadSize];
     int                                    offset              [payloadSize];
     int                                    queBuffer;

     int                                    fps = 0;
     bool                                   found = false;

    };
    struct S_filterflags
      {
      public:
      //Pipeline modules
      bool undistordActive          = false;
      bool openActive               = false;
      bool closeActive              = false;
      bool filterActive             = false;
      bool objectDetectionActive    = false;
      bool roiAdjustmentActive      = false;
      bool trackingActive           = false;
      //Image Filter
      bool erosionActive            = false;
      bool dilationActive           = false;
      bool gaussianActive           = false;
      bool morphActive              = false;
      bool bilateralActive          = false;


    public:
      bool getUndistordActive() const;
      void setUndistordActive(bool value);
      bool getOpenActive() const;
      void setOpenActive(bool value);
      bool getCloseActive() const;
      void setCloseActive(bool value);
      bool getFilterActive() const;
      void setFilterActive(bool value);
      bool getObjectDetection() const;
      void setObjectDetection(bool value);
      bool getRoiAdjustment() const;
      void setRoiAdjustment(bool value);
      bool getTrackingActive() const;
      void setTrackingActive(bool value);
      bool getErosionActive() const;
      void setErosionActive(bool value);
      bool getDilationActive() const;
      void setDilationActive(bool value);
      bool getGaussianActive() const;
      void setGaussianActive(bool value);
      bool getMorphActive() const;
      void setMorphActive(bool value);
      bool getBilateralActive() const;
      void setBilateralActive(bool value);
      };

    enum roiStatus
      {
      initZone,
      objectFound,
      objectLost,
      };

    class C_CameraManager
      {
    public:
      /*************************************************************** Konstruktoren *************************************************************/
    C_CameraManager                         ( C_GlobalObjects* globalObjects);
    /*************************************************************** Destruktor ****************************************************************/
    ~C_CameraManager                        ();

    typedef void *                          (*THREADFUNCPTR)(void *);
    /**************************************************** Öffentliche Klassenobjekte ********************************************************/
    public:
    std::vector<Camera::C_Camera2*>*         vecCameras;
    trackingManager::C_trackingManager*     trackingManager;
    cv::Mat                                 arrImgShow[payloadSize];
    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    C_GlobalObjects*                        globalObjects;
    imagefilter::C_ImageFilter*             ImageFilter;
    thread*                                 camThread;
    std::mutex*  restrict                   lock;
    posen::C_RelativePose*                  relPose;
    posen::C_AbsolutePose*                  absPose;
    roiStatus*                              roistatus;
    public:
    tbb::concurrent_bounded_queue<CameraManager::S_pipelinePayload*>*  pipelineQue;
    tbb::concurrent_bounded_queue<CameraManager::S_threadPayload*>*    threadQue;

    private:
    S_pipelinePayload*                              payData;
    S_threadPayload*                                tData;
    S_filterflags*                            filterFlags;

    int                           camera_id;
    int                           frameWidth;
    int                           frameHeight;
    int                           initZoneWidth;
    int                           initZoneHeight;
    int                           transferZoneWidth;
    int                           arrActiveCameras[4];
    int                           delta_t;
    int                           deltaT_old;

    public:
    std::atomic<bool>*             calibrationDone;
    std::atomic<bool>*             positioningDone;
    std::atomic<bool>*             pipelineDone;
    std::atomic<bool>*             pipelineFlush;
    std::atomic<bool>*             switchCamForward;
    std::atomic<bool>*             switchCamBackward;


    /********************************************************* Öffentliche Klassenmethoden*******************************************************/
    public:

    bool openCameras              ();
    bool closeCameras             ();
    void mvVecCamera2Temp         (std::vector<int> vecCamOrder);
    void calibrateSingleCamera    (int current_camera_id,
                                   int absCornersWidth,
                                   int absCornersHeight,
                                   int absBoardImg,
                                   float absCornerLength,
                                   double* rms);

    void calibrate_stereo_camera  (int current_camera_id,
                                   int absCornersWidth,
                                   int absCornersHeight,
                                   int absBoardImg,
                                   float absCornerLength);
    void calibrate_stereo_camera_aruco(int current_camera_id, int numImages);

    bool startThreadCameraPositioning();
    bool stopThreadCameraPositioning();
    bool startPipelineTracking  ();
    bool stopPipelineTracking();
    bool pollPipeline               (CameraManager::S_pipelinePayload* arg1);



    void calculate_camera_pose    (int camera1, int camera2, cv::Mat* M10, cv::Mat* M20);
    void calculate_camera_pose    (int camera1, int camera2, std::vector<cv::Mat>* M10, std::vector<cv::Mat>* M20);


    void getDeviceList            ();

    void startTracking();
    void stopTracking();



    /******************************************************* Private Klassenmethoden***************************************************************/
  private:
    void initialize                         ();
    void start_camera_thread                ();
    void loadCameras                        ();
    void pipelineTracking                   (std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_pipelinePayload*> *que);
    void threadCameraPositioning(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_threadPayload*> *que);
    static void *threadHelper                 (void* This);
    static void *pipelineHelper(void* This);

    void mvTemp2VecCamera                   (std::vector<Camera::C_Camera2*> temp_CameraVector);
    void helper() const;
    cv::Mat inverseMat(cv::Mat& Matrix);
    void version1(int camera1, int camera2, std::vector<cv::Mat>* M10, std::vector<cv::Mat>* M20);
    void version2(int camera1, int camera2, std::vector<cv::Mat>* M10, std::vector<cv::Mat>* M20);
    void version3(int camera1, int camera2, std::vector<cv::Mat>* M10, std::vector<cv::Mat>* M20);

    /******************************************************* Getter-Setter Klassenmethoden***************************************************************/
  public:
    bool scanChAruco(cv::Mat& image, Camera::C_Camera2& camera, cv::Mat& Pose);

    std::vector<cv::Mat*> getVecImgShow    () const;
    void setVecImgShow                      (const std::vector<cv::Mat*> &value);

    bool getCalibrationDone                 () const;
    void setCalibrationDone                 (volatile bool value);

    void setRoiStatus (roiStatus status);

    int getArrActiveCameras                 (int position) const;
    void setArrActiveCameras                (int value, int position);

    std::atomic<bool>* getPipelineDone                    ();
    std::atomic<bool>* getPositioningDone                 ();

    S_filterflags *getFilterFlags() const;
    void setFilterFlags(S_filterflags *value);
    std::mutex *getLock() const;
    void setLock(std::mutex *value);
    thread *getCamPipeline() const;
    thread *getCamPositioning() const;
    void setDelta_t(int value);
    thread *getCamThread() const;
      };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged
#endif
