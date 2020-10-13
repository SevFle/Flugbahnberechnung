#ifndef __Savemanager_H
#define __Savemanager_H
#include "headers/Roboter/posen.h"
#include "CSV_Datei.h"
#include "headers/Bildverarbeitung/camera2.h"
#include "headers/Roboter/robot.h"

namespace Savemanager
  {
  class c_SaveManager
    {
    public:
    c_SaveManager();
    ~c_SaveManager();

    UM_CSV_Datei::C_CSV_Parameter_Datei* csv_parameter_datei;



    void saveCameraCalibration    (Camera::C_Camera2 &Camera);
    void saveCameraPositioning    (std::vector<Camera::C_Camera2*>& vecCameras, int absCameras) const;
    void saveCameraCos            (Camera::C_Camera2 &Camera);
    void saveCameraSettings       (Camera::C_Camera2 &Camera);

    void saveRobotCos            (robot::C_robot& robot);


    };

  }

#endif //Savemanager_H
