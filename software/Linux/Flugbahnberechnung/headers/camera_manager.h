#ifndef __Camera_Manager_H
#define __Camera_Manager_H



/************************************************************ Includes *******************************************************************/


#include <pthread.h>
#include <thread>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

//#include "headers/camera.h"
#include "camera2.h"
#include "loadmanager.h"
#include "savemanager.h"
#include "imagefilter.h"

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
    struct S_Payload
    {
     cv::Mat                                cpuSrcImg           [payloadSize];
     cv::Mat                                cpuUndistortedImg   [payloadSize];
     cv::Mat                                cpuHSVImg           [payloadSize];
     cv::Mat                                cpuConturedImg      [payloadSize];

     cv::cuda::GpuMat                       gpuUndistortedImg   [payloadSize];
     cv::Mat                                gray                [payloadSize];
     cv::Mat                                final               [payloadSize];
     Camera::C_Camera2::S_filterProperties  Filter              [payloadSize];

     S_Positionsvektor                      objektVektor;
     S_Positionsvektor*                     Richtungsvektoren   [payloadSize];
     int                                    cameraID            [payloadSize];
     int                                    ist_X               [payloadSize];
     int                                    ist_Y               [payloadSize];
     int                                    radius              [payloadSize];
     bool                                   found = false;
     double                                 fps = 0;
     double                                 frametime = 0;
     double                                 timestamp = 0;
     int                                    offset              [payloadSize];
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


    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    public:
    Savemanager::c_SaveManager*             saveManager;
    LoadManager::C_LoadManager*             loadManager;
    trackingManager::C_trackingManager*     trackingManager;
    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    C_GlobalObjects*                        globalObjects;
    imagefilter::C_ImageFilter*             ImageFilter;
    pthread_t*                              camPipeline;
    pthread_t*                              camSimple;
    pthread_t*                              camPositioning;
    pthread_mutex_t*  restrict              lock;
    std::vector<cv::Mat*>                   vecImgShow;
    tbb::concurrent_bounded_queue<S_Payload*>*  Que;
    S_Payload*                              pData;

    int                           camera_id;
    int                           frameWidth;
    int                           frameHeight;
    int                           arrActiveCameras[4];
    int                           cntPipeline;
    volatile bool                 calibrationDone;
    volatile bool                 positioningDone;
    volatile bool                 pipelineDone;


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
    bool startPipelineTracking();
    bool stopPipelineTracking();
    bool pollPipeline               (CameraManager::S_Payload* payload);



    void calculate_camera_pose    (int camera1, int camera2, cv::Vec3d T, cv::Mat R);

    void getDeviceList            ();


    /******************************************************* Private Klassenmethoden***************************************************************/
  private:
    void start_camera_thread                ();
    void loadCameras                        ();
    void pipelineTracking                   (std::vector<Camera::C_Camera2*> vecCamera, tbb::concurrent_bounded_queue<S_Payload*> &que);
    static void* threadCameraPositioning    (void *This);
    static void *pipelineHelper             (void* This);
    void threadCameraSimple                 ();
    void mvTemp2VecCamera                   (std::vector<Camera::C_Camera2*> temp_CameraVector);
    void smTracking                         (S_Payload* payload);
    bool getObjectPosition2D                (trackingManager::S_trackingPayload& trackingPayload);
    /******************************************************* Getter-Setter Klassenmethoden***************************************************************/
  public:
    std::vector<cv::Mat *> getVecImgShow    () const;
    void setVecImgShow                      (const std::vector<cv::Mat *> &value);

    bool getCalibrationDone                 () const;
    void setCalibrationDone                 (volatile bool value);

    int getArrActiveCameras                 (int position) const;
    void setArrActiveCameras                (int value, int position);

    bool getPipelineDone                    () const;
    void setPipelineDone                    (volatile bool value);

    bool getPositioningDone                 () const;
    void setPositioningDone                 (volatile bool value);

    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged
#endif
