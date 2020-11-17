#include "headers/Forms/frm_robot_calibration.h"

using namespace frm_Robot_Calibration;

C_frm_Robot_Calibration::C_frm_Robot_Calibration(C_GlobalObjects* GlobalObjects, Main::C_Main* Main, QWidget *parent) :
  QMainWindow(parent)
  {
  this->ui = new Ui::C_frm_robot_calibration();
  ui->setupUi(this);
  this->GlobalObjects = GlobalObjects;
  this->Main = Main;
  this->Taktgeber = new QTimer;
  this->robotTcpPose = new C_RelativePose;
  this->pose_WorldToRobotBase = new C_AbsolutePose;
  this->pose_CamToBoard = new C_AbsolutePose;
  this->pData = nullptr;

  this->Taktgeber_Intervall = 0;
  this->Zaehler = 0;
  this->cameraID = 0;
  this->moving = false;
  this->MsgBox = new QMessageBox;

  }

C_frm_Robot_Calibration::~C_frm_Robot_Calibration()
  {
  delete (this->MsgBox);

  this->moving = false;

  this->cameraID = 0;
  this->Zaehler = 0;
  this->Taktgeber_Intervall = 0;
  if(this->pData != nullptr)
    {
      delete (this->pData);
    }
  else
    {
    this->pData = nullptr;
    }
  delete (pose_CamToBoard);
  delete (pose_WorldToRobotBase);
  delete (robotTcpPose);
  delete (Taktgeber);
  this->Main = nullptr;
  this->GlobalObjects = nullptr;




  delete ui;
  }


void C_frm_Robot_Calibration::showEvent(QShowEvent* ShowEvent)
{
this->Zaehler                           = 0;
this->Taktgeber_Intervall               = 25;
this->cameraID = 0;
connect                                 (this->Taktgeber, &QTimer::timeout, this, &C_frm_Robot_Calibration::Taktgeber_Tick);
this->Taktgeber->start                  (this->Taktgeber_Intervall);
this->installEventFilter                (this);
this->on_rb_no_tool_clicked();
this->initUi();
Q_UNUSED(ShowEvent)
}

void C_frm_Robot_Calibration::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED                   (CloseEvent);
 this->removeEventFilter    (this);
 this->Taktgeber->stop      ();
 disconnect                 (this->Taktgeber, &QTimer::timeout, this, &C_frm_Robot_Calibration::Taktgeber_Tick);
 this->Zaehler              = 0;
 this->cameraID             = 0;
 this->ui->num_camID->setMaximum     (GlobalObjects->absCameras-1);


 }

bool               C_frm_Robot_Calibration::eventFilter                                       (QObject* Object, QEvent* Event)
  {
  if (Object == this)
    {
    switch (Event->type())
      {
      default:
        {
        return false;
        }
      break;
      case QEvent::WindowBlocked:
        {
        this->Taktgeber->stop();
        return true;
        }
      break;
      case QEvent::WindowUnblocked:
        {
        this->Taktgeber->start(this->Taktgeber_Intervall);
        return true;
        }
      break;
      }
    }
  else
    {
    return false;
    }
  }
/************************************** Nicht Ã¶ffentliche QT-Slots******************************/

void C_frm_Robot_Calibration::Taktgeber_Tick()
  {
  this->ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  this->Main->cameraManager->setRoiStatus(roiStatus::objectLost);

  if(this->Main->cameraManager->pipelineQue->try_pop(this->pData))
    {
    if(this->Main->cameraManager->scanChAruco(pData->cpuUndistortedImg[0], *Main->cameraManager->vecCameras->at(this->ui->num_camID->value()), *this->pose_CamToBoard))
      {
      this->writeCamPose();
      this->writeRobotBaseToWorldPose();
      }
    else
      {
      this->pose_CamToBoard->clear();
      writeCamPose();
      }
    this->Main->frm_Main->FillMat2Lbl(pData->cpuUndistortedImg[0], this->ui->lbl_camera_img);
    this->writeRobotTcpPose();

    delete(pData);
    pData = nullptr;
    }//if  if(this->Main->cameraManager->pipelineQue->try_pop(this->pData))
  else
    {
    pData = nullptr;
    this->pose_CamToBoard->clear();
    writeCamPose();
    writeRobotTcpPose();
    }
  if(this->Main->robotManager->roboter->Is_MotionDone())
    {
    this->enableUi();
    this->moving = false;
    this->Main->robotManager->close_Panda_threading();
    }
  }//void C_frm_Robot_Calibration::Taktgeber_Tick()
