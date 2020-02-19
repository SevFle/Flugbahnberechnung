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

/*************************************************** Nicht öffentliche private Methoden *****************************************************/
System::Void          C_frm_ObjectCalibration::FillMat2Picturebox                                 (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &cpu_img)
  {
  Int32                              colorImage_cols   =   colorImage.cols;
  Int32                              colorImage_rows   =   colorImage.rows;
  Int32                              colorImage_step   =   colorImage.step;
  Int32                              colorImage_type   =   colorImage.type();
  System::IntPtr                     colorImage_ptr  (colorImage.ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox

System::Void          C_frm_ObjectCalibration::FillPicturebox                                     (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
{
  
}

