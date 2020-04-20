#pragma once
#include "Main.h"
#include <opencv2/core/mat.hpp>

using namespace nmsp_Main;

namespace nsmp_object_tracking
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






	  System::Windows::Forms::Button^  bt_exit;

    private:
	  System::Windows::Forms::TextBox^  txtb_counter;
    private: System::Windows::Forms::Timer^  Taktgeber;
    private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->bt_exit = (gcnew System::Windows::Forms::Button());
      this->txtb_counter = (gcnew System::Windows::Forms::TextBox());
      this->Taktgeber = (gcnew System::Windows::Forms::Timer(this->components));
      this->SuspendLayout();
      // 
      // bt_exit
      // 
      this->bt_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                             static_cast<System::Byte>(0)));
      this->bt_exit->Location = System::Drawing::Point(1110, 475);
      this->bt_exit->Name = L"bt_exit";
      this->bt_exit->Size = System::Drawing::Size(167, 73);
      this->bt_exit->TabIndex = 14;
      this->bt_exit->Text = L"Exit";
      this->bt_exit->UseVisualStyleBackColor = true;
      this->bt_exit->Click += gcnew System::EventHandler(this, &c_frm_Object_Tracking::bt_exit_Click);
      // 
      // txtb_counter
      // 
      this->txtb_counter->Location = System::Drawing::Point(1110, 554);
      this->txtb_counter->Name = L"txtb_counter";
      this->txtb_counter->Size = System::Drawing::Size(166, 20);
      this->txtb_counter->TabIndex = 13;
      // 
      // Taktgeber
      // 
      this->Taktgeber->Interval = 25;
      this->Taktgeber->Tick += gcnew System::EventHandler(this, &c_frm_Object_Tracking::Taktgeber_Tick);
      // 
      // c_frm_Object_Tracking
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1289, 581);
      this->Controls->Add(this->bt_exit);
      this->Controls->Add(this->txtb_counter);
      this->Name = L"c_frm_Object_Tracking";
      this->Text = L"frm_Object_Tracking";
      this->ResumeLayout(false);
      this->PerformLayout();

      }
#pragma endregion


	  private:
    System::Void		bt_exit_Click						                         (System::Object^  sender, System::EventArgs^ e);
    System::Void		Taktgeber_Tick						                       (System::Object^  sender, System::EventArgs^ e);
    System::Void    FillPicturebox                                   (System::Windows::Forms::PictureBox^ Picturebox, Int32 ColorImageCols, Int32 ColorImageRows, Int32 ColorImageStep, Int32 ColorImageType, System::IntPtr ColorImagePtr);
    System::Void    FillMat2Picturebox                               (System::Windows::Forms::PictureBox^ Picturebox, cv::Mat &colorImage);

	  public:
	};
}
