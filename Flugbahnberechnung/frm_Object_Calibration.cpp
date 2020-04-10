#pragma once
/****************************************************************** Includes ****************************************************************/
#include "frm_Object_Calibration.h"

using namespace NmSp_frm_ObjectCalibration;
/*************************************************************** Konstruktoren **************************************************************/
C_frm_ObjectCalibration::C_frm_ObjectCalibration                        (C_GlobalObjects* GlobalObjects, C_Main^  Main)
  {
    InitializeComponent                                          ();
    this->GlobalObjects                       = GlobalObjects;
    this->Main                                = Main;

    camera_id_in_use = 0;

    trb_hue_min->Minimum                      = 0;
    trb_hue_min->Maximum                      = 179;

    trb_hue_max->Minimum                      = 0;
    trb_hue_max->Maximum                      = 179;

    trb_saturation_min->Minimum               = 0;
    trb_saturation_min->Maximum               = 255;

    trb_saturation_max->Minimum               = 0;
    trb_saturation_max->Maximum               = 255;

    trb_value_min->Minimum                    = 0;
    trb_value_min->Maximum                    = 255;

    trb_value_max->Minimum                    = 0;
    trb_value_max->Maximum                    = 255;


    numUD_erode_iterations->Minimum           = 0;
    numUD_erode_iterations->Maximum           = 10;

    numUD_dilation_iterations->Minimum        = 0;
    numUD_dilation_iterations->Maximum        = 10;

    numUD_opening_iterations->Minimum         = 0;
    numUD_opening_iterations->Maximum         = 10;

    numUD_bilateral_color->Minimum            = 0;
    numUD_bilateral_color->Maximum            = 10;

    numUD_morph_iterations->Minimum           = 1;
    numUD_morph_iterations->Maximum           = 10;


    numUD_erode_kernelsize->Minimum           = 1;
    numUD_erode_kernelsize->Maximum           = 10;

    numUD_dilation_kernelsize->Minimum        = 1;
    numUD_dilation_kernelsize->Maximum        = 10;

    numUD_opening_kernelsize->Minimum         = 1;
    numUD_opening_kernelsize->Maximum         = 10;

    numUD_bilateral_kernelsize->Minimum       = 1;
    numUD_bilateral_kernelsize->Maximum       = 10;

    numUD_morph_kernelsize->Minimum           = 1;
    numUD_morph_kernelsize->Maximum           = 10;

    TimerWait = 0;


  }
/**************************************************************** Destruktor ****************************************************************/
C_frm_ObjectCalibration::~C_frm_ObjectCalibration                       ()
  {
  TimerWait = 0;

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

  //Initial Wait um das abgreifen nicht vorhandener Bilder zu verhindern
  if (Zaehler > TimerWait+8 )
    {
    FillMat2Picturebox(pb_original, *Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_src_img);
    FillMat2Picturebox(pb_gray,     *Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_filtered);
    FillMat2Picturebox(pb_filtered, *Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_masked_img);
    FillMat2Picturebox(pb_tracked,  *Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_contoured);
    }
  }

System::Void        C_frm_ObjectCalibration::C_frm_ObjectCalibration_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
  {
  this->Taktgeber->Enabled                = false;
  for (int i = 0; i<0; i++)
    {
    Main->camera_managed->camera_unmanaged->camera_vector[i]->filtering_active = false;
    }

  }

System::Void        C_frm_ObjectCalibration::C_frm_ObjectCalibration_Load(System::Object^  sender, System::EventArgs^  e)
  {
  this->Zaehler                           = 0;
  this->Taktgeber->Interval               = 100;
  this->Taktgeber->Enabled                = true;
  TimerWait                               = 7;
  numUD_cam_id->Maximum                   = GlobalObjects->cameras_in_use;
  trb_hue_min->Value                      = 0;
  trb_hue_max->Value                      = 179;
  trb_saturation_min->Value               = 0;
  trb_saturation_max->Value               = 255;
  trb_value_min->Value                    = 0;
  trb_value_max->Value                    = 255;

  Main->camera_managed->camera_unmanaged->camera_vector[0]->idle = false;
  Main->camera_managed->camera_unmanaged->camera_vector[0]->filtering_active = true;


  }

