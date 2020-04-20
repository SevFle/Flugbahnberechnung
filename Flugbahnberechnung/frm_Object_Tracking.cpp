#include "frm_Object_Tracking.h"

using namespace nsmp_object_tracking;

c_frm_Object_Tracking::c_frm_Object_Tracking (C_GlobalObjects* GlobalObjects, C_Main^  Main)
{
  InitializeComponent                                          ();
  this->GlobalObjects                       = GlobalObjects;
  this->Main                                = Main;
  }

c_frm_Object_Tracking::~c_frm_Object_Tracking ()
  {
  if (components)
    {
    delete components;
    }
  this->Main                    = nullptr;
  this->GlobalObjects           = nullptr;

  }

System::Void c_frm_Object_Tracking::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Close();
  }

System::Void c_frm_Object_Tracking::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format("{0:0}", this->Zaehler++);
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



