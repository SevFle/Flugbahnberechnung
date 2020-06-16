#include "frm_object_calibration.h"
using namespace frm_Object_Calibration;

C_frm_Object_Calibration::C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QDialog(parent)
{
    this->Ui = new Ui::C_frm_object_calibration();
    Ui->setupUi(this);
    this->GlobalObjects = GlobalObjects;
    this->Main          = Main;

    camera_id_in_use = 0;
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


    TimerWait        = 0;
    camera_id_in_use = 0;

}

C_frm_Object_Calibration::~C_frm_Object_Calibration()
{
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
/*
trb_hue_min->Minimum = 0;
trb_hue_min->Maximum = 179;

trb_hue_max->Minimum = 0;
trb_hue_max->Maximum = 179;

trb_saturation_min->Minimum = 0;
trb_saturation_min->Maximum = 255;

trb_saturation_max->Minimum = 0;
trb_saturation_max->Maximum = 255;

trb_value_min->Minimum = 0;
trb_value_min->Maximum = 255;

trb_value_max->Minimum = 0;
trb_value_max->Maximum = 255;

trb_ObjectSize_min->Minimum = 0;
trb_ObjectSize_min->Maximum = 479999;

trb_ObjectSize_max->Minimum = 0;
trb_ObjectSize_max->Maximum = 480000;

numUD_erode_iterations->Minimum = 0;
numUD_erode_iterations->Maximum = 10;

numUD_dilation_iterations->Minimum = 0;
numUD_dilation_iterations->Maximum = 10;

numUD_opening_iterations->Minimum = 0;
numUD_opening_iterations->Maximum = 10;

numUD_bilateral_color->Minimum = 0;
numUD_bilateral_color->Maximum = 10;

numUD_morph_iterations->Minimum = 0;
numUD_morph_iterations->Maximum = 10;


numUD_erode_kernelsize->Minimum = static_cast<Int32>(1);
numUD_erode_kernelsize->Maximum = static_cast<Int32>(10);

numUD_dilation_kernelsize->Minimum = static_cast<Int32>(1);
numUD_dilation_kernelsize->Maximum = static_cast<Int32>(10);

numUD_opening_kernelsize->Minimum = static_cast<Int32>(1);
numUD_opening_kernelsize->Maximum = static_cast<Int32>(10);

numUD_closing_kernelsize->Minimum = static_cast<Int32>(1);
numUD_closing_kernelsize->Maximum = static_cast<Int32>(10);

numUD_bilateral_kernelsize->Minimum = static_cast<Int32>(1);
numUD_bilateral_kernelsize->Maximum = static_cast<Int32>(10);

numUD_morph_kernelsize->Minimum = static_cast<Int32> (1);
numUD_morph_kernelsize->Maximum = static_cast<Int32>(10);
*/

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
    //if (this->Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->is_thread_ready())
    //  {
    //  FillMat2Picturebox (pb_original,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_src_img);
    //  FillMat2Picturebox (pb_gray,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_hsv_filtered);
    //  FillMat2Picturebox (pb_filtered,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_masked_img);
    //  FillMat2Picturebox (pb_tracked,*Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->cpu_contoured);
    //  }
    this->Ui->txb_fps->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_fps()));
    this->Ui->txb_frametime->   setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_frametime().count()));
    this->Ui->txb_delta_x->     setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_delta_x()));
    this->Ui->txb_delta_y->     setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_delta_y()));
    this->Ui->txb_s_x->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_schwerpunkt_x()));
    this->Ui->txb_s_y->         setText(QString::number(this->Main->Camera_manager->camera_vector[camera_id_in_use]->get_schwerpunkt_y()));
}


void C_frm_Object_Calibration::on_num_opening_iterations_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_opening_iterations (static_cast<int> (this->numUD_opening_iterations->Value));

}

void C_frm_Object_Calibration::on_num_opening_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_opening_kernel_size (static_cast<int> (this->numUD_opening_kernelsize->Value));
}

