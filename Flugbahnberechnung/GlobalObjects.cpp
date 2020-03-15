#pragma once

#include "GlobalObjects.h"


using namespace nmsp_GlobalObjects;

C_GlobalObjects::C_GlobalObjects()
  {
  cameras_in_use = 0;
  camera_id = 0;
  this->csv_parameter_datei = new C_CSV_Parameter_Datei();
  }
C_GlobalObjects::~C_GlobalObjects()
  {
  delete (this->csv_parameter_datei);
  camera_id = 0;
  cameras_in_use = 0;
  }

