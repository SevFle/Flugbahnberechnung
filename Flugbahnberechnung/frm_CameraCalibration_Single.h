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
    C_GlobalObjects*      GlobalObjects;
    C_Main^               Main;

    UInt32      Zaehler;
    private: System::Windows::Forms::Timer^  Taktgeber;
    private: System::Windows::Forms::TextBox^  txtb_counter;
    private: System::Windows::Forms::Button^  bt_exit;
    private: System::Windows::Forms::NumericUpDown^  nup_camera_id;
    private: System::Windows::Forms::Label^  lbl_camera_id;
    private: System::Windows::Forms::PictureBox^  pb_camera_picture;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::PictureBox^  pictureBox1;
    private: System::Windows::Forms::PictureBox^  pictureBox2;
    private: System::Windows::Forms::PictureBox^  pictureBox3;
    private: System::Windows::Forms::TextBox^  tb_picture_count;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Button^  bt_start;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::TextBox^  textBox2;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::TextBox^  tb_corner_count_L;
    private: System::Windows::Forms::TextBox^  tb_corner_count_H;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::TextBox^  textBox3;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TextBox^  textBox4;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::TextBox^  textBox5;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::TextBox^  textBox6;
    private: System::Windows::Forms::RadioButton^  radioButton1;
    private: System::Windows::Forms::RadioButton^  radioButton2;
    private: System::Windows::Forms::GroupBox^  groupBox3;
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
      this->pb_camera_picture = (gcnew System::Windows::Forms::PictureBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
      this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
      this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
      this->tb_picture_count = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->bt_start = (gcnew System::Windows::Forms::Button());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->tb_corner_count_L = (gcnew System::Windows::Forms::TextBox());
      this->tb_corner_count_H = (gcnew System::Windows::Forms::TextBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
      this->textBox3 = (gcnew System::Windows::Forms::TextBox());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->textBox4 = (gcnew System::Windows::Forms::TextBox());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->textBox5 = (gcnew System::Windows::Forms::TextBox());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->textBox6 = (gcnew System::Windows::Forms::TextBox());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_camera_picture))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->SuspendLayout();
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
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_camera_id->Location = System::Drawing::Point(1137, 78);
      this->nup_camera_id->Margin = System::Windows::Forms::Padding(4);
      this->nup_camera_id->Name = L"nup_camera_id";
      this->nup_camera_id->Size = System::Drawing::Size(45, 34);
      this->nup_camera_id->TabIndex = 5;
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_camera_id->Location = System::Drawing::Point(1132, 45);
      this->lbl_camera_id->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_camera_id->Name = L"lbl_camera_id";
      this->lbl_camera_id->Size = System::Drawing::Size(193, 29);
      this->lbl_camera_id->TabIndex = 6;
      this->lbl_camera_id->Text = L"Auswahl Kamera";
      // 
      // pb_camera_picture
      // 
      this->pb_camera_picture->Location = System::Drawing::Point(733, 46);
      this->pb_camera_picture->Margin = System::Windows::Forms::Padding(4);
      this->pb_camera_picture->Name = L"pb_camera_picture";
      this->pb_camera_picture->Size = System::Drawing::Size(388, 258);
      this->pb_camera_picture->TabIndex = 7;
      this->pb_camera_picture->TabStop = false;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(733, 16);
      this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(137, 29);
      this->label1->TabIndex = 8;
      this->label1->Text = L"Kamerabild";
      // 
      // pictureBox1
      // 
      this->pictureBox1->Location = System::Drawing::Point(7, 66);
      this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
      this->pictureBox1->Name = L"pictureBox1";
      this->pictureBox1->Size = System::Drawing::Size(388, 258);
      this->pictureBox1->TabIndex = 9;
      this->pictureBox1->TabStop = false;
      // 
      // pictureBox2
      // 
      this->pictureBox2->Location = System::Drawing::Point(7, 333);
      this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
      this->pictureBox2->Name = L"pictureBox2";
      this->pictureBox2->Size = System::Drawing::Size(388, 258);
      this->pictureBox2->TabIndex = 10;
      this->pictureBox2->TabStop = false;
      // 
      // pictureBox3
      // 
      this->pictureBox3->Location = System::Drawing::Point(9, 599);
      this->pictureBox3->Margin = System::Windows::Forms::Padding(4);
      this->pictureBox3->Name = L"pictureBox3";
      this->pictureBox3->Size = System::Drawing::Size(388, 258);
      this->pictureBox3->TabIndex = 11;
      this->pictureBox3->TabStop = false;
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
      this->bt_start->Location = System::Drawing::Point(1137, 745);
      this->bt_start->Margin = System::Windows::Forms::Padding(4);
      this->bt_start->Name = L"bt_start";
      this->bt_start->Size = System::Drawing::Size(223, 90);
      this->bt_start->TabIndex = 14;
      this->bt_start->Text = L"Start";
      this->bt_start->UseVisualStyleBackColor = true;
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
      // textBox1
      // 
      this->textBox1->Location = System::Drawing::Point(14, 95);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(126, 22);
      this->textBox1->TabIndex = 15;
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
      // textBox2
      // 
      this->textBox2->Location = System::Drawing::Point(14, 147);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(126, 22);
      this->textBox2->TabIndex = 17;
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Location = System::Drawing::Point(11, 205);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(171, 17);
      this->label5->TabIndex = 20;
      this->label5->Text = L"Anzahl der Kanten (L x H)";
      // 
      // tb_corner_count_L
      // 
      this->tb_corner_count_L->Location = System::Drawing::Point(14, 225);
      this->tb_corner_count_L->Name = L"tb_corner_count_L";
      this->tb_corner_count_L->Size = System::Drawing::Size(126, 22);
      this->tb_corner_count_L->TabIndex = 19;
      // 
      // tb_corner_count_H
      // 
      this->tb_corner_count_H->Location = System::Drawing::Point(146, 225);
      this->tb_corner_count_H->Name = L"tb_corner_count_H";
      this->tb_corner_count_H->Size = System::Drawing::Size(126, 22);
      this->tb_corner_count_H->TabIndex = 21;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->radioButton1);
      this->groupBox1->Controls->Add(this->tb_corner_count_H);
      this->groupBox1->Controls->Add(this->label5);
      this->groupBox1->Controls->Add(this->tb_corner_count_L);
      this->groupBox1->Controls->Add(this->label4);
      this->groupBox1->Controls->Add(this->textBox2);
      this->groupBox1->Controls->Add(this->label3);
      this->groupBox1->Controls->Add(this->textBox1);
      this->groupBox1->Location = System::Drawing::Point(427, 16);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(299, 409);
      this->groupBox1->TabIndex = 22;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Single Calibration [Intrinsic]";
      // 
      // radioButton1
      // 
      this->radioButton1->AutoSize = true;
      this->radioButton1->Location = System::Drawing::Point(16, 37);
      this->radioButton1->Name = L"radioButton1";
      this->radioButton1->Size = System::Drawing::Size(110, 21);
      this->radioButton1->TabIndex = 22;
      this->radioButton1->TabStop = true;
      this->radioButton1->Text = L"radioButton1";
      this->radioButton1->UseVisualStyleBackColor = true;
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->radioButton2);
      this->groupBox2->Controls->Add(this->textBox3);
      this->groupBox2->Controls->Add(this->label6);
      this->groupBox2->Controls->Add(this->textBox4);
      this->groupBox2->Controls->Add(this->label7);
      this->groupBox2->Controls->Add(this->textBox5);
      this->groupBox2->Controls->Add(this->label8);
      this->groupBox2->Controls->Add(this->textBox6);
      this->groupBox2->Location = System::Drawing::Point(427, 473);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(299, 409);
      this->groupBox2->TabIndex = 23;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Stereo Calibration [Extrinsic]";
      // 
      // radioButton2
      // 
      this->radioButton2->AutoSize = true;
      this->radioButton2->Location = System::Drawing::Point(16, 37);
      this->radioButton2->Name = L"radioButton2";
      this->radioButton2->Size = System::Drawing::Size(110, 21);
      this->radioButton2->TabIndex = 23;
      this->radioButton2->TabStop = true;
      this->radioButton2->Text = L"radioButton2";
      this->radioButton2->UseVisualStyleBackColor = true;
      // 
      // textBox3
      // 
      this->textBox3->Location = System::Drawing::Point(148, 225);
      this->textBox3->Name = L"textBox3";
      this->textBox3->Size = System::Drawing::Size(126, 22);
      this->textBox3->TabIndex = 21;
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
      // textBox4
      // 
      this->textBox4->Location = System::Drawing::Point(16, 225);
      this->textBox4->Name = L"textBox4";
      this->textBox4->Size = System::Drawing::Size(126, 22);
      this->textBox4->TabIndex = 19;
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
      // textBox5
      // 
      this->textBox5->Location = System::Drawing::Point(16, 147);
      this->textBox5->Name = L"textBox5";
      this->textBox5->Size = System::Drawing::Size(126, 22);
      this->textBox5->TabIndex = 17;
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
      // textBox6
      // 
      this->textBox6->Location = System::Drawing::Point(16, 95);
      this->textBox6->Name = L"textBox6";
      this->textBox6->Size = System::Drawing::Size(126, 22);
      this->textBox6->TabIndex = 15;
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add(this->pictureBox3);
      this->groupBox3->Controls->Add(this->pictureBox2);
      this->groupBox3->Controls->Add(this->pictureBox1);
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
      // C_frm_CameraCalibration_Single
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1373, 1007);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->bt_start);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pb_camera_picture);
      this->Controls->Add(this->lbl_camera_id);
      this->Controls->Add(this->nup_camera_id);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Margin = System::Windows::Forms::Padding(4);
      this->Name = L"C_frm_CameraCalibration_Single";
      this->Text = L"frm_CameraCalibration_Single";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_camera_picture))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
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
	};
}
