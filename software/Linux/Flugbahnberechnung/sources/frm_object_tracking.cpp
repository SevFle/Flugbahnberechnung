#include "headers/frm_object_tracking.h"
using namespace frm_Object_Tracking;

C_frm_Object_Tracking::C_frm_Object_Tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
    {
    this->Ui = new Ui::C_frm_object_tracking();
    Ui->setupUi(this);
    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;
    this->Zaehler       = 0;
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 100;
    this->container = QWidget::createWindowContainer(this->Main->cameraManager->trackingManager->dataPlotter->graph);
    this->Ui->horizontalLayout->addWidget(container);
    }

C_frm_Object_Tracking::~C_frm_Object_Tracking()
  {
  delete (container);
  this->Taktgeber_Intervall = 0;
  delete (this->Taktgeber);

  this->Main          = nullptr;
  this->GlobalObjects = nullptr;
  delete Ui;
  }


/************************************** QT-Events******************************/
void C_frm_Object_Tracking::showEvent(QShowEvent* ShowEvent)
  {
  Q_UNUSED(ShowEvent)
  this->Zaehler = 0;
  connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Object_Tracking::Taktgeber_Tick);
  this->Taktgeber->start(this->Taktgeber_Intervall);
  this->showNormal();
}

void C_frm_Object_Tracking::closeEvent(QCloseEvent* CloseEvent)
  {
  Q_UNUSED(CloseEvent);
  this->removeEventFilter(this);
  this->Taktgeber->stop();
  disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Object_Tracking::Taktgeber_Tick);
  this->Zaehler = 0;
  }

bool               C_frm_Object_Tracking::eventFilter                                       (QObject* Object, QEvent* Event)
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
/************************************** Nicht öffentliche QT-Slots*(*it) = *****************************/
void ::C_frm_Object_Tracking::on_bt_exit_clicked()
  {
  this->Ui->lbl_thread_running->              setEnabled  (false);
  this->Main->cameraManager->trackingManager->setAlive    (false);
  this->Ui->bt_start->                        setText     ("Start Tracking");
  this->Main->cameraManager->getFilterFlags()->setObjectDetection(false);
  this->Main->cameraManager->getFilterFlags()->setRoiAdjustment(false);
  this->Main->cameraManager->getFilterFlags()->setTrackingActive(false);
  this->close();
  }


void C_frm_Object_Tracking::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  if(this->Main->cameraManager->pipelineQue->try_pop(pData))
    {
    this->Fill_Mat_2_Lbl(pData->cpuUndistortedImg[0], this->Ui->lbl_img_left);
    this->Fill_Mat_2_Lbl(pData->cpuUndistortedImg[1], this->Ui->lbl_img_right);


    //TODO Add method to display current coordinates
    this->Ui->txb_position_x->setText (QString::number(pData->objektVektor.X));
    this->Ui->txb_position_y->setText (QString::number(pData->objektVektor.Y));
    this->Ui->txb_position_z->setText (QString::number(pData->objektVektor.Z));

    this->Ui->txb_activeCamera->setText (QString::number(pData->cameraID[0]));
    delete(pData);
    }
    //Get Current Object Position
  }
void C_frm_Object_Tracking::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
  {
  if(img.empty()) return;
  if(img.type()!= 0)
    {
    QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
    label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
    return;
    }
  QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
  label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
  }

void frm_Object_Tracking::C_frm_Object_Tracking::on_bt_start_clicked()
  {
  if (!this->Main->cameraManager->trackingManager->getAlive())
    {
    this->Ui->lbl_thread_running->              setEnabled  (true);
    this->Ui->bt_start->                        setText     ("Stop");
    this->Main->cameraManager->trackingManager->setAlive    (true);

    this->Main->cameraManager->startTracking();
    }
  else
    {
    this->Ui->lbl_thread_running->              setEnabled  (false);
    this->Main->cameraManager->trackingManager->setAlive    (false);
    this->Ui->bt_start->                        setText     ("Start Tracking");
    this->Main->cameraManager->getFilterFlags()->setObjectDetection(false);
    this->Main->cameraManager->getFilterFlags()->setRoiAdjustment(false);
    this->Main->cameraManager->getFilterFlags()->setTrackingActive(false);

    }
}


void frm_Object_Tracking::C_frm_Object_Tracking::on_num_camera_id_valueChanged(int arg1)
{
this->cameraID = arg1;
  }

void C_frm_Object_Tracking::setTaktgeber_Intervall(int value)
  {
  Taktgeber_Intervall = value;
  }
