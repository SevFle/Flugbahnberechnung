#pragma once
/****************************************************************** Includes ****************************************************************/
#include "frm_Object_Calibration.h"

using namespace NmSp_frm_ObjectCalibration;
/*************************************************************** Konstruktoren **************************************************************/
c_frm_object_calibration::c_frm_object_calibration (C_GlobalObjects* GlobalObjects, C_Main^ Main)
  {
  InitializeComponent();
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;

  camera_id_in_use = 0;

  trb_hue_min->Minimum = 0;
  trb_hue_min->Maximum = 179;

  trb_hue_max->Minimum = 0;
  trb_hue_max->Maximum = 179;

  trb_saturation_min->Minimum = 0;
  trb_saturation_min->Maximum = 255;

  trb_saturation_max->Minimum = 0;
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

  numUD_bilateral_color->Minimum = 0;
  numUD_bilateral_color->Maximum = 10;

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

  TimerWait        = 0;
  camera_id_in_use = 0;
  }
/**************************************************************** Destruktor ****************************************************************/
c_frm_object_calibration::~c_frm_object_calibration ()
  {
  TimerWait = 0;

  this->Main          = nullptr;
  this->GlobalObjects = nullptr;
  if (components)
    {
    delete components;
    }
  }
/**************************************************** WinForms Event-Handler *********************************************************/
System::Void c_frm_object_calibration::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Main->frm_object_tracking->Close();
  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_idle             (true);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_undistord_active (false);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_filtering_active (false);
    }
  cv::destroyAllWindows();
  this->Close();
  }

System::Void c_frm_object_calibration::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format ("{0:0}",this->Zaehler++);

  //Initial Wait um das abgreifen nicht vorhandener Bilder zu verhindern
  if (Zaehler > TimerWait)
    {
    FillMat2Picturebox (pb_original,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_src_img);
    FillMat2Picturebox (pb_gray,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_hsv_filtered);
    FillMat2Picturebox (pb_filtered,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_masked_img);
    FillMat2Picturebox (pb_tracked,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_contoured);
    }
  }

System::Void c_frm_object_calibration::C_frm_ObjectCalibration_FormClosing (System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  }

System::Void c_frm_object_calibration::C_frm_ObjectCalibration_Load (System::Object^ sender, System::EventArgs^ e)
  {
  this->Zaehler                   = 0;
  this->Taktgeber->Interval       = 25;
  this->Taktgeber->Enabled        = true;
  this->TimerWait                 = 50;
  this->numUD_cam_id->Maximum     = GlobalObjects->cameras_in_use;
  this->trb_hue_min->Value        = 0;
  this->trb_hue_max->Value        = 179;
  this->trb_saturation_min->Value = 0;
  this->trb_saturation_max->Value = 255;
  this->trb_value_min->Value      = 0;
  this->trb_value_max->Value      = 255;

  this->get_camera_settings (0);
  }

#pragma region ValueChanged_Events
System::Void c_frm_object_calibration::numUD_cam_id_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  TimerWait                                                                                       = Zaehler + 30;
  this->camera_id_in_use                                                                          = static_cast<int> (numUD_cam_id->Value);
  this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_idle             (false);
  this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_filtering_active (true);
  this->get_camera_settings (camera_id_in_use);
  }

System::Void c_frm_object_calibration::trb_hue_min_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_min->Value = this->trb_hue_max->Value - 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_hue_min (this->trb_hue_min->Value);
  this->txb_hue_min->Text                                                          = System::String::Format ("{0:0}",this->trb_hue_min->Value);
  }
System::Void c_frm_object_calibration::trb_hue_max_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_max->Value = this->trb_hue_min->Value + 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_hue_max (this->trb_hue_max->Value);
  this->txb_hue_max->Text                                                          = System::String::Format ("{0:0}",this->trb_hue_max->Value);
  }//TODO complete the rest of ValueChanged methods
System::Void c_frm_object_calibration::trb_saturation_min_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value - 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_saturation_min (this->trb_saturation_min->Value);
  this->txb_saturation_min->Text                                                          = System::String::Format ("{0:0}",this->trb_saturation_min->Value);
  }
System::Void c_frm_object_calibration::trb_saturation_max_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_max->Value = this->trb_saturation_min->Value + 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_saturation_max (this->trb_saturation_max->Value);
  this->txb_saturation_max->Text                                                          = System::String::Format ("{0:0}",this->trb_saturation_max->Value);
  }
System::Void c_frm_object_calibration::trb_value_min_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value - 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_value_min (this->trb_value_min->Value);
  this->txb_value_min->Text                                                          = System::String::Format ("{0:0}",this->trb_value_min->Value);
  }
System::Void c_frm_object_calibration::trb_value_max_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_max->Value = this->trb_value_min->Value + 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_value_max (this->trb_value_max->Value);
  this->txb_value_max->Text                                                          = System::String::Format ("{0:0}",this->trb_value_max->Value);
  }

System::Void c_frm_object_calibration::trb_ObjectSize_min_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_ObjectSize_min->Value > this->trb_ObjectSize_max->Value) this->trb_ObjectSize_min->Value = this->trb_ObjectSize_max->Value - 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_object_size_min (static_cast<uchar> (trb_ObjectSize_min->Value));
  txb_objectsize_min->Text                                                                 = trb_ObjectSize_min->Value.ToString();
  }
System::Void c_frm_object_calibration::trb_ObjectSize_max_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (this->trb_ObjectSize_min->Value > this->trb_ObjectSize_max->Value) this->trb_ObjectSize_max->Value = this->trb_ObjectSize_min->Value + 1;

  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_object_size_max  (static_cast<uchar> (trb_ObjectSize_max->Value));
  txb_objectsize_max->Text                                                                 = trb_ObjectSize_max->Value.ToString();
  }

System::Void c_frm_object_calibration::numUD_opening_iterations_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_opening_iterations (static_cast<int> (this->numUD_opening_iterations->Value));
  }
System::Void c_frm_object_calibration::numUD_opening_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_opening_kernel_size (static_cast<int> (this->numUD_opening_kernelsize->Value));
  }
System::Void c_frm_object_calibration::numUD_closing_iterations_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_closing_iterations (static_cast<int> (this->numUD_closing_iterations->Value));
  }
System::Void c_frm_object_calibration::numUD_closing_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_closing_kernel_size (static_cast<int> (this->numUD_closing_kernelsize->Value));
  }
System::Void c_frm_object_calibration::numUD_gaussian_kernel_size_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_gaussian_kernel_size (static_cast<int> (this->numUD_gaussian_kernel_size->Value));
  }
System::Void c_frm_object_calibration::numUD_gaussian_sigma_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_gaussian_sigma (static_cast<double> (this->numUD_gaussian_sigma->Value));
  }
System::Void c_frm_object_calibration::numUD_erode_iterations_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erosion_iterations (static_cast<int> (this->numUD_erode_iterations->Value));
  }
System::Void c_frm_object_calibration::numUD_erode_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erosion_kernel_size (static_cast<int> (this->numUD_erode_kernelsize->Value));
  }
System::Void c_frm_object_calibration::numUD_dilation_iterations_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilation_iterations (static_cast<int> (this->numUD_dilation_iterations->Value));
  }
System::Void c_frm_object_calibration::numUD_dilation_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilation_kernel_size (static_cast<int> (this->numUD_dilation_kernelsize->Value));
  }
System::Void c_frm_object_calibration::numUD_bilateral_spatial_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_sigma_spatial (static_cast<float> (this->numUD_bilateral_spatial->Value));
  }
System::Void c_frm_object_calibration::numUD_bilateral_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_kernel_size (static_cast<int> (this->numUD_bilateral_kernelsize->Value));
  }
System::Void c_frm_object_calibration::numUD_bilateral_color_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_sigma_color (static_cast<float> (this->numUD_bilateral_color->Value));
  }
System::Void c_frm_object_calibration::numUD_morph_iterations_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_iterations (static_cast<int> (this->numUD_morph_iterations->Value));
  }
System::Void c_frm_object_calibration::numUD_morph_kernelsize_ValueChanged (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_kernel_size (static_cast<int> (this->numUD_morph_kernelsize->Value));
  }


System::Void c_frm_object_calibration::chkb_erode_CheckStateChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (erode_active == false)
    {
    erode_active                                                                          = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erode_active(true);
    numUD_erode_iterations->Enabled                                                       = true;
    numUD_erode_kernelsize->Enabled                                                       = true;
    }
  else if (erode_active == true)
    {
    erode_active                                                                          = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erode_active (false);
    numUD_erode_iterations->Enabled                                                       = false;
    numUD_erode_kernelsize->Enabled                                                       = false;
    }
  }
System::Void c_frm_object_calibration::chkb_dilate_CheckStateChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (dilate_active == false)
    {
    dilate_active                                                                          = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilate_active (true);
    numUD_dilation_iterations->Enabled                                                     = true;
    numUD_dilation_kernelsize->Enabled                                                     = true;
    }
  else if (dilate_active == true)
    {
    dilate_active                                                                          = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilate_active (false);
    numUD_dilation_iterations->Enabled                                                     = false;
    numUD_dilation_kernelsize->Enabled                                                     = false;
    }
  }

System::Void c_frm_object_calibration::chkb_bilateral_CheckStateChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (bilateral_active == false)
    {
    numUD_bilateral_color->Enabled      = true;
    numUD_bilateral_spatial->Enabled    = true;
    numUD_bilateral_kernelsize->Enabled = true;
    }
  else if (bilateral_active == true)
    {
    numUD_bilateral_color->Enabled      = false;
    numUD_bilateral_spatial->Enabled    = false;
    numUD_bilateral_kernelsize->Enabled = false;
    }
  }
System::Void c_frm_object_calibration::chkb_morph_CheckStateChanged (System::Object^ sender, System::EventArgs^ e)
  {
  if (morph_active == false)
    {
    morph_active                                                                          = true;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_active (true);
    numUD_morph_iterations->Enabled                                                       = true;
    numUD_morph_kernelsize->Enabled                                                       = true;
    }
  else if (morph_active == true)
    {
    morph_active                                                                          = false;
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_active (false);
    numUD_morph_iterations->Enabled                                                       = false;
    numUD_morph_kernelsize->Enabled                                                       = false;
    }
  }
