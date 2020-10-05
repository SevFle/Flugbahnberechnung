#include "headers/frm_main.h"
using namespace frm_Main;

C_frm_Main::C_frm_Main(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent)
    : QMainWindow(parent)
  {
  this->Ui = new Ui::C_frm_Main();
  Ui->setupUi(this);

  this->GlobalObjects = GlobalObjects;
  this->Main          = Main;
  this->MsgBox = new QMessageBox;
  this->Taktgeber = new QTimer;
  this->Qimg = new QImage;
  this->QPixImg = new QPixmap;

  this->Taktgeber_Intervall = 0;
  this->Zaehler = 0;
  }

C_frm_Main::~C_frm_Main()
  {
  this->Zaehler = 0;
  this->Taktgeber_Intervall = 0;

  delete (this->QPixImg);
  delete (this->Qimg);
  delete (this->Taktgeber);
  delete (this->MsgBox);
  this->Main = nullptr;
  this->GlobalObjects = nullptr;
  delete this->Ui;
  }

/************************************** QT-Events******************************/
void C_frm_Main::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
    this->Zaehler                           = 0;
    this->Taktgeber_Intervall               = 25;
this->Taktgeber_Intervall = 100;
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
 if(!this->Main->cameraManager->openCameras() || GlobalObjects->absCameras % 2 !=0 || GlobalObjects->absCameras == 0)
        {
        this->MsgBox->setText("Kameras konnten nicht ge�ffnet werden");
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
  this->GlobalObjects->watchdog = new watchdog::C_watchdog(100, this->Main->cameraManager->pipelineDone,
                                                             this->Main->cameraManager->getCamThread(),
                                                             [&]{this->Main->cameraManager->startPipelineTracking();});

  this->Main->cameraManager->getFilterFlags()->undistordActive        = true;
  this->Main->cameraManager->getFilterFlags()->openActive             = true;
  this->Main->cameraManager->getFilterFlags()->filterActive           = true;
  this->Main->cameraManager->getFilterFlags()->objectDetectionActive  = true;
  this->Main->cameraManager->getFilterFlags()->closeActive            = true;
  this->Main->cameraManager->getFilterFlags()->roiAdjustmentActive    = false;
  this->Main->cameraManager->getFilterFlags()->trackingActive         = false;
  this->Main->cameraManager->setRoiStatus(objectFound);
  if(!this->Main->cameraManager->startPipelineTracking())
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
  this->GlobalObjects->watchdog = new watchdog::C_watchdog(100, this->Main->cameraManager->pipelineDone,
                                                               this->Main->cameraManager->getCamThread(),
                                                               [&]{this->Main->cameraManager->startPipelineTracking();});
  this->Main->cameraManager->getFilterFlags()->undistordActive        = false;
  this->Main->cameraManager->getFilterFlags()->openActive             = false;
  this->Main->cameraManager->getFilterFlags()->filterActive           = false;
  this->Main->cameraManager->getFilterFlags()->objectDetectionActive  = false;
  this->Main->cameraManager->getFilterFlags()->closeActive            = false;
  this->Main->cameraManager->getFilterFlags()->roiAdjustmentActive    = false;
  this->Main->cameraManager->getFilterFlags()->trackingActive         = false;

  if(!this->Main->cameraManager->startPipelineTracking())
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
  this->GlobalObjects->watchdog = new watchdog::C_watchdog(100, this->Main->cameraManager->positioningDone,
                                         this->Main->cameraManager->getCamThread(),
                                         [&]{this->Main->cameraManager->startThreadCameraPositioning();});

  if(!this->Main->cameraManager->startThreadCameraPositioning())
    {


    this->MsgBox->setText("Thread zur Kamerapositionierung konnte nicht gestartet werden");
    this->MsgBox->setIcon(QMessageBox::Critical);
    this->MsgBox->exec();
    return;
    }
  this->Main->frm_Camera_Positioning->setWindowModality(Qt::ApplicationModal);
  this->Main->frm_Camera_Positioning->show();
  delete(this->GlobalObjects->watchdog);
  }

void  frm_Main::C_frm_Main::FillMat2Lbl(cv::Mat& img, QLabel* label)
  {
  cv::Mat* imgPtr = &img;
  if(imgPtr == nullptr)
    return;
  else if(img.empty())
    return;
  else
    {
    *this->Qimg = this->cvMatToQImage(img);
    this->QPixImg->convertFromImage(*this->Qimg);
    label->setPixmap(QPixImg->scaled(label->size(), Qt::KeepAspectRatio));
    }
  }
inline QImage   frm_Main::C_frm_Main::cvMatToQImage( const cv::Mat &inMat )
   {
   switch ( inMat.type() )
     {
     // 8-bit, 4 channel
     case CV_8UC4:
       {
       QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
       QImage copy(image);
       copy.bits(); //enforce deep copy
       return copy;
       }
     // 8-bit, 3 channel
     case CV_8UC3:
       {
       QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
       return image.rgbSwapped();
       }
     // 8-bit, 1 channel
     case CV_8UC1:
       {
       static QVector<QRgb>  sColorTable;
       // only create our color table once
      if ( sColorTable.isEmpty() )
        {
        for ( int i = 0; i < 256; ++i )
              sColorTable.push_back( qRgb( i, i, i ) );
        }
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
        QImage copy(image);
        copy.bits(); //enforce deep copy
        return copy;
       }
     default:
       qWarning() << "***ERROR*** ::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
       break;
      }
      return QImage();
   }


