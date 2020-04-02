#pragma once
#include "frm_CameraCalibration.h"


using namespace NmSp_CamerCalibration_Single;

C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single(C_GlobalObjects* GlobalObjects, C_Main^  Main)
  {
  InitializeComponent();
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  this->Zaehler       = 0;
  this->cameras_in_use= 0;
  this->calibration_running = false;
  this->photo_interval = 0;
  this->photo_count     = 0;
  this->photo_id        =0;
  this->intervall       = 0;
  this->photocount_user_input = 0;

  }
C_frm_CameraCalibration_Single::~C_frm_CameraCalibration_Single()
  {
  this->cameras_in_use  = 0;

  if (components)
    {
    delete components;
    }
  }

System::Void          C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single_Load(System::Object^  sender, System::EventArgs^  e)
  {
  this->Zaehler                           = 0;
  this->Taktgeber->Interval               = 100;
  this->Taktgeber->Enabled                = true;
  this->cameras_in_use                    = GlobalObjects->cameras_in_use;
  this->current_camera_id                 = 0;
  }


System::Void          C_frm_CameraCalibration_Single::rb_single_calibration_Click(System::Object^  sender, System::EventArgs^  e)
  {
  this->method = 0;
  this->rb_stereo_calibration->Checked = false;
  this->rb_single_calibration->Checked = true;
  }
System::Void          C_frm_CameraCalibration_Single::rb_stereo_calibration_Click(System::Object^  sender, System::EventArgs^  e)
  {
  this->method = 1;
  this->rb_single_calibration->Checked = false;
  this->rb_stereo_calibration->Checked = true;
  }


System::Void          C_frm_CameraCalibration_Single::Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);

  if (Zaehler > this->Timerwait)
    {
    FillMat2Picturebox    (pb_live_camera_picture, Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cpu_src_img);

    if (calibration_running && Zaehler >= intervall && photo_count < photocount_user_input)
      {
      this->intervall = Zaehler + photo_interval;

      switch (this->method)
        {
          case 0:
            this->Main->camera_managed->camera_unmanaged->save_picture(current_camera_id, photo_id);
            photo_id++;
            break;


          case 1:

            break;

        }
      }
    }
  if (photo_count >= photocount_user_input) calibration_running = false;
  }
System::Void          C_frm_CameraCalibration_Single::bt_exit_Click(System::Object^  sender, System::EventArgs^  e)
  {
  this->Taktgeber->Enabled = false;
  this->Close();
  }
System::Void          C_frm_CameraCalibration_Single::bt_take_picture_Click(System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          C_frm_CameraCalibration_Single::bt_start_Click(System::Object^  sender, System::EventArgs^  e)
  {
  if (!calibration_running)
    {
    photo_id                  =   0;
    photo_interval            =  Int16::TryParse(tb_photo_interval->Text)*10;
    photocount_user_input     =   Convert::ToInt16(tb_picture_count->Text);
    Main->camera_managed->camera_unmanaged->SquareSize = static_cast<float> (Convert::ToDouble(this->tb_single_edge_length->Text))*10;

    grB_single->Enabled       =   false;
    grb_stereo->Enabled       =   false;
    this->bt_start->Text      =   "Beenden";
    this->calibration_running =   true;

    }
  else
    {
    calibration_running       =   false;
    grB_single->Enabled       =   true;
    grb_stereo->Enabled       =   true;
    this->bt_start->Text      =   "Start";

    Main->camera_managed->camera_unmanaged->calibrate_single_camera(current_camera_id);
    }
  }

System::Void          C_frm_CameraCalibration_Single::FillPicturebox                                      (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
  {
  System::Drawing::Graphics^    graphics = Picturebox->CreateGraphics();
  System::Drawing::Bitmap       bitmap   (ColorImageCols, ColorImageRows, ColorImageStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ColorImagePtr);
  System::Drawing::RectangleF   rect (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
  graphics->DrawImage           (%bitmap, rect);
  delete (graphics);
  }
System::Void          C_frm_CameraCalibration_Single::FillMat2Picturebox                                  (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage)
  {
  Int32                              colorImage_cols   =   colorImage->cols;
  Int32                              colorImage_rows   =   colorImage->rows;
  Int32                              colorImage_step   =   colorImage->step;
  Int32                              colorImage_type   =   colorImage->type();
  System::IntPtr                     colorImage_ptr  (colorImage->ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox
System::Void          C_frm_CameraCalibration_Single::nup_camera_id_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {
  Timerwait = Zaehler + 8;
  if (nup_camera_id->Value> cameras_in_use) nup_camera_id->Value  =  static_cast<int>  (nup_camera_id->Value) - 1;
  this->current_camera_id                                         =  static_cast<int>  (nup_camera_id->Value);
  }
