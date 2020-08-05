#pragma once
#include "headers/posen.h"
#include "headers/GlobalObjects.h"
#include "camera2.h"

using namespace GlobalObjects;


namespace Savemanager
  {
  class c_SaveManager
    {
    public:
    c_SaveManager(C_GlobalObjects* GlobalObjects);
    ~c_SaveManager();

    C_GlobalObjects* GlobalObjects;


    void saveCameraCalibration    (Camera::C_Camera2 &Camera);
    void saveCameraPositioning    (std::vector<int> camera_list) const;
    void saveCameraCos            (Camera::C_Camera2 &Camera);
    void saveCameraSettings       (Camera::C_Camera2 &Camera);

    };

  }

