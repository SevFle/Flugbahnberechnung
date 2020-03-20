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
  //camera_thread   = new std::thread(&c_camera_unmanaged::camera_vector_unsorted[camera_id]::camera_thread, this);
  //std::thread Camera_Thread(camera_vector_unsorted[camera_id]->camera_thread());
 //std::thread cam_thread( camera_vector_unsorted[camera_id]);
  camera_vector_unsorted[current_camera_id]->camera_thread();
  }
/******************************************************* Öffentliche Anwender-Methoden ******************************************************/

void c_camera_unmanaged::state_machine_object_calibration               ()
  {
  while (stop_statemachine == false)
    {
    //state_machine_per_vector_exe();
    }
  }

void c_camera_unmanaged::create_camera_vectors                          (int cameras_in_use)
{
  for (int i = 0; i < cameras_in_use; i++)
    {
    nmsp_opencv_unmanaged::c_opencv_unmanaged *cam = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    camera_vector_unsorted.push_back                          (cam);
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
  //camera_vector_temp[camera_current_id] = std::move(camera_vector_unsorted[camera_desired_id]);
  camera_vector_temp.insert(camera_vector_temp.begin()+camera_desired_id, camera_vector_unsorted[camera_current_id]);
  std::cout << " Moved Pointer for Camera " << camera_current_id << " to Position " << camera_desired_id << " in temporary Vector" << std::endl;
  }

void c_camera_unmanaged::move_camera_temp2vector                             (int cameras_in_use)
  {
  for (int i = 0; i < cameras_in_use; i++)
    {
    camera_vector_unsorted[i] = std::move(camera_vector_temp[i]);
    }
  }

//Diese Statemachine verwendet erzeugt n Kamera Objekte die mit ihren individuellen cv::Mat Objekten arbeiten.
//void  c_camera_unmanaged::state_machine_per_object_exe                  ()
//  {
//  while (true)
//    {
//    switch (statemachine_state)
//      {
//        case 0:
//          std::cout<< "State 0 \n\n";
//          for (int i = 0; i< cameras_in_use; i++)
//            {
//            create_cam_vector(i);
//            camera_vector_unsorted[i]->create_videocapture_vector(i);
//            camera_vector_unsorted[i]->init(i);
//
//            }
//
//          statemachine_state = 1;
//
//
//        case 1:
//          std::cout<< "State 1 \n\n";
//          camera_vector_unsorted[camera_id]->cpu_grab_frame(camera_vector_unsorted[camera_id]->cpu_src_img);
//          statemachine_state = 2;
//
//
//        case 2:
//          std::cout<< "State 2 \n\n";
//
//          camera_vector_unsorted[camera_id]->apply_filter(camera_vector_unsorted[camera_id]->cpu_src_img, camera_vector_unsorted[camera_id]->cpu_mid_img);
//
//          if (camera_id<cameras_in_use)
//            statemachine_state = 2;
//          statemachine_state = 3;
//
//
//        case 3:
//          std::cout<< "State 3 \n\n";
//          camera_vector_unsorted[camera_id]->cpu_mask_img(camera_vector_unsorted[camera_id]->cpu_mid_img, camera_vector_unsorted[camera_id]->cpu_masked_img);
//          statemachine_state = 4;
//
//
//        case 4:
//          std::cout<< "State 4 \n\n";
//          camera_vector_unsorted[camera_id]->cpu_img_show(camera_vector_unsorted[camera_id]->cpu_masked_img, camera_vector_unsorted[camera_id]->cpu_src_img);
//          if (cv::waitKey(5)>=0)
//            break;
//
//          statemachine_state = 5;
//
//
//        case 5:
//          std::cout<<"State 5 \n\n";
//          if (camera_id<cameras_in_use-1)
//            {
//            camera_id++;
//            }
//          else if (camera_id = cameras_in_use)
//            {
//            camera_id = 0;
//            }
//
//          statemachine_state = 1;
////
//
//      }
//    }
//  }
      //Diese Statemachine verwendet die vector<cv::Mat*> Objekte eines Camera Objektes 
//void c_camera_unmanaged::state_machine_per_vector_exe                   ()
//  {
//  nmsp_opencv_unmanaged::c_opencv_unmanaged opencv(cameras_in_use, camera_id);
//    switch (statemachine_state)
//      {
//        case 0:
//          std::cout<< "State 0 \n\n";
//          for (int i = 0; i< cameras_in_use; i++)
//            {
//            opencv.create_videocapture_vector(i);
//            opencv.init(i);
//            opencv.create_img_vectors();
//            }
//
//          statemachine_state = 1;
//
//        case 1:
//          std::cout<< "State 1 \n\n";
//          opencv.cpu_grab_frame(opencv.cpu_src_vector[camera_id]);
//          statemachine_state = 2;
//        case 2:
//          std::cout<< "State 2 \n\n";
//          opencv.apply_filter(opencv.cpu_src_vector[camera_id], opencv.cpu_mid_vector[camera_id]);
//
//        case 3:
//          std::cout<< "State 3 \n\n";
//          opencv.cpu_mask_img(opencv.cpu_mid_vector[camera_id], opencv.cpu_masked_vector[camera_id]);
//          statemachine_state = 4;
//        case 4:
//          std::cout<< "State 4 \n\n";
//          opencv.cpu_img_show(opencv.cpu_masked_vector[camera_id], opencv.cpu_src_vector[camera_id]);
//          if (cv::waitKey(5)>=0)
//            break;
//
//          statemachine_state = 5;
//        case 5:
//          std::cout<<"State 5 \n\n";
//          if (camera_id<cameras_in_use-1)
//            {
//            camera_id++;
//            }
//          else if (camera_id = cameras_in_use)
//            {
//            camera_id = 0;
//            }
//
//          statemachine_state = 1;
//
//
//      }
//
//  }
