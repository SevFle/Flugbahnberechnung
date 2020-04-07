#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_managed.h"

/****************************************************************** Namespaces***************************************************************/

using namespace nmsp_GlobalObjects;
using namespace nmsp_camera_managed;
/*************************************************************** Konstruktoren **************************************************************/
C_camera_managed::C_camera_managed                            (C_GlobalObjects* GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;
  this->camera_unmanaged = new c_camera_unmanaged             (GlobalObjects->cameras_in_use, GlobalObjects);
  }
/**************************************************************** Destruktor ****************************************************************/
C_camera_managed::~C_camera_managed()
  {
  delete (camera_unmanaged);
  GlobalObjects = nullptr;
  }

