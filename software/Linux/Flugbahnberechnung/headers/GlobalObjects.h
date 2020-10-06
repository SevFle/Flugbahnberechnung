#ifndef __GlobalObjects_H
#define __GlobalObjects_H
#include "CSV_Datei.h"
#include "watchdog.h"
#include <vector>

using namespace UM_CSV_Datei;

/*********************************************************** Definition Namespace **************************************************************/
namespace GlobalObjects
  {
  class C_GlobalObjects
    {
    public:
    C_GlobalObjects ();
    ~C_GlobalObjects ();

    C_CSV_Parameter_Datei* csv_parameter_datei;
    watchdog::C_watchdog* watchdog;


    int absCameras;
    int camera_id;

    std::vector<int>* camera_order;
    }; //ref class C_GlobalObjects
  }
#endif
