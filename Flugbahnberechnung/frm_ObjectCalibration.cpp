#pragma once
#include "frm_ObjectCalibration.h"

using namespace NmSp_ObjectCalibration;

C_frm_ObjectCalibration::C_frm_ObjectCalibration(C_GlobalObjects^ GlobalObjects, C_Main^ Main)
  {
  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  }

C_frm_ObjectCalibration::~C_frm_ObjectCalibration()
  {
  if (components)
    {
    delete components;
    }
  }


