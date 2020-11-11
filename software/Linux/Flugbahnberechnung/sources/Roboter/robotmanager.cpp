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
  this->outerConstraints    = new robotManager::robotConstraints;
  this->innerConstraints    = new robotManager::robotConstraints;
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
  C_AbsolutePose RobotToObject;

  S_Posenvektor  WorldToObject;

  C_AbsolutePose waitForHitWorld;
  C_RelativePose waitForHitWorld_inv;

  C_AbsolutePose waitForHitRobot;
  C_AbsolutePose waitForHitRobot_TCP;
  C_AbsolutePose temp;
  posen::S_Positionsvektor deltaHome, deltaIntermediate, deltaReady, deltaMin;

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

  double Panda_Vel_max   = 0;
  double Panda_Acc_max   = 0;
  double Panda_Omega_max = 0;
  double Panda_Alpha_max = 0;


  bool inRange = false;
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
//        if(this->globalObjects->objectPosenQue->try_pop(this->objectPayload))
//          {
//          //float gainMean = this->math->calcMedian(objectPayload->gain);
//          //if(gainMean < 0,2)
//            this->smBallTrackingStep = 10;
//          else
//            this->smBallTrackingStep = 9;
//          }
//        else
//          {
//          this->smBallTrackingStep = 9;
//          }
        break;

      case 10:
      //WHERE TO PROPAGATE THROUGH THE KF PREDICTIon?
    break;

        //Berechne die aktuelle Trajektorie mit den gegebenen Objektdaten. Überprüfe ob in jedem Schritt dt ob sich X,Y,Z selbst mit Anlaufweg (15 cm in Bewegungsrichtung) innerhalb der Roboterkugel befinden
      case 11:
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

          //Wenn die Objekttrajektorie die äußeren Begrenzung des Roboterkäfigs erreicht, setzte diesen Punkt als Entry
          if(x > ConstraintsInWorld.nX && x < outerConstraints->Y &&
             y > ConstraintsInWorld.nY && y < outerConstraints->Y &&
             z > ConstraintsInWorld.nZ && z < outerConstraints->Z && !inRange)
            {
            this->objectEntry->X = x;
            this->objectEntry->X = x;
            this->objectEntry->X = x;
            inRange = true;
            }
          //Wenn die Objekttrajektorie die äußeren Begrenzung des Roboterkäfigs verlässt, setzte diesen Punkt als exit.
          //Kalkuliere den Mittelpunkt der Geraden zwischen Entry(X,Y,Z) und Exit(X,Y,Z) und setze diesen als Wartepunkt für den Roboter
          else if  (x < ConstraintsInWorld.nX && x > outerConstraints->Y &&
                    y < ConstraintsInWorld.nY && y > outerConstraints->Y &&
                    z < ConstraintsInWorld.nZ && z > outerConstraints->Z && inRange)
            {
            this->objectExit->X = x;
            this->objectExit->X = x;
            this->objectExit->X = x;
            inRange = false;

            waitForHitWorld.px((this->objectEntry->X+this->objectExit->X)/2);
            waitForHitWorld.py((this->objectEntry->Y+this->objectExit->Y)/2);
            waitForHitWorld.pz((this->objectEntry->Z+this->objectExit->Z)/2);

            std::cout << "################## Robot preparing for hit ##############################" << ConstraintsInWorld.X << std::endl;
            std::cout << "Waiting at X: " << waitForHitWorld.px() << std::endl;
            std::cout << "Waiting at Y: " << waitForHitWorld.py() << std::endl;
            std::cout << "Waiting at Z: " << waitForHitWorld.pz() << std::endl;

            this->smBallTrackingStep = 12;
            }
           else
            {
            this->smBallTrackingStep = 11;
            }
          }
        //vx = v0x
        //x = x0 + v0x*t

        //vy = v0y
        //y = y0 + v0y*t

        //vz = v0z - g*t
        //z = z0+v0z*t-0.5*g*t*t
        break;
      case 12:
        //Transformiere die WartePosition von Welt- zu Robotkoordinatensystem

        waitForHitWorld.InversHomogenousPose(waitForHitWorld, waitForHitWorld_inv.HomogenePosenMatrix);
        //temp = waitForHitWorld_inv.operator*()


        //Überprüfe auf welcher Seite des Roboter das Objekt landen wird.
        //Wenn Objekt vor dem Robot ist (-0.40 < Y < 0.27)
        if(waitForHitRobot.py() > -0.40 && waitForHitRobot.py() < 0.27)
          {

          }

        //Wenn Ball zwischen der linken seite vom Robot ist (Y+)
        if(waitForHitRobot.py() >= 0.27)
          {

          }

        //Wenn Ball zwischen der rechten seite vom Robot ist (Y-)
        if(waitForHitRobot.py() <= -0.40)
          {

          }



        break;


































      }
    }
  }
