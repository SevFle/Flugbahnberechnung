#include "headers/Forms/frm_camera_positioning.h"
using namespace frm_Camera_Positioning;

C_frm_Camera_Positioning::C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, Main::C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
  {
  this->Ui = new Ui::C_frm_camera_positioning();
  Ui->setupUi(this);
  this->GlobalObjects = GlobalObjects;
  this->Main = Main;
  this->Taktgeber = new QTimer;
  this->tData = nullptr;

  this->Taktgeber_Intervall = 0;
  this->Zaehler = 0;
  }
C_frm_Camera_Positioning::~C_frm_Camera_Positioning()
  {
  this->Zaehler = 0;
  this->Taktgeber_Intervall = 0;
  if(this->tData != nullptr)
    {
    delete (this->tData);
    this->tData = nullptr;
    }
  delete (this->Taktgeber);
  this->Main = nullptr;
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
  delete(this->GlobalObjects->watchdog);
  this->Main->cameraManager->positioningDone->store(true);
  if(!this->Main->cameraManager->stopThreadCameraPositioning()) return;
  this->close();
  }


void C_frm_Camera_Positioning::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  if(this->Main->cameraManager->threadQue->try_pop(tData))
    {
    this->Ui->txb_queBuffer->setText(QString::number(tData->queBuffer));
    if(!tData->srcImg.empty() || tData->srcImg.size() != 0)
        {
        switch (this->GlobalObjects->absCameras)
          {
          case 2:
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          break;

          case 4:
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
          break;

          case 6:
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_4->value()], this->Ui->lbl_cam_4);
            this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_5->value()], this->Ui->lbl_cam_5);
          break;

        case 8:
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_4->value()], this->Ui->lbl_cam_4);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_5->value()], this->Ui->lbl_cam_5);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_6->value()], this->Ui->lbl_cam_6);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_7->value()], this->Ui->lbl_cam_7);

        break;

        case 10:
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_4->value()], this->Ui->lbl_cam_4);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_5->value()], this->Ui->lbl_cam_5);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_6->value()], this->Ui->lbl_cam_6);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_7->value()], this->Ui->lbl_cam_7);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_8->value()], this->Ui->lbl_cam_8);
          this->Main->frm_Main->FillMat2Lbl(*tData->srcImg[this->Ui->num_cam_9->value()], this->Ui->lbl_cam_9);

        break;

          }

        }
    for(auto it = std::begin(tData->srcImg); it < std::end(tData->srcImg); it ++)
      {
      (*it)->release();
      delete (*it);
      }
    delete (tData);
    this->tData = nullptr;
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

    case 8:

      camera_list.push_back (this->Ui->num_cam_0->value());
      camera_list.push_back (this->Ui->num_cam_1->value());
      camera_list.push_back (this->Ui->num_cam_2->value());
      camera_list.push_back (this->Ui->num_cam_3->value());
      camera_list.push_back (this->Ui->num_cam_4->value());
      camera_list.push_back (this->Ui->num_cam_5->value());
      camera_list.push_back (this->Ui->num_cam_6->value());
      camera_list.push_back (this->Ui->num_cam_7->value());


      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      this->Ui->num_cam_2->setValue(2);
      this->Ui->num_cam_3->setValue(3);
      this->Ui->num_cam_4->setValue(4);
      this->Ui->num_cam_5->setValue(5);
      this->Ui->num_cam_6->setValue(6);
      this->Ui->num_cam_7->setValue(7);


      break;

    case 10:

        camera_list.push_back (this->Ui->num_cam_0->value());
        camera_list.push_back (this->Ui->num_cam_1->value());
        camera_list.push_back (this->Ui->num_cam_2->value());
        camera_list.push_back (this->Ui->num_cam_3->value());
        camera_list.push_back (this->Ui->num_cam_4->value());
        camera_list.push_back (this->Ui->num_cam_5->value());
        camera_list.push_back (this->Ui->num_cam_6->value());
        camera_list.push_back (this->Ui->num_cam_7->value());
        camera_list.push_back (this->Ui->num_cam_8->value());
        camera_list.push_back (this->Ui->num_cam_9->value());



        this->Ui->num_cam_0->setValue(0);
        this->Ui->num_cam_1->setValue(1);
        this->Ui->num_cam_2->setValue(2);
        this->Ui->num_cam_3->setValue(3);
        this->Ui->num_cam_4->setValue(4);
        this->Ui->num_cam_5->setValue(5);
        this->Ui->num_cam_6->setValue(6);
        this->Ui->num_cam_7->setValue(7);
        this->Ui->num_cam_8->setValue(6);
        this->Ui->num_cam_9->setValue(7);

      break;


      }

    this->Main->cameraManager->mvVecCamera2Temp(camera_list);

    for (int i = 0; i < GlobalObjects->absCameras; i++)
      {
      this->GlobalObjects->loadManager->loadCameraCalibration   (this->Main->cameraManager->vecCameras->at(i));
      this->GlobalObjects->loadManager->loadCameraSettings      (this->Main->cameraManager->vecCameras->at(i));
      }
    this->GlobalObjects->saveManager->saveCameraPositioning   (*this->Main->cameraManager->vecCameras, GlobalObjects->absCameras);
    for(int i = 0; i < GlobalObjects->absCameras; i ++)
    {
     this->Main->cameraManager->vecCameras->at(i)->setCameraID(i);
    }

    this->Ui->bt_apply->setEnabled(true);

}

