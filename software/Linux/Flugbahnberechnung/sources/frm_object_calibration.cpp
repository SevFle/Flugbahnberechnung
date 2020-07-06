#include "headers/frm_object_calibration.h"
using namespace frm_Object_Calibration;

C_frm_Object_Calibration::C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_object_calibration();
    Ui->setupUi(this);
    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;

    camera_id_in_use = 0;
    TimerWait        = 0;
    camera_id_in_use = 0;
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 100;


}

C_frm_Object_Calibration::~C_frm_Object_Calibration()
{
    this->Taktgeber_Intervall = 0;
    delete (this->Taktgeber);

    TimerWait = 0;

    this->Main          = nullptr;
    this->GlobalObjects = nullptr;

    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Object_Calibration::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Object_Calibration::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);

this->Zaehler                   = 0;
this->TimerWait                 = 75;
this->Ui->num_camera->setMaximum(GlobalObjects->cameras_in_use);
this->Ui->sld_hue_min->setValue(0);
this->Ui->sld_hue_max->setValue(50);
this->Ui->sld_saturation_min->setValue(0);
this->Ui->sld_saturation_max->setValue(255);
this->Ui->sld_value_min->setValue(0);
this->Ui->sld_value_max->setValue(255);

this->set_gui();
this->get_camera_settings (0);
}



void C_frm_Object_Calibration::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Object_Calibration::Taktgeber_Tick);
 this->Zaehler = 0;
 cv::destroyAllWindows();

 }

bool               C_frm_Object_Calibration::eventFilter                                       (QObject* Object, QEvent* Event)
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
void ::C_frm_Object_Calibration::on_bt_exit_clicked()
{
    this->Main->frm_Object_Tracking->close();
    for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
      {
      this->Main->Camera_manager->camera_vector[i]->set_idle (true);
      this->Main->Camera_manager->camera_vector[i]->set_undistord_active (false);
      this->Main->Camera_manager->camera_vector[i]->set_filtering_active (false);
      this->Main->Camera_manager->camera_vector[i]->set_show_cropped_image(false);
      this->Main->Camera_manager->camera_vector[i]->set_show_contoured_active(false);
      }
    //TODO Implement proper cv windows handling
    //cv::destroyAllWindows();

this->close();
}


void C_frm_Object_Calibration::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));

    //Initial Wait um das abgreifen nicht vorhandener Bilder zu verhindern
    if (this->Main->Camera_manager->camera_vector[camera_id_in_use]->is_thread_ready())
      {
      this->Fill_Mat_2_Lbl(*Main->Camera_manager->camera_vector[camera_id_in_use]->cpu_src_img, this->Ui->lbl_src_img);
      this->Fill_Mat_2_Lbl(*Main->Camera_manager->camera_vector[camera_id_in_use]->cpu_hsv_filtered, this->Ui->lbl_img_gray);
      this->Fill_Mat_2_Lbl(*Main->Camera_manager->camera_vector[camera_id_in_use]->cpu_masked_img, this->Ui->lbl_hsv_filtered);
      this->Fill_Mat_2_Lbl(*Main->Camera_manager->camera_vector[camera_id_in_use]->cpu_contoured, this->Ui->lbl_img_contoured);
      }
    this->Ui->txb_fps->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_fps()));
    this->Ui->txb_frametime->   setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_frametime().count()));
    this->Ui->txb_delta_x->     setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_delta_x()));
    this->Ui->txb_delta_y->     setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_delta_y()));
    this->Ui->txb_s_x->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_schwerpunkt_x()));
    this->Ui->txb_s_y->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_schwerpunkt_y()));
}


void C_frm_Object_Calibration::on_num_opening_iterations_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_opening_iterations (arg1);

}

void C_frm_Object_Calibration::on_num_opening_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_opening_kernel_size (arg1);
}

void C_frm_Object_Calibration::on_num_closing_iterations_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_closing_iterations (arg1);
}

void C_frm_Object_Calibration::on_num_closing_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_closing_kernel_size (arg1);
}


void C_frm_Object_Calibration::on_num_erode_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_erosion_kernel_size (arg1);
}


void C_frm_Object_Calibration::on_num_dilate_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_dilation_kernel_size (arg1);
}
void C_frm_Object_Calibration::on_num_gaussian_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_gaussian_kernel_size (arg1);
}

void C_frm_Object_Calibration::on_num_morph_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_morph_kernel_size (arg1);
}

