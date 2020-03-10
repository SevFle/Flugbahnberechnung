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
  }
/**************************************************************** Destruktor ****************************************************************/
C_camera_managed::~C_camera_managed()
  {
  delete (camera_unmanaged);
  GlobalObjects = nullptr;
  }



//System::Void C_camera_managed::Mat2Bitmap_unfiltered                                     (int camera_id, cv::Mat Mat2Bit_Img)
//  {
// // cv::Size                size         = camera_unmanaged->
//  //cv::cvtColor                         (camera_unmanaged->camera_vector_referrences[camera_id]->cpu_src_img, camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap, cv::COLOR_BGRA2RGBA);
//  //System::Drawing::Bitmap color_Bitmap (size.width, size.height, camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap.step1(), System::Drawing::Imaging::PixelFormat::Format24bppRgb, &camera_unmanaged->camera_vector_referrences[camera_id]->Mat2Bitmap.ptr);
// 
//
//  }

