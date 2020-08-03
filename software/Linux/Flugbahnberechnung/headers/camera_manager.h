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
 cv::Mat img;
 double timestamp = 0;
 cv::Mat gray;
 cv::Mat final;
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
    pthread_t*                    pipelineCam;
    pthread_t*                    simpleCam;

    int                           camera_id;
    int                           absCameras;
    int                           frameWidth;
    int                           frameHeight;
    int                           arrActiveCameras[4];
    float                         SquareSize;
    bool                          calibration_done;


    /********************************************************* Öffentliche Klassenmethoden*******************************************************/
    public:
    void mvVecCamera2Temp         (std::vector<int> vecCamOrder);
    void mvTemp2VecCamera         (std::vector<Camera::C_Camera2*> temp_CameraVector);

    void openCameras              ();
    void closeCameras             ();

    void calibrateSingleCamera    (int current_camera_id, int absCornersWidth, int absCornersHeight, int absBoardImg );
    void calibrate_stereo_camera  (int current_camera_id, int absCornersWidth, int absCornersHeight, int absBoardImg);
    void sm_object_tracking       ();

    void calculate_camera_pose    (int camera1, int camera2, cv::Vec3d T, cv::Mat R);

    void getDeviceList            ();

    void pipelineTracking         (std::vector<cv::VideoCapture*> &camera_vector, tbb::concurrent_bounded_queue<Payload*> &que);


    /******************************************************* Private Klassenmethoden***************************************************************/
    private:
    void start_camera_thread ();
    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged
#endif
