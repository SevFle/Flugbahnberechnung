#pragma once

#include "GlobalObjects.h"

using namespace NmSp_GlobalObjects;


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
  #pragma endregion

/*********************************************************** Definition Namespace **************************************************************/
  namespace NmSp_Main
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
      C_Main              (C_GlobalObjects^ GlobalObjects);

      ~C_Main             ();

      private:
      C_GlobalObjects^     GlobalObjects;

      public:
      C_frm_Main^         frm_Main;
      C_frm_CameraCalibration_Menu^     frm_CameraCalibration_Menu;
      C_frm_CameraCalibration_Single^   frm_CameraCalibration_Single;
      C_frm_CameraCalibration_Stereo^   frm_CameraCalibration_Stereo;



    };//ref class C_Main

  }//namespace NmSp_Main


#include "frm_Main.h"
#include "frm_CameraCalibration_Menu.h"
#include "frm_CameraCalibration_Single.h"
#include "frm_CameraCalibration_Stereo.h"

