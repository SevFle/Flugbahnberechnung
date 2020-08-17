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
/************************************** Nicht öffentliche QT-Slots******************************/
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
    if (this->Ui->num_cameras->value() % 2 != 0)
      {
      //MessageBox::Show ("Es muss eine gerade Anzahl an Kameras verwendet werden","Fehler",MessageBoxButtons::OK,MessageBoxIcon::Error);
      this->MsgBox->setText("Es muss eine gerade Anzahl an Kameras verwendet werden");
      this->MsgBox->setIcon(QMessageBox::Critical);
      this->MsgBox->exec();
      return;
      }
    else
      {
      GlobalObjects->absCameras = this->Ui->num_cameras->value();
      this->Ui->num_cameras->setEnabled(false);
      this->Ui->bt_apply->setEnabled     (false);

      if(!this->Main->cameraManager->openCameras ())
        {
        this->MsgBox->setText("Kameras konnten nicht ge�ffnet werden");
        this->MsgBox->setIcon(QMessageBox::Critical);
        this->MsgBox->exec();
        return;
        }
      else
        {
        this->Ui->bt_tracking->setEnabled(true);
        this->Ui->bt_camera_calibration->setEnabled(true);
        this->Ui->bt_camera_positioning->setEnabled(true);
        }
    }

}
void frm_Main::C_frm_Main::on_bt_tracking_clicked()
  {
  if(!this->Main->cameraManager->startPipelineTracking())
    {
    this->MsgBox->setText("Pipeline konnte nicht gestartet werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }
  this->Main->frm_Object_Calibration->setWindowModality(Qt::ApplicationModal);
  this->Main->frm_Object_Calibration->show();
  }

void frm_Main::C_frm_Main::on_bt_camera_calibration_clicked()
  {
  if(!this->Main->cameraManager->startThreadCameraPositioning())
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
