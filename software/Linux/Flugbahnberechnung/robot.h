#ifndef C_ROBOT_H
#define C_ROBOT_H

#include <franka/robot.h>
#include <franka/robot_state.h>


class C_robot
  {
public:
  C_robot();
  ~C_robot();

  franka::Robot* robot;
  franka::RobotState *robotstate;

  bool createRobot(std::string ipAdress);
  bool startRobot();
  bool stopRobot();
  bool abortRobot();

  };

#endif // C_ROBOT_H