void C_frm_Camera_Positioning::set_num_value()
  {
//  switch (this->GlobalObjects->absCameras)
//    {
//    case 2:
//      this->Ui->num_cam_0->setValue(0);
//      this->Ui->num_cam_1->setValue(1);
//      break;

//    case 4:
//      this->Ui->num_cam_0->setValue(0);
//      this->Ui->num_cam_1->setValue(1);
//      this->Ui->num_cam_2->setValue(2);
//      this->Ui->num_cam_3->setValue(3);
//      break;

//    case 6:
//      this->Ui->num_cam_0->setValue(0);
//      this->Ui->num_cam_1->setValue(1);
//      this->Ui->num_cam_2->setValue(2);
//      this->Ui->num_cam_3->setValue(3);
//      this->Ui->num_cam_4->setValue(4);
//      this->Ui->num_cam_5->setValue(5);
//      break;
//    }
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

  case 8:
    this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_2->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_3->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_4->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_5->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_6->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_7->setMaximum(GlobalObjects->absCameras-1);

    if(camera_list.empty()) return;
    this->Ui->num_cam_0->setValue(camera_list[0]);
    this->Ui->num_cam_1->setValue(camera_list[1]);
    this->Ui->num_cam_2->setValue(camera_list[2]);
    this->Ui->num_cam_3->setValue(camera_list[3]);
    this->Ui->num_cam_4->setValue(camera_list[4]);
    this->Ui->num_cam_5->setValue(camera_list[5]);
    this->Ui->num_cam_6->setValue(camera_list[6]);
    this->Ui->num_cam_7->setValue(camera_list[7]);

    break;

  case 10:
    this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_2->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_3->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_4->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_5->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_6->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_7->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_8->setMaximum(GlobalObjects->absCameras-1);
    this->Ui->num_cam_9->setMaximum(GlobalObjects->absCameras-1);


    if(camera_list.empty()) return;
    this->Ui->num_cam_0->setValue(camera_list[0]);
    this->Ui->num_cam_1->setValue(camera_list[1]);
    this->Ui->num_cam_2->setValue(camera_list[2]);
    this->Ui->num_cam_3->setValue(camera_list[3]);
    this->Ui->num_cam_4->setValue(camera_list[4]);
    this->Ui->num_cam_5->setValue(camera_list[5]);
    this->Ui->num_cam_6->setValue(camera_list[6]);
    this->Ui->num_cam_7->setValue(camera_list[7]);
    this->Ui->num_cam_8->setValue(camera_list[8]);
    this->Ui->num_cam_9->setValue(camera_list[9]);
    break;

    }
  }//set_numUD_value

void C_frm_Camera_Positioning::FillMat2Lbl(cv::Mat& img, QLabel* label)
{
    cv::Mat* imgPtr = &img;
    if(imgPtr == nullptr)
        return;
    if(img.empty())
        return;
    if(img.type()!= 0)
      {
      //Darstellung von RGB Bildern in UI Labeln
      QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
      label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
      return;
      }
    //Darstellung von Grayscale Bildern in UI Labeln
    QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
    label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
}




void frm_Camera_Positioning::C_frm_Camera_Positioning::on_numTimerIntervall_valueChanged(int arg1)
{
    this->Taktgeber->setInterval(arg1);
}
