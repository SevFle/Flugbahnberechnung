#include "headers/frm_object_calibration.h"
using namespace frm_Object_Calibration;

C_frm_Object_Calibration::C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
  {
  this->Ui                    = new Ui::C_frm_object_calibration();
  Ui->setupUi                 (this);
  this->GlobalObjects         = GlobalObjects;
  this->Main                  = Main;
  this->Taktgeber             = new QTimer(this);
  this->Taktgeber_Intervall   = 18;
  this->camID      = 0;
  this->TimerWait             = 0;
  this->trackingActive        = false;
  }

C_frm_Object_Calibration::~C_frm_Object_Calibration()
  {
  this->trackingActive        = false;
  this->TimerWait             = 0;
  this->camID      = 0;
  this->Taktgeber_Intervall   = 0;
  delete                      (Taktgeber);
  this->Main                  = nullptr;
  this->GlobalObjects         = nullptr;
  delete                      (Ui);
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
this->Ui->num_camera->setMaximum(GlobalObjects->absCameras);
this->Ui->numTimerIntervall->setValue(Taktgeber_Intervall);
this->set_gui();
this->get_camera_settings (0);
//this->Main->cameraManager->trackingManager->dataPlotter->show();
}



void C_frm_Object_Calibration::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Object_Calibration::Taktgeber_Tick);
 this->Zaehler = 0;
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
void C_frm_Object_Calibration::on_bt_exit_clicked()
  {
  this->GlobalObjects->watchdog->stop();
  delete(this->GlobalObjects->watchdog);
  this->Main->cameraManager->pipelineDone.store(true);
  if(!this->Main->cameraManager->stopPipelineTracking())
    return;
  this->Main->frm_Object_Tracking->close();
  this->close();
}
void C_frm_Object_Calibration::Taktgeber_Tick()
  {
  cv::Mat img;
  this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));
  if(this->Main->cameraManager->pipelineQue->try_pop(pData))
    {
    this->                      Fill_Mat_2_Lbl(pData->cpuSrcImg[0], this->Ui->lbl_src_img);
    this->                      Fill_Mat_2_Lbl(pData->cpuGrayImg[0], this->Ui->lbl_img_gray);
    this->                      Fill_Mat_2_Lbl(pData->cpuUndistortedImg[0], this->Ui->lbl_imgFinal);
    this->Ui->txb_fps->         setText(QString::number(pData->fps));
    this->Ui->txb_frametime->   setText(QString::number(pData->frametime.count()));
//    this->Ui->txb_delta_x->     setText(QString::number(payload->delta_x));
//    this->Ui->txb_delta_y->     setText(QString::number(payload->delta_y));
//    this->Ui->txb_s_x->         setText(QString::number(payload->s_x));
//    this->Ui->txb_s_y->         setText(QString::number(payload->s_y));
      this->Ui->txb_worker_1->         setText(QString::number(pData->executionTime[0].count()));
      this->Ui->txb_worker_2->         setText(QString::number(pData->executionTime[1].count()));
      this->Ui->txb_worker_3->         setText(QString::number(pData->executionTime[2].count()));
      this->Ui->txb_worker_4->         setText(QString::number(pData->executionTime[3].count()));
      this->Ui->txb_worker_5->         setText(QString::number(pData->executionTime[4].count()));
      this->Ui->txb_worker_6->         setText(QString::number(pData->executionTime[5].count()));
      this->Ui->txb_worker_7->         setText(QString::number(pData->executionTime[6].count()));
      this->Ui->txb_worker_8->         setText(QString::number(pData->executionTime[7].count()));
    delete(pData);
    }
  }


void C_frm_Object_Calibration::on_num_opening_iterations_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setOpening_iterations(arg1);

}

void C_frm_Object_Calibration::on_num_opening_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setOpening_kernel_size (arg1);
}

void C_frm_Object_Calibration::on_num_closing_iterations_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setClosing_iterations(arg1);
}

void C_frm_Object_Calibration::on_num_closing_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setClosing_kernel_size(arg1);
}


void C_frm_Object_Calibration::on_num_erode_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setErosion_kernel_size(arg1);
}


void C_frm_Object_Calibration::on_num_dilate_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setDilation_kernel_size(arg1);
}
void C_frm_Object_Calibration::on_num_gaussian_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setGaussian_kernel_size(arg1);
}

void C_frm_Object_Calibration::on_num_morph_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setMorph_kernel_size(arg1);
}

