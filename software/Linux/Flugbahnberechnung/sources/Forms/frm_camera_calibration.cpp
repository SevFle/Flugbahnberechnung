#include "headers/Forms/frm_camera_calibration.h"
using namespace frm_Camera_Calibration;

C_frm_Camera_Calibration::C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, Main::C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_calibration();
    Ui->setupUi(this);
    this->GlobalObjects = GlobalObjects;
    this->Main = Main;
    this->camThread = new pthread_t;
    this->pData = nullptr;
    this->Taktgeber = new QTimer;
    this->imgBuffer[0] = new cv::Mat;
    this->imgBuffer[1] = new cv::Mat;
    this->mPose = new cv::Mat(cv::Mat_<double>(4,4));
    this->Camera0ToWorld = new cv::Mat(cv::Mat_<double>(4,4));
    this->Camera1ToWorld = new cv::Mat(cv::Mat_<double>(4,4));
    this->Camera0ToCamera1 = new cv::Mat(cv::Mat_<double>(4,4));

    this->finished.store(false);
    this->Taktgeber_Intervall = 0;
    this->Zaehler = 0;
    this->photo_id = 0;
    this->method = 0;
    this->cameraID = 0;
    this->sm_calibration_state = 0;
    this->usrInputAbsPhoto = 0;

    this->calibration_running = false;

}

C_frm_Camera_Calibration::~C_frm_Camera_Calibration()
{
  this->calibration_running = false;

  this->usrInputAbsPhoto = 0;
  this->sm_calibration_state = 0;
  this->cameraID = 0;
  this->method = 0;
  this->photo_id = 0;
  this->Zaehler = 0;
  this->Taktgeber_Intervall = 0;


  this->finished.store(false);
  delete (Camera0ToCamera1);
  delete (Camera1ToWorld);
  delete (Camera0ToWorld);

  delete (mPose);
  delete(imgBuffer[1]);
  delete (imgBuffer[0]);
  delete (Taktgeber);
  if(this->pData != nullptr)
    {
      delete (this->pData);
      this->pData = nullptr;
    }

  delete (this->camThread);
  this->Main = nullptr;
  this->GlobalObjects = nullptr;

    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Calibration::showEvent(QShowEvent* ShowEvent)
{
this->Zaehler                           = 0;
this->Taktgeber_Intervall               = 25;
this->cameraID = 0;
connect                                 (this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration::Taktgeber_Tick);
this->Taktgeber->start                  (this->Taktgeber_Intervall);
this->installEventFilter                (this);
this->Ui->num_TimerIntervall->setValue  (this->Taktgeber_Intervall);
this->on_rb_single_calibration_clicked  ();
this->Ui->num_camera_id->setMaximum     (GlobalObjects->absCameras-1);
this->Ui->grpb_2_output->setVisible     (false);
this->Ui->lbl_stereo_camera_current_cam->setVisible(false);

Q_UNUSED(ShowEvent)
}

void C_frm_Camera_Calibration::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED                   (CloseEvent);
 this->removeEventFilter    (this);
 this->Taktgeber->stop      ();
 disconnect                 (this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration::Taktgeber_Tick);
 this->Zaehler              = 0;
 this->cameraID             = 0;

 }

bool               C_frm_Camera_Calibration::eventFilter                                       (QObject* Object, QEvent* Event)
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

