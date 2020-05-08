#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_unmanaged.h"

#include <thread>

/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_camera_unmanaged;
using namespace nmsp_GlobalObjects;

/*************************************************************** Konstruktoren **************************************************************/
c_camera_unmanaged::c_camera_unmanaged (int cameras_in_use, C_GlobalObjects* GlobalObjects)
  {
  this->cameras_in_use       = cameras_in_use;
  this->tracking_thread      = new c_tracking (GlobalObjects);
  this->tracked_data         = new nmsp_tracking::s_tracking_data();
  this->vec_WorldToCam_Poses = new std::vector<C_AbsolutePose>;
  stop_statemachine          = false;
  this->GlobalObjects        = GlobalObjects;
  load_positioning           = false;
  tracking_active            = false;
  numCornersWidth            = 0;
  numCornersHeight           = 0;
  SquareSize                 = 0;
  numBoards_imgs             = 0;
  Photo_ID                   = 0;
  }
/**************************************************************** Destruktor ****************************************************************/
c_camera_unmanaged::~c_camera_unmanaged ()
  {
  Photo_ID         = 0;
  numBoards_imgs   = 0;
  SquareSize       = 0;
  numCornersHeight = 0;
  numCornersWidth  = 0;
  tracking_active  = false;

  load_positioning  = false;
  GlobalObjects     = nullptr;
  stop_statemachine = false;
  cameras_in_use    = 0;
  delete(this->vec_WorldToCam_Poses);
  vec_WorldToCam_Poses = nullptr;
  delete(this->tracked_data);
  tracked_data = nullptr;

  delete(this->tracking_thread);
  this->tracking_thread = nullptr;
  }

/*************************************************** Nicht öffentliche private Methoden *****************************************************/

