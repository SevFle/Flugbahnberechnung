#include "headers/frm_main.h"
using namespace frm_Main;

C_frm_Main::C_frm_Main(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent)
    : QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_Main();
    Ui->setupUi(this);

    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;

    this->Zaehler = 0;
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 100;
    this->MsgBox = new QMessageBox();
}

C_frm_Main::~C_frm_Main()
{
    delete (MsgBox);
    this->Taktgeber_Intervall = 0;
    delete (this->Taktgeber);
    this->Zaehler = 0;
    this->Main = nullptr;
    this->GlobalObjects = nullptr;
    delete this->Ui;
}

/************************************** QT-Events******************************/
void C_frm_Main::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Main::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);
}

void C_frm_Main::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Main::Taktgeber_Tick);
 this->Zaehler = 0;
 }

bool               C_frm_Main::eventFilter                                       (QObject* Object, QEvent* Event)
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
void ::C_frm_Main::on_bt_exit_clicked()
  {
  if(!this->Main->cameraManager->closeCameras())
    {
    this->MsgBox->setText("Offene Kameraverbindungen konnten nicht geschlossen werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }
  this->close();
  }


void C_frm_Main::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  }

void ::C_frm_Main::on_bt_apply_clicked()
{
 if(!this->Main->cameraManager->openCameras() || GlobalObjects->absCameras % 2 !=0)
        {
        this->MsgBox->setText("Kameras konnten nicht geöffnet werden");
        this->MsgBox->setIcon(QMessageBox::Critical);
        this->MsgBox->exec();
        this->Main->cameraManager->closeCameras();
        return;
        }
      else
        {
        this->Ui->bt_apply->setEnabled     (false);
        this->Ui->bt_tracking->setEnabled(true);
        this->Ui->bt_camera_calibration->setEnabled(true);
        this->Ui->bt_camera_positioning->setEnabled(true);
        this->Ui->bt_camera_pose->setEnabled(true);

        }


}
void frm_Main::C_frm_Main::on_bt_tracking_clicked()
  {
  if(!this->Main->cameraManager->startPipelineTracking(true, true, true, true, true, false, false))
    {
    this->MsgBox->setText("Pipeline konnte nicht gestartet werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }
  this->Main->frm_Main->setEnabled(false);
  //this->Main->frm_Object_Calibration->setWindowModality(Qt::ApplicationModal);
  this->Main->frm_Object_Calibration->show();
  this->Main->frm_Main->setEnabled(true);
  }

void frm_Main::C_frm_Main::on_bt_camera_calibration_clicked()
  {
  if(!this->Main->cameraManager->startPipelineTracking(false, false, false, false, false, false, false))
    {
    this->MsgBox->setText("Thread zur Kamerakalibrierung konnte nicht gestartet werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }

    this->Main->frm_Camera_Calibration->setWindowModality(Qt::ApplicationModal);
    this->Main->frm_Camera_Calibration->show();
  }

void frm_Main::C_frm_Main::on_bt_camera_pose_clicked()
{
    this->Main->frm_Camera_Positioning_Pose->setWindowModality(Qt::ApplicationModal);
    this->Main->frm_Camera_Positioning_Pose->show();
}

void frm_Main::C_frm_Main::on_bt_camera_positioning_clicked()
  {
  if(!this->Main->cameraManager->startThreadCameraPositioning())
    {
    this->MsgBox->setText("Thread zur Kamerapositionierung konnte nicht gestartet werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }
  this->Main->frm_Camera_Positioning->setWindowModality(Qt::ApplicationModal);
  this->Main->frm_Camera_Positioning->show();
  }
