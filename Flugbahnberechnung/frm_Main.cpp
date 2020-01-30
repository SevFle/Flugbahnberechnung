#pragma once
#include "frm_Main.h"

using namespace NmSp_frm_Main;

C_frm_Main::C_frm_Main(C_GlobalObjects^ GlobalObjects, C_Main^  Main)
  {
  InitializeComponent();
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  this->Zaehler       = 0;
  }
C_frm_Main::~C_frm_Main()
  {
  this->Zaehler       = 0;
  this->Main          = nullptr;
  this->GlobalObjects = nullptr;
  if (components)
    {
    delete components;
    }
  }

inline System::Void NmSp_frm_Main::C_frm_Main::bt_ObjectCalibration_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  }

inline System::Void NmSp_frm_Main::C_frm_Main::bt_CameraCalibration_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Taktgeber->Enabled								= false;
  this->Main->frm_CameraCalibration_Menu->ShowDialog();
  this->Taktgeber->Enabled								= true;
  }

inline System::Void NmSp_frm_Main::C_frm_Main::bt_exit_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Close();
  }

inline System::Void NmSp_frm_Main::C_frm_Main::C_frm_Main_Load(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Zaehler = 0;
  this->Taktgeber->Interval = 100;
  this->Taktgeber->Enabled  = true;
  }

inline System::Void NmSp_frm_Main::C_frm_Main::C_frm_Main_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
  {
  this->Taktgeber->Enabled  = false;
  }

inline System::Void NmSp_frm_Main::C_frm_Main::Taktgeber_Tick(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);
  }
