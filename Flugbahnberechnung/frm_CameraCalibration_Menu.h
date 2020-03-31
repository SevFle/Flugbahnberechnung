#pragma once

#include "Main.h"

using namespace nmsp_Main;


namespace NmSp_CamerCalibration_Menu 
  {
  using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class C_frm_CameraCalibration_Menu : public System::Windows::Forms::Form
	  {
	  public:
    C_frm_CameraCalibration_Menu(C_GlobalObjects* GlobalObjects, C_Main^  Main);

	  protected:
    ~C_frm_CameraCalibration_Menu();

    private:
    C_GlobalObjects*      GlobalObjects;
    C_Main^               Main;

    UInt32      Zaehler;

    private:
    System::Windows::Forms::Button^                   bt_SingleCalibration;
    System::Windows::Forms::Button^                   bt_StereoCalibration;
    System::Windows::Forms::TextBox^                  txtb_counter;
    System::Windows::Forms::Button^                   bt_exit;
    System::Windows::Forms::Timer^                    Taktgeber;
    System::ComponentModel::IContainer^               components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->bt_SingleCalibration = (gcnew System::Windows::Forms::Button());
      this->bt_StereoCalibration = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->SuspendLayout();
      // 
      // bt_SingleCalibration
      // 
      this->bt_SingleCalibration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                          System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->bt_SingleCalibration->Location = System::Drawing::Point(12, 23);
      this->bt_SingleCalibration->Name = L"bt_SingleCalibration";
      this->bt_SingleCalibration->Size = System::Drawing::Size(196, 73);
      this->bt_SingleCalibration->TabIndex = 5;
      this->bt_SingleCalibration->Text = L"Single Kalibrierung";
      this->bt_SingleCalibration->UseVisualStyleBackColor = true;
      this->bt_SingleCalibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Menu::bt_SingleCalibration_Click);
      // 
      // bt_StereoCalibration
      // 
      this->bt_StereoCalibration->Enabled = false;
      this->bt_StereoCalibration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                          System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->bt_StereoCalibration->Location = System::Drawing::Point(224, 23);
      this->bt_StereoCalibration->Name = L"bt_StereoCalibration";
      this->bt_StereoCalibration->Size = System::Drawing::Size(196, 73);
      this->bt_StereoCalibration->TabIndex = 6;
      this->bt_StereoCalibration->Text = L"Stereo Kalibrierung";
      this->bt_StereoCalibration->UseVisualStyleBackColor = true;
      this->bt_StereoCalibration->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Menu::bt_StereoCalibration_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(262, 274);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 7;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(262, 195);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 8;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Menu::bt_exit_Click);
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Menu::Taktgeber_Tick);
      // 
      // C_frm_CameraCalibration_Menu
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(441, 301);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Controls->Add(this->bt_StereoCalibration);
      this->Controls->Add(this->bt_SingleCalibration);
      this->Name = L"C_frm_CameraCalibration_Menu";
      this->Text = L"frm_CameraCalibration_Menu";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &C_frm_CameraCalibration_Menu::C_frm_CameraCalibration_Menu_FormClosing);
      this->Load += gcnew System::EventHandler(this, &C_frm_CameraCalibration_Menu::C_frm_CameraCalibration_Menu_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
/**************************************************** WinForms Event-Handler *********************************************************/

    private: 
    System::Void bt_exit_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e);
    System::Void bt_StereoCalibration_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void bt_SingleCalibration_Click(System::Object^  sender, System::EventArgs^  e);
    System::Void C_frm_CameraCalibration_Menu_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
    System::Void C_frm_CameraCalibration_Menu_Load(System::Object^  sender, System::EventArgs^  e);
    };//	public ref class C_frm_CameraCalibration_Menu 

}//namespace NmSp_CamerCalibration_Menu 

                                                