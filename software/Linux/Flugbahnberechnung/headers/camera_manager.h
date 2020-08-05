#ifndef __Camera_Manager_H
#define __Camera_Manager_H


/************************************************************ Includes *******************************************************************/

#include "tbb/pipeline.h"
#include "tbb/concurrent_queue.h"

#include <pthread.h>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

//#include "headers/camera.h"
#include "camera2.h"
#include "loadmanager.h"
#include "savemanager.h"
#include "imagefilter.h"

#include "headers/tracking.h"
#include "headers/object.h"
#include "headers/GlobalObjects.h"
#include "gst/gst.h"

using namespace Camera;
using namespace tracking;
using namespace object;
using namespace posen;
using namespace GlobalObjects;

struct S_Payload
{
 cv::Mat cpuSrcImg;
 cv::Mat cpuUndistortedImg;
 cv::Mat cpuHSVImg;
 cv::Mat cpuConturedImg;

 cv::cuda::GpuMat gpuUndistortedImg;
 double timestamp = 0;
 cv::Mat gray;
 cv::Mat final;
 Camera::C_Camera2::S_filterProperties Filter;

 int cameraID = 0;
 int offset[];
};





namespace CameraManager
  {
  class C_CameraManager
    {
    public:
    /*************************************************************** Konstruktoren *************************************************************/
    C_CameraManager ( C_GlobalObjects* GlobalObjects);
    /*************************************************************** Destruktor ****************************************************************/
    ~C_CameraManager ();

    typedef void * (*THREADFUNCPTR)(void *);
    /**************************************************** Öffentliche Klassenobjekte ********************************************************/
    public:
    std::vector<Camera::C_Camera2*>        vecCameras;


    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    public:

    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    C_GlobalObjects*              GlobalObjects;
    Savemanager::c_SaveManager*   SaveManager;
    LoadManager::C_LoadManager*   Loadmanager;
    imagefilter::C_ImageFilter*   ImageFilter;
    pthread_t*                    camPipeline;
    pthread_t*                    camSimple;
    pthread_t*                    camPositioning;
    pthread_mutex_t*  restrict    lock;
    std::vector<cv::Mat*>         vecImgShow;
    int                           camera_id;
    int                           absCameras;
    int                           frameWidth;
    int                           frameHeight;
    int                           arrActiveCameras[4];
    int                           cntPipeline;
    float                         SquareSize;
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
                                   int absCornerLength);

    void calibrate_stereo_camera  (int current_camera_id,
                                   int absCornersWidth,
                                   int absCornersHeight,
                                   int absBoardImg,
                                   int absCornerLength);

    bool startThreadCameraPositioning();
    bool stopThreadCameraPositioning();
    bool startPipelineTracking();
    bool stopPipelineTracking();

    void sm_object_tracking       ();

    void calculate_camera_pose    (int camera1, int camera2, cv::Vec3d T, cv::Mat R);

    void getDeviceList            ();



    /******************************************************* Private Klassenmethoden***************************************************************/
    std::vector<cv::Mat *> getVecImgShow() const;
    void setVecImgShow(const std::vector<cv::Mat *> &value);

    bool getCalibrationDone() const;
    void setCalibrationDone(volatile bool value);


  private:
    void start_camera_thread ();
    void pipelineTracking(std::vector<Camera::C_Camera2*> vecCamera, tbb::concurrent_bounded_queue<S_Payload*> &que);
   static void* threadCameraPositioning  (void *This);
    void threadCameraSimple();
    void mvTemp2VecCamera         (std::vector<Camera::C_Camera2*> temp_CameraVector);

    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged
#endif
