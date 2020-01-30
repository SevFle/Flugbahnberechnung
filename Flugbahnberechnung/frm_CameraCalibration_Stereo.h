#pragma once
#include "Main.h"

using namespace NmSp_Main;

namespace NmSp_frm_CameraCalibration_Stereo 
  {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	public ref class C_frm_CameraCalibration_Stereo : public System::Windows::Forms::Form
	  {
	  public:
    C_frm_CameraCalibration_Stereo(C_GlobalObjects^ GlobalObjects, C_Main^  Main);
	  protected:
    ~C_frm_CameraCalibration_Stereo();

	  private:
    C_GlobalObjects^      GlobalObjects;
    C_Main                Main;

    UInt32      Zaehler;


    private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		  {
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = L"frm_CameraCalibration_Stereo";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		  }
#pragma endregion
	};
}
