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
  this->outerConstraints    = new GlobalObjects::robotConstraints;
  this->innerConstraints    = new GlobalObjects::robotConstraints;
  this->objectEntry         = new posen::S_Positionsvektor;
  this->objectExit          = new posen::S_Positionsvektor;
  this->state_machine_running = new std::atomic<bool>(false);
  this->smThread            = nullptr;
  this->Pose_waiting        = new posen::C_AbsolutePose;
  this->Pose_inter_waiting  = new posen::C_AbsolutePose;
  this->math                = new C_mathHelper;

  }
C_robotManager::~C_robotManager()
  {
  delete                    (math);
  delete                    (Pose_inter_waiting);
  delete                    (Pose_waiting);

  this->smThread            = nullptr;
  delete                    (state_machine_running);
  delete                    (objectExit);
  delete                    (objectEntry);
  delete                    (innerConstraints);
  delete                    (outerConstraints);
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
  this->globalObjects->loadManager->loadRobotHomePose(&this->roboter->Abs_Home_Pose);
  this->globalObjects->loadManager->loadRobotInterWaitingPose(&this->roboter->Abs_inter_waiting_Pose);
  this->globalObjects->loadManager->loadRobotReadyPose(&this->roboter->Abs_waiting_Pose);

  this->globalObjects->loadManager->loadPID(*this->roboter);

  this->outerConstraints->X   =   0.75f;
  this->outerConstraints->nX  =  -0.30f;
  this->outerConstraints->Y   =   0.60f;
  this->outerConstraints->nY  =  -0.60f;
  this->outerConstraints->Z   =   0.80f;
  this->outerConstraints->nZ  =  -0.13f;

  this->innerConstraints->X = 0.0;

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

C_AbsolutePose C_robotManager::calibrateRobotBaseToWorld(C_AbsolutePose& worldToCam, C_RelativePose& BoardToTCP)
  {
    C_RelativePose robotBaseToTCP;
    C_RelativePose TCPToRobotBase;
    C_AbsolutePose WorldToRobotBase;
    C_AbsolutePose WorldToBoard;
    C_AbsolutePose WorldToTCP;

    robotBaseToTCP.clear();
    TCPToRobotBase.clear();
    WorldToRobotBase.clear();
    WorldToBoard.clear();
    WorldToTCP.clear();



    this->getAbsoluteHomogenousBaseToTCP  (&robotBaseToTCP);
    robotBaseToTCP.InversHomogenousPose   (robotBaseToTCP.HomogenePosenMatrix, TCPToRobotBase.HomogenePosenMatrix);

    //Berechne die Absolute Pose des Boards im Weltkoordinatensystem
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
          {
          WorldToBoard.HomogenePosenMatrix[i][j] += worldToCam.HomogenePosenMatrix[i][k] * globalObjects->camToBoard->HomogenePosenMatrix[k][j];
          }
    //Rotiere die Pose des Boards in die Pose des TCP
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
          {
          WorldToTCP.HomogenePosenMatrix[i][j] += WorldToBoard.HomogenePosenMatrix[i][k] * BoardToTCP.HomogenePosenMatrix[k][j];
          }

    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
          {
          //this->relPose ist die Pose von Kamera1 zu Kamera 2 (M12)
          WorldToRobotBase.HomogenePosenMatrix[i][j] += WorldToTCP.HomogenePosenMatrix[i][k] * TCPToRobotBase.HomogenePosenMatrix[k][j];
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
  delete robotThread;
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
  C_RelativePose tcpPose;
  C_AbsolutePose WorldToRobot = this->roboter->Abs_WorldToRobot_Pose;
  C_AbsolutePose RobotToWorld = this->roboter->Abs_RobotToWorld_Pose;

  C_AbsolutePose RobotToObject;
  C_AbsolutePose estimateBall;

  S_Posenvektor  WorldToObject;

  C_AbsolutePose waitForHitWorld;
  C_RelativePose waitForHitWorld_inv;

  C_AbsolutePose waitForHitRobot;
  C_AbsolutePose waitForHitRobot_TCP;
  C_AbsolutePose temp;
  posen::S_Positionsvektor deltaHome, deltaIntermediate, deltaReady, deltaMin;

  GlobalObjects::robotConstraints ConstraintsInWorld;

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

  double Panda_Vel_max   = 0;
  double Panda_Acc_max   = 0;
  double Panda_Omega_max = 0;
  double Panda_Alpha_max = 0;


  bool inRange = false;
  bool robotHitReady = false;
  std::cout << "Robot preparing in World " << std::endl;
  while(*this->state_machine_running == true)
    {
    switch(this->smBallTrackingStep)
       {
      //Berechne Robot Bewegungsraum zu Weltkoordinaten
      case 0:
        //Transformiere die Roboter Boundingbox ins Weltkoordinatensystem
        ConstraintsInWorld.X  = this->roboter->Abs_WorldToRobot_Pose.px() + this->outerConstraints->X;
        ConstraintsInWorld.nX = this->roboter->Abs_WorldToRobot_Pose.px() - this->outerConstraints->nX;
        ConstraintsInWorld.Y  = this->roboter->Abs_WorldToRobot_Pose.py() + this->outerConstraints->Y;
        ConstraintsInWorld.nY = this->roboter->Abs_WorldToRobot_Pose.py() - this->outerConstraints->nY;
        ConstraintsInWorld.Z  = this->roboter->Abs_WorldToRobot_Pose.pz() + this->outerConstraints->Z;
        ConstraintsInWorld.nZ = this->roboter->Abs_WorldToRobot_Pose.pz() - this->outerConstraints->nZ;

        std::cout << "Robot Constraints in World X: " << ConstraintsInWorld.X << std::endl;
        std::cout << "Robot Constraints in World nX: " << ConstraintsInWorld.nX << std::endl;
        std::cout << "Robot Constraints in World Y: " << ConstraintsInWorld.Y << std::endl;
        std::cout << "Robot Constraints in World nY: " << ConstraintsInWorld.nY << std::endl;
        std::cout << "Robot Constraints in World Z: " << ConstraintsInWorld.Z << std::endl;
        std::cout << "Robot Constraints in World nZ: " << ConstraintsInWorld.nZ << std::endl;


        Panda_Vel_max   = abs(1.7);
        Panda_Acc_max   = abs(4);
        Panda_Omega_max = abs(1.7);
        Panda_Alpha_max = abs(4);
        this->roboter->Set_Panda_Vel_Acc_max(Panda_Vel_max, Panda_Acc_max, Panda_Omega_max, Panda_Alpha_max);



        //Berechne die Distanz zu den drei vorgespeicherten Posen und vergleiche die Distanz. Die kürzeste Strecke wird angefahren
        //
        this->getAbsoluteHomogenousBaseToTCP(&tcpPose);
        deltaHome.X = tcpPose.px() - this->roboter->Abs_Home_Pose.px();
        deltaHome.Y = tcpPose.py() - this->roboter->Abs_Home_Pose.py();
        deltaHome.Z = tcpPose.pz() - this->roboter->Abs_Home_Pose.pz();
        deltaHome.length = std::sqrt((deltaHome.X*deltaHome.X) + (deltaHome.Y*deltaHome.Y) + (deltaHome.Z*deltaHome.Z));

        deltaIntermediate.X = tcpPose.px() - this->roboter->Abs_inter_waiting_Pose.px();
        deltaIntermediate.Y = tcpPose.py() - this->roboter->Abs_inter_waiting_Pose.py();
        deltaIntermediate.Z = tcpPose.pz() - this->roboter->Abs_inter_waiting_Pose.pz();
        deltaIntermediate.length = std::sqrt((deltaIntermediate.X*deltaIntermediate.X) + (deltaIntermediate.Y*deltaIntermediate.Y) + (deltaIntermediate.Z*deltaIntermediate.Z));

        deltaReady.X = tcpPose.px() - this->roboter->Abs_waiting_Pose.px();
        deltaReady.Y = tcpPose.py() - this->roboter->Abs_waiting_Pose.py();
        deltaReady.Z = tcpPose.pz() - this->roboter->Abs_waiting_Pose.pz();
        deltaReady.length = std::sqrt((deltaReady.X*deltaReady.X) + (deltaReady.Y*deltaReady.Y) + (deltaReady.Z*deltaReady.Z));

        deltaMin.length = std::min({deltaHome.length, deltaIntermediate.length, deltaReady.length});

        if(deltaMin.length == deltaHome.length)
          {
          this->smBallTrackingStep = 2;
          break;
          }
        else if(deltaMin.length == deltaIntermediate.length)
          {
          this->smBallTrackingStep = 4;
          break;
          }
        else if(deltaMin.length == deltaReady.length)
          {
          this->smBallTrackingStep = 7;
          break;
          }
        else
          {
          std::cout << "No vaild Pose found, Moving to Home" << std::endl;
          }


        this->smBallTrackingStep = 2;
      break;

        //Fahre Roboter zur HomePosition
      case 2:
        this->moveRobotToTarget(&this->roboter->Abs_Home_Pose);
        this->smBallTrackingStep = 3;
        break;
      case 3:
        if(this->roboter->Is_MotionDone())
          {
          this->close_Panda_threading();
          this->smBallTrackingStep = 4;
          }
        else
          {
          this->smBallTrackingStep = 3;
          }
        break;
    case 4:
      this->moveRobotToTarget(&this->roboter->Abs_inter_waiting_Pose);
      this->smBallTrackingStep = 5;
      break;
    case 5:
      if(this->roboter->Is_MotionDone())
        {
        this->close_Panda_threading();
        this->smBallTrackingStep = 6;
        }
      else
        {
        this->smBallTrackingStep = 5;
        }
      break;
    case 6:
      this->moveRobotToTarget(&this->roboter->Abs_waiting_Pose);
      this->smBallTrackingStep = 7;
      break;
    case 7:
      if(this->roboter->Is_MotionDone())
        {
        this->close_Panda_threading();
        this->smBallTrackingStep = 8;
        }
      else
        {
        this->smBallTrackingStep = 7;
        }
      break;
    case 8:
        //Signal Robot Ready
        break;

      //Versuche aktuelle Objektdaten aus der Que zu holen. Falls nicht erfolgreich, bleibe im aktuellen Schritt
      case 9:
        if(this->globalObjects->objectPosenQue->try_pop(this->objectPayload))
          {
          this->smBallTrackingStep = 10;
          }
        else
          {
          this->smBallTrackingStep = 9;
          }
        break;

      case 10:
          {
          //Transformiere die erwartete Pose zurück in RobotPose und fahre sie an wenn sie im Arbeitsraum (CONSTRAINT) liegt.
//          estimateBall.px(this->objectPayload->predPosition->X);
//          estimateBall.py(this->objectPayload->predPosition->Y);
//          estimateBall.py(this->objectPayload->predPosition->Z);

//          waitForHitRobot_TCP = RobotToWorld.operator *(estimateBall);
//          robotHitReady = true;
//          if(this->objectPayload->timeOnTarget_mid <= 1.0)
//            {
//            this->smBallTrackingStep = 12;
//            }
//          else
//           {

//           }
          }
    break;
      case 11:

        break;
      case 12:
      //FAHRE DEM BALL ENTGEGEN,

        break;


































      }
    }
  }
