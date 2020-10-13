#include "headers/CSV_Manager/savemanager.h"

using namespace Savemanager;
using namespace UM_CSV_Datei;

c_SaveManager::c_SaveManager()
  {
  }
c_SaveManager::~c_SaveManager()
  {
  }

void c_SaveManager::saveCameraCos         (Camera::C_Camera2 &Camera)
  {
  string Dateiname = "../Parameter/Pose_camera_to_world" + to_string (Camera.getCameraID()) + ".csv";
  string Dateityp = "Value of the individual setting";;
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

  nx = Camera.CameraToWorld->nx();
  ny = Camera.CameraToWorld->ny();
  nz = Camera.CameraToWorld->nz();

  ox = Camera.CameraToWorld->ox();
  oy = Camera.CameraToWorld->oy();
  oz = Camera.CameraToWorld->oz();

  ax = Camera.CameraToWorld->ax();
  ay = Camera.CameraToWorld->ay();
  az = Camera.CameraToWorld->az();

  px = Camera.CameraToWorld->px();
  py = Camera.CameraToWorld->py();
  pz = Camera.CameraToWorld->pz();
 this->csv_parameter_datei->Oeffnen (Dateiname, Enum_CSV_Access::Write);
 if(this->csv_parameter_datei->IsOpen())
 {
    this->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    this->csv_parameter_datei->Schreiben ("nx",nx,"[1]");
    this->csv_parameter_datei->Schreiben ("ny",ny,"[1]");
    this->csv_parameter_datei->Schreiben ("nz",nz,"[1]");
    this->csv_parameter_datei->Schreiben ("ox",ox,"[1]");
    this->csv_parameter_datei->Schreiben ("oy",oy,"[1]");
    this->csv_parameter_datei->Schreiben ("oz",oz,"[1]");
    this->csv_parameter_datei->Schreiben ("ax",ax,"[1]");
    this->csv_parameter_datei->Schreiben ("ay",ay,"[1]");
    this->csv_parameter_datei->Schreiben ("az",az,"[1]");
    this->csv_parameter_datei->Schreiben ("px",px,"[m]");
    this->csv_parameter_datei->Schreiben ("py",py,"[m]");
    this->csv_parameter_datei->Schreiben ("pz",pz,"[m]");
    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Pose fuer Kamera " << std::to_string(Camera.getCameraID()) << " wurde gespeichert" << std::endl;
 }
 else
 {}
  }
void c_SaveManager::saveCameraPositioning (std::vector<Camera::C_Camera2*>& vecCameras, int absCameras) const
  {
  string Dateiname = "../Parameter/Camera_Positioning.csv";
  string Dateityp  = "Correct Camera position in vector corresponding to their ID";

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);
  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    this->csv_parameter_datei->Schreiben ("Anzahl Kameras",to_string (absCameras),"[1]");
    for (int i = 0; i < absCameras; i++)
      {
      this->csv_parameter_datei->Schreiben ("Cameravector[" + to_string (i) + "]",to_string (vecCameras[i]->getCameraID()),"[1]");
      std::cout << "Saving Camera " << to_string (vecCameras[i]->getCameraID()) << " to position " << i;
      }
    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Reihung wurde gespeichert" << std::endl;
    }
  else
    {
    std::cout << "**ERROR** Reihung wurde nicht gespeichert" << std::endl;
    }


  }
void c_SaveManager::saveCameraCalibration (Camera::C_Camera2 &Camera)
  {
  int    cameraID = Camera.getCameraID();
  string Dateiname = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (cameraID) + ".csv";
  string Dateityp  = "Intrinisic and distortion parameters of camera-single-calibration";

  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  Camera.getCalibrationParameter(DistCoeffs,Intrinsic);

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);
  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    this->csv_parameter_datei->Schreiben ("Distortion k1",DistCoeffs[0][0],"[1]");
    this->csv_parameter_datei->Schreiben ("Distortion k2",DistCoeffs[0][1],"[1]");
    this->csv_parameter_datei->Schreiben ("Distortion p1",DistCoeffs[0][2],"[1]");
    this->csv_parameter_datei->Schreiben ("Distortion p2",DistCoeffs[0][3],"[1]");
    this->csv_parameter_datei->Schreiben ("Distortion k3",DistCoeffs[0][4],"[1]");
    this->csv_parameter_datei->Schreiben ("Intrinsic fx",Intrinsic[0][0],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic 01",Intrinsic[0][1],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic cx",Intrinsic[0][2],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic 10",Intrinsic[1][0],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic fy",Intrinsic[1][1],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic cy",Intrinsic[1][2],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic 20",Intrinsic[2][0],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic 21",Intrinsic[2][1],"[Px]");
    this->csv_parameter_datei->Schreiben ("Intrinsic 22",Intrinsic[2][2],"[Px]");

    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Kalibrierung fuer Kamera " << std::to_string(Camera.getCameraID()) << " wurde gespeichert" << std::endl;
    }
  else
    {
    std::cout << "**ERROR** Kalibrierung fuer Kamera " << std::to_string(Camera.getCameraID()) << " wurde nicht gespeichert" << std::endl;
    }
  }
