#pragma once

#include "Main.h"

using namespace NmSp_Main;

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
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->BeginInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_camera_picture))->BeginInit();
      this->SuspendLayout();
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1152, 540);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 3;
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1152, 461);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 4;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      // 
      // nup_camera_id
      // 
      this->nup_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->nup_camera_id->Location = System::Drawing::Point(1033, 307);
      this->nup_camera_id->Name = L"nup_camera_id";
      this->nup_camera_id->Size = System::Drawing::Size(34, 29);
      this->nup_camera_id->TabIndex = 5;
      // 
      // lbl_camera_id
      // 
      this->lbl_camera_id->AutoSize = true;
      this->lbl_camera_id->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                                   static_cast<System::Byte>(0)));
      this->lbl_camera_id->Location = System::Drawing::Point(1029, 280);
      this->lbl_camera_id->Name = L"lbl_camera_id";
      this->lbl_camera_id->Size = System::Drawing::Size(152, 24);
      this->lbl_camera_id->TabIndex = 6;
      this->lbl_camera_id->Text = L"Auswahl Kamera";
      // 
      // pb_camera_picture
      // 
      this->pb_camera_picture->Location = System::Drawing::Point(1027, 54);
      this->pb_camera_picture->Name = L"pb_camera_picture";
      this->pb_camera_picture->Size = System::Drawing::Size(291, 210);
      this->pb_camera_picture->TabIndex = 7;
      this->pb_camera_picture->TabStop = false;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                            static_cast<System::Byte>(0)));
      this->label1->Location = System::Drawing::Point(1029, 25);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(105, 24);
      this->label1->TabIndex = 8;
      this->label1->Text = L"Kamerabild";
      // 
      // C_frm_CameraCalibration_Single
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1331, 574);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pb_camera_picture);
      this->Controls->Add(this->lbl_camera_id);
      this->Controls->Add(this->nup_camera_id);
      this->Controls->Add(this->txtb_counter);
      this->Controls->Add(this->bt_exit);
      this->Name = L"C_frm_CameraCalibration_Single";
      this->Text = L"frm_CameraCalibration_Single";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nup_camera_id))->EndInit();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_camera_picture))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion
	};
}
