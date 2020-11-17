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
  std::cout << "Roboter initialisiert. PID und Posen geladen" << std::endl;
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
void C_robotManager::getAbsoluteHomogenousBaseToTCP(posen::C_AbsolutePose* TcpPose)
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
  this->threadSelector = threadselector::singlePose;
  this->robotThread = new std::thread (&C_robotManager::open_Panda_threading, this);
  this->threadActive = true;
  return true;
  }
bool C_robotManager::close_Panda_threading()
  {
  if(threadSelector == singlePose)
    {
    this->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled = false;
    }
  else if(threadSelector == continousMovement)
    {
    this->roboter->signalMotionDone.store(true);
    }
  this->threadActive = false;
  this->robotThread->join();
  delete robotThread;

  return true;
  }

void C_robotManager::open_Panda_threading(void* This)
  {
  switch(static_cast<robotManager::C_robotManager*>(This)->threadSelector)
    {
    case singlePose:
      while(static_cast<robotManager::C_robotManager*>(This)->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled)
        {
        static_cast<robotManager::C_robotManager*>(This)->roboter->Panda_Processor_MoveToPose_Slow();
        }
      std::cout << "Movement done " << std::endl;
      break;
    case continousMovement:
      while(static_cast<robotManager::C_robotManager*>(This)->roboter->SM_Panda_Processor_Move_Robot_Slow_Enabled)
        {
        static_cast<robotManager::C_robotManager*>(This)->roboter->signalMotionDone.store(false);
        static_cast<robotManager::C_robotManager*>(This)->roboter->Panda_Processor_ContinousMovement();
        }
      break;
    }
  }

void C_robotManager::start_smTracking                   ()
  {
  this->state_machine_running->store(true);
  this->threadSelector = threadselector::continousMovement;
  this->smThread = new std::thread(&robotManager::C_robotManager::threadHelper,this);
  this->robotThread = new std::thread (&C_robotManager::open_Panda_threading, this);
  }

void C_robotManager::stop_smTracking                    ()
  {
  this->state_machine_running->store(false);
  this->roboter->signalMotionDone.store(true);
  this->roboter->signalPose.store(false);
  std::this_thread::sleep_for (std::chrono::milliseconds (500));

  this->threadSelector = threadselector::continousMovement;
  this->smThread->join();
  this->robotThread->join();
  }

void C_robotManager::threadHelper                (void* This)
  {
  static_cast<robotManager::C_robotManager*>(This)->sm_BallTracking();
  }

float C_robotManager::mix(float a, float b, float t)
  {
  // degree 1
  return a * (1.0f - t) + b*t;
  }
float C_robotManager::BezierQuadratic(float A, float B, float C, float t)
  {
  // degree 2
  float AB = mix(A, B, t);
  float BC = mix(B, C, t);
  return mix(AB, BC, t);
  }
float C_robotManager::BezierCubic(float A, float B, float C, float D, float t)
  {
  // degree 3
  float ABC = BezierQuadratic(A, B, C, t);
  float BCD = BezierQuadratic(B, C, D, t);
  return mix(ABC, BCD, t);
  }
float C_robotManager::BezierQuartic(float A, float B, float C, float D, float E, float t)
  {
  // degree 4
  float ABCD = BezierCubic(A, B, C, D, t);
  float BCDE = BezierCubic(B, C, D, E, t);
  return mix(ABCD, BCDE, t);
  }
float C_robotManager::BezierQuintic(float A, float B, float C, float D, float E, float F, float t)
  {
  // degree 5
  float ABCDE = BezierQuartic(A, B, C, D, E, t);
  float BCDEF = BezierQuartic(B, C, D, E, F, t);
  return mix(ABCDE, BCDEF, t);
  }
float C_robotManager::BezierSextic(float A, float B, float C, float D, float E, float F, float G, float t)
  {
  // degree 6
  float ABCDEF = BezierQuintic(A, B, C, D, E, F, t);
  float BCDEFG = BezierQuintic(B, C, D, E, F, G, t);
  return mix(ABCDEF, BCDEFG, t);
  }

C_AbsolutePose C_robotManager::computeBezier              (C_AbsolutePose start, C_AbsolutePose mid, C_AbsolutePose end, float t)
  {
  C_AbsolutePose bezierPose;

  bezierPose.px(this->BezierQuadratic(start.px(), mid.px(), end.px(), t));
  bezierPose.py(this->BezierQuadratic(start.py(), mid.py(), end.py(), t));
  bezierPose.pz(this->BezierQuadratic(start.pz(), mid.pz(), end.pz(), t));

  bezierPose.nx(this->BezierQuadratic(start.nx(), mid.nx(), end.nx(), t));
  bezierPose.ny(this->BezierQuadratic(start.ny(), mid.ny(), end.ny(), t));
  bezierPose.nz(this->BezierQuadratic(start.nz(), mid.nz(), end.nz(), t));

  bezierPose.ox(this->BezierQuadratic(start.ox(), mid.ox(), end.ox(), t));
  bezierPose.oy(this->BezierQuadratic(start.oy(), mid.oy(), end.oy(), t));
  bezierPose.oz(this->BezierQuadratic(start.oz(), mid.oz(), end.oz(), t));

  bezierPose.ax(this->BezierQuadratic(start.ax(), mid.ax(), end.ax(), t));
  bezierPose.ay(this->BezierQuadratic(start.ay(), mid.ay(), end.ay(), t));
  bezierPose.az(this->BezierQuadratic(start.az(), mid.az(), end.az(), t));

  }

