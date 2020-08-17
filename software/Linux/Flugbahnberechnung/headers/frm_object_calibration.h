#ifndef FRM_OBJECT_CALIBRATION_H
#define FRM_OBJECT_CALIBRATION_H


#include <QtWidgets/QMainWindow>
#include <QTimer>

#include "Main.h"
#include "ui_frm_object_calibration.h"
using namespace Main;


namespace frm_Object_Calibration
{
class C_frm_Object_Calibration : public QMainWindow
{
Q_OBJECT

public:
C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);

~C_frm_Object_Calibration();
private:

C_GlobalObjects*                GlobalObjects;
C_Main*                         Main;
QTimer*                         Taktgeber;
Ui::C_frm_object_calibration*   Ui;
QMessageBox*                    MsgBox;
CameraManager::S_pipelinePayload*       pData;

  int Zaehler;
  int             Taktgeber_Intervall;
int camera_id_in_use;
int TimerWait;


int hue_min;
int hue_max;
int saturation_min;
int saturation_max;
int value_min;
int value_max;
int target_size_width;     //Resizing the image to the wanted width Values
int target_size_height;     //Resizing the image to the wanted height Values


int erosion_iterations;
int dilation_iterations;
int opening_iterations;
int closing_iterations;

int erosion_kernel_size;
int dilation_kernel_size;
int bilateral_kernel_size;
int opening_kernel_size;
int closing_kernel_size;
int morph_kernel_size;
int gaussian_kernel_size;

int ksize;

int bordertype;

int numBoards;
int numCornersHor;
int numcornersVer;

int prior_selection;

double gaussian_sigma;


float bilateral_sigma_color;
float bilateral_sigma_space;

bool erode_active;
bool dilate_active;
bool open_active;
bool close_active;
bool bilateral_active;
bool morph_active;

private slots:
void on_num_opening_iterations_valueChanged(int arg1);

void on_num_opening_kernelsize_valueChanged(int arg1);

void on_num_closing_iterations_valueChanged(int arg1);

void on_num_closing_kernelsize_valueChanged(int arg1);

void on_num_erode_kernelsize_valueChanged(int arg1);

void on_num_dilate_kernelsize_valueChanged(int arg1);

void on_num_morph_kernelsize_valueChanged(int arg1);

void on_num_gaussian_sigma_valueChanged(int arg1);

void on_num_bilateral_color_valueChanged(int arg1);

void on_num_bilateral_spatial_valueChanged(int arg1);

void on_num_bilateral_kernelsize_valueChanged(int arg1);

void on_sld_hue_min_valueChanged(int value);

void on_sld_hue_max_valueChanged(int value);

void on_sld_saturation_min_valueChanged(int value);

void on_sld_saturation_max_valueChanged(int value);

void on_sld_value_min_valueChanged(int value);

void on_sld_value_max_valueChanged(int value);

void on_sld_objectsize_min_valueChanged(int value);

void on_sld_objectsize_max_valueChanged(int value);

void on_num_camera_valueChanged(int arg1);

void on_bt_exit_clicked();






private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();
  void on_num_dilate_iterations_valueChanged(int arg1);
  void on_num_erode_iterations_valueChanged(int arg1);
  void on_num_morph_iterations_valueChanged(int arg1);
  void on_num_gaussian_kernelsize_valueChanged(int arg1);
  void on_bt_apply_all_clicked();
  void on_bt_apply_clicked();
  void on_chkb_dilate_stateChanged(int arg1);
  void on_chkb_morph_stateChanged(int arg1);
  void on_chkb_erode_stateChanged(int arg1);
  void on_bt_tracking_clicked();
  void on_chkb_bilateral_stateChanged(int arg1);
  void get_camera_settings (int camera_id);
  void set_gui();
  void Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label);
};

}


#endif // FRM_OBJECT_CALIBRATION_H