void C_frm_Robot_Calibration::disableUi()
  {
  this->ui->grp_tcp_tool->setEnabled                  (false);
  this->ui->grpb_PID->setEnabled                      (false);
  this->ui->grpb_constraints->setEnabled              (false);
  this->ui->grpb_move_horizontal->setEnabled          (false);
  this->ui->grpb_posen->setEnabled                    (false);
  this->ui->grpb_rotation_board_to_world->setEnabled  (false);
  }
void C_frm_Robot_Calibration::enableUi()
  {
    this->ui->grp_tcp_tool->setEnabled                (true);
    this->ui->grpb_PID->setEnabled                    (true);
    this->ui->grpb_constraints->setEnabled            (true);
    this->ui->grpb_move_horizontal->setEnabled        (true);
    this->ui->grpb_posen->setEnabled                  (true);
    this->ui->grpb_rotation_board_to_world->setEnabled(true);
  }
void C_frm_Robot_Calibration::initUi()
  {
  this->ui->txb_constraint_x->setText     (QString::number(this->Main->robotManager->outerConstraints->X));
  this->ui->txb_constraint_nx->setText    (QString::number(this->Main->robotManager->outerConstraints->nX));
  this->ui->txb_constraint_y->setText     (QString::number(this->Main->robotManager->outerConstraints->Y));
  this->ui->txb_constraint_ny->setText    (QString::number(this->Main->robotManager->outerConstraints->nY));
  this->ui->txb_constraint_z->setText     (QString::number(this->Main->robotManager->outerConstraints->Z));
  this->ui->txb_constraint_nz->setText    (QString::number(this->Main->robotManager->outerConstraints->nZ));

    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_Home_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

    this->writeWorldToCamPose();
    this->on_rb_home_Pose_clicked();
  }

void C_frm_Robot_Calibration::writeCamPose()
  {
  this->ui->txb_nx_cam->setText(QString::number(this->pose_CamToBoard->nx()));
  this->ui->txb_ny_cam->setText(QString::number(this->pose_CamToBoard->ny()));
  this->ui->txb_nz_cam->setText(QString::number(this->pose_CamToBoard->nz()));

  this->ui->txb_ox_cam->setText(QString::number(this->pose_CamToBoard->ox()));
  this->ui->txb_oy_cam->setText(QString::number(this->pose_CamToBoard->oy()));
  this->ui->txb_oz_cam->setText(QString::number(this->pose_CamToBoard->oz()));

  this->ui->txb_ax_cam->setText(QString::number(this->pose_CamToBoard->ax()));
  this->ui->txb_ay_cam->setText(QString::number(this->pose_CamToBoard->ay()));
  this->ui->txb_az_cam->setText(QString::number(this->pose_CamToBoard->az()));

  this->ui->txb_px_cam->setText(QString::number(this->pose_CamToBoard->px()));
  this->ui->txb_py_cam->setText(QString::number(this->pose_CamToBoard->py()));
  this->ui->txb_pz_cam->setText(QString::number(this->pose_CamToBoard->pz()));

  }
void C_frm_Robot_Calibration::writeRobotTcpPose()
  {
  if(!this->moving)
    {
    this->Main->robotManager->getAbsoluteHomogenousBaseToTCP(this->robotTcpPose);
    this->ui->txb_nx_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[1][2]));
    this->ui->txb_az_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[2][2]));

    this->ui->txb_px_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[0][3]));
    this->ui->txb_py_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_robot->setText(QString::number(this->robotTcpPose->HomogenePosenMatrix[2][3]));
    }
  }
void C_frm_Robot_Calibration::writeWorldToBoardPose(C_AbsolutePose& WorldToBoard)
  {
    this->ui->txb_nx_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_worldToBoard->setText(QString::number(WorldToBoard.HomogenePosenMatrix[2][3]));
  }
void C_frm_Robot_Calibration::writeRobotBaseToWorldPose()
  {
  if(!this->moving)
    {
    C_AbsolutePose RobotToWorld = this->getPoseRobotBaseToWorld();
    this->ui->txb_nx_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][3]));
    }
  }
void C_frm_Robot_Calibration::writeWorldToCamPose()
  {
  C_AbsolutePose WorldToCam = *this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->WorldToCamera;

  this->ui->txb_nx_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[0][0]));
  this->ui->txb_ny_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[1][0]));
  this->ui->txb_nz_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[2][0]));

  this->ui->txb_ox_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[0][1]));
  this->ui->txb_oy_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[1][1]));
  this->ui->txb_oz_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[2][1]));

  this->ui->txb_ax_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[0][2]));
  this->ui->txb_ay_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[1][2]));
  this->ui->txb_az_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[2][2]));

  this->ui->txb_px_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[0][3]));
  this->ui->txb_py_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[1][3]));
  this->ui->txb_pz_worldToCam->setText(QString::number(WorldToCam.HomogenePosenMatrix[2][3]));
  }

