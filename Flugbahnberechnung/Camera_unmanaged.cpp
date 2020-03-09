#pragma once
/****************************************************************** Includes ****************************************************************/
#include "Camera_unmanaged.h"

#include <thread>

/****************************************************************** Namespaces***************************************************************/
using namespace nmsp_camera_unmanaged;
/*************************************************************** Konstruktoren **************************************************************/
c_camera_unmanaged::c_camera_unmanaged                                  (int cameras_in_use)
  {
  
  this->cameras_in_use  = cameras_in_use;
  stop_statemachine = false;
  }
/**************************************************************** Destruktor ****************************************************************/
c_camera_unmanaged::~c_camera_unmanaged                                 ()
  {
  cameras_in_use  = 0;
  }

//bool c_opencv_unmanaged::tbb_camera_pipeline (size_t ntoken)
//  {
//  /*tbb::parallel_pipeline
//    (
//    ntoken,
//    tbb::make_filter<void, cv::Mat>
//      (
//  tbb::filter::serial_in_order,[&](tbb::flow_control& fc)-> cv::Mat
//        {
//        grabbed_frame = camera_vector[current_pipeline_camera_grab].grab;
//        current_pipeline_camera_grab++;
//        if (current_pipeline_camera_grab > cameras_in_use-1)
//          {
//          current_pipeline_camera_grab = 0;
//          }
//        return grabbed_frame;
//        }
//      ) &
//    tbb::make_filter<cv::Mat, cv::Mat>
//      (
//  tbb::filter::parallel, [](cv::Mat)
//        {
//    
//        }
//      )
//      
//    )*/
//  
//  }
/*************************************************** Nicht öffentliche private Methoden *****************************************************/
void  c_camera_unmanaged::create_cam_vector                             (int camera_id)
  {
  //nmsp_opencv_unmanaged::c_opencv_unmanaged* opencv = new nmsp_opencv_unmanaged::c_opencv_unmanaged(cameras_in_use, camera_id);
  //camera_vector_unsorted.push_back(opencv);
  }

/******************************************************* Öffentliche Anwender-Methoden ******************************************************/
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

void c_camera_unmanaged::state_machine_object_calibration               ()
  {
  while (stop_statemachine == false)
    {
    //state_machine_per_vector_exe();
    }
  }

void c_camera_unmanaged::create_camera_objects                          (int cameras_in_use)
{
  for (int i = 0; i < cameras_in_use; i++)
  {
    nmsp_opencv_unmanaged::c_opencv_unmanaged* cam = new nmsp_opencv_unmanaged::c_opencv_unmanaged (i);
    camera_vector_unsorted.push_back                       (*cam);
    }
}

void c_camera_unmanaged::sort_camera_vector                             (int camera_current_id, int camera_desired_id) 
  {
  camera_vector_referrences[camera_current_id] = camera_vector_unsorted[camera_desired_id];
  }
