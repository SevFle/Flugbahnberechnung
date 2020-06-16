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

  int cameras_in_use;
  int Timerwait;

  bool calibration_running;
  int  photo_interval;
  int  intervall;
  int  photo_count;
  int  photo_id;
  int  method;
  int  current_camera_id;
  int  sm_calibration_state;
  int photocount_user_input;

private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();
};
}

#endif // FRM_CAMERA_CALIBRATION_H
