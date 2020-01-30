#include "frm_CameraCalibration_Single.h"

using namespace NmSp_CamerCalibration_Single;


C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single(C_GlobalObjects^ GlobalObjects, C_Main^  Main)
  {
  InitializeComponent();
  }
C_frm_CameraCalibration_Single::~C_frm_CameraCalibration_Single()
  {
  if (components)
    {
    delete components;
    }
  }