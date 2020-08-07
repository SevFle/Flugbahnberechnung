#include "headers/Main.h"

using namespace Main;

C_Main::C_Main(C_GlobalObjects* GlobalObjects)
  {
  this->cameraManager = new C_CameraManager(GlobalObjects);

  this->frm_Main = new C_frm_Main(GlobalObjects, this);
  this->frm_Main->show();

  this->frm_Camera_Calibration          = new C_frm_Camera_Calibration(GlobalObjects, this);
  this->frm_Camera_Calibration_Crop     = new C_frm_Camera_Calibration_Crop(GlobalObjects, this);

  this->frm_Camera_Positioning          = new C_frm_Camera_Positioning(GlobalObjects, this);
  this->frm_Camera_Positioning_Pose     = new C_frm_Camera_Positioning_Pose(GlobalObjects, this);

  this->frm_Object_Calibration          = new C_frm_Object_Calibration(GlobalObjects, this);
  this->frm_Object_Tracking             = new C_frm_Object_Tracking(GlobalObjects, this);

  this->GlobalObjects                   = GlobalObjects;
}



C_Main::~C_Main()
{
    this->GlobalObjects = nullptr;

    delete  (frm_Object_Tracking);
    delete  (frm_Object_Calibration);

    delete  (frm_Camera_Positioning_Pose);
    delete  (frm_Camera_Positioning);


    delete  (frm_Camera_Calibration_Crop);
    delete  (frm_Camera_Calibration);

    delete  (frm_Main);
    delete  (cameraManager);

}


#include "frm_main.cpp"
#include "frm_object_calibration.cpp"
#include "frm_object_tracking.cpp"
#include "frm_camera_calibration.cpp"
#include "frm_camera_calibration_crop.cpp"
#include "frm_camera_positioning.cpp"
#include "frm_camera_positioning_pose.cpp"
