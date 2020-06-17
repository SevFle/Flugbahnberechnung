#include "frm_camera_positioning.h"
using namespace frm_Camera_Positioning;

C_frm_Camera_Positioning::C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_positioning();
    Ui->setupUi(this);
    this->GlobalObjects  = GlobalObjects;
    this->Main           = Main;
    this->cameras_in_use = GlobalObjects->cameras_in_use;
    this->TimerWait      = 0;

}

C_frm_Camera_Positioning::~C_frm_Camera_Positioning()
{
    this->TimerWait = 0;

    this->Main          = nullptr;
    this->GlobalObjects = nullptr;

    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Positioning::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);
this->Zaehler             = 0;
this->TimerWait           = 80;
this->cameras_in_use      = GlobalObjects->cameras_in_use;

if (this->Main->Camera_manager->load_positioning) this->set_numUD_value (*GlobalObjects->camera_order);

this->Ui->num_cam_0->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->num_cam_1->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->num_cam_2->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->num_cam_3->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->num_cam_4->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->num_cam_5->setMaximum(GlobalObjects->cameras_in_use);

}

void C_frm_Camera_Positioning::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning::Taktgeber_Tick);
 this->Zaehler = 0;
 for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
   {
   Main->camera_managed->camera_unmanaged->camera_vector[i]->set_idle (true);
   }

 }

bool               C_frm_Camera_Positioning::eventFilter                                       (QObject* Object, QEvent* Event)
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
void ::C_frm_Camera_Positioning::on_bt_exit_clicked()
{
this->close();
}


void C_frm_Camera_Positioning::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
    if (Zaehler > TimerWait + 30)
      {
      switch (this->cameras_in_use)
        {
        case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
          FillMat2Picturebox (pb_Camera_L1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
          break;

        case 2:
          FillMat2Picturebox (pb_Camera_L1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
          break;

        case 4:
          FillMat2Picturebox (pb_Camera_L1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_L2,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R2,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
          break;

        case 6:
          FillMat2Picturebox (pb_Camera_L1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L1->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R1,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R1->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_L2,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L2->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R2,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R2->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_L3,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_L3->Value)]->cpu_src_img);
          FillMat2Picturebox (pb_Camera_R3,Main->camera_managed->camera_unmanaged->camera_vector[static_cast<int> (nup_Camera_R3->Value)]->cpu_src_img);
          break;
        }
      }
}

void C_frm_Camera_Positioning::C_frm_Camera_Positioning::on_bt_apply_clicked()
{
    std::vector<nmsp_opencv_unmanaged::c_opencv_unmanaged*> camera_vector_temp;
    camera_vector_temp.resize (cameras_in_use);

    this->Taktgeber->Enabled = false;
    this->bt_apply->Enabled  = false;

    std::vector<int> camera_list;

    switch (this->cameras_in_use)
      {
      case 1:   //Nur zu Testzwecken f�r die Laptopverwendung
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (0,static_cast<int> (nup_Camera_L1->Value),camera_vector_temp);

        camera_list.push_back (static_cast<int> (nup_Camera_L1->Value));

        nup_Camera_L1->Value = 0;

        break;

      case 2:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (0,static_cast<int> (nup_Camera_L1->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (1,static_cast<int> (nup_Camera_R1->Value),camera_vector_temp);

        camera_list.push_back (static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R1->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;

        break;

      case 4:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (0,static_cast<int> (nup_Camera_L1->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (1,static_cast<int> (nup_Camera_R1->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (2,static_cast<int> (nup_Camera_L2->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (3,static_cast<int> (nup_Camera_R2->Value),camera_vector_temp);

        camera_list.push_back (static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R1->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_L2->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R2->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;
        nup_Camera_L2->Value = 2;
        nup_Camera_R2->Value = 3;

        break;

      case 6:
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (0,static_cast<int> (nup_Camera_L1->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (1,static_cast<int> (nup_Camera_R1->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (2,static_cast<int> (nup_Camera_L2->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (3,static_cast<int> (nup_Camera_R2->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (4,static_cast<int> (nup_Camera_L3->Value),camera_vector_temp);
        Main->camera_managed->camera_unmanaged->move_camera_vector2temp (5,static_cast<int> (nup_Camera_R3->Value),camera_vector_temp);

        camera_list.push_back (static_cast<int> (nup_Camera_L1->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R1->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_L2->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R2->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_L3->Value));
        camera_list.push_back (static_cast<int> (nup_Camera_R3->Value));

        nup_Camera_L1->Value = 0;
        nup_Camera_R1->Value = 1;
        nup_Camera_L2->Value = 2;
        nup_Camera_R2->Value = 3;
        nup_Camera_L3->Value = 4;
        nup_Camera_R3->Value = 5;

        break;
      }

    this->Main->camera_managed->camera_unmanaged->move_camera_temp2vector (cameras_in_use,camera_vector_temp);
    for (int i = 0; i < cameras_in_use; i++)
      {
      this->Main->camera_managed->camera_unmanaged->load_camera_calibration (i);
      this->Main->camera_managed->camera_unmanaged->load_camera_settings (i);
      }
    this->Main->camera_managed->camera_unmanaged->save_camera_positioning (camera_list);


    TimerWait                = Zaehler + 5;
    this->Taktgeber->Enabled = true;
}

void C_frm_Camera_Positioning::set_num_value()
  {
  switch (this->cameras_in_use)
    {
    case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
      this->Ui->num_cam_0->setValue(0);
      break;

    case 2:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      break;

    case 4:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      this->Ui->num_cam_2->setValue(2);
      this->Ui->num_cam_3->setValue(3);
      break;

    case 6:
      this->Ui->num_cam_0->setValue(0);
      this->Ui->num_cam_1->setValue(1);
      this->Ui->num_cam_2->setValue(2);
      this->Ui->num_cam_3->setValue(3);
      this->Ui->num_cam_4->setValue(4);
      this->Ui->num_cam_5->setValue(5);
      break;
    }
  }//set_numUD_value
void C_frm_Camera_Positioning::set_num_value (std::vector<int> camera_list)
  {
  switch (this->cameras_in_use)
    {
    case 1:   //Nur zu Testzwecken fuer die Laptopverwendung
      this->Ui->num_cam_0->setValue(camera_list[0]);
      break;

    case 2:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      break;

    case 4:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      break;

    case 6:
      this->Ui->num_cam_0->setValue(camera_list[0]);
      this->Ui->num_cam_1->setValue(camera_list[1]);
      this->Ui->num_cam_2->setValue(camera_list[2]);
      this->Ui->num_cam_3->setValue(camera_list[3]);
      this->Ui->num_cam_4->setValue(camera_list[4]);
      this->Ui->num_cam_5->setValue(camera_list[5]);
      break;
    }
  }//set_numUD_value

void C_frm_Camera_Positioning::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
{
label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
}