void c_camera_unmanaged::start_camera_thread ()
  {
  camera_vector[current_camera_id]->set_idle (true);

  camera_vector[current_camera_id]->camera_thread();
  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void c_camera_unmanaged::save_camera_settings (int camera_id)
  {
  string Dateiname = "../Parameter/Camera_setting" + to_string (camera_id) + ".csv";
  string Dateityp  = "Value of the individual setting";


  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);


  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");


    GlobalObjects->csv_parameter_datei->Schreiben ("hue_min",to_string (camera_vector[camera_id]->get_hue_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("hue_max",to_string (camera_vector[camera_id]->get_hue_max()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("saturation_min",to_string (camera_vector[camera_id]->get_saturation_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("saturation_max",to_string (camera_vector[camera_id]->get_saturation_max()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("value_min",to_string (camera_vector[camera_id]->get_value_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("value_max",to_string (camera_vector[camera_id]->get_value_max()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("erosion_iterations",to_string (camera_vector[camera_id]->get_erosion_iterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("dilation_iterations",to_string (camera_vector[camera_id]->get_dilation_iterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("opening_iteration",to_string (camera_vector[camera_id]->get_opening_iterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("closing_iteration",to_string (camera_vector[camera_id]->get_closing_iterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("morph_iteration",to_string (camera_vector[camera_id]->get_morph_iterations()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("erosion_kernel_size",to_string (camera_vector[camera_id]->get_erosion_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("dilation_kernel_size",to_string (camera_vector[camera_id]->get_dilation_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("opening_kernel_size",to_string (camera_vector[camera_id]->get_opening_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("closing_kernel_size",to_string (camera_vector[camera_id]->get_closing_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("morph_kernel_size",to_string (camera_vector[camera_id]->get_morph_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("gaussian_kernel_size",to_string (camera_vector[camera_id]->get_gaussian_kernel_size()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_kernel_size",to_string (camera_vector[camera_id]->get_bilateral_kernel_size()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("gaussian_sigma",to_string (camera_vector[camera_id]->get_gaussian_sigma()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_sigma_color",to_string (camera_vector[camera_id]->get_bilateral_sigma_color()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_sigma_spatial",to_string (camera_vector[camera_id]->get_bilateral_sigma_spatial()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("Erode_Active",to_string (camera_vector[camera_id]->is_erode_active()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("Dilate_Active",to_string (camera_vector[camera_id]->is_dilate_active()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("Morph_Active",to_string (camera_vector[camera_id]->is_morph_active()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("Bilateral_Active",to_string (camera_vector[camera_id]->is_bilateral_active()),"[1]");
    }
  this->GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_camera_unmanaged::load_camera_settings (int camera_id)
  {
  string Dateiname      = "../Parameter/Camera_setting" + to_string (camera_id) + ".csv";
  string Dateityp       = "Value of the individual setting";
  int    hue_min        = 0;
  int    hue_max        = 0;
  int    saturation_min = 0;
  int    saturation_max = 0;
  int    value_min      = 0;
  int    value_max      = 0;

  int erosion_iterations  = 0;
  int dilation_iterations = 0;
  int opening_iterations  = 0;
  int closing_iterations  = 0;
  int morph_iterations    = 0;

  int erosion_kernel_size   = 0;
  int dilation_kernel_size  = 0;
  int opening_kernel_size   = 0;
  int closing_kernel_size   = 0;
  int morph_kernel_size     = 0;
  int gaussian_kernel_size  = 0;
  int bilateral_kernel_size = 0;

  double gaussian_sigma = 0.0;


  float bilateral_sigma_color   = 0.0;
  float bilateral_sigma_spatial = 0.0;

  bool erode_active     = false;
  bool dilation_active  = false;
  bool morph_active     = false;
  bool bilateral_active = false;


  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);

  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Lesen (Dateityp);

    GlobalObjects->csv_parameter_datei->Lesen (hue_min);
    GlobalObjects->csv_parameter_datei->Lesen (hue_max);
    GlobalObjects->csv_parameter_datei->Lesen (saturation_min);
    GlobalObjects->csv_parameter_datei->Lesen (saturation_max);
    GlobalObjects->csv_parameter_datei->Lesen (value_min);
    GlobalObjects->csv_parameter_datei->Lesen (value_max);

    GlobalObjects->csv_parameter_datei->Lesen (erosion_iterations);
    GlobalObjects->csv_parameter_datei->Lesen (dilation_iterations);
    GlobalObjects->csv_parameter_datei->Lesen (opening_iterations);
    GlobalObjects->csv_parameter_datei->Lesen (closing_iterations);
    GlobalObjects->csv_parameter_datei->Lesen (morph_iterations);

    GlobalObjects->csv_parameter_datei->Lesen (erosion_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (dilation_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (opening_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (closing_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (morph_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (gaussian_kernel_size);
    GlobalObjects->csv_parameter_datei->Lesen (bilateral_kernel_size);

    GlobalObjects->csv_parameter_datei->Lesen (gaussian_sigma);

    GlobalObjects->csv_parameter_datei->Lesen (bilateral_sigma_color);
    GlobalObjects->csv_parameter_datei->Lesen (bilateral_sigma_spatial);

    GlobalObjects->csv_parameter_datei->Lesen (erode_active);
    GlobalObjects->csv_parameter_datei->Lesen (dilation_active);
    GlobalObjects->csv_parameter_datei->Lesen (morph_active);
    GlobalObjects->csv_parameter_datei->Lesen (bilateral_active);


    camera_vector[camera_id]->set_hue_min       (hue_min);
    camera_vector[camera_id]->set_hue_max       (hue_max);
    camera_vector[camera_id]->set_saturation_min(saturation_min);
    camera_vector[camera_id]->set_saturation_max(saturation_max);
    camera_vector[camera_id]->set_value_min     (value_min);
    camera_vector[camera_id]->set_value_max     (value_max);

    camera_vector[camera_id]->set_erosion_iterations (erosion_iterations);
    camera_vector[camera_id]->set_dilation_iterations(dilation_iterations);
    camera_vector[camera_id]->set_opening_iterations (opening_iterations);
    camera_vector[camera_id]->set_closing_iterations (closing_iterations);
    camera_vector[camera_id]->set_morph_iterations   (morph_iterations);

    camera_vector[camera_id]->set_erosion_kernel_size  (erosion_kernel_size);
    camera_vector[camera_id]->set_dilation_kernel_size (dilation_kernel_size);
    camera_vector[camera_id]->set_opening_kernel_size  (opening_kernel_size);
    camera_vector[camera_id]->set_closing_kernel_size  (closing_kernel_size);
    camera_vector[camera_id]->set_morph_kernel_size    (morph_kernel_size);
    camera_vector[camera_id]->set_gaussian_kernel_size (gaussian_kernel_size);
    camera_vector[camera_id]->set_bilateral_kernel_size(bilateral_kernel_size);

    camera_vector[camera_id]->set_gaussian_sigma(gaussian_sigma);

    camera_vector[camera_id]->set_bilateral_sigma_color  (bilateral_sigma_color);
    camera_vector[camera_id]->set_bilateral_sigma_spatial(bilateral_sigma_spatial);

    camera_vector[camera_id]->set_dilate_active   (dilation_active);
    camera_vector[camera_id]->set_erode_active    (erode_active);
    camera_vector[camera_id]->set_morph_active    (morph_active);
    camera_vector[camera_id]->set_bilateral_active(bilateral_active);
    }
  std::cout << "Loaded Settings for Camera " << camera_id << "." << endl;
  }

void c_camera_unmanaged::save_camera_calibration (int camera_id)
  {
  string Dateiname = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (camera_id) + ".csv";
  string Dateityp  = "Intrinisic and distortion parameters of camera-single-calibration";
  int    numBoards = this->numBoards_imgs;

  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  int    real_size_width  = this->camera_vector[camera_id]->get_resize_width();
  int    real_size_height = this->camera_vector[camera_id]->get_resize_height();

  this->camera_vector[camera_id]->get_calibration_parameter (DistCoeffs,Intrinsic);

  this->GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);

  this->GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Anzahl Boards",numBoards,"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Distortion k1",DistCoeffs[0][0],"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Distortion k2",DistCoeffs[0][1],"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Distortion p1",DistCoeffs[0][2],"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Distortion p2",DistCoeffs[0][3],"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Distortion k3",DistCoeffs[0][4],"[1]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic fx",Intrinsic[0][0],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 01",Intrinsic[0][1],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic cx",Intrinsic[0][2],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 10",Intrinsic[1][0],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic fy",Intrinsic[1][1],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic cy",Intrinsic[1][2],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 20",Intrinsic[2][0],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 21",Intrinsic[2][1],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 22",Intrinsic[2][2],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 21",Intrinsic[2][1],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Intrinsic 22",Intrinsic[2][2],"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Resize Width",real_size_width,"[Px]");
  this->GlobalObjects->csv_parameter_datei->Schreiben ("Resize Height",real_size_height,"[Px]");


  std::cout << "Camera " << camera_id << " Saved Distortion k1 " << to_string (DistCoeffs[0][0]) << endl;
  std::cout << "Camera " << camera_id << " Saved Distortion k2 " << to_string (DistCoeffs[0][1]) << endl;
  std::cout << "Camera " << camera_id << " Saved Distortion p1 " << to_string (DistCoeffs[0][2]) << endl;
  std::cout << "Camera " << camera_id << " Saved Distortion p2 " << to_string (DistCoeffs[0][3]) << endl;
  std::cout << "Camera " << camera_id << " Saved Distortion k3 " << to_string (DistCoeffs[0][4]) << endl;

  std::cout << "Camera " << camera_id << " Saved Intrinsic fx " << to_string (Intrinsic[0][0]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic 01 " << to_string (Intrinsic[0][1]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic cx " << to_string (Intrinsic[0][2]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic 10 " << to_string (Intrinsic[1][0]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic fy " << to_string (Intrinsic[1][1]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic cy " << to_string (Intrinsic[1][2]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic 20 " << to_string (Intrinsic[2][0]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic 21 " << to_string (Intrinsic[2][1]) << endl;
  std::cout << "Camera " << camera_id << " Saved Intrinsic 22 " << to_string (Intrinsic[2][2]) << endl;


  this->GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_camera_unmanaged::load_camera_calibration (int camera_id)
  {
  string Dateiname = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (camera_id) + ".csv";
  string Dateityp  = "Intrinisic and distortion parameters of camera-single-calibration";
  int    numBoards;
  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  int    real_size_width;
  int    real_size_height;

  this->GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);

  if (this->GlobalObjects->csv_parameter_datei->IsOpen())
    {
    this->GlobalObjects->csv_parameter_datei->Lesen (Dateityp);
    this->GlobalObjects->csv_parameter_datei->Lesen (numBoards);
    this->GlobalObjects->csv_parameter_datei->Lesen (DistCoeffs[0][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen (DistCoeffs[0][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen (DistCoeffs[0][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen (DistCoeffs[0][3]);
    this->GlobalObjects->csv_parameter_datei->Lesen (DistCoeffs[0][4]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[0][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[0][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[0][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[1][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[1][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[1][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[2][0]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[2][1]);
    this->GlobalObjects->csv_parameter_datei->Lesen (Intrinsic[2][2]);
    this->GlobalObjects->csv_parameter_datei->Lesen (real_size_width);
    this->GlobalObjects->csv_parameter_datei->Lesen (real_size_height);
    this->GlobalObjects->csv_parameter_datei->Schliessen();
    }
  else
    {
    numBoards        = 50;
    DistCoeffs[0][0] = -0.422409;
    DistCoeffs[0][1] = -0.102515;
    DistCoeffs[0][2] = -0.005320;
    DistCoeffs[0][3] = 0.001334;
    DistCoeffs[0][4] = 2.581073;
    Intrinsic[0][0]  = 946.734995;
    Intrinsic[0][1]  = 0.000000;
    Intrinsic[0][2]  = 279.097216;
    Intrinsic[1][0]  = 0.000000;
    Intrinsic[1][1]  = 948.766038;
    Intrinsic[1][2]  = 254.572998;
    Intrinsic[1][0]  = 0.000000;
    Intrinsic[2][1]  = 0.000000;
    Intrinsic[2][2]  = 1.000000;
    }

  this->camera_vector[camera_id]->set_calibration_parameter (DistCoeffs,Intrinsic);
  this->camera_vector[camera_id]->set_resize_height (real_size_height);
  this->camera_vector[camera_id]->set_resize_width  (real_size_width);

  std::cout << "Loaded Calibration for Camera " << camera_id << "." << endl;
  }

void c_camera_unmanaged::save_camera_positioning (std::vector<int> camera_list) const
  {
  string Dateiname = "../Parameter/Camera_Positioning.csv";
  string Dateityp  = "Correct Camera position in vector corresponding to their ID";

  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);

  GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
  GlobalObjects->csv_parameter_datei->Schreiben ("Anzahl Kameras",to_string (GlobalObjects->cameras_in_use),"[1]");


  for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
    {
    GlobalObjects->csv_parameter_datei->Schreiben ("Cameravector[" + to_string (i) + "]",to_string (camera_list[i]),"[1]");
    std::cout << "Saving Camera " << i << " to position " << camera_list[i];
    }


  GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_camera_unmanaged::load_camera_positioning ()
  {
  string                                                  Dateiname = "../Parameter/Camera_Positioning.csv";
  string                                                  Dateityp;
  std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*> camera_vector_temp;
  camera_vector_temp.resize (GlobalObjects->cameras_in_use);

  int id;
  int Camera_count;

  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Lesen (Dateityp);
    GlobalObjects->csv_parameter_datei->Lesen (Camera_count);
    if (GlobalObjects->cameras_in_use == Camera_count)
      {
      for (int i = 0; i < Camera_count; i++)
        {
        GlobalObjects->csv_parameter_datei->Lesen (id);
        GlobalObjects->camera_order->push_back (id);
        move_camera_vector2temp (i,id,camera_vector_temp);
        }

      move_camera_temp2vector (Camera_count,camera_vector_temp);
      load_positioning = true;
      }
    }
  std::cout << "Loaded Positioning." << endl;
  }

void c_camera_unmanaged::load_camera_cos (int camera_id, C_AbsolutePose& WorldToCam_Param)
  {
  string Dateiname = "../Parameter/Pose_world_to_camera" + to_string (camera_id) + ".csv";
  string Dateityp;
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

  //TODO Rotation der Kameras einfügen
  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Lesen (Dateityp);
    GlobalObjects->csv_parameter_datei->Lesen (nx);
    GlobalObjects->csv_parameter_datei->Lesen (ny);
    GlobalObjects->csv_parameter_datei->Lesen (nz);
    GlobalObjects->csv_parameter_datei->Lesen (ox);
    GlobalObjects->csv_parameter_datei->Lesen (oy);
    GlobalObjects->csv_parameter_datei->Lesen (oz);
    GlobalObjects->csv_parameter_datei->Lesen (ax);
    GlobalObjects->csv_parameter_datei->Lesen (ay);
    GlobalObjects->csv_parameter_datei->Lesen (az);
    GlobalObjects->csv_parameter_datei->Lesen (px);
    GlobalObjects->csv_parameter_datei->Lesen (py);
    GlobalObjects->csv_parameter_datei->Lesen (pz);

    WorldToCam_Param.nx (nx);
    WorldToCam_Param.ny (ny);
    WorldToCam_Param.nz (nz);
    WorldToCam_Param.ox (ox);
    WorldToCam_Param.oy (oy);
    WorldToCam_Param.oz (oz);
    WorldToCam_Param.ax (ax);
    WorldToCam_Param.ay (ay);
    WorldToCam_Param.az (az);
    WorldToCam_Param.px (px);
    WorldToCam_Param.py (py);
    WorldToCam_Param.pz (pz);
    }
  }


void c_camera_unmanaged::init_camera_vectors (int cameras_in_use)
  {
  //Create a camera object and start its according thread. The amount of objects equals the amount of cameras in use 
  for (int i = 0; i < cameras_in_use; i++)
    {
    auto* opencv_unmanaged = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    opencv_unmanaged->set_idle (true);
    camera_vector.push_back (opencv_unmanaged);

    std::cout << "Created " << i + 1 << " Camera Objects with according pointers" << std::endl;


    current_camera_id = i;
    //camera_thread   = new std::thread                       (&c_camera_unmanaged::start_camera_thread, this);
    this->camera_thread = new std::thread (&c_camera_unmanaged::start_camera_thread,this);
    }

  //Reorder recently created Cameras
  this->load_camera_positioning();

  //Load Settings and Calibration for each camera created earlier
  for (int i = 0; i < cameras_in_use; i++)
    {
    this->load_camera_calibration (i);
    this->load_camera_settings (i);
    }
  }
void c_camera_unmanaged::close_cameras (int cameras_in_use)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector[i]->cap->release();
    camera_vector[i]->set_thread_running (false);
    }
  }

void c_camera_unmanaged::move_camera_vector2temp (int camera_desired_id, int camera_current_id, std::vector<c_opencv_unmanaged*>& temp_CameraVector)
  {
  // Wo ist die feste Position der Kamera? -> Camera_Current_ID
  // Wo ist die Position der Kamera im unsorted Vector? ->Camera_desired_id
  // Zeige die fest installierte Position des Vektors "Referrences" auf die Adresse im Unsortierten Vektor
  temp_CameraVector[camera_desired_id] = std::move (camera_vector[camera_current_id]);
  //camera_vector_temp.insert(camera_vector_temp.begin()+camera_desired_id, camera_vector[camera_current_id]);
  std::cout << " Moved Pointer for Camera " << camera_current_id << " to Position " << camera_desired_id << " in temporary Vector" << std::endl;
  }
void c_camera_unmanaged::move_camera_temp2vector (int cameras_in_use, std::vector<c_opencv_unmanaged*> temp_CameraVector)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector[i] = std::move (temp_CameraVector[i]);
    }
  }

void c_camera_unmanaged::calibrate_single_camera (int current_camera_id)
  {
  // Deklaration benötigter Variablen
  cv::Mat                     Originalbild;
  cv::Mat                     Grau_Bild;
  vector<cv::Point2f>         Corners;
  cv::Size                    Board_Sz = cv::Size (this->numCornersWidth,this->numCornersHeight);
  cv::Mat                     intrinsic (cv::Mat_<double> (3,3));
  cv::Mat                     distCoeffs;
  vector<cv::Point3f>         Obj;
  vector<vector<cv::Point3f>> Object_Points;
  vector<vector<cv::Point2f>> Image_Points;
  vector<cv::Mat>             Rvecs;
  vector<cv::Mat>             Tvecs;
  vector<cv::Mat>             TCP_Orientation;
  vector<cv::Mat>             TCP_Position;

  this->Photo_ID  = 0;
  int error_count = 0;

  // Füllen des "Obj"-Vektors mit 3D-Koordinaten der Schachbrett-Ecken. Die Koordinaten werden manuell vorgegeben und ergeben sich über Länge
  // und Breite der Schachbrett-Rechtecke über die gesamte Länge und Breite des Schachbrettes. Das Schachbrett-Rechteck hat eine Größe von
  // 24.23mm x 24.23mm. Damit ergeben sich die Koordinaten (x, y, z) wie folgt: (0, 0, 0), (24.23, 0, 0), (48.46, 0, 0), .... z ist immer null,
  // da die Rechtecke auf einer Ebene liegen und der Koordinatensystemursprung (Welt) auf dem Schachbrett liegt.
  for (int i = 0; i < this->numCornersHeight; i++)
    {
    for (int j = 0; j < this->numCornersWidth; j++)
      {
      Obj.push_back (cv::Point3f ((float)j * this->SquareSize,(float)i * this->SquareSize,0.0f));
      }
    }

  // Abarbeiten aller gespeicherten Bilder
  while (this->Photo_ID < this->numBoards_imgs)
    {
    std::cout << "Processing image " << Photo_ID << " out of " << numBoards_imgs << " images." << endl;
    // Laden des Bildes mit der angegebenen Photo_ID
    Originalbild = cv::imread ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (this->Photo_ID) + ".png",1);

    // Umwandeln des geladenen Bildes in ein Grauwertbild und abspeichern dieses in einem anderen Bild-Array
    cvtColor (Originalbild,Grau_Bild,cv::COLOR_BGR2GRAY);

    // Das geladenene Originalbild nach Schachbrett-Ecken absuchen. Die Anzahl der inneren Ecken über Länge und Breite wird über "Board_Sz" vorgegeben und
    // die gefundenen Ecken werden in "Corners" abgespeichert. Es wird eine adaptive Schwellwertbildung genutzt und das Bild wird nach Rechtecken
    // gefiltert. "Found" wird nur true, wenn alle Ecken gefunden wurden. Die Ecken-Koordinaten aus "Corners" sind 2D-Koordinaten der Bildebene.
    bool Found = findChessboardCorners (Grau_Bild,Board_Sz,Corners,cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_FILTER_QUADS + cv::CALIB_CB_NORMALIZE_IMAGE);

    if (!Found) error_count++;

    if (Found) // Falls Rechtecke gefunden wurden
      {
      // Mit Hilfe der gefundenen Ecken in "Corners" werden im Graustufenbild nun die Ecken-Standorte verfeinert. Mit den beiden "Size"-Angaben
      // wird die Größe der abzusuchenden Bereiche in jedem Iterationsschritt angegeben. Der erste Wert legt die Fenstergröße auf (2*5+1) x (2*5+1) = 11x11
      // fest, der zweite Wert legt die Mindestgröße fest, wobei die Werte -1 angeben, dass es keine "Totzone" gibt. Mit "TermCriteria" werden die
      // Ausstiegbedingungen für den Iterationsvorgang angegeben. "EPS" legt eine gewünschte Genauigkeit bzw. Parameteränderung von 0.1 fest. "MAX_ITER"
      // legt die Anzahl der maximalen Iterationen von 30 fest. Die Ausstiegsbedingung ist eine ODER-Bedingung.
      cornerSubPix (Grau_Bild,Corners,cv::Size (5,5),cv::Size (-1,-1),cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));

      // Mit dieser Funktion werden die gefundenen Ecken aus "Corners" im Graustufenbild eingezeichnet. Ist "Found" true, wurde das Schachbrett und die
      // Ecken erkannt und diese werden markiert und mit Linien verbunden. Ist "Found" false, werden nur die gefundenen Ecken mit einem roten Kreis markiert.
      drawChessboardCorners (Grau_Bild,Board_Sz,Corners,Found);

      // Die gefundenen Ecken-Koordinaten (2D, ohne z-Koordinate) im Vektor "Image-Points" abspeichern.
      Image_Points.push_back (Corners);

      // Alle manuell vorgegebenen Ecken-Koordinaten aus "Obj" in Vektor "Object_Points" ablegen.
      Object_Points.push_back (Obj);

      // Die entsprechende Roboterpose zum aktuellen Bild in einem Vektor abspeichern. Dieser Vektor wird für
      // die Eye-In-Hand-Kalibrierung benötigt.
      cv::Mat Mat_Orientation (cv::Mat_<double> (3,3));
      cv::Mat Mat_Position (cv::Mat_<double> (3,1));

      //// Zuweisung der übermittelten Roboter-TCP-Positionen
      //for (int i = 0; i < 3; i++)
      //  {
      //  Mat_Position.ptr<double>(i)[0] = this->TCP_Poses->at(this->Photo_ID).ptr<double>(i)[3];
      // }
      //// Zuweisung der übermittelten Roboter-TCP-Orientierungen
      //for (int i = 0; i < 3; i++)
      //  {
      //  for (int j = 0; j < 3; j++)
      //    {
      //    Mat_Orientation.ptr<double>(i)[j] = this->TCP_Poses->at(this->Photo_ID).ptr<double>(i)[j];
      //    }
      //  }

      // Ablegen aller Roboter-TCP-Orientierungen und -Positionen in Vektoren
      TCP_Orientation.push_back (Mat_Orientation);
      TCP_Position.push_back (Mat_Position);
      }

    // Grauwertbild mit eingezeichneten Ecken abspeichern.
    imwrite ("../Parameter/Bilder/Camera_Single_Calibration_" + std::to_string (camera_id) + "_Gray_DrawCorners_" + std::to_string (this->Photo_ID) + ".png",Grau_Bild);

    // Photo-ID für nächsten Durchlauf erhöhen.
    this->Photo_ID++;
    }

  std::cout << "Analyzed " << numBoards_imgs - error_count << "good images out of " << numBoards_imgs << endl;

  // Mit den gefundenen Ecken in 2D-Koordinaten und den vorgegebenen 3D-Koordinaten werden die intrinsischen Parameter (Camera-Matrix) und
  // die Koeffizienten der Verzerrung berechnet. Rvecs und Tvecs erhalten dabei die Orientierung und die Position der Transformationsmatrix
  // zwischen Kamerakoordinatensystem und Schachbrettkoordinatensystem.
  //The intrinsic matrix contains 5 intrinsic parameters.These parameters encompass focal length, image format, and principal point.
  //The parameters \alpha_{ x } = f \cdot m_{ x } and \alpha_{ y } = f \cdot m_{ y } represent focal length in terms of pixels, 
  //where m_{ x } and m_{ y } are the scale factors relating pixels to distance and f is the focal length in terms of distance.
  std::cout << endl << "Calculating Intrinsic and DistCoeffs. This may take a while, please wait." << endl;
  cv::calibrateCamera (Object_Points,Image_Points,Originalbild.size(),intrinsic,distCoeffs,Rvecs,Tvecs);

  std::cout << "Calculation finished. Saving data." << endl << endl;

  //Kopieren der berechneten Daten zur dazugehörigen Kamera
  *camera_vector[current_camera_id]->Intrinsic  = intrinsic;
  *camera_vector[current_camera_id]->DistCoeffs = distCoeffs;

  //Speichern der berechenten Daten in CSV Datei
  this->save_camera_calibration (current_camera_id);

  //Reaktivierung der Bildentzerrung
  this->camera_vector[current_camera_id]->init_rectify_map();
  this->camera_vector[current_camera_id]->set_undistord_active (true);
  }
void c_camera_unmanaged::calibrate_stereo_camera (int current_camera_id)
  {
  vector<vector<cv::Point3f>> object_points;
  vector<vector<cv::Point2f>> imagePoints1;
  vector<vector<cv::Point2f>> imagePoints2;
  vector<vector<cv::Point2f>> left_img_points;
  vector<vector<cv::Point2f>> right_img_points;

  vector<cv::Point2f> corners1;
  vector<cv::Point2f> corners2;

  cv::Mat img1;
  cv::Mat img2;
  cv::Mat gray1;
  cv::Mat gray2;

  Photo_ID        = 0;
  int error_count = 0;

  cv::Size board_size = cv::Size (this->numCornersWidth,this->numCornersHeight);
  int      board_n    = this->numCornersWidth * this->numCornersHeight;


  //Iterate over all available photos
  while (this->Photo_ID < this->numBoards_imgs)
    {
    char left_img[100], right_img[100];
    img1 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id) + "_Snapshot_" + std::to_string (this->Photo_ID) + ".png",1);
    img2 = cv::imread ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (current_camera_id + 1) + "_Snapshot_" + std::to_string (this->Photo_ID) + ".png",1);

    cv::cvtColor (img1,gray1,cv::COLOR_BGR2GRAY);
    cv::cvtColor (img2,gray2,cv::COLOR_BGR2GRAY);

    bool found1 = false;
    bool found2 = false;

    found1 = cv::findChessboardCorners (img1,board_size,corners1,
                                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
    found2 = cv::findChessboardCorners (img2,board_size,corners2,
                                        cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);


    if (!found1 || !found2)
      {
      std::cout << "Chessboard find error!" << endl;
      std::cout << "Setnumber: " << Photo_ID << endl;
      Photo_ID++;
      error_count++;
      continue;
      }

    if (found1)
      {
      cv::cornerSubPix (gray1,corners1,cv::Size (5,5),cv::Size (-1,-1),
                        cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));
      cv::drawChessboardCorners (gray1,board_size,corners1,found1);
      }
    if (found2)
      {
      cv::cornerSubPix (gray2,corners2,cv::Size (5,5),cv::Size (-1,-1),
                        cv::TermCriteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER,30,0.1));
      cv::drawChessboardCorners (gray2,board_size,corners2,found2);
      }

    cv::imwrite ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id) + "_Gray_DrawCorners_" + std::to_string (this->Photo_ID) + ".png",gray1);
    cv::imwrite ("../Parameter/Bilder/Camera_Stereo_Calibration_" + std::to_string (camera_id + 1) + "_Gray_DrawCorners_" + std::to_string (this->Photo_ID) + ".png",gray2);

    vector<cv::Point3f> obj;
    for (int i = 0; i < this->numCornersHeight; i++)
      for (int j = 0; j < this->numCornersWidth; j++) obj.emplace_back (static_cast<float> (j) * SquareSize,static_cast<float> (i) * SquareSize,0);

    if (found1 && found2)
      {
      imagePoints1.push_back (corners1);
      imagePoints2.push_back (corners2);
      object_points.push_back (obj);
      }
    Photo_ID++;
    }//  while (this->Photo_ID < this->numBoards_imgs)

  std::cout << endl << "Analyzed " << Photo_ID - error_count << " out of " << Photo_ID << " source immages successfully." << endl;

  for (int i = 0; i < imagePoints1.size(); i++)
    {
    vector<cv::Point2f> v1, v2;
    for (int j = 0; j < imagePoints1[i].size(); j++)
      {
      v1.emplace_back (static_cast<double> (imagePoints1[i][j].x),static_cast<double> (imagePoints1[i][j].y));
      v2.emplace_back (static_cast<double> (imagePoints2[i][j].x),static_cast<double> (imagePoints2[i][j].y));
      }
    left_img_points.push_back (v1);
    right_img_points.push_back (v2);
    }

  std::cout << "Starting Calibration" << endl;
  cv::Mat   K1, K2, R, F, E;
  cv::Vec3d T;
  cv::Mat   D1, D2;
  this->camera_vector[current_camera_id]->Intrinsic->copyTo (K1);
  this->camera_vector[current_camera_id + 1]->Intrinsic->copyTo (K2);
  this->camera_vector[current_camera_id]->DistCoeffs->copyTo (D1);
  this->camera_vector[current_camera_id + 1]->DistCoeffs->copyTo (D2);

  cv::stereoCalibrate (object_points,left_img_points,right_img_points,K1,D1,K2,D2,img1.size(),R,T,E,F,cv::CALIB_FIX_INTRINSIC);

  std::cout << "K1" << endl << K1 << endl << endl;
  std::cout << "K2" << endl << K2 << endl << endl;
  std::cout << "D1" << endl << D1 << endl << endl;
  std::cout << "D2" << endl << D2 << endl << endl;
  std::cout << "R" << endl << R << endl << endl;
  std::cout << "T" << endl << T << endl << endl;
  std::cout << "E" << endl << E << endl << endl;
  std::cout << "F" << endl << F << endl << endl;
  std::cout << "Done Calibration" << endl;


  std::cout << "Starting Rectification" << endl;

  cv::Mat R1, R2, P1, P2, Q;
  stereoRectify (K1,D1,K2,D2,img1.size(),R,T,R1,R2,P1,P2,Q);

  std::cout << "R1" << R1 << endl;
  std::cout << "R2" << R2 << endl;
  std::cout << "P1" << P1 << endl;
  std::cout << "P2" << P2 << endl;
  std::cout << "Q" << Q << endl;

  std::cout << "Done Rectification" << endl;
  }

void c_camera_unmanaged::sm_object_tracking ()
  {
  int statemachine_state                = 0;
  this->tracked_data->positionsvektor.X = 0.0;
  this->tracked_data->positionsvektor.Y = 0.0;
  this->tracked_data->positionsvektor.Z = 0.0;
  int object_found_camID                = 0;

  int stateSize = 6;
  int measSize  = 4;
  int contrSize = 4;

  unsigned int type = CV_32F;

  while (this->tracking_active)
    {
    switch (statemachine_state)
      {
      case 0:
        //Lade alle fest definierten Welt-Kamera Posen und erstelle einen Vektor mit allen Posen. Vektor[0] bezieht sich auf Kamera[0], usw.
        for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
          {
          C_AbsolutePose abs_WorldToCam;
          load_camera_cos (i,abs_WorldToCam);
          vec_WorldToCam_Poses->push_back (abs_WorldToCam);
          }
        statemachine_state = 1;
        break;
      case 1:
        //Überprüfe ob eine Kameras das Objekt gefunden hat. Gehe dazu durch die komplette linke Reihe (+2).
        //Hat eine Kamera (0) das Objekt gesichtet, wird es wahrscheinlich
        //auch von der gegenüberliegenden Kamera (1) auffindbar sein.
        for (int i = 0; i < this->camera_vector.size(); i + 2)
          {
          if (this->camera_vector[i]->is_contour_found())
            {
            object_found_camID = i;
            statemachine_state = 2;
            break;
            }
          }
        break;

      case 2:
        //Hole die 2D-Koordinaten des Objektes aus dem Kamerabild
        this->camera_vector[object_found_camID]->get_objectPosition_2D_Pixel (tracked_data->found_0,tracked_data->Richtungsvektor_0);
        this->camera_vector[object_found_camID + 1]->get_objectPosition_2D_Pixel (tracked_data->found_1,tracked_data->Richtungsvektor_1);

        //Validiere die Bedingung, dass ein Objekt gefunden wurde 
        if (!tracked_data->found_1 && tracked_data->found_0)
          {
          statemachine_state = 1;
          break;
          }
        statemachine_state = 3;
        break;

      case 3:
        this->tracking_thread->Get_Position_ObjectTracking (*tracked_data,*vec_WorldToCam_Poses);

        statemachine_state = 1;
      case 4:
        //cv::KalmanFilter()
        break;
      }
    }
  }
