#include "headers/frm_camera_positioning.h"
using namespace frm_Camera_Positioning;

C_frm_Camera_Positioning::C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_positioning();
    Ui->setupUi(this);
    this->GlobalObjects       = GlobalObjects;
    this->Taktgeber           = new QTimer(this);
    this->lock                = new pthread_mutex_t;
    this->Main                = Main;
    this->TimerWait           = 0;
    this->Taktgeber_Intervall = 50;

}

C_frm_Camera_Positioning::~C_frm_Camera_Positioning()
  {
  this->Taktgeber_Intervall = 0;
  this->TimerWait           = 0;
  this->Main                = nullptr;
  delete                    (lock);
  delete                    (this->Taktgeber);
  this->GlobalObjects       = nullptr;
  delete                    (Ui);
}


/************************************** QT-Events******************************/
void C_frm_Camera_Positioning::showEvent(QShowEvent* ShowEvent)
  {
  this->Zaehler               = 0;
  connect                     (this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
  this->Taktgeber->start      (this->Taktgeber_Intervall);
  this->installEventFilter    (this);
  this->Ui->numTimerIntervall->setValue(Taktgeber_Intervall);
  this->Zaehler               = 0;
  pthread_mutex_init          (lock, NULL);
  this->Main->cameraManager->setPositioningDone(false);
  this->Main->cameraManager->startThreadCameraPositioning();
  this->set_num_value(*GlobalObjects->camera_order);
  Q_UNUSED                    (ShowEvent)
  }

void C_frm_Camera_Positioning::closeEvent(QCloseEvent* CloseEvent)
  {
  this->removeEventFilter(this);
  this->Taktgeber->stop();
  disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
  this->Zaehler = 0;
  Q_UNUSED(CloseEvent);
  }

bool               C_frm_Camera_Positioning::eventFilter                                       (QObject* Object, QEvent* Event)
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
void C_frm_Camera_Positioning::on_bt_exit_clicked()
  {
  this->Main->cameraManager->setPositioningDone(true);
  if(!this->Main->cameraManager->stopThreadCameraPositioning()) return;
  this->close();
  }


void C_frm_Camera_Positioning::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));

      if(this->Main->cameraManager->threadQue->try_pop(tData))
        {
          this->Ui->txb_queBuffer->setText(QString::number(tData->queBuffer));
          if(!tData->srcImg.empty())
            {
            switch (this->GlobalObjects->absCameras)
              {
              case 2:
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
              break;

              case 4:
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
              break;

              case 6:
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_4->value()], this->Ui->lbl_cam_4);
                FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_5->value()], this->Ui->lbl_cam_5);
              break;
              }

            }
        for(auto it = std::begin(tData->srcImg); it < std::end(tData->srcImg); it ++)
            {
            (*it)->release();
            delete (*it);
            }
      delete (tData);
       }
}


void C_frm_Camera_Positioning::on_bt_apply_clicked()
{
    std::vector<Camera::C_Camera2*> camera_vector_temp;
    camera_vector_temp.resize (this->GlobalObjects->absCameras);
    this->Ui->bt_apply->setEnabled(false);

    std::vector<int> camera_list;

    switch (this->GlobalObjects->absCameras)
      {
      case 2:

        camera_list.push_back (this->Ui->num_cam_0->value());
        camera_list.push_back (this->Ui->num_cam_1->value());

        this->Ui->num_cam_0->setValue(0);
        this->Ui->num_cam_1->setValue(1);

        break;

      case 4:
        camera_list.push_back (this->Ui->num_cam_0->value());
        camera_list.push_back (this->Ui->num_cam_1->value());
        camera_list.push_back (this->Ui->num_cam_2->value());
        camera_list.push_back (this->Ui->num_cam_3->value());

        this->Ui->num_cam_0->setValue(0);
        this->Ui->num_cam_1->setValue(1);
        this->Ui->num_cam_2->setValue(2);
        this->Ui->num_cam_3->setValue(3);

        break;

      case 6:

        camera_list.push_back (this->Ui->num_cam_0->value());
        camera_list.push_back (this->Ui->num_cam_1->value());
        camera_list.push_back (this->Ui->num_cam_2->value());
        camera_list.push_back (this->Ui->num_cam_3->value());
        camera_list.push_back (this->Ui->num_cam_4->value());
        camera_list.push_back (this->Ui->num_cam_5->value());

        this->Ui->num_cam_0->setValue(0);
        this->Ui->num_cam_1->setValue(1);
        this->Ui->num_cam_2->setValue(2);
        this->Ui->num_cam_3->setValue(3);
        this->Ui->num_cam_4->setValue(4);
        this->Ui->num_cam_5->setValue(5);

        break;
      }

    this->Main->cameraManager->mvVecCamera2Temp(camera_list);
    for (int i = 0; i < GlobalObjects->absCameras; i++)
      {
      this->Main->cameraManager->loadManager->loadCameraCalibration   (this->Main->cameraManager->vecCameras[i]);
      this->Main->cameraManager->loadManager->loadCameraSettings      (this->Main->cameraManager->vecCameras[i]);
      }
    this->Main->cameraManager->saveManager->saveCameraPositioning   (camera_list);


    TimerWait                = Zaehler + 5;
    this->Ui->bt_apply->setEnabled(true);

}

void C_frm_Camera_Positioning::set_num_value()
  {
  switch (this->GlobalObjects->absCameras)
    {
    case 2:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      break;

    case 4:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      this->Ui->num_cam_2->setValue(2);
      this->Ui->num_cam_3->setValue(3);
      break;

    case 6:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      this->Ui->num_cam_2->setValue(2);
      this->Ui->num_cam_3->setValue(3);
      this->Ui->num_cam_4->setValue(4);
      this->Ui->num_cam_5->setValue(5);
      break;
    }
  }//set_numUD_value
void C_frm_Camera_Positioning::set_num_value (std::vector<int> camera_list)
  {
  switch (this->GlobalObjects->absCameras)
    {
    case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
      this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_0->setValue(camera_list[0]);
      break;

    case 2:
      this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras-1);
      if(camera_list.empty()) return;
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      break;

    case 4:
      this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_2->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_3->setMaximum(GlobalObjects->absCameras-1);
      if(camera_list.empty()) return;
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      break;

    case 6:
      this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_2->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_3->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_4->setMaximum(GlobalObjects->absCameras-1);
      this->Ui->num_cam_5->setMaximum(GlobalObjects->absCameras-1);
      if(camera_list.empty()) return;
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      this->Ui->num_cam_4->setValue(camera_list[4]);
      this->Ui->num_cam_5->setValue(camera_list[5]);
      break;
      break;
    }
  }//set_numUD_value

void C_frm_Camera_Positioning::FillMat2Lbl(cv::Mat& img, QLabel* label)
{
  QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
  label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
}




void frm_Camera_Positioning::C_frm_Camera_Positioning::on_numTimerIntervall_valueChanged(int arg1)
{
    this->Taktgeber->setInterval(arg1);
}