C_AbsolutePose C_robotManager::computeBezier              (C_AbsolutePose start, C_AbsolutePose mid1, C_AbsolutePose mid2, C_AbsolutePose end, float t)
  {
  C_AbsolutePose bezierPose;

  bezierPose.px(this->BezierCubic(start.px(), mid1.px(), mid2.px(), end.px(), t));
  bezierPose.py(this->BezierCubic(start.py(), mid1.py(), mid2.py(), end.py(), t));
  bezierPose.pz(this->BezierCubic(start.pz(), mid1.pz(), mid2.pz(),end.pz(), t));

  bezierPose.nx(this->BezierCubic(start.nx(), mid1.nx(), mid2.nx(), end.nx(), t));
  bezierPose.ny(this->BezierCubic(start.ny(), mid1.ny(), mid2.ny(), end.ny(), t));
  bezierPose.nz(this->BezierCubic(start.nz(), mid1.nz(), mid2.nz(), end.nz(), t));

  bezierPose.ox(this->BezierCubic(start.ox(), mid1.ox(), mid2.ox(), end.ox(), t));
  bezierPose.oy(this->BezierCubic(start.oy(), mid1.oy(), mid2.oy(), end.oy(), t));
  bezierPose.oz(this->BezierCubic(start.oz(), mid1.oz(), mid2.oz(), end.oz(), t));

  bezierPose.ax(this->BezierCubic(start.ax(), mid1.ax(), mid2.ax(), end.ax(), t));
  bezierPose.ay(this->BezierCubic(start.ay(), mid1.ay(), mid2.ay(), end.ay(), t));
  bezierPose.az(this->BezierCubic(start.az(), mid1.az(), mid2.az(), end.az(), t));
  return bezierPose;
  }
float C_robotManager::computeBezierlength(std::vector<C_AbsolutePose>& vecOfBezierPoints)
  {
  float bezierlength = 0.0;
  for (auto it = std::begin(vecOfBezierPoints); it < std::end(vecOfBezierPoints); it++)
    {
    bezierlength += std::sqrt(std::pow(it++ - it, 2) + std::pow(it++ - it, 2));
    }
  return bezierlength;
  }


