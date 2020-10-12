#include "robot.h"

C_robot::C_robot()
  {
  this->robot = nullptr;
  this->robotstate = new franka::RobotState;
  }
C_robot::~C_robot()
  {
  delete (this->robotstate);
  if(this->robot != nullptr)
    {
    delete (robot);
    }
  else
    {
    this->robot = nullptr;
    }
  }

bool C_robot::createRobot(std::string ipAdress)
  {
  this->robot = new franka::Robot(ipAdress, franka::RealtimeConfig::kIgnore);
  return true;
  }
bool C_robot::startRobot()
  {

  }
bool C_robot::stopRobot()
  {

  }
bool C_robot::abortRobot()
  {

  }


