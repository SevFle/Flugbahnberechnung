#ifndef C_ROBOTMANAGER_H
#define C_ROBOTMANAGER_H
#include "posen.h"
#include "robot.h"
#include "headers/Etc/GlobalObjects.h"

using namespace GlobalObjects;

namespace robotManager
  {
  class C_robotManager
    {
  public:
    C_robotManager(C_GlobalObjects* globalObjects);
    ~C_robotManager();

    Robot_Panda::C_Robot_Panda *roboter;
    C_GlobalObjects* globalObjects;
    std::thread*                  robotThread;


    bool threadActive;
    void initTCP();
    void initRobot(std::string IPAdresse);

    void getAbsoluteHomogenousBaseToTCP(posen::C_RelativePose* TcpPose);
    void getAbsoluteHomogenousBaseToWorld(posen::C_AbsolutePose* BasePose);

    C_AbsolutePose calibrateRobotToWorld(C_AbsolutePose& worldToCam);

    bool moveRobotToTarget_Slow(C_AbsolutePose* targetPose);
    bool close_Panda_threading();

  private:
    static void open_Panda_threading(void *This);
    };
  }

#endif // C_ROBOTMANAGER_H
