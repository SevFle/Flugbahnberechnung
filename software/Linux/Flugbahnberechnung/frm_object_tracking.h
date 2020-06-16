#ifndef FRM_OBJECT_TRACKING_H
#define FRM_OBJECT_TRACKING_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"

#include "ui_frm_object_tracking.h"

namespace frm_Object_Tracking
{
class C_frm_Object_Tracking : public QDialog
{
    Q_OBJECT

public:
    C_frm_Object_Tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Object_Tracking();

private slots:
    void on_bt_start_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_bt_exit_clicked();

    void on_num_camera_id_valueChanged(int arg1);

private:
  Ui::C_frm_object_tracking* Ui;



  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  std::thread*    Tracking;

  int Zaehler;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;
  int             TimerWait;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
};

}

#endif // FRM_OBJECT_TRACKING_H
