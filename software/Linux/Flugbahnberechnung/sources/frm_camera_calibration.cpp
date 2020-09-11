#include "headers/frm_camera_calibration.h"
using namespace frm_Camera_Calibration;

C_frm_Camera_Calibration::C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_calibration();
    Ui->setupUi(this);
    this->GlobalObjects         = GlobalObjects;
    this->Main                  = Main;
    this->Zaehler               = 0;
    this->calibration_running   = false;
    this->photo_interval        = 0;
    this->photo_count           = 0;
    this->photo_id              = 0;
    this->intervall             = 0;
    this->usrInputAbsPhoto      = 3;
    this->Taktgeber             = new QTimer(this);
    this->Taktgeber_Intervall   = 0;
    this->lock                  = new pthread_mutex_t;
    this->camThread             = new pthread_t;
    this->imgPopOut             =  false;
    this->imgBuffer[0]          = new cv::Mat;
    this->imgBuffer[1]          = new cv::Mat;
}

C_frm_Camera_Calibration::~C_frm_Camera_Calibration()
{
    delete imgBuffer[0];
    delete imgBuffer[1];

    delete (lock);
    this->Taktgeber_Intervall = 0;
    delete (this->Taktgeber);

    this->usrInputAbsPhoto = 3;
    this->intervall             = 0;
    this->photo_id              = 0;
    this->photo_interval        = 0;
    this->calibration_running   = false;
    this->Zaehler               = 0;

    this->Main          = nullptr;
    this->GlobalObjects = nullptr;


    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Calibration::showEvent(QShowEvent* ShowEvent)
{
this->Zaehler                     = 0;
this->Taktgeber_Intervall         = 25;

connect                           (this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration::Taktgeber_Tick);
this->Taktgeber->start            (this->Taktgeber_Intervall);
this->installEventFilter          (this);
this->Zaehler                     = 0;
this->cameraID                    = 0;
this->Ui->num_TimerIntervall->setValue(this->Taktgeber_Intervall);
this->on_rb_single_calibration_clicked();
this->Ui->num_camera_id->setMaximum(GlobalObjects->absCameras-1);

Q_UNUSED(ShowEvent)
}

void C_frm_Camera_Calibration::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration::Taktgeber_Tick);
 this->Zaehler = 0;
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
  if(this->Main->cameraManager->pipelineQue->try_pop(pData))
    {
    this->Ui->txb_worker_1->setText(QString::number(pData->executionTime[0].count()));
    this->Ui->txb_worker_2->setText(QString::number(pData->executionTime[1].count()));
    this->Ui->txb_worker_3->setText(QString::number(pData->executionTime[2].count()));
    this->Ui->txb_worker_4->setText(QString::number(pData->executionTime[3].count()));
    this->Ui->txb_worker_5->setText(QString::number(pData->executionTime[4].count()));
    this->Ui->txb_worker_6->setText(QString::number(pData->executionTime[5].count()));
    this->Ui->txb_worker_7->setText(QString::number(pData->executionTime[6].count()));
    this->Ui->txb_worker_8->setText(QString::number(pData->executionTime[7].count()));
    this->Ui->txb_fps->setText(QString::number(pData->fps));
    this->Ui->txb_frametime->   setText(QString::number(pData->frametime.count()));
      this->Ui->txb_quebuffer->   setText(QString::number(pData->queBuffer));

    switch (method)
      {
      case 0:
        this->FillMat2Lbl(this->pData->cpuSrcImg[0], this->Ui->lbl_img_single_calibration);
        this->pData->cpuSrcImg[0].copyTo(*this->imgBuffer[0]);
        break;
      case 1:
        this->FillMat2Lbl(this->pData->cpuSrcImg[0], this->Ui->lbl_img_stereo_left);
        this->FillMat2Lbl(this->pData->cpuSrcImg[1], this->Ui->lbl_img_stereo_right);
        this->pData->cpuSrcImg[0].copyTo(*this->imgBuffer[0]);
        this->pData->cpuSrcImg[1].copyTo(*this->imgBuffer[1]);

        break;
       }
    delete(pData);
    }

   if (this->Main->cameraManager->getCalibrationDone())
     {
     this->ShowTable();
     }
  }

void C_frm_Camera_Calibration::FillMat2Lbl(cv::Mat& img, QLabel* label)
  {
  QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
  label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
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
  this->GlobalObjects->watchdog->stop();
  delete(this->GlobalObjects->watchdog);
  this->Main->cameraManager->pipelineDone.store(true);
  if(!this->Main->cameraManager->stopPipelineTracking()) return;
  this->close();
}

void C_frm_Camera_Calibration::on_num_camera_id_valueChanged(int arg1)
{
    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->setFlush(true);
    if(method == 0)
        this->Main->cameraManager->setArrActiveCameras(arg1,0);
    else
        this->Main->cameraManager->setArrActiveCameras(arg1,0);
        int arg2 = arg1+1;
        this->Main->cameraManager->setArrActiveCameras(arg2,1);
        this->Main->cameraManager->setFlush(false);
}

