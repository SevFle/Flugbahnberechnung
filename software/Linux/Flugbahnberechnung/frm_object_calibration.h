#ifndef FRM_OBJECT_CALIBRATION_H
#define FRM_OBJECT_CALIBRATION_H


#include <QMainWindow>
#include <QTimer>

#include "Main.h"
#include "ui_frm_object_calibration.h"

namespace frm_Object_Calibration
{
class C_frm_Object_Calibration : public QDialog
{
Q_OBJECT

public:
C_frm_Object_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);

~C_frm_Object_Calibration();

private slots:
void on_num_sigma_kernelsize_valueChanged(int arg1);

void on_num_opening_iterations_valueChanged(int arg1);

void on_num_opening_kernelsize_valueChanged(int arg1);

void on_num_closing_iterations_valueChanged(int arg1);

void on_num_closing_kernelsize_valueChanged(int arg1);

void on_num_closing_iterations_2_valueChanged(int arg1);

void on_num_erode_kernelsize_valueChanged(int arg1);

void on_num_closing_iterations_3_valueChanged(int arg1);

void on_num_dilate_kernelsize_valueChanged(int arg1);

void on_num_closing_iterations_4_valueChanged(int arg1);

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
  Ui::C_frm_object_calibration* Ui;
  QMessageBox* MsgBox;



  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  int Zaehler;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
};

}


#endif // FRM_OBJECT_CALIBRATION_H