#pragma region ValueChanged_Events
System::Void        C_frm_ObjectCalibration::numUD_cam_id_ValueChanged         (System::Object^  sender, System::EventArgs^  e)
  {
  TimerWait = Zaehler;
  this->Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (numUD_cam_id->Value)]->idle = false;
  this->Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (numUD_cam_id->Value)]->filtering_active = true;
  this->camera_id_in_use = static_cast<int> (numUD_cam_id->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_min         = static_cast<uchar> (trb_hue_min         ->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_max         = static_cast<uchar> (trb_hue_max->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_min  = static_cast<uchar> (trb_saturation_min->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_max  = static_cast<uchar> (trb_saturation_max->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_min       = static_cast<uchar> (trb_value_min->Value);
  //Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_max       = static_cast<uchar> (trb_value_max->Value);


  this->trb_hue_min->Value                  =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_min);
  this->trb_hue_max->Value                  =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_max);
  this->trb_saturation_min->Value           =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_min);
  this->trb_saturation_max->Value           =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_max);
  this->trb_value_min->Value                =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_min);
  this->trb_value_max->Value                =  static_cast<int> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_max);

  this->numUD_erode_iterations->Value       = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erosion_iterations;
  this->numUD_closing_iterations->Value     = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->closing_iterations;
  this->numUD_opening_iterations->Value     = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->opening_iterations;
  this->numUD_dilation_iterations->Value    = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilation_iterations;

  this->numUD_erode_kernelsize->Value       = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erosion_kernel_size;
  this->numUD_closing_kernelsize->Value     = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->closing_kernel_size;
  this->numUD_opening_kernelsize->Value     = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->opening_kernel_size;
  this->numUD_dilation_kernelsize->Value    = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilation_kernel_size;

  this->numUD_gaussian_kernel_size->Value   = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->gaussian_kernel_size;
  this->numUD_gaussian_sigma->Value         = static_cast<System::Decimal>(Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->gaussian_sigma);

  this->numUD_bilateral_color->Value        = static_cast<System::Decimal>(Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_sigma_color);
  this->numUD_bilateral_spatial->Value      = static_cast<System::Decimal>(Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_sigma_spatial);
  this->numUD_bilateral_kernelsize->Value   = Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_kernel_size;


  }
System::Void        C_frm_ObjectCalibration::trb_hue_min_ValueChanged          (System::Object^  sender, System::EventArgs^  e)
  {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_min->Value = this->trb_hue_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_min =static_cast<uchar> (trb_hue_min->Value);
  txb_hue_min->Text = System::String::Format("{0:0}", trb_hue_min->Value);
  }
System::Void        C_frm_ObjectCalibration::trb_hue_max_ValueChanged          (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_min->Value = this->trb_hue_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->hue_max = static_cast<uchar> (trb_hue_max->Value);
 txb_hue_max->Text = System::String::Format("{0:0}", trb_hue_max->Value);
 }
System::Void        C_frm_ObjectCalibration::trb_saturation_min_ValueChanged   (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_min = static_cast<uchar> (trb_saturation_min->Value);
 txb_saturation_min->Text = System::String::Format("{0:0}", trb_saturation_min->Value);
 }
System::Void        C_frm_ObjectCalibration::trb_saturation_max_ValueChanged   (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->saturation_max = static_cast<uchar> (trb_saturation_max->Value);
  txb_saturation_max->Text = System::String::Format("{0:0}", trb_saturation_max->Value);

 }
System::Void        C_frm_ObjectCalibration::trb_value_min_ValueChanged        (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_min = static_cast<uchar> (trb_value_min->Value);
  txb_value_min->Text = System::String::Format("{0:0}", trb_value_min->Value);

 }
System::Void        C_frm_ObjectCalibration::trb_value_max_ValueChanged        (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->value_max = static_cast<uchar> (trb_value_max->Value);
  txb_value_max->Text = System::String::Format("{0:0}", trb_value_max->Value);

 }

