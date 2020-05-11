#include "frm_Camera_Positioning_Pose.h"

using namespace nmsp_frm_camera_positioning_pose;


c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose(C_GlobalObjects* GlobalObjects, C_Main^ Main)
    {

    InitializeComponent();
    this->GlobalObjects     = GlobalObjects;
    this->Main              = Main;
    this->current_camera_id = 0;
    this->Zaehler           = 0;
    this->method            = 1;
    nx, ny, nz,  ox, oy, oz,  ax, ay, az,  px, py, pz, n0, a0, o0 = 0.0;
      p0 = 1.0;
    }

c_frm_Camera_Positioning_Pose::~c_frm_Camera_Positioning_Pose()
  {
  nx, ny, nz, n0, ox, oy, oz, o0, ax, ay, az, a0, px, py, pz, p0 = 0;
  this->Zaehler           = 0;
  this->current_camera_id = 0;
  this->Main              = nullptr;
  this->GlobalObjects     = nullptr;

  if (components)
    {
    delete components;
    }
}     


System::Void c_frm_Camera_Positioning_Pose::tait_extrinsic_zyx ()
  {
  double temp = 0;

  this->nx = cos(theta)*cos(phi);

  temp = cos(psi)*sin(phi);
  this->ny  = sin(psi)*sin(theta)*cos(phi)-temp;

  temp = sin(psi)*sin(phi);
  this->nz  = cos(psi)*cos(theta)*cos(phi)+ temp;

  this->ox  = cos(theta)*sin(phi);

  temp = cos(psi)+cos(phi);
  this->oy  = sin(psi)*sin(theta)*sin(phi)+temp;

  temp = sin(psi)*cos(phi);
  this->oz  = cos(psi)*sin(theta)*sin(phi)-temp;

  this->ax  = -sin(theta);
  this->ay  = sin(psi)*cos(theta);
  this->az  = cos(psi)*cos(theta);

  this->px  = t_x;
  this->py  = t_y;
  this->pz  = t_z;

  }
System::Void c_frm_Camera_Positioning_Pose::tait_intrinsic_zyx ()
  {
  double temp = 0;

  this->nx = cos(phi)*cos(theta);

  this->ny = sin(phi)*cos(theta);

  this->nz = -sin(theta);

  temp = sin(phi)*cos(psi);
  this->ox = cos(phi)*sin(theta)*sin(psi)-temp;

  temp = cos(phi)+cos(psi);
  this->oy = sin(phi)*sin(theta)*sin(psi)+temp;

  this->oz = cos(theta)*sin(psi);

  temp = sin(phi)+sin(psi);
  this->ax = cos(phi)*sin(theta)*cos(psi)+temp;

  temp = cos(phi)*sin(psi);
  this->ay = sin(phi)*sin(theta)*cos(psi)-temp;

  this->az = cos(theta)*cos(psi);

  this->px = t_x;
  this->py = t_y;
  this->pz = t_z;


  }
System::Void c_frm_Camera_Positioning_Pose::euler_extrinsic_zyz ()
  {
  double temp = 0;

  temp = sin(psi)*sin(phi);
  this->nx = cos(psi)*cos(theta)*cos(phi)-temp;

  temp = cos(psi)*sin(phi);
  this->ny  = sin(psi)*cos(theta)*cos(phi)+temp;

  this->nz  = -sin(theta)*cos(phi);

  temp = sin(psi)*cos(phi);
  this->ox  = -cos(psi)*cos(theta)*sin(phi)-temp;

  temp = cos(psi)*cos(phi);
  this->oy  = -sin(psi)*cos(theta)*sin(phi)+temp;

  this->oz  = sin(theta)*sin(phi);

  this->ax  = cos(psi)*sin(theta);

  this->ay  = sin(psi)*sin(theta);

  this->az  = cos(theta);

  this->px  = t_x;
  this->py  = t_y;
  this->pz  = t_z;

  }
