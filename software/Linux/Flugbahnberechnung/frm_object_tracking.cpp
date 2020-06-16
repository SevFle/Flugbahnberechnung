#include "frm_object_tracking.h"
using namespace frm_Object_Tracking;

C_frm_Object_Tracking::C_frm_Object_Tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QDialog(parent)
{
    this->Ui = new Ui::C_frm_object_tracking();
    Ui->setupUi(this);
    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;
    this->Zaehler       = 0;
    this->TimerWait     = 0;


}

C_frm_Object_Tracking::~C_frm_Object_Tracking()
{
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
this->installEventFilter(this);

this->TimerWait          = 60;
this->Main->Camera_manager->camera_vector[0]->set_undistord_active (true);
this->Main->Camera_manager->camera_vector[1]->set_undistord_active (true);
this->Main->Camera_manager->camera_vector[0]->set_filtering_active (true);
this->Main->Camera_manager->camera_vector[1]->set_filtering_active (true);
this->Ui->num_camera_id->setMaximum(GlobalObjects->cameras_in_use);

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
/************************************** Nicht öffentliche QT-Slots******************************/
void ::C_frm_Object_Tracking::on_bt_exit_clicked()
{
    this->Main->Camera_manager->tracking_active = false;
    //this->Tracking->Join();
    this->close();
}


void C_frm_Object_Tracking::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
if (this->Zaehler > this->TimerWait)
  {
    //TODO Display images
  this->FillMat2Picturebox (pb_cam_left,*this->Main->camera_managed->camera_unmanaged->camera_vector[this->camera_id_in_use]->cpu_contoured);
  this->FillMat2Picturebox (pb_cam_right,*this->Main->camera_managed->camera_unmanaged->camera_vector[this->camera_id_in_use + 1]->cpu_contoured);
  if (this->Main->camera_managed->camera_unmanaged->tracking_active)
    {
    txb_object_pos_x->Text = System::String::Format ("{0:0}",this->Main->camera_managed->camera_unmanaged->tracked_data->positionsvektor.X);
    txb_object_pos_y->Text = System::String::Format ("{0:0}",this->Main->camera_managed->camera_unmanaged->tracked_data->positionsvektor.Y);
    txb_object_pos_z->Text = System::String::Format ("{0:0}",this->Main->camera_managed->camera_unmanaged->tracked_data->positionsvektor.Z);
    }
  }

//Get Current Object Position
}

void C_frm_Object_Tracking::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
{
label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
}

void frm_Object_Tracking::C_frm_Object_Tracking::on_bt_start_clicked()
{
    this->TimerWait = Zaehler + 30;
    if (!this->Main->Camera_manager->tracking_active)
      {
      this->Main->Camera_manager->tracking_active = true;
      this->Ui->lbl_thread_running->setEnabled(true);
        //TODO Rework Threading
      this->Tracking = new std::thread;


      this->Ui->bt_start->setText("Stop");
      }
    else
      {
      this->Ui->lbl_thread_running->setEnabled(false);
      this->Main->Camera_manager->tracking_active = false;
      //this->Tracking->Join();
      this->Ui->bt_start->setText("Start Tracking");
      }

}


void frm_Object_Tracking::C_frm_Object_Tracking::on_num_camera_id_valueChanged(int arg1)
{

}