void C_frm_Camera_Calibration::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  this->Main->cameraManager->setRoiStatus(roiStatus::objectLost);

  if(this->Main->cameraManager->pipelineQue->try_pop(this->pData))
    {
    this->Ui->txb_worker_1->setText(QString::number(pData->executionTime[0].count(), 'f', 1));
    this->Ui->txb_worker_2->setText(QString::number(pData->executionTime[1].count(), 'f', 1));
    this->Ui->txb_worker_3->setText(QString::number(pData->executionTime[2].count(), 'f', 1));
    this->Ui->txb_worker_4->setText(QString::number(pData->executionTime[3].count(), 'f', 1));
    this->Ui->txb_worker_5->setText(QString::number(pData->executionTime[4].count(), 'f', 1));
    this->Ui->txb_worker_6->setText(QString::number(pData->executionTime[5].count(), 'f', 1));
    this->Ui->txb_worker_7->setText(QString::number(pData->executionTime[6].count(), 'f', 1));
    this->Ui->txb_worker_8->setText(QString::number(pData->executionTime[7].count(), 'f', 1));
    this->Ui->txb_fps->setText(QString::number(pData->fps));
    this->Ui->txb_frametime->   setText(QString::number(pData->frametime.count()));
    this->Ui->txb_quebuffer->   setText(QString::number(pData->queBuffer));

    switch (method)
      {
      case 0:
        if(this->Main->cameraManager->scanChAruco(this->pData->cpuSrcImg[0], *Main->cameraManager->vecCameras->at(this->Ui->num_camera_id->value()), *this->Camera0ToWorld))
          {
          this->Main->frm_Main->FillMat2Lbl(this->pData->cpuSrcImg[0], this->Ui->lbl_img_single_calibration);
          //imgBuffer dient zur speicherung von Bildern im Kalibrrierungsprozess
          this->pData->cpuSrcImg[0].copyTo(*this->imgBuffer[0]);
          this->Ui->txb_nx->setText(QString::number(this->Camera0ToWorld->at<double>(0,0)));
          this->Ui->txb_ny->setText(QString::number(this->Camera0ToWorld->at<double>(1,0)));
          this->Ui->txb_nz->setText(QString::number(this->Camera0ToWorld->at<double>(2,0)));

          this->Ui->txb_ox->setText(QString::number(this->Camera0ToWorld->at<double>(0,1)));
          this->Ui->txb_oy->setText(QString::number(this->Camera0ToWorld->at<double>(1,1)));
          this->Ui->txb_oz->setText(QString::number(this->Camera0ToWorld->at<double>(2,1)));

          this->Ui->txb_ax->setText(QString::number(this->Camera0ToWorld->at<double>(0,2)));
          this->Ui->txb_ay->setText(QString::number(this->Camera0ToWorld->at<double>(1,2)));
          this->Ui->txb_az->setText(QString::number(this->Camera0ToWorld->at<double>(2,2)));

          this->Ui->txb_px->setText(QString::number(this->Camera0ToWorld->at<double>(0,3)));
          this->Ui->txb_py->setText(QString::number(this->Camera0ToWorld->at<double>(1,3)));
          this->Ui->txb_pz->setText(QString::number(this->Camera0ToWorld->at<double>(2,3)));
          }
        else
          {
            this->Main->frm_Main->FillMat2Lbl(this->pData->cpuSrcImg[0], this->Ui->lbl_img_single_calibration);
            //imgBuffer dient zur speicherung von Bildern im Kalibrrierungsprozess
            this->pData->cpuSrcImg[0].copyTo(*this->imgBuffer[0]);
            this->Ui->txb_nx->setText(QString::number(0));
            this->Ui->txb_ny->setText(QString::number(0));
            this->Ui->txb_nz->setText(QString::number(0));

            this->Ui->txb_ox->setText(QString::number(0));
            this->Ui->txb_oy->setText(QString::number(0));
            this->Ui->txb_oz->setText(QString::number(0));

            this->Ui->txb_ax->setText(QString::number(0));
            this->Ui->txb_ay->setText(QString::number(0));
            this->Ui->txb_az->setText(QString::number(0));

            this->Ui->txb_px->setText(QString::number(0));
            this->Ui->txb_py->setText(QString::number(0));
            this->Ui->txb_pz->setText(QString::number(0));
          }
        break;
      case 1:
        cv::Mat temp1, temp2;
        this->pData->gpuUndistortedImg[0].download(temp1);
        this->pData->gpuUndistortedImg[1].download(temp2);
        temp1.copyTo(*this->imgBuffer[0]);
        temp2.copyTo(*this->imgBuffer[1]);

        bool btemp1, btemp2;
        btemp1 = this->Main->cameraManager->scanChAruco(temp1, *Main->cameraManager->vecCameras->at(this->Ui->num_camera_id->value()), *this->Camera0ToWorld);
        if(btemp1)
          {
          this->Ui->txb_nx->setText(QString::number(this->Camera0ToWorld->at<double>(0,0)));
          this->Ui->txb_ny->setText(QString::number(this->Camera0ToWorld->at<double>(1,0)));
          this->Ui->txb_nz->setText(QString::number(this->Camera0ToWorld->at<double>(2,0)));

          this->Ui->txb_ox->setText(QString::number(this->Camera0ToWorld->at<double>(0,1)));
          this->Ui->txb_oy->setText(QString::number(this->Camera0ToWorld->at<double>(1,1)));
          this->Ui->txb_oz->setText(QString::number(this->Camera0ToWorld->at<double>(2,1)));

          this->Ui->txb_ax->setText(QString::number(this->Camera0ToWorld->at<double>(0,2)));
          this->Ui->txb_ay->setText(QString::number(this->Camera0ToWorld->at<double>(1,2)));
          this->Ui->txb_az->setText(QString::number(this->Camera0ToWorld->at<double>(2,2)));

          this->Ui->txb_px->setText(QString::number(this->Camera0ToWorld->at<double>(0,3)));
          this->Ui->txb_py->setText(QString::number(this->Camera0ToWorld->at<double>(1,3)));
          this->Ui->txb_pz->setText(QString::number(this->Camera0ToWorld->at<double>(2,3)));
          }
        else
          {
          this->Ui->txb_nx->setText(QString::number(0));
          this->Ui->txb_ny->setText(QString::number(0));
          this->Ui->txb_nz->setText(QString::number(0));

          this->Ui->txb_ox->setText(QString::number(0));
          this->Ui->txb_oy->setText(QString::number(0));
          this->Ui->txb_oz->setText(QString::number(0));

          this->Ui->txb_ax->setText(QString::number(0));
          this->Ui->txb_ay->setText(QString::number(0));
          this->Ui->txb_az->setText(QString::number(0));

          this->Ui->txb_px->setText(QString::number(0));
          this->Ui->txb_py->setText(QString::number(0));
          this->Ui->txb_pz->setText(QString::number(0));
          }
        btemp2 = this->Main->cameraManager->scanChAruco(temp2, *Main->cameraManager->vecCameras->at(this->Ui->num_camera_id->value()+1), *this->Camera1ToWorld);
        if(btemp2)
          {
          this->Ui->txb_nx_2->setText(QString::number(this->Camera1ToWorld->at<double>(0,0)));
          this->Ui->txb_ny_2->setText(QString::number(this->Camera1ToWorld->at<double>(1,0)));
          this->Ui->txb_nz_2->setText(QString::number(this->Camera1ToWorld->at<double>(2,0)));

          this->Ui->txb_ox_2->setText(QString::number(this->Camera1ToWorld->at<double>(0,1)));
          this->Ui->txb_oy_2->setText(QString::number(this->Camera1ToWorld->at<double>(1,1)));
          this->Ui->txb_oz_2->setText(QString::number(this->Camera1ToWorld->at<double>(2,1)));

          this->Ui->txb_ax_2->setText(QString::number(this->Camera1ToWorld->at<double>(0,2)));
          this->Ui->txb_ay_2->setText(QString::number(this->Camera1ToWorld->at<double>(1,2)));
          this->Ui->txb_az_2->setText(QString::number(this->Camera1ToWorld->at<double>(2,2)));

          this->Ui->txb_px_2->setText(QString::number(this->Camera1ToWorld->at<double>(0,3)));
          this->Ui->txb_py_2->setText(QString::number(this->Camera1ToWorld->at<double>(1,3)));
          this->Ui->txb_pz_2->setText(QString::number(this->Camera1ToWorld->at<double>(2,3)));
          }
        else
          {
          this->Ui->txb_nx_2->setText(QString::number(0));
          this->Ui->txb_ny_2->setText(QString::number(0));
          this->Ui->txb_nz_2->setText(QString::number(0));

          this->Ui->txb_ox_2->setText(QString::number(0));
          this->Ui->txb_oy_2->setText(QString::number(0));
          this->Ui->txb_oz_2->setText(QString::number(0));

          this->Ui->txb_ax_2->setText(QString::number(0));
          this->Ui->txb_ay_2->setText(QString::number(0));
          this->Ui->txb_az_2->setText(QString::number(0));

          this->Ui->txb_px_2->setText(QString::number(0));
          this->Ui->txb_py_2->setText(QString::number(0));
          this->Ui->txb_pz_2->setText(QString::number(0));
          }

        if(btemp1 && btemp2)
          {
          *this->Camera0ToCamera1 = this->Main->cameraManager->calculate_camera_pose(this->Ui->num_camera_id->value(), this->Ui->num_camera_id->value()+1, this->Camera0ToWorld, this->Camera1ToWorld);
            {
            this->Ui->txb_nx_3->setText(QString::number(this->Camera0ToCamera1->at<double>(0,0)));
            this->Ui->txb_ny_3->setText(QString::number(this->Camera0ToCamera1->at<double>(1,0)));
            this->Ui->txb_nz_3->setText(QString::number(this->Camera0ToCamera1->at<double>(2,0)));

            this->Ui->txb_ox_3->setText(QString::number(this->Camera0ToCamera1->at<double>(0,1)));
            this->Ui->txb_oy_3->setText(QString::number(this->Camera0ToCamera1->at<double>(1,1)));
            this->Ui->txb_oz_3->setText(QString::number(this->Camera0ToCamera1->at<double>(2,1)));

            this->Ui->txb_ax_3->setText(QString::number(this->Camera0ToCamera1->at<double>(0,2)));
            this->Ui->txb_ay_3->setText(QString::number(this->Camera0ToCamera1->at<double>(1,2)));
            this->Ui->txb_az_3->setText(QString::number(this->Camera0ToCamera1->at<double>(2,2)));

            this->Ui->txb_px_3->setText(QString::number(this->Camera0ToCamera1->at<double>(0,3)));
            this->Ui->txb_py_3->setText(QString::number(this->Camera0ToCamera1->at<double>(1,3)));
            this->Ui->txb_pz_3->setText(QString::number(this->Camera0ToCamera1->at<double>(2,3)));
            }
          }


        this->Main->frm_Main->FillMat2Lbl(temp1, this->Ui->lbl_img_stereo_left);
        this->Main->frm_Main->FillMat2Lbl(temp2, this->Ui->lbl_img_stereo_right);

        break;
       }
    delete(pData);
    pData = nullptr;

    }
  else
      pData = nullptr;

  if(this->finished == true)
    {

      this->Ui->txb_rms->setText(QString::number(this->rms));
      this->Ui->txb_fx->setText(QString::number(this->intrinsic[0][0]));
      this->Ui->txb_fy->setText(QString::number(this->intrinsic[1][1]));
      this->Ui->txb_cx->setText(QString::number(this->intrinsic[0][2]));
      this->Ui->txb_cy->setText(QString::number(this->intrinsic[1][2]));

      this->finished.store(false);


    }

  }

