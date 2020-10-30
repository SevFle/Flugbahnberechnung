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
  this->robotBaseToWorldPose = new C_AbsolutePose;
  this->camPose = new cv::Mat(cv::Mat_<double>(4,4));
  this->pData = nullptr;

  this->Taktgeber_Intervall = 0;
  this->Zaehler = 0;
  this->cameraID = 0;
  this->moving = false;


  }

C_frm_Robot_Calibration::~C_frm_Robot_Calibration()
  {
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
  delete (camPose);
  delete (robotBaseToWorldPose);
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
/************************************** Nicht öffentliche QT-Slots******************************/

void C_frm_Robot_Calibration::Taktgeber_Tick()
  {
  this->ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  this->Main->cameraManager->setRoiStatus(roiStatus::objectLost);

  if(this->Main->cameraManager->pipelineQue->try_pop(this->pData))
    {
    cv::Mat temp;
    pData->gpuUndistortedImg[0].download(temp);
    if(this->Main->cameraManager->scanChAruco(temp, *Main->cameraManager->vecCameras->at(this->ui->num_camID->value()), *this->camPose))
      {
      this->writeCamPose();
      this->writeRobotBaseToWorld();
      }
    else
      {
      for(int i =0; i < 4; i ++)
        for(int j = 0; j < 4; j++)
          {
          this->camPose->at<double>(i,j) = 0.0;
          }
      writeCamPose();
      }
    this->Main->frm_Main->FillMat2Lbl(temp, this->ui->lbl_camera_img);
    this->writeRobotTcpPose();

    delete(pData);
    pData = nullptr;
    }//if  if(this->Main->cameraManager->pipelineQue->try_pop(this->pData))
  else
    {
    pData = nullptr;
    for(int i =0; i < 4; i ++)
      for(int j = 0; j < 4; j++)
        {
        this->camPose->at<double>(i,j) = 0.0;
        }
    writeCamPose();
    writeRobotTcpPose();
    }
  if(this->Main->robotManager->roboter->Is_MotionDone())
    {
    this->moving = false;
    this->Main->robotManager->close_Panda_threading();
      this->ui->bt_move_home->setEnabled(true);
      this->ui->bt_save_pose->setEnabled(true);
      this->ui->bt_set_constraint->setEnabled(true);
      this->ui->bt_set_home->setEnabled(true);
      this->ui->dspb_Panda_Vel_max->setEnabled(true);
      this->ui->dspb_Panda_Acc_max->setEnabled(true);
      this->ui->dspb_Panda_Omega_max->setEnabled(true);
      this->ui->dspb_Panda_Alpha_max->setEnabled(true);
    }
  }//void C_frm_Robot_Calibration::Taktgeber_Tick()

void C_frm_Robot_Calibration::initUi()
  {
  this->ui->txb_constraint_x->setText(QString::number(this->Main->robotManager->outerConstraints->X));
  this->ui->txb_constraint_nx->setText(QString::number(this->Main->robotManager->outerConstraints->nX));
  this->ui->txb_constraint_y->setText(QString::number(this->Main->robotManager->outerConstraints->Y));
  this->ui->txb_constraint_ny->setText(QString::number(this->Main->robotManager->outerConstraints->nY));
  this->ui->txb_constraint_z->setText(QString::number(this->Main->robotManager->outerConstraints->Z));
  this->ui->txb_constraint_nz->setText(QString::number(this->Main->robotManager->outerConstraints->nZ));

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

void C_frm_Robot_Calibration::writeCamPose()
  {
  this->ui->txb_nx_cam->setText(QString::number(this->camPose->at<double>(0,0)));
  this->ui->txb_ny_cam->setText(QString::number(this->camPose->at<double>(1,0)));
  this->ui->txb_nz_cam->setText(QString::number(this->camPose->at<double>(2,0)));

  this->ui->txb_ox_cam->setText(QString::number(this->camPose->at<double>(0,1)));
  this->ui->txb_oy_cam->setText(QString::number(this->camPose->at<double>(1,1)));
  this->ui->txb_oz_cam->setText(QString::number(this->camPose->at<double>(2,1)));

  this->ui->txb_ax_cam->setText(QString::number(this->camPose->at<double>(0,2)));
  this->ui->txb_ay_cam->setText(QString::number(this->camPose->at<double>(1,2)));
  this->ui->txb_az_cam->setText(QString::number(this->camPose->at<double>(2,2)));

  this->ui->txb_px_cam->setText(QString::number(this->camPose->at<double>(0,3)));
  this->ui->txb_py_cam->setText(QString::number(this->camPose->at<double>(1,3)));
  this->ui->txb_pz_cam->setText(QString::number(this->camPose->at<double>(2,3)));

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

void C_frm_Robot_Calibration::writeRobotBaseToWorld()
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
C_AbsolutePose C_frm_Robot_Calibration::getPoseRobotBaseToWorld()
  {
  C_RelativePose camToBoard;
  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->camPose->at<double>(i,j);
      }
  *this->GlobalObjects->camToBoard = camToBoard;
  *this->robotBaseToWorldPose = this->Main->robotManager->calibrateRobotBaseToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->WorldToCamera);


  return *this->robotBaseToWorldPose;
 }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_num_camID_valueChanged(int arg1)
  {
  std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
  this->Main->cameraManager->pipelineFlush->store(true);
  this->Main->cameraManager->setArrActiveCameras(arg1,0);
  this->Main->cameraManager->pipelineFlush->store(false);
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

  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->camPose->at<double>(i,j);
      }
  *this->GlobalObjects->camToBoard = camToBoard;
  WorldToRobot =  this->Main->robotManager->calibrateRobotBaseToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->CameraToWorld);
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

  this->ui->bt_move_home->setEnabled(false);
  this->ui->bt_save_pose->setEnabled(false);
  this->ui->bt_set_constraint->setEnabled(false);
  this->ui->bt_set_home->setEnabled(false);
  this->ui->dspb_Panda_Vel_max->setEnabled(false);
  this->ui->dspb_Panda_Acc_max->setEnabled(false);
  this->ui->dspb_Panda_Omega_max->setEnabled(false);
  this->ui->dspb_Panda_Alpha_max->setEnabled(false);

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
