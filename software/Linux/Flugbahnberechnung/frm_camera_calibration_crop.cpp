#include "frm_camera_calibration_crop.h"
using namespace frm_Camera_Calibration_Crop;

C_frm_Camera_Calibration_Crop::C_frm_Camera_Calibration_Crop(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_calibration_crop();
    Ui->setupUi(this);
}

C_frm_Camera_Calibration_Crop::~C_frm_Camera_Calibration_Crop()
{
    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Calibration_Crop::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration_Crop::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);
}

void C_frm_Camera_Calibration_Crop::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Calibration_Crop::Taktgeber_Tick);
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
void ::C_frm_Camera_Calibration_Crop::on_bt_exit_clicked()
{
this->close();
}


void C_frm_Camera_Calibration_Crop::Taktgeber_Tick()
{
}
void C_frm_Camera_Positioning::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
{
label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
}

