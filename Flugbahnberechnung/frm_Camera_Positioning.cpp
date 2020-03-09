#include "frm_Camera_Positioning.h"

using namespace nmsp_frm_camera_positioning;

 c_frm_Camera_Positioning::c_frm_Camera_Positioning(C_GlobalObjects^ GlobalObjects, C_Main^  Main)
   {
   InitializeComponent();
   this->GlobalObjects     = GlobalObjects;
   this->Main              = Main;
   }

 c_frm_Camera_Positioning::~c_frm_Camera_Positioning()
   {
   this->Main              = nullptr;
   this->GlobalObjects     = nullptr;
   if (components)
     {
     delete components;
     }
   }

 
System::Void c_frm_Camera_Positioning::nup_Camera_L1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(0, static_cast<int>(nup_Camera_L1->Value));
  }
System::Void c_frm_Camera_Positioning::nup_Camera_L2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(2, static_cast<int>(nup_Camera_L2->Value));
  }
System::Void c_frm_Camera_Positioning::nup_Camera_L3_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(4, static_cast<int>(nup_Camera_L3->Value));
  }
System::Void c_frm_Camera_Positioning::nup_Camera_R1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(1, static_cast<int>(nup_Camera_R1->Value));
  }
System::Void c_frm_Camera_Positioning::nup_Camera_R2_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(3, static_cast<int>(nup_Camera_R2->Value));
  }
System::Void c_frm_Camera_Positioning::nup_Camera_R3_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->sort_camera_vector(5, static_cast<int>(nup_Camera_R3->Value));
  }


