#pragma once

#include "Main.h"

using namespace nmsp_Main;

namespace NmSp_frm_Main
  {
  using namespace nmsp_GlobalObjects;
  public ref class C_frm_Main : public System::Windows::Forms::Form
    {
    public:
    /*************************************************************** Konstruktoren **************************************************************/
    C_frm_Main (C_GlobalObjects* GlobalObjects, C_Main^ Main);

    protected:
    /**************************************************************** Destruktor ****************************************************************/
    ~C_frm_Main ();
    /******************************************** Nicht öffentliche private Klassenobjekte **************************************************/
    private:
    C_GlobalObjects* GlobalObjects;
    C_Main^          Main;

    UInt32 Zaehler;
    UInt32 Taktgeber_Intervall;

    UInt32 state;
    UInt32 timerwait;


    private:
    System::Windows::Forms::Timer^         Taktgeber;
    System::Windows::Forms::Button^        bt_exit;
    System::Windows::Forms::Button^        bt_ObjectCalibration;
    System::Windows::Forms::Button^        bt_CameraCalibration;
    System::Windows::Forms::TextBox^       txtb_counter;
    System::Windows::Forms::NumericUpDown^ nup_camera_count;
    System::Windows::Forms::Label^         label1;
    private:
    System::Windows::Forms::Button^ bt_camera_positioning;
    private:
    System::Windows::Forms::Button^ bt_apply_cameras;
    private:
    System::Windows::Forms::GroupBox^ groupBox1;
    private:
    System::Windows::Forms::Button^ bt_Kameraposen;


    System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
    void InitializeComponent (void)
      {
      this->components            = (gcnew System::ComponentModel::Container());
      this->Taktgeber             = (gcnew System::Windows::Forms::Timer (this->components));
      this->bt_exit               = (gcnew System::Windows::Forms::Button());
      this->bt_ObjectCalibration  = (gcnew System::Windows::Forms::Button());
      this->bt_CameraCalibration  = (gcnew System::Windows::Forms::Button());
      this->txtb_counter          = (gcnew System::Windows::Forms::TextBox());
      this->nup_camera_count      = (gcnew System::Windows::Forms::NumericUpDown());
      this->label1                = (gcnew System::Windows::Forms::Label());
      this->bt_camera_positioning = (gcnew System::Windows::Forms::Button());
      this->bt_apply_cameras      = (gcnew System::Windows::Forms::Button());
      this->groupBox1             = (gcnew System::Windows::Forms::GroupBox());
      this->bt_Kameraposen        = (gcnew System::Windows::Forms::Button());
      (cli::
      safe_cast<System::ComponentModel::ISupportInitialize^> (this->nup_camera_count)
      )
      ->
      BeginInit();
      this->groupBox1->SuspendLayout();
      this->SuspendLayout();
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler (this,&C_frm_Main::Taktgeber_Tick);
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                          static_cast<System::Byte> (0)));
      this->bt_exit->Location                = System::Drawing::Point (11,376);
      this->bt_exit->Name                    = L"bt_exit";
      this->bt_exit->Size                    = System::Drawing::Size (167,73);
      this->bt_exit->TabIndex                = 2;
      this->bt_exit->Text                    = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler (this,&C_frm_Main::bt_exit_Click);
      // 
      // bt_ObjectCalibration
      // 
      this->bt_ObjectCalibration->Enabled = false;
      this->bt_ObjectCalibration->Font    = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,
                                                                          System::Drawing::GraphicsUnit::Point,static_cast<System::Byte> (0)));
      this->bt_ObjectCalibration->Location                = System::Drawing::Point (12,23);
      this->bt_ObjectCalibration->Name                    = L"bt_ObjectCalibration";
      this->bt_ObjectCalibration->Size                    = System::Drawing::Size (213,54);
      this->bt_ObjectCalibration->TabIndex                = 3;
      this->bt_ObjectCalibration->Text                    = L"Tracking";
      this->bt_ObjectCalibration->UseVisualStyleBackColor = true;
      this->bt_ObjectCalibration->Click += gcnew System::EventHandler (this,&C_frm_Main::bt_ObjectCalibration_Click);
      // 
      // bt_CameraCalibration
      // 
      this->bt_CameraCalibration->Enabled = false;
      this->bt_CameraCalibration->Font    = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,
                                                                          System::Drawing::GraphicsUnit::Point,static_cast<System::Byte> (0)));
      this->bt_CameraCalibration->Location                = System::Drawing::Point (6,28);
      this->bt_CameraCalibration->Name                    = L"bt_CameraCalibration";
      this->bt_CameraCalibration->Size                    = System::Drawing::Size (211,54);
      this->bt_CameraCalibration->TabIndex                = 4;
      this->bt_CameraCalibration->Text                    = L"Kamerakalibierung";
      this->bt_CameraCalibration->UseVisualStyleBackColor = true;
      this->bt_CameraCalibration->Click += gcnew System::EventHandler (this,&C_frm_Main::bt_CameraCalibration_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point (11,456);
      this->txtb_counter->Name     = L"txtb_counter";
      this->txtb_counter->Size     = System::Drawing::Size (166,20);
      this->txtb_counter->TabIndex = 0;
      // 
      // nup_camera_count
      // 
      this->nup_camera_count->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",13.8F,System::Drawing::FontStyle::Regular,
                                                                   System::Drawing::GraphicsUnit::Point,static_cast<System::Byte> (0)));
      this->nup_camera_count->Location = System::Drawing::Point (11,301);
      this->nup_camera_count->Maximum  = System::Decimal (gcnew cli::array<System::Int32> (4)
        {
        10, 0, 0, 0
        });
      this->nup_camera_count->Minimum = System::Decimal (gcnew cli::array<System::Int32> (4)
        {
        1, 0, 0, 0
        });
      this->nup_camera_count->Name     = L"nup_camera_count";
      this->nup_camera_count->Size     = System::Drawing::Size (62,28);
      this->nup_camera_count->TabIndex = 5;
      this->nup_camera_count->Value    = System::Decimal (gcnew cli::array<System::Int32> (4)
        {
        1, 0, 0, 0
        });
