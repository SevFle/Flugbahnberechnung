#pragma once

#include "GlobalObjects.h"


using namespace nmsp_GlobalObjects;

C_GlobalObjects::C_GlobalObjects()
  {
  cameras_in_use = 0;
  camera_id = 0;
  }
C_GlobalObjects::~C_GlobalObjects()
  {
  camera_id = 0;
  cameras_in_use = 0;
  }

