#include "frm_Camera_Positioning.h"

using namespace nmsp_frm_camera_positioning;
using namespace nmsp_camera_unmanaged;

 c_frm_Camera_Positioning::c_frm_Camera_Positioning                                                 (C_GlobalObjects^ GlobalObjects, C_Main^  Main)
   {
   InitializeComponent();
   this->GlobalObjects     = GlobalObjects;
   this->Main              = Main;
   }

 c_frm_Camera_Positioning::~c_frm_Camera_Positioning                                                ()
   {
   this->Main              = nullptr;
   this->GlobalObjects     = nullptr;
   if (components)
     {
     delete components;
     }
   }

System::Void          c_frm_Camera_Positioning::nup_Camera_L1_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::nup_Camera_L2_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::nup_Camera_L3_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::nup_Camera_R1_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::nup_Camera_R2_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::nup_Camera_R3_ValueChanged                          (System::Object^  sender, System::EventArgs^  e)
  {

  }
System::Void          c_frm_Camera_Positioning::taktgeber_Tick                                      (System::Object^  sender, System::EventArgs^  e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);

  switch (GlobalObjects->cameras_in_use-1)
    {
      case 0:   //Nur zu Testzwecken für die Laptopverwendung
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        break;

      case 1:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        break;

      case 3:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L2, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R2, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
        break;

      case 5:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L2, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R2, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L3, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_L3->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R3, Main->camera_managed->camera_unmanaged->camera_vector_unsorted[static_cast<int> (nup_Camera_R3->Value)]->cpu_src_img);
        break;
    }


  }
System::Void          c_frm_Camera_Positioning::bt_appy_Click                                       (System::Object^  sender, System::EventArgs^  e)
  {
  switch (GlobalObjects->cameras_in_use-1)
    {
      case 0:   //Nur zu Testzwecken für die Laptopverwendung
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        break;

      case 1:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));
        break;

      case 3:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(2, static_cast<int> (nup_Camera_L2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(3, static_cast<int> (nup_Camera_R2->Value));
        break;

      case 5:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(2, static_cast<int> (nup_Camera_L2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(3, static_cast<int> (nup_Camera_R2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(4, static_cast<int> (nup_Camera_L3->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(5, static_cast<int> (nup_Camera_R3->Value));
        break;
    }
  Main->camera_managed->camera_unmanaged->move_camera_temp2vector();

  }
System::Void          c_frm_Camera_Positioning::c_frm_Camera_Positioning_FormClosing                (System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
  {
  this->Taktgeber->Enabled                = false;
  }
System::Void          c_frm_Camera_Positioning::c_frm_Camera_Positioning_Load                       (System::Object^  sender, System::EventArgs^  e)
  {
  this->Zaehler                           = 0;
  this->Taktgeber->Interval               = 100;
  this->Taktgeber->Enabled                = true;
  }
System::Void          c_frm_Camera_Positioning::bt_exit_Click                                       (System::Object^  sender, System::EventArgs^  e)
  {
  this->Close();
  }
System::Void          c_frm_Camera_Positioning::FillPicturebox                                      (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr)
  {
            System::Drawing::Graphics^    graphics = Picturebox->CreateGraphics();
            System::Drawing::Bitmap       bitmap   (ColorImageCols, ColorImageRows, ColorImageStep, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ColorImagePtr);
            System::Drawing::RectangleF   rect (0, 0, (float)Picturebox->Width, (float)Picturebox->Height);
            graphics->DrawImage           (%bitmap, rect);
            delete (graphics);
  }
System::Void          c_frm_Camera_Positioning::FillMat2Picturebox                                  (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage)
  {
  Int32                              colorImage_cols   =   colorImage.cols;
  Int32                              colorImage_rows   =   colorImage.rows;
  Int32                              colorImage_step   =   colorImage.step;
  Int32                              colorImage_type   =   colorImage.type();
  System::IntPtr                     colorImage_ptr  (colorImage.ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox



