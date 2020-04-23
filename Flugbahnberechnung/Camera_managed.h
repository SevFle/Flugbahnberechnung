#pragma once
#include "GlobalObjects.h"
#include "Camera_unmanaged.h"



using namespace nmsp_GlobalObjects;
/*********************************************************** Vorw�rtsdeklarationen ************************************************************/

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
      /**************************************************** �ffentliche Klassenobjekte ********************************************************/
      public:
      c_camera_unmanaged*                 camera_unmanaged;

      /**************************************************** �ffentliche Anwender-Attribute ********************************************************/


      /******************************************** Nicht �ffentliche private Anwender-Attribute **************************************************/
      private:
      C_GlobalObjects*                    GlobalObjects;

      
      /********************************************************* �ffentliche Klassenmethoden*******************************************************/
      public:
  
      /******************************************************** Private Klassenmethoden***************************************************************/

    };
  }

