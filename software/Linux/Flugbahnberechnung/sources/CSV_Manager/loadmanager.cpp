#include "headers/CSV_Manager/loadmanager.h"

using namespace LoadManager;
using namespace UM_CSV_Datei;


C_LoadManager::C_LoadManager()
  {
  this->csv_parameter_datei = new UM_CSV_Datei::C_CSV_Parameter_Datei;
  }
C_LoadManager::~C_LoadManager()
  {
  delete (csv_parameter_datei);
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

  this->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);
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
  C_AbsolutePose CameraToWorld;
  C_AbsolutePose WorldToCamera;

  string Dateiname = "../Parameter/Pose_camera_to_world" + to_string (Camera->getCameraID()) + ".csv";

  string Dateityp = "";
  double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;

  this->csv_parameter_datei->Oeffnen (Dateiname,Enum_CSV_Access::Read);
  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen (Dateityp);
    this->csv_parameter_datei->Lesen (nx);
    this->csv_parameter_datei->Lesen (ny);
    this->csv_parameter_datei->Lesen (nz);

    this->csv_parameter_datei->Lesen (ox);
    this->csv_parameter_datei->Lesen (oy);
    this->csv_parameter_datei->Lesen (oz);

    this->csv_parameter_datei->Lesen (ax);
    this->csv_parameter_datei->Lesen (ay);
    this->csv_parameter_datei->Lesen (az);

    this->csv_parameter_datei->Lesen (px);
    this->csv_parameter_datei->Lesen (py);
    this->csv_parameter_datei->Lesen (pz);

    CameraToWorld.nx(nx);
    CameraToWorld.ny(ny);
    CameraToWorld.nz(nz);

    CameraToWorld.ox(ox);
    CameraToWorld.oy(oy);
    CameraToWorld.oz(oz);

    CameraToWorld.ax(ax);
    CameraToWorld.ay(ay);
    CameraToWorld.az(az);

    CameraToWorld.px(px);
    CameraToWorld.py(py);
    CameraToWorld.pz(pz);


    *Camera->CameraToWorld = CameraToWorld;
    CameraToWorld.InversHomogenousPose(CameraToWorld.HomogenePosenMatrix, WorldToCamera.HomogenePosenMatrix);

    *Camera->WorldToCamera = WorldToCamera;

    std::cout << "**INFO** Kameraposition fuer Kamera " << std::to_string(Camera->getCameraID()) << " wurde geladen" << std::endl;

    }
  else
    {
    std::cout << "**ERROR** Kameraposition fuer Kamera " << std::to_string(Camera->getCameraID()) << " wurde nicht geladen" << std::endl;
    }
  this->csv_parameter_datei->Schliessen();
  }

double* C_LoadManager::loadRobotTCP(double (&tcp)[4][4])
  {
  string  Dateiname;
  string  Dateityp;

    Dateiname   = "../Parameter/Flange_To_EndEffector_Pose_No_Gripper_default.csv";
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

double* C_LoadManager::loadRobotTCPCalibration(double (&tcp)[4][4])
  {
  string  Dateiname;
  string  Dateityp;

    Dateiname   = "../Parameter/Flange_To_EndEffector_Pose_World_Calibration_Tool.csv";
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
        std::cout << "**INFO** TCP wurde auf Kalibriertool eingerichtet" << std::endl;

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

void C_LoadManager::loadRobotCos    (Robot_Panda::C_Robot_Panda& robot)
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
    robot.Abs_RobotToWorld_Pose = RobotToWorld;
    robot.Abs_WorldToRobot_Pose = WorldToRobot;
    this->csv_parameter_datei->Schliessen();


    }
  }

void C_LoadManager::loadRobotHomePose(C_AbsolutePose *HomePose)
  {
  string Dateiname = "../Parameter/RobotHome_Pose.csv";
  string Dateityp = "Pose Robot TCP Home";;

  this->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

  if (this->csv_parameter_datei->IsOpen())
    {
    this->csv_parameter_datei->Lesen(Dateityp);

    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[0][0]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[1][0]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[2][0]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[0][1]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[1][1]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[2][1]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[0][2]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[1][2]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[2][2]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[0][3]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[1][3]);
    this->csv_parameter_datei->Lesen(HomePose->HomogenePosenMatrix[2][3]);
    this->csv_parameter_datei->Schliessen();
      std::cout << "Home Pose loaded" << std::endl;

    }
  }