void C_frm_Object_Calibration::on_num_gaussian_sigma_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_gaussian_sigma (arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_color_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_bilateral_sigma_color (arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_spatial_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_bilateral_sigma_spatial (arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_kernelsize_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_bilateral_kernel_size (arg1);
}

void C_frm_Object_Calibration::on_sld_hue_min_valueChanged(int value)
{
    if (value > this->Ui->sld_hue_max->value()) this->Ui->sld_hue_min->setValue(this->Ui->sld_hue_max->value() - 1);

    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_hue_min (value);
    this->Ui->txb_hue_min->setText(QString::number(value));

}

void C_frm_Object_Calibration::on_sld_hue_max_valueChanged(int value)
{
    if (this->Ui->sld_hue_min->value() > value) this->Ui->sld_hue_max->setValue(this->Ui->sld_hue_min->value() + 1);

    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_hue_max (value);
    this->Ui->txb_hue_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_saturation_min_valueChanged(int value)
{
    if (this->Ui->sld_saturation_min->value() > this->Ui->sld_saturation_max->value()) this->Ui->sld_saturation_min->setValue(this->Ui->sld_saturation_max->value() - 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_saturation_min (value);
    this->Ui->txb_saturation_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_saturation_max_valueChanged(int value)
{
    if (this->Ui->sld_saturation_min->value() > this->Ui->sld_saturation_max->value()) this->Ui->sld_saturation_max->setValue(this->Ui->sld_saturation_min->value() + 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_saturation_max (value);
    this->Ui->txb_saturation_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_value_min_valueChanged(int value)
{
    if (value > this->Ui->sld_value_max->value()) this->Ui->sld_value_min->setValue(this->Ui->sld_value_max->value() - 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_value_min (value);
    this->Ui->txb_value_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_value_max_valueChanged(int value)
{
    if (this->Ui->sld_value_min->value() > this->Ui->sld_value_max->value()) this->Ui->sld_value_max->setValue(this->Ui->sld_value_min->value() + 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_value_max (value);
    this->Ui->txb_value_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_objectsize_min_valueChanged(int value)
{
    if (value > this->Ui->sld_objectsize_max->value()) this->Ui->sld_objectsize_min->setValue(this->Ui->sld_objectsize_max->value() - 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_object_size_min (value);
    this->Ui->txb_objectsize_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_objectsize_max_valueChanged(int value)
{
    if (this->Ui->sld_objectsize_min->value() > this->Ui->sld_objectsize_max->value()) this->Ui->sld_objectsize_max->setValue(this->Ui->sld_objectsize_min->value() + 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_object_size_max (value);
    this->Ui->txb_objectsize_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_num_camera_valueChanged(int arg1)
{
    TimerWait              = Zaehler + 100;
    this->camera_id_in_use = arg1;
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_idle (false);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_show_cropped_image (false);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_undistord_active (true);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_filtering_active (true);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_show_contoured_active (true);

    this->get_camera_settings (arg1);
}



void C_frm_Object_Calibration::on_num_dilate_iterations_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_dilation_iterations (arg1);
}

void C_frm_Object_Calibration::on_num_erode_iterations_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_erosion_iterations (arg1);
}

void C_frm_Object_Calibration::on_num_morph_iterations_valueChanged(int arg1)
{
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_morph_iterations (arg1);
}

void C_frm_Object_Calibration::on_bt_apply_all_clicked()
{
    for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
      {
      this->Main->Camera_manager->camera_vector[i]->set_value_min (this->Ui->sld_value_min->value());
      this->Main->Camera_manager->camera_vector[i]->set_value_max (this->Ui->sld_value_max->value());

      this->Main->Camera_manager->camera_vector[i]->set_saturation_min (this->Ui->sld_saturation_min->value());
      this->Main->Camera_manager->camera_vector[i]->set_saturation_max (this->Ui->sld_saturation_max->value());

      this->Main->Camera_manager->camera_vector[i]->set_hue_min (this->Ui->sld_hue_min->value());
      this->Main->Camera_manager->camera_vector[i]->set_hue_max (this->Ui->sld_hue_max->value());

      this->Main->Camera_manager->camera_vector[i]->set_opening_iterations (this->Ui->num_opening_iterations->value());
      this->Main->Camera_manager->camera_vector[i]->set_opening_kernel_size (this->Ui->num_opening_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_closing_iterations (this->Ui->num_closing_iterations->value());
      this->Main->Camera_manager->camera_vector[i]->set_closing_kernel_size (this->Ui->num_closing_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_erode_active (this->Ui->chkb_erode->isChecked());
      this->Main->Camera_manager->camera_vector[i]->set_erosion_iterations (this->Ui->num_erode_iterations->value());
      this->Main->Camera_manager->camera_vector[i]->set_erosion_kernel_size (this->Ui->num_erode_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_dilate_active (this->Ui->chkb_dilate->isChecked());
      this->Main->Camera_manager->camera_vector[i]->set_dilation_iterations (this->Ui->num_dilate_iterations->value());
      this->Main->Camera_manager->camera_vector[i]->set_dilation_kernel_size (this->Ui->num_dilate_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_morph_active (this->Ui->chkb_morph->isChecked());
      this->Main->Camera_manager->camera_vector[i]->set_morph_iterations (this->Ui->num_morph_iterations->value());
      this->Main->Camera_manager->camera_vector[i]->set_morph_kernel_size (this->Ui->num_morph_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_gaussian_sigma (this->Ui->num_gaussian_sigma->value());
      this->Main->Camera_manager->camera_vector[i]->set_gaussian_kernel_size (this->Ui->num_gaussian_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_bilateral_active (this->Ui->chkb_bilateral->isChecked());
      this->Main->Camera_manager->camera_vector[i]->set_bilateral_sigma_color (Ui->num_bilateral_color->value());
      this->Main->Camera_manager->camera_vector[i]->set_bilateral_sigma_spatial (Ui->num_bilateral_spatial->value());
      this->Main->Camera_manager->camera_vector[i]->set_bilateral_kernel_size (this->Ui->num_dilate_kernelsize->value());

      this->Main->Camera_manager->camera_vector[i]->set_object_size_min (this->Ui->sld_objectsize_min->value());
      this->Main->Camera_manager->camera_vector[i]->set_object_size_max (this->Ui->sld_objectsize_min->value());


      this->Main->Camera_manager->save_camera_settings (i);
      }
}

void C_frm_Object_Calibration::set_gui()
{
    this->Ui->sld_hue_min->setMinimum(0);
    this->Ui->sld_hue_min->setMaximum(179);

    this->Ui->sld_hue_max->setMinimum(0);
    this->Ui->sld_hue_max->setMaximum(179);

    this->Ui->sld_saturation_min->setMinimum(0);
    this->Ui->sld_saturation_min->setMaximum(255);

    this->Ui->sld_saturation_max->setMinimum(0);
    this->Ui->sld_saturation_max->setMaximum(255);

    this->Ui->sld_value_min->setMinimum(0);
    this->Ui->sld_value_min->setMaximum(255);

    this->Ui->sld_value_max->setMinimum(0);
    this->Ui->sld_value_max->setMaximum(255);

    this->Ui->sld_objectsize_min->setMinimum(0);
    this->Ui->sld_objectsize_min->setMaximum (479999);

    this->Ui->sld_objectsize_max->setMinimum(0);
    this->Ui->sld_objectsize_max->setMaximum (480000);

    this->Ui->num_erode_iterations->setMinimum(0);
    this->Ui->num_erode_iterations->setMaximum(10);

    this->Ui->num_dilate_iterations->setMinimum(0);
    this->Ui->num_dilate_iterations->setMaximum(10);

    this->Ui->num_opening_iterations->setMinimum(0);
    this->Ui->num_opening_iterations->setMaximum(10);

    this->Ui->num_bilateral_color->setMinimum(0);
    this->Ui->num_bilateral_color->setMaximum(10);

    this->Ui->num_morph_iterations->setMinimum(0);
    this->Ui->num_morph_iterations->setMaximum(10);

    this->Ui->num_erode_kernelsize->setMinimum(1);
    this->Ui->num_erode_kernelsize->setMaximum(10);

    this->Ui->num_dilate_kernelsize->setMinimum(1);
    this->Ui->num_dilate_kernelsize->setMaximum(10);

    this->Ui->num_opening_kernelsize->setMinimum(1);
    this->Ui->num_opening_kernelsize->setMaximum(10);

    this->Ui->num_closing_kernelsize->setMinimum(1);
    this->Ui->num_closing_kernelsize->setMaximum(10);

    this->Ui->num_bilateral_kernelsize->setMinimum(1);
    this->Ui->num_bilateral_kernelsize->setMaximum(10);

    this->Ui->num_morph_kernelsize->setMinimum (1);
    this->Ui->num_morph_kernelsize->setMaximum(10);
}

void C_frm_Object_Calibration::on_bt_apply_clicked()
{
    this->Main->Camera_manager->save_camera_settings (this->camera_id_in_use);
}

void C_frm_Object_Calibration::on_chkb_dilate_stateChanged(int arg1)
{
    if (dilate_active == false)
      {
      this->dilate_active = true;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_dilate_active (true);
      this->Ui->num_dilate_iterations->setEnabled(true);
      this->Ui->num_dilate_kernelsize->setEnabled(true);
      }
    else if (dilate_active == true)
      {
      dilate_active = false;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_dilate_active (false);
      this->Ui->num_dilate_iterations->setEnabled(false);
      this->Ui->num_dilate_kernelsize->setEnabled(false);
      }

}

void C_frm_Object_Calibration::on_chkb_morph_stateChanged(int arg1)
{
    if (morph_active == false)
      {
      this->morph_active = true;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_morph_active (true);
      this->Ui->num_morph_iterations->setEnabled(true);
      this->Ui->num_morph_kernelsize->setEnabled(true);
      }
    else if (morph_active == true)
      {
      morph_active = false;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_morph_active (false);
      this->Ui->num_morph_iterations->setEnabled(false);
      this->Ui->num_morph_kernelsize->setEnabled(false);
      }

}


void C_frm_Object_Calibration::on_chkb_erode_stateChanged(int arg1)
{
    if (erode_active == false)
      {
      this->erode_active = true;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_erode_active (true);
      this->Ui->num_erode_iterations->setEnabled(true);
      this->Ui->num_erode_kernelsize->setEnabled(true);
      }
    else if (erode_active == true)
      {
      this->erode_active = false;
      this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_erode_active (false);
      this->Ui->num_erode_iterations->setEnabled(false);
      this->Ui->num_erode_kernelsize->setEnabled(false);
      }

}
void C_frm_Object_Calibration::get_camera_settings (int camera_id)
  {
  this->Ui->sld_hue_min->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_hue_min());
  this->Ui->sld_hue_max->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_hue_max());

  this->Ui->sld_saturation_min->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_saturation_min());
  this->Ui->sld_saturation_max->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_saturation_max());

  this->Ui->sld_value_min->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_value_min());
  this->Ui->sld_value_max->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_value_max());

  this->Ui->num_opening_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_opening_iterations());
  this->Ui->num_opening_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_opening_kernel_size());

  this->Ui->num_closing_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_closing_iterations());
  this->Ui->num_closing_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_closing_kernel_size());

  this->Ui->chkb_erode->setCheckState(Qt::CheckState(this->Main->Camera_manager->camera_vector[camera_id]->is_erode_active()));
  this->Ui->num_erode_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_erosion_iterations());
  this->Ui->num_erode_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_erosion_kernel_size());

  this->Ui->chkb_dilate->setCheckState(Qt::CheckState(this->Main->Camera_manager->camera_vector[camera_id]->is_dilate_active()));
  this->Ui->num_dilate_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_dilation_iterations());
  this->Ui->num_dilate_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_dilation_kernel_size());

  this->Ui->chkb_morph->setCheckState(Qt::CheckState(this->Main->Camera_manager->camera_vector[camera_id]->is_morph_active()));
  this->Ui->num_morph_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_morph_iterations());
  this->Ui->num_morph_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_morph_kernel_size());

  this->Ui->num_gaussian_sigma->setValue (Main->Camera_manager->camera_vector[camera_id]->get_gaussian_sigma());
  this->Ui->num_gaussian_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_gaussian_kernel_size());

  this->Ui->chkb_bilateral->setCheckState(Qt::CheckState(this->Main->Camera_manager->camera_vector[camera_id]->is_bilateral_active()));
  this->Ui->num_bilateral_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_kernel_size());
  this->Ui->num_bilateral_spatial->setValue (this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_sigma_spatial());
  this->Ui->num_bilateral_color->setValue (this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_sigma_color());

  this->Ui->sld_objectsize_min->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_object_size_min());
  this->Ui->sld_objectsize_max->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_object_size_max());
  }




