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
  this->robotToWorldPose = new C_AbsolutePose;
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
  delete (robotToWorldPose);
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
      this->writeRobotToWorld();
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
  }//void C_frm_Robot_Calibration::Taktgeber_Tick()

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

void C_frm_Robot_Calibration::writeRobotToWorld()
  {
  if(!this->moving)
    {
    C_AbsolutePose RobotToWorld = this->getPoseRobotToWorld();
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
C_AbsolutePose C_frm_Robot_Calibration::getPoseRobotToWorld()
  {
  C_RelativePose camToBoard;
  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->camPose->at<double>(i,j);
      }
  *this->GlobalObjects->camToBoard = camToBoard;
  *this->robotToWorldPose = this->Main->robotManager->calibrateRobotToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->WorldToCamera);


  return *this->robotToWorldPose;
 }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_num_camID_valueChanged(int arg1)
  {
  std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
  this->Main->cameraManager->pipelineFlush.store(true);
  this->Main->cameraManager->setArrActiveCameras(arg1,0);
  this->Main->cameraManager->pipelineFlush.store(false);
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_exit_clicked()
  {
  this->Taktgeber->stop();
  this->Main->cameraManager->pipelineDone.store(true);
  if(!this->Main->cameraManager->stopPipelineTracking()) return;
  this->close();
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_save_pose_clicked()
  {
  C_RelativePose camToBoard;
  for(int i = 0;i < 4; i++)
    for(int j=0; j < 4; j++)
      {
      camToBoard.HomogenePosenMatrix[i][j] = this->camPose->at<double>(i,j);
      }
  *this->GlobalObjects->camToBoard = camToBoard;
  this->Main->robotManager->calibrateRobotToWorld(*this->Main->cameraManager->vecCameras->at(this->ui->num_camID->value())->CameraToWorld);


  *this->robotToWorldPose = this->Main->robotManager->roboter->Abs_RobotToWorld_Pose;
  this->ui->txb_nx_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[0][0]));
  this->ui->txb_ny_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[1][0]));
  this->ui->txb_nz_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[2][0]));

  this->ui->txb_ox_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[0][1]));
  this->ui->txb_oy_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[1][1]));
  this->ui->txb_oz_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[2][1]));

  this->ui->txb_ax_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[0][2]));
  this->ui->txb_ay_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[1][2]));
  this->ui->txb_az_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[2][2]));

  this->ui->txb_px_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[0][3]));
  this->ui->txb_py_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[1][3]));
  this->ui->txb_pz_robot_world->setText(QString::number(this->robotToWorldPose->HomogenePosenMatrix[2][3]));
  }

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_set_home_clicked()
{
C_AbsolutePose HomePose;
this->Main->robotManager->roboter->Get_Current_TCP_Pose(HomePose);
this->Main->robotManager->roboter->Abs_Home_Pose = HomePose;
this->GlobalObjects->saveManager->saveRobotHomePose(&HomePose);
}

void frm_Robot_Calibration::C_frm_Robot_Calibration::on_bt_move_home_clicked()
{
  double Panda_Vel_max   = abs(this->ui->dspb_Panda_Vel_max->value());
  double Panda_Acc_max   = abs(this->ui->dspb_Panda_Acc_max->value());
  double Panda_Omega_max = abs(this->ui->dspb_Panda_Omega_max->value());
  double Panda_Alpha_max = abs(this->ui->dspb_Panda_Alpha_max->value());
  this->Main->robotManager->roboter->Set_Panda_Vel_Acc_max(Panda_Vel_max, Panda_Acc_max, Panda_Omega_max, Panda_Alpha_max);

C_AbsolutePose target;
target = this->Main->robotManager->roboter->Abs_Home_Pose;
this->Taktgeber->stop();
this->Main->robotManager->moveRobotToTarget_Slow(&target);
}
