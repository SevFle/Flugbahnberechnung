#include "headers/frm_camera_positioning.h"
using namespace frm_Camera_Positioning;

C_frm_Camera_Positioning::C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_positioning();
    Ui->setupUi(this);
    this->GlobalObjects  = GlobalObjects;
    this->Main           = Main;
    this->cameras_in_use = GlobalObjects->absCameras;
    this->TimerWait      = 0;
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 25;
    this->lock            = new pthread_mutex_t;

}

C_frm_Camera_Positioning::~C_frm_Camera_Positioning()
{
    delete(lock);
    this->Taktgeber_Intervall = 0;
    delete (this->Taktgeber);

    this->TimerWait = 0;

    this->Main          = nullptr;
    this->GlobalObjects = nullptr;

    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Positioning::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
    connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);
this->Zaehler             = 0;
this->TimerWait           = 50;
this->cameras_in_use      = GlobalObjects->absCameras;
pthread_mutex_init(lock, NULL);
if (this->Main->Camera_manager->load_positioning) this->set_num_value (*GlobalObjects->camera_order);

this->Ui->num_cam_0->setMaximum(GlobalObjects->absCameras);
this->Ui->num_cam_1->setMaximum(GlobalObjects->absCameras);
this->Ui->num_cam_2->setMaximum(GlobalObjects->absCameras);
this->Ui->num_cam_3->setMaximum(GlobalObjects->absCameras);
this->Ui->num_cam_4->setMaximum(GlobalObjects->absCameras);
this->Ui->num_cam_5->setMaximum(GlobalObjects->absCameras);

}

void C_frm_Camera_Positioning::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
 this->Zaehler = 0;
 for (int i = 0; i < GlobalObjects->absCameras; i++)
   {
   Main->Camera_manager->camera_vector[i]->set_idle (true);
   }

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
this->close();
}


void C_frm_Camera_Positioning::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
    if (Zaehler > TimerWait)
      {
      pthread_mutex_lock(lock);
      this->Main->Camera_manager->getVecImgShow();
      switch (this->cameras_in_use)
        {
        case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          break;

        case 2:
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          break;

        case 4:
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
          break;

        case 6:
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_0->value()], this->Ui->lbl_cam_0);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_1->value()], this->Ui->lbl_cam_1);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_2->value()], this->Ui->lbl_cam_2);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_3->value()], this->Ui->lbl_cam_3);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_4->value()], this->Ui->lbl_cam_4);
          FillMat2Lbl(*this->Main->Camera_manager->getVecImgShow()[this->Ui->num_cam_5->value()], this->Ui->lbl_cam_5);
          break;
        }
      pthread_mutex_unlock(lock);
      }
}

void C_frm_Camera_Positioning::on_bt_apply_clicked()
{
  //TODO NEED WORKS
    std::vector<Camera::C_Camera*> camera_vector_temp;
    camera_vector_temp.resize (cameras_in_use);
    //TODO Need way to stop Taktgeber
    this->Taktgeber->stop();
    this->Ui->bt_apply->setEnabled(false);

    std::vector<int> camera_list;

    switch (this->cameras_in_use)
      {
      case 1:   //Nur zu Testzwecken f�r die Laptopverwendung

        camera_list.push_back (this->Ui->num_cam_0->value());

        this->Ui->num_cam_0->setValue(0);

        break;

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

    this->Main->Camera_manager->mvVecCamera2Temp(camera_vector_temp);
    for (int i = 0; i < cameras_in_use; i++)
      {
      this->Main->Camera_manager->load_camera_calibration (i);
      this->Main->Camera_manager->load_camera_settings (i);
      }
    this->Main->Camera_manager->save_camera_positioning (camera_list);


    TimerWait                = Zaehler + 5;
    this->Taktgeber->start();
}

void C_frm_Camera_Positioning::set_num_value()
  {
  switch (this->cameras_in_use)
    {
    case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
      this->Ui->num_cam_0->setValue(0);
      break;

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
  switch (this->cameras_in_use)
    {
    case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
      this->Ui->num_cam_0->setValue(camera_list[0]);
      break;

    case 2:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      break;

    case 4:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      break;

    case 6:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      this->Ui->num_cam_4->setValue(camera_list[4]);
      this->Ui->num_cam_5->setValue(camera_list[5]);
      break;
    }
  }//set_numUD_value

void C_frm_Camera_Positioning::FillMat2Lbl(cv::Mat& img, QLabel* label)
{
    QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

label->setPixmap(QPixmap::fromImage(imgIn));
}



