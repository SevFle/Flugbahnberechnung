#pragma once

#include "headers/GlobalObjects.h"


using namespace GlobalObjects;

C_GlobalObjects::C_GlobalObjects ()
  {
  absCameras                = 0;
  camera_id                 = 0;
  this->csv_parameter_datei = new C_CSV_Parameter_Datei();
  this->camera_order        = new std::vector<int>;
  }
C_GlobalObjects::~C_GlobalObjects ()
  {
  delete                    (this->camera_order);
  delete                    (this->csv_parameter_datei);
  camera_id                 = 0;
  absCameras                = 0;
  }
