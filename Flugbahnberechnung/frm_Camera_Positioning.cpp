#include "frm_Camera_Positioning.h"

using namespace nmsp_frm_camera_positioning;
using namespace nmsp_camera_unmanaged;

 c_frm_Camera_Positioning::c_frm_Camera_Positioning                                                 (C_GlobalObjects* GlobalObjects, C_Main^  Main)
   {
   InitializeComponent();
   this->GlobalObjects     = GlobalObjects;
   this->Main              = Main;
   this->cameras_in_use    = GlobalObjects->cameras_in_use;
   TimerWait  = 0;
   }

 c_frm_Camera_Positioning::~c_frm_Camera_Positioning                                                ()
   {
   TimerWait  = 0;

   this->Main              = nullptr;
   this->GlobalObjects     = nullptr;
   if (components)
     {
     delete components;
     }
   }

System::Void          c_frm_Camera_Positioning::taktgeber_Tick                                      (System::Object^  sender, System::EventArgs^  e)
  {
  this->txtb_counter->Text								= System::String::Format("{0:0}", this->Zaehler++);
  if (Zaehler > TimerWait+15)
    {
    switch (this->cameras_in_use)
      {
      case 1:   //Nur zu Testzwecken für die Laptopverwendung
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        break;

      case 2:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        break;

      case 4:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L2, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R2, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
        break;

      case 6:
        FillMat2Picturebox(pb_Camera_L1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R1, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L2, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R2, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_L3, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L3->Value)]->cpu_src_img);
        FillMat2Picturebox(pb_Camera_R3, Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R3->Value)]->cpu_src_img);
        break;
        }
    }

  }
System::Void          c_frm_Camera_Positioning::bt_apply_Click                                      (System::Object^  sender, System::EventArgs^  e)
  {
  this->Taktgeber->Enabled=false;
  std::vector<int> camera_list;

  switch (this->cameras_in_use)                              
    {
      case 1:   //Nur zu Testzwecken für die Laptopverwendung
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));

        camera_list.push_back(static_cast<int> (nup_Camera_L1->Value));

        nup_Camera_L1->Value = 0;

        break;

      case 2:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));

        camera_list.push_back(static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R1->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;

        break;

      case 4:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(2, static_cast<int> (nup_Camera_L2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(3, static_cast<int> (nup_Camera_R2->Value));

        camera_list.push_back(static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R1->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_L2->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R2->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;
        nup_Camera_L2->Value = 2;
        nup_Camera_R2->Value = 3;

        break;

      case 6:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(0, static_cast<int> (nup_Camera_L1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(1, static_cast<int> (nup_Camera_R1->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(2, static_cast<int> (nup_Camera_L2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(3, static_cast<int> (nup_Camera_R2->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(4, static_cast<int> (nup_Camera_L3->Value));
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp(5, static_cast<int> (nup_Camera_R3->Value));

        camera_list.push_back(static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R1->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_L2->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R2->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_L3->Value));
        camera_list.push_back(static_cast<int> (nup_Camera_R3->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;
        nup_Camera_L2->Value = 2;
        nup_Camera_R2->Value = 3;
        nup_Camera_L3->Value = 4;
        nup_Camera_R3->Value = 5;

        break;
    }

  Main->camera_managed->camera_unmanaged->move_camera_temp2vector(this->GlobalObjects->cameras_in_use);
  Main->camera_managed->camera_unmanaged->save_camera_positioning(camera_list);


  TimerWait = Zaehler + 5;
  this->Taktgeber->Enabled=true;
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
  this->cameras_in_use                    = GlobalObjects->cameras_in_use;
  this->set_numUD_value(*GlobalObjects->camera_order);
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
System::Void          c_frm_Camera_Positioning::FillMat2Picturebox                                  (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage)
  {
  Int32                              colorImage_cols   =   colorImage->cols;
  Int32                              colorImage_rows   =   colorImage->rows;
  Int32                              colorImage_step   =   colorImage->step;
  Int32                              colorImage_type   =   colorImage->type();
  System::IntPtr                     colorImage_ptr  (colorImage->ptr());

  FillPicturebox                     (Picturebox, colorImage_cols, colorImage_rows, colorImage_step, colorImage_type, colorImage_ptr);
  } // FillMatInToPictureBox

System::Void          c_frm_Camera_Positioning::set_numUD_value                                     ()
  {
  Int32 maximum = static_cast<Int32> (cameras_in_use);
  this->nup_Camera_L1->Value = maximum;
  this->nup_Camera_R1->Value = maximum;
  this->nup_Camera_L2->Value = maximum;
  this->nup_Camera_R2->Value = maximum;
  this->nup_Camera_L3->Value = maximum;
  this->nup_Camera_R3->Value = maximum;

  switch (this->cameras_in_use)
    {
      case 1:   //Nur zu Testzwecken für die Laptopverwendung
        this->nup_Camera_L1->Value = 0;
        break;

      case 2:
        this->nup_Camera_L1->Value = 0;
        this->nup_Camera_R1->Value = 1;
        break;

      case 4:
        this->nup_Camera_L1->Value = 0;
        this->nup_Camera_R1->Value = 1;
        this->nup_Camera_L2->Value = 2;
        this->nup_Camera_R2->Value = 3;
        break;

      case 6:
        this->nup_Camera_L1->Value = 0;
        this->nup_Camera_R1->Value = 1;
        this->nup_Camera_L2->Value = 2;
        this->nup_Camera_R2->Value = 3;
        this->nup_Camera_L3->Value = 4;
        this->nup_Camera_R3->Value = 5;
        break;
    }
  }
System::Void          c_frm_Camera_Positioning::set_numUD_value                                     (std::vector<int> camera_list)
  {
  Int32 maximum = static_cast<Int32> (cameras_in_use);
  this->nup_Camera_L1->Value = maximum;
  this->nup_Camera_R1->Value = maximum;
  this->nup_Camera_L2->Value = maximum;
  this->nup_Camera_R2->Value = maximum;
  this->nup_Camera_L3->Value = maximum;
  this->nup_Camera_R3->Value = maximum;

  switch (this->cameras_in_use)
    {
      case 1:   //Nur zu Testzwecken für die Laptopverwendung
        this->nup_Camera_L1->Value = camera_list[0];
        break;

      case 2:
        this->nup_Camera_L1->Value = camera_list[0];
        this->nup_Camera_R1->Value = camera_list[1];
        break;

      case 4:
        this->nup_Camera_L1->Value = camera_list[0];
        this->nup_Camera_R1->Value = camera_list[1];
        this->nup_Camera_L2->Value = camera_list[2];
        this->nup_Camera_R2->Value = camera_list[3];
        break;

      case 6:
        this->nup_Camera_L1->Value = camera_list[0];
        this->nup_Camera_R1->Value = camera_list[1];
        this->nup_Camera_L2->Value = camera_list[2];
        this->nup_Camera_R2->Value = camera_list[3];
        this->nup_Camera_L3->Value = camera_list[4];
        this->nup_Camera_R3->Value = camera_list[5];
        break;
    }
  }