C_AbsolutePose C_frm_Robot_Calibration::getPoseRobotBaseToWorld()
  {
  C_RelativePose camToBoard;
  C_RelativePose BoardToTCP;
  C_AbsolutePose WorldToBoard;

  camToBoard.clear();
  WorldToBoard.clear();
  BoardToTCP.clear();

  BoardToTCP.nx(this->ui->num_nx_boardToTCP->value());
  BoardToTCP.oy(this->ui->num_oy_boardToTCP->value());
  BoardToTCP.az(this->ui->num_az_boardToTCP->value());


  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->pose_CamToBoard->HomogenePosenMatrix[i][j];
      }

  //Berechne die Absolute Pose des Boards im Weltkoordinatensystem
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++)
        {
        WorldToBoard.HomogenePosenMatrix[i][j] += this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->WorldToCamera->HomogenePosenMatrix[i][k] *
                                                  camToBoard.HomogenePosenMatrix[k][j];
        }
  this->writeWorldToBoardPose(WorldToBoard);
  *this->GlobalObjects->camToBoard = camToBoard;
  *this->pose_WorldToRobotBase = this->Main->robotManager->calibrateRobotBaseToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->WorldToCamera, BoardToTCP);


  return *this->pose_WorldToRobotBase;
 }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_num_camID_valueChanged(int arg1)
  {
  std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
  this->Main->cameraManager->pipelineFlush->store(true);
  this->Main->cameraManager->setArrActiveCameras(arg1,0);
  this->Main->cameraManager->pipelineFlush->store(false);
  this->writeWorldToCamPose();
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_exit_clicked()
  {
  this->Taktgeber->stop();
  this->Main->cameraManager->pipelineDone->store(true);
  if(!this->Main->cameraManager->stopPipelineTracking()) return;
  this->close();
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_save_pose_clicked()
  {
  C_RelativePose camToBoard;
  C_AbsolutePose WorldToRobot;
  C_AbsolutePose RobotToWorld;
  C_RelativePose BoardToTCP;


  camToBoard.clear();
  WorldToRobot.clear();
  RobotToWorld.clear();
  BoardToTCP.clear();

  BoardToTCP.nx(this->ui->num_nx_boardToTCP->value());
  BoardToTCP.oy(this->ui->num_oy_boardToTCP->value());
  BoardToTCP.az(this->ui->num_az_boardToTCP->value());

  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->pose_CamToBoard->HomogenePosenMatrix[i][j];
      }

  *this->GlobalObjects->camToBoard = camToBoard;
  WorldToRobot =  this->Main->robotManager->calibrateRobotBaseToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->CameraToWorld, BoardToTCP);
  RobotToWorld.InversHomogenousPose(WorldToRobot, RobotToWorld.HomogenePosenMatrix);

  this->Main->robotManager->roboter->Abs_RobotToWorld_Pose = RobotToWorld;
  this->Main->robotManager->roboter->Abs_WorldToRobot_Pose = WorldToRobot;

  this->ui->txb_nx_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][0]));
  this->ui->txb_ny_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][0]));
  this->ui->txb_nz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][0]));

  this->ui->txb_ox_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][1]));
  this->ui->txb_oy_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][1]));
  this->ui->txb_oz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][1]));

  this->ui->txb_ax_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][2]));
  this->ui->txb_ay_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][2]));
  this->ui->txb_az_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][2]));

  this->ui->txb_px_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[0][3]));
  this->ui->txb_py_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[1][3]));
  this->ui->txb_pz_robot_world->setText(QString::number(RobotToWorld.HomogenePosenMatrix[2][3]));

  this->GlobalObjects->saveManager->saveRobotCos(*this->Main->robotManager->roboter);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_set_home_clicked()
{
C_AbsolutePose Pose;
this->Main->robotManager->roboter->Get_Current_TCP_Pose(Pose);
this->MsgBox->setText("Der Roboter setzt sich nun in Bewegung. \n Räumen Sie bitte das Umfeld frei!");
this->MsgBox->setIcon(QMessageBox::Critical);
this->MsgBox->exec();

if(this->ui->rb_home_Pose->isChecked())
  {
  this->Main->robotManager->roboter->Abs_Home_Pose = Pose;
  this->GlobalObjects->saveManager->saveRobotHomePose(&Pose);
    this->ui->grpb_home_pose->setTitle("Home Pose");

    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_Home_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

  }
else if(this->ui->rb_inter_waiting_Pose->isChecked())
  {
  this->Main->robotManager->roboter->Abs_inter_waiting_Pose = Pose;
  this->GlobalObjects->saveManager->saveRobotInterWaitingPose(&Pose);
    this->ui->grpb_home_pose->setTitle("Inter Pose");

    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_inter_waiting_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

  }
else if(this->ui->rb_waiting_Pose->isChecked())
  {
  this->Main->robotManager->roboter->Abs_waiting_Pose = Pose;
  this->GlobalObjects->saveManager->saveRobotReadyPose(&Pose);
    this->ui->grpb_home_pose->setTitle("Ready Pose");
      C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_waiting_Pose;
      this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
      this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
      this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

      this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
      this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
      this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

      this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
      this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
      this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

      this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
      this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
      this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));
  }
}


