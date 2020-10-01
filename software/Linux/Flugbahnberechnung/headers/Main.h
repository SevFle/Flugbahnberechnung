#ifndef __MAIN_H
#define __MAIN_H

#include "headers/GlobalObjects.h"
#include "headers/camera_manager.h"
#include <thread>

using namespace GlobalObjects;
using namespace CameraManager;

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


namespace Main
  {
  class C_Main
    {
    public:

    C_Main                              (C_GlobalObjects* GlobalObjects);
    ~C_Main                             ();

    C_CameraManager*                    cameraManager;

    C_frm_Main*                         frm_Main;
    C_frm_Object_Calibration*           frm_Object_Calibration;
    C_frm_Object_Tracking*              frm_Object_Tracking;

    C_frm_Camera_Calibration*           frm_Camera_Calibration;

    C_frm_Camera_Positioning*           frm_Camera_Positioning;
    C_frm_Camera_Positioning_Pose*      frm_Camera_Positioning_Pose;

    C_GlobalObjects*                    GlobalObjects;
    std::thread::id MAIN_THREAD_ID;
    };
  }

#include "headers/frm_main.h"
#include "headers/frm_object_calibration.h"
#include "headers/frm_object_tracking.h"
#include "headers/frm_camera_calibration.h"
#include "headers/frm_camera_positioning.h"
#include "headers/frm_camera_positioning_pose.h"


#endif // C_MAIN_H

