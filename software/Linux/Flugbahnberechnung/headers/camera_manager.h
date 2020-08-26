#ifndef __Camera_Manager_H
#define __Camera_Manager_H



/************************************************************ Includes *******************************************************************/


#include <pthread.h>
#include <thread>
#include <memory>

#include "headers/camera2.h"
#include "headers/loadmanager.h"
#include "headers/savemanager.h"
#include "headers/imagefilter.h"
#include "headers/trackingManager.h"
#include "headers/object.h"
#include "headers/GlobalObjects.h"
#include "gst/gst.h"


#if !defined(Q_MOC_RUN)
#include <tbb/tbb.h>
#include "tbb/pipeline.h"
#include "tbb/concurrent_queue.h"
#endif



using namespace Camera;
using namespace trackingManager;
using namespace object;
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
      milliseconds executionTime[8];
      std::chrono::nanoseconds                                frametime;

      Clock::time_point start;
      Clock::time_point timestamp;
      Clock::time_point end;
      Clock::time_point fpsStart;
      Clock::time_point fpsEnd;


     cv::Mat                                cpuSrcImg           [payloadSize];
     cv::Mat                                cpuUndistortedImg   [payloadSize];
     cv::Mat                                cpuFinalImg         [payloadSize];
     cv::Mat                                cpuGrayImg          [payloadSize];
     cv::Mat                                cpuGrayImg2          [payloadSize];
     cv::Mat                                cpuConturedImg      [payloadSize];

     cv::cuda::GpuMat                       gpuUndistortedImg   [payloadSize];
     Camera::C_Camera2::S_filterProperties  Filter              [payloadSize];

     S_Positionsvektor                      objektVektor;
     S_Positionsvektor                      Richtungsvektoren   [payloadSize];
     int                                    cameraID            [payloadSize];
     int                                    ist_X               [payloadSize];
     int                                    ist_Y               [payloadSize];
     int                                    pred_X              [payloadSize];
     int                                    pred_Y              [payloadSize];
     int                                    radius              [payloadSize];
     bool                                   found = false;
     int                                    fps = 0;
     double                                 timestampT0 = 0;
     double                                 dTimestamp = 0;
     int                                    offset              [payloadSize];
     int                                    queBuffer;

    };
    struct S_filterflags
      {
      bool undistordActive  = false;
      bool openActive       = false;
      bool closeActive      = false;
      bool filterActive     = false;
      bool objectDetectionActive   = false;
      bool roiAdjustmentActive = false;
      bool trackingActive         = false;
      bool erosionActive     = false;
      bool dilationActive     = false;
      bool gaussianActive   = false;
      bool morphActive      = false;
      bool bilateralActive  = false;


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
      bool getTracking() const;
      void setTracking(bool value);
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
    std::vector<Camera::C_Camera2*>         vecCameras;
    std::string                            test;


    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    public:
    Savemanager::c_SaveManager*             saveManager;
    LoadManager::C_LoadManager*             loadManager;
    trackingManager::C_trackingManager*     trackingManager;
    cv::Mat                                 arrImgShow[payloadSize];
    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    C_GlobalObjects*                        globalObjects;
    imagefilter::C_ImageFilter*             ImageFilter;
    thread*                                 camPipeline;
    thread*                                 camPositioning;
    std::mutex*  restrict                   lock;
    Clock::time_point                       timestampTm1;

    public:
    tbb::concurrent_bounded_queue<CameraManager::S_pipelinePayload*>*  pipelineQue;
    tbb::concurrent_bounded_queue<CameraManager::S_threadPayload*>*                    threadQue;

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
    int                           cntPipeline;
    volatile bool                 calibrationDone;
    volatile bool                 positioningDone;
    volatile bool                 pipelineDone;
    bool                          flush;
    bool                          flushComplete;


    /********************************************************* Öffentliche Klassenmethoden*******************************************************/
    public:

    bool openCameras              ();
    bool closeCameras             ();
    void mvVecCamera2Temp         (std::vector<int> vecCamOrder);
    void calibrateSingleCamera    (int current_camera_id,
                                   int absCornersWidth,
                                   int absCornersHeight,
                                   int absBoardImg,
                                   float absCornerLength);

    void calibrate_stereo_camera  (int current_camera_id,
                                   int absCornersWidth,
                                   int absCornersHeight,
                                   int absBoardImg,
                                   float absCornerLength);


    bool startThreadCameraPositioning();
    bool stopThreadCameraPositioning();
    bool startPipelineTracking  (bool undistordActive, bool openActive, bool closeActive,  bool filterActive, bool objectDetectionActive,  bool roiAdjustmentActive, bool trackingActive);
    bool stopPipelineTracking();
    bool pollPipeline               (CameraManager::S_pipelinePayload* arg1);



    void calculate_camera_pose    (int camera1, int camera2, cv::Vec3d T, cv::Mat R);

    void getDeviceList            ();


    /******************************************************* Private Klassenmethoden***************************************************************/
  private:
    void start_camera_thread                ();
    void loadCameras                        ();
    void pipelineTracking                   (std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_pipelinePayload*> *que);
    void threadCameraPositioning(std::vector<Camera::C_Camera2*> vecCameras, tbb::concurrent_bounded_queue<S_threadPayload*> *que);
    static void *threadHelper                 (void* This);
    static void *pipelineHelper(void* This);

    void mvTemp2VecCamera                   (std::vector<Camera::C_Camera2*> temp_CameraVector);
    void smTracking                         (S_pipelinePayload* payload);
    bool getObjectPosition2D                (trackingManager::S_trackingPayload& trackingPayload);
    void helper() const;
    /******************************************************* Getter-Setter Klassenmethoden***************************************************************/
  public:
    std::vector<cv::Mat*> getVecImgShow    () const;
    void setVecImgShow                      (const std::vector<cv::Mat*> &value);

    bool getCalibrationDone                 () const;
    void setCalibrationDone                 (volatile bool value);

    int getArrActiveCameras                 (int position) const;
    void setArrActiveCameras                (int value, int position);

    bool getPipelineDone                    () const;
    void setPipelineDone                    (volatile bool value);

    bool getPositioningDone                 () const;
    void setPositioningDone                 (volatile bool value);

    S_filterflags *getFilterFlags() const;
    void setFilterFlags(S_filterflags *value);
    std::mutex *getLock() const;
    void setLock(std::mutex *value);
    bool getFlush() const;
    void setFlush(bool value);
    };// c_camera_unmanaged
}//nmsp_c_camera_unmanaged
#endif
