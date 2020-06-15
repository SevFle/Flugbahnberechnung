#ifndef FRM_CAMERA_CALIBRATION_H
#define FRM_CAMERA_CALIBRATION_H

#include <QDialog>

namespace Ui {
class frm_camera_calibration;
}

class C_frm_camera_calibration : public QDialog
{
    Q_OBJECT

public:
    explicit C_frm_camera_calibration(QWidget *parent = nullptr);
    ~C_frm_camera_calibration();

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

#endif // FRM_CAMERA_CALIBRATION_H
