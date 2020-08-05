#include "headers/frm_camera_calibration.h"
using namespace frm_Camera_Calibration;

C_frm_Camera_Calibration::C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
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
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 100;
    this->lock                  = new pthread_mutex_t;


}

C_frm_Camera_Calibration::~C_frm_Camera_Calibration()
{
    delete (lock);
    this->Taktgeber_Intervall = 0;
    delete (this->Taktgeber);

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
pthread_mutex_init(lock, NULL);
this->Zaehler             = 0;
this->cameraID   = 0;
this->Timerwait           = 50;
this->Ui->rb_single_calibration->setChecked(true);

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

void C_frm_Camera_Calibration::Taktgeber_Tick()
  {
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  pthread_mutex_lock(lock);
  switch (method)
    {
    case 0:
      this->Fill_Mat_2_Lbl(*this->Main->Camera_manager->getVecImgShow()[cameraID], this->Ui->lbl_img_single_calibration);
      break;

    case 1:
      this->Fill_Mat_2_Lbl(*this->Main->Camera_manager->getVecImgShow()[cameraID], this->Ui->lbl_img_single_calibration);
      this->Fill_Mat_2_Lbl(*this->Main->Camera_manager->getVecImgShow()[cameraID+1], this->Ui->lbl_img_single_calibration);
      break;
     }
  pthread_mutex_unlock(lock);
   if (this->Main->Camera_manager->getCalibrationDone())
     {
     this->ShowTable();
     }
  }

void C_frm_Camera_Calibration::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
{
QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);

label->setPixmap(QPixmap::fromImage(imgIn));
}


void C_frm_Camera_Calibration::on_bt_start_clicked()
{
    this->Ui->lbl_calibration_running->setVisible(false);
    this->Ui->bt_photo->setVisible(true);
    this->sm_calibration_state             = 0;
    this->calibration_running              = true;

    switch (method)
      {
      case 0:
        sm_Single_camera_calibration();
        break;
      case 1:
        sm_Stereo_camera_calibration();
        break;
      }
    }


void frm_Camera_Calibration::C_frm_Camera_Calibration::on_bt_exit_clicked()
{
this->close();
}

void C_frm_Camera_Calibration::on_num_camera_id_valueChanged(int arg1)
{
    Timerwait = Zaehler + 8;
    this->cameraID = arg1;
}

void C_frm_Camera_Calibration::on_rb_single_calibration_clicked()
{
    this->method                   = 0;
    this->Ui->num_camera_id->setValue(0);
    this->Ui->num_camera_id->setSingleStep(1);
    this->cameraID        = 0;

    this->Ui->rb_stereo_calibration->setChecked(false);
    this->Ui->rb_single_calibration->setChecked(true);

    this->Ui->lbl_img_stereo_left->setVisible(false);
    this->Ui->lbl_img_stereo_left->setVisible(false);

   this->Ui->lbl_img_single_calibration->setVisible(true);

}

void C_frm_Camera_Calibration::on_rb_stereo_calibration_clicked()
{
    this->method                   = 1;
    this->Ui->num_camera_id->setValue(0);
    this->Ui->num_camera_id->setSingleStep(2);
    this->cameraID        = 0;

    this->Ui->rb_stereo_calibration->setChecked(true);
    this->Ui->rb_single_calibration->setChecked(false);

    this->Ui->lbl_img_stereo_left->setVisible(true);
    this->Ui->lbl_img_stereo_left->setVisible(true);

   this->Ui->lbl_img_single_calibration->setVisible(false);

}

void C_frm_Camera_Calibration::on_bt_photo_clicked()
{

}
void C_frm_Camera_Calibration::camera_calibration_thread ()
  {
  switch (method)
    {
    case 0:
      this->Main->Camera_manager->calibrateSingleCamera(this->cameraID,
                                                        this->Ui->txb_edge_width->text().toInt(),
                                                        this->Ui->txb_edge_height->text().toInt(),
                                                        this->Ui->txb_usrInput_images->text().toInt(),
                                                        this->Ui->txb_edge_length->text().toInt());
      break;

    case 1:
      this->Main->Camera_manager->calibrate_stereo_camera (this->cameraID,
                                                           this->Ui->txb_edge_width->text().toInt(),
                                                           this->Ui->txb_edge_height->text().toInt(),
                                                           this->Ui->txb_usrInput_images->text().toInt(),
                                                           this->Ui->txb_edge_length->text().toInt());
      break;
    }
  }