void C_frm_Object_Calibration::on_num_closing_iterations_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_closing_iterations (static_cast<int> (this->numUD_closing_iterations->Value));
}

void C_frm_Object_Calibration::on_num_closing_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_closing_kernel_size (static_cast<int> (this->numUD_closing_kernelsize->Value));
}


void C_frm_Object_Calibration::on_num_erode_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erosion_kernel_size (static_cast<int> (this->numUD_erode_kernelsize->Value));
}


void C_frm_Object_Calibration::on_num_dilate_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilation_kernel_size (static_cast<int> (this->numUD_dilation_kernelsize->Value));
}
void C_frm_Object_Calibration::on_num_gaussian_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_gaussian_kernel_size (static_cast<int> (this->numUD_gaussian_kernel_size->Value));
}

void C_frm_Object_Calibration::on_num_morph_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_kernel_size (static_cast<int> (this->numUD_morph_kernelsize->Value));
}

void C_frm_Object_Calibration::on_num_gaussian_sigma_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_gaussian_sigma (static_cast<double> (this->numUD_gaussian_sigma->Value));
}

void C_frm_Object_Calibration::on_num_bilateral_color_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_sigma_color (static_cast<float> (this->numUD_bilateral_color->Value));
}

void C_frm_Object_Calibration::on_num_bilateral_spatial_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_sigma_spatial (static_cast<float> (this->numUD_bilateral_spatial->Value));
}

void C_frm_Object_Calibration::on_num_bilateral_kernelsize_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_bilateral_kernel_size (static_cast<int> (this->numUD_bilateral_kernelsize->Value));
}

void C_frm_Object_Calibration::on_sld_hue_min_valueChanged(int value)
{
    if (this->Ui->sld_hue_min->value() > this->Ui->sld_hue_max->value()) this->Ui->sld_hue_min->setValue(this->Ui->sld_hue_max->value() - 1);

    Main->Camera_manager->camera_vector[camera_id_in_use]->set_hue_min (this->Ui->sld_hue_min->value());
    this->Ui->txb_hue_min->setText(QString::number(this->Ui->sld_hue_min->value()));

}

void C_frm_Object_Calibration::on_sld_hue_max_valueChanged(int value)
{
    if (this->trb_hue_min->Value > this->trb_hue_max->Value) this->trb_hue_max->Value = this->trb_hue_min->Value + 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_hue_max (this->trb_hue_max->Value);
    this->txb_hue_max->Text = System::String::Format ("{0:0}",this->trb_hue_max->Value);
}

void C_frm_Object_Calibration::on_sld_saturation_min_valueChanged(int value)
{
    if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_min->Value = this->trb_saturation_max->Value - 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_saturation_min (this->trb_saturation_min->Value);
    this->txb_saturation_min->Text = System::String::Format ("{0:0}",this->trb_saturation_min->Value);
}

void C_frm_Object_Calibration::on_sld_saturation_max_valueChanged(int value)
{
    if (this->trb_saturation_min->Value > this->trb_saturation_max->Value) this->trb_saturation_max->Value = this->trb_saturation_min->Value + 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_saturation_max (this->trb_saturation_max->Value);
    this->txb_saturation_max->Text = System::String::Format ("{0:0}",this->trb_saturation_max->Value);
}

void C_frm_Object_Calibration::on_sld_value_min_valueChanged(int value)
{
    if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_min->Value = this->trb_value_max->Value - 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_value_min (this->trb_value_min->Value);
    this->txb_value_min->Text = System::String::Format ("{0:0}",this->trb_value_min->Value);
}

void C_frm_Object_Calibration::on_sld_value_max_valueChanged(int value)
{
    if (this->trb_value_min->Value > this->trb_value_max->Value) this->trb_value_max->Value = this->trb_value_min->Value + 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_value_max (this->trb_value_max->Value);
    this->txb_value_max->Text = System::String::Format ("{0:0}",this->trb_value_max->Value);
}

