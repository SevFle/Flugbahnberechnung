#ifndef FRM_OBJECT_CALIBRATION_H
#define FRM_OBJECT_CALIBRATION_H


#include <QtWidgets/QMainWindow>
#include <QTimer>

#include "headers/Etc/Main.h"
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
    CameraManager::S_pipelinePayload*       pData;

    int                                     Zaehler;
    int                                     Taktgeber_Intervall;
    int                                     camID;
    int executionTime[8];
    int Zaehler_old;


    bool dilate_active;
    bool bilateral_active;
    bool morph_active;
    bool erode_active;

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
  void get_camera_settings (Camera::C_Camera2 &Camera);
  void set_gui();
  void Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label);
  void on_numTimerIntervall_valueChanged(int arg1);
};

}


#endif // FRM_OBJECT_CALIBRATION_H