// 
// label1
// 
      this->label1->AutoSize = true;
      this->label1->Font     = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",13.8F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                             static_cast<System::Byte> (0)));
      this->label1->Location = System::Drawing::Point (8,262);
      this->label1->Name     = L"label1";
      this->label1->Size     = System::Drawing::Size (335,24);
      this->label1->TabIndex = 6;
      this->label1->Text     = L"Anzahl der angeschlossenen Kameras";
      // 
      // bt_camera_positioning
      // 
      this->bt_camera_positioning->Enabled = false;
      this->bt_camera_positioning->Font    = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,
                                                                           System::Drawing::GraphicsUnit::Point,static_cast<System::Byte> (0)));
      this->bt_camera_positioning->Location                = System::Drawing::Point (6,88);
      this->bt_camera_positioning->Name                    = L"bt_camera_positioning";
      this->bt_camera_positioning->Size                    = System::Drawing::Size (211,54);
      this->bt_camera_positioning->TabIndex                = 7;
      this->bt_camera_positioning->Text                    = L"Kamerapositionierung";
      this->bt_camera_positioning->UseVisualStyleBackColor = true;
      this->bt_camera_positioning->MouseClick += gcnew System::Windows::Forms::MouseEventHandler (this,&C_frm_Main::bt_camera_positioning_MouseClick);
      // 
      // bt_apply_cameras
      // 
      this->bt_apply_cameras->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,
                                                                   System::Drawing::GraphicsUnit::Point,static_cast<System::Byte> (0)));
      this->bt_apply_cameras->Location                = System::Drawing::Point (80,288);
      this->bt_apply_cameras->Name                    = L"bt_apply_cameras";
      this->bt_apply_cameras->Size                    = System::Drawing::Size (142,41);
      this->bt_apply_cameras->TabIndex                = 8;
      this->bt_apply_cameras->Text                    = L"Anwenden";
      this->bt_apply_cameras->UseVisualStyleBackColor = true;
      this->bt_apply_cameras->Click += gcnew System::EventHandler (this,&C_frm_Main::bt_apply_cameras_Click);
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add (this->bt_Kameraposen);
      this->groupBox1->Controls->Add (this->bt_CameraCalibration);
      this->groupBox1->Controls->Add (this->bt_camera_positioning);
      this->groupBox1->Font = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                            static_cast<System::Byte> (0)));
      this->groupBox1->Location = System::Drawing::Point (447,1);
      this->groupBox1->Name     = L"groupBox1";
      this->groupBox1->Size     = System::Drawing::Size (229,239);
      this->groupBox1->TabIndex = 9;
      this->groupBox1->TabStop  = false;
      this->groupBox1->Text     = L"Settings";
      // 
      // bt_Kameraposen
      // 
      this->bt_Kameraposen->Enabled = false;
      this->bt_Kameraposen->Font    = (gcnew System::Drawing::Font (L"Microsoft Sans Serif",14.25F,System::Drawing::FontStyle::Regular,System::Drawing::GraphicsUnit::Point,
                                                                    static_cast<System::Byte> (0)));
      this->bt_Kameraposen->Location                = System::Drawing::Point (6,148);
      this->bt_Kameraposen->Name                    = L"bt_Kameraposen";
      this->bt_Kameraposen->Size                    = System::Drawing::Size (211,54);
      this->bt_Kameraposen->TabIndex                = 8;
      this->bt_Kameraposen->Text                    = L"Kameraposen";
      this->bt_Kameraposen->UseVisualStyleBackColor = true;
      this->bt_Kameraposen->Click += gcnew System::EventHandler (this,&C_frm_Main::button1_Click);
      // 
      // C_frm_Main
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF (6,13);
      this->AutoScaleMode       = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize          = System::Drawing::Size (709,628);
      this->Controls->Add (this->bt_ObjectCalibration);
      this->Controls->Add (this->groupBox1);
      this->Controls->Add (this->bt_apply_cameras);
      this->Controls->Add (this->label1);
      this->Controls->Add (this->nup_camera_count);
      this->Controls->Add (this->txtb_counter);
      this->Controls->Add (this->bt_exit);
      this->Name = L"C_frm_Main";
      this->Text = L"frm_Main";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler (this,&C_frm_Main::C_frm_Main_FormClosing);
      this->Load += gcnew System::EventHandler (this,&C_frm_Main::C_frm_Main_Load);
      (cli::
      safe_cast<System::ComponentModel::ISupportInitialize^> (this->nup_camera_count)
      )
      ->
      EndInit();
      this->groupBox1->ResumeLayout (false);
      this->ResumeLayout (false);
      this->PerformLayout();
      }
#pragma endregion
    private:
    System::Void bt_ObjectCalibration_Click (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void bt_CameraCalibration_Click (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void bt_exit_Click (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void C_frm_Main_Load (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void C_frm_Main_FormClosing (System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
    private:
    System::Void Taktgeber_Tick (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void bt_camera_positioning_MouseClick (System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
    private:
    System::Void bt_apply_cameras_Click (System::Object^ sender, System::EventArgs^ e);
    private:
    System::Void button1_Click (System::Object^ sender, System::EventArgs^ e);
    };
  }