void C_frm_Object_Calibration::on_sld_objectsize_min_valueChanged(int value)
{
    if (this->trb_ObjectSize_min->Value > this->trb_ObjectSize_max->Value) this->trb_ObjectSize_min->Value = this->trb_ObjectSize_max->Value - 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_object_size_min (static_cast<int> (trb_ObjectSize_min->Value));
    txb_objectsize_min->Text = trb_ObjectSize_min->Value.ToString();
}

void C_frm_Object_Calibration::on_sld_objectsize_max_valueChanged(int value)
{
    if (this->trb_ObjectSize_min->Value > this->trb_ObjectSize_max->Value) this->trb_ObjectSize_max->Value = this->trb_ObjectSize_min->Value + 1;

    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_object_size_max (static_cast<int> (trb_ObjectSize_max->Value));
    txb_objectsize_max->Text = trb_ObjectSize_max->Value.ToString();
}

void C_frm_Object_Calibration::on_num_camera_valueChanged(int arg1)
{
    TimerWait              = Zaehler + 100;
    this->camera_id_in_use = this->Ui->num_camera->value();
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_idle (false);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_show_cropped_image (false);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_undistord_active (true);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_filtering_active (true);
    this->Main->Camera_manager->camera_vector[camera_id_in_use]->set_show_contoured_active (true);

    this->get_camera_settings (camera_id_in_use);
}



void C_frm_Object_Calibration::on_num_dilate_iterations_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilation_iterations (static_cast<int> (this->numUD_dilation_iterations->Value));
}

void C_frm_Object_Calibration::on_num_erode_iterations_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erosion_iterations (static_cast<int> (this->numUD_erode_iterations->Value));
}

void C_frm_Object_Calibration::on_num_morph_iterations_valueChanged(int arg1)
{
    Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_iterations (static_cast<int> (this->numUD_morph_iterations->Value));
}

