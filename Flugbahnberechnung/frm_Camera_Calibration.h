#pragma once

#include "Main.h"


using namespace nmsp_Main;

namespace NmSp_CamerCalibration_Single 
  {
  using namespace nmsp_GlobalObjects;
	public ref class C_frm_CameraCalibration_Single : public System::Windows::Forms::Form
	{
	  public:
    C_frm_CameraCalibration_Single(C_GlobalObjects* GlobalObjects, C_Main^  Main);

	  protected:
    ~C_frm_CameraCalibration_Single();

	  private:
    C_GlobalObjects*        GlobalObjects;
    C_Main^                 Main;




    UInt32      Zaehler;

    int         cameras_in_use;
    int         Timerwait;

    bool        calibration_running;
    int         photo_interval;
    int         intervall;
    int         photo_count;
    int         photo_id;
    int         method;
    int         current_camera_id;
    Int16         photocount_user_input;







    private: System::Windows::Forms::Timer^  Taktgeber;
    private: System::Windows::Forms::TextBox^  txtb_counter;
    private: System::Windows::Forms::Button^  bt_exit;
    private: System::Windows::Forms::NumericUpDown^  nup_camera_id;
    private: System::Windows::Forms::Label^  lbl_camera_id;
    private: System::Windows::Forms::PictureBox^  pb_live_camera_picture;

    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::PictureBox^  pb_taken_picture_1;
    private: System::Windows::Forms::PictureBox^  pb_taken_picture_2;
    private: System::Windows::Forms::PictureBox^  pb_taken_picture_3;



    private: System::Windows::Forms::TextBox^  tb_picture_count;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Button^  bt_start;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::TextBox^  tb_single_imgs_to_take;

    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::TextBox^  tb_single_edge_length;

    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::TextBox^  tb_single_corner_count_B;

    private: System::Windows::Forms::TextBox^  tb_single_corner_count_H;
    private: System::Windows::Forms::GroupBox^  grB_single;
    private: System::Windows::Forms::GroupBox^  grb_stereo;




    private: System::Windows::Forms::TextBox^  tb_stereo_corner_count_H;

    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TextBox^  tb_stereo_corner_count_L;

    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::TextBox^  tb_stereo_edge_length;

    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::TextBox^  tb_stereo_imgs_to_take;

    private: System::Windows::Forms::RadioButton^  rb_single_calibration;
    private: System::Windows::Forms::RadioButton^  rb_stereo_calibration;


    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::TextBox^  tb_photo_interval;

    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  lbl_calibration_running;
    private: System::Windows::Forms::Button^  bt_take_photo;

    private: System::ComponentModel::IContainer^  components;


    private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->nup_camera_id = (gcnew System::Windows::Forms::NumericUpDown());
      this->lbl_camera_id = (gcnew System::Windows::Forms::Label());
      this->pb_live_camera_picture = (gcnew System::Windows::Forms::PictureBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->pb_taken_picture_1 = (gcnew System::Windows::Forms::PictureBox());
      this->pb_taken_picture_2 = (gcnew System::Windows::Forms::PictureBox());
      this->pb_taken_picture_3 = (gcnew System::Windows::Forms::PictureBox());
      this->tb_picture_count = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->bt_start = (gcnew System::Windows::Forms::Button());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->tb_single_imgs_to_take = (gcnew System::Windows::Forms::TextBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->tb_single_edge_length = (gcnew System::Windows::Forms::TextBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->tb_single_corner_count_B = (gcnew System::Windows::Forms::TextBox());
      this->tb_single_corner_count_H = (gcnew System::Windows::Forms::TextBox());
      this->grB_single = (gcnew System::Windows::Forms::GroupBox());
      this->rb_single_calibration = (gcnew System::Windows::Forms::RadioButton());
      this->grb_stereo = (gcnew System::Windows::Forms::GroupBox());
      this->rb_stereo_calibration = (gcnew System::Windows::Forms::RadioButton());
      this->tb_stereo_corner_count_H = (gcnew System::Windows::Forms::TextBox());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->tb_stereo_corner_count_L = (gcnew System::Windows::Forms::TextBox());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->tb_stereo_edge_length = (gcnew System::Windows::Forms::TextBox());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->tb_stereo_imgs_to_take = (gcnew System::Windows::Forms::TextBox());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->tb_photo_interval = (gcnew System::Windows::Forms::TextBox());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->lbl_calibration_running = (gcnew System::Windows::Forms::Label());
      this->bt_take_photo = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_live_camera_picture))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_3))->BeginInit();
      this->grB_single->SuspendLayout();
      this->grb_stereo->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->SuspendLayout();
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::Taktgeber_Tick);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1137, 961);
      this->txtb_counter->Margin = System::Windows::Forms::Padding(4);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(220, 22);
      this->txtb_counter->TabIndex = 3;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1137, 863);
      this->bt_exit->Margin = System::Windows::Forms::Padding(4);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(223, 90);
      this->bt_exit->TabIndex = 4;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_exit_Click);
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_camera_id->Location = System::Drawing::Point(191, 924);
      this->nup_camera_id->Margin = System::Windows::Forms::Padding(4);
      this->nup_camera_id->Name = L"nup_camera_id";
      this->nup_camera_id->Size = System::Drawing::Size(45, 34);
      this->nup_camera_id->TabIndex = 5;
      this->nup_camera_id->ValueChanged += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::nup_camera_id_ValueChanged);
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_camera_id->Location = System::Drawing::Point(16, 924);
      this->lbl_camera_id->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_camera_id->Name = L"lbl_camera_id";
      this->lbl_camera_id->Size = System::Drawing::Size(167, 29);
      this->lbl_camera_id->TabIndex = 6;
      this->lbl_camera_id->Text = L"Aktive Kamera";
      // 
      // pb_live_camera_picture
      // 
      this->pb_live_camera_picture->Location = System::Drawing::Point(433, 478);
      this->pb_live_camera_picture->Margin = System::Windows::Forms::Padding(4);
      this->pb_live_camera_picture->Name = L"pb_live_camera_picture";
      this->pb_live_camera_picture->Size = System::Drawing::Size(598, 404);
      this->pb_live_camera_picture->TabIndex = 7;
      this->pb_live_camera_picture->TabStop = false;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(428, 428);
      this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(137, 29);
      this->label1->TabIndex = 8;
      this->label1->Text = L"Kamerabild";
      // 
      // pb_taken_picture_1
      // 
      this->pb_taken_picture_1->Location = System::Drawing::Point(7, 66);
      this->pb_taken_picture_1->Margin = System::Windows::Forms::Padding(4);
      this->pb_taken_picture_1->Name = L"pb_taken_picture_1";
      this->pb_taken_picture_1->Size = System::Drawing::Size(388, 258);
      this->pb_taken_picture_1->TabIndex = 9;
      this->pb_taken_picture_1->TabStop = false;
      // 
      // pb_taken_picture_2
      // 
      this->pb_taken_picture_2->Location = System::Drawing::Point(7, 333);
      this->pb_taken_picture_2->Margin = System::Windows::Forms::Padding(4);
      this->pb_taken_picture_2->Name = L"pb_taken_picture_2";
      this->pb_taken_picture_2->Size = System::Drawing::Size(388, 258);
      this->pb_taken_picture_2->TabIndex = 10;
      this->pb_taken_picture_2->TabStop = false;
      // 
      // pb_taken_picture_3
      // 
      this->pb_taken_picture_3->Location = System::Drawing::Point(9, 599);
      this->pb_taken_picture_3->Margin = System::Windows::Forms::Padding(4);
      this->pb_taken_picture_3->Name = L"pb_taken_picture_3";
      this->pb_taken_picture_3->Size = System::Drawing::Size(388, 258);
      this->pb_taken_picture_3->TabIndex = 11;
      this->pb_taken_picture_3->TabStop = false;
      // 
      // tb_picture_count
      // 
      this->tb_picture_count->Location = System::Drawing::Point(284, 29);
      this->tb_picture_count->Name = L"tb_picture_count";
      this->tb_picture_count->Size = System::Drawing::Size(48, 30);
      this->tb_picture_count->TabIndex = 12;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(4, 34);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(274, 25);
      this->label2->TabIndex = 13;
      this->label2->Text = L"Anzahl aufgenommener Bilder";
      // 
      // bt_start
      // 
      this->bt_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->bt_start->Location = System::Drawing::Point(279, 904);
      this->bt_start->Margin = System::Windows::Forms::Padding(4);
      this->bt_start->Name = L"bt_start";
      this->bt_start->Size = System::Drawing::Size(223, 90);
      this->bt_start->TabIndex = 14;
      this->bt_start->Text = L"Start";
      this->bt_start->UseVisualStyleBackColor = true;
      this->bt_start->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_start_Click);
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(11, 75);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(202, 17);
      this->label3->TabIndex = 16;
      this->label3->Text = L"Anzahl aufzunehmender Bilder";
      // 
      // tb_single_imgs_to_take
      // 
      this->tb_single_imgs_to_take->Location = System::Drawing::Point(14, 95);
      this->tb_single_imgs_to_take->Name = L"tb_single_imgs_to_take";
      this->tb_single_imgs_to_take->Size = System::Drawing::Size(126, 22);
      this->tb_single_imgs_to_take->TabIndex = 15;
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point(11, 127);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(189, 17);
      this->label4->TabIndex = 18;
      this->label4->Text = L"Kantenlänge eines Quadrats";
      // 
      // tb_single_edge_length
      // 
      this->tb_single_edge_length->Location = System::Drawing::Point(14, 147);
      this->tb_single_edge_length->Name = L"tb_single_edge_length";
      this->tb_single_edge_length->Size = System::Drawing::Size(126, 22);
      this->tb_single_edge_length->TabIndex = 17;
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(11, 205);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(172, 17);
      this->label5->TabIndex = 20;
      this->label5->Text = L"Anzahl der Kanten (B x H)";
      // 
      // tb_single_corner_count_B
      // 
      this->tb_single_corner_count_B->Location = System::Drawing::Point(14, 225);
      this->tb_single_corner_count_B->Name = L"tb_single_corner_count_B";
      this->tb_single_corner_count_B->Size = System::Drawing::Size(126, 22);
      this->tb_single_corner_count_B->TabIndex = 19;
      // 
      // tb_single_corner_count_H
      // 
      this->tb_single_corner_count_H->Location = System::Drawing::Point(146, 225);
      this->tb_single_corner_count_H->Name = L"tb_single_corner_count_H";
      this->tb_single_corner_count_H->Size = System::Drawing::Size(126, 22);
      this->tb_single_corner_count_H->TabIndex = 21;
      // 
      // grB_single
      // 
      this->grB_single->Controls->Add(this->rb_single_calibration);
      this->grB_single->Controls->Add(this->tb_single_corner_count_H);
      this->grB_single->Controls->Add(this->label5);
      this->grB_single->Controls->Add(this->tb_single_corner_count_B);
      this->grB_single->Controls->Add(this->label4);
      this->grB_single->Controls->Add(this->tb_single_edge_length);
      this->grB_single->Controls->Add(this->label3);
      this->grB_single->Controls->Add(this->tb_single_imgs_to_take);
      this->grB_single->Location = System::Drawing::Point(427, 16);
      this->grB_single->Name = L"grB_single";
      this->grB_single->Size = System::Drawing::Size(299, 409);
      this->grB_single->TabIndex = 22;
      this->grB_single->TabStop = false;
      this->grB_single->Text = L"Single Calibration [Intrinsic]";
      // 
      // rb_single_calibration
      // 
      this->rb_single_calibration->AutoSize = true;
      this->rb_single_calibration->Checked = true;
      this->rb_single_calibration->Location = System::Drawing::Point(16, 37);
      this->rb_single_calibration->Name = L"rb_single_calibration";
      this->rb_single_calibration->Size = System::Drawing::Size(59, 21);
      this->rb_single_calibration->TabIndex = 22;
      this->rb_single_calibration->TabStop = true;
      this->rb_single_calibration->Text = L"Aktiv";
      this->rb_single_calibration->UseVisualStyleBackColor = true;
      this->rb_single_calibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::rb_single_calibration_Click);
      // 
      // grb_stereo
      // 
      this->grb_stereo->Controls->Add(this->rb_stereo_calibration);
      this->grb_stereo->Controls->Add(this->tb_stereo_corner_count_H);
      this->grb_stereo->Controls->Add(this->label6);
      this->grb_stereo->Controls->Add(this->tb_stereo_corner_count_L);
      this->grb_stereo->Controls->Add(this->label7);
      this->grb_stereo->Controls->Add(this->tb_stereo_edge_length);
      this->grb_stereo->Controls->Add(this->label8);
      this->grb_stereo->Controls->Add(this->tb_stereo_imgs_to_take);
      this->grb_stereo->Location = System::Drawing::Point(732, 16);
      this->grb_stereo->Name = L"grb_stereo";
      this->grb_stereo->Size = System::Drawing::Size(299, 409);
      this->grb_stereo->TabIndex = 23;
      this->grb_stereo->TabStop = false;
      this->grb_stereo->Text = L"Stereo Calibration [Extrinsic]";
      // 
      // rb_stereo_calibration
      // 
      this->rb_stereo_calibration->AutoSize = true;
      this->rb_stereo_calibration->Location = System::Drawing::Point(16, 37);
      this->rb_stereo_calibration->Name = L"rb_stereo_calibration";
      this->rb_stereo_calibration->Size = System::Drawing::Size(59, 21);
      this->rb_stereo_calibration->TabIndex = 23;
      this->rb_stereo_calibration->TabStop = true;
      this->rb_stereo_calibration->Text = L"Aktiv";
      this->rb_stereo_calibration->UseVisualStyleBackColor = true;
      this->rb_stereo_calibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::rb_stereo_calibration_Click);
      // 
      // tb_stereo_corner_count_H
      // 
      this->tb_stereo_corner_count_H->Location = System::Drawing::Point(148, 225);
      this->tb_stereo_corner_count_H->Name = L"tb_stereo_corner_count_H";
      this->tb_stereo_corner_count_H->Size = System::Drawing::Size(126, 22);
      this->tb_stereo_corner_count_H->TabIndex = 21;
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Location = System::Drawing::Point(13, 205);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(171, 17);
      this->label6->TabIndex = 20;
      this->label6->Text = L"Anzahl der Kanten (L x H)";
      // 
      // tb_stereo_corner_count_L
      // 
      this->tb_stereo_corner_count_L->Location = System::Drawing::Point(16, 225);
      this->tb_stereo_corner_count_L->Name = L"tb_stereo_corner_count_L";
      this->tb_stereo_corner_count_L->Size = System::Drawing::Size(126, 22);
      this->tb_stereo_corner_count_L->TabIndex = 19;
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Location = System::Drawing::Point(13, 127);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(223, 17);
      this->label7->TabIndex = 18;
      this->label7->Text = L"Kantenlänge eines Quadrats [mm]";
      // 
      // tb_stereo_edge_length
      // 
      this->tb_stereo_edge_length->Location = System::Drawing::Point(16, 147);
      this->tb_stereo_edge_length->Name = L"tb_stereo_edge_length";
      this->tb_stereo_edge_length->Size = System::Drawing::Size(126, 22);
      this->tb_stereo_edge_length->TabIndex = 17;
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Location = System::Drawing::Point(13, 75);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(202, 17);
      this->label8->TabIndex = 16;
      this->label8->Text = L"Anzahl aufzunehmender Bilder";
      // 
      // tb_stereo_imgs_to_take
      // 
      this->tb_stereo_imgs_to_take->Location = System::Drawing::Point(16, 95);
      this->tb_stereo_imgs_to_take->Name = L"tb_stereo_imgs_to_take";
      this->tb_stereo_imgs_to_take->Size = System::Drawing::Size(126, 22);
      this->tb_stereo_imgs_to_take->TabIndex = 15;
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add(this->pb_taken_picture_3);
      this->groupBox3->Controls->Add(this->pb_taken_picture_2);
      this->groupBox3->Controls->Add(this->pb_taken_picture_1);
      this->groupBox3->Controls->Add(this->tb_picture_count);
      this->groupBox3->Controls->Add(this->label2);
      this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                               static_cast<System::Byte>(0)));
      this->groupBox3->Location = System::Drawing::Point(12, 12);
      this->groupBox3->Name = L"groupBox3";
      this->groupBox3->Size = System::Drawing::Size(409, 870);
      this->groupBox3->TabIndex = 24;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = L"Aufgenommene Bilder";
      // 
      // tb_photo_interval
      // 
      this->tb_photo_interval->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular,
                                       System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->tb_photo_interval->Location = System::Drawing::Point(514, 931);
      this->tb_photo_interval->Name = L"tb_photo_interval";
      this->tb_photo_interval->Size = System::Drawing::Size(48, 28);
      this->tb_photo_interval->TabIndex = 14;
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label9->Location = System::Drawing::Point(510, 904);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(73, 24);
      this->label9->TabIndex = 14;
      this->label9->Text = L"Intervall";
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label10->Location = System::Drawing::Point(564, 931);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(29, 24);
      this->label10->TabIndex = 25;
      this->label10->Text = L"[s]";
      // 
      // lbl_calibration_running
      // 
      this->lbl_calibration_running->AutoSize = true;
      this->lbl_calibration_running->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
                                             System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_calibration_running->ForeColor = System::Drawing::Color::Red;
      this->lbl_calibration_running->Location = System::Drawing::Point(567, 428);
      this->lbl_calibration_running->Name = L"lbl_calibration_running";
      this->lbl_calibration_running->Size = System::Drawing::Size(424, 32);
      this->lbl_calibration_running->TabIndex = 26;
      this->lbl_calibration_running->Text = L"Kalibrierung läuft im Hintergrund";
      this->lbl_calibration_running->Visible = false;
      // 
      // bt_take_photo
      // 
      this->bt_take_photo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->bt_take_photo->Location = System::Drawing::Point(618, 904);
      this->bt_take_photo->Margin = System::Windows::Forms::Padding(4);
      this->bt_take_photo->Name = L"bt_take_photo";
      this->bt_take_photo->Size = System::Drawing::Size(223, 90);
      this->bt_take_photo->TabIndex = 27;
      this->bt_take_photo->Text = L"Foto";
      this->bt_take_photo->UseVisualStyleBackColor = true;
      this->bt_take_photo->Visible = false;
      this->bt_take_photo->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_take_photo_Click);
      // 
      // C_frm_CameraCalibration_Single
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1373, 1007);
      this->Controls->Add(this->bt_take_photo);
      this->Controls->Add(this->lbl_calibration_running);
      this->Controls->Add(this->label10);
      this->Controls->Add(this->label9);
      this->Controls->Add(this->tb_photo_interval);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->grb_stereo);
      this->Controls->Add(this->grB_single);
      this->Controls->Add(this->bt_start);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pb_live_camera_picture);
      this->Controls->Add(this->lbl_camera_id);
      this->Controls->Add(this->nup_camera_id);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Margin = System::Windows::Forms::Padding(4);
      this->Name = L"C_frm_CameraCalibration_Single";
      this->Text = L"frm_CameraCalibration_Single";
      this->Load += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_live_camera_picture))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_3))->EndInit();
      this->grB_single->ResumeLayout(false);
      this->grB_single->PerformLayout();
      this->grb_stereo->ResumeLayout(false);
      this->grb_stereo->PerformLayout();
      this->groupBox3->ResumeLayout(false);
      this->groupBox3->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
      private: 
      System::Void      rb_single_calibration_Click                         (System::Object^  sender, System::EventArgs^  e);
      System::Void      rb_stereo_calibration_Click                         (System::Object^  sender, System::EventArgs^  e);
      System::Void      Taktgeber_Tick                                      (System::Object^  sender, System::EventArgs^  e);
      System::Void      bt_exit_Click                                       (System::Object^  sender, System::EventArgs^  e);
      System::Void      C_frm_CameraCalibration_Single_Load                 (System::Object^  sender, System::EventArgs^  e);


      System::Void      FillPicturebox                                      (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
      System::Void      FillMat2Picturebox                                  (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage);

      System::Void      bt_take_picture_Click                               (System::Object^  sender, System::EventArgs^  e);
      System::Void      bt_start_Click                                      (System::Object^  sender, System::EventArgs^  e);

      System::Void      nup_camera_id_ValueChanged                          (System::Object^  sender, System::EventArgs^  e);

      System::Void      Camera_calibration_condition                        ();
      System::Void      camera_calibration_thread                           ();
      System::Void      bt_take_photo_Click                                 (System::Object^  sender, System::EventArgs^  e);
};
}
