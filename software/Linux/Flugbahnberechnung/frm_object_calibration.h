#ifndef FRM_OBJECT_CALIBRATION_H
#define FRM_OBJECT_CALIBRATION_H

#include <QDialog>

namespace Ui {
class frm_object_calibration;
}

class frm_object_calibration : public QDialog
{
    Q_OBJECT

public:
    explicit frm_object_calibration(QWidget *parent = nullptr);
    ~frm_object_calibration();

private:
  Ui::C_frm_Main* Ui;
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

#endif // FRM_OBJECT_CALIBRATION_H
