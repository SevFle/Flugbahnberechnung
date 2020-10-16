#include "headers/Roboter/robotmanager.h"

using namespace robotManager;

C_robotManager::C_robotManager(C_GlobalObjects* Globalobjects)
  {
  this->roboter = nullptr;
  this->globalObjects = Globalobjects;
  this->robotThread = nullptr;
  this->threadActive = false;
  }
C_robotManager::~C_robotManager()
  {
  this->threadActive = false;
  this->robotThread = nullptr;
  this->globalObjects = nullptr;
  if(this->roboter != nullptr)
    delete (this->roboter);
  }

void C_robotManager::initTCP()
  {
  double tcp_frame[4][4];
  this->globalObjects->loadManager->loadRobotTCP(tcp_frame);
  this->roboter->Set_TCP_Frame(tcp_frame);
  }
void C_robotManager::initRobot(std::string IPAdresse)
  {
  int n = IPAdresse.length();
  char char_array[n + 1];
  strcpy(char_array, IPAdresse.c_str());
  this->roboter = new Robot_Panda::C_Robot_Panda(char_array, false);
  C_AbsolutePose HomePose;
  this->globalObjects->loadManager->loadRobotHomePose(&HomePose);
  this->globalObjects->loadManager->loadPID(*this->roboter);
  this->roboter->Abs_Home_Pose = HomePose;
  }

void C_robotManager::getAbsoluteHomogenousBaseToTCP(posen::C_RelativePose* TcpPose)
  {
  C_AbsolutePose actTcpPose;
  this->roboter->Get_Current_TCP_Pose(actTcpPose);
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      TcpPose->HomogenePosenMatrix[i][j] = actTcpPose.HomogenePosenMatrix[i][j];
  }

void C_robotManager::getAbsoluteHomogenousBaseToWorld(posen::C_AbsolutePose* BasePose)
  {
  *BasePose = this->roboter->Abs_RobotToWorld_Pose;
  }


C_AbsolutePose C_robotManager::calibrateRobotToWorld(C_AbsolutePose& worldToCam)
  {
  C_RelativePose robotBaseToTCP;
  C_RelativePose TCPToRobotBase;
  C_AbsolutePose WorldToRobotBase;
  C_AbsolutePose WorldToBoard;


  this->getAbsoluteHomogenousBaseToTCP  (&robotBaseToTCP);
  robotBaseToTCP.InversHomogenousPose   (robotBaseToTCP.HomogenePosenMatrix, TCPToRobotBase.HomogenePosenMatrix);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        {
        //this->relPose ist die Pose von Kamera1 zu Kamera 2 (M12)
        WorldToBoard.HomogenePosenMatrix[i][j] += worldToCam.HomogenePosenMatrix[i][k] * globalObjects->camToBoard->HomogenePosenMatrix[k][j];
        }

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        {
        //this->relPose ist die Pose von Kamera1 zu Kamera 2 (M12)
        WorldToRobotBase.HomogenePosenMatrix[i][j] += WorldToBoard.HomogenePosenMatrix[i][k] * TCPToRobotBase.HomogenePosenMatrix[k][j];
        }
  return WorldToRobotBase;

  }


bool C_robotManager::moveRobotToTarget_Slow(C_AbsolutePose* targetPose)
  {
  if(threadActive)
    return false;
  this->roboter->Set_Target_Pose(*targetPose);
  this->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled = true;
  this->robotThread = new std::thread (&C_robotManager::open_Panda_threading, this);
  this->threadActive = true;
  return true;
  }

void C_robotManager::open_Panda_threading(void* This)
  {
  while(static_cast<robotManager::C_robotManager*>(This)->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled)
    {
    static_cast<robotManager::C_robotManager*>(This)->roboter->Panda_Processor_MoveToPose_Slow();
    }
  std::cout << "Movement done " << std::endl;
  }
