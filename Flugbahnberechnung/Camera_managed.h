#pragma once
#include "GlobalObjects.h"
#include "Camera_unmanaged.h"



using namespace nmsp_GlobalObjects;
/*********************************************************** Vorwärtsdeklarationen ************************************************************/

namespace nmsp_camera_managed
  {
  using namespace nmsp_camera_unmanaged;
  ref class C_camera_managed
    {
      public:
      /*************************************************************** Konstruktoren *************************************************************/
      C_camera_managed                                                  (C_GlobalObjects* GlobalObjects);
      /*************************************************************** Destruktor ****************************************************************/
      ~C_camera_managed                                                 ();
      /**************************************************** Öffentliche Klassenobjekte ********************************************************/
      public:
      c_camera_unmanaged*                 camera_unmanaged;

      /**************************************************** Öffentliche Anwender-Attribute ********************************************************/


      /******************************************** Nicht öffentliche private Anwender-Attribute **************************************************/
      private:
      C_GlobalObjects*                    GlobalObjects;

      
      /********************************************************* Öffentliche Klassenmethoden*******************************************************/
      public:
  
      /******************************************************** Private Klassenmethoden***************************************************************/

    };
  }