#pragma endregion
/*************************************************** Nicht öffentliche private Methoden *****************************************************/
System::Void c_frm_object_calibration::FillPicturebox (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
  {
  switch (ColorImageType)
    {
    case CV_8UC3: // non-grayscale images are correctly displayed here
      {
      System::Drawing::Graphics^  graphics = Picturebox->CreateGraphics();
      System::Drawing::Bitmap     bitmap (ColorImageCols,ColorImageRows,ColorImageStep,System::Drawing::Imaging::PixelFormat::Format24bppRgb,ColorImagePtr);
      System::Drawing::RectangleF rect (0,0,(float)Picturebox->Width,(float)Picturebox->Height);
      graphics->DrawImage (%bitmap,rect);
      delete (graphics);
      }
      break;
    case CV_8UC1: // grayscale images are incorrectly displayed here 
      {
      System::Drawing::Graphics^  graphics = Picturebox->CreateGraphics();
      System::Drawing::Bitmap     bitmap (ColorImageCols,ColorImageRows,(int)ColorImageStep,System::Drawing::Imaging::PixelFormat::Format8bppIndexed,ColorImagePtr);
      System::Drawing::RectangleF rect (0,0,(float)Picturebox->Width,(float)Picturebox->Height);
      graphics->DrawImage (%bitmap,rect);
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
System::Void c_frm_object_calibration::FillMat2Picturebox (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat& colorImage)
  {
  Int32          colorImage_cols = colorImage.cols;
  Int32          colorImage_rows = colorImage.rows;
  Int32          colorImage_step = colorImage.step;
  Int32          colorImage_type = colorImage.type();
  System::IntPtr colorImage_ptr (colorImage.ptr());

  FillPicturebox (Picturebox,colorImage_cols,colorImage_rows,colorImage_step,colorImage_type,colorImage_ptr);
  } // FillMatInToPictureBox
System::Void c_frm_object_calibration::bt_apply_Click (System::Object^ sender, System::EventArgs^ e)
  {
  Main->camera_managed->camera_unmanaged->save_camera_settings (static_cast<int> (numUD_cam_id->Value));
  }

System::Void c_frm_object_calibration::bt_apply_all_Click (System::Object^ sender, System::EventArgs^ e)
  {
  int current_camera = static_cast<int> (numUD_cam_id->Value);
  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_value_min(this->trb_value_min->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_value_max(this->trb_value_max->Value);

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_saturation_min(this->trb_saturation_min->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_saturation_max(this->trb_saturation_max->Value);

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_hue_min(this->trb_hue_min->Value);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_hue_max(this->trb_hue_max->Value);

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_opening_iterations (static_cast<int> (this->numUD_opening_iterations->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_opening_kernel_size(static_cast<int> (this->numUD_opening_kernelsize->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_closing_iterations (static_cast<int> (this->numUD_closing_iterations->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_closing_kernel_size(static_cast<int> (this->numUD_closing_kernelsize->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erode_active       (this->chkb_erode->Checked);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erosion_iterations (static_cast<int> (this->numUD_erode_iterations->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erosion_kernel_size(static_cast<int> (this->numUD_erode_kernelsize->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilate_active       (this->chkb_dilate->Checked);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilation_iterations (static_cast<int> (this->numUD_dilation_iterations->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilation_kernel_size(static_cast<int> (this->numUD_dilation_kernelsize->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_active     (this->chkb_morph->Checked);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_iterations (static_cast<int> (this->numUD_morph_iterations->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_kernel_size(static_cast<int> (this->numUD_morph_kernelsize->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_gaussian_sigma      (static_cast<double> (this->numUD_gaussian_sigma->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_gaussian_kernel_size(static_cast<int> (this->numUD_gaussian_kernel_size->Value));

    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_active       (this->chkb_bilateral->Checked);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_sigma_color  (static_cast<float> (this->numUD_bilateral_color->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_sigma_spatial(static_cast<float> (this->numUD_bilateral_spatial->Value));
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_kernel_size  (static_cast<int> (this->numUD_bilateral_kernelsize->Value));

    Main->camera_managed->camera_unmanaged->save_camera_settings (i);
    }
  }

System::Void c_frm_object_calibration::get_camera_settings (int camera_id)
  {
  this->trb_hue_min->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_hue_min());
  this->trb_hue_max->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_hue_max());

  this->trb_saturation_min->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_saturation_min());
  this->trb_saturation_max->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_saturation_max());

  this->trb_value_min->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_value_min());
  this->trb_value_max->Value = static_cast<int> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_value_max());

  this->numUD_opening_iterations->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_opening_iterations());
  this->numUD_opening_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_opening_kernel_size());

  this->numUD_closing_iterations->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_closing_iterations());
  this->numUD_closing_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_closing_kernel_size());

  this->chkb_erode->Checked           = this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->is_erode_active();
  this->numUD_erode_iterations->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_erosion_iterations());
  this->numUD_erode_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_erosion_kernel_size());

  this->chkb_dilate->Checked             = this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->is_dilate_active();
  this->numUD_dilation_iterations->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_dilation_iterations());
  this->numUD_dilation_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_dilation_kernel_size());

  this->chkb_morph->Checked           = this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->is_morph_active();
  this->numUD_morph_iterations->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_morph_iterations());
  this->numUD_morph_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_morph_kernel_size());

  this->numUD_gaussian_sigma->Value       = static_cast<Decimal> (Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_gaussian_sigma());
  this->numUD_gaussian_kernel_size->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_gaussian_kernel_size());

  this->chkb_bilateral->Checked           = this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->is_bilateral_active();
  this->numUD_bilateral_kernelsize->Value = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_bilateral_kernel_size());
  this->numUD_bilateral_spatial->Value    = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_bilateral_sigma_spatial());
  this->numUD_bilateral_color->Value      = static_cast<Decimal> (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id]->get_bilateral_sigma_color());
  }

System::Void c_frm_object_calibration::bt_Tracking_MouseClick (System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
  {
  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_idle              (false);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_show_cropped_image(false);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_undistord_active  (true);
    this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_filtering_active  (true);
    }
  this->Main->frm_object_tracking->Show();
  }
