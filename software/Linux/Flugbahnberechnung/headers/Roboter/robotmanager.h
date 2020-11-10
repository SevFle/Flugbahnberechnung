#ifndef C_ROBOTMANAGER_H
#define C_ROBOTMANAGER_H
#include "posen.h"
#include "robot.h"
#include "headers/Etc/GlobalObjects.h"
#include "headers/Etc/mathhelper.h"

using namespace GlobalObjects;

namespace robotManager
  {
  struct robotConstraints
    {
    double X  =  0.60;
    double nX = -0.30;
    double Y  =  0.60;
    double nY = -0.60;
    double Z  =  0.80;
    double nZ = -0.20;

    };

  class C_robotManager
    {
  public:
    C_robotManager                      (C_GlobalObjects* globalObjects);
    ~C_robotManager                     ();

    Robot_Panda::C_Robot_Panda*         roboter;
    C_GlobalObjects*                    globalObjects;
    std::thread*                        robotThread;
    GlobalObjects::S_PositionPayload*   objectPayload;
    robotManager::robotConstraints*     outerConstraints;
    robotManager::robotConstraints*     innerConstraints;

    C_AbsolutePose*                     Pose_waiting;
    C_AbsolutePose*                     Pose_inter_waiting;

    posen::S_Positionsvektor*           objectEntry;
    posen::S_Positionsvektor*           objectExit;
    std::atomic<bool>*                  state_machine_running;
    std::thread*                        smThread;
    C_mathHelper*                       math;


    bool                                threadActive;
    bool                                robotReady;
    int                                 smBallTrackingStep;


    void initTCP                            ();
    void initRobot                          (std::string IPAdresse);
    bool moveRobotToTarget                  (C_AbsolutePose* targetPose);
    void sm_BallTracking                    ();
    bool close_Panda_threading              ();

    void start_smTracking                   ();

    C_AbsolutePose calibrateRobotBaseToWorld    (C_AbsolutePose& worldToCam,  C_RelativePose& BoardToTCP);


  private:
    static void open_Panda_threading        (void *This);
    static void threadHelper                (void* This);
    void boundingBoxToWorld                 ();


    /************************************************* GETTER SETTER *******************************************************************/
  public:
    void getAbsoluteHomogenousBaseToTCP     (posen::C_RelativePose* TcpPose);
    void getAbsoluteHomogenousBaseToWorld   (posen::C_AbsolutePose* BasePose);
    };
  }



#endif // C_ROBOTMANAGER_H