void frm_Object_Calibration::C_frm_Object_Calibration::on_bt_tracking_clicked()
{
    for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
      {
      this->Main->Camera_manager->camera_vector[i]->set_idle (false);
      this->Main->Camera_manager->camera_vector[i]->set_show_cropped_image (false);
      this->Main->Camera_manager->camera_vector[i]->set_undistord_active (true);
      this->Main->Camera_manager->camera_vector[i]->set_filtering_active (true);
      }
    //TODO Open Form
    //this->Main->frm_Object_Tracking->setModal();

}

void frm_Object_Calibration::C_frm_Object_Calibration::on_chkb_bilateral_stateChanged(int arg1)
{
    if (bilateral_active == false)
      {
      this->bilateral_active = true;
      this->Ui->num_bilateral_color->setEnabled(true);
      this->Ui->num_bilateral_spatial->setEnabled(true);
      this->Ui->num_bilateral_kernelsize->setEnabled(true);
      }
    else if (bilateral_active == true)
      {
      this->bilateral_active = false;
        this->Ui->num_bilateral_color->setEnabled(false);
        this->Ui->num_bilateral_spatial->setEnabled(false);
        this->Ui->num_bilateral_kernelsize->setEnabled(false);
      }
}
void C_frm_Object_Calibration::Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label)
{
label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
}

