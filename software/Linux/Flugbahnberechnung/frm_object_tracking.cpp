#include "frm_object_tracking.h"
#include "ui_frm_object_tracking.h"

C_frm_object_tracking::C_frm_object_tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QDialog(parent)
{
    this->Ui = new Ui::C_frm_object_tracking();
    Ui->setupUi(this);
}

C_frm_object_tracking::~C_frm_object_tracking()
{
    delete Ui;
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
