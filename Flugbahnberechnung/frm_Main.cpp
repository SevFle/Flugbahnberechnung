#pragma once
#include "frm_Main.h"

using namespace NmSp_frm_Main;
/*************************************************************** Konstruktoren **************************************************************/
C_frm_Main::C_frm_Main                                                  (C_GlobalObjects* GlobalObjects, C_Main^  Main)
  {
  InitializeComponent();
  this->GlobalObjects     = GlobalObjects;
  this->Main              = Main;
  this->Zaehler           = 0;
  }
/**************************************************************** Destruktor ****************************************************************/
C_frm_Main::~C_frm_Main                                                 ()
  {
  //Stop Camera Thread
  //for (int i = 0; i< GlobalObjects->cameras_in_use; i++)
  //{
  //  Main->camera_managed->camera_unmanaged->camera_vector[i]->thread_running = false;
  //}
  this->Zaehler           = 0;
  this->Main              = nullptr;
  this->GlobalObjects     = nullptr;

  if (components)
    {
    delete components;
    }
  }

/**************************************************** WinForms Event-Handler *********************************************************/
System::Void        C_frm_Main::bt_ObjectCalibration_Click              (System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Taktgeber->Enabled								= false;
  this->Main->frm_ObjectCalibration->ShowDialog();
  this->Taktgeber->Enabled								= true;
  }

System::Void        C_frm_Main::bt_CameraCalibration_Click              (System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Taktgeber->Enabled								= false;
  this->Main->camera_managed->camera_unmanaged->camera_vector[0];
  this->Main->frm_CameraCalibration_Single->ShowDialog();
  this->Taktgeber->Enabled								= true;
  }

System::Void        C_frm_Main::bt_exit_Click                           (System::Object ^ sender, System::EventArgs ^ e)
  {
  if(this->bt_apply_cameras->Enabled) this->Main->camera_managed->camera_unmanaged->close_cameras(static_cast<int>(nup_camera_count->Value));
  this->Close();

  }

System::Void        C_frm_Main::C_frm_Main_Load                         (System::Object ^ sender, System::EventArgs ^ e)
  {
  this->Zaehler                           = 0;
  this->Taktgeber->Interval               = 100;
  this->Taktgeber->Enabled                = true;
  }

System::Void        C_frm_Main::C_frm_Main_FormClosing                  (System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
  {
  this->Taktgeber->Enabled                = false;
  }

System::Void        C_frm_Main::Taktgeber_Tick                          (System::Object ^ sender, System::EventArgs ^ e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);
  }

System::Void        C_frm_Main::bt_camera_positioning_MouseClick        (System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
  {
  this->Taktgeber->Enabled								= false;
  for (int i = 0; i < static_cast<int>(nup_camera_count->Value)-1; i++)
    {
    Main->camera_managed->camera_unmanaged->camera_vector[i]->idle = false;
    }
  this->Main->frm_Camera_Positioning->ShowDialog();
  this->Taktgeber->Enabled								= true;
  }

System::Void        C_frm_Main::bt_apply_cameras_Click                  (System::Object^  sender, System::EventArgs^  e)
  {
  if (static_cast<int>(nup_camera_count->Value) % 2 != 0)
    {
    MessageBox::Show("Es muss eine gerade Anzahl an Kameras verwendet werden", "Fehler", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
  else
    {
    GlobalObjects->cameras_in_use           = static_cast<int>                                      (nup_camera_count->Value);

    Main->camera_managed->camera_unmanaged->init_camera_vectors                 (static_cast<int>   (nup_camera_count->Value));

    bt_ObjectCalibration->Enabled           = true;
    bt_CameraCalibration->Enabled           = true;
    bt_camera_positioning->Enabled          = true;
    nup_camera_count->Enabled               = false;
    bt_apply_cameras->Enabled               = false;
    }
  }



