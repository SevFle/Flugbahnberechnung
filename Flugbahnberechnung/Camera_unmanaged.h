#pragma once

/************************************************************ Includes *******************************************************************/

#include "opencv_unmanaged.h"
#include "tracking.h"
#include "GlobalObjects.h"

namespace std
  {
  class thread;
  } using namespace std;

using namespace nmsp_opencv_unmanaged;
using namespace nmsp_tracking;
using namespace nmsp_posen;
using namespace nmsp_GlobalObjects;



namespace nmsp_camera_unmanaged
  {
  class c_camera_unmanaged
    {
      
      public:
      /*************************************************************** Konstruktoren *************************************************************/
      c_camera_unmanaged (int cameras_in_use, C_GlobalObjects* GlobalObjects);
      /*************************************************************** Destruktor ****************************************************************/
      ~c_camera_unmanaged ();


      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      c_tracking*                                               tracking;

      std::thread*                                              camera_thread;


      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                                       cameras_in_use;
      int                                                       camera_id;

      int**                                                     camera_referrence;

      bool                                                      stop_statemachine;
      bool                                                      load_positioning;
      bool                                                      tracking_active;

      std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>   camera_vector;


      /*** Variablen zur Kamerakalibrierung ********************************************************/

      public:
      int                           numCornersWidth;
      int                           numCornersHeight;
      float                           SquareSize;
      int                             numBoards_imgs;

      private:
      int                             Photo_ID;








      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      C_GlobalObjects*                                                     GlobalObjects;
      int                                                                  current_camera_id;

    
      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:
      void  move_camera_vector2temp                         (int camera_desired_id, int camera_current_id, std::vector<c_opencv_unmanaged*>& temp_CameraVector);
      void  move_camera_temp2vector                         (int cameras_in_use, std::vector<c_opencv_unmanaged*> temp_CameraVector);


      void save_camera_calibration                          (int camera_id);
      void load_camera_calibration                          (int camera_id);
      void save_camera_positioning                          (std::vector<int> camera_list) const;
      void load_camera_positioning                          ();
      void init_camera_vectors                              (int cameras_in_use);
      void close_cameras                                    (int cameras_in_use);

      void save_camera_settings                             (int camera_id);
      void load_camera_settings                             (int camera_id);

      void calibrate_single_camera                          (int current_camera_id);
      void calibrate_stereo_camera                          (int current_camera_id);
      void sm_object_tracking                               ();


    /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void start_camera_thread                         ();
    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged

