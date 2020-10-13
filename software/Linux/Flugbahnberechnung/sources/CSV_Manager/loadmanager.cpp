#include "headers/CSV_Manager/loadmanager.h"

using namespace LoadManager;
using namespace UM_CSV_Datei;


C_LoadManager::C_LoadManager()
  {
  }
C_LoadManager::~C_LoadManager()
  {
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

  int object_size_min = 0;
  int object_size_max = 0;

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);

  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen (Dateityp);
    this->csv_parameter_datei->Lesen (hue_min);
    this->csv_parameter_datei->Lesen (hue_max);
    this->csv_parameter_datei->Lesen (saturation_min);
    this->csv_parameter_datei->Lesen (saturation_max);
    this->csv_parameter_datei->Lesen (value_min);
    this->csv_parameter_datei->Lesen (value_max);

    this->csv_parameter_datei->Lesen (erosion_iterations);
    this->csv_parameter_datei->Lesen (dilation_iterations);
    this->csv_parameter_datei->Lesen (opening_iterations);
    this->csv_parameter_datei->Lesen (closing_iterations);
    this->csv_parameter_datei->Lesen (morph_iterations);

    this->csv_parameter_datei->Lesen (erosion_kernel_size);
    this->csv_parameter_datei->Lesen (dilation_kernel_size);
    this->csv_parameter_datei->Lesen (opening_kernel_size);
    this->csv_parameter_datei->Lesen (closing_kernel_size);
    this->csv_parameter_datei->Lesen (morph_kernel_size);
    this->csv_parameter_datei->Lesen (gaussian_kernel_size);
    this->csv_parameter_datei->Lesen (bilateral_kernel_size);

    this->csv_parameter_datei->Lesen (gaussian_sigma);

    this->csv_parameter_datei->Lesen (bilateral_sigma_color);
    this->csv_parameter_datei->Lesen (bilateral_sigma_spatial);

    this->csv_parameter_datei->Lesen (object_size_min);
    this->csv_parameter_datei->Lesen (object_size_max);
    this->csv_parameter_datei->Schliessen();

    Camera->filterValues->setHue_min                (hue_min);
    Camera->filterValues->setHue_max                (hue_max);
    Camera->filterValues->setSaturation_min         (saturation_min);
    Camera->filterValues->setSaturation_max         (saturation_max);
    Camera->filterValues->setValue_min              (value_min);
    Camera->filterValues->setValue_max              (value_max);

    Camera->filterValues->setErosion_iterations     (erosion_iterations);
    Camera->filterValues->setDilation_iterations    (dilation_iterations);
    Camera->filterValues->setOpening_iterations     (opening_iterations);
    Camera->filterValues->setClosing_iterations     (closing_iterations);
    Camera->filterValues->setMorph_iterations       (morph_iterations);

    Camera->filterValues->setErosion_kernel_size    (erosion_kernel_size);
    Camera->filterValues->setDilation_kernel_size   (dilation_kernel_size);
    Camera->filterValues->setOpening_kernel_size    (opening_kernel_size);
    Camera->filterValues->setClosing_kernel_size    (closing_kernel_size);
    Camera->filterValues->setMorph_kernel_size      (morph_kernel_size);
    Camera->filterValues->setGaussian_kernel_size   (gaussian_kernel_size);
    Camera->filterValues->setBilateral_kernel_size  (bilateral_kernel_size);

    Camera->filterValues->setGaussian_sigma         (gaussian_sigma);

    Camera->filterValues->setBilateral_sigma_color  (bilateral_sigma_color);
    Camera->filterValues->setBilateral_sigma_spatial(bilateral_sigma_spatial);

    Camera->filterValues->setObject_Size_min        (object_size_min);
    Camera->filterValues->setObject_Size_max        (object_size_max);
    std::cout << "**INFO** Filterwerte fuer Kamera " << std::to_string(cameraID) << " wurde geladen" << std::endl;

    }
  else
    {
      std::cout << "**ERROR** Filterwerte fuer Kamera " << std::to_string(cameraID) << " wurde nicht geladen" << std::endl;
    }

  }

void C_LoadManager::loadCameraCalibration (Camera::C_Camera2* Camera)
  {
  int cameraID      = Camera->getCameraID();
  string Dateiname  = "../Parameter/Camera_Calibration_Parameter_CameraID_" + to_string (cameraID) + ".csv";
  string Dateityp   = "Intrinisic and distortion parameters of camera-single-calibration";
  double DistCoeffs[1][5];
  double Intrinsic[3][3];
  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);

  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen (Dateityp);
    this->csv_parameter_datei->Lesen (DistCoeffs[0][0]);
    this->csv_parameter_datei->Lesen (DistCoeffs[0][1]);
    this->csv_parameter_datei->Lesen (DistCoeffs[0][2]);
    this->csv_parameter_datei->Lesen (DistCoeffs[0][3]);
    this->csv_parameter_datei->Lesen (DistCoeffs[0][4]);
    this->csv_parameter_datei->Lesen (Intrinsic[0][0]);
    this->csv_parameter_datei->Lesen (Intrinsic[0][1]);
    this->csv_parameter_datei->Lesen (Intrinsic[0][2]);
    this->csv_parameter_datei->Lesen (Intrinsic[1][0]);
    this->csv_parameter_datei->Lesen (Intrinsic[1][1]);
    this->csv_parameter_datei->Lesen (Intrinsic[1][2]);
    this->csv_parameter_datei->Lesen (Intrinsic[2][0]);
    this->csv_parameter_datei->Lesen (Intrinsic[2][1]);
    this->csv_parameter_datei->Lesen (Intrinsic[2][2]);
    this->csv_parameter_datei->Schliessen();
    std::cout << "**INFO** Gespeicherte Kalibrierung fuer Kamera " << std::to_string(cameraID) << " wurde geladen" << std::endl;
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
    std::cout << "**INFO** Standardkalibrierung fuer Kamera " << std::to_string(cameraID) << " wurde geladen" << std::endl;

    }

  Camera->setCalibrationParameter(DistCoeffs,Intrinsic);
  }

bool C_LoadManager::loadCameraPositioning   (std::vector<Camera::C_Camera2*> &vecCameras, int absCameras)
  {
  string                                                  Dateiname = "../Parameter/Camera_Positioning.csv";
  string                                                  Dateityp;
  int                                                     id;
  int                                                     Camera_count;

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen (Dateityp);
    this->csv_parameter_datei->Lesen (Camera_count);
    if (absCameras == Camera_count)
      {
        std::vector<Camera::C_Camera2*>                         vecTempCameras;
        //std::vector<int>                                        istCamIDs;
        std::vector<int>                                        sollCamIDs;
        vecTempCameras.resize(vecCameras.size());

      //Hole IST Reihenfolge der derzeitigen Kameras
//      for (int i = 0; i < Camera_count; i++)
//        {
//        istCamIDs.push_back(vecCameras[i]->getCameraID());
//        }
      //Hole SOLL Reihenfolge der derzeitigen Kameras
      for (int i = 0; i < Camera_count; i++)
        {
        this->csv_parameter_datei->Lesen (id);
        sollCamIDs.push_back(id);
        }
      for(int i = 0; i < Camera_count; i++)
        {
        Camera::C_Camera2 *ptrAdress = nullptr;
        ptrAdress = vecCameras[sollCamIDs[i]];
        vecTempCameras[i] = ptrAdress;
        }
      vecCameras.clear();
      vecCameras.resize(vecTempCameras.size());
      for(int i = 0; i < Camera_count; i++)
        {
        vecCameras[i] = vecTempCameras[i];
        vecCameras[i]->setCameraID(i);
        }
      int i = 0;
      for(auto it = std::begin(vecCameras); it < std::end(vecCameras); it++)
        {
        (*it)->setCameraID(i);
        i++;
        }

      std::cout << "**INFO** Positionierung wurde geladen" << std::endl;
      }
    else
      {
      std::cout << "**ERROR** Standardpositionierung wurde geladen" << std::endl;
      }
    this->csv_parameter_datei->Schliessen();
    return  true;
    }
  std::cout << "**ERROR** Standardpositionierung wurde geladen" << std::endl;
  return false;
  }

