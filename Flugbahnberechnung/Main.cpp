#pragma once

#include "Main.h"

using namespace NmSp_Main;

C_Main::C_Main              (C_GlobalObjects^ GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;

  this->frm_Main                      = gcnew C_frm_Main                        (this->GlobalObjects, this);
  this->frm_Main->Show();

  this->frm_CameraCalibration_Menu    = gcnew C_frm_CameraCalibration_Menu      (this->GlobalObjects, this);
  this->frm_CameraCalibration_Single  = gcnew C_frm_CameraCalibration_Single    (this->GlobalObjects, this);
  this->frm_CameraCalibration_Stereo  = gcnew C_frm_CameraCalibration_Stereo    (this->GlobalObjects, this);
  this->frm_ObjectCalibration         = gcnew C_frm_ObjectCalibration           (this->GlobalObjects, this);

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