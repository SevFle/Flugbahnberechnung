#pragma once
#include "frm_Camera_Calibration.h"


using namespace NmSp_CamerCalibration_Single;

C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single (C_GlobalObjects* GlobalObjects, C_Main^ Main)
  {
  InitializeComponent();
  this->GlobalObjects         = GlobalObjects;
  this->Main                  = Main;
  this->Zaehler               = 0;
  this->cameras_in_use        = 0;
  this->calibration_running   = false;
  this->photo_interval        = 0;
  this->photo_count           = 0;
  this->photo_id              = 0;
  this->intervall             = 0;
  this->photocount_user_input = 3;
  }
C_frm_CameraCalibration_Single::~C_frm_CameraCalibration_Single ()
  {
  this->cameras_in_use        = 0;
  this->photocount_user_input = 3;
  this->intervall             = 0;
  this->photo_id              = 0;
  this->photo_interval        = 0;
  this->calibration_running   = false;
  this->cameras_in_use        = 0;
  this->Zaehler               = 0;

  this->Main          = nullptr;
  this->GlobalObjects = nullptr;

  if (components)
    {
    delete components;
    }
  }

System::Void C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single_Load (System::Object^ sender, System::EventArgs^ e)
  {
  this->Zaehler             = 0;
  this->Taktgeber->Interval = 25;
  this->Taktgeber->Enabled  = true;
  this->cameras_in_use      = GlobalObjects->cameras_in_use;
  this->current_camera_id   = 0;
  this->Timerwait           = 50;
  //Main->camera_managed->camera_unmanaged->camera_vector[0]->set_aspect_ratio(1080, 1920);
  }

System::Void C_frm_CameraCalibration_Single::rb_single_calibration_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->method                   = 0;
  this->nup_camera_id->Value     = 0;
  this->nup_camera_id->Increment = 1;
  this->current_camera_id        = 0;

  this->rb_stereo_calibration->Checked = false;
  this->rb_single_calibration->Checked = true;

  this->pb_stereo_L->Visible            = false;
  this->pb_stereo_R->Visible            = false;
  this->pb_live_camera_picture->Visible = true;
  }
System::Void C_frm_CameraCalibration_Single::rb_stereo_calibration_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->method                   = 1;
  this->nup_camera_id->Value     = 0;
  this->nup_camera_id->Increment = 2;
  this->current_camera_id        = 0;

  this->rb_single_calibration->Checked = false;
  this->rb_stereo_calibration->Checked = true;

  this->pb_live_camera_picture->Visible = false;
  this->pb_stereo_L->Visible            = true;
  this->pb_stereo_R->Visible            = true;
  }

System::Void C_frm_CameraCalibration_Single::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format ("{0:0}",this->Zaehler++);
  if (Zaehler > this->Timerwait)
    {
    switch (method)
      {
      case 0:
        this->FillMat2Picturebox (pb_live_camera_picture,Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->get_cpu_src_img());
        break;

      case 1:
        this->FillMat2Picturebox (pb_stereo_L,Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->get_cpu_src_img());
        this->FillMat2Picturebox (pb_stereo_R,Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id + 1]->get_cpu_src_img());
        break;
      }
    }
  }

System::Void C_frm_CameraCalibration_Single::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  this->Close();
  }
System::Void C_frm_CameraCalibration_Single::bt_start_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->lbl_calibration_running->Visible = false;
  this->bt_take_photo->Visible           = true;
  this->sm_calibration_state             = 0;
  this->calibration_running              = true;

  switch (method)
    {
    case 0:
      sm_Single_camera_calibration();
      break;
    case 1:
      sm_Stereo_camera_calibration();
      break;
    }
  }


System::Void C_frm_CameraCalibration_Single::FillPicturebox (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
  {
  System::Drawing::Graphics^  graphics = Picturebox->CreateGraphics();
  System::Drawing::Bitmap     bitmap (ColorImageCols,ColorImageRows,ColorImageStep,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ColorImagePtr);
  System::Drawing::RectangleF rect (0,0,(float)Picturebox->Width,(float)Picturebox->Height);
  graphics->DrawImage (%bitmap,rect);
  delete (graphics);
  }
System::Void C_frm_CameraCalibration_Single::FillMat2Picturebox (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat* colorImage)
  {
  Int32          colorImage_cols = colorImage->cols;
  Int32          colorImage_rows = colorImage->rows;
  Int32          colorImage_step = colorImage->step;
  Int32          colorImage_type = colorImage->type();
  System::IntPtr colorImage_ptr (colorImage->ptr());

  FillPicturebox (Picturebox,colorImage_cols,colorImage_rows,colorImage_step,colorImage_type,colorImage_ptr);
  } // FillMatInToPictureBox
System::Void C_frm_CameraCalibration_Single::nup_camera_id_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Timerwait = Zaehler + 8;
  if (nup_camera_id->Value > cameras_in_use) nup_camera_id->Value = static_cast<int> (nup_camera_id->Value) - 1;
  this->current_camera_id = static_cast<int> (nup_camera_id->Value);

  Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->set_idle (false);
  }

