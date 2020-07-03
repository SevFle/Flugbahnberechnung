#ifndef __MAIN_H
#define __MAIN_H

#include "headers/GlobalObjects.h"
#include "headers/camera_manager.h"
#include <thread>

using namespace nmsp_GlobalObjects;
using namespace nmsp_camera_unmanaged;

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

namespace frm_Camera_Calibration_Crop
  {
  class C_frm_Camera_Calibration_Crop;
  }using namespace frm_Camera_Calibration_Crop;

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

    c_camera_unmanaged*                 Camera_manager;

    C_frm_Main*                         frm_Main;
    C_frm_Object_Calibration*           frm_Object_Calibration;
    C_frm_Object_Tracking*              frm_Object_Tracking;

    C_frm_Camera_Calibration*           frm_Camera_Calibration;
    C_frm_Camera_Calibration_Crop*      frm_Camera_Calibration_Crop;

    C_frm_Camera_Positioning*           frm_Camera_Positioning;
    C_frm_Camera_Positioning_Pose*      frm_Camera_Positioning_Pose;

    C_GlobalObjects*                    GlobalObjects;
    };
  }

#include "headers/frm_main.h"
#include "headers/frm_object_calibration.h"
#include "headers/frm_object_tracking.h"
#include "headers/frm_camera_calibration.h"
#include "headers/frm_camera_calibration_crop.h"
#include "headers/frm_camera_positioning.h"
#include "headers/frm_camera_positioning_pose.h"


#endif // C_MAIN_H