void C_frm_Camera_Calibration::on_bt_start_clicked()
{
    this->Ui->lbl_calibration_running->setVisible     (false);
    this->Ui->bt_photo->setVisible                    (true);
    this->sm_calibration_state                        = 0;
    this->calibration_running                         = true;

    switch (method)
      {
      case 0:
        sm_Single_camera_calibration                  ();
        break;
      case 1:
        sm_Stereo_camera_calibration                  ();
        break;
      }
    }


void frm_Camera_Calibration::C_frm_Camera_Calibration::on_bt_exit_clicked()
{
  this->Taktgeber->stop();
  delete(this->GlobalObjects->watchdog);
  this->Main->cameraManager->pipelineDone->store(true);
  if(!this->Main->cameraManager->stopPipelineTracking()) return;
  this->close();
}

void C_frm_Camera_Calibration::on_num_camera_id_valueChanged(int arg1)
{
    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->pipelineFlush->store(true);
    if(method == 0)
        this->Main->cameraManager->setArrActiveCameras(arg1,0);
    else
      {
        this->Main->cameraManager->setArrActiveCameras(arg1,0);
        int arg2 = arg1+1;
        this->Main->cameraManager->setArrActiveCameras(arg2,1);
      }
    this->Main->cameraManager->pipelineFlush->store(false);

    if(arg1 == 0)
      {
      this->Ui->bt_pose_estimation->setEnabled(true);
      }
    else
      {
      this->Ui->bt_pose_estimation->setEnabled(false);
      }

}