void C_frm_Object_Calibration::on_num_gaussian_sigma_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setGaussian_sigma(arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_color_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setBilateral_sigma_color(arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_spatial_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setBilateral_sigma_spatial(arg1);
}

void C_frm_Object_Calibration::on_num_bilateral_kernelsize_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setBilateral_kernel_size(arg1);
}

void C_frm_Object_Calibration::on_sld_hue_min_valueChanged(int value)
{
    if (value > this->Ui->sld_hue_max->value()) this->Ui->sld_hue_min->setValue(this->Ui->sld_hue_max->value() - 1);

    this->Main->cameraManager->vecCameras[camID]->filterValues->setHue_min(value);
    this->Ui->txb_hue_min->setText(QString::number(value));

}

void C_frm_Object_Calibration::on_sld_hue_max_valueChanged(int value)
{
    if (this->Ui->sld_hue_min->value() > value) this->Ui->sld_hue_max->setValue(this->Ui->sld_hue_min->value() + 1);

    this->Main->cameraManager->vecCameras[camID]->filterValues->setHue_max (value);
    this->Ui->txb_hue_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_saturation_min_valueChanged(int value)
{
    if (this->Ui->sld_saturation_min->value() > this->Ui->sld_saturation_max->value()) this->Ui->sld_saturation_min->setValue(this->Ui->sld_saturation_max->value() - 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setSaturation_min(value);
    this->Ui->txb_saturation_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_saturation_max_valueChanged(int value)
{
    if (this->Ui->sld_saturation_min->value() > this->Ui->sld_saturation_max->value()) this->Ui->sld_saturation_max->setValue(this->Ui->sld_saturation_min->value() + 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setSaturation_max(value);
    this->Ui->txb_saturation_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_value_min_valueChanged(int value)
{
    if (value > this->Ui->sld_value_max->value()) this->Ui->sld_value_min->setValue(this->Ui->sld_value_max->value() - 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setValue_min(value);
    this->Ui->txb_value_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_value_max_valueChanged(int value)
{
    if (this->Ui->sld_value_min->value() > this->Ui->sld_value_max->value()) this->Ui->sld_value_max->setValue(this->Ui->sld_value_min->value() + 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setValue_max (value);
    this->Ui->txb_value_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_objectsize_min_valueChanged(int value)
{
    if (value > this->Ui->sld_objectsize_max->value()) this->Ui->sld_objectsize_min->setValue(this->Ui->sld_objectsize_max->value() - 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setObject_Size_min(value);
    this->Ui->txb_objectsize_min->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_sld_objectsize_max_valueChanged(int value)
{
    if (this->Ui->sld_objectsize_min->value() > this->Ui->sld_objectsize_max->value()) this->Ui->sld_objectsize_max->setValue(this->Ui->sld_objectsize_min->value() + 1);

    Main->cameraManager->vecCameras[camID]->filterValues->setObject_Size_max(value);
    this->Ui->txb_objectsize_max->setText(QString::number(value));
}

void C_frm_Object_Calibration::on_num_camera_valueChanged(int arg1)
  {
    this->get_camera_settings (arg1);
    this->camID = arg1;
    std::lock_guard<std::mutex> lck (*this->Main->cameraManager->getLock());
    this->Main->cameraManager->setFlush(true);
    this->Main->cameraManager->setArrActiveCameras(camID, 0);
    this->Main->cameraManager->setArrActiveCameras(camID, 1);
    this->Main->cameraManager->setFlush(false);

  }



void C_frm_Object_Calibration::on_num_dilate_iterations_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setDilation_iterations(arg1);
}

void C_frm_Object_Calibration::on_num_erode_iterations_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setErosion_iterations(arg1);
}

void C_frm_Object_Calibration::on_num_morph_iterations_valueChanged(int arg1)
{
    this->Main->cameraManager->vecCameras[camID]->filterValues->setMorph_iterations(arg1);
}

void C_frm_Object_Calibration::on_bt_apply_all_clicked()
{
    int i = 0;
    for (auto it = std::begin(this->Main->cameraManager->vecCameras); it != std::end(this->Main->cameraManager->vecCameras); it++)
      {
      (*it)->filterValues->setHue_min                   (this->Ui->sld_hue_min->value());
      (*it)->filterValues->setHue_max                   (this->Ui->sld_hue_max->value());

      (*it)->filterValues->setSaturation_min            (this->Ui->sld_saturation_min->value());
      (*it)->filterValues->setSaturation_min            (this->Ui->sld_saturation_max->value());

      (*it)->filterValues->setValue_min                 (this->Ui->sld_value_min->value());
      (*it)->filterValues->setValue_max                 (this->Ui->sld_value_max->value());

      (*it)->filterValues->setOpening_iterations        (this->Ui->num_opening_iterations->value());
      (*it)->filterValues->setOpening_kernel_size       (this->Ui->num_opening_kernelsize->value());

      (*it)->filterValues->setClosing_iterations        (this->Ui->num_closing_iterations->value());
      (*it)->filterValues->setClosing_kernel_size       (this->Ui->num_closing_kernelsize->value());

      (*it)->filterValues->setErode_active              (this->Ui->chkb_erode->isChecked());
      (*it)->filterValues->setErosion_iterations        (this->Ui->num_erode_iterations->value());
      (*it)->filterValues->setErosion_kernel_size       (this->Ui->num_erode_kernelsize->value());

      (*it)->filterValues->setDilate_active             (this->Ui->chkb_dilate->isChecked());
      (*it)->filterValues->setDilation_iterations       (this->Ui->num_dilate_iterations->value());
      (*it)->filterValues->setDilation_kernel_size      (this->Ui->num_dilate_kernelsize->value());

      (*it)->filterValues->setMorph_active              (this->Ui->chkb_morph->isChecked());
      (*it)->filterValues->setMorph_iterations          (this->Ui->num_morph_iterations->value());
      (*it)->filterValues->setMorph_kernel_size         (this->Ui->num_morph_kernelsize->value());

      (*it)->filterValues->setGaussian_sigma            (this->Ui->num_gaussian_sigma->value());
      (*it)->filterValues->setGaussian_kernel_size      (this->Ui->num_gaussian_kernelsize->value());

      (*it)->filterValues->setBilateral_active          (this->Ui->chkb_bilateral->isChecked());
      (*it)->filterValues->setBilateral_sigma_color     (this->Ui->num_bilateral_color->value());
      (*it)->filterValues->setBilateral_sigma_spatial   (this->Ui->num_bilateral_spatial->value());
      (*it)->filterValues->setBilateral_kernel_size     (this->Ui->num_dilate_kernelsize->value());

      (*it)->filterValues->setObject_Size_min           (this->Ui->sld_objectsize_min->value());
      (*it)->filterValues->setObject_Size_max           (this->Ui->sld_objectsize_max->value());

      //TODO
      this->Main->cameraManager->saveManager->saveCameraSettings(*(*it));
      i++;
      }
}

void C_frm_Object_Calibration::set_gui()
{
    this->Ui->sld_hue_min->setValue(0);
    this->Ui->sld_hue_max->setValue(255);
    this->Ui->sld_saturation_min->setValue(0);
    this->Ui->sld_saturation_max->setValue(255);
    this->Ui->sld_value_min->setValue(0);
    this->Ui->sld_value_max->setValue(255);

    this->Ui->sld_hue_min->setMinimum(0);
    this->Ui->sld_hue_min->setMaximum(255);

    this->Ui->sld_hue_max->setMinimum(0);
    this->Ui->sld_hue_max->setMaximum(255);

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

    this->Ui->num_gaussian_kernelsize->setSingleStep(2);
    this->Ui->num_gaussian_kernelsize->setMaximum(10);
    this->Ui->num_gaussian_kernelsize->setMinimum(1);

    this->Ui->num_gaussian_sigma->setMaximum(10);
    this->Ui->num_gaussian_sigma->setMinimum(1);

    }

void C_frm_Object_Calibration::on_bt_apply_clicked()
    {
    this->Main->cameraManager->saveManager->saveCameraSettings(*this->Main->cameraManager->vecCameras[camID]);
    }

void C_frm_Object_Calibration::on_chkb_dilate_stateChanged(int arg1)
    {
    if (dilate_active == false)
      {
      this->dilate_active = true;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setDilate_active (true);
      this->Ui->num_dilate_iterations->setEnabled(true);
      this->Ui->num_dilate_kernelsize->setEnabled(true);
      }
    else if (dilate_active == true)
      {
      dilate_active = false;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setDilate_active (false);
      this->Ui->num_dilate_iterations->setEnabled(false);
      this->Ui->num_dilate_kernelsize->setEnabled(false);
      }

    }

void C_frm_Object_Calibration::on_chkb_morph_stateChanged(int arg1)
    {
    if (morph_active == false)
      {
      this->morph_active = true;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setMorph_active (true);
      this->Ui->num_morph_iterations->setEnabled(true);
      this->Ui->num_morph_kernelsize->setEnabled(true);
      }
    else if (morph_active == true)
      {
      morph_active = false;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setMorph_active (false);
      this->Ui->num_morph_iterations->setEnabled(false);
      this->Ui->num_morph_kernelsize->setEnabled(false);
      }

    }


void C_frm_Object_Calibration::on_chkb_erode_stateChanged(int arg1)
{
    if (erode_active == false)
      {
      this->erode_active = true;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setErode_active(true);
      this->Ui->num_erode_iterations->setEnabled(true);
      this->Ui->num_erode_kernelsize->setEnabled(true);
      }
    else if (erode_active == true)
      {
      this->erode_active = false;
      this->Main->cameraManager->vecCameras[camID]->filterValues->setErode_active (false);
      this->Ui->num_erode_iterations->setEnabled(false);
      this->Ui->num_erode_kernelsize->setEnabled(false);
      }

}
void C_frm_Object_Calibration::get_camera_settings (int camera_id)
  {
  this->Ui->sld_hue_min->setValue               (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getHue_min());
  this->Ui->sld_hue_max->setValue               (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getHue_max());

  this->Ui->sld_saturation_min->setValue        (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getSaturation_min());
  this->Ui->sld_saturation_max->setValue        (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getSaturation_max());

  this->Ui->sld_value_min->setValue             (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getValue_min());
  this->Ui->sld_value_max->setValue             (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getValue_max());

  this->Ui->num_opening_iterations->setValue    (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getOpenIterations());
  this->Ui->num_opening_kernelsize->setValue    (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getOpenKernelSize());

  this->Ui->num_closing_iterations->setValue    (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getCloseIterations());
  this->Ui->num_closing_kernelsize->setValue    (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getCloseKernelSize());

  this->Ui->chkb_erode->setCheckState           (Qt::CheckState(this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getErode_active()));
  this->Ui->num_erode_iterations->setValue      (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getErodeIterations());
  this->Ui->num_erode_kernelsize->setValue      (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getErodeKernelSize());

  this->Ui->chkb_dilate->setCheckState          (Qt::CheckState(this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getDilate_active()));
  this->Ui->num_dilate_iterations->setValue     (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getDilateIterations());
  this->Ui->num_dilate_kernelsize->setValue     (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getDilateKernelSize());

  this->Ui->chkb_morph->setCheckState           (Qt::CheckState(this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getMorph_active()));
  this->Ui->num_morph_iterations->setValue      (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getMorphIterations());
  this->Ui->num_morph_kernelsize->setValue      (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getMorphKernelSize());

  this->Ui->num_gaussian_sigma->setValue        (Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getGaussianSigma());
  this->Ui->num_gaussian_kernelsize->setValue   (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getGaussianKernelSize());

  this->Ui->chkb_bilateral->setCheckState       (Qt::CheckState(this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getBilateral_active()));
  this->Ui->num_bilateral_kernelsize->setValue  (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getBilateralKernelSize());
  this->Ui->num_bilateral_spatial->setValue     (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getBilateralSigmaSpatial());
  this->Ui->num_bilateral_color->setValue       (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getBilateralSigmaColor());

  this->Ui->sld_objectsize_min->setValue        (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getObject_Size_min());
  this->Ui->sld_objectsize_max->setValue        (this->Main->cameraManager->vecCameras[camera_id]->getFilterproperties()->getObject_Size_max());
  }




void frm_Object_Calibration::C_frm_Object_Calibration::on_bt_tracking_clicked()
{
    //TODO Open Form
    //this->hide();
    this->trackingActive = true;
    this->Ui->num_camera->setEnabled(false);
    this->Main->cameraManager->setFlush(true);
    this->Main->cameraManager->setArrActiveCameras(0,0);
    this->Main->cameraManager->setArrActiveCameras(1,1);
    this->Main->cameraManager->setFlush(false);
    this->Main->cameraManager->getFilterFlags()->setObjectDetection(true);
    this->Main->cameraManager->getFilterFlags()->setRoiAdjustment(true);
    this->Main->cameraManager->getFilterFlags()->setTracking(true);


    //this->Main->frm_Object_Tracking->setWindowModality(Qt::NonModal);
    this->Main->frm_Object_Tracking->show();
    //this->Main->frm_Object_Tracking->setParent(this);

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
  if(img.type()!= 0)
  {
     QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_BGR888);
     label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));
     return;
  }
  QImage imgIn= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
  label->setPixmap(QPixmap::fromImage(imgIn).scaled(label->size(),Qt::KeepAspectRatio));


}


void frm_Object_Calibration::C_frm_Object_Calibration::on_numTimerIntervall_valueChanged(int arg1)
  {
  this->Taktgeber->setInterval(arg1);
  }