void C_frm_Object_Calibration::on_bt_apply_all_clicked()
{
    int current_camera = static_cast<int> (numUD_cam_id->Value);
    for (int i = 0; i < GlobalObjects->cameras_in_use; i++)
      {
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_value_min (this->trb_value_min->Value);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_value_max (this->trb_value_max->Value);

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_saturation_min (this->trb_saturation_min->Value);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_saturation_max (this->trb_saturation_max->Value);

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_hue_min (this->trb_hue_min->Value);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_hue_max (this->trb_hue_max->Value);

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_opening_iterations (static_cast<int> (this->numUD_opening_iterations->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_opening_kernel_size (static_cast<int> (this->numUD_opening_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_closing_iterations (static_cast<int> (this->numUD_closing_iterations->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_closing_kernel_size (static_cast<int> (this->numUD_closing_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erode_active (this->chkb_erode->Checked);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erosion_iterations (static_cast<int> (this->numUD_erode_iterations->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_erosion_kernel_size (static_cast<int> (this->numUD_erode_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilate_active (this->chkb_dilate->Checked);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilation_iterations (static_cast<int> (this->numUD_dilation_iterations->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_dilation_kernel_size (static_cast<int> (this->numUD_dilation_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_active (this->chkb_morph->Checked);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_iterations (static_cast<int> (this->numUD_morph_iterations->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_morph_kernel_size (static_cast<int> (this->numUD_morph_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_gaussian_sigma (static_cast<double> (this->numUD_gaussian_sigma->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_gaussian_kernel_size (static_cast<int> (this->numUD_gaussian_kernel_size->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_active (this->chkb_bilateral->Checked);
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_sigma_color (static_cast<float> (this->numUD_bilateral_color->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_sigma_spatial (static_cast<float> (this->numUD_bilateral_spatial->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_bilateral_kernel_size (static_cast<int> (this->numUD_bilateral_kernelsize->Value));

      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_object_size_min (static_cast<int> (this->trb_ObjectSize_min->Value));
      this->Main->camera_managed->camera_unmanaged->camera_vector[i]->set_object_size_max (static_cast<int> (this->trb_ObjectSize_min->Value));


      Main->camera_managed->camera_unmanaged->save_camera_settings (i);
      }
}

void C_frm_Object_Calibration::on_bt_apply_clicked()
{
    Main->camera_managed->camera_unmanaged->save_camera_settings (static_cast<int> (numUD_cam_id->Value));
}

void C_frm_Object_Calibration::on_chkb_dilate_stateChanged(int arg1)
{
    if (dilate_active == false)
      {
      dilate_active = true;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilate_active (true);
      numUD_dilation_iterations->Enabled = true;
      numUD_dilation_kernelsize->Enabled = true;
      }
    else if (dilate_active == true)
      {
      dilate_active = false;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_dilate_active (false);
      numUD_dilation_iterations->Enabled = false;
      numUD_dilation_kernelsize->Enabled = false;
      }

}

void C_frm_Object_Calibration::on_chkb_morph_stateChanged(int arg1)
{
    if (morph_active == false)
      {
      morph_active = true;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_active (true);
      numUD_morph_iterations->Enabled = true;
      numUD_morph_kernelsize->Enabled = true;
      }
    else if (morph_active == true)
      {
      morph_active = false;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_morph_active (false);
      numUD_morph_iterations->Enabled = false;
      numUD_morph_kernelsize->Enabled = false;
      }

}


void C_frm_Object_Calibration::on_chkb_erode_stateChanged(int arg1)
{
    if (erode_active == false)
      {
      erode_active = true;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erode_active (true);
      numUD_erode_iterations->Enabled = true;
      numUD_erode_kernelsize->Enabled = true;
      }
    else if (erode_active == true)
      {
      erode_active = false;
      Main->camera_managed->camera_unmanaged->camera_vector[camera_id_in_use]->set_erode_active (false);
      numUD_erode_iterations->Enabled = false;
      numUD_erode_kernelsize->Enabled = false;
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

  this->numUD_opening_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_opening_iterations());
  this->numUD_opening_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_opening_kernel_size());

  this->numUD_closing_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_closing_iterations());
  this->numUD_closing_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_closing_kernel_size());

  this->chkb_erode->Checked           = this->Main->Camera_manager->camera_vector[camera_id]->is_erode_active();
  this->numUD_erode_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_erosion_iterations());
  this->numUD_erode_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_erosion_kernel_size());

  this->chkb_dilate->Checked             = this->Main->Camera_manager->camera_vector[camera_id]->is_dilate_active();
  this->numUD_dilation_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_dilation_iterations());
  this->numUD_dilation_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_dilation_kernel_size());

  this->chkb_morph->Checked           = this->Main->Camera_manager->camera_vector[camera_id]->is_morph_active();
  this->numUD_morph_iterations->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_morph_iterations());
  this->numUD_morph_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_morph_kernel_size());

  this->numUD_gaussian_sigma->Value       = (Main->Camera_manager->camera_vector[camera_id]->get_gaussian_sigma());
  this->numUD_gaussian_kernel_size->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_gaussian_kernel_size());

  this->Ui->chkb_bilateral->setCheckState(this->Main->Camera_manager->camera_vector[camera_id]->is_bilateral_active());
  this->Ui->num_bilateral_kernelsize->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_kernel_size());
  this->Ui->num_bilateral_spatial->setValue (this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_sigma_spatial());
  this->Ui->num_bilateral_color->setValue (this->Main->Camera_manager->camera_vector[camera_id]->get_bilateral_sigma_color());

  this->Ui->sld_objectsize_min->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_object_size_min();
  this->Ui->sld_objectsize_max->setValue(this->Main->Camera_manager->camera_vector[camera_id]->get_object_size_max();
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
      numUD_bilateral_color->Enabled      = true;
      numUD_bilateral_spatial->Enabled    = true;
      numUD_bilateral_kernelsize->Enabled = true;
      }
    else if (bilateral_active == true)
      {
      numUD_bilateral_color->Enabled      = false;
      numUD_bilateral_spatial->Enabled    = false;
      numUD_bilateral_kernelsize->Enabled = false;
      }
}
