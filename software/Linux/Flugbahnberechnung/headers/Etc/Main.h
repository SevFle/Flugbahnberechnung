#ifndef __MAIN_H
#define __MAIN_H

#include "headers/Etc/GlobalObjects.h"
#include "headers/Bildverarbeitung/camera_manager.h"
#include "headers/Roboter/robotmanager.h"
#include <thread>
#include <memory>


using namespace GlobalObjects;
using namespace CameraManager;
using namespace robotManager;

namespace frm_Main
  {
  class C_frm_Main;
  }using namespace frm_Main;

namespace frm_Object_Calibration
  {
  class C_frm_Object_Calibration;
  }using namespace frm_Object_Calibration;

namespace frm_Object_Tracking
  {
  class C_frm_Object_Tracking;
  }using namespace frm_Object_Tracking;

namespace frm_Camera_Calibration
  {
   class C_frm_Camera_Calibration;
  }using namespace frm_Camera_Calibration;

namespace frm_Camera_Positioning
  {
  class C_frm_Camera_Positioning;
  }using namespace frm_Camera_Positioning;

namespace frm_Camera_Positioning_Pose
  {
  class C_frm_Camera_Positioning_Pose;
  }using namespace frm_Camera_Positioning_Pose;

namespace frm_Robot_Calibration
  {
  class C_frm_Robot_Calibration;
  }using namespace frm_Robot_Calibration;



namespace Main
  {
  class C_Main
    {
    public:
    C_Main                              (C_GlobalObjects* GlobalObjects);
    ~C_Main                             ();

    C_CameraManager*                    cameraManager;
    C_robotManager*                     robotManager;

    C_frm_Main*                         frm_Main;
    C_frm_Object_Calibration*           frm_Object_Calibration;
    C_frm_Object_Tracking*              frm_Object_Tracking;

    C_frm_Camera_Calibration*           frm_Camera_Calibration;

    C_frm_Camera_Positioning*           frm_Camera_Positioning;
    C_frm_Camera_Positioning_Pose*      frm_Camera_Positioning_Pose;

    C_frm_Robot_Calibration*            frm_Robot_Calibration;


    C_GlobalObjects*                    GlobalObjects;
    };
  }

#include "headers/Forms/frm_main.h"
#include "headers/Forms/frm_object_calibration.h"
#include "headers/Forms/frm_object_tracking.h"
#include "headers/Forms/frm_camera_calibration.h"
#include "headers/Forms/frm_camera_positioning.h"
#include "headers/Forms/frm_camera_positioning_pose.h"
#include "headers/Forms/frm_robot_calibration.h"

#endif // C_MAIN_H

