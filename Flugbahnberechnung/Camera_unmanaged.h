#pragma once

/************************************************************ Includes *******************************************************************/

#include "opencv_unmanaged.h"
#include "GlobalObjects.h"
#include <bitset>

namespace std
  {
  class thread;
  } using namespace std;


namespace nmsp_camera_unmanaged
  {
  using namespace nmsp_opencv_unmanaged;
  using namespace nmsp_GlobalObjects;
  class c_camera_unmanaged
    {
      
      public:
      /*************************************************************** Konstruktoren *************************************************************/
      c_camera_unmanaged (int cameras_in_use, C_GlobalObjects* GlobalObjects);
      /*************************************************************** Destruktor ****************************************************************/
      ~c_camera_unmanaged ();


      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      //c_opencv_unmanaged*                                   opencv_unmananged;

      std::thread*                                              camera_thread;


      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/
      public:
      int                                                       cameras_in_use;
      int                                                       statemachine_state;
      int                                                       camera_id;

      int**                                                     camera_referrence;

      bool                                                      stop_statemachine;
      bool                                                      load_positioning;

      std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>   camera_vector;
      std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*>   camera_vector_temp;

      /*** Variablen zur Kamerakalibrierung ********************************************************/

      public:
      float                           numCornersWidth;
      float                           numCornersHeight;
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
      void  move_camera_vector2temp                         (int camera_desired_id, int camera_current_id);
      void  move_camera_temp2vector                         (int cameras_in_use);


      void save_camera_calibration                          (int camera_id);
      void load_camera_calibration                          (int camera_id);
      void save_camera_positioning                          (std::vector<int> camera_list);
      void load_camera_positioning                          ();
      void init_camera_vectors                              (int cameras_in_use);
      void close_cameras                                    (int cameras_in_use);

      void save_camera_settings                             (int camera_id);
      void load_camera_settings                             (int camera_id);

      void calibrate_single_camera                          (int current_camera_id);
      void save_picture                                     (int camera_id, int photo_id);



    /******************************************************* Private Klassenmethoden***************************************************************/
      private:
      void start_camera_thread                         ();
    };// c_camera_unmanaged
  }//nmsp_c_camera_unmanaged