System::Void c_frm_Camera_Positioning_Pose::euler_intrinsic_zyz ()
  {
  double temp = 0;

  temp = sin(phi)*sin(psi);
  this->nx  = cos(phi)*cos(theta)*cos(psi)-temp;

  temp = cos(phi)*sin(psi);
  this->ny  = sin(phi)*cos(theta)*cos(psi)+temp;

  this->nz  = -sin(theta)*cos(psi);

  temp = sin(phi)*cos(psi);
  this->ox  = -cos(phi)*cos(theta)*sin(psi)-temp;

  temp = cos(phi)*cos(psi);
  this->oy  = -sin(phi)*cos(theta)*sin(psi)+temp;

  this->oz  = sin(theta)*sin(psi);

  this->ax  = cos(phi)*sin(theta);

  this->ay  = sin(phi)*sin(theta);

  this->az  = cos(theta);

  this->px  = t_x;
  this->py  = t_y;
  this->pz  = t_z;

  }
System::Void c_frm_Camera_Positioning_Pose::calculation_method ()
  {
  switch(method)
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
System::Void c_frm_Camera_Positioning_Pose::get_textbox_data()
  {
  double temp;
  if(this->txb_phi->Text == ""||this->txb_phi->Text == "-")
    {
    this->phi = 0.0;
    }
  else
    {
    temp        =   Convert::ToInt32 (txb_phi->Text);
    this->phi   =  (temp*3.141592653589793238463)/180.0;
    }

  if (this->txb_theta->Text == ""||this->txb_theta->Text == "-")
    {
    this->theta = 0.0;
    }
  else
    {
    temp        =   Convert::ToInt32 (txb_theta->Text);
    this->theta   =  (temp*3.141592653589793238463)/180.0;
    }

  if (this->txb_psi->Text == "" ||this->txb_psi->Text == "-")
    {
    this->psi = 0.0;
    }
  else
    {
    temp        =   Convert::ToInt32 (txb_psi->Text);
    this->psi   =  (temp*3.141592653589793238463)/180.0;
    }

  if (this->txb_t_x->Text == ""||this->txb_t_x->Text == "-")
    {
    this->t_x = 0.0;
    }
  else
    {
    this->t_x = Convert::ToInt32 (txb_t_x->Text);
    }

  if (this->txb_t_y->Text == ""||this->txb_t_y->Text == "-")
    {
    this->t_y = 0.0;
    }
  else
    {
    this->t_y = Convert::ToInt32 (txb_t_y->Text);
    }

  if (this->txb_t_z->Text == ""||this->txb_t_z->Text == "-")
    {
    this->t_z = 0.0;
    }
  else
    {
    this->t_z = Convert::ToInt32 (txb_t_z->Text);
    }


  }
System::Void c_frm_Camera_Positioning_Pose::set_textbox_data()
  {
  this->txtb_nx->Text =   this->nx.ToString();
  this->txtb_ny->Text =   this->ny.ToString();
  this->txtb_nz->Text =   this->nz.ToString();
  this->txtb_n0->Text =   this->n0.ToString();


  this->txtb_ox->Text =   this->ox.ToString();
  this->txtb_oy->Text =   this->oy.ToString();
  this->txtb_oz->Text =   this->oz.ToString();
  this->txtb_o0->Text =   this->o0.ToString();

  this->txtb_ax->Text =   this->ax.ToString();
  this->txtb_ay->Text =   this->ay.ToString();
  this->txtb_az->Text =   this->az.ToString();
  this->txtb_a0->Text =   this->a0.ToString();


  this->txtb_px->Text =   this->px.ToString();
  this->txtb_py->Text =   this->py.ToString();
  this->txtb_pz->Text =   this->pz.ToString();
  this->txtb_p0->Text =   this->p0.ToString();

  }
System::Void c_frm_Camera_Positioning_Pose::convert_rad_to_degree ()
  {
  nx = nx*(180.0/3.141592653589793238463);
  ny = ny*(180.0/3.141592653589793238463);
  nz = nz*(180.0/3.141592653589793238463);
  ox = ox*(180.0/3.141592653589793238463);
  oy = oy*(180.0/3.141592653589793238463);
  oz = oz*(180.0/3.141592653589793238463);
  ax = ax*(180.0/3.141592653589793238463);
  ay = ay*(180.0/3.141592653589793238463);
  az = az*(180.0/3.141592653589793238463);
  }
System::Void c_frm_Camera_Positioning_Pose::convert_degree_to_rad ()
  {
  nx = nx/(180.0*3.141592653589793238463);
  ny = ny/(180.0*3.141592653589793238463);
  nz = nz/(180.0*3.141592653589793238463);
  ox = ox/(180.0*3.141592653589793238463);
  oy = oy/(180.0*3.141592653589793238463);
  oz = oz/(180.0*3.141592653589793238463);
  ax = ax/(180.0*3.141592653589793238463);
  ay = ay/(180.0*3.141592653589793238463);
  az = az/(180.0*3.141592653589793238463);
  }
System::Void c_frm_Camera_Positioning_Pose::Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e)
      {
  this->txtb_counter->Text = System::String::Format ("{0:0}", this->Zaehler++);

  this->get_textbox_data();
  calculation_method();
  if (convert_to_degree_active) convert_rad_to_degree();
  set_textbox_data();

      }