void C_robotManager::sm_BallTracking()
  {
  C_AbsolutePose tcpPose;
  C_AbsolutePose WorldToRobot = this->roboter->Abs_WorldToRobot_Pose;
  C_AbsolutePose RobotToWorld = this->roboter->Abs_RobotToWorld_Pose;
  C_AbsolutePose bezierMidPose;

  C_AbsolutePose RobotToObject;
  C_AbsolutePose estimateBall;

  S_Positionsvektor   TCPToTargetPose;
  C_AbsolutePose      waitForHitWorld;
  C_RelativePose      waitForHitWorld_inv;

  C_AbsolutePose waitForHitRobot;
  C_AbsolutePose waitForHitRobot_TCP;
  C_AbsolutePose temp;
  posen::S_Positionsvektor deltaHome, deltaIntermediate, deltaReady, deltaMin;

  GlobalObjects::robotConstraints ConstraintsInWorld;
 //########################################
 //maxVel 1.7 m/s
 //maxAcc 13.0 m/s²
 //maxJerk 6500.0 m/s³
 //########################################
  const double maxVel= 1.2;
  const double maxAcc = 9.0;
  const double maxJerk= 5000;

  double Panda_Vel_max   = 0;
  double Panda_Acc_max   = 0;
  double Panda_Omega_max = 0;
  double Panda_Alpha_max = 0;
  double verschleifen_grob = 0.1;
  double verschleifen_fein = 0.03;
  double Abs_tcp_pose = 0.0;
  int iterator = 0;

  const float bezier_iterations = 20;

  bool inRange = false;
  bool robotHitReady = false;
  bool robotInKugel = false;
  std::cout << "Robot preparing in World " << std::endl;
  while(*this->state_machine_running == true)
    {
    switch(this->smBallTrackingStep)
       {
      //Berechne Robot Bewegungsraum zu Weltkoordinaten
      case 0:
        //Transformiere die Roboter Boundingbox ins Weltkoordinatensystem

        ConstraintsInWorld.X  = this->roboter->Abs_RobotToWorld_Pose.px() + this->outerConstraints->X;
        ConstraintsInWorld.nX = this->roboter->Abs_RobotToWorld_Pose.px() - this->outerConstraints->nX;
        ConstraintsInWorld.Y  = this->roboter->Abs_RobotToWorld_Pose.py() + this->outerConstraints->Y;
        ConstraintsInWorld.nY = this->roboter->Abs_RobotToWorld_Pose.py() - this->outerConstraints->nY;
        ConstraintsInWorld.Z  = this->roboter->Abs_RobotToWorld_Pose.pz() + this->outerConstraints->Z;
        ConstraintsInWorld.nZ = this->roboter->Abs_RobotToWorld_Pose.pz() - this->outerConstraints->nZ;

        Panda_Vel_max   = abs(0.2);
        Panda_Acc_max   = abs(1);
        Panda_Omega_max = abs(0.2);
        Panda_Alpha_max = abs(1);
        this->roboter->Set_Panda_Vel_Acc_max(Panda_Vel_max, Panda_Acc_max, Panda_Omega_max, Panda_Alpha_max);



        //Berechne die Distanz zu den drei vorgespeicherten Posen und vergleiche die Distanz. Die kürzeste Strecke wird angefahren
        //
        this->smBallTrackingStep = 2;
      break;
    case 1:

    break;

      //Bezier Kurve mit Home und Intermediate als Zwischenpunkte
      case 2:
    for (int i = 0; i < bezier_iterations; ++i)
      {
      float t = ((float)i) / (float(bezier_iterations - 1));
      bezierMidPose = this->computeBezier(tcpPose, this->roboter->Abs_inter_waiting_Pose,  this->roboter->Abs_waiting_Pose, t);
      this->vec_AbsPosenBezier.push_back(bezierMidPose);
      }

      while(iterator <= bezier_iterations -1)
        {
        this->roboter->signalPose.store               (true);
        this->roboter->Set_Target_Pose                (this->vec_AbsPosenBezier.at(iterator));
        this->roboter->Get_Current_TCP_Pose_Motion    (tcpPose);

        TCPToTargetPose.X       = tcpPose.px() - this->vec_AbsPosenBezier.at(iterator).px();
        TCPToTargetPose.Y       = tcpPose.py() - this->vec_AbsPosenBezier.at(iterator).py();
        TCPToTargetPose.Z       = tcpPose.pz() - this->vec_AbsPosenBezier.at(iterator).pz();

        TCPToTargetPose.length  = sqrt                (std::pow(TCPToTargetPose.X,2) +
                                                       std::pow(TCPToTargetPose.Y,2) +
                                                       std::pow(TCPToTargetPose.Z,2));

        if (TCPToTargetPose.length < verschleifen_grob && iterator <= bezier_iterations -1 )
          {
          iterator++;
          }
        }
        this->vec_AbsPosenBezier.clear();
        this->smBallTrackingStep = 5;
          //nächster step
        break;


    case 5:
      this->roboter->Set_Target_Pose                (this->roboter->Abs_waiting_Pose);
      if(this->roboter->Pose_Reached(this->roboter->Panda_RobotState->O_T_EE,this->roboter->Abs_waiting_Pose,0.001 ,0.01))
      {
      this->roboter->signalPose.store(false);
      this->smBallTrackingStep = 6;
      }
      else
      {
      this->smBallTrackingStep = 5;
      }
      break;

    case 6:
      //Signal Robot Ready
      this->smBallTrackingStep = 7;
      break;
    case 7:
      if(this->globalObjects->objectPosenQue->try_pop(this->objectPayload))
        {
        this->smBallTrackingStep = 10;
        }
      else
        {
        this->smBallTrackingStep = 7;
        }
      break;
    case 8:
//      this->roboter->Get_Current_TCP_Pose_Motion(tcpPose);
//      //Fahre Roboter zur rechten Seite (-Y)bezogen auf sein KOS
//      if(this->objectPayload->predBall_in->Y > this->roboter->Abs_WorldToRobot_Pose.py())
//        {
//        }
//      //Fahre Roboter zur linken Seite (+Y) bezogen auf sein KOS
//      else if(this->objectPayload->predBall_in->Y < this->roboter->Abs_WorldToRobot_Pose.py())
//        {
//        tcpPose.py(0.3);
//        this->roboter->Set_Target_Pose(tcpPose);
//        }

//      this->roboter->signalPose.store(true);
    break;
    case 9:

    break;

      case 10:
      {
      C_AbsolutePose pose_BallIn, pose_BallOut, pose_ballMed;
      float length, execTime;

      this->roboter->Get_Current_TCP_Pose_Motion(tcpPose);
      //Berechne Kurve für die aktuell verfügbaren Balldaten
      for (int i = 0; i < bezier_iterations; ++i)
        {
        float t = ((float)i) / (float(bezier_iterations - 1));
        bezierMidPose = this->computeBezier(tcpPose, pose_BallOut, pose_ballMed,  pose_BallIn, t);
        this->vec_AbsPosenBezier.push_back(bezierMidPose);
        }
      //Berechne die Länge der Kurve [m]
      length    = this->computeBezierlength(this->vec_AbsPosenBezier);

      //Berechne die benötigte Zeit zur Ausführung der Bewegung
      execTime  = length/maxVel;

      }
    break;
    }//switch
    }//while
  }//void
