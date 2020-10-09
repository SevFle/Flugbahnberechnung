#include "headers/frm_object_tracking.h"
using namespace frm_Object_Tracking;

C_frm_Object_Tracking::C_frm_Object_Tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
    {
    this->Ui = new Ui::C_frm_object_tracking();
    Ui->setupUi(this);
    this->GlobalObjects           = GlobalObjects;
    this->Main                    = Main;
    this->Taktgeber               = new QTimer;
    this->pData                   = nullptr;
    this->Zaehler                 = 0;
    this->Taktgeber_Intervall     = 0;
    this->cameraID                = 0;
    this->Plotter_Intervall       = 0;
    this->Zaehler_old             = 0;

    this->container = QWidget::createWindowContainer(this->Main->cameraManager->trackingManager->dataPlotter->graph);
    this->Ui->horizontalLayout->addWidget(container);


    }

C_frm_Object_Tracking::~C_frm_Object_Tracking()
  {
  delete (this->container);
  this->Zaehler_old             = 0;
  this->Plotter_Intervall       = 0;
  this->cameraID                = 0;
  this->Taktgeber_Intervall     = 0;
  this->Zaehler                 = 0;
  if(this->pData != nullptr)
    {
      delete (this->pData);
      this->pData = nullptr;
    }

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
  this->Plotter_Intervall = 50;
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
/************************************** Nicht Ã¶ffentliche QT-Slots*(*it) = *****************************/
void ::C_frm_Object_Tracking::on_bt_exit_clicked()
  {
  if(this->Main->cameraManager->getFilterFlags()->getTrackingActive())
    {
    this->on_bt_start_clicked();
    }
  this->Ui->lbl_thread_running->              setEnabled  (false);
  this->Ui->bt_start->                        setText     ("Start Tracking");
  this->Main->cameraManager->getFilterFlags()->setRoiAdjustment(false);
  this->Main->cameraManager->getFilterFlags()->setTrackingActive(false);
  this->close();
  }


void C_frm_Object_Tracking::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  if(this->Main->cameraManager->pipelineQue->try_pop(pData))
    {
    this->Main->frm_Main->FillMat2Lbl(pData->cpuFinal[0], this->Ui->lbl_img_left);
    this->Main->frm_Main->FillMat2Lbl(pData->cpuFinal[1], this->Ui->lbl_img_right);
    if(pData->found)
      {
      this->Ui->label_found->setText(QString("Tracking"));
      this->Ui->txb_position_x->setText (QString::number(pData->objektVektor.X, 'f', 3));
      this->Ui->txb_position_y->setText (QString::number(pData->objektVektor.Y, 'f', 3));
      this->Ui->txb_position_z->setText (QString::number(pData->objektVektor.Z, 'f', 3));

      this->Ui->txb_velocity_x->setText(QString::number(pData->objectVelocity[0], 'f', 3));
      this->Ui->txb_velocity_y->setText(QString::number(pData->objectVelocity[1], 'f', 3));
      this->Ui->txb_velocity_z->setText(QString::number(pData->objectVelocity[2], 'f', 3));

      this->Ui->txb_acceleration_x->setText(QString::number(pData->objectAcceleration[0], 'f', 3));
      this->Ui->txb_acceleration_y->setText(QString::number(pData->objectAcceleration[1], 'f', 3));
      this->Ui->txb_acceleration_z->setText(QString::number(pData->objectAcceleration[2], 'f', 3));


        }
    else
      {
      this->Ui->label_found->setText(QString("Not found"));
      this->Ui->txb_position_x->setText (QString::number(0));
      this->Ui->txb_position_y->setText (QString::number(0));
      this->Ui->txb_position_z->setText (QString::number(0));

      this->Ui->txb_velocity_x->setText(QString::number(0));
      this->Ui->txb_velocity_y->setText(QString::number(0));
      this->Ui->txb_velocity_z->setText(QString::number(0));

      this->Ui->txb_acceleration_x->setText(QString::number(0));
      this->Ui->txb_acceleration_y->setText(QString::number(0));
      this->Ui->txb_acceleration_z->setText(QString::number(0));


      }


    this->Ui->txb_activeCamera_0->setText (QString::number(pData->cameraID[0]));
    this->Ui->txb_activeCamera_1->setText (QString::number(pData->cameraID[1]));

    this->Ui->txb_ist_x_L->setText(QString::number(pData->ist_X[0]));
    this->Ui->txb_ist_x_R->setText(QString::number(pData->ist_X[1]));
    this->Ui->txb_ist_y_L->setText(QString::number(pData->ist_Y[0]));
    this->Ui->txb_ist_y_R->setText(QString::number(pData->ist_X[1]));

    this->Ui->txb_fps->              setText(QString::number(pData->fps));
    this->Ui->txb_frametime->        setText(QString::number(pData->frametime.count()));
    this->Ui->txb_quebuffer->        setText(QString::number(pData->queBuffer));
    this->Ui->txb_worker_1->         setText(QString::number(pData->executionTime[0].count()));
    this->Ui->txb_worker_2->         setText(QString::number(pData->executionTime[1].count()));
    this->Ui->txb_worker_3->         setText(QString::number(pData->executionTime[2].count()));
    this->Ui->txb_worker_4->         setText(QString::number(pData->executionTime[3].count()));
    this->Ui->txb_worker_5->         setText(QString::number(pData->executionTime[4].count()));
    this->Ui->txb_worker_6->         setText(QString::number(pData->executionTime[5].count()));
    this->Ui->txb_worker_7->         setText(QString::number(pData->executionTime[6].count()));


    this->Ui->txb_tracker_dt->setText(QString::number(this->Main->cameraManager->trackingManager->getDTime()));

    if(this->Main->cameraManager->getFilterFlags()->getTrackingActive() && this->Zaehler > Plotter_Intervall + Zaehler_old && pData->objektVektor.X != 0 && pData->objektVektor.Y != 0 && pData->objektVektor.Z != 0)
      {
      //Mappe die aktuellen Objektpositionen auf einen QVector um diesen plotten zu können
      QVector3D vec3d;
      vec3d.setX(pData->objektVektor.X);
      vec3d.setY(pData->objektVektor.Y);
      vec3d.setZ(pData->objektVektor.Z);

      this->Main->cameraManager->trackingManager->dataPlotter->addSingleData(vec3d, plotter::series::realValue);

      this->Zaehler_old = Zaehler;
      }
    delete(pData);
    pData = nullptr;
    }
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
  if (!this->Main->cameraManager->getFilterFlags()->getTrackingActive())
    {
    this->Ui->lbl_thread_running->              setEnabled  (true);
    this->Ui->bt_start->                        setText     ("Stop");
      this->Main->cameraManager->pipelineFlush.store(true);
    this->Main->cameraManager->setArrActiveCameras(0,0);
    this->Main->cameraManager->setArrActiveCameras(1,1);
    this->Main->cameraManager->pipelineFlush.store(false);
    this->Main->cameraManager->startTracking();
    }
  else
    {
    this->Ui->lbl_thread_running->              setEnabled  (false);
    this->Ui->bt_start->                        setText     ("Start Tracking");
    this->Main->cameraManager->stopTracking();
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
