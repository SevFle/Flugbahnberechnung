#include "loadmanager.h"

using namespace LoadManager;

C_LoadManager::C_LoadManager()
  {

  }

void C_LoadManager::loadCameraSettings (int camera_id)
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

  int object_size_min = 0;
  int object_size_max = 0;

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

    GlobalObjects->csv_parameter_datei->Lesen (object_size_min);
    GlobalObjects->csv_parameter_datei->Lesen (object_size_max);


    camera_vector[camera_id]->set_hue_min (hue_min);
    camera_vector[camera_id]->set_hue_max (hue_max);
    camera_vector[camera_id]->set_saturation_min (saturation_min);
    camera_vector[camera_id]->set_saturation_max (saturation_max);
    camera_vector[camera_id]->set_value_min (value_min);
    camera_vector[camera_id]->set_value_max (value_max);

    camera_vector[camera_id]->set_erosion_iterations (erosion_iterations);
    camera_vector[camera_id]->set_dilation_iterations (dilation_iterations);
    camera_vector[camera_id]->set_opening_iterations (opening_iterations);
    camera_vector[camera_id]->set_closing_iterations (closing_iterations);
    camera_vector[camera_id]->set_morph_iterations (morph_iterations);

    camera_vector[camera_id]->set_erosion_kernel_size (erosion_kernel_size);
    camera_vector[camera_id]->set_dilation_kernel_size (dilation_kernel_size);
    camera_vector[camera_id]->set_opening_kernel_size (opening_kernel_size);
    camera_vector[camera_id]->set_closing_kernel_size (closing_kernel_size);
    camera_vector[camera_id]->set_morph_kernel_size (morph_kernel_size);
    camera_vector[camera_id]->set_gaussian_kernel_size (gaussian_kernel_size);
    camera_vector[camera_id]->set_bilateral_kernel_size (bilateral_kernel_size);

    camera_vector[camera_id]->set_gaussian_sigma (gaussian_sigma);

    camera_vector[camera_id]->set_bilateral_sigma_color (bilateral_sigma_color);
    camera_vector[camera_id]->set_bilateral_sigma_spatial (bilateral_sigma_spatial);

    camera_vector[camera_id]->set_dilate_active (dilation_active);
    camera_vector[camera_id]->set_erode_active (erode_active);
    camera_vector[camera_id]->set_morph_active (morph_active);
    camera_vector[camera_id]->set_bilateral_active (bilateral_active);

    camera_vector[camera_id]->set_object_size_min (object_size_min);
    camera_vector[camera_id]->set_object_size_max (object_size_max);
    }
  std::cout << "Loaded Settings for Camera " << camera_id << "." << endl;
  }

void C_LoadManager::loadCameraCalibration (int camera_id)
  {
  string Dateiname = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (camera_id) + ".csv";
  string Dateityp  = "Intrinisic and distortion parameters of camera-single-calibration";
  int    numBoards;
  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  int    real_size_width = 800;
  int    real_size_height = 600;

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
  this->camera_vector[camera_id]->set_resize_width (real_size_width);

  std::cout << "Loaded Calibration for Camera " << camera_id << "." << endl;
  }

void C_LoadManager::loadCameraPositioning ()
  {
  string                                                  Dateiname = "../Parameter/Camera_Positioning.csv";
  string                                                  Dateityp;
  std::vector<camera::c_camera*> camera_vector_temp;
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

void C_LoadManager::loadCameraCos (int camera_id, C_AbsolutePose& WorldToCam_Param)
  {
  string Dateiname = "../Parameter/Pose_world_to_camera" + to_string (camera_id) + ".csv";
  string Dateityp;
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

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
  GlobalObjects->csv_parameter_datei->Schliessen();
  }

void C_LoadManager::load_camera_pipelines(std::vector<std::string> &vec_pipeline)
{
    int deviceNo = 0;
for(auto i= 1; i <= this->GlobalObjects->cameras_in_use; i++)
    {
    if(i < 7)
    {
        vec_pipeline.push_back("v4l2src device=/dev/video" + to_string(deviceNo) +" ! image/jpeg, format=BGR, framerate=60/1, width=1280,height=720 ! jpegdec ! videoconvert ! appsink");
        deviceNo += 2;
    }
    else
    {
        vec_pipeline.push_back("v4l2src device=/dev/video" + to_string(deviceNo) +" ! image/jpeg, format=BGR, framerate=30/1, width=1280,height=720 ! jpegdec ! videoconvert ! appsink");
        deviceNo += 2;
    }
    }

}


