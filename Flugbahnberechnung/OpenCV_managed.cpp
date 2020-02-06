#pragma once
#include "OpenCV_managed.h"


using namespace nmsp_opencv_managed;

C_OpenCV_managed::C_OpenCV_managed                            (C_GlobalObjects^ GlobalObjects)
  {
  //this->opencv_unmanaged = new C_opencv_unmanaged     ();
  }

C_OpenCV_managed::~C_OpenCV_managed()
  {
  
  }

bool C_OpenCV_managed::open_cam_thread (int& cam_id, int width, int height)
  {

  }

bool C_OpenCV_managed::close_cam_thread (int& cam_id)
  {

  }
