#pragma once

#include "Main.h"

using namespace nmsp_Main;

namespace nmsp_camera_calibration_crop {
	public ref class c_frm_Camera_Calibration_crop : public System::Windows::Forms::Form
	{
	public:
  c_frm_Camera_Calibration_crop(C_GlobalObjects* GlobalObjects, C_Main^  Main);

	protected:
  ~c_frm_Camera_Calibration_crop();

	private:
  C_GlobalObjects*        GlobalObjects;
  C_Main^                 Main;

  UInt32      Zaehler;
  int         cameras_in_use;
  int         Timerwait;
  int         current_camera_id;
  int         last_camera_id;
  cv::Rect*    fitting_rect;

    private: System::Windows::Forms::TextBox^  txtb_counter;
    private: System::Windows::Forms::Button^  bt_exit;
    private: System::Windows::Forms::Timer^  Taktgeber;
    private: System::Windows::Forms::NumericUpDown^  num_UD_resize_height;
    private: System::Windows::Forms::NumericUpDown^  num_UD_resize_width;
    private: System::Windows::Forms::Label^  lbl_camera_id;
    private: System::Windows::Forms::NumericUpDown^  nup_camera_id;
    private: System::Windows::Forms::PictureBox^  pb_uncropped_img;


    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::PictureBox^  pb_cropped_img;

    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::TextBox^  textBox2;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::TextBox^  textBox4;
    private: System::Windows::Forms::TextBox^  textBox3;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label8;
    private: System::ComponentModel::IContainer^  components;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->num_UD_resize_height = (gcnew System::Windows::Forms::NumericUpDown());
      this->num_UD_resize_width = (gcnew System::Windows::Forms::NumericUpDown());
      this->lbl_camera_id = (gcnew System::Windows::Forms::Label());
      this->nup_camera_id = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_uncropped_img = (gcnew System::Windows::Forms::PictureBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->pb_cropped_img = (gcnew System::Windows::Forms::PictureBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox4 = (gcnew System::Windows::Forms::TextBox());
      this->textBox3 = (gcnew System::Windows::Forms::TextBox());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->num_UD_resize_height))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->num_UD_resize_width))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_uncropped_img))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cropped_img))->BeginInit();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->SuspendLayout();
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1176, 682);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 5;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1176, 602);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 6;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::bt_exit_Click);
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::Taktgeber_Tick);
      // 
      // num_UD_resize_height
      // 
      this->num_UD_resize_height->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                          System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->num_UD_resize_height->Location = System::Drawing::Point(80, 57);
      this->num_UD_resize_height->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        600, 0, 0, 0
        });
      this->num_UD_resize_height->Name = L"num_UD_resize_height";
      this->num_UD_resize_height->Size = System::Drawing::Size(74, 29);
      this->num_UD_resize_height->TabIndex = 33;
      this->num_UD_resize_height->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        400, 0, 0, 0
        });
      this->num_UD_resize_height->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::num_UD_resize_height_ValueChanged);
      // 
      // num_UD_resize_width
      // 
      this->num_UD_resize_width->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                         System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->num_UD_resize_width->Location = System::Drawing::Point(80, 20);
      this->num_UD_resize_width->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        800, 0, 0, 0
        });
      this->num_UD_resize_width->Name = L"num_UD_resize_width";
      this->num_UD_resize_width->Size = System::Drawing::Size(74, 29);
      this->num_UD_resize_width->TabIndex = 32;
      this->num_UD_resize_width->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        300, 0, 0, 0
        });
      this->num_UD_resize_width->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::num_UD_resize_width_ValueChanged);
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_camera_id->Location = System::Drawing::Point(989, 673);
      this->lbl_camera_id->Name = L"lbl_camera_id";
      this->lbl_camera_id->Size = System::Drawing::Size(130, 24);
      this->lbl_camera_id->TabIndex = 35;
      this->lbl_camera_id->Text = L"Aktive Kamera";
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_camera_id->Location = System::Drawing::Point(1120, 673);
      this->nup_camera_id->Name = L"nup_camera_id";
      this->nup_camera_id->Size = System::Drawing::Size(34, 29);
      this->nup_camera_id->TabIndex = 34;
      this->nup_camera_id->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::nup_camera_id_ValueChanged);
      // 
      // pb_uncropped_img
      // 
      this->pb_uncropped_img->Location = System::Drawing::Point(29, 38);
      this->pb_uncropped_img->Name = L"pb_uncropped_img";
      this->pb_uncropped_img->Size = System::Drawing::Size(635, 543);
      this->pb_uncropped_img->TabIndex = 37;
      this->pb_uncropped_img->TabStop = false;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(25, 9);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(162, 24);
      this->label1->TabIndex = 38;
      this->label1->Text = L"Uncropped Image";
      // 
      // pb_cropped_img
      // 
      this->pb_cropped_img->Location = System::Drawing::Point(708, 38);
      this->pb_cropped_img->Name = L"pb_cropped_img";
      this->pb_cropped_img->Size = System::Drawing::Size(635, 543);
      this->pb_cropped_img->TabIndex = 39;
      this->pb_cropped_img->TabStop = false;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(704, 9);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(141, 24);
      this->label2->TabIndex = 40;
      this->label2->Text = L"Cropped Image";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(17, 56);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(57, 24);
      this->label3->TabIndex = 41;
      this->label3->Text = L"Höhe";
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label4->Location = System::Drawing::Point(18, 22);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(58, 24);
      this->label4->TabIndex = 42;
      this->label4->Text = L"Breite";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->label4);
      this->groupBox1->Controls->Add(this->label3);
      this->groupBox1->Controls->Add(this->num_UD_resize_height);
      this->groupBox1->Controls->Add(this->num_UD_resize_width);
      this->groupBox1->Location = System::Drawing::Point(10, 592);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(188, 109);
      this->groupBox1->TabIndex = 43;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Zuschnitt";
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->textBox2);
      this->groupBox2->Controls->Add(this->textBox1);
      this->groupBox2->Controls->Add(this->label5);
      this->groupBox2->Controls->Add(this->label6);
      this->groupBox2->Location = System::Drawing::Point(234, 592);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(214, 109);
      this->groupBox2->TabIndex = 44;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Ursprüngliche Bildauflösung";
      // 
      // textBox2
      // 
      this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox2->Location = System::Drawing::Point(69, 56);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(82, 29);
      this->textBox2->TabIndex = 46;
      // 
      // textBox1
      // 
      this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox1->Location = System::Drawing::Point(69, 17);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(82, 29);
      this->textBox1->TabIndex = 45;
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label5->Location = System::Drawing::Point(6, 59);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(58, 24);
      this->label5->TabIndex = 44;
      this->label5->Text = L"Breite";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label6->Location = System::Drawing::Point(6, 22);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(57, 24);
      this->label6->TabIndex = 43;
      this->label6->Text = L"Höhe";
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add(this->textBox4);
      this->groupBox3->Controls->Add(this->textBox3);
      this->groupBox3->Controls->Add(this->label7);
      this->groupBox3->Controls->Add(this->label8);
      this->groupBox3->Location = System::Drawing::Point(488, 592);
      this->groupBox3->Name = L"groupBox3";
      this->groupBox3->Size = System::Drawing::Size(214, 110);
      this->groupBox3->TabIndex = 45;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = L"Zugeschnittene Bildauflösung";
      // 
      // textBox4
      // 
      this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox4->Location = System::Drawing::Point(69, 54);
      this->textBox4->Name = L"textBox4";
      this->textBox4->Size = System::Drawing::Size(82, 29);
      this->textBox4->TabIndex = 48;
      // 
      // textBox3
      // 
      this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox3->Location = System::Drawing::Point(69, 19);
      this->textBox3->Name = L"textBox3";
      this->textBox3->Size = System::Drawing::Size(82, 29);
      this->textBox3->TabIndex = 47;
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label7->Location = System::Drawing::Point(6, 59);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(58, 24);
      this->label7->TabIndex = 46;
      this->label7->Text = L"Breite";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label8->Location = System::Drawing::Point(6, 22);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(57, 24);
      this->label8->TabIndex = 45;
      this->label8->Text = L"Höhe";
      // 
      // c_frm_Camera_Calibration_crop
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1363, 719);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->label2);
      this->Controls->Add(this->pb_cropped_img);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pb_uncropped_img);
      this->Controls->Add(this->lbl_camera_id);
      this->Controls->Add(this->nup_camera_id);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Name = L"c_frm_Camera_Calibration_crop";
      this->Text = L"frm_Camera_Calibration_crop";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &c_frm_Camera_Calibration_crop::c_frm_Camera_Calibration_crop_FormClosing);
      this->Load += gcnew System::EventHandler(this, &c_frm_Camera_Calibration_crop::c_frm_Camera_Calibration_crop_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->num_UD_resize_height))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->num_UD_resize_width))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_uncropped_img))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cropped_img))->EndInit();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      this->groupBox3->ResumeLayout(false);
      this->groupBox3->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
	private:
  System::Void Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e);
  System::Void bt_exit_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void nup_camera_id_ValueChanged(System::Object^  sender, System::EventArgs^  e);
  System::Void num_UD_resize_width_ValueChanged(System::Object^  sender, System::EventArgs^  e);
  System::Void num_UD_resize_height_ValueChanged(System::Object^  sender, System::EventArgs^  e);



  System::Void  FillPicturebox                                     (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
  System::Void  FillMat2Picturebox                                 (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage);
  System::Void  FillMat2PictureboxFramed                           (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat *colorImage);

  System::Void c_frm_Camera_Calibration_crop_Load(System::Object^  sender, System::EventArgs^  e);
  System::Void c_frm_Camera_Calibration_crop_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};
}
