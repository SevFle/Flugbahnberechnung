#pragma once
/****************************************************************** Includes ****************************************************************/
#include "frm_ObjectCalibration.h"

using namespace NmSp_frm_ObjectCalibration;
/*************************************************************** Konstruktoren **************************************************************/
C_frm_ObjectCalibration::C_frm_ObjectCalibration                        (C_GlobalObjects^ GlobalObjects, C_Main^  Main)
  {
    InitializeComponent                                          ();
    this->GlobalObjects           = GlobalObjects;
    this->Main                    = Main;
  }
/**************************************************************** Destruktor ****************************************************************/
C_frm_ObjectCalibration::~C_frm_ObjectCalibration                       ()
  {
    this->Main                    = nullptr;
    this->GlobalObjects           = nullptr;

  }
/**************************************************** WinForms Event-Handler *********************************************************/
System::Void				C_frm_ObjectCalibration::bt_exit_Click			        (System::Object^  sender, System::EventArgs^  e)
  {
  this->Close();
  }

System::Void				C_frm_ObjectCalibration::Taktgeber_Tick			        (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format("{0:0}", this->Zaehler++);
  }

System::Void        C_frm_ObjectCalibration::bt_Start_Click             (System::Object^ sender, System::EventArgs^ e)
  {
  //this->Main->OpenCV_managed->opencv_unmanaged->all_camera_state_machine();
    this->Main->camera_managed->camera_unmanaged
  }

System::Void        C_frm_ObjectCalibration::bt_Stop_Click              (System::Object^ sender, System::EventArgs^ e)
  {
  }

System::Void        C_frm_ObjectCalibration::nup_Cam_ID_ValueChanged    (System::Object^ sender, System::EventArgs^ e)
  {
  nup_Cam_ID->Value = GlobalObjects->camera_id;
  }


