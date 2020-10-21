
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
  this->loadManager         = new LoadManager::C_LoadManager;
  this->saveManager         = new Savemanager::c_SaveManager;
  this->watchdog            = nullptr;
  this->globalLock          = new std::mutex;

  this->objectPosenQue =  new tbb::concurrent_bounded_queue<GlobalObjects::S_PositionPayload*>;
  this->objectPosenQue->set_capacity(5);

  }
C_GlobalObjects::~C_GlobalObjects ()
  {
  delete                    (objectPosenQue);

  delete                    (globalLock);
  this->watchdog            = nullptr;
  delete                    (saveManager);
  delete                    (loadManager);
  delete                    (camToBoard);
  delete                    (camToWorld);
  delete                    (worldToCam);
  delete                    (this->camera_order);
  camera_id                 = 0;
  absCameras                = 0;
  }
