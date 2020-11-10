#ifndef __GlobalObjects_H
#define __GlobalObjects_H
#include "watchdog.h"
#include "headers/CSV_Manager/loadmanager.h"
#include "headers/CSV_Manager/savemanager.h"

#if !defined(Q_MOC_RUN)
#include <tbb/tbb.h>
#include "tbb/pipeline.h"
#include "tbb/concurrent_queue.h"
#endif

#include <vector>

using namespace UM_CSV_Datei;

/*********************************************************** Definition Namespace **************************************************************/
namespace GlobalObjects
  {
  struct S_PositionPayload
    {
    posen::S_Positionsvektor*     predPosition;
    double                        predVelocity[3];
    double                        dt;
    float                         gain[][];
    };
  class C_GlobalObjects
    {
    public:
    C_GlobalObjects ();
    ~C_GlobalObjects ();

    watchdog::C_watchdog*         watchdog;
    Savemanager::c_SaveManager*   saveManager;
    LoadManager::C_LoadManager*   loadManager;
    posen::C_AbsolutePose*        camToWorld;
    posen::C_AbsolutePose*        worldToCam;
    posen::C_RelativePose*        camToBoard;
    std::mutex*                   globalLock;

    tbb::concurrent_bounded_queue<GlobalObjects::S_PositionPayload*>*  objectPosenQue;


    int absCameras;
    int camera_id;

    std::vector<int>* camera_order;
    }; //ref class C_GlobalObjects
  }
#endif
