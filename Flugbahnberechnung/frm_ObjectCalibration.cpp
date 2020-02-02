#pragma once
#include "frm_ObjectCalibration.h"

using namespace NmSp_frm_ObjectCalibration;

  C_frm_ObjectCalibration::C_frm_ObjectCalibration               (C_GlobalObjects^ GlobalObjects, C_Main^  Main)
  {
    InitializeComponent                                           ();
    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;
  }
  C_frm_ObjectCalibration::~C_frm_ObjectCalibration     ()
  {
 
  }


System::Void				C_frm_ObjectCalibration::bt_exit_Click			(System::Object^  sender, System::EventArgs^  e)
  {
  this->Close();
  }

System::Void				C_frm_ObjectCalibration::Taktgeber_Tick			(System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format("{0:0}", this->Zaehler++);
  }


