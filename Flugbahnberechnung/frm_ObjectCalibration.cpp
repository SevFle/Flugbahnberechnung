#pragma once
/****************************************************************** Includes ****************************************************************/
#include "frm_ObjectCalibration.h"

using namespace NmSp_frm_ObjectCalibration;
/*************************************************************** Konstruktoren **************************************************************/
C_frm_ObjectCalibration::C_frm_ObjectCalibration                        (C_GlobalObjects* GlobalObjects, C_Main^  Main)
  {
    InitializeComponent                                          ();
    this->GlobalObjects           = GlobalObjects;
    this->Main                    = Main;

    camera_id_in_use = 0;

    trb_hue_min->Minimum  = 0;
    trb_hue_min->Maximum  = 255;

    trb_hue_max->Minimum  = 0;
    trb_hue_max->Maximum  = 255;

    trb_saturation_min->Minimum =0;
    trb_saturation_min->Maximum = 255;

    trb_saturation_max->Minimum =0;
    trb_saturation_max->Maximum = 255;

    trb_value_min->Minimum = 0;
    trb_value_min->Maximum = 255;

    trb_value_max->Minimum = 0;
    trb_value_max->Maximum = 255;


    numUD_erode_iterations->Minimum = 0;
    numUD_erode_iterations->Maximum = 10;

    numUD_dilation_iterations->Minimum = 0;
    numUD_dilation_iterations->Maximum = 10;

    numUD_opening_iterations->Minimum = 0;
    numUD_opening_iterations->Maximum = 10;

    numUD_bilateral_iterations->Minimum = 0;
    numUD_bilateral_iterations->Maximum = 10;

    numUD_morph_iterations->Minimum = 1;
    numUD_morph_iterations->Maximum = 10;


    numUD_erode_kernelsize->Minimum = 1;
    numUD_erode_kernelsize->Maximum = 10;

    numUD_dilation_kernelsize->Minimum = 1;
    numUD_dilation_kernelsize->Maximum = 10;

    numUD_opening_kernelsize->Minimum = 1;
    numUD_opening_kernelsize->Maximum = 10;

    numUD_bilateral_kernelsize->Minimum = 1;
    numUD_bilateral_kernelsize->Maximum = 10;

    numUD_morph_kernelsize->Minimum = 1;
    numUD_morph_kernelsize->Maximum = 10;




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

  //Initial Wait um das abgreifen nicht vorhandener Bilder zu verhindern
  if (Zaehler > TimerWait+10 )
    {
    FillMat2Picturebox(pb_original, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->cpu_src_img);
    //FillMat2Picturebox(pb_gray, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->cpu_gray);
    FillMat2Picturebox(pb_filtered, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->cpu_masked_img);
    FillMat2Picturebox(pb_tracked, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->cpu_dst_img_test);

    }
  }

System::Void        C_frm_ObjectCalibration::bt_Start_Click             (System::Object^ sender, System::EventArgs^ e)
  {
  }

System::Void        C_frm_ObjectCalibration::bt_Stop_Click              (System::Object^ sender, System::EventArgs^ e)
  {
  this->Main->camera_managed->camera_unmanaged->stop_statemachine = true;
  }


System::Void C_frm_ObjectCalibration::C_frm_ObjectCalibration_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
  {
  this->Taktgeber->Enabled                = false;
  for (int i = 0; i<0; i++)
    {
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[i]->filtering_active = false;
    }

  }
System::Void C_frm_ObjectCalibration::C_frm_ObjectCalibration_Load(System::Object^  sender, System::EventArgs^  e)
  {
  this->Zaehler                           = 0;
  this->Taktgeber->Interval               = 100;
  this->Taktgeber->Enabled                = true;
  numUD_cam_id->Maximum                   = GlobalObjects->cameras_in_use;
  trb_hue_min->Value                      = 0;
  trb_hue_max->Value                      = 255;
  trb_saturation_min->Value               = 0;
  trb_saturation_max->Value               = 255;
  trb_value_min->Value                    = 0;
  trb_value_max->Value                    = 255;

  
 Main->camera_managed->camera_unmanaged->camera_vector_unsorted[0]->filtering_active = true;


  }

