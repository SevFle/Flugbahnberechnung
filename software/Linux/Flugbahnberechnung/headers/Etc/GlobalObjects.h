#ifndef __GlobalObjects_H
#define __GlobalObjects_H
#include "watchdog.h"
#include "headers/CSV_Manager/loadmanager.h"
#include "headers/CSV_Manager/savemanager.h"
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

    watchdog::C_watchdog*         watchdog;
    Savemanager::c_SaveManager*   saveManager;
    LoadManager::C_LoadManager*   loadManager;
    C_CSV_Parameter_Datei*        csv_parameter_datei;
    posen::C_AbsolutePose*        camToWorld;
    posen::C_AbsolutePose*        worldToCam;
    posen::C_RelativePose*        camToBoard;

    int absCameras;
    int camera_id;

    std::vector<int>* camera_order;
    }; //ref class C_GlobalObjects
  }
#endif
