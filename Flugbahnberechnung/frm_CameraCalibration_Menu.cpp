#include "frm_CameraCalibration_Menu.h"

using namespace NmSp_CamerCalibration_Menu;


C_frm_CameraCalibration_Menu::C_frm_CameraCalibration_Menu      (C_GlobalObjects^ GlobalObjects, C_Main^  Main)
  {
  InitializeComponent                                           ();
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  }



C_frm_CameraCalibration_Menu::~C_frm_CameraCalibration_Menu     ()
  {
  if (components)
    {
    delete components;
    }
  }

inline System::Void       C_frm_CameraCalibration_Menu::bt_exit_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Close();
  }

inline System::Void       C_frm_CameraCalibration_Menu::Taktgeber_Tick(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);
  }

inline System::Void       C_frm_CameraCalibration_Menu::bt_StereoCalibration_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Taktgeber->Enabled								= false;
  this->Main->frm_CameraCalibration_Stereo->ShowDialog();
  this->Taktgeber->Enabled								= true;
  }

inline System::Void       C_frm_CameraCalibration_Menu::bt_SingleCalibration_Click(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Taktgeber->Enabled								= false;
  this->Main->frm_CameraCalibration_Single->ShowDialog();
  this->Taktgeber->Enabled								= true;

  }

inline System::Void       C_frm_CameraCalibration_Menu::C_frm_CameraCalibration_Menu_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
  {
  this->Taktgeber->Enabled  = false;
  }

inline System::Void       C_frm_CameraCalibration_Menu::C_frm_CameraCalibration_Menu_Load(System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Zaehler = 0;
  this->Taktgeber->Interval = 100;
  this->Taktgeber->Enabled  = true;
  }
