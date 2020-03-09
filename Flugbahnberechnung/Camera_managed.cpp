#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_managed.h"

/****************************************************************** Namespaces***************************************************************/

using namespace nmsp_GlobalObjects;
using namespace nmsp_camera_managed;
/*************************************************************** Konstruktoren **************************************************************/
C_camera_managed::C_camera_managed                            (C_GlobalObjects^ GlobalObjects)
  {
  this->GlobalObjects = GlobalObjects;
  this->camera_unmanaged = new c_camera_unmanaged             (GlobalObjects->cameras_in_use);

  for (int i = 0; i<this->camera_unmanaged->cameras_in_use; i++)
    {
    }
  }
/**************************************************************** Destruktor ****************************************************************/
C_camera_managed::~C_camera_managed()
  {
  delete (camera_unmanaged);
  GlobalObjects = nullptr;
  }



System::Drawing::Bitmap C_camera_managed::Mat2Bitmap_unfiltered                                     (int camera_id)
  {
  int Cols;
  int Rows;
  cv::cvtColor(camera_unmanaged->camera_vector_referrences[camera_id]->cpu_src_img, camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap, cv::COLOR_BGRA2RGBA);
  Cols = camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap.col;
  Rows = camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap.row;
  System::Drawing::Bitmap Color_Bitmap (Cols, Rows, 1, System::Drawing::Imaging::PixelFormat::Format24bppRgb, camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap.ptr);
  return Color_Bitmap;
  }

cv::


