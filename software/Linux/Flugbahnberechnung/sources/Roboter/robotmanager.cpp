#include "headers/Roboter/robotmanager.h"

using namespace robotManager;

C_robotManager::C_robotManager(C_GlobalObjects* Globalobjects)
  {
  this->roboter = new robot::C_robot();
  this->globalObjects = Globalobjects;
  }
C_robotManager::~C_robotManager()
  {
  this->globalObjects = nullptr;
  delete (this->roboter);
  }
void C_robotManager::initRobots(std::string IPAdresse)
  {
  this->roboter->createRobot(IPAdresse);
  this->globalObjects->loadManager->loadRobotCos(*this->roboter);
  this->initTCP();

  }


void C_robotManager::initTCP()
  {
  double tcp_frame[4][4];
  this->globalObjects->loadManager->loadRobotTCP(tcp_frame);
  this->roboter->setTCP(tcp_frame);
  }
void C_robotManager::getAbsoluteHomogenousBaseToTCP(posen::C_RelativePose* TcpPose)
  {
  franka::RobotState* state;
  state = this->roboter->getRobotstate();
  TcpPose->nx(state->O_T_EE[0]);
  TcpPose->ny(state->O_T_EE[1]);
  TcpPose->nz(state->O_T_EE[2]);
  TcpPose->ox(state->O_T_EE[4]);
  TcpPose->oy(state->O_T_EE[5]);
  TcpPose->oz(state->O_T_EE[6]);
  TcpPose->ax(state->O_T_EE[8]);
  TcpPose->ay(state->O_T_EE[9]);
  TcpPose->az(state->O_T_EE[10]);
  TcpPose->px(state->O_T_EE[12]);
  TcpPose->py(state->O_T_EE[13]);
  TcpPose->pz(state->O_T_EE[14]);
  }

void getAbsoluteHomogenousBaseToWorld(posen::C_AbsolutePose* BasePose)
  {
  }


void C_robotManager::calibrateRobotToWorld(C_AbsolutePose& camToWorld)
  {
  C_RelativePose robotBaseToTCP;
  C_RelativePose TCPToRobotBase;
  C_AbsolutePose WorldToCam;
  C_AbsolutePose WorldToRobotBase;
  C_AbsolutePose WorldToBoard;

  //Pose_worldToRobot = Pose_WorldToCamera * Pose_CameraToBoard * Pose_RobotTcpToRobotBase


  WorldToCam.InversHomogenousPose       (camToWorld.HomogenePosenMatrix, WorldToCam.HomogenePosenMatrix);

  this->getAbsoluteHomogenousBaseToTCP  (&robotBaseToTCP);
  robotBaseToTCP.InversHomogenousPose   (robotBaseToTCP.HomogenePosenMatrix, TCPToRobotBase.HomogenePosenMatrix);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        {
        //this->relPose ist die Pose von Kamera1 zu Kamera 2 (M12)
        WorldToBoard.HomogenePosenMatrix[i][j] += WorldToCam.HomogenePosenMatrix[i][k] * globalObjects->camToBoard->HomogenePosenMatrix[k][j];
        }

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        {
        //this->relPose ist die Pose von Kamera1 zu Kamera 2 (M12)
        WorldToRobotBase.HomogenePosenMatrix[i][j] += WorldToBoard.HomogenePosenMatrix[i][k] * TCPToRobotBase.HomogenePosenMatrix[k][j];
        }


  }


