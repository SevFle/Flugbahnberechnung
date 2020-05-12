#pragma once
#include "Main.h"

#define PI = 3.141592653589793238463


namespace nmsp_frm_camera_positioning_pose
  {
  public ref class c_frm_Camera_Positioning_Pose : public System::Windows::Forms::Form
    {
    public:
    c_frm_Camera_Positioning_Pose (C_GlobalObjects* GlobalObjects, C_Main^ Main);
    protected:
    ~c_frm_Camera_Positioning_Pose ();

    private:
    C_GlobalObjects* GlobalObjects;
    C_Main^          Main;

    UInt32 Zaehler;
    UInt32 current_camera_id;


    double phi;
    double theta;
    double psi;

    bool convert_to_degree_active;

    int t_x;
    int t_y;
    int t_z;

    int method;

    double nx, ny, nz, n0, ox, oy, oz, o0, ax, ay, az, a0, px, py, pz, p0;

    C_AbsolutePose* pose_;


    private:
    System::Windows::Forms::Button^ bt_apply;
    protected:
    private:
    System::Windows::Forms::TextBox^ txtb_counter;
    private:
    System::Windows::Forms::Button^ bt_exit;
    private:
    System::Windows::Forms::Timer^ Taktgeber;
    private:
    System::Windows::Forms::Label^ lbl_camera_id;
    private:
    System::Windows::Forms::NumericUpDown^ nup_camera_id;
    private:
    System::Windows::Forms::TextBox^ txb_phi;
    private:
    System::Windows::Forms::TextBox^ txb_theta;
    private:
    System::Windows::Forms::TextBox^ txb_psi;


    private:
    System::Windows::Forms::TextBox^ txtb_az;
    private:
    System::Windows::Forms::TextBox^ txtb_ay;
    private:
    System::Windows::Forms::TextBox^ txtb_ax;
    private:
    System::Windows::Forms::TextBox^ txtb_nz;
    private:
    System::Windows::Forms::TextBox^ txtb_ny;
    private:
    System::Windows::Forms::TextBox^ txtb_nx;
    private:
    System::Windows::Forms::TextBox^ txtb_oz;
    private:
    System::Windows::Forms::TextBox^ txtb_oy;
    private:
    System::Windows::Forms::TextBox^ txtb_ox;
    private:
    System::Windows::Forms::TextBox^ txtb_pz;
    private:
    System::Windows::Forms::TextBox^ txtb_py;
    private:
    System::Windows::Forms::TextBox^ txtb_px;
    private:
    System::Windows::Forms::TextBox^ txtb_p0;
    private:
    System::Windows::Forms::TextBox^ txtb_o0;
    private:
    System::Windows::Forms::TextBox^ txtb_n0;
    private:
    System::Windows::Forms::TextBox^ txtb_a0;
    private:
    System::Windows::Forms::GroupBox^ groupBox1;
    private:
    System::Windows::Forms::Label^ label3;
    private:
    System::Windows::Forms::Label^ label2;
    private:
    System::Windows::Forms::Label^ label1;
    private:
    System::Windows::Forms::Label^ lbl_n;
    private:
    System::Windows::Forms::Label^ lbl_phi_rot;
    private:
    System::Windows::Forms::Label^ lbl_theta_rot;
    private:
    System::Windows::Forms::Label^ lbl_psi_rot;


    private:
    System::Windows::Forms::GroupBox^ groupBox2;
    private:
    System::Windows::Forms::GroupBox^ groupBox3;
    private:
    System::Windows::Forms::Label^ label6;
    private:
    System::Windows::Forms::Label^ label7;
    private:
    System::Windows::Forms::Label^ label8;
    private:
    System::Windows::Forms::TextBox^ txb_t_z;

    private:
    System::Windows::Forms::TextBox^ txb_t_y;

    private:
    System::Windows::Forms::TextBox^ txb_t_x;

    private:
    System::Windows::Forms::Label^ label9;
    private:
    System::Windows::Forms::GroupBox^ groupBox4;
    private:
    System::Windows::Forms::Label^ label11;
    private:
    System::Windows::Forms::Label^ label10;
    private:
    System::Windows::Forms::RadioButton^ rB_euler_intrinsic_zyz;
    private:
    System::Windows::Forms::RadioButton^ rB_euler_extrinsic_zyz;
    private:
    System::Windows::Forms::RadioButton^ rB_Tait_intrinsic_zyx;
    private:
    System::Windows::Forms::RadioButton^ rB_Tait_extrinsic_zyx;
    private:
    System::Windows::Forms::Label^ label4;
    private:
    System::Windows::Forms::RadioButton^ rB_radiant;
    private:
    System::Windows::Forms::RadioButton^ rB_Grad;
    private:
    System::ComponentModel::IContainer^ components;

    private:
#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent (void)
      {
      this->components             = (gcnew System::ComponentModel::Container());
      this->bt_apply               = (gcnew System::Windows::Forms::Button());
      this->txtb_counter           = (gcnew System::Windows::Forms::TextBox());
      this->bt_exit                = (gcnew System::Windows::Forms::Button());
      this->Taktgeber              = (gcnew System::Windows::Forms::Timer (this->components));
      this->lbl_camera_id          = (gcnew System::Windows::Forms::Label());
      this->nup_camera_id          = (gcnew System::Windows::Forms::NumericUpDown());
      this->txb_phi                = (gcnew System::Windows::Forms::TextBox());
      this->txb_theta              = (gcnew System::Windows::Forms::TextBox());
      this->txb_psi                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_az                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_ay                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_ax                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_nz                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_ny                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_nx                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_oz                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_oy                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_ox                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_pz                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_py                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_px                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_p0                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_o0                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_n0                = (gcnew System::Windows::Forms::TextBox());
      this->txtb_a0                = (gcnew System::Windows::Forms::TextBox());
      this->groupBox1              = (gcnew System::Windows::Forms::GroupBox());
      this->label3                 = (gcnew System::Windows::Forms::Label());
      this->label2                 = (gcnew System::Windows::Forms::Label());
      this->label1                 = (gcnew System::Windows::Forms::Label());
      this->lbl_n                  = (gcnew System::Windows::Forms::Label());
      this->lbl_phi_rot            = (gcnew System::Windows::Forms::Label());
      this->lbl_theta_rot          = (gcnew System::Windows::Forms::Label());
      this->lbl_psi_rot            = (gcnew System::Windows::Forms::Label());
      this->groupBox2              = (gcnew System::Windows::Forms::GroupBox());
      this->groupBox3              = (gcnew System::Windows::Forms::GroupBox());
      this->label6                 = (gcnew System::Windows::Forms::Label());
      this->label7                 = (gcnew System::Windows::Forms::Label());
      this->label8                 = (gcnew System::Windows::Forms::Label());
      this->txb_t_z                = (gcnew System::Windows::Forms::TextBox());
      this->txb_t_y                = (gcnew System::Windows::Forms::TextBox());
      this->txb_t_x                = (gcnew System::Windows::Forms::TextBox());
      this->label9                 = (gcnew System::Windows::Forms::Label());
      this->groupBox4              = (gcnew System::Windows::Forms::GroupBox());
      this->label11                = (gcnew System::Windows::Forms::Label());
      this->label10                = (gcnew System::Windows::Forms::Label());
      this->rB_euler_intrinsic_zyz = (gcnew System::Windows::Forms::RadioButton());
      this->rB_euler_extrinsic_zyz = (gcnew System::Windows::Forms::RadioButton());
      this->rB_Tait_intrinsic_zyx  = (gcnew System::Windows::Forms::RadioButton());
      this->rB_Tait_extrinsic_zyx  = (gcnew System::Windows::Forms::RadioButton());
      this->rB_Grad                = (gcnew System::Windows::Forms::RadioButton());
      this->rB_radiant             = (gcnew System::Windows::Forms::RadioButton());
      this->label4                 = (gcnew System::Windows::Forms::Label());
      (cli::
      safe_cast<System::ComponentModel::ISupportInitialize^> (this->nup_camera_id)
      )
      ->
      BeginInit();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->groupBox4->SuspendLayout();
      this->SuspendLayout();
      // 
      // bt_apply
      // 
      this->bt_apply->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                           static_cast<System::Byte> (0)));
      this->bt_apply->Location                = System::Drawing::Point (573,250);
      this->bt_apply->Name                    = L"bt_apply";
      this->bt_apply->Size                    = System::Drawing::Size (167,73);
      this->bt_apply->TabIndex                = 16;
      this->bt_apply->Text                    = L"Apply";
      this->bt_apply->UseVisualStyleBackColor = true;
      this->bt_apply->Click += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::bt_apply_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point (573,420);
      this->txtb_counter->Name     = L"txtb_counter";
      this->txtb_counter->Size     = System::Drawing::Size (166,20);
      this->txtb_counter->TabIndex = 14;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                          static_cast<System::Byte> (0)));
      this->bt_exit->Location                = System::Drawing::Point (573,341);
      this->bt_exit->Name                    = L"bt_exit";
      this->bt_exit->Size                    = System::Drawing::Size (167,73);
      this->bt_exit->TabIndex                = 15;
      this->bt_exit->Text                    = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::bt_exit_Click);
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::Taktgeber_Tick);
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font     = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                                    static_cast<System::Byte> (0)));
      this->lbl_camera_id->Location = System::Drawing::Point (61,413);
      this->lbl_camera_id->Name     = L"lbl_camera_id";
      this->lbl_camera_id->Size     = System::Drawing::Size (15,24);
      this->lbl_camera_id->TabIndex = 18;
      this->lbl_camera_id->Text     = L" ";
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                                static_cast<System::Byte> (0)));
      this->nup_camera_id->Location = System::Drawing::Point (140,413);
      this->nup_camera_id->Name     = L"nup_camera_id";
      this->nup_camera_id->Size     = System::Drawing::Size (34,29);
      this->nup_camera_id->TabIndex = 17;
      // 
      // txb_phi
      // 
      this->txb_phi->Location = System::Drawing::Point (78,34);
      this->txb_phi->Name     = L"txb_phi";
      this->txb_phi->Size     = System::Drawing::Size (89,20);
      this->txb_phi->TabIndex = 19;
      // 
      // txb_theta
      // 
      this->txb_theta->Location = System::Drawing::Point (78,77);
      this->txb_theta->Name     = L"txb_theta";
      this->txb_theta->Size     = System::Drawing::Size (89,20);
      this->txb_theta->TabIndex = 20;
      // 
      // txb_psi
      // 
      this->txb_psi->Location = System::Drawing::Point (78,120);
      this->txb_psi->Name     = L"txb_psi";
      this->txb_psi->Size     = System::Drawing::Size (89,20);
      this->txb_psi->TabIndex = 21;
      // 
      // txtb_az
      // 
      this->txtb_az->Location = System::Drawing::Point (206,94);
      this->txtb_az->Name     = L"txtb_az";
      this->txtb_az->ReadOnly = true;
      this->txtb_az->Size     = System::Drawing::Size (89,20);
      this->txtb_az->TabIndex = 24;
      // 
      // txtb_ay
      // 
      this->txtb_ay->Location = System::Drawing::Point (206,68);
      this->txtb_ay->Name     = L"txtb_ay";
      this->txtb_ay->ReadOnly = true;
      this->txtb_ay->Size     = System::Drawing::Size (89,20);
      this->txtb_ay->TabIndex = 23;
      // 
      // txtb_ax
      // 
      this->txtb_ax->Location = System::Drawing::Point (206,42);
      this->txtb_ax->Name     = L"txtb_ax";
      this->txtb_ax->ReadOnly = true;
      this->txtb_ax->Size     = System::Drawing::Size (89,20);
      this->txtb_ax->TabIndex = 22;
      // 
      // txtb_nz
      // 
      this->txtb_nz->Location = System::Drawing::Point (16,94);
      this->txtb_nz->Name     = L"txtb_nz";
      this->txtb_nz->ReadOnly = true;
      this->txtb_nz->Size     = System::Drawing::Size (89,20);
      this->txtb_nz->TabIndex = 27;
      // 
      // txtb_ny
      // 
      this->txtb_ny->Location = System::Drawing::Point (16,68);
      this->txtb_ny->Name     = L"txtb_ny";
      this->txtb_ny->ReadOnly = true;
      this->txtb_ny->Size     = System::Drawing::Size (89,20);
      this->txtb_ny->TabIndex = 26;
      // 
      // txtb_nx
      // 
      this->txtb_nx->Location = System::Drawing::Point (16,42);
      this->txtb_nx->Name     = L"txtb_nx";
      this->txtb_nx->ReadOnly = true;
      this->txtb_nx->Size     = System::Drawing::Size (89,20);
      this->txtb_nx->TabIndex = 25;
      // 
      // txtb_oz
      // 
      this->txtb_oz->Location = System::Drawing::Point (111,94);
      this->txtb_oz->Name     = L"txtb_oz";
      this->txtb_oz->ReadOnly = true;
      this->txtb_oz->Size     = System::Drawing::Size (89,20);
      this->txtb_oz->TabIndex = 30;
      // 
      // txtb_oy
      // 
      this->txtb_oy->Location = System::Drawing::Point (111,68);
      this->txtb_oy->Name     = L"txtb_oy";
      this->txtb_oy->ReadOnly = true;
      this->txtb_oy->Size     = System::Drawing::Size (89,20);
      this->txtb_oy->TabIndex = 29;
      // 
      // txtb_ox
      // 
      this->txtb_ox->Location = System::Drawing::Point (111,42);
      this->txtb_ox->Name     = L"txtb_ox";
      this->txtb_ox->ReadOnly = true;
      this->txtb_ox->Size     = System::Drawing::Size (89,20);
      this->txtb_ox->TabIndex = 28;
      // 
      // txtb_pz
      // 
      this->txtb_pz->Location = System::Drawing::Point (301,94);
      this->txtb_pz->Name     = L"txtb_pz";
      this->txtb_pz->ReadOnly = true;
      this->txtb_pz->Size     = System::Drawing::Size (89,20);
      this->txtb_pz->TabIndex = 33;
      // 
      // txtb_py
      // 
      this->txtb_py->Location = System::Drawing::Point (301,68);
      this->txtb_py->Name     = L"txtb_py";
      this->txtb_py->ReadOnly = true;
      this->txtb_py->Size     = System::Drawing::Size (89,20);
      this->txtb_py->TabIndex = 32;
      // 
      // txtb_px
      // 
      this->txtb_px->Location = System::Drawing::Point (301,42);
      this->txtb_px->Name     = L"txtb_px";
      this->txtb_px->ReadOnly = true;
      this->txtb_px->Size     = System::Drawing::Size (89,20);
      this->txtb_px->TabIndex = 31;
      // 
      // txtb_p0
      // 
      this->txtb_p0->Location = System::Drawing::Point (301,120);
      this->txtb_p0->Name     = L"txtb_p0";
      this->txtb_p0->ReadOnly = true;
      this->txtb_p0->Size     = System::Drawing::Size (89,20);
      this->txtb_p0->TabIndex = 37;
      this->txtb_p0->Text     = L"1";
      // 
      // txtb_o0
      // 
      this->txtb_o0->Location = System::Drawing::Point (111,120);
      this->txtb_o0->Name     = L"txtb_o0";
      this->txtb_o0->ReadOnly = true;
      this->txtb_o0->Size     = System::Drawing::Size (89,20);
      this->txtb_o0->TabIndex = 36;
      this->txtb_o0->Text     = L"0";
      // 
      // txtb_n0
      // 
      this->txtb_n0->Location = System::Drawing::Point (16,120);
      this->txtb_n0->Name     = L"txtb_n0";
      this->txtb_n0->ReadOnly = true;
      this->txtb_n0->Size     = System::Drawing::Size (89,20);
      this->txtb_n0->TabIndex = 35;
      this->txtb_n0->Text     = L"0";
      // 
      // txtb_a0
      // 
      this->txtb_a0->Location = System::Drawing::Point (206,120);
      this->txtb_a0->Name     = L"txtb_a0";
      this->txtb_a0->ReadOnly = true;
      this->txtb_a0->Size     = System::Drawing::Size (89,20);
      this->txtb_a0->TabIndex = 34;
      this->txtb_a0->Text     = L"0";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add (this->label3);
      this->groupBox1->Controls->Add (this->label2);
      this->groupBox1->Controls->Add (this->label1);
      this->groupBox1->Controls->Add (this->lbl_n);
      this->groupBox1->Controls->Add (this->txtb_p0);
      this->groupBox1->Controls->Add (this->txtb_o0);
      this->groupBox1->Controls->Add (this->txtb_n0);
      this->groupBox1->Controls->Add (this->txtb_a0);
      this->groupBox1->Controls->Add (this->txtb_pz);
      this->groupBox1->Controls->Add (this->txtb_py);
      this->groupBox1->Controls->Add (this->txtb_px);
      this->groupBox1->Controls->Add (this->txtb_oz);
      this->groupBox1->Controls->Add (this->txtb_oy);
      this->groupBox1->Controls->Add (this->txtb_ox);
      this->groupBox1->Controls->Add (this->txtb_nz);
      this->groupBox1->Controls->Add (this->txtb_ny);
      this->groupBox1->Controls->Add (this->txtb_nx);
      this->groupBox1->Controls->Add (this->txtb_az);
      this->groupBox1->Controls->Add (this->txtb_ay);
      this->groupBox1->Controls->Add (this->txtb_ax);
      this->groupBox1->Location = System::Drawing::Point (12,202);
      this->groupBox1->Name     = L"groupBox1";
      this->groupBox1->Size     = System::Drawing::Size (423,164);
      this->groupBox1->TabIndex = 41;
      this->groupBox1->TabStop  = false;
      this->groupBox1->Text     = L"Absolute Pose";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point (338,26);
      this->label3->Name     = L"label3";
      this->label3->Size     = System::Drawing::Size (13,13);
      this->label3->TabIndex = 41;
      this->label3->Text     = L"p";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point (243,26);
      this->label2->Name     = L"label2";
      this->label2->Size     = System::Drawing::Size (13,13);
      this->label2->TabIndex = 40;
      this->label2->Text     = L"a";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point (149,26);
      this->label1->Name     = L"label1";
      this->label1->Size     = System::Drawing::Size (13,13);
      this->label1->TabIndex = 39;
      this->label1->Text     = L"o";
      // 
      // lbl_n
      // 
      this->lbl_n->AutoSize = true;
      this->lbl_n->Location = System::Drawing::Point (51,26);
      this->lbl_n->Name     = L"lbl_n";
      this->lbl_n->Size     = System::Drawing::Size (13,13);
      this->lbl_n->TabIndex = 38;
      this->lbl_n->Text     = L"n";
      // 
      // lbl_phi_rot
      // 
      this->lbl_phi_rot->AutoSize = true;
      this->lbl_phi_rot->Location = System::Drawing::Point (5,37);
      this->lbl_phi_rot->Name     = L"lbl_phi_rot";
      this->lbl_phi_rot->Size     = System::Drawing::Size (58,13);
      this->lbl_phi_rot->TabIndex = 42;
      this->lbl_phi_rot->Text     = L"Rot (x, phi)";
      // 
      // lbl_theta_rot
      // 
      this->lbl_theta_rot->AutoSize = true;
      this->lbl_theta_rot->Location = System::Drawing::Point (6,84);
      this->lbl_theta_rot->Name     = L"lbl_theta_rot";
      this->lbl_theta_rot->Size     = System::Drawing::Size (68,13);
      this->lbl_theta_rot->TabIndex = 43;
      this->lbl_theta_rot->Text     = L"Rot (y, theta)";
      // 
      // lbl_psi_rot
      // 
      this->lbl_psi_rot->AutoSize = true;
      this->lbl_psi_rot->Location = System::Drawing::Point (6,127);
      this->lbl_psi_rot->Name     = L"lbl_psi_rot";
      this->lbl_psi_rot->Size     = System::Drawing::Size (57,13);
      this->lbl_psi_rot->TabIndex = 44;
      this->lbl_psi_rot->Text     = L"Rot (z, psi)";
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add (this->lbl_psi_rot);
      this->groupBox2->Controls->Add (this->lbl_theta_rot);
      this->groupBox2->Controls->Add (this->lbl_phi_rot);
      this->groupBox2->Controls->Add (this->txb_psi);
      this->groupBox2->Controls->Add (this->txb_theta);
      this->groupBox2->Controls->Add (this->txb_phi);
      this->groupBox2->Location = System::Drawing::Point (12,12);
      this->groupBox2->Name     = L"groupBox2";
      this->groupBox2->Size     = System::Drawing::Size (186,162);
      this->groupBox2->TabIndex = 45;
      this->groupBox2->TabStop  = false;
      this->groupBox2->Text     = L"Rotation [Grad]";
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add (this->label6);
      this->groupBox3->Controls->Add (this->label7);
      this->groupBox3->Controls->Add (this->label8);
      this->groupBox3->Controls->Add (this->txb_t_z);
      this->groupBox3->Controls->Add (this->txb_t_y);
      this->groupBox3->Controls->Add (this->txb_t_x);
      this->groupBox3->Location = System::Drawing::Point (216,12);
      this->groupBox3->Name     = L"groupBox3";
      this->groupBox3->Size     = System::Drawing::Size (186,162);
      this->groupBox3->TabIndex = 46;
      this->groupBox3->TabStop  = false;
      this->groupBox3->Text     = L"Translation [mm]";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Location = System::Drawing::Point (14,120);
      this->label6->Name     = L"label6";
      this->label6->Size     = System::Drawing::Size (49,13);
      this->label6->TabIndex = 44;
      this->label6->Text     = L"Transl. Z";
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Location = System::Drawing::Point (14,77);
      this->label7->Name     = L"label7";
      this->label7->Size     = System::Drawing::Size (49,13);
      this->label7->TabIndex = 43;
      this->label7->Text     = L"Transl. Y";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Location = System::Drawing::Point (14,34);
      this->label8->Name     = L"label8";
      this->label8->Size     = System::Drawing::Size (49,13);
      this->label8->TabIndex = 42;
      this->label8->Text     = L"Transl. X";
      // 
      // txb_t_z
      // 
      this->txb_t_z->Location = System::Drawing::Point (78,120);
      this->txb_t_z->Name     = L"txb_t_z";
      this->txb_t_z->Size     = System::Drawing::Size (89,20);
      this->txb_t_z->TabIndex = 21;
      // 
      // txb_t_y
      // 
      this->txb_t_y->Location = System::Drawing::Point (78,77);
      this->txb_t_y->Name     = L"txb_t_y";
      this->txb_t_y->Size     = System::Drawing::Size (89,20);
      this->txb_t_y->TabIndex = 20;
      // 
      // txb_t_x
      // 
      this->txb_t_x->Location = System::Drawing::Point (78,34);
      this->txb_t_x->Name     = L"txb_t_x";
      this->txb_t_x->Size     = System::Drawing::Size (89,20);
      this->txb_t_x->TabIndex = 19;
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Location = System::Drawing::Point (63,427);
      this->label9->Name     = L"label9";
      this->label9->Size     = System::Drawing::Size (43,13);
      this->label9->TabIndex = 45;
      this->label9->Text     = L"Kamera";
      // 
      // groupBox4
      // 
      this->groupBox4->Controls->Add (this->label4);
      this->groupBox4->Controls->Add (this->rB_radiant);
      this->groupBox4->Controls->Add (this->rB_Grad);
      this->groupBox4->Controls->Add (this->label11);
      this->groupBox4->Controls->Add (this->label10);
      this->groupBox4->Controls->Add (this->rB_euler_intrinsic_zyz);
      this->groupBox4->Controls->Add (this->rB_euler_extrinsic_zyz);
      this->groupBox4->Controls->Add (this->rB_Tait_intrinsic_zyx);
      this->groupBox4->Controls->Add (this->rB_Tait_extrinsic_zyx);
      this->groupBox4->Location = System::Drawing::Point (444,12);
      this->groupBox4->Name     = L"groupBox4";
      this->groupBox4->Size     = System::Drawing::Size (295,210);
      this->groupBox4->TabIndex = 47;
      this->groupBox4->TabStop  = false;
      this->groupBox4->Text     = L"Methode";
      // 
      // label11
      // 
      this->label11->AutoSize = true;
      this->label11->Location = System::Drawing::Point (180,34);
      this->label11->Name     = L"label11";
      this->label11->Size     = System::Drawing::Size (74,13);
      this->label11->TabIndex = 46;
      this->label11->Text     = L"Euler-Rotation";
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Location = System::Drawing::Point (16,34);
      this->label10->Name     = L"label10";
      this->label10->Size     = System::Drawing::Size (98,13);
      this->label10->TabIndex = 45;
      this->label10->Text     = L"Tait-Bryan-Rotation";
      // 
      // rB_euler_intrinsic_zyz
      // 
      this->rB_euler_intrinsic_zyz->AutoSize                = true;
      this->rB_euler_intrinsic_zyz->Location                = System::Drawing::Point (183,105);
      this->rB_euler_intrinsic_zyz->Name                    = L"rB_euler_intrinsic_zyz";
      this->rB_euler_intrinsic_zyz->Size                    = System::Drawing::Size (97,17);
      this->rB_euler_intrinsic_zyz->TabIndex                = 3;
      this->rB_euler_intrinsic_zyz->Text                    = L"Intrinisch ZY\'Z\'\'";
      this->rB_euler_intrinsic_zyz->UseVisualStyleBackColor = true;
      this->rB_euler_intrinsic_zyz->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_euler_intrinsic_zyz_CheckedChanged);
      // 
      // rB_euler_extrinsic_zyz
      // 
      this->rB_euler_extrinsic_zyz->AutoSize                = true;
      this->rB_euler_extrinsic_zyz->Location                = System::Drawing::Point (183,60);
      this->rB_euler_extrinsic_zyz->Name                    = L"rB_euler_extrinsic_zyz";
      this->rB_euler_extrinsic_zyz->Size                    = System::Drawing::Size (99,17);
      this->rB_euler_extrinsic_zyz->TabIndex                = 2;
      this->rB_euler_extrinsic_zyz->Text                    = L"Extrinsisch ZYZ";
      this->rB_euler_extrinsic_zyz->UseVisualStyleBackColor = true;
      this->rB_euler_extrinsic_zyz->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_euler_extrinsic_zyz_CheckedChanged);
      // 
      // rB_Tait_intrinsic_zyx
      // 
      this->rB_Tait_intrinsic_zyx->AutoSize                = true;
      this->rB_Tait_intrinsic_zyx->Location                = System::Drawing::Point (19,105);
      this->rB_Tait_intrinsic_zyx->Name                    = L"rB_Tait_intrinsic_zyx";
      this->rB_Tait_intrinsic_zyx->Size                    = System::Drawing::Size (97,17);
      this->rB_Tait_intrinsic_zyx->TabIndex                = 1;
      this->rB_Tait_intrinsic_zyx->Text                    = L"Intrinisch ZY\'X\'\'";
      this->rB_Tait_intrinsic_zyx->UseVisualStyleBackColor = true;
      this->rB_Tait_intrinsic_zyx->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_Tait_intrinsic_zyx_CheckedChanged);
      // 
      // rB_Tait_extrinsic_zyx
      // 
      this->rB_Tait_extrinsic_zyx->AutoSize                = true;
      this->rB_Tait_extrinsic_zyx->Checked                 = true;
      this->rB_Tait_extrinsic_zyx->Location                = System::Drawing::Point (19,60);
      this->rB_Tait_extrinsic_zyx->Name                    = L"rB_Tait_extrinsic_zyx";
      this->rB_Tait_extrinsic_zyx->Size                    = System::Drawing::Size (99,17);
      this->rB_Tait_extrinsic_zyx->TabIndex                = 0;
      this->rB_Tait_extrinsic_zyx->TabStop                 = true;
      this->rB_Tait_extrinsic_zyx->Text                    = L"Extrinsisch ZYX";
      this->rB_Tait_extrinsic_zyx->UseVisualStyleBackColor = true;
      this->rB_Tait_extrinsic_zyx->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_Tait_extrinsic_zyx_CheckedChanged);
      // 
      // rB_Grad
      // 
      this->rB_Grad->AutoSize                = true;
      this->rB_Grad->Location                = System::Drawing::Point (19,165);
      this->rB_Grad->Name                    = L"rB_Grad";
      this->rB_Grad->Size                    = System::Drawing::Size (48,17);
      this->rB_Grad->TabIndex                = 47;
      this->rB_Grad->Text                    = L"Grad";
      this->rB_Grad->UseVisualStyleBackColor = true;
      this->rB_Grad->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_Grad_CheckedChanged);
      // 
      // rB_radiant
      // 
      this->rB_radiant->AutoSize                = true;
      this->rB_radiant->Location                = System::Drawing::Point (183,165);
      this->rB_radiant->Name                    = L"rB_radiant";
      this->rB_radiant->Size                    = System::Drawing::Size (62,17);
      this->rB_radiant->TabIndex                = 48;
      this->rB_radiant->Text                    = L"Radiant";
      this->rB_radiant->UseVisualStyleBackColor = true;
      this->rB_radiant->CheckedChanged += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::rB_radiant_CheckedChanged);
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point (16,149);
      this->label4->Name     = L"label4";
      this->label4->Size     = System::Drawing::Size (110,13);
      this->label4->TabIndex = 49;
      this->label4->Text     = L"Absolute Pose Einheit";
      // 
      // c_frm_Camera_Positioning_Pose
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF (6,13);
      this->AutoScaleMode       = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize          = System::Drawing::Size (758,454);
      this->Controls->Add (this->groupBox4);
      this->Controls->Add (this->label9);
      this->Controls->Add (this->groupBox3);
      this->Controls->Add (this->groupBox2);
      this->Controls->Add (this->groupBox1);
      this->Controls->Add (this->lbl_camera_id);
      this->Controls->Add (this->nup_camera_id);
      this->Controls->Add (this->bt_apply);
      this->Controls->Add (this->txtb_counter);
      this->Controls->Add (this->bt_exit);
      this->Name = L"c_frm_Camera_Positioning_Pose";
      this->Text = L"frm_Camera_Positioning_Pose";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler (this,&c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_FormClosing);
      this->Load += gcnew System::EventHandler (this,&c_frm_Camera_Positioning_Pose::c_frm_Camera_Positioning_Pose_Load);
      (cli::
      safe_cast<System::ComponentModel::ISupportInitialize^> (this->nup_camera_id)
      )
      ->
      EndInit();
      this->groupBox1->ResumeLayout (false);
      this->groupBox1->PerformLayout();
      this->groupBox2->ResumeLayout (false);
      this->groupBox2->PerformLayout();
      this->groupBox3->ResumeLayout (false);
      this->groupBox3->PerformLayout();
      this->groupBox4->ResumeLayout (false);
      this->groupBox4->PerformLayout();
      this->ResumeLayout (false);
      this->PerformLayout();
      }
#pragma endregion

    System::Void tait_extrinsic_zyx ();
    System::Void tait_intrinsic_zyx ();
    System::Void euler_extrinsic_zyz ();
    System::Void euler_intrinsic_zyz ();
    System::Void calculation_method ();
    System::Void get_textbox_data ();
    System::Void set_textbox_data ();
    System::Void convert_rad_to_degree ();
    System::Void convert_degree_to_rad ();

    System::Void rB_Tait_extrinsic_zyx_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    System::Void rB_Tait_intrinsic_zyx_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    System::Void rB_euler_extrinsic_zyz_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    System::Void rB_euler_intrinsic_zyz_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    System::Void bt_apply_Click (System::Object^ sender, System::EventArgs^ e);
    System::Void Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e);
    System::Void bt_exit_Click (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void c_frm_Camera_Positioning_Pose_Load (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void c_frm_Camera_Positioning_Pose_FormClosing (System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
    private:
    System::Void rB_Grad_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void rB_radiant_CheckedChanged (System::Object^ sender, System::EventArgs^ e);
    };
  }
