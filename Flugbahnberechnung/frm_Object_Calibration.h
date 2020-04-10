#pragma once
#include "Main.h"
#include <opencv2/core/mat.hpp>

using namespace nmsp_Main;

namespace NmSp_frm_ObjectCalibration 
  {
  using namespace nmsp_GlobalObjects;
  public ref class C_frm_ObjectCalibration : public System::Windows::Forms::Form
	  {
	  public:
    C_frm_ObjectCalibration               (C_GlobalObjects* GlobalObjects, C_Main^  Main);
 	  protected:
    ~C_frm_ObjectCalibration              ();

	  private:
    C_GlobalObjects*    GlobalObjects;
    C_Main^             Main;

    UInt32              Zaehler;
    UInt32              camera_id_in_use;
    UInt32              Taktgeber_Intervall;
    UInt32              TimerWait;




    int                                     hue_min;
    int                                     hue_max;
    int                                     saturation_min;
    int                                     saturation_max;
    int                                     value_min;
    int                                     value_max;
    int                                     target_size_width;     //Resizing the image to the wanted width Values
    int                                     target_size_height;     //Resizing the image to the wanted height Values


    int                                     erosion_iterations;
    int                                     dilation_iterations;
    int                                     opening_iterations;
    int                                     closing_iterations;

    int                                     erosion_kernel_size;
    int                                     dilation_kernel_size;
    int                                     bilateral_kernel_size;
    int                                     opening_kernel_size;
    int                                     closing_kernel_size;
    int                                     morph_kernel_size;
    int                                     gaussian_kernel_size;

    int                                     ksize;

    int                                     bordertype;

    int                                     numBoards;
    int                                     numCornersHor;
    int                                     numcornersVer;

    int                                     prior_selection;

    double                                  gaussian_sigma;


    float                                   bilateral_sigma_color;
    float                                   bilateral_sigma_space;

    bool  erode_active;
    bool  dilate_active;
    bool  open_active;
    bool  close_active;
    bool  bilateral_active;
    bool  morph_active;



      private: System::Windows::Forms::PictureBox^  pb_original;



      protected:

      private: System::Windows::Forms::Label^  lbl_org_pic;
      private: System::Windows::Forms::Label^  lbl_gray;

      private: System::Windows::Forms::PictureBox^  pb_filtered;
      private: System::Windows::Forms::Label^  lbl_filtered;





      private: System::Windows::Forms::PictureBox^  pb_tracked;






      private: System::Windows::Forms::GroupBox^  gb_farbfilter;


      private: System::Windows::Forms::Label^  label1;
      private: System::Windows::Forms::Label^  label7;
      private: System::Windows::Forms::Label^  label8;


      private: System::Windows::Forms::Label^  label9;


      private: System::Windows::Forms::Label^  label2;
      private: System::Windows::Forms::Label^  label5;


      private: System::Windows::Forms::Label^  label6;


      private: System::Windows::Forms::Label^  label4;
      private: System::Windows::Forms::Label^  label3;


      private: System::Windows::Forms::Button^  bt_exit;
      private: System::Windows::Forms::TextBox^  txtb_counter;
      private: System::Windows::Forms::Timer^  Taktgeber;

      private: System::Windows::Forms::Label^  label10;

      private: System::Windows::Forms::Label^  label11;

      private: System::Windows::Forms::Label^  lbl_bilateral;
      private: System::Windows::Forms::Label^  label14;



      private: System::Windows::Forms::Label^  label12;

      private: System::Windows::Forms::Label^  label13;
  private: System::Windows::Forms::NumericUpDown^  numUD_closing_kernelsize;


  private: System::Windows::Forms::NumericUpDown^  numUD_closing_iterations;
  private: System::Windows::Forms::NumericUpDown^  numUD_opening_kernelsize;




  private: System::Windows::Forms::NumericUpDown^  numUD_opening_iterations;

  private: System::Windows::Forms::NumericUpDown^  numUD_erode_iterations;
  private: System::Windows::Forms::NumericUpDown^  numUD_erode_kernelsize;


  private: System::Windows::Forms::Label^  lbl_kernel_size;
  private: System::Windows::Forms::NumericUpDown^  numUD_dilation_iterations;
  private: System::Windows::Forms::NumericUpDown^  numUD_cam_id;






      private: System::Windows::Forms::Label^  label17;
  private: System::Windows::Forms::TrackBar^  trb_hue_min;
  private: System::Windows::Forms::TrackBar^  trb_hue_max;
  private: System::Windows::Forms::TextBox^  txb_hue_min;







  private: System::Windows::Forms::TextBox^  txb_hue_max;





    private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::TrackBar^  trb_value_min;
  private: System::Windows::Forms::TrackBar^  trb_value_max;
  private: System::Windows::Forms::TextBox^  txb_value_max;
  private: System::Windows::Forms::TextBox^  txb_value_min;




  private: System::Windows::Forms::TrackBar^  trb_saturation_min;
  private: System::Windows::Forms::TrackBar^  trb_saturation_max;
  private: System::Windows::Forms::TextBox^  txb_saturation_max;
  private: System::Windows::Forms::TextBox^  txb_saturation_min;
  private: System::Windows::Forms::Label^  lbl_iterations;
  private: System::Windows::Forms::NumericUpDown^  numUD_dilation_kernelsize;
  private: System::Windows::Forms::NumericUpDown^  numUD_morph_kernelsize;

  private: System::Windows::Forms::NumericUpDown^  numUD_bilateral_kernelsize;
  private: System::Windows::Forms::NumericUpDown^  numUD_gaussian_kernel_size;


  private: System::Windows::Forms::NumericUpDown^  numUD_morph_iterations;
  private: System::Windows::Forms::NumericUpDown^  numUD_bilateral_spatial;






    private: System::Windows::Forms::Label^  label15;
  private: System::Windows::Forms::CheckBox^  chkb_morph;
    private: System::Windows::Forms::CheckBox^  chkb_bilateral;


    private: System::Windows::Forms::CheckBox^  chkb_dilate;

  private: System::Windows::Forms::Label^  label16;
  private: System::Windows::Forms::PictureBox^  pb_gray;
  private: System::Windows::Forms::CheckBox^  chkb_erode;
  private: System::Windows::Forms::Label^  label19;

  private: System::Windows::Forms::NumericUpDown^  numUD_gaussian_sigma;
  private: System::Windows::Forms::NumericUpDown^  numUD_bilateral_color;
    private: System::Windows::Forms::Label^  label22;
    private: System::Windows::Forms::Label^  label21;
  private: System::Windows::Forms::Button^  bt_apply;
  private: System::Windows::Forms::Button^  bt_apply_all;










          private: System::ComponentModel::IContainer^  components;

  

    #pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->pb_original = (gcnew System::Windows::Forms::PictureBox());
      this->lbl_org_pic = (gcnew System::Windows::Forms::Label());
      this->lbl_gray = (gcnew System::Windows::Forms::Label());
      this->pb_filtered = (gcnew System::Windows::Forms::PictureBox());
      this->lbl_filtered = (gcnew System::Windows::Forms::Label());
      this->pb_tracked = (gcnew System::Windows::Forms::PictureBox());
      this->gb_farbfilter = (gcnew System::Windows::Forms::GroupBox());
      this->numUD_bilateral_color = (gcnew System::Windows::Forms::NumericUpDown());
      this->label22 = (gcnew System::Windows::Forms::Label());
      this->label21 = (gcnew System::Windows::Forms::Label());
      this->numUD_gaussian_sigma = (gcnew System::Windows::Forms::NumericUpDown());
      this->label19 = (gcnew System::Windows::Forms::Label());
      this->chkb_morph = (gcnew System::Windows::Forms::CheckBox());
      this->chkb_dilate = (gcnew System::Windows::Forms::CheckBox());
      this->chkb_erode = (gcnew System::Windows::Forms::CheckBox());
      this->chkb_bilateral = (gcnew System::Windows::Forms::CheckBox());
      this->numUD_gaussian_kernel_size = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_dilation_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->lbl_iterations = (gcnew System::Windows::Forms::Label());
      this->numUD_morph_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->lbl_kernel_size = (gcnew System::Windows::Forms::Label());
      this->numUD_dilation_iterations = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_bilateral_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_morph_iterations = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_erode_iterations = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_bilateral_spatial = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_erode_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->numUD_closing_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->label15 = (gcnew System::Windows::Forms::Label());
      this->label11 = (gcnew System::Windows::Forms::Label());
      this->numUD_closing_iterations = (gcnew System::Windows::Forms::NumericUpDown());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->lbl_bilateral = (gcnew System::Windows::Forms::Label());
      this->numUD_opening_kernelsize = (gcnew System::Windows::Forms::NumericUpDown());
      this->label13 = (gcnew System::Windows::Forms::Label());
      this->label14 = (gcnew System::Windows::Forms::Label());
      this->label12 = (gcnew System::Windows::Forms::Label());
      this->numUD_opening_iterations = (gcnew System::Windows::Forms::NumericUpDown());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->numUD_cam_id = (gcnew System::Windows::Forms::NumericUpDown());
      this->label17 = (gcnew System::Windows::Forms::Label());
      this->trb_hue_min = (gcnew System::Windows::Forms::TrackBar());
      this->trb_hue_max = (gcnew System::Windows::Forms::TrackBar());
      this->txb_hue_min = (gcnew System::Windows::Forms::TextBox());
      this->txb_hue_max = (gcnew System::Windows::Forms::TextBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->trb_value_min = (gcnew System::Windows::Forms::TrackBar());
      this->trb_value_max = (gcnew System::Windows::Forms::TrackBar());
      this->txb_value_max = (gcnew System::Windows::Forms::TextBox());
      this->txb_value_min = (gcnew System::Windows::Forms::TextBox());
      this->trb_saturation_min = (gcnew System::Windows::Forms::TrackBar());
      this->trb_saturation_max = (gcnew System::Windows::Forms::TrackBar());
      this->txb_saturation_max = (gcnew System::Windows::Forms::TextBox());
      this->txb_saturation_min = (gcnew System::Windows::Forms::TextBox());
      this->label16 = (gcnew System::Windows::Forms::Label());
      this->pb_gray = (gcnew System::Windows::Forms::PictureBox());
      this->bt_apply = (gcnew System::Windows::Forms::Button());
      this->bt_apply_all = (gcnew System::Windows::Forms::Button());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_original))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_filtered))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_tracked))->BeginInit();
      this->gb_farbfilter->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_color))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_gaussian_sigma))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_gaussian_kernel_size))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_dilation_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_morph_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_dilation_iterations))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_morph_iterations))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_erode_iterations))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_spatial))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_erode_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_closing_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_closing_iterations))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_opening_kernelsize))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_opening_iterations))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_cam_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_hue_min))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_hue_max))->BeginInit();
      this->groupBox1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_value_min))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_value_max))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_saturation_min))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_saturation_max))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_gray))->BeginInit();
      this->SuspendLayout();
      // 
      // pb_original
      // 
      this->pb_original->Location = System::Drawing::Point(20, 37);
      this->pb_original->Margin = System::Windows::Forms::Padding(4);
      this->pb_original->Name = L"pb_original";
      this->pb_original->Size = System::Drawing::Size(512, 354);
      this->pb_original->TabIndex = 0;
      this->pb_original->TabStop = false;
      // 
      // lbl_org_pic
      // 
      this->lbl_org_pic->AutoSize = true;
      this->lbl_org_pic->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                 static_cast<System::Byte>(0)));
      this->lbl_org_pic->Location = System::Drawing::Point(16, 11);
      this->lbl_org_pic->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_org_pic->Name = L"lbl_org_pic";
      this->lbl_org_pic->Size = System::Drawing::Size(105, 24);
      this->lbl_org_pic->TabIndex = 2;
      this->lbl_org_pic->Text = L"Originalbild";
      // 
      // lbl_gray
      // 
      this->lbl_gray->AutoSize = true;
      this->lbl_gray->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                              static_cast<System::Byte>(0)));
      this->lbl_gray->Location = System::Drawing::Point(536, 11);
      this->lbl_gray->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_gray->Name = L"lbl_gray";
      this->lbl_gray->Size = System::Drawing::Size(49, 24);
      this->lbl_gray->TabIndex = 5;
      this->lbl_gray->Text = L"Gray";
      // 
      // pb_filtered
      // 
      this->pb_filtered->Location = System::Drawing::Point(1060, 37);
      this->pb_filtered->Margin = System::Windows::Forms::Padding(4);
      this->pb_filtered->Name = L"pb_filtered";
      this->pb_filtered->Size = System::Drawing::Size(512, 354);
      this->pb_filtered->TabIndex = 3;
      this->pb_filtered->TabStop = false;
      // 
      // lbl_filtered
      // 
      this->lbl_filtered->AutoSize = true;
      this->lbl_filtered->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                  static_cast<System::Byte>(0)));
      this->lbl_filtered->Location = System::Drawing::Point(1056, 11);
      this->lbl_filtered->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_filtered->Name = L"lbl_filtered";
      this->lbl_filtered->Size = System::Drawing::Size(130, 24);
      this->lbl_filtered->TabIndex = 8;
      this->lbl_filtered->Text = L"GPU_InRange";
      // 
      // pb_tracked
      // 
      this->pb_tracked->Location = System::Drawing::Point(1580, 37);
      this->pb_tracked->Margin = System::Windows::Forms::Padding(4);
      this->pb_tracked->Name = L"pb_tracked";
      this->pb_tracked->Size = System::Drawing::Size(512, 354);
      this->pb_tracked->TabIndex = 6;
      this->pb_tracked->TabStop = false;
      // 
      // gb_farbfilter
      // 
      this->gb_farbfilter->Controls->Add(this->numUD_bilateral_color);
      this->gb_farbfilter->Controls->Add(this->label22);
      this->gb_farbfilter->Controls->Add(this->label21);
      this->gb_farbfilter->Controls->Add(this->numUD_gaussian_sigma);
      this->gb_farbfilter->Controls->Add(this->label19);
      this->gb_farbfilter->Controls->Add(this->chkb_morph);
      this->gb_farbfilter->Controls->Add(this->chkb_dilate);
      this->gb_farbfilter->Controls->Add(this->chkb_erode);
      this->gb_farbfilter->Controls->Add(this->chkb_bilateral);
      this->gb_farbfilter->Controls->Add(this->numUD_gaussian_kernel_size);
      this->gb_farbfilter->Controls->Add(this->numUD_dilation_kernelsize);
      this->gb_farbfilter->Controls->Add(this->lbl_iterations);
      this->gb_farbfilter->Controls->Add(this->numUD_morph_kernelsize);
      this->gb_farbfilter->Controls->Add(this->lbl_kernel_size);
      this->gb_farbfilter->Controls->Add(this->numUD_dilation_iterations);
      this->gb_farbfilter->Controls->Add(this->numUD_bilateral_kernelsize);
      this->gb_farbfilter->Controls->Add(this->numUD_morph_iterations);
      this->gb_farbfilter->Controls->Add(this->numUD_erode_iterations);
      this->gb_farbfilter->Controls->Add(this->numUD_bilateral_spatial);
      this->gb_farbfilter->Controls->Add(this->numUD_erode_kernelsize);
      this->gb_farbfilter->Controls->Add(this->numUD_closing_kernelsize);
      this->gb_farbfilter->Controls->Add(this->label15);
      this->gb_farbfilter->Controls->Add(this->label11);
      this->gb_farbfilter->Controls->Add(this->numUD_closing_iterations);
      this->gb_farbfilter->Controls->Add(this->label10);
      this->gb_farbfilter->Controls->Add(this->lbl_bilateral);
      this->gb_farbfilter->Controls->Add(this->numUD_opening_kernelsize);
      this->gb_farbfilter->Controls->Add(this->label13);
      this->gb_farbfilter->Controls->Add(this->label14);
      this->gb_farbfilter->Controls->Add(this->label12);
      this->gb_farbfilter->Controls->Add(this->numUD_opening_iterations);
      this->gb_farbfilter->Location = System::Drawing::Point(16, 399);
      this->gb_farbfilter->Margin = System::Windows::Forms::Padding(4);
      this->gb_farbfilter->Name = L"gb_farbfilter";
      this->gb_farbfilter->Padding = System::Windows::Forms::Padding(4);
      this->gb_farbfilter->Size = System::Drawing::Size(507, 610);
      this->gb_farbfilter->TabIndex = 10;
      this->gb_farbfilter->TabStop = false;
      this->gb_farbfilter->Text = L"Filtering";
      // 
      // numUD_bilateral_color
      // 
      this->numUD_bilateral_color->DecimalPlaces = 2;
      this->numUD_bilateral_color->Enabled = false;
      this->numUD_bilateral_color->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        2, 0, 0, 131072
        });
      this->numUD_bilateral_color->Location = System::Drawing::Point(197, 349);
      this->numUD_bilateral_color->Margin = System::Windows::Forms::Padding(4);
      this->numUD_bilateral_color->Name = L"numUD_bilateral_color";
      this->numUD_bilateral_color->Size = System::Drawing::Size(76, 22);
      this->numUD_bilateral_color->TabIndex = 82;
      this->numUD_bilateral_color->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        2, 0, 0, 131072
        });
      this->numUD_bilateral_color->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_bilateral_color_ValueChanged);
      // 
      // label22
      // 
      this->label22->AutoSize = true;
      this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label22->Location = System::Drawing::Point(193, 321);
      this->label22->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label22->Name = L"label22";
      this->label22->Size = System::Drawing::Size(55, 24);
      this->label22->TabIndex = 81;
      this->label22->Text = L"Color";
      // 
      // label21
      // 
      this->label21->AutoSize = true;
      this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label21->Location = System::Drawing::Point(277, 321);
      this->label21->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label21->Name = L"label21";
      this->label21->Size = System::Drawing::Size(65, 24);
      this->label21->TabIndex = 80;
      this->label21->Text = L"Spatial";
      // 
      // numUD_gaussian_sigma
      // 
      this->numUD_gaussian_sigma->DecimalPlaces = 1;
      this->numUD_gaussian_sigma->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 65536
        });
      this->numUD_gaussian_sigma->Location = System::Drawing::Point(221, 278);
      this->numUD_gaussian_sigma->Margin = System::Windows::Forms::Padding(4);
      this->numUD_gaussian_sigma->Name = L"numUD_gaussian_sigma";
      this->numUD_gaussian_sigma->Size = System::Drawing::Size(76, 22);
      this->numUD_gaussian_sigma->TabIndex = 78;
      this->numUD_gaussian_sigma->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 65536
        });