System::Void        C_frm_ObjectCalibration::numUD_opening_iterations_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->opening_iterations = static_cast<int>(this->numUD_opening_iterations->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_opening_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->opening_kernel_size = static_cast<int>(this->numUD_opening_kernelsize->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_closing_iterations_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->closing_iterations = static_cast<int>(this->numUD_closing_iterations->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_closing_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->closing_kernel_size = static_cast<int>(this->numUD_closing_kernelsize->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_gaussian_kernel_size_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->gaussian_kernel_size = static_cast<int>(this->numUD_gaussian_kernel_size->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_gaussian_sigma_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->gaussian_sigma = static_cast<double>(this->numUD_gaussian_sigma->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_erode_iterations_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erosion_iterations = static_cast<int>(this->numUD_erode_iterations->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_erode_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erosion_kernel_size = static_cast<int>(this->numUD_erode_kernelsize->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_dilation_iterations_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilation_iterations = static_cast<int>(this->numUD_dilation_iterations->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_dilation_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilation_kernel_size = static_cast<int>(this->numUD_dilation_kernelsize->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_bilateral_spatial_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_sigma_spatial = static_cast<float>(this->numUD_bilateral_spatial->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_bilateral_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_kernel_size = static_cast<int>(this->numUD_bilateral_kernelsize->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_bilateral_color_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->bilateral_sigma_color = static_cast<float>(this->numUD_bilateral_color->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_morph_iterations_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->morph_iterations = static_cast<int>(this->numUD_morph_iterations->Value);
  }
System::Void        C_frm_ObjectCalibration::numUD_morph_kernelsize_ValueChanged(System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->morph_kernel_size = static_cast<int>(this->numUD_morph_kernelsize->Value);
  }


System::Void        C_frm_ObjectCalibration::chkb_erode_CheckStateChanged      (System::Object^  sender, System::EventArgs^  e)
 {
  if (erode_active == false)
    {
    erode_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erode_active = true;
    numUD_erode_iterations->Enabled = true;
    numUD_erode_kernelsize->Enabled = true;

    }
  else if (erode_active == true)
    {
    erode_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->erode_active = false;
    numUD_erode_iterations->Enabled = false;
    numUD_erode_kernelsize->Enabled = false;
    }

 }
System::Void        C_frm_ObjectCalibration::chkb_dilate_CheckStateChanged     (System::Object^  sender, System::EventArgs^  e)
 {
  if (dilate_active == false)
    {
    dilate_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilate_active = true;
    numUD_dilation_iterations->Enabled                     = true;
    numUD_dilation_kernelsize->Enabled                     = true;
    }
  else if (dilate_active == true)
    {
    dilate_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->dilate_active = false;
    numUD_dilation_iterations->Enabled                    = false;
    numUD_dilation_kernelsize->Enabled                    = false;

    }

 }

//////// STUFF TO DO//////////////////////////////////////////////////////
///
System::Void        C_frm_ObjectCalibration::chkb_bilateral_CheckStateChanged  (System::Object^  sender, System::EventArgs^  e)
 {
  if (bilateral_active == false)
    {
    numUD_bilateral_color->     Enabled                   = true;
    numUD_bilateral_spatial->   Enabled                   = true;
    numUD_bilateral_kernelsize->Enabled                   = true;

    }
  else if(bilateral_active == true)
    {
    numUD_bilateral_color->     Enabled                   = false;
    numUD_bilateral_spatial->   Enabled                   = false;
    numUD_bilateral_kernelsize->Enabled                   = false;
    }

 }
System::Void        C_frm_ObjectCalibration::chkb_morph_CheckStateChanged      (System::Object^  sender, System::EventArgs^  e)
 {
  if (morph_active == false)
    {
    morph_active                                          = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->morph_active = true;
    numUD_morph_iterations->Enabled                       = true;
    numUD_morph_kernelsize->Enabled                       = true;

    }
  else if (morph_active == true)
    {
    morph_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->morph_active = false;
    numUD_morph_iterations->Enabled                       = false;
    numUD_morph_kernelsize->Enabled                       = false;

    }
  }
#pragma endregion
/*************************************************** Nicht öffentliche private Methoden *****************************************************/
System::Void          C_frm_ObjectCalibration::FillPicturebox                                      (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
  {
  switch (ColorImageType)
    {
      case CV_8UC3: // non-grayscale images are correctly displayed here
        {
        System::Drawing::Graphics^    graphics            = Picturebox->CreateGraphics();
        System::Drawing::Bitmap       bitmap              (ColorImageCols, ColorImageRows, ColorImageStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ColorImagePtr);
        System::Drawing::RectangleF   rect                (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
        graphics->DrawImage                               (%bitmap, rect);
        delete (graphics);
        }
        break;
      case CV_8UC1: // grayscale images are incorrectly displayed here 
        {
        System::Drawing::Graphics^   graphics             = Picturebox->CreateGraphics    ();
        System::Drawing::Bitmap      bitmap               (ColorImageCols, ColorImageRows, (int)ColorImageStep, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, ColorImagePtr);
        System::Drawing::RectangleF  rect                 (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
        graphics->DrawImage                               (%bitmap, rect);
        delete (graphics);
        }
        break;
      default:
        {
        // error message
        }
        break;
    }  // switch (ColorImageType)
  }
System::Void          C_frm_ObjectCalibration::FillMat2Picturebox                                  (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage)
  {
  Int32                              colorImage_cols      =   colorImage.cols;
  Int32                              colorImage_rows      =   colorImage.rows;
  Int32                              colorImage_step      =   colorImage.step;
  Int32                              colorImage_type      =   colorImage.type  ();
  System::IntPtr                     colorImage_ptr       (colorImage.ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox
System::Void          C_frm_ObjectCalibration::bt_apply_Click                                      (System::Object^  sender, System::EventArgs^  e)
  {
  Main->camera_managed->camera_unmanaged->save_camera_settings          (static_cast<int>(numUD_cam_id->Value));
  }

System::Void          C_frm_ObjectCalibration::bt_apply_all_Click                                  (System::Object^  sender, System::EventArgs^  e)
  {
  for (int i = 0;     i<GlobalObjects->cameras_in_use;      i++)
    {
    Main->camera_managed->camera_unmanaged->save_camera_settings        (i);
    }
  }

