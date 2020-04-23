#pragma once
#include "Main.h"
#include <opencv2/core/mat.hpp>

using namespace nmsp_Main;

namespace nsmp_frm_object_tracking
  {
  using namespace nmsp_GlobalObjects;
	public ref class c_frm_Object_Tracking : public System::Windows::Forms::Form
	{
	public:
		c_frm_Object_Tracking             (C_GlobalObjects* GlobalObjects, C_Main^  Main);

	protected:
  ~c_frm_Object_Tracking              ();

    private:
    C_GlobalObjects*    GlobalObjects;
    C_Main^             Main;

    UInt32              Zaehler;
    UInt32              camera_id_in_use;
    UInt32              Taktgeber_Intervall;
    UInt32              TimerWait;


    Thread ^tracking = gcnew Thread(gcnew ThreadStart(this, &c_frm_Object_Tracking::tracking_thread));







	  System::Windows::Forms::Button^  bt_exit;

    private:
	  System::Windows::Forms::TextBox^  txtb_counter;
    private: System::Windows::Forms::Timer^  Taktgeber;
    private: System::Windows::Forms::PictureBox^  pb_cam_left;
    private: System::Windows::Forms::PictureBox^  pb_cam_right;


    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Label^  lbl_cam_right;
    private: System::Windows::Forms::Label^  lbl_cam_left;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TextBox^  lbl_object_pos_z;
    private: System::Windows::Forms::TextBox^  lbl_object_pos_y;
    private: System::Windows::Forms::TextBox^  lbl_object_pos_x;
    private: System::Windows::Forms::Button^  bt_start;
    private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::GroupBox^  groupBox4;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::TextBox^  textBox2;
    private: System::Windows::Forms::TextBox^  textBox3;
    private: System::Windows::Forms::Label^  lbl_thread_running;

    private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->pb_cam_left = (gcnew System::Windows::Forms::PictureBox());
      this->pb_cam_right = (gcnew System::Windows::Forms::PictureBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->lbl_cam_right = (gcnew System::Windows::Forms::Label());
      this->lbl_cam_left = (gcnew System::Windows::Forms::Label());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->lbl_object_pos_z = (gcnew System::Windows::Forms::TextBox());
      this->lbl_object_pos_y = (gcnew System::Windows::Forms::TextBox());
      this->lbl_object_pos_x = (gcnew System::Windows::Forms::TextBox());
      this->bt_start = (gcnew System::Windows::Forms::Button());
      this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->textBox3 = (gcnew System::Windows::Forms::TextBox());
      this->lbl_thread_running = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cam_left))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cam_right))->BeginInit();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
      this->groupBox3->SuspendLayout();
      this->groupBox4->SuspendLayout();
      this->SuspendLayout();
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1672, 712);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 14;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &c_frm_Object_Tracking::bt_exit_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1672, 791);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 13;
      // 
      // Taktgeber
      // 
      this->Taktgeber->Interval = 25;
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &c_frm_Object_Tracking::Taktgeber_Tick);
      // 
      // pb_cam_left
      // 
      this->pb_cam_left->Location = System::Drawing::Point(19, 47);
      this->pb_cam_left->Name = L"pb_cam_left";
      this->pb_cam_left->Size = System::Drawing::Size(578, 504);
      this->pb_cam_left->TabIndex = 15;
      this->pb_cam_left->TabStop = false;
      // 
      // pb_cam_right
      // 
      this->pb_cam_right->Location = System::Drawing::Point(634, 47);
      this->pb_cam_right->Name = L"pb_cam_right";
      this->pb_cam_right->Size = System::Drawing::Size(578, 504);
      this->pb_cam_right->TabIndex = 16;
      this->pb_cam_right->TabStop = false;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->lbl_cam_right);
      this->groupBox1->Controls->Add(this->lbl_cam_left);
      this->groupBox1->Controls->Add(this->pb_cam_right);
      this->groupBox1->Controls->Add(this->pb_cam_left);
      this->groupBox1->Location = System::Drawing::Point(11, 14);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(1239, 581);
      this->groupBox1->TabIndex = 17;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"groupBox1";
      // 
      // lbl_cam_right
      // 
      this->lbl_cam_right->AutoSize = true;
      this->lbl_cam_right->Location = System::Drawing::Point(631, 31);
      this->lbl_cam_right->Name = L"lbl_cam_right";
      this->lbl_cam_right->Size = System::Drawing::Size(75, 13);
      this->lbl_cam_right->TabIndex = 18;
      this->lbl_cam_right->Text = L"Kamera rechts";
      // 
      // lbl_cam_left
      // 
      this->lbl_cam_left->AutoSize = true;
      this->lbl_cam_left->Location = System::Drawing::Point(16, 31);
      this->lbl_cam_left->Name = L"lbl_cam_left";
      this->lbl_cam_left->Size = System::Drawing::Size(67, 13);
      this->lbl_cam_left->TabIndex = 17;
      this->lbl_cam_left->Text = L"Kamera links";
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->label4);
      this->groupBox2->Controls->Add(this->label3);
      this->groupBox2->Controls->Add(this->label2);
      this->groupBox2->Controls->Add(this->lbl_object_pos_z);
      this->groupBox2->Controls->Add(this->lbl_object_pos_y);
      this->groupBox2->Controls->Add(this->lbl_object_pos_x);
      this->groupBox2->Location = System::Drawing::Point(1309, 14);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(507, 266);
      this->groupBox2->TabIndex = 18;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Aktuellen Objektdaten";
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label4->Location = System::Drawing::Point(27, 139);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(87, 20);
      this->label4->TabIndex = 21;
      this->label4->Text = L"Position [Z]";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(27, 90);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(88, 20);
      this->label3->TabIndex = 20;
      this->label3->Text = L"Position [Y]";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(27, 47);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(88, 20);
      this->label2->TabIndex = 19;
      this->label2->Text = L"Position [X]";
      // 
      // lbl_object_pos_z
      // 
      this->lbl_object_pos_z->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
                                      System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_object_pos_z->Location = System::Drawing::Point(121, 137);
      this->lbl_object_pos_z->Name = L"lbl_object_pos_z";
      this->lbl_object_pos_z->Size = System::Drawing::Size(71, 24);
      this->lbl_object_pos_z->TabIndex = 2;
      // 
      // lbl_object_pos_y
      // 
      this->lbl_object_pos_y->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
                                      System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_object_pos_y->Location = System::Drawing::Point(121, 90);
      this->lbl_object_pos_y->Name = L"lbl_object_pos_y";
      this->lbl_object_pos_y->Size = System::Drawing::Size(71, 24);
      this->lbl_object_pos_y->TabIndex = 1;
      // 
      // lbl_object_pos_x
      // 
      this->lbl_object_pos_x->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
                                      System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_object_pos_x->Location = System::Drawing::Point(121, 47);
      this->lbl_object_pos_x->Name = L"lbl_object_pos_x";
      this->lbl_object_pos_x->Size = System::Drawing::Size(71, 24);
      this->lbl_object_pos_x->TabIndex = 0;
      // 
      // bt_start
      // 
      this->bt_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->bt_start->Location = System::Drawing::Point(30, 712);
      this->bt_start->Name = L"bt_start";
      this->bt_start->Size = System::Drawing::Size(167, 73);
      this->bt_start->TabIndex = 19;
      this->bt_start->Text = L"Start";
      this->bt_start->UseVisualStyleBackColor = true;
      this->bt_start->Click += gcnew System::EventHandler(this, &c_frm_Object_Tracking::bt_start_Click);
      // 
      // numericUpDown1
      // 
      this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                    static_cast<System::Byte>(0)));
      this->numericUpDown1->Location = System::Drawing::Point(224, 756);
      this->numericUpDown1->Name = L"numericUpDown1";
      this->numericUpDown1->Size = System::Drawing::Size(44, 29);
      this->numericUpDown1->TabIndex = 20;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(220, 733);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(86, 20);
      this->label1->TabIndex = 19;
      this->label1->Text = L"Kameraset";
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add(this->groupBox4);
      this->groupBox3->Location = System::Drawing::Point(1309, 299);
      this->groupBox3->Name = L"groupBox3";
      this->groupBox3->Size = System::Drawing::Size(507, 266);
      this->groupBox3->TabIndex = 22;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = L"Kalmanfilter Vorraussagen";
      // 
      // groupBox4
      // 
      this->groupBox4->Controls->Add(this->label5);
      this->groupBox4->Controls->Add(this->label6);
      this->groupBox4->Controls->Add(this->label7);
      this->groupBox4->Controls->Add(this->textBox1);
      this->groupBox4->Controls->Add(this->textBox2);
      this->groupBox4->Controls->Add(this->textBox3);
      this->groupBox4->Location = System::Drawing::Point(22, 42);
      this->groupBox4->Name = L"groupBox4";
      this->groupBox4->Size = System::Drawing::Size(181, 187);
      this->groupBox4->TabIndex = 22;
      this->groupBox4->TabStop = false;
      this->groupBox4->Text = L"Landepunkt";
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label5->Location = System::Drawing::Point(5, 144);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(87, 20);
      this->label5->TabIndex = 21;
      this->label5->Text = L"Position [Z]";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label6->Location = System::Drawing::Point(5, 95);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(88, 20);
      this->label6->TabIndex = 20;
      this->label6->Text = L"Position [Y]";
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label7->Location = System::Drawing::Point(5, 52);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(88, 20);
      this->label7->TabIndex = 19;
      this->label7->Text = L"Position [X]";
      // 
      // textBox1
      // 
      this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox1->Location = System::Drawing::Point(99, 142);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(71, 24);
      this->textBox1->TabIndex = 2;
      // 
      // textBox2
      // 
      this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox2->Location = System::Drawing::Point(99, 95);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(71, 24);
      this->textBox2->TabIndex = 1;
      // 
      // textBox3
      // 
      this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->textBox3->Location = System::Drawing::Point(99, 52);
      this->textBox3->Name = L"textBox3";
      this->textBox3->Size = System::Drawing::Size(71, 24);
      this->textBox3->TabIndex = 0;
      // 
      // lbl_thread_running
      // 
      this->lbl_thread_running->AutoSize = true;
      this->lbl_thread_running->Enabled = false;
      this->lbl_thread_running->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold,
                                        System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_thread_running->ForeColor = System::Drawing::Color::Green;
      this->lbl_thread_running->Location = System::Drawing::Point(25, 662);
      this->lbl_thread_running->Name = L"lbl_thread_running";
      this->lbl_thread_running->Size = System::Drawing::Size(252, 25);
      this->lbl_thread_running->TabIndex = 22;
      this->lbl_thread_running->Text = L"Tracker thread running";
      // 
      // c_frm_Object_Tracking
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1851, 819);
      this->Controls->Add(this->lbl_thread_running);
      this->Controls->Add(this->groupBox3);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->numericUpDown1);
      this->Controls->Add(this->bt_start);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->bt_exit);
      this->Controls->Add(this->txtb_counter);
      this->Name = L"c_frm_Object_Tracking";
      this->Text = L"frm_Object_Tracking";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &c_frm_Object_Tracking::c_frm_Object_Tracking_FormClosing);
      this->Load += gcnew System::EventHandler(this, &c_frm_Object_Tracking::c_frm_Object_Tracking_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cam_left))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_cam_right))->EndInit();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
      this->groupBox3->ResumeLayout(false);
      this->groupBox4->ResumeLayout(false);
      this->groupBox4->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion


	  private:
    System::Void		bt_exit_Click						                          (System::Object^  sender, System::EventArgs^ e);
    System::Void		Taktgeber_Tick						                        (System::Object^  sender, System::EventArgs^ e);
    System::Void    FillPicturebox                                    (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
    System::Void    FillMat2Picturebox                                (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage);
    System::Void    c_frm_Object_Tracking_Load                        (System::Object^  sender, System::EventArgs^  e);
    System::Void    c_frm_Object_Tracking_FormClosing                 (System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
    System::Void    bt_start_Click                                    (System::Object^  sender, System::EventArgs^  e);
  System::Void tracking_thread ();
  };
}
