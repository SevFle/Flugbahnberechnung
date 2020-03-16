#include "frm_CameraCalibration_Stereo.h"

using namespace NmSp_frm_CameraCalibration_Stereo;


C_frm_CameraCalibration_Stereo::C_frm_CameraCalibration_Stereo(C_GlobalObjects* GlobalObjects, C_Main^  Main)
  {
  InitializeComponent();
  }
C_frm_CameraCalibration_Stereo::~C_frm_CameraCalibration_Stereo()
  {
  if (components)
    {
    delete components;
    }
  }