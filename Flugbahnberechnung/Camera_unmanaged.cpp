#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_unmanaged.h"

#include <thread>

/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_camera_unmanaged;
/*************************************************************** Konstruktoren **************************************************************/
c_camera_unmanaged::c_camera_unmanaged                                  (int cameras_in_use)
  {
  this->cameras_in_use = cameras_in_use;
  stop_statemachine = false;

  }
/**************************************************************** Destruktor ****************************************************************/
c_camera_unmanaged::~c_camera_unmanaged                                 ()
  {
  stop_statemachine = false;
  cameras_in_use  = 0;
  }

/*************************************************** Nicht öffentliche private Methoden *****************************************************/

void c_camera_unmanaged::start_camera_thread                            ()
  {
  //camera_thread   = new std::thread(&c_camera_unmanaged::camera_vector[camera_id]::camera_thread, this);
  //std::thread Camera_Thread(camera_vector[camera_id]->camera_thread());
 //std::thread cam_thread( camera_vector[camera_id]);
  camera_vector[current_camera_id]->camera_thread();
  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void c_camera_unmanaged::save_camera_settings()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {
    
    }
  }
void c_camera_unmanaged::apply_camera_settings()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {

    }
  }
void c_camera_unmanaged::save_camera_calibration()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {

    }
  }
void c_camera_unmanaged::apply_camera_calibration()
  {
  for (int i = 0; i< cameras_in_use; i++)
    {

    }
  }


void c_camera_unmanaged::create_camera_vectors                          (int cameras_in_use)
{
  for (int i = 0; i < cameras_in_use; i++)
    {
    nmsp_opencv_unmanaged::c_opencv_unmanaged *opencv_unmanaged = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    camera_vector.push_back                          (opencv_unmanaged);
    //camera_vector_referrences.push_back                       (camera_referrence);
    std::cout << "Created " << i+1 << " Camera Objects with according pointers"<< std::endl;
    current_camera_id = i;
    camera_thread   = new std::thread(&c_camera_unmanaged::start_camera_thread, this);
    camera_vector_temp.resize(cameras_in_use);
    }
}

void c_camera_unmanaged::move_camera_vector2temp                             (int camera_current_id, int camera_desired_id)
  {
  std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>::iterator iterator = camera_vector_temp.begin();
  // Wo ist die feste Position der Kamera? -> Camera_Current_ID
  // Wo ist die Position der Kamera im unsorted Vector? ->Camera_desired_id
  // Zeige die fest installierte Position des Vektors "Referrences" auf die Adresse im Unsortierten Vektor
  camera_vector_temp[camera_current_id] = std::move(camera_vector[camera_desired_id]);
  //camera_vector_temp.insert(camera_vector_temp.begin()+camera_desired_id, camera_vector[camera_current_id]);
  std::cout << " Moved Pointer for Camera " << camera_current_id << " to Position " << camera_desired_id << " in temporary Vector" << std::endl;
  }

void c_camera_unmanaged::move_camera_temp2vector                             (int cameras_in_use)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector[i] = std::move(camera_vector_temp[i]);
    }
  }

