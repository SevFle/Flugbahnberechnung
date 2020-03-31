#pragma once
#include "CSV_Datei.h"
#include <vector>

using namespace UM_CSV_Datei;
/*********************************************************** Definition Namespace **************************************************************/
namespace nmsp_GlobalObjects
  {
   class C_GlobalObjects
    {
      public:
      C_GlobalObjects();
      ~C_GlobalObjects();

      C_CSV_Parameter_Datei* csv_parameter_datei;

      int cameras_in_use;
      int camera_id;

      std::vector<int> *camera_order;

    }; //ref class C_GlobalObjects

  }

