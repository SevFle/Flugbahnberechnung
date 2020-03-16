#pragma once

#include "Main.h"

using namespace NmSp_Main;

C_Main::C_Main              (C_GlobalObjects* GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;
  this->camera_managed  = gcnew C_camera_managed(GlobalObjects);

  this->frm_Main                      = gcnew C_frm_Main                        (GlobalObjects, this);
  this->frm_Main->Show();

  this->frm_CameraCalibration_Menu    = gcnew C_frm_CameraCalibration_Menu      (GlobalObjects, this);
  this->frm_CameraCalibration_Single  = gcnew C_frm_CameraCalibration_Single    (GlobalObjects, this);
  this->frm_CameraCalibration_Stereo  = gcnew C_frm_CameraCalibration_Stereo    (GlobalObjects, this);
  this->frm_ObjectCalibration         = gcnew C_frm_ObjectCalibration           (GlobalObjects, this);
  this->frm_Camera_Positioning        = gcnew c_frm_Camera_Positioning          (GlobalObjects, this);


  }

C_Main::~C_Main()
  {
  delete (this->frm_CameraCalibration_Stereo);
  delete (this->frm_CameraCalibration_Single);
  delete (this->frm_CameraCalibration_Menu);
  delete (this->frm_Main);
  this->GlobalObjects = nullptr;
  }

//
//#include "frm_Main.cpp"
//#include "frm_CameraCalibration_Menu.cpp"
//#include "frm_CameraCalibration_Single.cpp"
//#include "frm_CameraCalibration_Stereo.cpp"