System::Void c_frm_Camera_Positioning_Pose::bt_exit_Click(System::Object^  sender, System::EventArgs^  e)
      {
  this->Close();
      }
System::Void c_frm_Camera_Positioning_Pose::bt_apply_Click(System::Object^  sender, System::EventArgs^  e)
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

  this->Main->camera_managed->camera_unmanaged->save_camera_cos (current_camera_id, *pose_);
  }

System::Void c_frm_Camera_Positioning_Pose::rB_Tait_extrinsic_zyx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y, theta)";
  this->lbl_psi_rot->Text   = "Rot(x, psi)";

  this->rB_Tait_intrinsic_zyx->Checked = false;
  this->rB_euler_extrinsic_zyz->Checked = false;
  this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 1;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_Tait_intrinsic_zyx_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y, theta)";
  this->lbl_psi_rot->Text   = "Rot(x, psi)";

  this->rB_Tait_extrinsic_zyx->Checked = false;
  this->rB_euler_extrinsic_zyz->Checked = false;
  this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 2;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_euler_extrinsic_zyz_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y', theta)";
  this->lbl_psi_rot->Text   = "Rot(z'', psi)";

  this->rB_Tait_extrinsic_zyx->Checked = false;
  this->rB_Tait_intrinsic_zyx->Checked = false;
  this->rB_euler_intrinsic_zyz->Checked = false;

  this->method = 3;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_euler_intrinsic_zyz_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
  {
  this->lbl_phi_rot->Text   = "Rot(z, phi)";
  this->lbl_theta_rot->Text = "Rot(y', theta)";
  this->lbl_psi_rot->Text   = "Rot(x'', psi)";

  this->rB_Tait_extrinsic_zyx->Checked = false;
  this->rB_Tait_intrinsic_zyx->Checked = false;
  this->rB_euler_extrinsic_zyz->Checked = false;

  this->method = 4;
  }
System::Void c_frm_Camera_Positioning_Pose::rB_Grad_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
      {
      rB_radiant->Checked = false;
      this->convert_to_degree_active = true;
      }
System::Void c_frm_Camera_Positioning_Pose::rB_radiant_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
      {
      rB_Grad->Checked = false;
      this->convert_to_degree_active = false;
      }
System::Void c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_Load(System::Object^  sender, System::EventArgs^  e)
      {
  this->Zaehler             = 0;
  this->Taktgeber->Interval = 100;
  this->Taktgeber->Enabled  = true;

      }
System::Void c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
      {
  this->Taktgeber->Enabled = false;
      }