void C_frm_Camera_Calibration::on_rb_single_calibration_clicked()
{
    this->method                                      = 0;
    this->Ui->num_camera_id->setValue                 (0);
    this->Ui->num_camera_id->setSingleStep            (1);
    this->Ui->num_camera_id->setMaximum               (GlobalObjects->absCameras-1);
    this->cameraID                                    = 0;
    this->Ui->grpb_1_output->setTitle(QString("Pose Kamera " + QString::number(this->Ui->num_camera_id->value())));
    this->Ui->grpb_2_output->setVisible(false);


    std::lock_guard<std::mutex> lck                   (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->pipelineFlush->store               (true);
    this->Main->cameraManager->setArrActiveCameras    (0,0);
    this->Main->cameraManager->pipelineFlush->store               (false);
    this->Ui->rb_stereo_calibration->setChecked       (false);
    this->Ui->rb_single_calibration->setChecked       (true);

    this->Ui->label_5->setVisible                     (true);
    this->Ui->label_6->setVisible                     (true);
    this->Ui->label_7->setVisible                     (true);


    this->Ui->lbl_img_stereo_right->setVisible        (false);
    this->Ui->lbl_img_stereo_left->setVisible         (false);

    this->Ui->txb_edge_width->setVisible              (true);
    this->Ui->txb_edge_height->setVisible             (true);
    this->Ui->txb_edge_length->setVisible             (true);
    this->Ui->lbl_stereo_camera_current_cam->setVisible(false);
    this->Ui->lbl_stereo_camera_current_cam->setText("");

   this->Ui->lbl_img_single_calibration->setVisible   (true);
}

void C_frm_Camera_Calibration::on_rb_stereo_calibration_clicked()
{
    this->method                                      = 1;
    this->Ui->num_camera_id->setValue                 (0);
    this->Ui->num_camera_id->setSingleStep            (1);
    this->Ui->num_camera_id->setMaximum               (GlobalObjects->absCameras-2);
    this->Ui->grpb_1_output->setTitle(QString("Pose Kamera " + QString::number(this->Ui->num_camera_id->value())));
    this->Ui->grpb_2_output->setTitle(QString("Pose Kamera " + QString::number(this->Ui->num_camera_id->value() + 1)));
    this->Ui->grpb_2_output->setVisible(true);


    this->Ui->label_5->setVisible                     (false);
    this->Ui->label_6->setVisible                     (false);
    this->Ui->label_7->setVisible                     (false);

    this->Ui->txb_edge_width->setVisible              (false);
    this->Ui->txb_edge_height->setVisible             (false);
    this->Ui->txb_edge_length->setVisible             (false);

    this->Ui->txb_usrInput_images->setVisible         (false);

    this->cameraID                            = 0;
    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->pipelineFlush->store               (true);
    this->Main->cameraManager->setArrActiveCameras    (0,0);
    this->Main->cameraManager->setArrActiveCameras    (1,1);
    this->Main->cameraManager->pipelineFlush->store               (false);
    this->Ui->rb_stereo_calibration->setChecked       (true);
    this->Ui->rb_single_calibration->setChecked       (false);

    this->Ui->lbl_img_single_calibration->setVisible  (false);
    this->Ui->lbl_img_stereo_left->setVisible         (true);
    this->Ui->lbl_img_stereo_right->setVisible        (true);
    this->Ui->lbl_stereo_camera_current_cam->setVisible(true);
    this->Ui->lbl_stereo_camera_current_cam->setText("");


}

void C_frm_Camera_Calibration::on_bt_photo_clicked()
  {
  switch(method)
    {
    case 0:
      sm_Single_camera_calibration();
      break;
    case 1:
      sm_Stereo_camera_calibration();
      break;
    }
  }
void C_frm_Camera_Calibration::camera_calibration_thread (void* This)
  {
  C_AbsolutePose Pose;
  double rms;
  double intrinsic[3][3];
  double distcoeffs[1][5];


  static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->lbl_calibration_running->setVisible(true);
  switch (static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->method)
    {
    case 0:
      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->calibrateSingleCamera
                                                       (static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID,
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_width->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_height->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_usrInput_images->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_length->toPlainText().toFloat()/ 1000.0f, &rms);

      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->
          Main->cameraManager->vecCameras->at(static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID)->getCalibrationParameter(distcoeffs, intrinsic);
      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->rms = rms;
      for(int i=0; i<3;i++)
        for(int j=0;j<3;j++)
          {
          static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->intrinsic[i][j] = intrinsic[i][j];
          }
      for(int i=0; i<3;i++)
        {
        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->distcoeffs[0][i] = distcoeffs[0][i];
        }
      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->finished.store(true);

      break;

    case 1:
       static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->calibrate_stereo_camera_aruco(static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID,
                                                                                                                      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_usrInput_images->toPlainText().toInt());
      Pose = *static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->vecCameras->at(static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID + 1)->CameraToWorld;
      break;

    }
  static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->lbl_calibration_running->setVisible(false);
  }

void C_frm_Camera_Calibration::sm_Single_camera_calibration ()
  {
  std::string naming = "../Parameter/Bilder/Camera_Single_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      this->cameraID                        = this->Ui->num_camera_id->value();
      this->Ui->num_camera_id->setEnabled(false);
      this->photo_id                        = 0;
      this->usrInputAbsPhoto                = this->Ui->txb_usrInput_images->toPlainText().toInt();
      this->Ui->bt_photo->setEnabled        (true);
      this->Ui->bt_start->setText           ("Beenden");
      this->sm_calibration_state            = 1;
      break;

      //Take pictures
    case 1:
      this->Main->cameraManager->vecCameras->at(cameraID)->save_picture    (photo_id,naming,*this->imgBuffer[0]);
      this->Main->frm_Main->FillMat2Lbl(*this->imgBuffer[0], this->Ui->lbl_img_0);
      this->Ui->txb_img_count->setText(QString::number                  (this->photo_id + 1));
      this->photo_id++;

      if (photo_id >= usrInputAbsPhoto)
        {
        this->sm_calibration_state = 2;
        }

      break;

    case 2:
      this->Ui->bt_photo->setVisible      (false);
      this->calibration_running           = false;
      this->Ui->bt_start->setText         ("Start");
      this->Ui->lbl_calibration_running->setVisible(true);

      if(int err = pthread_create(camThread,NULL, (THREADFUNCPTR) &frm_Camera_Calibration::C_frm_Camera_Calibration::camera_calibration_thread, this) !=0)
        {
          printf("**ERROR** Kamerathread konnte nicht gestartet werden");
          photo_id = 0;
        }
      else
        {
          photo_id = 0;
        }
      this->Ui->num_camera_id->setEnabled(true);

      return;
    }
  }

