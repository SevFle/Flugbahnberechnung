#include "headers/Roboter/robotmanager.h"

using namespace robotManager;

C_robotManager::C_robotManager(C_GlobalObjects* Globalobjects)
  {
  this->roboter = nullptr;
  this->globalObjects = Globalobjects;
  this->robotThread = nullptr;
  this->threadActive = false;
  this->smBallTrackingStep = 0;
  this->objectPayload = nullptr;
  this->robotConstraints = new robotManager::robotConstraints;
  }
C_robotManager::~C_robotManager()
  {
  delete (robotConstraints);
  if(this->objectPayload != nullptr)
    delete (this->objectPayload);

  this->smBallTrackingStep = 0;
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

bool C_robotManager::moveRobotToTarget(C_AbsolutePose* targetPose)
  {
  if(threadActive)
    return false;
  this->roboter->Set_Target_Pose(*targetPose);
  this->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled = true;
  this->robotThread = new std::thread (&C_robotManager::open_Panda_threading, this);
  this->threadActive = true;
  return true;
  }
bool C_robotManager::close_Panda_threading()
  {
  this->robotThread->join();
  this->threadActive = false;
  this->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled = false;
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

void C_robotManager::sm_BallTracking()
  {
  C_AbsolutePose WorldToRobot = this->roboter->Abs_WorldToRobot_Pose;
  S_Posenvektor  WorldToObject;
  double distanceObjectToRobot_X = 0.0;
  double distanceObjectToRobot_Y = 0.0;
  double distanceObjectToRobot_Z = 0.0;
  double v0 = 0.0;
  double height = 0.0;
  double theta = 0.0;
  double timeOfFlight = 0.0;
  int aufloesung = 200;
  double timestep = 0.0;
  double distance = 0.0;
  while(true)
    {
    switch(this->smBallTrackingStep)
       {
      //Versuche aktuelle Objektdaten aus der Que zu holen. Falls nicht erfolgreich, bleibe im aktuellen Schritt
      case 1:
        if(this->globalObjects->objectPosenQue->try_pop(this->objectPayload))
          {
          this->smBallTrackingStep = 2;
          }
        else
          {
          this->smBallTrackingStep = 1;
          }
        break;

        //Berechne die aktuelle Trajektorie mit den gegebenen Objektdaten. Überprüfe ob in jedem Schritt dt ob sich X,Y,Z selbst mit Anlaufweg (15 cm in Bewegungsrichtung) innerhalb der Roboterkugel befinden
      case 2:
        distanceObjectToRobot_X = 0.0;
        distanceObjectToRobot_Y = 0.0;
        distanceObjectToRobot_Z = 0.0;

        WorldToObject.X         = this->objectPayload->predPosition->X;
        WorldToObject.Y         = this->objectPayload->predPosition->Y;
        WorldToObject.Z         = this->objectPayload->predPosition->Z;

        distanceObjectToRobot_X =  WorldToRobot.HomogenePosenMatrix[0][3] - WorldToObject.X;
        distanceObjectToRobot_Y =  WorldToRobot.HomogenePosenMatrix[1][3] - WorldToObject.Y;
        distanceObjectToRobot_Z =  WorldToRobot.HomogenePosenMatrix[2][3] - WorldToObject.Z;

        v0 = std::sqrt((this->objectPayload->predVelocity[0]*this->objectPayload->predVelocity[0]) + (this->objectPayload->predVelocity[1]*this->objectPayload->predVelocity[1])
                                                                                                  + (this->objectPayload->predVelocity[2]*this->objectPayload->predVelocity[2]));
        height = WorldToObject.Z;

        theta = std::tan(this->objectPayload->predVelocity[2]/this->objectPayload->predVelocity[0]);
        distance = ((v0*v0)* std::sin(2*theta))/9.807
        //Xt = Xt-1 + Vx*t
        //Yt = Yt-1 + Vx*t
        //Zt = Zt-1 + Vz*t - 0.5*g*t*t


        //Height z at distance x = initialheight + x*tan(launchangle) - (g*x²)/2*(v0*cos
        timeOfFlight = (2*v0*std::sin(theta))/9.807;
        timestep = timeOfFlight/aufloesung;

        for(int i =0; i <=timeOfFlight; i = i+ timestep)
          {
           double vx = this->objectPayload->predVelocity[0];
           double x = WorldToObject.X + vx*i;

           double vy = this->objectPayload->predVelocity[1];
           double y = WorldToObject.Y + vy*i;

           double vz = this->objectPayload->predVelocity[2] - 9.807*i;
           double z = WorldToObject.Z + this->objectPayload->predVelocity[2]*i - 0.5*9.807*i*i;
          }

        //vx = v0x
        //x = x0 + v0x*t

        //vy = v0y - g*t
        //y = y0+v0y*t-0.5*g*t*t



        break;
        //Bewege den Roboter zur kalkulierten Anlaufposition
      case 3:
        break;

      }
    }
  }
