#ifndef __Loadmanager_H
#define __Loadmanager_H
#include "headers/posen.h"
#include "headers/GlobalObjects.h"

#include "camera2.h"

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
    C_LoadManager                             (C_GlobalObjects* GlobalObjects);
    ~C_LoadManager                            ();

    C_GlobalObjects* GlobalObjects;

    void              loadCameraCalibration   (Camera::C_Camera2* Camera);
    bool              loadCameraPositioning   (std::vector<int>* order);
    void              loadCameraCos           (Camera::C_Camera2* Camera);
    void              loadCameraSettings      (Camera::C_Camera2* Camera);



    };

  }

#endif //Loadmanager_H
