#pragma once
#include "headers/posen.h"
#include "headers/GlobalObjects.h"

using namespace GlobalObjects;


namespace Savemanager
  {
  class c_SaveManager
    {
    public:
    c_SaveManager();
    ~c_SaveManager();

    C_GlobalObjects* GlobalObjects;


    void saveCameraCalibration (int camera_id);
    void saveCameraPositioning (std::vector<int> camera_list) const;
    void saveCameraCos (int camera_id, C_AbsolutePose& WorldToCam_Param);
    void saveCameraSettings (int camera_id);

    };

  }

