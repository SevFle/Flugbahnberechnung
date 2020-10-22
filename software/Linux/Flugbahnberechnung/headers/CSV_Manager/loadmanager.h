#ifndef __Loadmanager_H
#define __Loadmanager_H
#include "headers/Roboter/posen.h"
#include "headers/CSV_Manager/CSV_Datei.h"

#include "headers/Bildverarbeitung/camera2.h"
#include "headers/Roboter/robot.h"

using namespace UM_CSV_Datei;

namespace Camera
  {
  class C_Camera2;
  }

namespace LoadManager
  {
  class C_LoadManager
    {
    public:
    C_LoadManager                             ();
    ~C_LoadManager                            ();

    C_CSV_Parameter_Datei* csv_parameter_datei;

    void              loadCameraCalibration   (Camera::C_Camera2* Camera);
    bool              loadCameraPositioning   (std::vector<Camera::C_Camera2*> &vecCameras, int absCameras);
    void              loadCameraCos           (Camera::C_Camera2* Camera);
    void              loadCameraSettings      (Camera::C_Camera2* Camera);

    double*           loadRobotTCP            (double (&tcp)[4][4]);
    double*           loadRobotTCPCalibration (double (&tcp)[4][4]);

    void              loadRobotCos            (Robot_Panda::C_Robot_Panda& robot);
    void              loadRobotHomePose       (C_AbsolutePose* HomePose);
    void              loadPID                 (Robot_Panda::C_Robot_Panda& robot);


    };

  }

#endif //Loadmanager_H
