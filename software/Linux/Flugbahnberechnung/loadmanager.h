#pragma once
#include "headers/posen.h"
#include "headers/GlobalObjects.h"

using namespace GlobalObjects;

namespace Camera
  {
  class C_Camera2;
  }

namespace LoadManager
  {
  class C_LoadManager
    {
    public:
    C_LoadManager();
    ~C_LoadManager();



    C_GlobalObjects* GlobalObjects;


    void loadCameraCalibration  (Camera::C_Camera2*);
    void loadCameraPositioning  (std::vector<Camera::C_Camera2*>vecCameras);
    void loadCameraCos          (Camera::C_Camera2*, C_AbsolutePose& WorldToCam_Param);
    void loadCameraSettings     (Camera::C_Camera2*);



    };

  }

