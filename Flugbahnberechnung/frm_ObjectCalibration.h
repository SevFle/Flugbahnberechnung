#pragma once
#include "Main.h"

using namespace NmSp_Main;

namespace NmSp_frm_ObjectCalibration 
  {
  using namespace nmsp_GlobalObjects;
  public ref class C_frm_ObjectCalibration : public System::Windows::Forms::Form
	  {
	  public:
    C_frm_ObjectCalibration               (C_GlobalObjects^ GlobalObjects, C_Main^  Main);
 	  protected:
    ~C_frm_ObjectCalibration              ();

	  private:
    C_GlobalObjects^    GlobalObjects;
    C_Main^             Main;

    UInt32              Zaehler;
    UInt32              Taktgeber_Intervall;


      private: System::Windows::Forms::PictureBox^  pictureBox1;
      protected:
      private: System::Windows::Forms::PictureBox^  pictureBox2;
      private: System::Windows::Forms::Label^  lbl_org_pic;
      private: System::Windows::Forms::Label^  lbl_hsv_filter;

      private: System::Windows::Forms::PictureBox^  pictureBox3;
      private: System::Windows::Forms::PictureBox^  pictureBox4;
      private: System::Windows::Forms::Label^  lbl_tracked_obj;

      private: System::Windows::Forms::PictureBox^  pictureBox5;
      private: System::Windows::Forms::PictureBox^  pictureBox6;
      private: System::Windows::Forms::HScrollBar^  hsb_hue_min;


      private: System::Windows::Forms::GroupBox^  gb_farbfilter;


      private: System::Windows::Forms::Label^  label1;
      private: System::Windows::Forms::Label^  label7;
      private: System::Windows::Forms::Label^  label8;
      private: System::Windows::Forms::HScrollBar^  hsb_value_max;

      private: System::Windows::Forms::Label^  label9;
      private: System::Windows::Forms::HScrollBar^  hsb_value_min;

      private: System::Windows::Forms::Label^  label2;
      private: System::Windows::Forms::Label^  label5;
      private: System::Windows::Forms::HScrollBar^  hsb_saturation_max;

      private: System::Windows::Forms::Label^  label6;
      private: System::Windows::Forms::HScrollBar^  hsb_saturation_min;

      private: System::Windows::Forms::Label^  label4;
      private: System::Windows::Forms::Label^  label3;
      private: System::Windows::Forms::HScrollBar^  hsb_hue_max;

      private: System::Windows::Forms::Button^  bt_exit;
      private: System::Windows::Forms::TextBox^  txtb_counter;
      private: System::Windows::Forms::Timer^  Taktgeber;

      private: System::Windows::Forms::Label^  label10;
      private: System::Windows::Forms::HScrollBar^  hsb_erode;
      private: System::Windows::Forms::Label^  label11;
      private: System::Windows::Forms::HScrollBar^  hsb_dilation;
      private: System::Windows::Forms::Label^  lbl_bilateral;
      private: System::Windows::Forms::Label^  label14;



      private: System::Windows::Forms::Label^  label12;

      private: System::Windows::Forms::Label^  label13;

      private: System::Windows::Forms::NumericUpDown^  nup_bilateral;

      private: System::Windows::Forms::NumericUpDown^  nup_gaussian;

      private: System::Windows::Forms::NumericUpDown^  nup_closing;
      private: System::Windows::Forms::NumericUpDown^  nup_opening;
      private: System::Windows::Forms::NumericUpDown^  nup_dilation;
      private: System::Windows::Forms::NumericUpDown^  nup_erode;
      private: System::Windows::Forms::Label^  label16;
      private: System::Windows::Forms::NumericUpDown^  nup_gaussian_sigma;
      private: System::Windows::Forms::NumericUpDown^  nup_Cam_ID;
      private: System::Windows::Forms::Button^  bt_Start;
      private: System::Windows::Forms::Button^  bt_Stop;
      private: System::Windows::Forms::Label^  label17;
      private: System::ComponentModel::IContainer^  components;

  

    #pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
      this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
      this->lbl_org_pic = (gcnew System::Windows::Forms::Label());
      this->lbl_hsv_filter = (gcnew System::Windows::Forms::Label());
      this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
      this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
      this->lbl_tracked_obj = (gcnew System::Windows::Forms::Label());
      this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
      this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
      this->hsb_hue_min = (gcnew System::Windows::Forms::HScrollBar());
      this->gb_farbfilter = (gcnew System::Windows::Forms::GroupBox());
      this->label16 = (gcnew System::Windows::Forms::Label());
      this->nup_gaussian_sigma = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_bilateral = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_gaussian = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_closing = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_opening = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_dilation = (gcnew System::Windows::Forms::NumericUpDown());
      this->nup_erode = (gcnew System::Windows::Forms::NumericUpDown());
      this->lbl_bilateral = (gcnew System::Windows::Forms::Label());
      this->label14 = (gcnew System::Windows::Forms::Label());
      this->label12 = (gcnew System::Windows::Forms::Label());
      this->label13 = (gcnew System::Windows::Forms::Label());
      this->label11 = (gcnew System::Windows::Forms::Label());
      this->hsb_dilation = (gcnew System::Windows::Forms::HScrollBar());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->hsb_erode = (gcnew System::Windows::Forms::HScrollBar());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->hsb_value_max = (gcnew System::Windows::Forms::HScrollBar());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->hsb_value_min = (gcnew System::Windows::Forms::HScrollBar());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->hsb_saturation_max = (gcnew System::Windows::Forms::HScrollBar());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->hsb_saturation_min = (gcnew System::Windows::Forms::HScrollBar());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->hsb_hue_max = (gcnew System::Windows::Forms::HScrollBar());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->nup_Cam_ID = (gcnew System::Windows::Forms::NumericUpDown());
      this->bt_Start = (gcnew System::Windows::Forms::Button());
      this->bt_Stop = (gcnew System::Windows::Forms::Button());
      this->label17 = (gcnew System::Windows::Forms::Label());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
      this->gb_farbfilter->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_gaussian_sigma))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_bilateral))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_gaussian))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_closing))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_opening))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_dilation))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_erode))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Cam_ID))->BeginInit();
      this->SuspendLayout();
      // 
      // pictureBox1
      // 
      this->pictureBox1->Location = System::Drawing::Point(15, 30);
      this->pictureBox1->Name = L"pictureBox1";
      this->pictureBox1->Size = System::Drawing::Size(239, 180);
      this->pictureBox1->TabIndex = 0;
      this->pictureBox1->TabStop = false;
      // 
      // pictureBox2
      // 
      this->pictureBox2->Location = System::Drawing::Point(260, 30);
      this->pictureBox2->Name = L"pictureBox2";
      this->pictureBox2->Size = System::Drawing::Size(239, 180);
      this->pictureBox2->TabIndex = 1;
      this->pictureBox2->TabStop = false;
      // 
      // lbl_org_pic
      // 
      this->lbl_org_pic->AutoSize = true;
      this->lbl_org_pic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                 static_cast<System::Byte>(0)));
      this->lbl_org_pic->Location = System::Drawing::Point(12, 9);
      this->lbl_org_pic->Name = L"lbl_org_pic";
      this->lbl_org_pic->Size = System::Drawing::Size(80, 18);
      this->lbl_org_pic->TabIndex = 2;
      this->lbl_org_pic->Text = L"Originalbild";
      // 
      // lbl_hsv_filter
      // 
      this->lbl_hsv_filter->AutoSize = true;
      this->lbl_hsv_filter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                    static_cast<System::Byte>(0)));
      this->lbl_hsv_filter->Location = System::Drawing::Point(12, 217);
      this->lbl_hsv_filter->Name = L"lbl_hsv_filter";
      this->lbl_hsv_filter->Size = System::Drawing::Size(75, 18);
      this->lbl_hsv_filter->TabIndex = 5;
      this->lbl_hsv_filter->Text = L"HSV-Filter";
      // 
      // pictureBox3
      // 
      this->pictureBox3->Location = System::Drawing::Point(260, 238);
      this->pictureBox3->Name = L"pictureBox3";
      this->pictureBox3->Size = System::Drawing::Size(239, 180);
      this->pictureBox3->TabIndex = 4;
      this->pictureBox3->TabStop = false;
      // 
      // pictureBox4
      // 
      this->pictureBox4->Location = System::Drawing::Point(15, 238);
      this->pictureBox4->Name = L"pictureBox4";
      this->pictureBox4->Size = System::Drawing::Size(239, 180);
      this->pictureBox4->TabIndex = 3;
      this->pictureBox4->TabStop = false;
      // 
      // lbl_tracked_obj
      // 
      this->lbl_tracked_obj->AutoSize = true;
      this->lbl_tracked_obj->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
                                     System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_tracked_obj->Location = System::Drawing::Point(12, 428);
      this->lbl_tracked_obj->Name = L"lbl_tracked_obj";
      this->lbl_tracked_obj->Size = System::Drawing::Size(109, 18);
      this->lbl_tracked_obj->TabIndex = 8;
      this->lbl_tracked_obj->Text = L"Tracked Object";
      // 
      // pictureBox5
      // 
      this->pictureBox5->Location = System::Drawing::Point(260, 449);
      this->pictureBox5->Name = L"pictureBox5";
      this->pictureBox5->Size = System::Drawing::Size(239, 180);
      this->pictureBox5->TabIndex = 7;
      this->pictureBox5->TabStop = false;
      // 
      // pictureBox6
      // 
      this->pictureBox6->Location = System::Drawing::Point(15, 449);
      this->pictureBox6->Name = L"pictureBox6";
      this->pictureBox6->Size = System::Drawing::Size(239, 180);
      this->pictureBox6->TabIndex = 6;
      this->pictureBox6->TabStop = false;
      // 
      // hsb_hue_min
      // 
      this->hsb_hue_min->Location = System::Drawing::Point(118, 17);
      this->hsb_hue_min->Name = L"hsb_hue_min";
      this->hsb_hue_min->Size = System::Drawing::Size(354, 20);
      this->hsb_hue_min->TabIndex = 9;
      // 
      // gb_farbfilter
      // 
      this->gb_farbfilter->Controls->Add(this->label16);
      this->gb_farbfilter->Controls->Add(this->nup_gaussian_sigma);
      this->gb_farbfilter->Controls->Add(this->nup_bilateral);
      this->gb_farbfilter->Controls->Add(this->nup_gaussian);
      this->gb_farbfilter->Controls->Add(this->nup_closing);
      this->gb_farbfilter->Controls->Add(this->nup_opening);
      this->gb_farbfilter->Controls->Add(this->nup_dilation);
      this->gb_farbfilter->Controls->Add(this->nup_erode);
      this->gb_farbfilter->Controls->Add(this->lbl_bilateral);
      this->gb_farbfilter->Controls->Add(this->label14);
      this->gb_farbfilter->Controls->Add(this->label12);
      this->gb_farbfilter->Controls->Add(this->label13);
      this->gb_farbfilter->Controls->Add(this->label11);
      this->gb_farbfilter->Controls->Add(this->hsb_dilation);
      this->gb_farbfilter->Controls->Add(this->label10);
      this->gb_farbfilter->Controls->Add(this->hsb_erode);
      this->gb_farbfilter->Controls->Add(this->label7);
      this->gb_farbfilter->Controls->Add(this->label8);
      this->gb_farbfilter->Controls->Add(this->hsb_value_max);
      this->gb_farbfilter->Controls->Add(this->label9);
      this->gb_farbfilter->Controls->Add(this->hsb_value_min);
      this->gb_farbfilter->Controls->Add(this->label2);
      this->gb_farbfilter->Controls->Add(this->label5);
      this->gb_farbfilter->Controls->Add(this->hsb_saturation_max);
      this->gb_farbfilter->Controls->Add(this->label6);
      this->gb_farbfilter->Controls->Add(this->hsb_saturation_min);
      this->gb_farbfilter->Controls->Add(this->label4);
      this->gb_farbfilter->Controls->Add(this->label3);
      this->gb_farbfilter->Controls->Add(this->hsb_hue_max);
      this->gb_farbfilter->Controls->Add(this->label1);
      this->gb_farbfilter->Controls->Add(this->hsb_hue_min);
      this->gb_farbfilter->Location = System::Drawing::Point(570, 14);
      this->gb_farbfilter->Name = L"gb_farbfilter";
      this->gb_farbfilter->Size = System::Drawing::Size(591, 679);
      this->gb_farbfilter->TabIndex = 10;
      this->gb_farbfilter->TabStop = false;
      this->gb_farbfilter->Text = L"Farbfilter";
      // 
      // label16
      // 
      this->label16->AutoSize = true;
      this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label16->Location = System::Drawing::Point(125, 351);
      this->label16->Name = L"label16";
      this->label16->Size = System::Drawing::Size(83, 18);
      this->label16->TabIndex = 58;
      this->label16->Text = L"Kernel Size";
      // 
      // nup_gaussian_sigma
      // 
      this->nup_gaussian_sigma->Location = System::Drawing::Point(324, 517);
      this->nup_gaussian_sigma->Name = L"nup_gaussian_sigma";
      this->nup_gaussian_sigma->Size = System::Drawing::Size(57, 20);
      this->nup_gaussian_sigma->TabIndex = 57;
      // 
      // nup_bilateral
      // 
      this->nup_bilateral->Location = System::Drawing::Point(128, 568);
      this->nup_bilateral->Name = L"nup_bilateral";
      this->nup_bilateral->Size = System::Drawing::Size(57, 20);
      this->nup_bilateral->TabIndex = 56;
      // 
      // nup_gaussian
      // 
      this->nup_gaussian->Location = System::Drawing::Point(128, 517);
      this->nup_gaussian->Name = L"nup_gaussian";
      this->nup_gaussian->Size = System::Drawing::Size(57, 20);
      this->nup_gaussian->TabIndex = 55;
      // 
      // nup_closing
      // 
      this->nup_closing->Location = System::Drawing::Point(128, 428);
      this->nup_closing->Name = L"nup_closing";
      this->nup_closing->Size = System::Drawing::Size(57, 20);
      this->nup_closing->TabIndex = 53;
      // 
      // nup_opening
      // 
      this->nup_opening->Location = System::Drawing::Point(128, 384);
      this->nup_opening->Name = L"nup_opening";
      this->nup_opening->Size = System::Drawing::Size(57, 20);
      this->nup_opening->TabIndex = 52;
      // 
      // nup_dilation
      // 
      this->nup_dilation->Location = System::Drawing::Point(510, 268);
      this->nup_dilation->Name = L"nup_dilation";
      this->nup_dilation->Size = System::Drawing::Size(57, 20);
      this->nup_dilation->TabIndex = 51;
      // 
      // nup_erode
      // 
      this->nup_erode->Location = System::Drawing::Point(510, 224);
      this->nup_erode->Name = L"nup_erode";
      this->nup_erode->Size = System::Drawing::Size(57, 20);
      this->nup_erode->TabIndex = 50;
      // 
      // lbl_bilateral
      // 
      this->lbl_bilateral->AutoSize = true;
      this->lbl_bilateral->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_bilateral->Location = System::Drawing::Point(6, 566);
      this->lbl_bilateral->Name = L"lbl_bilateral";
      this->lbl_bilateral->Size = System::Drawing::Size(60, 18);
      this->lbl_bilateral->TabIndex = 48;
      this->lbl_bilateral->Text = L"Bilateral";
      // 
      // label14
      // 
      this->label14->AutoSize = true;
      this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label14->Location = System::Drawing::Point(6, 519);
      this->label14->Name = L"label14";
      this->label14->Size = System::Drawing::Size(71, 18);
      this->label14->TabIndex = 40;
      this->label14->Text = L"Gaussian";
      // 
      // label12
      // 
      this->label12->AutoSize = true;
      this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label12->Location = System::Drawing::Point(6, 430);
      this->label12->Name = L"label12";
      this->label12->Size = System::Drawing::Size(58, 18);
      this->label12->TabIndex = 36;
      this->label12->Text = L"Closing";
      // 
      // label13
      // 
      this->label13->AutoSize = true;
      this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label13->Location = System::Drawing::Point(6, 386);
      this->label13->Name = L"label13";
      this->label13->Size = System::Drawing::Size(63, 18);
      this->label13->TabIndex = 34;
      this->label13->Text = L"Opening";
      // 
      // label11
      // 
      this->label11->AutoSize = true;
      this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label11->Location = System::Drawing::Point(6, 270);
      this->label11->Name = L"label11";
      this->label11->Size = System::Drawing::Size(57, 18);
      this->label11->TabIndex = 32;
      this->label11->Text = L"Dilation";
      // 
      // hsb_dilation
      // 
      this->hsb_dilation->Location = System::Drawing::Point(118, 268);
      this->hsb_dilation->Name = L"hsb_dilation";
      this->hsb_dilation->Size = System::Drawing::Size(354, 20);
      this->hsb_dilation->TabIndex = 31;
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label10->Location = System::Drawing::Point(6, 226);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(48, 18);
      this->label10->TabIndex = 30;
      this->label10->Text = L"Erode";
      // 
      // hsb_erode
      // 
      this->hsb_erode->Location = System::Drawing::Point(118, 224);
      this->hsb_erode->Name = L"hsb_erode";
      this->hsb_erode->Size = System::Drawing::Size(354, 20);
      this->hsb_erode->TabIndex = 29;
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label7->Location = System::Drawing::Point(83, 164);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(36, 18);
      this->label7->TabIndex = 28;
      this->label7->Text = L"max";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label8->Location = System::Drawing::Point(83, 142);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(32, 18);
      this->label8->TabIndex = 27;
      this->label8->Text = L"min";
      // 
      // hsb_value_max
      // 
      this->hsb_value_max->Location = System::Drawing::Point(118, 162);
      this->hsb_value_max->Name = L"hsb_value_max";
      this->hsb_value_max->Size = System::Drawing::Size(354, 20);
      this->hsb_value_max->TabIndex = 26;
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label9->Location = System::Drawing::Point(6, 142);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(44, 18);
      this->label9->TabIndex = 25;
      this->label9->Text = L"Value";
      // 
      // hsb_value_min
      // 
      this->hsb_value_min->Location = System::Drawing::Point(118, 142);
      this->hsb_value_min->Name = L"hsb_value_min";
      this->hsb_value_min->Size = System::Drawing::Size(354, 20);
      this->hsb_value_min->TabIndex = 24;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(83, 100);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(36, 18);
      this->label2->TabIndex = 23;
      this->label2->Text = L"max";
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label5->Location = System::Drawing::Point(83, 78);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(32, 18);
      this->label5->TabIndex = 22;
      this->label5->Text = L"min";
      // 
      // hsb_saturation_max
      // 
      this->hsb_saturation_max->Location = System::Drawing::Point(118, 98);
      this->hsb_saturation_max->Name = L"hsb_saturation_max";
      this->hsb_saturation_max->Size = System::Drawing::Size(354, 20);
      this->hsb_saturation_max->TabIndex = 21;
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label6->Location = System::Drawing::Point(6, 80);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(75, 18);
      this->label6->TabIndex = 20;
      this->label6->Text = L"Saturation";
      // 
      // hsb_saturation_min
      // 
      this->hsb_saturation_min->Location = System::Drawing::Point(118, 78);
      this->hsb_saturation_min->Name = L"hsb_saturation_min";
      this->hsb_saturation_min->Size = System::Drawing::Size(354, 20);
      this->hsb_saturation_min->TabIndex = 19;
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label4->Location = System::Drawing::Point(83, 39);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(36, 18);
      this->label4->TabIndex = 18;
      this->label4->Text = L"max";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(83, 17);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(32, 18);
      this->label3->TabIndex = 17;
      this->label3->Text = L"min";
      // 
      // hsb_hue_max
      // 
      this->hsb_hue_max->Location = System::Drawing::Point(118, 37);
      this->hsb_hue_max->Name = L"hsb_hue_max";
      this->hsb_hue_max->Size = System::Drawing::Size(354, 20);
      this->hsb_hue_max->TabIndex = 16;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(6, 16);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(35, 18);
      this->label1->TabIndex = 11;
      this->label1->Text = L"Hue";
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1310, 620);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 12;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_exit_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1310, 699);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 11;
      // 
      // nup_Cam_ID
      // 
      this->nup_Cam_ID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                static_cast<System::Byte>(0)));
      this->nup_Cam_ID->Location = System::Drawing::Point(1310, 238);
      this->nup_Cam_ID->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        6, 0, 0, 0
        });
      this->nup_Cam_ID->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->nup_Cam_ID->Name = L"nup_Cam_ID";
      this->nup_Cam_ID->Size = System::Drawing::Size(78, 38);
      this->nup_Cam_ID->TabIndex = 13;
      this->nup_Cam_ID->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->nup_Cam_ID->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::nup_Cam_ID_ValueChanged);
      // 
      // bt_Start
      // 
      this->bt_Start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->bt_Start->Location = System::Drawing::Point(1310, 282);
      this->bt_Start->Name = L"bt_Start";
      this->bt_Start->Size = System::Drawing::Size(167, 73);
      this->bt_Start->TabIndex = 14;
      this->bt_Start->Text = L"Start";
      this->bt_Start->UseVisualStyleBackColor = true;
      this->bt_Start->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_Start_Click);
      // 
      // bt_Stop
      // 
      this->bt_Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_Stop->Location = System::Drawing::Point(1309, 361);
      this->bt_Stop->Name = L"bt_Stop";
      this->bt_Stop->Size = System::Drawing::Size(167, 73);
      this->bt_Stop->TabIndex = 15;
      this->bt_Stop->Text = L"Stop";
      this->bt_Stop->UseVisualStyleBackColor = true;
      this->bt_Stop->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_Stop_Click);
      // 
      // label17
      // 
      this->label17->AutoSize = true;
      this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label17->Location = System::Drawing::Point(1309, 217);
      this->label17->Name = L"label17";
      this->label17->Size = System::Drawing::Size(79, 18);
      this->label17->TabIndex = 59;
      this->label17->Text = L"Camera ID";
      // 
      // C_frm_ObjectCalibration
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1489, 732);
      this->Controls->Add(this->label17);
      this->Controls->Add(this->bt_Stop);
      this->Controls->Add(this->bt_Start);
      this->Controls->Add(this->nup_Cam_ID);
      this->Controls->Add(this->bt_exit);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->gb_farbfilter);
      this->Controls->Add(this->lbl_tracked_obj);
      this->Controls->Add(this->pictureBox5);
      this->Controls->Add(this->pictureBox6);
      this->Controls->Add(this->lbl_hsv_filter);
      this->Controls->Add(this->pictureBox3);
      this->Controls->Add(this->pictureBox4);
      this->Controls->Add(this->lbl_org_pic);
      this->Controls->Add(this->pictureBox2);
      this->Controls->Add(this->pictureBox1);
      this->Name = L"C_frm_ObjectCalibration";
      this->Text = L"frm_UM_Object_Calibration";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
      this->gb_farbfilter->ResumeLayout(false);
      this->gb_farbfilter->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_gaussian_sigma))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_bilateral))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_gaussian))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_closing))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_opening))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_dilation))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_erode))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_Cam_ID))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
       private:
    System::Void		bt_exit_Click						  (System::Object^  sender, System::EventArgs^ e);
    System::Void		Taktgeber_Tick						(System::Object^  sender, System::EventArgs^ e);
    System::Void    bt_Start_Click            (System::Object^  sender, System::EventArgs^ e);
    System::Void    bt_Stop_Click             (System::Object^  sender, System::EventArgs^ e);
    System::Void    nup_Cam_ID_ValueChanged   (System::Object^  sender, System::EventArgs^ e);
};
  }//namespace NmSp_frm_ObjectCalibration
