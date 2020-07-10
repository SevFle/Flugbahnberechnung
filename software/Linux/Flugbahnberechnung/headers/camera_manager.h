#ifndef __Camera_Manager_H
#define __Camera_Manager_H


/************************************************************ Includes *******************************************************************/

#include "headers/camera.h"
#include "headers/tracking.h"
#include "headers/object.h"
#include "headers/GlobalObjects.h"

namespace std
  {
  class thread;
  }

using namespace std;

using namespace camera;
using namespace tracking;
using namespace object;
using namespace posen;
using namespace GlobalObjects;


namespace nmsp_camera_unmanaged
  {
  class c_camera_unmanaged
    {
    public:
    /*************************************************************** Konstruktoren *************************************************************/
    c_camera_unmanaged ( C_GlobalObjects* GlobalObjects);
    /*************************************************************** Destruktor ****************************************************************/
    ~c_camera_unmanaged ();


    /**************************************************** Öffentliche Klassenobjekte ********************************************************/
    public:
    c_tracking* tracking_thread;

    std::thread* camera_thread;


    /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
    public:
    int cameras_in_use;
    int camera_id;

    int** camera_referrence;

    bool             stop_statemachine;
    bool             load_positioning;
    bool             tracking_active;
  	

    cv::Mat cpu_kalman_filterL;
    cv::Mat cpu_kalman_filterR;
  	
	std::vector<c_camera*> camera_vector;

    /*** Variablen zur Kamerakalibrierung ********************************************************/

    public:
    int   numCornersWidth;
    int   numCornersHeight;
    float SquareSize;
    int   numBoards_imgs;
    bool calibration_done;

    private:
    int Photo_ID;


    /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
    private:
    C_GlobalObjects* GlobalObjects;
    int              current_camera_id;


    /********************************************************* Öffentliche Klassenmethoden*******************************************************/
    public:
    void move_camera_vector2temp (int camera_desired_id, int camera_current_id, std::vector<c_camera*>& temp_CameraVector);
    void move_camera_temp2vector (int cameras_in_use, std::vector<c_camera*> temp_CameraVector);

    void save_camera_calibration (int camera_id);
    void load_camera_calibration (int camera_id);
    void save_camera_positioning (std::vector<int> camera_list) const;
    void load_camera_positioning ();
    void save_camera_cos (int camera_id, C_AbsolutePose& WorldToCam_Param);
    void load_camera_cos (int camera_id, C_AbsolutePose& WorldToCam_Param);

    void load_camera_pipelines(std::vector<std::string> &vec_pipeline);

    void init_camera_vectors ();
    void close_cameras (int cameras_in_use);

    void save_camera_settings (int camera_id);
    void load_camera_settings (int camera_id);

    void calibrate_single_camera (int current_camera_id);
    void calibrate_stereo_camera (int current_camera_id);
    void sm_object_tracking ();

    void calculate_camera_pose(int camera1, int camera2, cv::Vec3d T, cv::Mat R);


    /******************************************************* Private Klassenmethoden***************************************************************/
    private:
    void start_camera_thread ();
    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged
#endif
