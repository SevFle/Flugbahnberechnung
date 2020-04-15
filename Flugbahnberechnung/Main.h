#pragma once

#include "GlobalObjects.h"
#include "Camera_managed.h"

using namespace nmsp_camera_managed;
using namespace nmsp_GlobalObjects;


/*********************************************************** Vorwärtsdeklarationen ********************************************************/
#pragma region Vorwärtsdeklarationen 
namespace NmSp_frm_Main
  {
  ref class C_frm_Main;
  }
using namespace NmSp_frm_Main;
  
namespace NmSp_CamerCalibration_Menu
  {
  ref class C_frm_CameraCalibration_Menu;
  }
using namespace NmSp_CamerCalibration_Menu;

namespace NmSp_CamerCalibration_Single
  {
  ref class C_frm_CameraCalibration_Single;
  }
using namespace NmSp_CamerCalibration_Single;

namespace NmSp_frm_CameraCalibration_Stereo
  {
  ref class C_frm_CameraCalibration_Stereo;
  }
  using namespace NmSp_frm_CameraCalibration_Stereo;

  namespace NmSp_frm_ObjectCalibration
    {
    ref class c_frm_object_calibration;
  }
  using namespace NmSp_frm_ObjectCalibration;

  namespace nmsp_frm_camera_positioning
    {
    ref class c_frm_Camera_Positioning;
    }
  using namespace nmsp_frm_camera_positioning;

  #pragma endregion

/*********************************************************** Definition Namespace **************************************************************/
  namespace nmsp_Main
  {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Threading;
  /******************************************************** Klasse C_main **********************************************************************/
  public ref class C_Main
    {
      public:
      C_Main              (C_GlobalObjects* GlobalObjects);

      ~C_Main             ();

      private:
      C_GlobalObjects*     GlobalObjects;

      public:
      C_frm_Main^                       frm_Main;
      C_frm_CameraCalibration_Menu^     frm_CameraCalibration_Menu;
      C_frm_CameraCalibration_Single^   frm_CameraCalibration_Single;
      C_frm_CameraCalibration_Stereo^   frm_CameraCalibration_Stereo;
      c_frm_object_calibration^          frm_ObjectCalibration;
      c_frm_Camera_Positioning^         frm_Camera_Positioning;
      C_camera_managed^                 camera_managed;

    };//ref class C_Main

  }//namespace nmsp_Main


#include "frm_Main.h"
#include "frm_Camera_Calibration.h"
#include "frm_Object_Calibration.h"
#include "frm_Camera_Positioning.h"

