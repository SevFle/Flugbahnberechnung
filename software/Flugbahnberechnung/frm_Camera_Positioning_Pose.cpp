#include "frm_Camera_Positioning_Pose.h"

using namespace nmsp_frm_camera_positioning_pose;


c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose (C_GlobalObjects* GlobalObjects, C_Main^ Main)
  {
  InitializeComponent();
  this->GlobalObjects                                        = GlobalObjects;
  this->Main                                                 = Main;
  this->convert_to_degree_active                             = false;
  this->current_camera_id                                    = 0;
  this->Zaehler                                              = 0;
  this->method                                               = 1;
  nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz, n0, a0, o0 = 0.0;
  p0                                                         = 1.0;
  this->pose_ =    new C_AbsolutePose();
  }

c_frm_Camera_Positioning_Pose::~c_frm_Camera_Positioning_Pose ()
  {
  delete(pose_);
  this->pose_ = nullptr;
  nx, ny, nz, n0, ox, oy, oz, o0, ax, ay, az, a0, px, py, pz, p0 = 0;
  this->Zaehler                                                  = 0;
  this->current_camera_id                                        = 0;
  this->Main                                                     = nullptr;
  this->GlobalObjects                                            = nullptr;

  if (components)
    {
    delete components;
    }
  }


System::Void c_frm_Camera_Positioning_Pose::tait_extrinsic_zyx ()
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
System::Void c_frm_Camera_Positioning_Pose::tait_intrinsic_zyx ()
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
System::Void c_frm_Camera_Positioning_Pose::euler_extrinsic_zyz ()
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
System::Void c_frm_Camera_Positioning_Pose::euler_intrinsic_zyz ()
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
System::Void c_frm_Camera_Positioning_Pose::calculation_method ()
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
System::Void c_frm_Camera_Positioning_Pose::get_textbox_data ()
  {
  double temp;

  //TODO Input PHI, PSI, Theta -> Deg oder rad?
  if (this->txb_phi->Text == "" || this->txb_phi->Text == "-")
    {
    this->phi = 0.0;
    }
  else
    {
    this->phi = Convert::ToInt32 (txb_phi->Text) * 3.141592653589793238463 / 180.0;
    }

  if (this->txb_theta->Text == "" || this->txb_theta->Text == "-")
    {
    this->theta = 0.0;
    }
  else
    {
    this->theta = Convert::ToInt32 (txb_theta->Text) * 3.141592653589793238463 / 180.0;
    }

  if (this->txb_psi->Text == "" || this->txb_psi->Text == "-")
    {
    this->psi = 0.0;
    }
  else
    {
    this->psi = Convert::ToInt32 (txb_psi->Text) * 3.141592653589793238463 / 180.0;
    }

  if (this->txb_t_x->Text == "" || this->txb_t_x->Text == "-")
    {
    this->t_x = 0.0;
    }
  else
    {
    this->t_x = Convert::ToInt32 (txb_t_x->Text);
    }

  if (this->txb_t_y->Text == "" || this->txb_t_y->Text == "-")
    {
    this->t_y = 0.0;
    }
  else
    {
    this->t_y = Convert::ToInt32 (txb_t_y->Text);
    }

  if (this->txb_t_z->Text == "" || this->txb_t_z->Text == "-")
    {
    this->t_z = 0.0;
    }
  else
    {
    this->t_z = Convert::ToInt32 (txb_t_z->Text);
    }
  }
System::Void c_frm_Camera_Positioning_Pose::set_textbox_data ()
  {
  
  this->txtb_nx->Text = pose_->nx().ToString();
  this->txtb_ny->Text = pose_->ny().ToString();
  this->txtb_nz->Text = pose_->nz().ToString();
  this->txtb_n0->Text = "0";


  this->txtb_ox->Text = pose_->ox().ToString();
  this->txtb_oy->Text = pose_->oy().ToString();
  this->txtb_oz->Text = pose_->oz().ToString();
  this->txtb_o0->Text ="0";

  this->txtb_ax->Text = pose_->ax().ToString();
  this->txtb_ay->Text = pose_->ay().ToString();
  this->txtb_az->Text = pose_->az().ToString();
  this->txtb_a0->Text = "0";


  this->txtb_px->Text =  pose_->px().ToString();
  this->txtb_py->Text =  pose_->py().ToString();
  this->txtb_pz->Text =  pose_->pz().ToString();
  this->txtb_p0->Text =   "1";
  }
System::Void c_frm_Camera_Positioning_Pose::convert_rad_to_degree ()
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
System::Void c_frm_Camera_Positioning_Pose::convert_degree_to_rad ()
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

System::Void c_frm_Camera_Positioning_Pose::Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e)
  {
  this->txtb_counter->Text = System::String::Format ("{0:0}",this->Zaehler++);

  this->get_textbox_data();
  calculation_method();
  if (convert_to_degree_active) convert_rad_to_degree();
  set_textbox_data();
  }
System::Void c_frm_Camera_Positioning_Pose::bt_exit_Click (System::Object^ sender, System::EventArgs^ e)
  {
  this->Close();
  }
System::Void c_frm_Camera_Positioning_Pose::bt_apply_Click (System::Object^ sender, System::EventArgs^ e)
  {
  //C_AbsolutePose temp;

  //temp.px(pose_->px());
  //temp.py(pose_->py());
  //temp.pz(pose_->pz());

  //temp.nx(pose_->nx());
  //temp.ny(pose_->ny());
  //temp.nz(pose_->nz());

  //temp.ox(pose_->ox());
  //temp.oy(pose_->oy());
  //temp.oz(pose_->oz());

  //temp.ax(pose_->ax());
  //temp.ay(pose_->ay());
  //temp.az(pose_->az());

  this->Main->camera_managed->camera_unmanaged->save_camera_cos (current_camera_id,*pose_);
  }

System::Void c_frm_Camera_Positioning_Pose::rB_Tait_extrinsic_zyx_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y, theta)";
  this->lbl_psi_rot->Text   = "Rot(x, psi)";

  //this->rB_Tait_extrinsic_zyx->Checked = true;
  //this->rB_Tait_intrinsic_zyx->Checked  = false;
  //this->rB_euler_extrinsic_zyz->Checked = false;
  //this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 1;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_Tait_intrinsic_zyx_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y, theta)";
  this->lbl_psi_rot->Text   = "Rot(x, psi)";

  //this->rB_Tait_intrinsic_zyx->Checked = true;
  //this->rB_Tait_extrinsic_zyx->Checked  = false;
  //this->rB_euler_extrinsic_zyz->Checked = false;
  //this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 2;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_euler_extrinsic_zyz_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y', theta)";
  this->lbl_psi_rot->Text   = "Rot(z'', psi)";

  //this->rB_euler_extrinsic_zyz->Checked = true;
  //this->rB_Tait_extrinsic_zyx->Checked  = false;
  //this->rB_Tait_intrinsic_zyx->Checked  = false;
  //this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 3;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_euler_intrinsic_zyz_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y', theta)";
  this->lbl_psi_rot->Text   = "Rot(x'', psi)";

  //this->rB_euler_intrinsic_zyz->Checked = true;
  //this->rB_Tait_extrinsic_zyx->Checked  = false;
  //this->rB_Tait_intrinsic_zyx->Checked  = false;
  //this->rB_euler_extrinsic_zyz->Checked = false;

  this->method = 4;
  }

System::Void c_frm_Camera_Positioning_Pose::rB_Grad_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
  //rB_Grad->Checked        = true;
  //rB_radiant->Checked            = false;
  //this->convert_to_degree_active = true;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_radiant_CheckedChanged (System::Object^ sender, System::EventArgs^ e)
  {
 // rB_radiant->Checked        = true;
  //rB_Grad->Checked               = false;
  //this->convert_to_degree_active = false;
  }

System::Void c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_Load (System::Object^ sender, System::EventArgs^ e)
  {
  this->Zaehler             = 0;
  this->Taktgeber->Interval = 100;
  this->Taktgeber->Enabled  = true;
  }
System::Void c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_FormClosing (System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
  {
  this->Taktgeber->Enabled = false;
  }
