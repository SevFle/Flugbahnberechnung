#include "frm_camera_calibration.h"
using namespace frm_Camera_Calibration;

C_frm_Camera_Calibration::C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QDialog(parent)
{
    this->Ui = new Ui::C_frm_camera_calibration();
    Ui->setupUi(this);
    this->GlobalObjects         = GlobalObjects;
    this->Main                  = Main;
    this->Zaehler               = 0;
    this->cameras_in_use        = 0;
    this->calibration_running   = false;
    this->photo_interval        = 0;
    this->photo_count           = 0;
    this->photo_id              = 0;
    this->intervall             = 0;
    this->photocount_user_input = 3;

}

C_frm_Camera_Calibration::~C_frm_Camera_Calibration()
{
    this->cameras_in_use        = 0;
    this->photocount_user_input = 3;
    this->intervall             = 0;
    this->photo_id              = 0;
    this->photo_interval        = 0;
    this->calibration_running   = false;
    this->cameras_in_use        = 0;
    this->Zaehler               = 0;

    this->Main          = nullptr;
    this->GlobalObjects = nullptr;


    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Calibration::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);

this->Zaehler             = 0;
this->cameras_in_use      = GlobalObjects->cameras_in_use;
this->current_camera_id   = 0;
this->Timerwait           = 50;

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
void ::C_frm_Main::on_bt_exit_clicked()
{
this->close();
}


void C_frm_Main::Taktgeber_Tick()
{
    switch (state)
      {
      case 0:
        this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
        break;
      case 1:
        this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
        if (this->Main->Camera_manager->camera_vector[GlobalObjects->cameras_in_use-1]->is_thread_ready())
          {
          this->Ui->bt_tracking->setEnabled(true);
            this->Ui->bt_camera_calibration->setEnabled(true);
            this->Ui->bt_camera_positioning->setEnabled(true);
          state                          = 0;
          }
        break;

}
}
