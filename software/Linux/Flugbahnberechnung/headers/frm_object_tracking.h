#ifndef FRM_OBJECT_TRACKING_H
#define FRM_OBJECT_TRACKING_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"

#include "ui_frm_object_tracking.h"

namespace frm_Object_Tracking
{
class C_frm_Object_Tracking : public QMainWindow
{
    Q_OBJECT

public:
    C_frm_Object_Tracking(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Object_Tracking();

private slots:
    void on_bt_start_clicked();

    void on_bt_exit_clicked();

    void on_num_camera_id_valueChanged(int arg1);

private:
  Ui::C_frm_object_tracking* Ui;

  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  std::thread*    Tracking;

  QTimer*         Taktgeber;
  CameraManager::S_pipelinePayload*       payload;


  int             Taktgeber_Intervall;
  int             TimerWait;
  int Zaehler;
  int cameraID;

private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();
  void Fill_Mat_2_Lbl(cv::Mat& img, QLabel* label);


};

}

#endif // FRM_OBJECT_TRACKING_H
