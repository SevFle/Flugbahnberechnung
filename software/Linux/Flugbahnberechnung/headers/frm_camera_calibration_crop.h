#ifndef FRM_CAMERA_CALIBRATION_CROP_H
#define FRM_CAMERA_CALIBRATION_CROP_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"
#include "ui_frm_camera_calibration_crop.h"

namespace frm_Camera_Calibration_Crop
{
class C_frm_Camera_Calibration_Crop : public QMainWindow
{
    Q_OBJECT

public:
     C_frm_Camera_Calibration_Crop(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Calibration_Crop();

private:
  Ui::C_frm_camera_calibration_crop*    Ui;
  C_GlobalObjects*                      GlobalObjects;
  C_Main*         Main;
  int Zaehler;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();
  void Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label);

};

}

#endif // FRM_CAMERA_CALIBRATION_CROP_H