#pragma region ValueChanged_Events
System::Void C_frm_ObjectCalibration::numUD_cam_id_ValueChanged         (System::Object^  sender, System::EventArgs^  e)
  {
  TimerWait = Zaehler;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (numUD_cam_id->Value)]->filtering_active = true;
  camera_id_in_use = static_cast<int> (numUD_cam_id->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->hue_min         = static_cast<uchar> (trb_hue_min         ->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->hue_max         = static_cast<uchar> (trb_hue_max         ->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->saturation_min  = static_cast<uchar> (trb_saturation_min  ->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->saturation_max  = static_cast<uchar> (trb_saturation_max  ->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->value_min       = static_cast<uchar> (trb_value_min       ->Value);
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->value_max       = static_cast<uchar> (trb_value_max       ->Value);

  }
System::Void C_frm_ObjectCalibration::trb_hue_min_ValueChanged          (System::Object^  sender, System::EventArgs^  e)
  {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_min->Value = this->trb_hue_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->hue_min =static_cast<uchar> (trb_hue_min->Value);
  txb_hue_min->Text = System::String::Format("{0:0}", trb_hue_min->Value);
  }
System::Void C_frm_ObjectCalibration::trb_hue_max_ValueChanged          (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_min->Value = this->trb_hue_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->hue_max = static_cast<uchar> (trb_hue_max->Value);
 txb_hue_max->Text = System::String::Format("{0:0}", trb_hue_max->Value);
 }
System::Void C_frm_ObjectCalibration::trb_saturation_min_ValueChanged   (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->saturation_min = static_cast<uchar> (trb_saturation_min->Value);
 txb_saturation_min->Text = System::String::Format("{0:0}", trb_saturation_min->Value);
 }
System::Void C_frm_ObjectCalibration::trb_saturation_max_ValueChanged   (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->saturation_max = static_cast<uchar> (trb_saturation_max->Value);
  txb_saturation_max->Text = System::String::Format("{0:0}", trb_saturation_max->Value);

 }
System::Void C_frm_ObjectCalibration::trb_value_min_ValueChanged        (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value-1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->value_min = static_cast<uchar> (trb_value_min->Value);
  txb_value_min->Text = System::String::Format("{0:0}", trb_value_min->Value);

 }
System::Void C_frm_ObjectCalibration::trb_value_max_ValueChanged        (System::Object^  sender, System::EventArgs^  e)
 {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value+1;
  Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->value_max = static_cast<uchar> (trb_value_max->Value);
  txb_value_max->Text = System::String::Format("{0:0}", trb_value_max->Value);

 }


System::Void C_frm_ObjectCalibration::chkb_erode_CheckStateChanged      (System::Object^  sender, System::EventArgs^  e)
 {
  if (erode_active == false)
    {
    erode_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->erode_active = true;
    numUD_erode_iterations->Enabled = true;
    numUD_erode_kernelsize->Enabled = true;

    }
  else if (erode_active == true)
    {
    erode_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->erode_active = false;
    numUD_erode_iterations->Enabled = false;
    numUD_erode_kernelsize->Enabled = false;
    }

 }
System::Void C_frm_ObjectCalibration::chkb_dilate_CheckStateChanged     (System::Object^  sender, System::EventArgs^  e)
 {
  if (dilate_active == false)
    {
    dilate_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->dilate_active = true;
    numUD_dilation_iterations->Enabled = true;
    numUD_dilation_kernelsize->Enabled = true;
    }
  else if (dilate_active == true)
    {
    dilate_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->dilate_active = false;
    numUD_dilation_iterations->Enabled = false;
    numUD_dilation_kernelsize->Enabled = false;

    }

 }
System::Void C_frm_ObjectCalibration::chkb_opening_CheckStateChanged    (System::Object^  sender, System::EventArgs^  e)
 {
  if (open_active == false)
    {
    open_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->open_active = true;
    numUD_opening_iterations->Enabled = true;
    numUD_opening_kernelsize->Enabled = true;

    }
  else if (open_active == true)
    {
    open_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->open_active = false;
    numUD_opening_iterations->Enabled = false;
    numUD_opening_kernelsize->Enabled = false;

    }

 }
System::Void C_frm_ObjectCalibration::chkb_closing_CheckStateChanged    (System::Object^  sender, System::EventArgs^  e)
 {
  if (close_active == false)
    {
    close_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->close_active = true;
    numUD_closing_iterations->Enabled = true;
    numUD_closing_kernelsize->Enabled = true;

    }
  else if (close_active == true)
    {
    close_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->close_active = false;
    numUD_closing_iterations->Enabled = false;
    numUD_closing_kernelsize->Enabled = false;

    }

 }
System::Void C_frm_ObjectCalibration::chkb_bilateral_CheckStateChanged  (System::Object^  sender, System::EventArgs^  e)
 {
  if (gaussian_active == false)
    {
    gaussian_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->gaussian_active = true;
    numUD_bilateral_iterations->Enabled = true;
    numUD_bilateral_kernelsize->Enabled = true;

    }
  else if(gaussian_active == true)
    {
    gaussian_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->gaussian_active = false;
    numUD_bilateral_iterations->Enabled = false;
    numUD_bilateral_kernelsize->Enabled = false;
    }

 }
System::Void C_frm_ObjectCalibration::chkb_morph_CheckStateChanged      (System::Object^  sender, System::EventArgs^  e)
 {
  if (morph_active == false)
    {
    morph_active = true;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->morph_active = true;
    numUD_morph_iterations->Enabled = true;
    numUD_morph_kernelsize->Enabled = true;

    }
  else if (morph_active == true)
    {
    morph_active = false;
    Main->camera_managed->camera_unmanaged->camera_vector_unsorted[camera_id_in_use]->morph_active = false;
    numUD_morph_iterations->Enabled = false;
    numUD_morph_kernelsize->Enabled = false;

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
        System::Drawing::Graphics^    graphics = Picturebox->CreateGraphics();
        System::Drawing::Bitmap       bitmap   (ColorImageCols, ColorImageRows, ColorImageStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ColorImagePtr);
        System::Drawing::RectangleF   rect (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
        graphics->DrawImage           (%bitmap, rect);
        delete (graphics);
        }
        break;
      case CV_8UC1: // grayscale images are incorrectly displayed here 
        {
        System::Drawing::Graphics^    graphics = Picturebox->CreateGraphics();
        System::Drawing::Bitmap       bitmap   (ColorImageCols, ColorImageRows, (int)ColorImageStep, System::Drawing::Imaging::PixelFormat::Format8bppIndexed, ColorImagePtr);
        System::Drawing::RectangleF   rect (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
        graphics->DrawImage           (%bitmap, rect);
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
  Int32                              colorImage_cols   =   colorImage.cols;
  Int32                              colorImage_rows   =   colorImage.rows;
  Int32                              colorImage_step   =   colorImage.step;
  Int32                              colorImage_type   =   colorImage.type();
  System::IntPtr                     colorImage_ptr  (colorImage.ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox


