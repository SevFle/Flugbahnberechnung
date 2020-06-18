#ifndef FRM_CAMERA_POSITIONING_H
#define FRM_CAMERA_POSITIONING_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"
#include "ui_frm_camera_positioning.h"

namespace frm_Camera_Positioning
{
class C_frm_Camera_Positioning : public QMainWindow
{
    Q_OBJECT

public:
     C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Positioning();

private:
  Ui::C_frm_camera_positioning* Ui;



  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;
  int TimerWait;
  int cameras_in_use;
  int Zaehler;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();
  void on_bt_apply_clicked();
  void on_bt_exit_clicked();
  void on_num_cam_2_valueChanged(int arg1);
  void on_num_cam_0_valueChanged(int arg1);
  void on_num_cam_1_valueChanged(int arg1);
  void on_num_cam_3_valueChanged(int arg1);
  void on_num_cam_4_valueChanged(int arg1);
  void on_num_cam_5_valueChanged(int arg1);
  void set_num_value (std::vector<int> camera_list);
  void set_num_value ();
  void FillMat2Lbl(cv::Mat& img, QLabel* label);

};

}

#endif // FRM_CAMERA_POSITIONING_H
