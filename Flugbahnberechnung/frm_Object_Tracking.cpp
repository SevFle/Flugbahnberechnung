#include "frm_Object_Tracking.h"

using namespace nsmp_frm_object_tracking;

c_frm_Object_Tracking::c_frm_Object_Tracking (C_GlobalObjects* GlobalObjects, C_Main^  Main)
{
  InitializeComponent                                          ();
  this->GlobalObjects                       = GlobalObjects;
  this->Main                                = Main;
  }

c_frm_Object_Tracking::~c_frm_Object_Tracking ()
  {
  this->Main                    = nullptr;
  this->GlobalObjects           = nullptr;
  if (components)
    {
    delete components;
    }

  }

System::Void c_frm_Object_Tracking::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Close();
  }

System::Void c_frm_Object_Tracking::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format("{0:0}", this->Zaehler++);
  if(this->Zaehler > TimerWait)
    {
    this->FillMat2Picturebox(pb_cam_left, *this->Main->camera_managed->camera_unmanaged->camera_vector[this->camera_id_in_use]->  cpu_contoured);
    this->FillMat2Picturebox(pb_cam_right, *this->Main->camera_managed->camera_unmanaged->camera_vector[this->camera_id_in_use+1]->cpu_contoured);
    }
  }

System::Void c_frm_Object_Tracking::FillPicturebox (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
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

System::Void c_frm_Object_Tracking::FillMat2Picturebox (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat& colorImage)
  {
  Int32                              colorImage_cols      =   colorImage.cols;
  Int32                              colorImage_rows      =   colorImage.rows;
  Int32                              colorImage_step      =   colorImage.step;
  Int32                              colorImage_type      =   colorImage.type  ();
  System::IntPtr                     colorImage_ptr       (colorImage.ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  }

System::Void c_frm_Object_Tracking::c_frm_Object_Tracking_Load(System::Object^  sender, System::EventArgs^  e)
  {
  this->Taktgeber->Enabled =true;
  this->TimerWait = 15;
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->undistord_active = true;
  this->Main->camera_managed->camera_unmanaged->camera_vector[1]->undistord_active = true;
  this->Main->camera_managed->camera_unmanaged->camera_vector[0]->filtering_active = true;
  this->Main->camera_managed->camera_unmanaged->camera_vector[1]->filtering_active = true;
  }
System::Void c_frm_Object_Tracking::c_frm_Object_Tracking_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
  {
  this->Taktgeber->Enabled =false;
  }
System::Void c_frm_Object_Tracking::bt_start_Click(System::Object^  sender, System::EventArgs^  e)
  {
  this->lbl_thread_running->Enabled = true;

  this->tracking->Start();
  }

System::Void c_frm_Object_Tracking::tracking_thread ()
  {
  this->Main->camera_managed->camera_unmanaged->sm_object_tracking();
  }

