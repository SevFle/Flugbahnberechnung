#pragma once

namespace Flugbahnberechnung {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frm_Camera_Positioning
	/// </summary>
	public ref class frm_Camera_Positioning : public System::Windows::Forms::Form
	{
	public:
		frm_Camera_Positioning(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frm_Camera_Positioning()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TextBox^  txtb_counter;
    protected:
    private: System::Windows::Forms::Button^  bt_exit;
    private: System::Windows::Forms::Timer^  taktgeber;
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
      this->taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->nup_Camera_L1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_L1 = (gcnew System::Windows::Forms::PictureBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->pb_Camera_L2 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_L2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_L3 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_L3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->pb_Camera_R3 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_R2 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->pb_Camera_R1 = (gcnew System::Windows::Forms::PictureBox());
      this->nup_Camera_R1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->label1 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L1))->BeginInit();
      this->groupBox1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L3))->BeginInit();
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
      this->txtb_counter->Location = System::Drawing::Point(965, 571);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 3;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(965, 492);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 4;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      // 
      // nup_Camera_L1
      // 
      this->nup_Camera_L1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L1->Location = System::Drawing::Point(28, 153);
      this->nup_Camera_L1->Name = L"nup_Camera_L1";
      this->nup_Camera_L1->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_L1->TabIndex = 5;
      this->nup_Camera_L1->ValueChanged += gcnew System::EventHandler(this, &frm_Camera_Positioning::nup_Camera_L1_ValueChanged);
      // 
      // pb_Camera_L1
      // 
      this->pb_Camera_L1->Location = System::Drawing::Point(28, 30);
      this->pb_Camera_L1->Name = L"pb_Camera_L1";
      this->pb_Camera_L1->Size = System::Drawing::Size(174, 117);
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
      this->groupBox1->Location = System::Drawing::Point(52, 48);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(807, 210);
      this->groupBox1->TabIndex = 7;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Links";
      // 
      // pb_Camera_L2
      // 
      this->pb_Camera_L2->Location = System::Drawing::Point(315, 30);
      this->pb_Camera_L2->Name = L"pb_Camera_L2";
      this->pb_Camera_L2->Size = System::Drawing::Size(174, 117);
      this->pb_Camera_L2->TabIndex = 8;
      this->pb_Camera_L2->TabStop = false;
      // 
      // nup_Camera_L2
      // 
      this->nup_Camera_L2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L2->Location = System::Drawing::Point(315, 153);
      this->nup_Camera_L2->Name = L"nup_Camera_L2";
      this->nup_Camera_L2->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_L2->TabIndex = 7;
      // 
      // pb_Camera_L3
      // 
      this->pb_Camera_L3->Location = System::Drawing::Point(603, 30);
      this->pb_Camera_L3->Name = L"pb_Camera_L3";
      this->pb_Camera_L3->Size = System::Drawing::Size(174, 117);
      this->pb_Camera_L3->TabIndex = 10;
      this->pb_Camera_L3->TabStop = false;
      // 
      // nup_Camera_L3
      // 
      this->nup_Camera_L3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_L3->Location = System::Drawing::Point(603, 153);
      this->nup_Camera_L3->Name = L"nup_Camera_L3";
      this->nup_Camera_L3->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_L3->TabIndex = 9;
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->pb_Camera_R3);
      this->groupBox2->Controls->Add(this->nup_Camera_R3);
      this->groupBox2->Controls->Add(this->pb_Camera_R2);
      this->groupBox2->Controls->Add(this->nup_Camera_R2);
      this->groupBox2->Controls->Add(this->pb_Camera_R1);
      this->groupBox2->Controls->Add(this->nup_Camera_R1);
      this->groupBox2->Location = System::Drawing::Point(52, 339);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(807, 210);
      this->groupBox2->TabIndex = 11;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Rechts";
      // 
      // pb_Camera_R3
      // 
      this->pb_Camera_R3->Location = System::Drawing::Point(603, 30);
      this->pb_Camera_R3->Name = L"pb_Camera_R3";
      this->pb_Camera_R3->Size = System::Drawing::Size(174, 117);
      this->pb_Camera_R3->TabIndex = 10;
      this->pb_Camera_R3->TabStop = false;
      // 
      // nup_Camera_R3
      // 
      this->nup_Camera_R3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R3->Location = System::Drawing::Point(603, 153);
      this->nup_Camera_R3->Name = L"nup_Camera_R3";
      this->nup_Camera_R3->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_R3->TabIndex = 9;
      // 
      // pb_Camera_R2
      // 
      this->pb_Camera_R2->Location = System::Drawing::Point(315, 30);
      this->pb_Camera_R2->Name = L"pb_Camera_R2";
      this->pb_Camera_R2->Size = System::Drawing::Size(174, 117);
      this->pb_Camera_R2->TabIndex = 8;
      this->pb_Camera_R2->TabStop = false;
      // 
      // nup_Camera_R2
      // 
      this->nup_Camera_R2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R2->Location = System::Drawing::Point(315, 153);
      this->nup_Camera_R2->Name = L"nup_Camera_R2";
      this->nup_Camera_R2->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_R2->TabIndex = 7;
      // 
      // pb_Camera_R1
      // 
      this->pb_Camera_R1->Location = System::Drawing::Point(28, 30);
      this->pb_Camera_R1->Name = L"pb_Camera_R1";
      this->pb_Camera_R1->Size = System::Drawing::Size(174, 117);
      this->pb_Camera_R1->TabIndex = 6;
      this->pb_Camera_R1->TabStop = false;
      // 
      // nup_Camera_R1
      // 
      this->nup_Camera_R1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_Camera_R1->Location = System::Drawing::Point(28, 153);
      this->nup_Camera_R1->Name = L"nup_Camera_R1";
      this->nup_Camera_R1->Size = System::Drawing::Size(37, 29);
      this->nup_Camera_R1->TabIndex = 5;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(90, 283);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(314, 31);
      this->label1->TabIndex = 12;
      this->label1->Text = L"Erste Wurfrichtung  ----->";
      // 
      // frm_Camera_Positioning
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1157, 606);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Name = L"frm_Camera_Positioning";
      this->Text = L"frm_Camera_Positioning";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L1))->EndInit();
      this->groupBox1->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Camera_L3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Camera_L3))->EndInit();
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
    private: System::Void nup_Camera_L1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
      {
      }
};
}