void C_LoadManager::loadPID(Robot_Panda::C_Robot_Panda &robot)
  {
  double  Kp;
  double  Tn;
  double  Tv;
  bool    P_Enabled;
  bool    I_Enabled;
  bool    D_Enabled;
  double  Kp_OT_trans;
  double  Tn_OT_trans;
  double  Tv_OT_trans;
  bool    P_OT_Enabled_trans;
  bool    I_OT_Enabled_trans;
  bool    D_OT_Enabled_trans;
  double  Kp_OT_rot;
  double  Tn_OT_rot;
  double  Tv_OT_rot;
  bool    P_OT_Enabled_rot;
  bool    I_OT_Enabled_rot;
  bool    D_OT_Enabled_rot;
  string  Dateiname;
  string  Dateityp;
  double  Taktzeit;

    Dateiname   = "../../../Parameter/PID_Parameter_PandaID.csv";
    Dateityp    = "";

    this->csv_parameter_datei->Oeffnen(Dateiname, Enum_CSV_Access::Read);

    if (this->csv_parameter_datei->IsOpen())
      {
      this->csv_parameter_datei->Lesen(Dateityp);
      this->csv_parameter_datei->Lesen(Kp);
      this->csv_parameter_datei->Lesen(Tn);
      this->csv_parameter_datei->Lesen(Tv);
      this->csv_parameter_datei->Lesen(P_Enabled);
      this->csv_parameter_datei->Lesen(I_Enabled);
      this->csv_parameter_datei->Lesen(D_Enabled);
      this->csv_parameter_datei->Lesen(Kp_OT_trans);
      this->csv_parameter_datei->Lesen(Tn_OT_trans);
      this->csv_parameter_datei->Lesen(Tv_OT_trans);
      this->csv_parameter_datei->Lesen(P_OT_Enabled_trans);
      this->csv_parameter_datei->Lesen(I_OT_Enabled_trans);
      this->csv_parameter_datei->Lesen(D_OT_Enabled_trans);
      this->csv_parameter_datei->Lesen(Kp_OT_rot);
      this->csv_parameter_datei->Lesen(Tn_OT_rot);
      this->csv_parameter_datei->Lesen(Tv_OT_rot);
      this->csv_parameter_datei->Lesen(P_OT_Enabled_rot);
      this->csv_parameter_datei->Lesen(I_OT_Enabled_rot);
      this->csv_parameter_datei->Lesen(D_OT_Enabled_rot);
      this->csv_parameter_datei->Lesen(Taktzeit);

      this->csv_parameter_datei->Schliessen();
      }
    else
      {
      // Standartwerte
      Kp                    = 1.0;
      Tn                    = 1000.0;
      Tv                    = 0.001;
      P_Enabled             = true;
      I_Enabled             = false;
      D_Enabled             = false;

      Kp_OT_trans           = 1.0;
      Tn_OT_trans           = 1000.0;
      Tv_OT_trans           = 0.001;
      P_OT_Enabled_trans    = true;
      I_OT_Enabled_trans    = false;
      D_OT_Enabled_trans    = false;

      Kp_OT_rot             = 1.0;
      Tn_OT_rot             = 1000.0;
      Tv_OT_rot             = 0.001;
      P_OT_Enabled_rot      = true;
      I_OT_Enabled_rot      = false;
      D_OT_Enabled_rot      = false;

      Taktzeit              = 0.001;
      }

    robot.PID_Regler_X_CamCalib->Set_PID_Parameter    (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_Y_CamCalib->Set_PID_Parameter    (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_Z_CamCalib->Set_PID_Parameter    (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_RX_CamCalib->Set_PID_Parameter   (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_RY_CamCalib->Set_PID_Parameter   (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_RZ_CamCalib->Set_PID_Parameter   (P_Enabled,          I_Enabled,          D_Enabled,          Kp,          Tn,          Tv ,          Taktzeit);
    robot.PID_Regler_X_OT->Set_PID_Parameter          (P_OT_Enabled_trans, I_OT_Enabled_trans, D_OT_Enabled_trans, Kp_OT_trans, Tn_OT_trans, Tv_OT_trans,  Taktzeit);
    robot.PID_Regler_Y_OT->Set_PID_Parameter          (P_OT_Enabled_trans, I_OT_Enabled_trans, D_OT_Enabled_trans, Kp_OT_trans, Tn_OT_trans, Tv_OT_trans,  Taktzeit);
    robot.PID_Regler_Z_OT->Set_PID_Parameter          (P_OT_Enabled_trans, I_OT_Enabled_trans, D_OT_Enabled_trans, Kp_OT_trans, Tn_OT_trans, Tv_OT_trans,  Taktzeit);
    robot.PID_Regler_RX_OT->Set_PID_Parameter         (P_OT_Enabled_rot,   I_OT_Enabled_rot,   D_OT_Enabled_rot,   Kp_OT_rot,   Tn_OT_rot,   Tv_OT_rot,    Taktzeit);
    robot.PID_Regler_RY_OT->Set_PID_Parameter         (P_OT_Enabled_rot,   I_OT_Enabled_rot,   D_OT_Enabled_rot,   Kp_OT_rot,   Tn_OT_rot,   Tv_OT_rot,    Taktzeit);
    robot.PID_Regler_RZ_OT->Set_PID_Parameter         (P_OT_Enabled_rot,   I_OT_Enabled_rot,   D_OT_Enabled_rot,   Kp_OT_rot,   Tn_OT_rot,   Tv_OT_rot,    Taktzeit);
    std::cout << "PID Values loaded" << std::endl;
    }





