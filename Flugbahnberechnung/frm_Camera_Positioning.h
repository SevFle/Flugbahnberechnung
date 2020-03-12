#pragma once

#include "Main.h"

namespace nmsp_frm_camera_positioning 
  {
  using namespace nmsp_GlobalObjects;
  using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class c_frm_Camera_Positioning : public System::Windows::Forms::Form
	{
	public:
  c_frm_Camera_Positioning(C_GlobalObjects^ GlobalObjects, C_Main^  Main);
	protected:
  ~c_frm_Camera_Positioning();


    private:
    C_GlobalObjects^    GlobalObjects;
    C_Main^             Main;

    UInt32              Zaehler;
    UInt32              Taktgeber_Intervall;


 



    private: System::Windows::Forms::TextBox^  txtb_counter;
    protected:
    private: System::Windows::Forms::Button^  bt_exit;
    private: System::Windows::Forms::Timer^  Taktgeber;

    private: System::Windows::Forms::NumericUpDown^  nup_Camera_L1;
    private: System::Windows::Forms::PictureBox^  pb_Camera_L1;

    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::PictureBox^  pb_Camera_L3;

    private: System::Windows::Forms::NumericUpDown^  nup_Camera_L3;
    private: System::Windows::Forms::PictureBox^  pb_Camera_L2;

    private: System::Windows::Forms::NumericUpDown^  nup_Camera_L2;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::PictureBox^  pb_Camera_R3;

    private: System::Windows::Forms::NumericUpDown^  nup_Camera_R3;
    private: System::Windows::Forms::PictureBox^  pb_Camera_R2;


    private: System::Windows::Forms::NumericUpDown^  nup_Camera_R2;
    private: System::Windows::Forms::PictureBox^  pb_Camera_R1;


    private: System::Windows::Forms::NumericUpDown^  nup_Camera_R1;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Button^  bt_appy;
    private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


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
      this->nup_Camera_L1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_L1 = (gcnew System::Windows::Forms::PictureBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->pb_Camera_L3 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_L3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_L2 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_L2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->pb_Camera_R3 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_R2 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_R1 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->bt_appy = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L1))->BeginInit();
      this->groupBox1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L2))->BeginInit();
      this->groupBox2->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R1))->BeginInit();
      this->SuspendLayout();
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1287, 703);
      this->txtb_counter->Margin = System::Windows::Forms::Padding(4);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(220, 22);
      this->txtb_counter->TabIndex = 3;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1287, 606);
      this->bt_exit->Margin = System::Windows::Forms::Padding(4);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(223, 90);
      this->bt_exit->TabIndex = 4;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::bt_exit_Click);
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::taktgeber_Tick);
      // 
      // nup_Camera_L1
      // 
      this->nup_Camera_L1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L1->Location = System::Drawing::Point(37, 234);
      this->nup_Camera_L1->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_L1->Name = L"nup_Camera_L1";
      this->nup_Camera_L1->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_L1->TabIndex = 5;
      this->nup_Camera_L1->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_L1_ValueChanged);
      // 
      // pb_Camera_L1
      // 
      this->pb_Camera_L1->Location = System::Drawing::Point(37, 83);
      this->pb_Camera_L1->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_L1->Name = L"pb_Camera_L1";
      this->pb_Camera_L1->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_L1->TabIndex = 6;
      this->pb_Camera_L1->TabStop = false;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->pb_Camera_L3);
      this->groupBox1->Controls->Add(this->nup_Camera_L3);
      this->groupBox1->Controls->Add(this->pb_Camera_L2);
      this->groupBox1->Controls->Add(this->nup_Camera_L2);
      this->groupBox1->Controls->Add(this->pb_Camera_L1);
      this->groupBox1->Controls->Add(this->nup_Camera_L1);
      this->groupBox1->Location = System::Drawing::Point(69, 26);
      this->groupBox1->Margin = System::Windows::Forms::Padding(4);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Padding = System::Windows::Forms::Padding(4);
      this->groupBox1->Size = System::Drawing::Size(1076, 291);
      this->groupBox1->TabIndex = 7;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Links";
      // 
      // pb_Camera_L3
      // 
      this->pb_Camera_L3->Location = System::Drawing::Point(804, 83);
      this->pb_Camera_L3->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_L3->Name = L"pb_Camera_L3";
      this->pb_Camera_L3->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_L3->TabIndex = 10;
      this->pb_Camera_L3->TabStop = false;
      // 
      // nup_Camera_L3
      // 
      this->nup_Camera_L3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L3->Location = System::Drawing::Point(804, 234);
      this->nup_Camera_L3->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_L3->Name = L"nup_Camera_L3";
      this->nup_Camera_L3->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_L3->TabIndex = 9;
      this->nup_Camera_L3->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_L3_ValueChanged);
      // 
      // pb_Camera_L2
      // 
      this->pb_Camera_L2->Location = System::Drawing::Point(420, 83);
      this->pb_Camera_L2->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_L2->Name = L"pb_Camera_L2";
      this->pb_Camera_L2->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_L2->TabIndex = 8;
      this->pb_Camera_L2->TabStop = false;
      // 
      // nup_Camera_L2
      // 
      this->nup_Camera_L2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L2->Location = System::Drawing::Point(420, 234);
      this->nup_Camera_L2->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_L2->Name = L"nup_Camera_L2";
      this->nup_Camera_L2->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_L2->TabIndex = 7;
      this->nup_Camera_L2->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_L2_ValueChanged);
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->pb_Camera_R3);
      this->groupBox2->Controls->Add(this->nup_Camera_R3);
      this->groupBox2->Controls->Add(this->pb_Camera_R2);
      this->groupBox2->Controls->Add(this->nup_Camera_R2);
      this->groupBox2->Controls->Add(this->pb_Camera_R1);
      this->groupBox2->Controls->Add(this->nup_Camera_R1);
      this->groupBox2->Location = System::Drawing::Point(69, 417);
      this->groupBox2->Margin = System::Windows::Forms::Padding(4);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Padding = System::Windows::Forms::Padding(4);
      this->groupBox2->Size = System::Drawing::Size(1076, 258);
      this->groupBox2->TabIndex = 11;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Rechts";
      // 
      // pb_Camera_R3
      // 
      this->pb_Camera_R3->Location = System::Drawing::Point(804, 37);
      this->pb_Camera_R3->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_R3->Name = L"pb_Camera_R3";
      this->pb_Camera_R3->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_R3->TabIndex = 10;
      this->pb_Camera_R3->TabStop = false;
      // 
      // nup_Camera_R3
      // 
      this->nup_Camera_R3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R3->Location = System::Drawing::Point(804, 188);
      this->nup_Camera_R3->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_R3->Name = L"nup_Camera_R3";
      this->nup_Camera_R3->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_R3->TabIndex = 9;
      this->nup_Camera_R3->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_R3_ValueChanged);
      // 
      // pb_Camera_R2
      // 
      this->pb_Camera_R2->Location = System::Drawing::Point(420, 37);
      this->pb_Camera_R2->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_R2->Name = L"pb_Camera_R2";
      this->pb_Camera_R2->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_R2->TabIndex = 8;
      this->pb_Camera_R2->TabStop = false;
      // 
      // nup_Camera_R2
      // 
      this->nup_Camera_R2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R2->Location = System::Drawing::Point(420, 188);
      this->nup_Camera_R2->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_R2->Name = L"nup_Camera_R2";
      this->nup_Camera_R2->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_R2->TabIndex = 7;
      this->nup_Camera_R2->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_R2_ValueChanged);
      // 
      // pb_Camera_R1
      // 
      this->pb_Camera_R1->Location = System::Drawing::Point(37, 37);
      this->pb_Camera_R1->Margin = System::Windows::Forms::Padding(4);
      this->pb_Camera_R1->Name = L"pb_Camera_R1";
      this->pb_Camera_R1->Size = System::Drawing::Size(232, 144);
      this->pb_Camera_R1->TabIndex = 6;
      this->pb_Camera_R1->TabStop = false;
      // 
      // nup_Camera_R1
      // 
      this->nup_Camera_R1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R1->Location = System::Drawing::Point(37, 188);
      this->nup_Camera_R1->Margin = System::Windows::Forms::Padding(4);
      this->nup_Camera_R1->Name = L"nup_Camera_R1";
      this->nup_Camera_R1->Size = System::Drawing::Size(49, 34);
      this->nup_Camera_R1->TabIndex = 5;
      this->nup_Camera_R1->ValueChanged += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::nup_Camera_R1_ValueChanged);
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(120, 348);
      this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(390, 39);
      this->label1->TabIndex = 12;
      this->label1->Text = L"Erste Wurfrichtung  ----->";
      // 
      // bt_appy
      // 
      this->bt_appy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_appy->Location = System::Drawing::Point(1287, 417);
      this->bt_appy->Margin = System::Windows::Forms::Padding(4);
      this->bt_appy->Name = L"bt_appy";
      this->bt_appy->Size = System::Drawing::Size(223, 90);
      this->bt_appy->TabIndex = 13;
      this->bt_appy->Text = L"Apply";
      this->bt_appy->UseVisualStyleBackColor = true;
      this->bt_appy->Click += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::bt_appy_Click);
      // 
      // c_frm_Camera_Positioning
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1543, 746);
      this->Controls->Add(this->bt_appy);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Margin = System::Windows::Forms::Padding(4);
      this->Name = L"c_frm_Camera_Positioning";
      this->Text = L"frm_Camera_Positioning";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &c_frm_Camera_Positioning::c_frm_Camera_Positioning_FormClosing);
      this->Load += gcnew System::EventHandler(this, &c_frm_Camera_Positioning::c_frm_Camera_Positioning_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L1))->EndInit();
      this->groupBox1->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L2))->EndInit();
      this->groupBox2->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_R1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_R1))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
    private: 
    System::Void nup_Camera_L1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void nup_Camera_L2_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void nup_Camera_L3_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void nup_Camera_R1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void nup_Camera_R2_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void nup_Camera_R3_ValueChanged(System::Object^  sender, System::EventArgs^  e);
    System::Void taktgeber_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void bt_appy_Click(System::Object^  sender, System::EventArgs^  e);


    System::Void          c_frm_Camera_Positioning::FillPicturebox                                     (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
    System::Void          c_frm_Camera_Positioning::FillMat2Picturebox                                 (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage);
    System::Void bt_exit_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void c_frm_Camera_Positioning_Load(System::Object^  sender, System::EventArgs^  e);
    System::Void c_frm_Camera_Positioning_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};
}


