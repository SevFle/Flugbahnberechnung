#include "headers/Roboter/robotmanager.h"

using namespace robotManager;

C_robotManager::C_robotManager(C_GlobalObjects* Globalobjects)
  {
  this->roboter             = nullptr;
  this->globalObjects       = Globalobjects;
  this->robotThread         = nullptr;
  this->threadActive        = false;
  this->smBallTrackingStep  = 0;
  this->objectPayload       = nullptr;
  this->robotConstraints    = new robotManager::robotConstraints;
  this->objectEntry         = new posen::S_Positionsvektor;
  this->objectExit          = new posen::S_Positionsvektor;
  this->state_machine_running = new std::atomic<bool>(false);
  this->smThread            = nullptr;
  }
C_robotManager::~C_robotManager()
  {
  this->smThread            = nullptr;
  delete                    (state_machine_running);
  delete                    (objectExit);
  delete                    (objectEntry);
  delete                    (robotConstraints);
  if(this->objectPayload != nullptr)
    delete                  (this->objectPayload);

  this->smBallTrackingStep  = 0;
  this->threadActive        = false;
  this->robotThread         = nullptr;
  this->globalObjects       = nullptr;
  if(this->roboter != nullptr)
    delete                  (this->roboter);
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

void C_robotManager::start_smTracking                   ()
  {
  this->state_machine_running->store(true);
  this->smThread = new std::thread(&robotManager::C_robotManager::threadHelper,this);
  }
void C_robotManager::threadHelper                (void* This)
  {
  static_cast<robotManager::C_robotManager*>(This)->sm_BallTracking();
  }


void C_robotManager::sm_BallTracking()
  {
  C_AbsolutePose WorldToRobot = this->roboter->Abs_WorldToRobot_Pose;
  S_Posenvektor  WorldToObject;

  S_Posenvektor  waitForHit;

  robotManager::robotConstraints ConstraintsInWorld;

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

  bool inRange = false;
  std::cout << "Robot preparing in World " << std::endl;
  while(*this->state_machine_running == true)
    {
    switch(this->smBallTrackingStep)
       {
      //Berechne Robot Bewegungsraum zu Weltkoordinaten
      case 1:
        ConstraintsInWorld.X  = this->roboter->Abs_WorldToRobot_Pose.px() + this->robotConstraints->X;
        ConstraintsInWorld.nX = this->roboter->Abs_WorldToRobot_Pose.px() - this->robotConstraints->nX;
        ConstraintsInWorld.Y  = this->roboter->Abs_WorldToRobot_Pose.py() + this->robotConstraints->Y;
        ConstraintsInWorld.nY = this->roboter->Abs_WorldToRobot_Pose.py() - this->robotConstraints->nY;
        ConstraintsInWorld.Z  = this->roboter->Abs_WorldToRobot_Pose.pz() + this->robotConstraints->Z;
        ConstraintsInWorld.nZ = this->roboter->Abs_WorldToRobot_Pose.pz() - this->robotConstraints->nZ;

        std::cout << "Robot Constraints in World X: " << ConstraintsInWorld.X << std::endl;
        std::cout << "Robot Constraints in World nX: " << ConstraintsInWorld.nX << std::endl;
        std::cout << "Robot Constraints in World Y: " << ConstraintsInWorld.Y << std::endl;
        std::cout << "Robot Constraints in World nY: " << ConstraintsInWorld.nY << std::endl;
        std::cout << "Robot Constraints in World Z: " << ConstraintsInWorld.Z << std::endl;
        std::cout << "Robot Constraints in World nZ: " << ConstraintsInWorld.nZ << std::endl;


        break;
      //Versuche aktuelle Objektdaten aus der Que zu holen. Falls nicht erfolgreich, bleibe im aktuellen Schritt
      case 2:
        if(this->globalObjects->objectPosenQue->try_pop(this->objectPayload))
          {
          this->smBallTrackingStep = 3;
          }
        else
          {
          this->smBallTrackingStep = 2;
          }
        break;

        //Berechne die aktuelle Trajektorie mit den gegebenen Objektdaten. ‹berpr¸fe ob in jedem Schritt dt ob sich X,Y,Z selbst mit Anlaufweg (15 cm in Bewegungsrichtung) innerhalb der Roboterkugel befinden
      case 3:
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
        distance = ((v0*v0)* std::sin(2*theta))/9.807;
        //Xt = Xt-1 + Vx*t
        //Yt = Yt-1 + Vx*t
        //Zt = Zt-1 + Vz*t - 0.5*g*t*t


        //Height z at distance x = initialheight + x*tan(launchangle) - (g*x≤)/2*(v0*cos
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

          //Wenn die Objekttrajektorie die ‰uﬂeren Begrenzung des Roboterk‰figs erreicht, setzte diesen Punkt als Entry
          if(x > ConstraintsInWorld.nX && x < robotConstraints->Y &&
             y > ConstraintsInWorld.nY && y < robotConstraints->Y &&
             z > ConstraintsInWorld.nZ && z < robotConstraints->Z && !inRange)
            {
            this->objectEntry->X = x;
            this->objectEntry->X = x;
            this->objectEntry->X = x;
            inRange = true;
            }
          //Wenn die Objekttrajektorie die ‰uﬂeren Begrenzung des Roboterk‰figs verl‰sst, setzte diesen Punkt als exit. Kalkuliere den Mittelpunkt der Geraden zwischen Entry(X,Y,Z) und Exit(X,Y,Z)
          else if  (x < ConstraintsInWorld.nX && x > robotConstraints->Y &&
                    y < ConstraintsInWorld.nY && y > robotConstraints->Y &&
                    z < ConstraintsInWorld.nZ && z > robotConstraints->Z && inRange)
            {
            this->objectExit->X = x;
            this->objectExit->X = x;
            this->objectExit->X = x;
            inRange = false;

            waitForHit.X = (this->objectEntry->X+this->objectExit->X)/2;
            waitForHit.Y = (this->objectEntry->Y+this->objectExit->Y)/2;
            waitForHit.Z = (this->objectEntry->Z+this->objectExit->Z)/2;
            std::cout << "################## Robot preparing for hit ##############################" << ConstraintsInWorld.X << std::endl;
            std::cout << "Waiting at X: " << waitForHit.X << std::endl;
            std::cout << "Waiting at Y: " << waitForHit.Y << std::endl;
            std::cout << "Waiting at Z: " << waitForHit.Z << std::endl;

            this->smBallTrackingStep = 3;
            }
           else
            {
            this->smBallTrackingStep = 2;
            }
          }




        //vx = v0x
        //x = x0 + v0x*t

        //vy = v0y
        //y = y0 + v0y*t

        //vz = v0z - g*t
        //z = z0+v0z*t-0.5*g*t*t



        break;
        //Bewege den Roboter zur kalkulierten Anlaufposition
      case 4:

        break;

      }
    }
  }
