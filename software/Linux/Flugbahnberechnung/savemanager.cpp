#include "savemanager.h"

using namespace Savemanager;

c_SaveManager::c_SaveManager(C_GlobalObjects* GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;
  }
c_SaveManager::~c_SaveManager()
  {
  this->GlobalObjects = nullptr;
  }

void c_SaveManager::saveCameraCos         (Camera::C_Camera2 &Camera)
  {
  string Dateiname = "../Parameter/Pose_world_to_camera" + to_string (Camera.getCameraID()) + ".csv";
  string Dateityp;
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

  nx = Camera.getCameraPose()->nx();
  ny = Camera.getCameraPose()->ny();
  nz = Camera.getCameraPose()->nz();

  ox = Camera.getCameraPose()->ox();
  oy = Camera.getCameraPose()->oy();
  oz = Camera.getCameraPose()->oz();

  ax = Camera.getCameraPose()->ax();
  ay = Camera.getCameraPose()->ay();
  az = Camera.getCameraPose()->az();

  px = Camera.getCameraPose()->px();
  py = Camera.getCameraPose()->py();
  pz = Camera.getCameraPose()->pz();

  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("nx",nx,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("ny",ny,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("nz",nz,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("ox",ox,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("oy",oy,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("oz",oz,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("ax",ax,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("ay",ay,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("az",az,"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("px",px,"[mm]");
    GlobalObjects->csv_parameter_datei->Schreiben ("py",py,"[mm]");
    GlobalObjects->csv_parameter_datei->Schreiben ("pz",pz,"[mm]");
    }
  GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_SaveManager::saveCameraPositioning (std::vector<int> camera_list) const
  {
  string Dateiname = "../Parameter/Camera_Positioning.csv";
  string Dateityp  = "Correct Camera position in vector corresponding to their ID";

  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);

  GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
  GlobalObjects->csv_parameter_datei->Schreiben ("Anzahl Kameras",to_string (GlobalObjects->absCameras),"[1]");


  for (int i = 0; i < GlobalObjects->absCameras; i++)
    {
    GlobalObjects->csv_parameter_datei->Schreiben ("Cameravector[" + to_string (i) + "]",to_string (camera_list[i]),"[1]");
    std::cout << "Saving Camera " << i << " to position " << camera_list[i];
    }


  GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_SaveManager::saveCameraCalibration (Camera::C_Camera2 &Camera)
  {
  int    cameraID = Camera.getCameraID();
  string Dateiname = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (cameraID) + ".csv";
  string Dateityp  = "Intrinisic and distortion parameters of camera-single-calibration";

  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  Camera.getCalibrationParameter(DistCoeffs,Intrinsic);

  this->GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);

  this->GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
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

  this->GlobalObjects->csv_parameter_datei->Schliessen();
  }
void c_SaveManager::saveCameraSettings    (Camera::C_Camera2 &Camera)
  {
  string Dateiname = "../Parameter/Camera_setting" + to_string (Camera.getCameraID()) + ".csv";
  string Dateityp  = "Value of the individual setting";


  GlobalObjects->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);


  if (GlobalObjects->csv_parameter_datei->IsOpen())
    {
    GlobalObjects->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");


    GlobalObjects->csv_parameter_datei->Schreiben ("hue_min",to_string (Camera.filterValues->getHue_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("hue_max",to_string (Camera.filterValues->getHue_max()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("saturation_min",to_string (Camera.filterValues->getSaturation_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("saturation_max",to_string (Camera.filterValues->getSaturation_max()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("value_min",to_string (Camera.filterValues->getValue_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("value_max",to_string (Camera.filterValues->getValue_max()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("erosion_iterations",to_string (Camera.filterValues->getErodeIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("dilation_iterations",to_string (Camera.filterValues->getDilateIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("opening_iteration",to_string (Camera.filterValues->getOpenIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("closing_iteration",to_string (Camera.filterValues->getCloseIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("morph_iteration",to_string (Camera.filterValues->getMorphIterations()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("erosion_kernel_size",to_string (Camera.filterValues->getErodeKernelSize()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("dilation_kernel_size",to_string (Camera.filterValues->getDilateKernelSize()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("opening_kernel_size",to_string (Camera.filterValues->getOpenIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("closing_kernel_size",to_string (Camera.filterValues->getCloseIterations()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("morph_kernel_size",to_string (Camera.filterValues->getMorphKernelSize()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("gaussian_kernel_size",to_string (Camera.filterValues->getGaussianKernelSize()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_kernel_size",to_string (Camera.filterValues->getBilateralKernelSize()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("gaussian_sigma",to_string (Camera.filterValues->getGaussianSigma()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_sigma_color",to_string (Camera.filterValues->getBilateralSigmaColor()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("bilateral_sigma_spatial",to_string (Camera.filterValues->getBilateralSigmaSpatial()),"[1]");

    GlobalObjects->csv_parameter_datei->Schreiben ("Object_size_min",to_string (Camera.filterValues->getObject_Size_min()),"[1]");
    GlobalObjects->csv_parameter_datei->Schreiben ("Object_size_max",to_string (Camera.filterValues->getObject_Size_max()),"[1]");
    }
  this->GlobalObjects->csv_parameter_datei->Schliessen();
  }
