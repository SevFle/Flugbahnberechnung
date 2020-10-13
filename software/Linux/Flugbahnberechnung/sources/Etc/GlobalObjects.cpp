
#include "headers/Etc/GlobalObjects.h"


using namespace GlobalObjects;

C_GlobalObjects::C_GlobalObjects ()
  {
  absCameras                = 0;
  camera_id                 = 0;
  this->camera_order        = new std::vector<int>;
  this->camToWorld          = new C_AbsolutePose;
  this->worldToCam          = new C_AbsolutePose;
  this->camToBoard          = new C_RelativePose;
  this->watchdog            = nullptr;

  }
C_GlobalObjects::~C_GlobalObjects ()
  {
  this->watchdog            = nullptr;
  delete                    (camToBoard);
  delete                    (camToWorld);
  delete                    (worldToCam);
  delete                    (this->camera_order);
  camera_id                 = 0;
  absCameras                = 0;
  }
