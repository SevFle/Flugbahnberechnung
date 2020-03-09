#pragma once

/************************************************************ Includes *******************************************************************/

#include "opencv_unmanaged.h"
/************************************************************ Include TBB *******************************************************************/
#include <tbb/concurrent_queue.h>
#include <tbb/pipeline.h>
#include <tbb/tbb.h>



namespace nmsp_camera_unmanaged
  {
  using namespace nmsp_opencv_unmanaged;
  class c_camera_unmanaged
    {
      
      public:
      /*************************************************************** Konstruktoren *************************************************************/
      c_camera_unmanaged (int cameras_in_use);
      /*************************************************************** Destruktor ****************************************************************/
      ~c_camera_unmanaged ();


      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      c_opencv_unmanaged*                                   opencv_unmananged;


      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                                   cameras_in_use;
      int                                                   statemachine_state;
      int                                                   camera_id;

      bool                                                  stop_statemachine;

      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged>    camera_vector_unsorted;

      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:
      void      state_machine_per_object_exe                ();
      void      state_machine_per_vector_exe                ();
      void      state_machine_object_calibration            ();
      void      create_camera_threads                       (int cameras_in_use);
      void      camera_thread                               (int camera_id);
      /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void      create_cam_vector                           (int camera_id);
      

    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged

