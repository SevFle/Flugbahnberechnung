#include "headers/Forms/frm_camera_positioning_pose.h"
using namespace frm_Camera_Positioning_Pose;

C_frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent) :
    QMainWindow(parent)
{
    this->Ui = new Ui::C_frm_camera_positioning_pose();
    Ui->setupUi(this);
    this->GlobalObjects                                        = GlobalObjects;
    this->Main                                                 = Main;
    this->convert_to_degree_active                             = false;
    this->camera_id                                    = 0;
    this->Zaehler                                              = 0;
    this->method                                               = 1;
    nx = 0;
    ny = 0;
    nz = 0;
    n0 = 0;
    ox = 0;
    oy = 0;
    oz = 0;
    o0 = 0;
    ax = 0;
    ay = 0;
    az = 0;
    a0 = 0;
    px = 0;
    py = 0;
    pz = 0;
    p0 = 1;
    this->pose_ =    new C_AbsolutePose();
    this->Taktgeber = new QTimer(this);
    this->Taktgeber_Intervall = 100;


}

C_frm_Camera_Positioning_Pose::~C_frm_Camera_Positioning_Pose()
{
    delete(pose_);
    this->pose_ = nullptr;
    nx = 0;
    ny = 0;
    nz = 0;
    n0 = 0;
    ox = 0;
    oy = 0;
    oz = 0;
    o0 = 0;
    ax = 0;
    ay = 0;
    az = 0;
    a0 = 0;
    px = 0;
    py = 0;
    pz = 0;
    p0 = 1;
    this->Zaehler                                 = 0;
    this->camera_id                               = 0;
    this->Main                                    = nullptr;
    this->GlobalObjects                                            = nullptr;

    delete Ui;
}


/************************************** QT-Events******************************/
void C_frm_Camera_Positioning_Pose::showEvent(QShowEvent* ShowEvent)
{
Q_UNUSED(ShowEvent)
this->Zaehler = 0;
connect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning_Pose::Taktgeber_Tick);
this->Taktgeber->start(this->Taktgeber_Intervall);
this->installEventFilter(this);

}

void C_frm_Camera_Positioning_Pose::closeEvent(QCloseEvent* CloseEvent)
{
 Q_UNUSED(CloseEvent);
 this->removeEventFilter(this);
 this->Taktgeber->stop();
 disconnect(this->Taktgeber, &QTimer::timeout, this, &C_frm_Camera_Positioning_Pose::Taktgeber_Tick);
 this->Zaehler = 0;
 }

bool               C_frm_Camera_Positioning_Pose::eventFilter                                       (QObject* Object, QEvent* Event)
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


void C_frm_Camera_Positioning_Pose::Taktgeber_Tick()
{
    this->Ui->txb_zaehler->setText(QString::number(this->Zaehler++));

    this->get_textbox_data();
    calculation_method();
    if (convert_to_degree_active) convert_rad_to_degree();
    set_textbox_data();

}
void C_frm_Camera_Positioning_Pose::tait_extrinsic_zyx ()
  {

  pose_->nx  (cos (theta) * cos (phi));

  pose_->ny  (sin (psi) * sin (theta) * cos (phi) - cos (psi) * sin (phi));

  pose_->nz  (cos (psi) * cos (theta) * cos (phi) + sin (psi) * sin (phi));

  pose_->ox  (cos (theta) * sin (phi));

  pose_->oy  (sin (psi) * sin (theta) * sin (phi) + cos (psi) * cos (phi));

  pose_->oz  (cos (psi) * sin (theta) * sin (phi) - sin (psi) * cos (phi));

  pose_->ax  (-sin (theta));

  pose_->ay  (sin (psi) * cos (theta));

  pose_->az  (cos (psi) * cos (theta));

  pose_->px  (t_x);
  pose_->py  (t_y);
  pose_->pz  (t_z);
  }
void C_frm_Camera_Positioning_Pose::tait_intrinsic_zyx ()
  {

 pose_->nx ( cos (phi) * cos (theta));

 pose_->ny  (sin (phi) * cos (theta));

 pose_->nz  (-sin (theta));

 pose_->ox  (cos (phi) * sin (theta) * sin (psi) - sin (phi) * cos (psi));

 pose_->oy  (sin (phi) * sin (theta) * sin (psi) + cos (phi) * cos (psi));

 pose_->oz  (cos (theta) * sin (psi));

 pose_->ax  (cos (phi) * sin (theta) * cos (psi) + sin (phi) * sin (psi));

 pose_->ay  (sin (phi) * sin (theta) * cos (psi) - cos (phi) * sin (psi));

 pose_->az  (cos (theta) * cos (psi));

 pose_->px  (t_x);
 pose_->py  (t_y);
 pose_->pz  (t_z);
  }
void C_frm_Camera_Positioning_Pose::euler_extrinsic_zyz ()
  {

  pose_->nx  (cos (psi) * cos (theta) * cos (phi) - sin (psi) * sin (phi));

  pose_->ny  (sin (psi) * cos (theta) * cos (phi) + cos (psi) * sin (phi));

  pose_->nz  (-sin (theta) * cos (phi));

  pose_->ox  (-cos (psi) * cos (theta) * sin (phi) - sin (psi) * cos (phi));

  pose_->oy  (-sin (psi) * cos (theta) * sin (phi) + cos (psi) * cos (phi));

  pose_->oz  (sin (theta) * sin (phi));

  pose_->ax  (cos (psi) * sin (theta));

  pose_->ay  (sin (psi) * sin (theta));

  pose_->az  (cos (theta));

  pose_->px  (t_x);
  pose_->py  (t_y);
  pose_->pz  (t_z);
  }
void C_frm_Camera_Positioning_Pose::euler_intrinsic_zyz ()
  {

  pose_->nx  (cos (phi) * cos (theta) * cos (psi) - sin (phi) * sin (psi));

  pose_->ny  (sin (phi) * cos (theta) * cos (psi) + cos (phi) * sin (psi));

  pose_->nz  (-sin (theta) * cos (psi));

  pose_->ox  (-cos (phi) * cos (theta) * sin (psi) - sin (phi) * cos (psi));

  pose_->oy  (-sin (phi) * cos (theta) * sin (psi) + cos (phi) * cos (psi));

  pose_->oz  (sin (theta) * sin (psi));

  pose_->ax  (cos (phi) * sin (theta));

  pose_->ay  (sin (phi) * sin (theta));

  pose_->az  (cos (theta));

  pose_->px  (t_x);
  pose_->py  (t_y);
  pose_->pz  (t_z);
  }
void C_frm_Camera_Positioning_Pose::calculation_method ()
  {
  switch (method)
    {
    case 1:
      tait_extrinsic_zyx();
      break;
    case 2:
      tait_intrinsic_zyx();
      break;
    case 3:
      euler_extrinsic_zyz();
      break;
    case 4:
      euler_intrinsic_zyz();
      break;
    }
  }
void C_frm_Camera_Positioning_Pose::get_textbox_data ()
  {

  if (this->Ui->txb_phi->toPlainText() == "" || this->Ui->txb_phi->toPlainText() == "-")
    {
    this->phi = 0.0;
    }
  else
    {
    this->phi =  this->Ui->txb_phi->toPlainText().toDouble() * 3.141592653589793238463 / 180.0;
    }

  if (this->Ui->txb_theta->toPlainText() == "" || this->Ui->txb_theta->toPlainText() == "-")
    {
    this->theta = 0.0;
    }
  else
    {
    this->theta = this->Ui->txb_theta->toPlainText().toDouble() * 3.141592653589793238463 / 180.0;
    }

  if (this->Ui->txb_psi->toPlainText() == "" || this->Ui->txb_psi->toPlainText() == "-")
    {
    this->psi = 0.0;
    }
  else
    {
    this->psi =this->Ui->txb_psi->toPlainText().toDouble() * 3.141592653589793238463 / 180.0;
    }

  if (this->Ui->txb_transl_x->toPlainText() == "" || this->Ui->txb_transl_x->toPlainText() == "-")
    {
    this->t_x = 0.0;
    }
  else
    {
    this->t_x = this->Ui->txb_transl_x->toPlainText().toInt();
    }

  if (this->Ui->txb_transl_y->toPlainText() == "" || this->Ui->txb_transl_y->toPlainText() == "-")
    {
    this->t_y = 0.0;
    }
  else
    {
      this->t_y = this->Ui->txb_transl_y->toPlainText().toInt();
    }

  if (this->Ui->txb_transl_z->toPlainText() == "" || this->Ui->txb_transl_z->toPlainText() == "-")
    {
    this->t_z = 0.0;
    }
  else
    {
      this->t_z = this->Ui->txb_transl_z->toPlainText().toInt();
    }
}

void C_frm_Camera_Positioning_Pose::set_textbox_data ()
  {

  this->Ui->txb_nx->setText(QString::number(pose_->nx()));
     this->Ui->txb_ny->setText(QString::number(pose_->ny()));
     this->Ui->txb_nz->setText(QString::number(pose_->nz()));
     this->Ui->txb_n0->setText(QString::number(0));


     this->Ui->txb_ox->setText(QString::number(pose_->ox()));
        this->Ui->txb_oy->setText(QString::number(pose_->oy()));
        this->Ui->txb_oz->setText(QString::number(pose_->oz()));
        this->Ui->txb_o0->setText(QString::number(0));

     this->Ui->txb_ax->setText(QString::number(pose_->ax()));
        this->Ui->txb_ay->setText(QString::number(pose_->ay()));
        this->Ui->txb_az->setText(QString::number(pose_->az()));
        this->Ui->txb_a0->setText(QString::number(0));


     this->Ui->txb_px->setText(QString::number(pose_->px()));
        this->Ui->txb_py->setText(QString::number(pose_->py()));
        this->Ui->txb_pz->setText(QString::number(pose_->pz()));
        this->Ui->txb_p0->setText(QString::number(1));
  }