void C_frm_Camera_Calibration::sm_Stereo_camera_calibration ()
  {
  this->Main->cameraManager->calculate_camera_pose(this->Ui->num_camera_id->value(), this->Ui->num_camera_id->value()+1, this->Camera0ToCamera1);
  std::string text;
  text = "Kamera " + std::to_string(this->Ui->num_camera_id->value()) + "gegen " + std::to_string(this->Ui->num_camera_id->value()+1) + "kalibriert";
  QString Qtext;
  Qtext.fromStdString(text);
  this->Ui->lbl_stereo_camera_current_cam->setText(Qtext);
  }

void C_frm_Camera_Calibration::ShowTable()
  {
  switch(method)
    {
     case 0:

      break;
    case 1:
      //this->Ui->tblv_stereo_output->data
      break;
    default:
      return;

    }
  }

void frm_Camera_Calibration::C_frm_Camera_Calibration::on_num_TimerIntervall_valueChanged(int arg1)
  {
  this->Taktgeber->setInterval(arg1);
  }

void frm_Camera_Calibration::C_frm_Camera_Calibration::on_bt_pose_estimation_clicked()
  {
  C_AbsolutePose CameraPose;
  std::cout << "Pose cam 0 " << std::endl << this->mPose << std::endl;
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
      {
      CameraPose.HomogenePosenMatrix[i][j] = this->mPose->at<double>(i,j);
      }
  *this->Main->cameraManager->vecCameras->at(0)->CameraToWorld = CameraPose;
  this->GlobalObjects->saveManager->saveCameraCos(*this->Main->cameraManager->vecCameras->at(0));
  std::cout << "Camera 0 to world saved, world set." << std::endl;
  }
