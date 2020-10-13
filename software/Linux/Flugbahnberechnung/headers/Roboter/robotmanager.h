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

    robot::C_robot *roboter;
    C_GlobalObjects* globalObjects;

    void initRobots(std::string IPAdresse);

    void initTCP();

    void getAbsoluteHomogenousBaseToTCP(posen::C_RelativePose* TcpPose);
    void getAbsoluteHomogenousBaseToWorld(posen::C_AbsolutePose* BasePose);

    void calibrateRobotToWorld(C_AbsolutePose& camToWorld);


    };
  }

#endif // C_ROBOTMANAGER_H