void C_LoadManager::loadCameraCos (Camera::C_Camera2* Camera)
  {
  int camerID = Camera->getCameraID();
  C_AbsolutePose CameraToWorld;
  C_AbsolutePose WorldToCamera;

  string Dateiname = "../Parameter/Pose_world_to_camera" + to_string (camerID) + ".csv";
  string Dateityp;

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen (Dateityp);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[0][0]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[1][0]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[2][0]);

    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[0][1]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[1][1]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[2][1]);

    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[0][2]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[1][2]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[2][2]);

    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[0][3]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[1][3]);
    this->csv_parameter_datei->Lesen (CameraToWorld.HomogenePosenMatrix[2][3]);


    CameraToWorld.InversHomogenousPose(CameraToWorld.HomogenePosenMatrix, WorldToCamera.HomogenePosenMatrix);

    *Camera->WorldToCamera = WorldToCamera;

    std::cout << "**INFO** Kameraposition fuer Kamera " << std::to_string(camerID) << " wurde geladen" << std::endl;

    }
  else
    {
    std::cout << "**ERROR** Kameraposition fuer Kamera " << std::to_string(camerID) << " wurde nicht geladen" << std::endl;
    }
  this->csv_parameter_datei->Schliessen();
  }

double* C_LoadManager::loadRobotTCP(double (&tcp)[4][4])
  {
  string  Dateiname;
  string  Dateityp;

    Dateiname   = "../Parameter/Flange_To_EndEffector_Pose.csv";
    Dateityp    = "";

    this->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

    if (this->csv_parameter_datei->IsOpen())
      {
      this->csv_parameter_datei->Lesen(Dateityp);
        this->csv_parameter_datei->Lesen(tcp[0][0]);
        this->csv_parameter_datei->Lesen(tcp[1][0]);
        this->csv_parameter_datei->Lesen(tcp[2][0]);
        this->csv_parameter_datei->Lesen(tcp[3][0]);
        this->csv_parameter_datei->Lesen(tcp[0][1]);
        this->csv_parameter_datei->Lesen(tcp[1][1]);
        this->csv_parameter_datei->Lesen(tcp[2][1]);
        this->csv_parameter_datei->Lesen(tcp[3][1]);
        this->csv_parameter_datei->Lesen(tcp[0][2]);
        this->csv_parameter_datei->Lesen(tcp[1][2]);
        this->csv_parameter_datei->Lesen(tcp[2][2]);
        this->csv_parameter_datei->Lesen(tcp[3][2]);
        this->csv_parameter_datei->Lesen(tcp[0][3],      1000.0);
        this->csv_parameter_datei->Lesen(tcp[1][3],      1000.0);
        this->csv_parameter_datei->Lesen(tcp[2][3],      1000.0);
        this->csv_parameter_datei->Lesen(tcp[3][3]);

        this->csv_parameter_datei->Schliessen();
        }
      else
        {
        // Standartwerte
        tcp[0][0]      =  1.0000;
        tcp[1][0]      =  0.0000;
        tcp[2][0]      =  0.0000;
        tcp[3][0]      =  0.0000;
        tcp[0][1]      =  0.0000;
        tcp[1][1]      =  1.0000;
        tcp[2][1]      =  0.0000;
        tcp[3][1]      =  0.0000;
        tcp[0][2]      =  0.0000;
        tcp[1][2]      =  0.0000;
        tcp[2][2]      =  1.0000;
        tcp[3][2]      =  0.0000;
        tcp[0][3]      =  0.0000;
        tcp[1][3]      =  0.0000;
        tcp[2][3]      =  0.0000;
        tcp[3][3]      =  1.0000;
        }
    }

void C_LoadManager::loadRobotCos    (robot::C_robot& robot)
  {
  double         Abs_Pose[4][4];
  C_AbsolutePose WorldToRobot;
  C_AbsolutePose RobotToWorld;
  string         Dateiname;
  string         Dateityp;
  Dateiname   = "../Parameter/RobotToWorld_Pose.csv";
  Dateityp    = "";

  this->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen(Dateityp);

    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[0][0]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[1][0]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[2][0]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[0][1]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[1][1]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[2][1]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[0][2]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[1][2]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[2][2]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[0][3]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[1][3]);
    this->csv_parameter_datei->Lesen(RobotToWorld.HomogenePosenMatrix[2][3]);

    RobotToWorld.InversHomogenousPose(RobotToWorld.HomogenePosenMatrix, WorldToRobot.HomogenePosenMatrix);
    *robot.RobotToWorld = RobotToWorld;
    *robot.WorldToRobot = WorldToRobot;
    this->csv_parameter_datei->Schliessen();


    }
  }



