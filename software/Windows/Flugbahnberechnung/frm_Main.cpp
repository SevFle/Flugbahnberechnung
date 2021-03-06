#pragma once
#include "frm_Main.h"

using namespace NmSp_frm_Main;
/*************************************************************** Konstruktoren **************************************************************/
C_frm_Main::C_frm_Main (C_GlobalObjects* GlobalObjects, C_Main^ Main)
  {
  InitializeComponent();
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  this->Zaehler       = 0;
  this->state         = 0;
  }
/**************************************************************** Destruktor ****************************************************************/
C_frm_Main::~C_frm_Main ()
  {
  this->state         = 0;
  this->Zaehler       = 0;
  this->Main          = nullptr;
  this->GlobalObjects = nullptr;

  if (components)
    {
    delete components;
    }
  }

/**************************************************** WinForms Event-Handler *********************************************************/
System::Void C_frm_Main::bt_ObjectCalibration_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_idle (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_show_cropped_image (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_undistord_active (true);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_filtering_active (true);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_show_contoured_active(true);
  this->Main->frm_ObjectCalibration->ShowDialog();
  this->Taktgeber->Enabled = true;
  }

System::Void C_frm_Main::bt_CameraCalibration_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_idle (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_show_cropped_image (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_undistord_active (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_filtering_active (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->set_show_contoured_active(false);
  this->Main->frm_CameraCalibration_Single->ShowDialog();
  this->Taktgeber->Enabled = true;
  }

System::Void C_frm_Main::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  if (!this->bt_apply_cameras->Enabled) this->Main->camera_managed->camera_unmanaged->close_cameras (GlobalObjects->cameras_in_use);
  this->Close();
  }

System::Void C_frm_Main::C_frm_Main_Load (System::Object^ sender, System::EventArgs^ e)
  {
  this->Zaehler             = 0;
  this->Taktgeber->Interval = 100;
  this->Taktgeber->Enabled  = true;
  }

System::Void C_frm_Main::C_frm_Main_FormClosing (System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  }

System::Void C_frm_Main::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  switch (state)
    {
    case 0:
      this->txtb_counter->Text = System::String::Format ("{0:0}",this->Zaehler++);
      break;
    case 1:
      this->txtb_counter->Text = System::String::Format ("{0:0}",this->Zaehler++);
      if (this->Main->camera_managed->camera_unmanaged->camera_vector[GlobalObjects->cameras_in_use-1]->is_thread_ready())
        {
        bt_ObjectCalibration->Enabled  = true;
        bt_CameraCalibration->Enabled  = true;
        bt_camera_positioning->Enabled = true;
        bt_Kameraposen->Enabled        = true;
        state                          = 0;
        }
      break;
    }
  }

System::Void C_frm_Main::bt_camera_positioning_MouseClick (System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    Main->camera_managed->camera_unmanaged->camera_vector[i]->set_idle (false);
    Main->camera_managed->camera_unmanaged->camera_vector[i]->set_undistord_active (false);
    }
  this->Main->frm_Camera_Positioning->ShowDialog();
  this->Taktgeber->Enabled = true;
  }

System::Void C_frm_Main::bt_apply_cameras_Click (System::Object^ sender, System::EventArgs^ e)
  {
  if (static_cast<int> (nup_camera_count->Value) % 2 != 0)
    {
    MessageBox::Show ("Es muss eine gerade Anzahl an Kameras verwendet werden","Fehler",MessageBoxButtons::OK,MessageBoxIcon::Error);
    }
  else
    {
    GlobalObjects->cameras_in_use = static_cast<int> (nup_camera_count->Value);
    nup_camera_count->Enabled     = false;
    bt_apply_cameras->Enabled     = false;

    Main->camera_managed->camera_unmanaged->init_camera_vectors (static_cast<int> (nup_camera_count->Value));
    timerwait   = Zaehler + 50;
    this->state = 1;
    }
  }
System::Void C_frm_Main::button1_Click (System::Object^ sender, System::EventArgs^ e)
  {
  Taktgeber->Enabled = false;
  this->Main->frm_camera_positioning_pose->ShowDialog();
  Taktgeber->Enabled = true;
  }