// 
// label19
// 
      this->label19->AutoSize = true;
      this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label19->Location = System::Drawing::Point(217, 252);
      this->label19->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label19->Name = L"label19";
      this->label19->Size = System::Drawing::Size(63, 24);
      this->label19->TabIndex = 77;
      this->label19->Text = L"Sigma";
      // 
      // chkb_morph
      // 
      this->chkb_morph->AutoSize = true;
      this->chkb_morph->Location = System::Drawing::Point(21, 226);
      this->chkb_morph->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->chkb_morph->Name = L"chkb_morph";
      this->chkb_morph->Size = System::Drawing::Size(18, 17);
      this->chkb_morph->TabIndex = 75;
      this->chkb_morph->UseVisualStyleBackColor = true;
      this->chkb_morph->CheckStateChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::chkb_morph_CheckStateChanged);
      // 
      // chkb_dilate
      // 
      this->chkb_dilate->AutoSize = true;
      this->chkb_dilate->Location = System::Drawing::Point(21, 191);
      this->chkb_dilate->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->chkb_dilate->Name = L"chkb_dilate";
      this->chkb_dilate->Size = System::Drawing::Size(18, 17);
      this->chkb_dilate->TabIndex = 71;
      this->chkb_dilate->UseVisualStyleBackColor = true;
      this->chkb_dilate->CheckStateChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::chkb_dilate_CheckStateChanged);
      // 
      // chkb_erode
      // 
      this->chkb_erode->AutoSize = true;
      this->chkb_erode->Location = System::Drawing::Point(21, 162);
      this->chkb_erode->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->chkb_erode->Name = L"chkb_erode";
      this->chkb_erode->Size = System::Drawing::Size(18, 17);
      this->chkb_erode->TabIndex = 70;
      this->chkb_erode->UseVisualStyleBackColor = true;
      this->chkb_erode->CheckStateChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::chkb_erode_CheckStateChanged);
      // 
      // chkb_bilateral
      // 
      this->chkb_bilateral->AutoSize = true;
      this->chkb_bilateral->Location = System::Drawing::Point(29, 349);
      this->chkb_bilateral->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->chkb_bilateral->Name = L"chkb_bilateral";
      this->chkb_bilateral->Size = System::Drawing::Size(18, 17);
      this->chkb_bilateral->TabIndex = 74;
      this->chkb_bilateral->UseVisualStyleBackColor = true;
      this->chkb_bilateral->CheckStateChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::chkb_bilateral_CheckStateChanged);
      // 
      // numUD_gaussian_kernel_size
      // 
      this->numUD_gaussian_kernel_size->Location = System::Drawing::Point(367, 281);
      this->numUD_gaussian_kernel_size->Margin = System::Windows::Forms::Padding(4);
      this->numUD_gaussian_kernel_size->Name = L"numUD_gaussian_kernel_size";
      this->numUD_gaussian_kernel_size->Size = System::Drawing::Size(76, 22);
      this->numUD_gaussian_kernel_size->TabIndex = 67;
      this->numUD_gaussian_kernel_size->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_gaussian_kernel_size_ValueChanged);
      // 
      // numUD_dilation_kernelsize
      // 
      this->numUD_dilation_kernelsize->Enabled = false;
      this->numUD_dilation_kernelsize->Location = System::Drawing::Point(365, 191);
      this->numUD_dilation_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_dilation_kernelsize->Name = L"numUD_dilation_kernelsize";
      this->numUD_dilation_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_dilation_kernelsize->TabIndex = 61;
      this->numUD_dilation_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_dilation_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_dilation_kernelsize_ValueChanged);
      // 
      // lbl_iterations
      // 
      this->lbl_iterations->AutoSize = true;
      this->lbl_iterations->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                    static_cast<System::Byte>(0)));
      this->lbl_iterations->Location = System::Drawing::Point(217, 34);
      this->lbl_iterations->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_iterations->Name = L"lbl_iterations";
      this->lbl_iterations->Size = System::Drawing::Size(84, 24);
      this->lbl_iterations->TabIndex = 60;
      this->lbl_iterations->Text = L"Iterations";
      // 
      // numUD_morph_kernelsize
      // 
      this->numUD_morph_kernelsize->Enabled = false;
      this->numUD_morph_kernelsize->Location = System::Drawing::Point(365, 222);
      this->numUD_morph_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_morph_kernelsize->Name = L"numUD_morph_kernelsize";
      this->numUD_morph_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_morph_kernelsize->TabIndex = 69;
      this->numUD_morph_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_morph_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_morph_kernelsize_ValueChanged);
      // 
      // lbl_kernel_size
      // 
      this->lbl_kernel_size->AutoSize = true;
      this->lbl_kernel_size->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
                                     System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->lbl_kernel_size->Location = System::Drawing::Point(363, 34);
      this->lbl_kernel_size->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_kernel_size->Name = L"lbl_kernel_size";
      this->lbl_kernel_size->Size = System::Drawing::Size(106, 24);
      this->lbl_kernel_size->TabIndex = 58;
      this->lbl_kernel_size->Text = L"Kernel Size";
      // 
      // numUD_dilation_iterations
      // 
      this->numUD_dilation_iterations->Enabled = false;
      this->numUD_dilation_iterations->Location = System::Drawing::Point(219, 191);
      this->numUD_dilation_iterations->Margin = System::Windows::Forms::Padding(4);
      this->numUD_dilation_iterations->Name = L"numUD_dilation_iterations";
      this->numUD_dilation_iterations->Size = System::Drawing::Size(76, 22);
      this->numUD_dilation_iterations->TabIndex = 57;
      this->numUD_dilation_iterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_dilation_iterations->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_dilation_iterations_ValueChanged);
      // 
      // numUD_bilateral_kernelsize
      // 
      this->numUD_bilateral_kernelsize->Enabled = false;
      this->numUD_bilateral_kernelsize->Location = System::Drawing::Point(367, 349);
      this->numUD_bilateral_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_bilateral_kernelsize->Name = L"numUD_bilateral_kernelsize";
      this->numUD_bilateral_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_bilateral_kernelsize->TabIndex = 68;
      this->numUD_bilateral_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_bilateral_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_bilateral_kernelsize_ValueChanged);
      // 
      // numUD_morph_iterations
      // 
      this->numUD_morph_iterations->Enabled = false;
      this->numUD_morph_iterations->Location = System::Drawing::Point(219, 222);
      this->numUD_morph_iterations->Margin = System::Windows::Forms::Padding(4);
      this->numUD_morph_iterations->Name = L"numUD_morph_iterations";
      this->numUD_morph_iterations->Size = System::Drawing::Size(76, 22);
      this->numUD_morph_iterations->TabIndex = 66;
      this->numUD_morph_iterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_morph_iterations->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_morph_iterations_ValueChanged);
      // 
      // numUD_erode_iterations
      // 
      this->numUD_erode_iterations->Enabled = false;
      this->numUD_erode_iterations->Location = System::Drawing::Point(219, 156);
      this->numUD_erode_iterations->Margin = System::Windows::Forms::Padding(4);
      this->numUD_erode_iterations->Name = L"numUD_erode_iterations";
      this->numUD_erode_iterations->Size = System::Drawing::Size(76, 22);
      this->numUD_erode_iterations->TabIndex = 51;
      this->numUD_erode_iterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_erode_iterations->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_erode_iterations_ValueChanged);
      // 
      // numUD_bilateral_spatial
      // 
      this->numUD_bilateral_spatial->DecimalPlaces = 2;
      this->numUD_bilateral_spatial->Enabled = false;
      this->numUD_bilateral_spatial->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        2, 0, 0, 131072
        });
      this->numUD_bilateral_spatial->Location = System::Drawing::Point(281, 349);
      this->numUD_bilateral_spatial->Margin = System::Windows::Forms::Padding(4);
      this->numUD_bilateral_spatial->Name = L"numUD_bilateral_spatial";
      this->numUD_bilateral_spatial->Size = System::Drawing::Size(76, 22);
      this->numUD_bilateral_spatial->TabIndex = 65;
      this->numUD_bilateral_spatial->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        2, 0, 0, 131072
        });
      this->numUD_bilateral_spatial->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_bilateral_spatial_ValueChanged);
      // 
      // numUD_erode_kernelsize
      // 
      this->numUD_erode_kernelsize->Enabled = false;
      this->numUD_erode_kernelsize->Location = System::Drawing::Point(365, 156);
      this->numUD_erode_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_erode_kernelsize->Name = L"numUD_erode_kernelsize";
      this->numUD_erode_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_erode_kernelsize->TabIndex = 50;
      this->numUD_erode_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_erode_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_erode_kernelsize_ValueChanged);
      // 
      // numUD_closing_kernelsize
      // 
      this->numUD_closing_kernelsize->Location = System::Drawing::Point(365, 112);
      this->numUD_closing_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_closing_kernelsize->Name = L"numUD_closing_kernelsize";
      this->numUD_closing_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_closing_kernelsize->TabIndex = 56;
      this->numUD_closing_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_closing_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_closing_kernelsize_ValueChanged);
      // 
      // label15
      // 
      this->label15->AutoSize = true;
      this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label15->Location = System::Drawing::Point(45, 222);
      this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label15->Name = L"label15";
      this->label15->Size = System::Drawing::Size(70, 24);
      this->label15->TabIndex = 63;
      this->label15->Text = L"Morph ";
      // 
      // label11
      // 
      this->label11->AutoSize = true;
      this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label11->Location = System::Drawing::Point(45, 187);
      this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label11->Name = L"label11";
      this->label11->Size = System::Drawing::Size(71, 24);
      this->label11->TabIndex = 32;
      this->label11->Text = L"Dilation";
      // 
      // numUD_closing_iterations
      // 
      this->numUD_closing_iterations->Location = System::Drawing::Point(219, 111);
      this->numUD_closing_iterations->Margin = System::Windows::Forms::Padding(4);
      this->numUD_closing_iterations->Name = L"numUD_closing_iterations";
      this->numUD_closing_iterations->Size = System::Drawing::Size(76, 22);
      this->numUD_closing_iterations->TabIndex = 55;
      this->numUD_closing_iterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_closing_iterations->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_closing_iterations_ValueChanged);
      // 
      // label10
      // 
      this->label10->AutoSize = true;
      this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label10->Location = System::Drawing::Point(45, 156);
      this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label10->Name = L"label10";
      this->label10->Size = System::Drawing::Size(62, 24);
      this->label10->TabIndex = 30;
      this->label10->Text = L"Erode";
      // 
      // lbl_bilateral
      // 
      this->lbl_bilateral->AutoSize = true;
      this->lbl_bilateral->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_bilateral->Location = System::Drawing::Point(55, 345);
      this->lbl_bilateral->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->lbl_bilateral->Name = L"lbl_bilateral";
      this->lbl_bilateral->Size = System::Drawing::Size(75, 24);
      this->lbl_bilateral->TabIndex = 48;
      this->lbl_bilateral->Text = L"Bilateral";
      // 
      // numUD_opening_kernelsize
      // 
      this->numUD_opening_kernelsize->Location = System::Drawing::Point(365, 71);
      this->numUD_opening_kernelsize->Margin = System::Windows::Forms::Padding(4);
      this->numUD_opening_kernelsize->Name = L"numUD_opening_kernelsize";
      this->numUD_opening_kernelsize->Size = System::Drawing::Size(76, 22);
      this->numUD_opening_kernelsize->TabIndex = 53;
      this->numUD_opening_kernelsize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_opening_kernelsize->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_opening_kernelsize_ValueChanged);
      // 
      // label13
      // 
      this->label13->AutoSize = true;
      this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label13->Location = System::Drawing::Point(45, 71);
      this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label13->Name = L"label13";
      this->label13->Size = System::Drawing::Size(84, 24);
      this->label13->TabIndex = 34;
      this->label13->Text = L"Opening";
      // 
      // label14
      // 
      this->label14->AutoSize = true;
      this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label14->Location = System::Drawing::Point(48, 281);
      this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label14->Name = L"label14";
      this->label14->Size = System::Drawing::Size(88, 24);
      this->label14->TabIndex = 40;
      this->label14->Text = L"Gaussian";
      // 
      // label12
      // 
      this->label12->AutoSize = true;
      this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label12->Location = System::Drawing::Point(45, 111);
      this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label12->Name = L"label12";
      this->label12->Size = System::Drawing::Size(73, 24);
      this->label12->TabIndex = 36;
      this->label12->Text = L"Closing";
      // 
      // numUD_opening_iterations
      // 
      this->numUD_opening_iterations->Location = System::Drawing::Point(219, 71);
      this->numUD_opening_iterations->Margin = System::Windows::Forms::Padding(4);
      this->numUD_opening_iterations->Name = L"numUD_opening_iterations";
      this->numUD_opening_iterations->Size = System::Drawing::Size(76, 22);
      this->numUD_opening_iterations->TabIndex = 52;
      this->numUD_opening_iterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        1, 0, 0, 0
        });
      this->numUD_opening_iterations->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_opening_iterations_ValueChanged);
      // 
      // label7
      // 
      this->label7->AutoSize = true;
      this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label7->Location = System::Drawing::Point(141, 386);
      this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(46, 24);
      this->label7->TabIndex = 28;
      this->label7->Text = L"max";
      // 
      // label8
      // 
      this->label8->AutoSize = true;
      this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label8->Location = System::Drawing::Point(141, 325);
      this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label8->Name = L"label8";
      this->label8->Size = System::Drawing::Size(41, 24);
      this->label8->TabIndex = 27;
      this->label8->Text = L"min";
      // 
      // label9
      // 
      this->label9->AutoSize = true;
      this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label9->Location = System::Drawing::Point(7, 325);
      this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(59, 24);
      this->label9->TabIndex = 25;
      this->label9->Text = L"Value";
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label2->Location = System::Drawing::Point(141, 242);
      this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(46, 24);
      this->label2->TabIndex = 23;
      this->label2->Text = L"max";
      // 
      // label5
      // 
      this->label5->AutoSize = true;
      this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label5->Location = System::Drawing::Point(141, 187);
      this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(41, 24);
      this->label5->TabIndex = 22;
      this->label5->Text = L"min";
      // 
      // label6
      // 
      this->label6->AutoSize = true;
      this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label6->Location = System::Drawing::Point(7, 185);
      this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(93, 24);
      this->label6->TabIndex = 20;
      this->label6->Text = L"Saturation";
      // 
      // label4
      // 
      this->label4->AutoSize = true;
      this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label4->Location = System::Drawing::Point(141, 102);
      this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(46, 24);
      this->label4->TabIndex = 18;
      this->label4->Text = L"max";
      // 
      // label3
      // 
      this->label3->AutoSize = true;
      this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label3->Location = System::Drawing::Point(141, 39);
      this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(41, 24);
      this->label3->TabIndex = 17;
      this->label3->Text = L"min";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(7, 37);
      this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(46, 24);
      this->label1->TabIndex = 11;
      this->label1->Text = L"Hue";
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(2099, 913);
      this->bt_exit->Margin = System::Windows::Forms::Padding(4);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(223, 90);
      this->bt_exit->TabIndex = 12;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_exit_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(2099, 1010);
      this->txtb_counter->Margin = System::Windows::Forms::Padding(4);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(220, 22);
      this->txtb_counter->TabIndex = 11;
      // 
      // Taktgeber
      // 
      this->Taktgeber->Interval = 10;
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::Taktgeber_Tick);
      // 
      // numUD_cam_id
      // 
      this->numUD_cam_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                  static_cast<System::Byte>(0)));
      this->numUD_cam_id->Location = System::Drawing::Point(1255, 510);
      this->numUD_cam_id->Margin = System::Windows::Forms::Padding(4);
      this->numUD_cam_id->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4)
        {
        50, 0, 0, 0
        });
      this->numUD_cam_id->Name = L"numUD_cam_id";
      this->numUD_cam_id->Size = System::Drawing::Size(104, 46);
      this->numUD_cam_id->TabIndex = 13;
      this->numUD_cam_id->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::numUD_cam_id_ValueChanged);
      // 
      // label17
      // 
      this->label17->AutoSize = true;
      this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label17->Location = System::Drawing::Point(1251, 469);
      this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label17->Name = L"label17";
      this->label17->Size = System::Drawing::Size(98, 24);
      this->label17->TabIndex = 59;
      this->label17->Text = L"Camera ID";
      // 
      // trb_hue_min
      // 
      this->trb_hue_min->Location = System::Drawing::Point(195, 39);
      this->trb_hue_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_hue_min->Name = L"trb_hue_min";
      this->trb_hue_min->Size = System::Drawing::Size(376, 56);
      this->trb_hue_min->TabIndex = 59;
      this->trb_hue_min->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_hue_min_ValueChanged);
      // 
      // trb_hue_max
      // 
      this->trb_hue_max->Location = System::Drawing::Point(195, 102);
      this->trb_hue_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_hue_max->Name = L"trb_hue_max";
      this->trb_hue_max->Size = System::Drawing::Size(376, 56);
      this->trb_hue_max->TabIndex = 60;
      this->trb_hue_max->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_hue_max_ValueChanged);
      // 
      // txb_hue_min
      // 
      this->txb_hue_min->Location = System::Drawing::Point(577, 39);
      this->txb_hue_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_hue_min->Name = L"txb_hue_min";
      this->txb_hue_min->Size = System::Drawing::Size(111, 22);
      this->txb_hue_min->TabIndex = 66;
      // 
      // txb_hue_max
      // 
      this->txb_hue_max->Location = System::Drawing::Point(577, 102);
      this->txb_hue_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_hue_max->Name = L"txb_hue_max";
      this->txb_hue_max->Size = System::Drawing::Size(111, 22);
      this->txb_hue_max->TabIndex = 67;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->trb_value_min);
      this->groupBox1->Controls->Add(this->trb_value_max);
      this->groupBox1->Controls->Add(this->txb_value_max);
      this->groupBox1->Controls->Add(this->txb_value_min);
      this->groupBox1->Controls->Add(this->trb_saturation_min);
      this->groupBox1->Controls->Add(this->trb_saturation_max);
      this->groupBox1->Controls->Add(this->txb_saturation_max);
      this->groupBox1->Controls->Add(this->txb_saturation_min);
      this->groupBox1->Controls->Add(this->trb_hue_min);
      this->groupBox1->Controls->Add(this->trb_hue_max);
      this->groupBox1->Controls->Add(this->txb_hue_max);
      this->groupBox1->Controls->Add(this->txb_hue_min);
      this->groupBox1->Controls->Add(this->label1);
      this->groupBox1->Controls->Add(this->label3);
      this->groupBox1->Controls->Add(this->label4);
      this->groupBox1->Controls->Add(this->label6);
      this->groupBox1->Controls->Add(this->label7);
      this->groupBox1->Controls->Add(this->label5);
      this->groupBox1->Controls->Add(this->label8);
      this->groupBox1->Controls->Add(this->label2);
      this->groupBox1->Controls->Add(this->label9);
      this->groupBox1->Location = System::Drawing::Point(531, 399);
      this->groupBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->groupBox1->Size = System::Drawing::Size(709, 513);
      this->groupBox1->TabIndex = 13;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"HSV-Filter";
      // 
      // trb_value_min
      // 
      this->trb_value_min->Location = System::Drawing::Point(195, 325);
      this->trb_value_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_value_min->Name = L"trb_value_min";
      this->trb_value_min->Size = System::Drawing::Size(376, 56);
      this->trb_value_min->TabIndex = 72;
      this->trb_value_min->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_value_min_ValueChanged);
      // 
      // trb_value_max
      // 
      this->trb_value_max->Location = System::Drawing::Point(195, 386);
      this->trb_value_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_value_max->Name = L"trb_value_max";
      this->trb_value_max->Size = System::Drawing::Size(376, 56);
      this->trb_value_max->TabIndex = 73;
      this->trb_value_max->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_value_max_ValueChanged);
      // 
      // txb_value_max
      // 
      this->txb_value_max->Location = System::Drawing::Point(577, 386);
      this->txb_value_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_value_max->Name = L"txb_value_max";
      this->txb_value_max->Size = System::Drawing::Size(111, 22);
      this->txb_value_max->TabIndex = 75;
      // 
      // txb_value_min
      // 
      this->txb_value_min->Location = System::Drawing::Point(577, 325);
      this->txb_value_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_value_min->Name = L"txb_value_min";
      this->txb_value_min->Size = System::Drawing::Size(111, 22);
      this->txb_value_min->TabIndex = 74;
      // 
      // trb_saturation_min
      // 
      this->trb_saturation_min->Location = System::Drawing::Point(195, 185);
      this->trb_saturation_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_saturation_min->Name = L"trb_saturation_min";
      this->trb_saturation_min->Size = System::Drawing::Size(376, 56);
      this->trb_saturation_min->TabIndex = 68;
      this->trb_saturation_min->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_saturation_min_ValueChanged);
      // 
      // trb_saturation_max
      // 
      this->trb_saturation_max->Location = System::Drawing::Point(195, 246);
      this->trb_saturation_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->trb_saturation_max->Name = L"trb_saturation_max";
      this->trb_saturation_max->Size = System::Drawing::Size(376, 56);
      this->trb_saturation_max->TabIndex = 69;
      this->trb_saturation_max->ValueChanged += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::trb_saturation_max_ValueChanged);
      // 
      // txb_saturation_max
      // 
      this->txb_saturation_max->Location = System::Drawing::Point(577, 246);
      this->txb_saturation_max->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_saturation_max->Name = L"txb_saturation_max";
      this->txb_saturation_max->Size = System::Drawing::Size(111, 22);
      this->txb_saturation_max->TabIndex = 71;
      // 
      // txb_saturation_min
      // 
      this->txb_saturation_min->Location = System::Drawing::Point(577, 185);
      this->txb_saturation_min->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
      this->txb_saturation_min->Name = L"txb_saturation_min";
      this->txb_saturation_min->Size = System::Drawing::Size(111, 22);
      this->txb_saturation_min->TabIndex = 70;
      // 
      // label16
      // 
      this->label16->AutoSize = true;
      this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->label16->Location = System::Drawing::Point(1576, 11);
      this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
      this->label16->Name = L"label16";
      this->label16->Size = System::Drawing::Size(99, 24);
      this->label16->TabIndex = 61;
      this->label16->Text = L"Contoured";
      // 
      // pb_gray
      // 
      this->pb_gray->Location = System::Drawing::Point(540, 37);
      this->pb_gray->Margin = System::Windows::Forms::Padding(4);
      this->pb_gray->Name = L"pb_gray";
      this->pb_gray->Size = System::Drawing::Size(512, 354);
      this->pb_gray->TabIndex = 60;
      this->pb_gray->TabStop = false;
      // 
      // bt_apply
      // 
      this->bt_apply->Location = System::Drawing::Point(1255, 568);
      this->bt_apply->Margin = System::Windows::Forms::Padding(4);
      this->bt_apply->Name = L"bt_apply";
      this->bt_apply->Size = System::Drawing::Size(184, 77);
      this->bt_apply->TabIndex = 62;
      this->bt_apply->Text = L"Apply";
      this->bt_apply->UseVisualStyleBackColor = true;
      this->bt_apply->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_apply_Click);
      // 
      // bt_apply_all
      // 
      this->bt_apply_all->Location = System::Drawing::Point(1255, 660);
      this->bt_apply_all->Margin = System::Windows::Forms::Padding(4);
      this->bt_apply_all->Name = L"bt_apply_all";
      this->bt_apply_all->Size = System::Drawing::Size(184, 86);
      this->bt_apply_all->TabIndex = 65;
      this->bt_apply_all->Text = L"Apply all";
      this->bt_apply_all->UseVisualStyleBackColor = true;
      this->bt_apply_all->Click += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::bt_apply_all_Click);
      // 
      // C_frm_ObjectCalibration
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(2335, 1041);
      this->Controls->Add(this->bt_apply_all);
      this->Controls->Add(this->bt_apply);
      this->Controls->Add(this->label16);
      this->Controls->Add(this->pb_gray);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->bt_exit);
      this->Controls->Add(this->label17);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->numUD_cam_id);
      this->Controls->Add(this->gb_farbfilter);
      this->Controls->Add(this->lbl_filtered);
      this->Controls->Add(this->pb_tracked);
      this->Controls->Add(this->lbl_gray);
      this->Controls->Add(this->pb_filtered);
      this->Controls->Add(this->lbl_org_pic);
      this->Controls->Add(this->pb_original);
      this->Margin = System::Windows::Forms::Padding(4);
      this->Name = L"C_frm_ObjectCalibration";
      this->Text = L"frm_UM_Object_Calibration";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &C_frm_ObjectCalibration::C_frm_ObjectCalibration_FormClosing);
      this->Load += gcnew System::EventHandler(this, &C_frm_ObjectCalibration::C_frm_ObjectCalibration_Load);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_original))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_filtered))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_tracked))->EndInit();
      this->gb_farbfilter->ResumeLayout(false);
      this->gb_farbfilter->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_color))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_gaussian_sigma))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_gaussian_kernel_size))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_dilation_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_morph_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_dilation_iterations))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_morph_iterations))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_erode_iterations))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_bilateral_spatial))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_erode_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_closing_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_closing_iterations))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_opening_kernelsize))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_opening_iterations))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUD_cam_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_hue_min))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_hue_max))->EndInit();
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_value_min))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_value_max))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_saturation_min))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trb_saturation_max))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_gray))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
       private:
    System::Void		bt_exit_Click						                         (System::Object^  sender, System::EventArgs^ e);
    System::Void		Taktgeber_Tick						                       (System::Object^  sender, System::EventArgs^ e);
    System::Void    numUD_cam_id_ValueChanged                        (System::Object^  sender, System::EventArgs^  e);
    System::Void    FillPicturebox                                   (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
    System::Void    FillMat2Picturebox                               (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage);
    System::Void    C_frm_ObjectCalibration_Load                     (System::Object^  sender, System::EventArgs^  e);
    System::Void    C_frm_ObjectCalibration_FormClosing              (System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
    System::Void    trb_hue_min_ValueChanged                         (System::Object^  sender, System::EventArgs^  e);
    System::Void    trb_hue_max_ValueChanged                         (System::Object^  sender, System::EventArgs^  e);
    System::Void    trb_saturation_min_ValueChanged                  (System::Object^  sender, System::EventArgs^  e);
    System::Void    trb_saturation_max_ValueChanged                  (System::Object^  sender, System::EventArgs^  e);
    System::Void    trb_value_min_ValueChanged                       (System::Object^  sender, System::EventArgs^  e);
    System::Void    trb_value_max_ValueChanged                       (System::Object^  sender, System::EventArgs^  e);
    System::Void    chkb_erode_CheckStateChanged                     (System::Object^  sender, System::EventArgs^  e);
    System::Void    chkb_dilate_CheckStateChanged                    (System::Object^  sender, System::EventArgs^  e);
    System::Void    chkb_bilateral_CheckStateChanged                 (System::Object^  sender, System::EventArgs^  e);
    System::Void    chkb_morph_CheckStateChanged                     (System::Object^  sender, System::EventArgs^  e);

    System::Void    numUD_opening_iterations_ValueChanged            (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_opening_kernelsize_ValueChanged            (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_closing_iterations_ValueChanged            (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_closing_kernelsize_ValueChanged            (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_gaussian_sigma_ValueChanged                (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_gaussian_kernel_size_ValueChanged          (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_erode_iterations_ValueChanged              (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_erode_kernelsize_ValueChanged              (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_dilation_iterations_ValueChanged           (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_dilation_kernelsize_ValueChanged           (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_bilateral_spatial_ValueChanged             (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_bilateral_kernelsize_ValueChanged          (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_morph_iterations_ValueChanged              (System::Object^  sender, System::EventArgs^  e);
    System::Void    numUD_morph_kernelsize_ValueChanged              (System::Object^  sender, System::EventArgs^  e);

    System::Void    numUD_bilateral_color_ValueChanged               (System::Object^  sender, System::EventArgs^  e);
    System::Void    bt_apply_Click                                   (System::Object^  sender, System::EventArgs^  e);

    System::Void bt_apply_all_Click(System::Object^  sender, System::EventArgs^  e);
};
  }//namespace NmSp_frm_ObjectCalibration