System::Void C_frm_CameraCalibration_Single::camera_calibration_thread ()
  {
  //lbl_calibration_running->Invoke(gcnew Action<bool>(lbl_calibration_running->Visible, true));
  switch (method)
    {
    case 0:
      this->Main->camera_managed->camera_unmanaged->calibrate_single_camera (this->current_camera_id);
      break;

    case 1:
      this->Main->camera_managed->camera_unmanaged->calibrate_stereo_camera (this->current_camera_id);
      break;
    }
  //this->lbl_calibration_running->ForeColor = System::Drawing::Color::Green;
  //this->lbl_calibration_running->Text = "Kalibrierung beendet";
  //terminate();
  }
System::Void C_frm_CameraCalibration_Single::bt_take_photo_Click (System::Object^ sender, System::EventArgs^ e)
  {
  switch (method)
    {
    case 0:
      sm_Single_camera_calibration();
      break;
    case 1:
      sm_Stereo_camera_calibration();
      break;
    }
  }

System::Void C_frm_CameraCalibration_Single::bt_show_crop_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  for (int i = 0; i < cameras_in_use; i++)
    {
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_idle             (false);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_undistord_active (true);
    }
  this->Main->frm_CameraCalibration_crop->ShowDialog();
  this->Taktgeber->Enabled = true;
  }


System::Void C_frm_CameraCalibration_Single::num_UD_resize_width_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  }
System::Void C_frm_CameraCalibration_Single::num_UD_resize_height_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  }

System::Void C_frm_CameraCalibration_Single::sm_Single_camera_calibration ()
  {
  std::string naming = "../Parameter/Bilder/Camera_Single_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cap->set (cv::CAP_PROP_XI_AEAG,false);
      this->current_camera_id = static_cast<int> (this->nup_camera_id->Value);
      this->photo_id          = 0;
      //this->photo_interval            =   int::Parse(tb_photo_interval->Text)*10;
      this->photocount_user_input = int::Parse (tb_single_imgs_to_take->Text);

      this->grB_options->Enabled = false;
      this->bt_start->Text       = "Beenden";

      this->sm_calibration_state = 1;
      break;

      //Take pictures
    case 1:
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->save_picture (current_camera_id,photo_id,naming);
      this->tb_picture_count->Text = System::String::Format ("{0:0}",this->photo_id + 1);
      this->photo_id++;

      if (photo_id >= photocount_user_input)
        {
        this->sm_calibration_state = 2;
        }

      break;

    case 2:
      this->bt_take_photo->Visible = false;
      this->calibration_running  = false;
      this->grB_options->Enabled = true;
      this->bt_start->Text       = "Start";

      this->Main->camera_managed->camera_unmanaged->SquareSize                                         = static_cast<float> (double::Parse (this->tb_single_edge_length->Text));
      this->Main->camera_managed->camera_unmanaged->numBoards_imgs                                     = this->photo_id;
      this->Main->camera_managed->camera_unmanaged->numCornersHeight                                   = int::Parse (this->tb_single_corner_count_H->Text);
      this->Main->camera_managed->camera_unmanaged->numCornersWidth                                    = int::Parse (this->tb_single_corner_count_B->Text);
      this->Main->camera_managed->camera_unmanaged->camera_id                                          = this->current_camera_id;
      this->lbl_calibration_running->Visible                                                           = true;
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->set_undistord_active(false);

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      Thread^ calibrate = gcnew Thread (gcnew ThreadStart (this,&C_frm_CameraCalibration_Single::camera_calibration_thread));
      calibrate->Start();
      photo_id = 0;


      break;
    }
  }

System::Void C_frm_CameraCalibration_Single::sm_Stereo_camera_calibration ()
  {
  std::string naming = "../Parameter/Bilder/Camera_Stereo_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cap->set (cv::CAP_PROP_XI_AEAG,false);
      current_camera_id = static_cast<int> (this->nup_camera_id->Value);
      photo_id          = 0;
      //photo_interval            =   int::Parse(tb_photo_interval->Text)*10;
      photocount_user_input = int::Parse (tb_single_imgs_to_take->Text);

      grB_options->Enabled = false;
      this->bt_start->Text = "Beenden";

      this->sm_calibration_state = 1;
      break;

      //Take pictures
    case 1:
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->save_picture (current_camera_id,photo_id,naming);
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->save_picture (current_camera_id + 1,photo_id,naming);

      this->tb_picture_count->Text = System::String::Format ("{0:0}",this->photo_id + 1);
      this->photo_id++;

      if (photo_id >= photocount_user_input)
        {
        this->sm_calibration_state = 2;
        }

      break;

    case 2:
      this->bt_take_photo->Visible = false;
      this->calibration_running  = false;
      this->grB_options->Enabled = true;
      this->bt_start->Text       = "Start";

      this->Main->camera_managed->camera_unmanaged->SquareSize                                         = static_cast<float> (double::Parse (this->tb_single_edge_length->Text));
      this->Main->camera_managed->camera_unmanaged->numBoards_imgs                                     = this->photo_id;
      this->Main->camera_managed->camera_unmanaged->numCornersHeight                                   = int::Parse (this->tb_single_corner_count_H->Text);
      this->Main->camera_managed->camera_unmanaged->numCornersWidth                                    = int::Parse (this->tb_single_corner_count_B->Text);
      this->Main->camera_managed->camera_unmanaged->camera_id                                          = this->current_camera_id;
      this->lbl_calibration_running->Visible                                                           = true;
      this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->set_undistord_active (false);

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      this->calibrate->Start();

      photo_id = 0;


      break;
    }
  }
