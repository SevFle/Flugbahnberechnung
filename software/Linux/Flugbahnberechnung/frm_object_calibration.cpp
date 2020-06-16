#include "frm_object_calibration.h"
using namespace frm_Object_Calibration;

C_frm_Object_Calibration::C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QDialog(parent)
{
    this->Ui = new Ui::C_frm_object_calibration();
    Ui->setupUi(this);
}

C_frm_Object_Calibration::~C_frm_Object_Calibration()
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

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_sigma_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_opening_iterations_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_opening_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_closing_iterations_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_closing_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_closing_iterations_2_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_erode_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_closing_iterations_3_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_dilate_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_closing_iterations_4_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_morph_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_gaussian_sigma_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_bilateral_color_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_bilateral_spatial_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_bilateral_kernelsize_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_hue_min_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_hue_max_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_saturation_min_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_saturation_max_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_value_min_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_value_max_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_objectsize_min_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_sld_objectsize_max_valueChanged(int value)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_num_camera_valueChanged(int arg1)
{

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_bt_exit_clicked()
{

}
