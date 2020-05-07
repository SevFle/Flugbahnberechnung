#include "frm_Camera_Calibration_crop.h"

using namespace nmsp_camera_calibration_crop;

c_frm_Camera_Calibration_crop::c_frm_Camera_Calibration_crop(C_GlobalObjects* GlobalObjects, C_Main^  Main)
    {
    InitializeComponent();
    this->GlobalObjects         = GlobalObjects;
    this->Main                  = Main;
    this->fitting_rect = new cv::Rect(0, 0, 400, 300);
    this->last_camera_id        = 0;
    this->current_camera_id        = 0;
    this->Timerwait             = 0;
    this->Zaehler        = 0;

  }

  c_frm_Camera_Calibration_crop::~c_frm_Camera_Calibration_crop()
    {
    this->Main                  = nullptr;
    this->GlobalObjects         = nullptr;
    if (components)
      {
      delete components;
      }
    }

  System::Void c_frm_Camera_Calibration_crop::Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e)
    {
    this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);

    if(Zaehler > Timerwait)
      {
      this->FillMat2PictureboxFramed(pb_uncropped_img,  this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cpu_undistorted);
      //this->FillMat2Picturebox      (pb_cropped_img,    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cpu_cropped_img);
      }
    }
  System::Void c_frm_Camera_Calibration_crop::bt_exit_Click(System::Object^  sender, System::EventArgs^  e)
    {
    this->Main->frm_CameraCalibration_crop->Close();
    }
  System::Void c_frm_Camera_Calibration_crop::nup_camera_id_ValueChanged(System::Object^  sender, System::EventArgs^  e)
    {
    this->Taktgeber->Enabled                                                                            = false;
    cv::destroyAllWindows();
    this->current_camera_id                                                                             = static_cast<int>(nup_camera_id->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->show_cropped_image  = true;
    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->idle                = false;
    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->undistord_active    = true;
    this->Timerwait                                                                                     = Zaehler+25;
    this->Taktgeber->Enabled                                                                            = true;

    this->Main->camera_managed->camera_unmanaged->camera_vector[last_camera_id]->show_cropped_image     = false;
    this->Main->camera_managed->camera_unmanaged->camera_vector[last_camera_id]->idle                   = true;
    this->Main->camera_managed->camera_unmanaged->camera_vector[last_camera_id]->undistord_active       = false;
    this->last_camera_id                                                                                = static_cast<int>(nup_camera_id->Value);
    }
  System::Void c_frm_Camera_Calibration_crop::num_UD_resize_width_ValueChanged(System::Object^  sender, System::EventArgs^  e)
    {
    this->Taktgeber->Enabled = false;
    this->bt_apply->Enabled = true;
    this->Timerwait = Zaehler+10;
    this->fitting_rect->width = static_cast<int>(this->num_UD_resize_width->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->resize_width = static_cast<int>(this->num_UD_resize_width->Value);
    this->Taktgeber->Enabled = true;

    }
  System::Void c_frm_Camera_Calibration_crop::num_UD_resize_height_ValueChanged(System::Object^  sender, System::EventArgs^  e)
    {
    this->Taktgeber->Enabled = false;
    this->bt_apply->Enabled = true;
    this->Timerwait = Zaehler+10;
    this->fitting_rect->height = static_cast<int>(this->num_UD_resize_height->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->resize_height = static_cast<int>(this->num_UD_resize_height->Value);
    this->Taktgeber->Enabled = true;

    }



  System::Void          c_frm_Camera_Calibration_crop::FillPicturebox                                       (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
    {
    System::Drawing::Graphics^    graphics = Picturebox->CreateGraphics();
    System::Drawing::Bitmap       bitmap   (ColorImageCols, ColorImageRows, ColorImageStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ColorImagePtr);
    System::Drawing::RectangleF   rect (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
    graphics->DrawImage           (%bitmap, rect);
    delete (graphics);
    }

  System::Void          c_frm_Camera_Calibration_crop::FillMat2Picturebox                                   (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage)
    {
    Int32                              colorImage_cols   =   colorImage->cols;
    Int32                              colorImage_rows   =   colorImage->rows;
    Int32                              colorImage_step   =   colorImage->step;
    Int32                              colorImage_type   =   colorImage->type();
    System::IntPtr                     colorImage_ptr  (colorImage->ptr());

    FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
    } // FillMatInToPictureBox
  System::Void          c_frm_Camera_Calibration_crop::FillMat2PictureboxFramed                             (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage)
  {
    cv::rectangle                                          (*colorImage, *fitting_rect, cv::Scalar(255.0, 255.0, 0.0), 1, cv::LINE_8);
    Int32                              colorImage_cols   =   colorImage->cols;
    Int32                              colorImage_rows   =   colorImage->rows;
    Int32                              colorImage_step   =   colorImage->step;
    Int32                              colorImage_type   =   colorImage->type();
    System::IntPtr                     colorImage_ptr  (colorImage->ptr());

    FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);

  }

  System::Void          c_frm_Camera_Calibration_crop::c_frm_Camera_Calibration_crop_Load                   (System::Object^  sender, System::EventArgs^  e)
      {
    this->Zaehler                           = 0;
    this->Taktgeber->Interval               = 25;
    this->Taktgeber->Enabled                = true;
    this->cameras_in_use                    = GlobalObjects->cameras_in_use;
    this->current_camera_id                 = 0;
    this->Timerwait                         = 50;
    this->Main->camera_managed->camera_unmanaged->camera_vector[0]->show_cropped_image = true;
      }
  System::Void          c_frm_Camera_Calibration_crop::c_frm_Camera_Calibration_crop_FormClosing            (System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
      {
      this->Taktgeber->Enabled                = false;
      cv::destroyAllWindows();
      }
  System::Void          c_frm_Camera_Calibration_crop::bt_apply_Click(System::Object^  sender, System::EventArgs^  e)
        {
    this->Main->camera_managed->camera_unmanaged->save_camera_calibration(current_camera_id);
    this->bt_apply->Enabled = false;
        }

