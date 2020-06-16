#ifndef FRM_CAMERA_CALIBRATION_H
#define FRM_CAMERA_CALIBRATION_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"
#include "ui_frm_camera_calibration.h"

namespace frm_Camera_Calibration
{
class C_frm_Camera_Calibration : public QDialog
{
    Q_OBJECT

public:
     C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Calibration();

private:
  Ui::C_frm_camera_calibration* Ui;



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

#endif // FRM_CAMERA_CALIBRATION_H