void C_frm_Camera_Positioning_Pose::convert_rad_to_degree ()
  {
  nx = nx * (180.0 / 3.141592653589793238463);
  ny = ny * (180.0 / 3.141592653589793238463);
  nz = nz * (180.0 / 3.141592653589793238463);
  ox = ox * (180.0 / 3.141592653589793238463);
  oy = oy * (180.0 / 3.141592653589793238463);
  oz = oz * (180.0 / 3.141592653589793238463);
  ax = ax * (180.0 / 3.141592653589793238463);
  ay = ay * (180.0 / 3.141592653589793238463);
  az = az * (180.0 / 3.141592653589793238463);
  }
void C_frm_Camera_Positioning_Pose::convert_degree_to_rad ()
  {
  nx = nx / (180.0 * 3.141592653589793238463);
  ny = ny / (180.0 * 3.141592653589793238463);
  nz = nz / (180.0 * 3.141592653589793238463);
  ox = ox / (180.0 * 3.141592653589793238463);
  oy = oy / (180.0 * 3.141592653589793238463);
  oz = oz / (180.0 * 3.141592653589793238463);
  ax = ax / (180.0 * 3.141592653589793238463);
  ay = ay / (180.0 * 3.141592653589793238463);
  az = az / (180.0 * 3.141592653589793238463);
  }

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_tait_extrinsic_zyx_clicked()
{
    this->Ui->lbl_phi_rot->setText("Rot(z, phi)");
    this->Ui->lbl_theta_rot->setText("Rot(y, theta)");
    this->Ui->lbl_theta_rot->setText("Rot(x, psi)");

    this->Ui->rb_tait_extrinsic_zyx->setChecked(true);
    this->Ui->rb_tait_intrinisc_zyx->setChecked(false);
    this->Ui->rb_euler_extrinsic_zyz->setChecked(false);
    this->Ui->rb_euler_intrinsic_zyz->setChecked(false);

    this->method = 1;


}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_euler_extrinsic_zyz_clicked()
{
    this->Ui->lbl_phi_rot->setText("Rot(z, phi)");
    this->Ui->lbl_theta_rot->setText ("Rot(y', theta)");
    this->Ui->lbl_psi_rot->setText   ("Rot(z'', psi)");

    this->Ui->rb_tait_extrinsic_zyx->setChecked(false);
    this->Ui->rb_tait_intrinisc_zyx->setChecked(false);
    this->Ui->rb_euler_extrinsic_zyz->setChecked(true);
    this->Ui->rb_euler_intrinsic_zyz->setChecked(false);


    this->method = 3;

}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_tait_intrinisc_zyx_clicked()
{
    this->Ui->lbl_phi_rot->setText("Rot(z, phi)");
    this->Ui->lbl_theta_rot->setText( "Rot(y, theta)");
    this->Ui->lbl_theta_rot->setText( "Rot(x, psi)");

    this->Ui->rb_tait_extrinsic_zyx->setChecked(false);
    this->Ui->rb_tait_intrinisc_zyx->setChecked(true);
    this->Ui->rb_euler_extrinsic_zyz->setChecked(false);
    this->Ui->rb_euler_intrinsic_zyz->setChecked(false);
    this->method = 2;

}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_euler_intrinsic_zyz_clicked()
{
    this->Ui->lbl_phi_rot->setText ("Rot(z, phi)");
    this->Ui->lbl_theta_rot->setText("Rot(y', theta)");
    this->Ui->lbl_theta_rot->setText("Rot(x'', psi)");

    this->Ui->rb_tait_extrinsic_zyx->setChecked(false);
    this->Ui->rb_tait_intrinisc_zyx->setChecked(false);
    this->Ui->rb_euler_extrinsic_zyz->setChecked(false);
    this->Ui->rb_euler_intrinsic_zyz->setChecked(true);

    this->method = 4;

}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_unit_grad_clicked()
{
    this->Ui->rb_unit_grad->setChecked(true);
    this->Ui->rb_unit_radiant->setChecked(false);
    this->convert_to_degree_active = true;

}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_rb_unit_radiant_clicked()
{
    this->Ui->rb_unit_grad->setChecked(false);
    this->Ui->rb_unit_radiant->setChecked(true);
    this->convert_to_degree_active = true;

}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_bt_exit_clicked()
{
 this->close();
}

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_bt_appy_clicked()
  {
  //this->Main->cameraManager->vecCameras->at(camera_id)->setCameraPose(pose_);
  this->GlobalObjects->saveManager->saveCameraCos(*this->Main->cameraManager->vecCameras->at(camera_id));
  }

void frm_Camera_Positioning_Pose::C_frm_Camera_Positioning_Pose::on_num_camera_valueChanged(int arg1)
{
    this->camera_id = arg1;
}
