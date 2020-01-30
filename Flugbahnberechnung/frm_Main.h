#pragma once
#include "Main.h"

using namespace NmSp_Main;

namespace NmSp_frm_Main {
  using namespace NmSp_GlobalObjects;
	public ref class C_frm_Main : public System::Windows::Forms::Form
	  {
	  public:
    C_frm_Main(C_GlobalObjects^ GlobalObjects, C_Main^  Main);

	  protected:
    ~C_frm_Main();

	  private:
    C_GlobalObjects^    GlobalObjects;
    C_Main^             Main;

    UInt32              Zaehler;
    UInt32              Taktgeber_Intervall;



    private: 
    System::Windows::Forms::Timer^  Taktgeber;
    System::Windows::Forms::Button^  bt_exit;
    System::Windows::Forms::Button^  bt_ObjectCalibration;
    System::Windows::Forms::Button^  bt_CameraCalibration;
    System::Windows::Forms::TextBox^  txtb_counter;
    System::ComponentModel::IContainer^  components;





#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->bt_ObjectCalibration = (gcnew System::Windows::Forms::Button());
      this->bt_CameraCalibration = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->SuspendLayout();
      // 
      // Taktgeber
      // 
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &C_frm_Main::Taktgeber_Tick);
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(12, 350);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 2;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &C_frm_Main::bt_exit_Click);
      // 
      // bt_ObjectCalibration
      // 
      this->bt_ObjectCalibration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                          System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->bt_ObjectCalibration->Location = System::Drawing::Point(11, 17);
      this->bt_ObjectCalibration->Name = L"bt_ObjectCalibration";
      this->bt_ObjectCalibration->Size = System::Drawing::Size(197, 73);
      this->bt_ObjectCalibration->TabIndex = 3;
      this->bt_ObjectCalibration->Text = L"Objektkalibierung";
      this->bt_ObjectCalibration->UseVisualStyleBackColor = true;
      this->bt_ObjectCalibration->Click += gcnew System::EventHandler(this, &C_frm_Main::bt_ObjectCalibration_Click);
      // 
      // bt_CameraCalibration
      // 
      this->bt_CameraCalibration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
                                          System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
      this->bt_CameraCalibration->Location = System::Drawing::Point(12, 96);
      this->bt_CameraCalibration->Name = L"bt_CameraCalibration";
      this->bt_CameraCalibration->Size = System::Drawing::Size(196, 73);
      this->bt_CameraCalibration->TabIndex = 4;
      this->bt_CameraCalibration->Text = L"Kamerakalibierung";
      this->bt_CameraCalibration->UseVisualStyleBackColor = true;
      this->bt_CameraCalibration->Click += gcnew System::EventHandler(this, &C_frm_Main::bt_CameraCalibration_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(12, 429);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 0;
      // 
      // C_frm_Main
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(299, 594);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_CameraCalibration);
      this->Controls->Add(this->bt_ObjectCalibration);
      this->Controls->Add(this->bt_exit);
      this->Name = L"C_frm_Main";
      this->Text = L"frm_Main";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &C_frm_Main::C_frm_Main_FormClosing);
      this->Load += gcnew System::EventHandler(this, &C_frm_Main::C_frm_Main_Load);
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
    private: System::Void bt_ObjectCalibration_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void bt_CameraCalibration_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void bt_exit_Click(System::Object^  sender, System::EventArgs^  e);
    private: System::Void C_frm_Main_Load(System::Object^  sender, System::EventArgs^  e);
    private: System::Void C_frm_Main_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
    private: System::Void Taktgeber_Tick(System::Object^  sender, System::EventArgs^  e);
};
}