void C_frm_Camera_Calibration::sm_Single_camera_calibration ()
  {
  std::string naming = "../Parameter/Bilder/Camera_Single_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      //this->Main->camera_managed->camera_unmanaged->camera_vector[current_camera_id]->cap->set (cv::CAP_PROP_XI_AEAG,false);
      this->cameraID = this->Ui->num_camera_id->value();
      this->photo_id          = 0;
      //this->photo_interval            =   int::Parse(tb_photo_interval->Text)*10;
      this->photocount_user_input = this->Ui->txb_count_images_to_take->toPlainText().toInt();

      this->Ui->bt_start->setText("Beenden");

      this->sm_calibration_state = 1;
      break;

      //Take pictures
    case 1:
      this->Main->Camera_manager->camera_vector[cameraID]->save_picture (cameraID,photo_id,naming);
      this->Ui->txb_img_count->setText(QString::number(this->photo_id + 1));
      this->photo_id++;

      if (photo_id >= photocount_user_input)
        {
        this->sm_calibration_state = 2;
        }

      break;

    case 2:
      this->Ui->bt_photo->setVisible(false);
      this->calibration_running  = false;
      this->Ui->bt_start->setText("Start");

      this->Main->Camera_manager->SquareSize       = this->Ui->txb_edge_length->toPlainText().toInt();
      this->Main->Camera_manager->numBoards_imgs   = this->photo_id;
      this->Main->Camera_manager->numCornersHeight = this->Ui->txb_edge_height->toPlainText().toInt();
      this->Main->Camera_manager->numCornersWidth  = this->Ui->txb_edge_width->toPlainText().toInt();
      this->Main->Camera_manager->camera_id        = this->cameraID;
      this->Ui->lbl_calibration_running->setVisible(true);
      this->Main->Camera_manager->camera_vector[cameraID]->set_undistord_active (false);

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      //TODO Add threading
      //Thread^ calibrate = gcnew Thread (gcnew ThreadStart (this,&C_frm_CameraCalibration_Single::camera_calibration_thread));
      std::thread calibrate(&C_frm_Camera_Calibration::camera_calibration_thread, this);
      photo_id = 0;


      break;
    }
  }

void C_frm_Camera_Calibration::sm_Stereo_camera_calibration ()
  {
  std::string naming = "../Parameter/Bilder/Camera_Stereo_Calibration_";
  switch (this->sm_calibration_state)
    {
    case 0:
      this->Main->Camera_manager->camera_vector[cameraID]->cap->set (cv::CAP_PROP_XI_AEAG,false);
      this->cameraID = this->Ui->num_camera_id->value();
      photo_id          = 0;
      //photo_interval            =   int::Parse(tb_photo_interval->Text)*10;
      this->photocount_user_input = this->Ui->txb_count_images_to_take->toPlainText().toInt();

      this->Ui->bt_start->setText("Beenden");

      this->sm_calibration_state = 1;
      break;

      //Take pictures
    case 1:
      this->Main->Camera_manager->camera_vector[cameraID]->save_picture (cameraID,photo_id,naming);
      this->Main->Camera_manager->camera_vector[cameraID]->save_picture (cameraID + 1,photo_id,naming);

      this->Ui->txb_img_count->                                     setText(QString::number(this->photo_id + 1));
      this->photo_id++;

      if (photo_id >= photocount_user_input)
        {
        this->sm_calibration_state = 2;
        }

      break;

    case 2:
      this->Ui->bt_photo->setVisible(false);
      this->calibration_running  = false;
      this->Ui->bt_start->setText("Start");

      this->Main->Camera_manager->SquareSize       = this->Ui->txb_edge_length->toPlainText().toInt();
      this->Main->Camera_manager->numBoards_imgs   = this->photo_id;
      this->Main->Camera_manager->numCornersHeight = this->Ui->txb_edge_height->toPlainText().toInt();
      this->Main->Camera_manager->numCornersWidth  = this->Ui->txb_edge_width->toPlainText().toInt();
      this->Main->Camera_manager->camera_id        = this->cameraID;
      this->Ui->lbl_calibration_running->setVisible(true);
      this->Main->Camera_manager->camera_vector[cameraID]->set_undistord_active (false);

      //Starte Hintergrund Thread zur Verarbeitung der aufgenommenen Bilder
      std::thread calibrate(&C_frm_Camera_Calibration::camera_calibration_thread, this);

      photo_id = 0;


      break;
    }
  }
void C_frm_Camera_Calibration::ShowTable()
  {
  switch(method)
  {
   case 0:
      this->Ui->tblv_single_parameters->verticalHeader()->hide();

      this->Ui->tblv_single_parameters->show();
      break;
  case 1:
      this->Ui->tblv_stereo_output->verticalHeader()->hide();
      //this->Ui->tblv_stereo_output->data
      break;
  default:
      return;

  }
  }