void c_SaveManager::saveCameraSettings    (Camera::C_Camera2 &Camera)
  {
  string Dateiname = "../Parameter/Camera_setting" + to_string (Camera.getCameraID()) + ".csv";
  string Dateityp  = "Value of the individual setting";


  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Write);


  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    this->csv_parameter_datei->Schreiben ("hue_min",to_string (Camera.getFilterproperties()->getHue_min()),"[1]");
    this->csv_parameter_datei->Schreiben ("hue_max",to_string (Camera.getFilterproperties()->getHue_max()),"[1]");
    this->csv_parameter_datei->Schreiben ("saturation_min",to_string (Camera.getFilterproperties()->getSaturation_min()),"[1]");
    this->csv_parameter_datei->Schreiben ("saturation_max",to_string (Camera.getFilterproperties()->getSaturation_max()),"[1]");
    this->csv_parameter_datei->Schreiben ("value_min",to_string (Camera.getFilterproperties()->getValue_min()),"[1]");
    this->csv_parameter_datei->Schreiben ("value_max",to_string (Camera.getFilterproperties()->getValue_max()),"[1]");

    this->csv_parameter_datei->Schreiben ("erosion_iterations",to_string (Camera.getFilterproperties()->getErodeIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("dilation_iterations",to_string (Camera.getFilterproperties()->getDilateIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("opening_iteration",to_string (Camera.getFilterproperties()->getOpenIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("closing_iteration",to_string (Camera.getFilterproperties()->getCloseIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("morph_iteration",to_string (Camera.getFilterproperties()->getMorphIterations()),"[1]");

    this->csv_parameter_datei->Schreiben ("erosion_kernel_size",to_string (Camera.getFilterproperties()->getErodeKernelSize()),"[1]");
    this->csv_parameter_datei->Schreiben ("dilation_kernel_size",to_string (Camera.getFilterproperties()->getDilateKernelSize()),"[1]");
    this->csv_parameter_datei->Schreiben ("opening_kernel_size",to_string (Camera.getFilterproperties()->getOpenIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("closing_kernel_size",to_string (Camera.getFilterproperties()->getCloseIterations()),"[1]");
    this->csv_parameter_datei->Schreiben ("morph_kernel_size",to_string (Camera.getFilterproperties()->getMorphKernelSize()),"[1]");
    this->csv_parameter_datei->Schreiben ("gaussian_kernel_size",to_string (Camera.getFilterproperties()->getGaussianKernelSize()),"[1]");
    this->csv_parameter_datei->Schreiben ("bilateral_kernel_size",to_string (Camera.getFilterproperties()->getBilateralKernelSize()),"[1]");

    this->csv_parameter_datei->Schreiben ("gaussian_sigma",to_string (Camera.getFilterproperties()->getGaussianSigma()),"[1]");

    this->csv_parameter_datei->Schreiben ("bilateral_sigma_color",to_string (Camera.getFilterproperties()->getBilateralSigmaColor()),"[1]");
    this->csv_parameter_datei->Schreiben ("bilateral_sigma_spatial",to_string (Camera.getFilterproperties()->getBilateralSigmaSpatial()),"[1]");

    this->csv_parameter_datei->Schreiben ("Object_size_min",to_string (Camera.getFilterproperties()->getObject_Size_min()),"[1]");
    this->csv_parameter_datei->Schreiben ("Object_size_max",to_string (Camera.getFilterproperties()->getObject_Size_max()),"[1]");
    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Filtereinstellungen fuer Kamera " << std::to_string(Camera.getCameraID()) << " wurden gespeichert" << std::endl;
    }
  else
    {
    std::cout << "**ERROR** Filtereinstellungen fuer Kamera " << std::to_string(Camera.getCameraID()) << " wurden nicht gespeichert" << std::endl;
    }
  }


void c_SaveManager::saveRobotCos           (robot::C_robot& robot)
  {
  string Dateiname = "../Parameter/RobotToWorld_Pose.csv";
  string Dateityp = "Pose Robot to World";;
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

  nx = robot.RobotToWorld->nx();
  ny = robot.RobotToWorld->ny();
  nz = robot.RobotToWorld->nz();

  ox = robot.RobotToWorld->ox();
  oy = robot.RobotToWorld->oy();
  oz = robot.RobotToWorld->oz();

  ax = robot.RobotToWorld->ax();
  ay = robot.RobotToWorld->ay();
  az = robot.RobotToWorld->az();

  px = robot.RobotToWorld->px();
  py = robot.RobotToWorld->py();
  pz = robot.RobotToWorld->pz();
 this->csv_parameter_datei->Oeffnen (Dateiname, Enum_CSV_Access::Write);
 if(this->csv_parameter_datei->IsOpen())
 {
    this->csv_parameter_datei->Schreiben ("Dateityp",Dateityp,"[1]");
    this->csv_parameter_datei->Schreiben ("nx",nx,"[1]");
    this->csv_parameter_datei->Schreiben ("ny",ny,"[1]");
    this->csv_parameter_datei->Schreiben ("nz",nz,"[1]");
    this->csv_parameter_datei->Schreiben ("ox",ox,"[1]");
    this->csv_parameter_datei->Schreiben ("oy",oy,"[1]");
    this->csv_parameter_datei->Schreiben ("oz",oz,"[1]");
    this->csv_parameter_datei->Schreiben ("ax",ax,"[1]");
    this->csv_parameter_datei->Schreiben ("ay",ay,"[1]");
    this->csv_parameter_datei->Schreiben ("az",az,"[1]");
    this->csv_parameter_datei->Schreiben ("px",px,"[m]");
    this->csv_parameter_datei->Schreiben ("py",py,"[m]");
    this->csv_parameter_datei->Schreiben ("pz",pz,"[m]");
    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Pose fuer Roboter wurde gespeichert" << std::endl;
 }
 else
 {}
  }
