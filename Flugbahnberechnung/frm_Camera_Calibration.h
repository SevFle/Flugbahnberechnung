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
    int         sm_calibration_state;


    Int16       photocount_user_input;

    Thread ^calibrate = gcnew Thread(gcnew ThreadStart(this, &C_frm_CameraCalibration_Single::camera_calibration_thread));








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
    private: System::Windows::Forms::GroupBox^  grB_options;
















    private: System::Windows::Forms::RadioButton^  rb_single_calibration;
    private: System::Windows::Forms::RadioButton^  rb_stereo_calibration;


    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::TextBox^  tb_photo_interval;

    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::Label^  lbl_calibration_running;
    private: System::Windows::Forms::Button^  bt_take_photo;
    private: System::Windows::Forms::PictureBox^  pb_stereo_L;
    private: System::Windows::Forms::PictureBox^  pb_stereo_R;

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
      this->grB_options = (gcnew System::Windows::Forms::GroupBox());
      this->rb_stereo_calibration = (gcnew System::Windows::Forms::RadioButton());
      this->rb_single_calibration = (gcnew System::Windows::Forms::RadioButton());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->tb_photo_interval = (gcnew System::Windows::Forms::TextBox());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->lbl_calibration_running = (gcnew System::Windows::Forms::Label());
      this->bt_take_photo = (gcnew System::Windows::Forms::Button());
      this->pb_stereo_L = (gcnew System::Windows::Forms::PictureBox());
      this->pb_stereo_R = (gcnew System::Windows::Forms::PictureBox());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_live_camera_picture))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_3))->BeginInit();
      this->grB_options->SuspendLayout();
      this->groupBox3->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_stereo_L))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_stereo_R))->BeginInit();
      this->SuspendLayout();
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::Taktgeber_Tick);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1673, 787);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 3;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1673, 707);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 4;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_exit_Click);
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_camera_id->Location = System::Drawing::Point(143, 751);
      this->nup_camera_id->Name = L"nup_camera_id";
      this->nup_camera_id->Size = System::Drawing::Size(34, 29);
      this->nup_camera_id->TabIndex = 5;
      this->nup_camera_id->ValueChanged += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::nup_camera_id_ValueChanged);
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_camera_id->Location = System::Drawing::Point(12, 751);
      this->lbl_camera_id->Name = L"lbl_camera_id";
      this->lbl_camera_id->Size = System::Drawing::Size(130, 24);
      this->lbl_camera_id->TabIndex = 6;
      this->lbl_camera_id->Text = L"Aktive Kamera";
      // 
      // pb_live_camera_picture
      // 
      this->pb_live_camera_picture->Location = System::Drawing::Point(754, 10);
      this->pb_live_camera_picture->Name = L"pb_live_camera_picture";
      this->pb_live_camera_picture->Size = System::Drawing::Size(916, 640);
      this->pb_live_camera_picture->TabIndex = 7;
      this->pb_live_camera_picture->TabStop = false;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(539, 10);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(105, 24);
      this->label1->TabIndex = 8;
      this->label1->Text = L"Kamerabild";
      // 
      // pb_taken_picture_1
      // 
      this->pb_taken_picture_1->Location = System::Drawing::Point(5, 54);
      this->pb_taken_picture_1->Name = L"pb_taken_picture_1";
      this->pb_taken_picture_1->Size = System::Drawing::Size(291, 210);
      this->pb_taken_picture_1->TabIndex = 9;
      this->pb_taken_picture_1->TabStop = false;
      // 
      // pb_taken_picture_2
      // 
      this->pb_taken_picture_2->Location = System::Drawing::Point(5, 271);
      this->pb_taken_picture_2->Name = L"pb_taken_picture_2";
      this->pb_taken_picture_2->Size = System::Drawing::Size(291, 210);
      this->pb_taken_picture_2->TabIndex = 10;
      this->pb_taken_picture_2->TabStop = false;
      // 
      // pb_taken_picture_3
      // 
      this->pb_taken_picture_3->Location = System::Drawing::Point(7, 487);
      this->pb_taken_picture_3->Name = L"pb_taken_picture_3";
      this->pb_taken_picture_3->Size = System::Drawing::Size(291, 210);
      this->pb_taken_picture_3->TabIndex = 11;
      this->pb_taken_picture_3->TabStop = false;
      // 
      // tb_picture_count
      // 
      this->tb_picture_count->Location = System::Drawing::Point(230, 22);
      this->tb_picture_count->Margin = System::Windows::Forms::Padding(2);
      this->tb_picture_count->Name = L"tb_picture_count";
      this->tb_picture_count->Size = System::Drawing::Size(37, 26);
      this->tb_picture_count->TabIndex = 12;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(3, 28);
      this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(223, 20);
      this->label2->TabIndex = 13;
      this->label2->Text = L"Anzahl aufgenommener Bilder";
      // 
      // bt_start
      // 
      this->bt_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->bt_start->Location = System::Drawing::Point(209, 734);
      this->bt_start->Name = L"bt_start";
      this->bt_start->Size = System::Drawing::Size(167, 73);
      this->bt_start->TabIndex = 14;
      this->bt_start->Text = L"Start";
      this->bt_start->UseVisualStyleBackColor = true;
      this->bt_start->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_start_Click);
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Location = System::Drawing::Point(8, 108);
      this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(150, 13);
      this->label3->TabIndex = 16;
      this->label3->Text = L"Anzahl aufzunehmender Bilder";
      // 
      // tb_single_imgs_to_take
      // 
      this->tb_single_imgs_to_take->Location = System::Drawing::Point(10, 124);
      this->tb_single_imgs_to_take->Margin = System::Windows::Forms::Padding(2);
      this->tb_single_imgs_to_take->Name = L"tb_single_imgs_to_take";
      this->tb_single_imgs_to_take->Size = System::Drawing::Size(96, 20);
      this->tb_single_imgs_to_take->TabIndex = 15;
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Location = System::Drawing::Point(8, 150);
      this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(141, 13);
      this->label4->TabIndex = 18;
      this->label4->Text = L"Kantenlänge eines Quadrats";
      // 
      // tb_single_edge_length
      // 
      this->tb_single_edge_length->Location = System::Drawing::Point(10, 166);
      this->tb_single_edge_length->Margin = System::Windows::Forms::Padding(2);
      this->tb_single_edge_length->Name = L"tb_single_edge_length";
      this->tb_single_edge_length->Size = System::Drawing::Size(96, 20);
      this->tb_single_edge_length->TabIndex = 17;
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(8, 214);
      this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(129, 13);
      this->label5->TabIndex = 20;
      this->label5->Text = L"Anzahl der Kanten (B x H)";
      // 
      // tb_single_corner_count_B
      // 
      this->tb_single_corner_count_B->Location = System::Drawing::Point(10, 230);
      this->tb_single_corner_count_B->Margin = System::Windows::Forms::Padding(2);
      this->tb_single_corner_count_B->Name = L"tb_single_corner_count_B";
      this->tb_single_corner_count_B->Size = System::Drawing::Size(96, 20);
      this->tb_single_corner_count_B->TabIndex = 19;
      // 
      // tb_single_corner_count_H
      // 
      this->tb_single_corner_count_H->Location = System::Drawing::Point(110, 230);
      this->tb_single_corner_count_H->Margin = System::Windows::Forms::Padding(2);
      this->tb_single_corner_count_H->Name = L"tb_single_corner_count_H";
      this->tb_single_corner_count_H->Size = System::Drawing::Size(96, 20);
      this->tb_single_corner_count_H->TabIndex = 21;
      // 
      // grB_options
      // 
      this->grB_options->Controls->Add(this->rb_stereo_calibration);
      this->grB_options->Controls->Add(this->rb_single_calibration);
      this->grB_options->Controls->Add(this->tb_single_corner_count_H);
      this->grB_options->Controls->Add(this->label5);
      this->grB_options->Controls->Add(this->tb_single_corner_count_B);
      this->grB_options->Controls->Add(this->label4);
      this->grB_options->Controls->Add(this->tb_single_edge_length);
      this->grB_options->Controls->Add(this->label3);
      this->grB_options->Controls->Add(this->tb_single_imgs_to_take);
      this->grB_options->Location = System::Drawing::Point(320, 13);
      this->grB_options->Margin = System::Windows::Forms::Padding(2);
      this->grB_options->Name = L"grB_options";
      this->grB_options->Padding = System::Windows::Forms::Padding(2);
      this->grB_options->Size = System::Drawing::Size(224, 332);
      this->grB_options->TabIndex = 22;
      this->grB_options->TabStop = false;
      this->grB_options->Text = L"Parameter";
      // 
      // rb_stereo_calibration
      // 
      this->rb_stereo_calibration->AutoSize = true;
      this->rb_stereo_calibration->Location = System::Drawing::Point(12, 51);
      this->rb_stereo_calibration->Margin = System::Windows::Forms::Padding(2);
      this->rb_stereo_calibration->Name = L"rb_stereo_calibration";
      this->rb_stereo_calibration->Size = System::Drawing::Size(115, 17);
      this->rb_stereo_calibration->TabIndex = 23;
      this->rb_stereo_calibration->TabStop = true;
      this->rb_stereo_calibration->Text = L"Stereo [Extrinsisch]";
      this->rb_stereo_calibration->UseVisualStyleBackColor = true;
      this->rb_stereo_calibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::rb_stereo_calibration_Click);
      // 
      // rb_single_calibration
      // 
      this->rb_single_calibration->AutoSize = true;
      this->rb_single_calibration->Checked = true;
      this->rb_single_calibration->Location = System::Drawing::Point(12, 30);
      this->rb_single_calibration->Margin = System::Windows::Forms::Padding(2);
      this->rb_single_calibration->Name = L"rb_single_calibration";
      this->rb_single_calibration->Size = System::Drawing::Size(110, 17);
      this->rb_single_calibration->TabIndex = 22;
      this->rb_single_calibration->TabStop = true;
      this->rb_single_calibration->Text = L"Single [Intrinsisch]";
      this->rb_single_calibration->UseVisualStyleBackColor = true;
      this->rb_single_calibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::rb_single_calibration_Click);
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
      this->groupBox3->Location = System::Drawing::Point(9, 10);
      this->groupBox3->Margin = System::Windows::Forms::Padding(2);
      this->groupBox3->Name = L"groupBox3";
      this->groupBox3->Padding = System::Windows::Forms::Padding(2);
      this->groupBox3->Size = System::Drawing::Size(307, 707);
      this->groupBox3->TabIndex = 24;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = L"Aufgenommene Bilder";
      // 
      // tb_photo_interval
      // 
      this->tb_photo_interval->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular,
                                       System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->tb_photo_interval->Location = System::Drawing::Point(386, 756);
      this->tb_photo_interval->Margin = System::Windows::Forms::Padding(2);
      this->tb_photo_interval->Name = L"tb_photo_interval";
      this->tb_photo_interval->Size = System::Drawing::Size(37, 24);
      this->tb_photo_interval->TabIndex = 14;
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label9->Location = System::Drawing::Point(382, 734);
      this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(57, 18);
      this->label9->TabIndex = 14;
      this->label9->Text = L"Intervall";
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label10->Location = System::Drawing::Point(423, 756);
      this->label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(24, 18);
      this->label10->TabIndex = 25;
      this->label10->Text = L"[s]";
      // 
      // lbl_calibration_running
      // 
      this->lbl_calibration_running->AutoSize = true;
      this->lbl_calibration_running->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
                                             System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_calibration_running->ForeColor = System::Drawing::Color::Red;
      this->lbl_calibration_running->Location = System::Drawing::Point(320, 372);
      this->lbl_calibration_running->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
      this->lbl_calibration_running->Name = L"lbl_calibration_running";
      this->lbl_calibration_running->Size = System::Drawing::Size(324, 26);
      this->lbl_calibration_running->TabIndex = 26;
      this->lbl_calibration_running->Text = L"Kalibrierung läuft im Hintergrund";
      this->lbl_calibration_running->Visible = false;
      // 
      // bt_take_photo
      // 
      this->bt_take_photo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->bt_take_photo->Location = System::Drawing::Point(464, 734);
      this->bt_take_photo->Name = L"bt_take_photo";
      this->bt_take_photo->Size = System::Drawing::Size(167, 73);
      this->bt_take_photo->TabIndex = 27;
      this->bt_take_photo->Text = L"Foto";
      this->bt_take_photo->UseVisualStyleBackColor = true;
      this->bt_take_photo->Visible = false;
      this->bt_take_photo->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::bt_take_photo_Click);
      // 
      // pb_stereo_L
      // 
      this->pb_stereo_L->Location = System::Drawing::Point(1253, 10);
      this->pb_stereo_L->Name = L"pb_stereo_L";
      this->pb_stereo_L->Size = System::Drawing::Size(608, 550);
      this->pb_stereo_L->TabIndex = 28;
      this->pb_stereo_L->TabStop = false;
      this->pb_stereo_L->Visible = false;
      // 
      // pb_stereo_R
      // 
      this->pb_stereo_R->Location = System::Drawing::Point(649, 10);
      this->pb_stereo_R->Name = L"pb_stereo_R";
      this->pb_stereo_R->Size = System::Drawing::Size(608, 550);
      this->pb_stereo_R->TabIndex = 29;
      this->pb_stereo_R->TabStop = false;
      this->pb_stereo_R->Visible = false;
      // 
      // C_frm_CameraCalibration_Single
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1862, 818);
      this->Controls->Add(this->pb_stereo_R);
      this->Controls->Add(this->pb_stereo_L);
      this->Controls->Add(this->bt_take_photo);
      this->Controls->Add(this->lbl_calibration_running);
      this->Controls->Add(this->label10);
      this->Controls->Add(this->label9);
      this->Controls->Add(this->tb_photo_interval);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->grB_options);
      this->Controls->Add(this->bt_start);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pb_live_camera_picture);
      this->Controls->Add(this->lbl_camera_id);
      this->Controls->Add(this->nup_camera_id);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Name = L"C_frm_CameraCalibration_Single";
      this->Text = L"frm_CameraCalibration_Single";
      this->Load += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Single::C_frm_CameraCalibration_Single_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_live_camera_picture))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_taken_picture_3))->EndInit();
      this->grB_options->ResumeLayout(false);
      this->grB_options->PerformLayout();
      this->groupBox3->ResumeLayout(false);
      this->groupBox3->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_stereo_L))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_stereo_R))->EndInit();
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

      System::Void      bt_start_Click                                      (System::Object^  sender, System::EventArgs^  e);

      System::Void      nup_camera_id_ValueChanged                          (System::Object^  sender, System::EventArgs^  e);

      System::Void      camera_calibration_thread                           ();
      System::Void      bt_take_photo_Click                                 (System::Object^  sender, System::EventArgs^  e);
      System::Void      sm_Single_camera_calibration                        ();
      System::Void      sm_Stereo_camera_calibration                        ();
  };
}
