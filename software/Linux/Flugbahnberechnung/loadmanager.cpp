#include "loadmanager.h"

using namespace LoadManager;

C_LoadManager::C_LoadManager(C_GlobalObjects* GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;
  }
C_LoadManager::~C_LoadManager()
  {
  this->GlobalObjects = nullptr;
  }


void C_LoadManager::loadCameraSettings (Camera::C_Camera2 *Camera)
  {
  int cameraID = Camera->getCameraID();
  string Dateiname      = "../Parameter/Camera_setting" + to_string (cameraID) + ".csv";
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


    Camera->filterValues->setHue_min(hue_min);
    Camera->filterValues->setHue_max(hue_max);
    Camera->filterValues->setSaturation_min(saturation_min);
    Camera->filterValues->setSaturation_max(saturation_max);
    Camera->filterValues->setValue_min(value_min);
    Camera->filterValues->setValue_max(value_max);

    Camera->filterValues->setErosion_iterations(erosion_iterations);
    Camera->filterValues->setDilation_iterations(dilation_iterations);
    Camera->filterValues->setOpening_iterations(opening_iterations);
    Camera->filterValues->setClosing_iterations(closing_iterations);
    Camera->filterValues->setMorph_iterations(morph_iterations);

    Camera->filterValues->setErosion_kernel_size (erosion_kernel_size);
    Camera->filterValues->setDilation_kernel_size (dilation_kernel_size);
    Camera->filterValues->setOpening_kernel_size (opening_kernel_size);
    Camera->filterValues->setClosing_kernel_size(closing_kernel_size);
    Camera->filterValues->setMorph_kernel_size(morph_kernel_size);
    Camera->filterValues->setGaussian_kernel_size(gaussian_kernel_size);
    Camera->filterValues->setBilateral_kernel_size(bilateral_kernel_size);

    Camera->filterValues->setGaussian_sigma(gaussian_sigma);

    Camera->filterValues->setBilateral_sigma_color(bilateral_sigma_color);
    Camera->filterValues->setBilateral_sigma_spatial(bilateral_sigma_spatial);

    Camera->filterValues->setObject_Size_min(object_size_min);
    Camera->filterValues->setObject_Size_max(object_size_max);
    }
  else
    {
    printf("Filterwerte für Kamera %i wurden nicht geladen", cameraID);
    }

  std::cout << "Loaded Settings for Camera " << cameraID << "." << endl;
  }

void C_LoadManager::loadCameraCalibration (Camera::C_Camera2* Camera)
  {
  int cameraID      = Camera->getCameraID();
  string Dateiname  = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (cameraID) + ".csv";
  string Dateityp   = "Intrinisic and distortion parameters of camera-single-calibration";
  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  int    real_size_width = 800;
  int    real_size_height = 600;

  this->GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);

  if (this->GlobalObjects->csv_parameter_datei->IsOpen())
    {
    this->GlobalObjects->csv_parameter_datei->Lesen (Dateityp);
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

  Camera->setCalibrationParameter(DistCoeffs,Intrinsic);
  std::cout << "Loaded Calibration for Camera " << cameraID << "." << endl;
  }

std::vector<int> C_LoadManager::loadCameraPositioning ()
  {
  string                                                  Dateiname = "../Parameter/Camera_Positioning.csv";
  string                                                  Dateityp;
  std::vector<int>                                        vecCameraPosition;
  int                                                     id;
  int                                                     Camera_count;

  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Lesen (Dateityp);
    GlobalObjects->csv_parameter_datei->Lesen (Camera_count);
    if (GlobalObjects->absCameras == Camera_count)
      {
      for (int i = 0; i < Camera_count; i++)
        {
        GlobalObjects->csv_parameter_datei->Lesen (id);
        vecCameraPosition.push_back(id);
        }
      }
    else
      {
      for (int i = 0; i < GlobalObjects->absCameras; i++)
        {
        vecCameraPosition.push_back(i);
        }
      printf("Standardreihung geladen");
      }
    }
  GlobalObjects->csv_parameter_datei->Schliessen();
  return vecCameraPosition;
  }

void C_LoadManager::loadCameraCos (Camera::C_Camera2* Camera)
  {
  int camerID = Camera->getCameraID();
  string Dateiname = "../Parameter/Pose_world_to_camera" + to_string (camerID) + ".csv";
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

    Camera->getCameraPose()->nx(nx);
    Camera->getCameraPose()->ny (ny);
    Camera->getCameraPose()->nz (nz);
    Camera->getCameraPose()->ox (ox);
    Camera->getCameraPose()->oy (oy);
    Camera->getCameraPose()->oz (oz);
    Camera->getCameraPose()->ax (ax);
    Camera->getCameraPose()->ay (ay);
    Camera->getCameraPose()->az (az);
    Camera->getCameraPose()->px (px);
    Camera->getCameraPose()->py (py);
    Camera->getCameraPose()->pz (pz);
    }
  else
    {
    printf("Kameraposition für Kamera %i wurde nicht geladen", camerID);
    }
  GlobalObjects->csv_parameter_datei->Schliessen();
  }