void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_move_home_clicked()
  {
  double Panda_Vel_max   = abs(this->ui->dspb_Panda_Vel_max->value());
  double Panda_Acc_max   = abs(this->ui->dspb_Panda_Acc_max->value());
  double Panda_Omega_max = abs(this->ui->dspb_Panda_Omega_max->value());
  double Panda_Alpha_max = abs(this->ui->dspb_Panda_Alpha_max->value());
  this->Main->robotManager->roboter->Set_Panda_Vel_Acc_max(Panda_Vel_max, Panda_Acc_max, Panda_Omega_max, Panda_Alpha_max);

  this->disableUi();
  this->MsgBox->setText("Der Roboter setzt sich nun in Bewegung. \n Räumen Sie bitte das Umfeld frei!");
  this->MsgBox->setIcon(QMessageBox::Critical);
  this->MsgBox->exec();

  C_AbsolutePose target;
  if(this->ui->rb_home_Pose->isChecked())
    {
    target = this->Main->robotManager->roboter->Abs_Home_Pose;
    }
  else if(this->ui->rb_inter_waiting_Pose->isChecked())
    {
    target = this->Main->robotManager->roboter->Abs_inter_waiting_Pose;
    }
  else if(this->ui->rb_waiting_Pose->isChecked())
    {
    target = this->Main->robotManager->roboter->Abs_waiting_Pose;
    }
  else
    {
    this->Main->robotManager->roboter->Get_Current_TCP_Pose(target);
    }
  this->moving = true;
  this->Main->robotManager->moveRobotToTarget(&target);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_no_tool_clicked()
  {
  this->ui->rb_no_tool->setChecked(true);
  this->ui->rb_calib_tool->setChecked(false);

  double tcp[4][4];
  this->GlobalObjects->loadManager->loadRobotTCP(tcp);
  this->Main->robotManager->roboter->Set_TCP_Frame(tcp);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_calib_tool_clicked()
  {
  this->ui->rb_calib_tool->setChecked(true);
  this->ui->rb_no_tool->setChecked(false);

  double tcp[4][4];
  this->GlobalObjects->loadManager->loadRobotTCPCalibration(tcp);
  this->Main->robotManager->roboter->Set_TCP_Frame(tcp);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_home_Pose_clicked()
  {
  this->ui->rb_home_Pose->setChecked(true);
  this->ui->rb_inter_waiting_Pose->setChecked(false);
  this->ui->rb_waiting_Pose->setChecked(false);
    this->ui->grpb_home_pose->setTitle("Home Pose");

    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_Home_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_inter_waiting_Pose_clicked()
  {
  this->ui->rb_home_Pose->setChecked(false);
  this->ui->rb_inter_waiting_Pose->setChecked(true);
  this->ui->rb_waiting_Pose->setChecked(false);
    this->ui->grpb_home_pose->setTitle("Inter Pose");

    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_inter_waiting_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_waiting_Pose_clicked()
  {
  this->ui->rb_home_Pose->setChecked(false);
  this->ui->rb_inter_waiting_Pose->setChecked(false);
  this->ui->rb_waiting_Pose->setChecked(true);
  this->ui->grpb_home_pose->setTitle("Ready Pose");
    C_AbsolutePose RobotHome = this->Main->robotManager->roboter->Abs_waiting_Pose;
    this->ui->txb_nx_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][0]));
    this->ui->txb_ny_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][0]));
    this->ui->txb_nz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][0]));

    this->ui->txb_ox_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][1]));
    this->ui->txb_oy_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][1]));
    this->ui->txb_oz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][1]));

    this->ui->txb_ax_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][2]));
    this->ui->txb_ay_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][2]));
    this->ui->txb_az_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][2]));

    this->ui->txb_px_home->setText(QString::number(RobotHome.HomogenePosenMatrix[0][3]));
    this->ui->txb_py_home->setText(QString::number(RobotHome.HomogenePosenMatrix[1][3]));
    this->ui->txb_pz_home->setText(QString::number(RobotHome.HomogenePosenMatrix[2][3]));

  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_set_constraint_clicked()
  {
  C_AbsolutePose pose;
  this->Main->robotManager->roboter->Get_Current_TCP_Pose(pose);
  if(this->ui->rb_constraint_x->isChecked())
    {
    this->Main->robotManager->outerConstraints->X = pose.px();
    }
  else if(this->ui->rb_constraint_nx->isChecked())
    {
    this->Main->robotManager->outerConstraints->nX = pose.px();
    }

  else if(this->ui->rb_constraint_y->isChecked())
    {
    this->Main->robotManager->outerConstraints->Y = pose.py();
    }
  else if(this->ui->rb_constraint_ny->isChecked())
    {
    this->Main->robotManager->outerConstraints->nY = pose.py();
    }

  else if(this->ui->rb_constraint_z->isChecked())
    {
    this->Main->robotManager->outerConstraints->Z = pose.pz();
    }
  else if(this->ui->rb_constraint_nz->isChecked())
    {
    this->Main->robotManager->outerConstraints->nZ = pose.pz();
    }
  this->ui->txb_constraint_x->  setText(QString::number(this->Main->robotManager->outerConstraints->X));
  this->ui->txb_constraint_nx-> setText(QString::number(this->Main->robotManager->outerConstraints->nX));
  this->ui->txb_constraint_y->  setText(QString::number(this->Main->robotManager->outerConstraints->Y));
  this->ui->txb_constraint_ny-> setText(QString::number(this->Main->robotManager->outerConstraints->nY));
  this->ui->txb_constraint_z->  setText(QString::number(this->Main->robotManager->outerConstraints->Z));
  this->ui->txb_constraint_nz-> setText(QString::number(this->Main->robotManager->outerConstraints->nZ));

  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_set_robot_horizontal_clicked()
  {
  C_AbsolutePose Horizontal;
  this->MsgBox->setText("Der Roboter setzt sich nun in Bewegung. \n Räumen Sie bitte das Umfeld frei!");
  this->MsgBox->setIcon(QMessageBox::Critical);
  this->MsgBox->exec();

  if(this->ui->rb_rel_pose->isChecked())
  {
  Horizontal.px(this->robotTcpPose->HomogenePosenMatrix[0][3]);
  Horizontal.py(this->robotTcpPose->HomogenePosenMatrix[1][3]);
  Horizontal.pz(this->robotTcpPose->HomogenePosenMatrix[2][3]);
  Horizontal.nx(0.99);
  Horizontal.ny(0.0);
  Horizontal.nz(0.0);
  Horizontal.ox(0.0);
  Horizontal.oy(-0.99);
  Horizontal.oz(0.0);
  Horizontal.ax(0.0);
  Horizontal.ay(0.0);
  Horizontal.az(-0.99);
  }
  else if(this->ui->rb_x_zero_pose->isChecked())
  {
  Horizontal.px(this->robotTcpPose->HomogenePosenMatrix[0][3]);
  Horizontal.py(0.0);
  Horizontal.pz(this->robotTcpPose->HomogenePosenMatrix[2][3]);
  Horizontal.nx(0.99);
  Horizontal.ny(0.0);
  Horizontal.nz(0.0);
  Horizontal.ox(0.0);
  Horizontal.oy(-0.99);
  Horizontal.oz(0.0);
  Horizontal.ax(0.0);
  Horizontal.ay(0.0);
  Horizontal.az(-0.99);
  }


  double Panda_Vel_max   = abs(this->ui->dspb_Panda_Vel_max->value());
  double Panda_Acc_max   = abs(this->ui->dspb_Panda_Acc_max->value());
  double Panda_Omega_max = abs(this->ui->dspb_Panda_Omega_max->value());
  double Panda_Alpha_max = abs(this->ui->dspb_Panda_Alpha_max->value());
  this->Main->robotManager->roboter->Set_Panda_Vel_Acc_max(Panda_Vel_max, Panda_Acc_max, Panda_Omega_max, Panda_Alpha_max);
  this->disableUi();
  this->moving = true;
  this->Main->robotManager->moveRobotToTarget(&Horizontal);

  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_rel_pose_clicked()
  {
  this->ui->rb_x_zero_pose->setChecked(false);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_rb_x_zero_pose_clicked()
  {
  this->ui->rb_rel_pose->setChecked(false);
  }