void C_frm_Camera_Calibration::on_rb_single_calibration_clicked()
{
    this->method                                  = 0;
    this->Ui->num_camera_id->setValue             (0);
    this->Ui->num_camera_id->setSingleStep        (1);
    this->Ui->num_camera_id->setMaximum       (GlobalObjects->absCameras-1);
    this->cameraID                                = 0;

    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->setFlush(true);
    this->Main->cameraManager->setArrActiveCameras(0,0);
    this->Main->cameraManager->setFlush(false);
    this->Ui->rb_stereo_calibration->setChecked   (false);
    this->Ui->rb_single_calibration->setChecked   (true);

    this->Ui->lbl_img_stereo_right->setVisible     (false);
    this->Ui->lbl_img_stereo_left->setVisible     (false);

   this->Ui->lbl_img_single_calibration->setVisible(true);

}

void C_frm_Camera_Calibration::on_rb_stereo_calibration_clicked()
{
    this->method                              = 1;
    this->Ui->num_camera_id->setValue         (0);
    this->Ui->num_camera_id->setSingleStep    (1);
    this->Ui->num_camera_id->setMaximum       (GlobalObjects->absCameras-2);

    this->cameraID                            = 0;
    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->setFlush(true);
    this->Main->cameraManager->setArrActiveCameras(0,0);
    this->Main->cameraManager->setArrActiveCameras(1,1);
    this->Main->cameraManager->setFlush(false);
    this->Ui->rb_stereo_calibration->setChecked(true);
    this->Ui->rb_single_calibration->setChecked(false);

    this->Ui->lbl_img_single_calibration->setVisible(false);
    this->Ui->lbl_img_stereo_left->setVisible(true);
    this->Ui->lbl_img_stereo_right->setVisible(true);


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
  static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->lbl_calibration_running->setVisible(true);
  switch (static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->method)
    {
    case 0:
      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->calibrateSingleCamera
                                                       (static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID,
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_width->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_height->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_usrInput_images->toPlainText().toInt(),
                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_length->toPlainText().toFloat()/ 1000.0f);
      break;

    case 1:
//      static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->calibrate_stereo_camera
//                                                       (static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID,
//                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_width->toPlainText().toInt(),
//                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_height->toPlainText().toInt(),
//                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_usrInput_images->toPlainText().toInt(),
//                                                        static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_edge_length->toPlainText().toFloat()/1000.0f);
       static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Main->cameraManager->calibrate_stereo_camera_aruco(static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->cameraID,
                                                                                                                                static_cast<frm_Camera_Calibration::C_frm_Camera_Calibration*>(This)->Ui->txb_usrInput_images->toPlainText().toInt());

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
      this->Main->cameraManager->vecCameras[cameraID]->save_picture    (photo_id,naming,*this->imgBuffer[0]);
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

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      //TODO Add threading
      //Thread^ calibrate = gcnew Thread (gcnew ThreadStart (this,&C_frm_CameraCalibration_Single::camera_calibration_thread));
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
  std::string naming = "../Parameter/Bilder/Charuco_Camera_Stereo_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      this->cameraID                        = this->Ui->num_camera_id->value();
      this->Ui->bt_photo->setEnabled        (true);
      this->Ui->bt_start->setText           ("Beenden");
      this->sm_calibration_state            = 1;
      break;

      //Take pictures
    case 1:
      this->Main->cameraManager->vecCameras[cameraID]->save_picture    (photo_id,naming,*this->imgBuffer[0]);
      this->Main->cameraManager->vecCameras[cameraID+1]->save_picture    (photo_id,naming,*this->imgBuffer[1]);
      this->Ui->txb_img_count->                                     setText(QString::number(this->photo_id + 1));
      this->sm_calibration_state = 2;
      this->Ui->bt_photo->setVisible      (false);
      this->Ui->bt_start->setText         ("Start");
      this->Ui->lbl_calibration_running->setVisible(true);

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      if(int err = pthread_create(camThread,NULL, (THREADFUNCPTR) &frm_Camera_Calibration::C_frm_Camera_Calibration::camera_calibration_thread, this) !=0)
        {
          printf("**ERROR** Kamerathread konnte nicht gestartet werden");
          photo_id = 0;
        }
      else
        {
          photo_id = 0;
        }
      break;
    }
  }

void C_frm_Camera_Calibration::ShowTable()
  {
  switch(method)
    {
     case 0:
      this->Ui->tblv_single_parameters->verticalHeader()->hide();

      this->Ui->tblv_single_parameters->show();
      break;
    case 1:
      this->Ui->tblv_stereo_output->verticalHeader()->hide();
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
