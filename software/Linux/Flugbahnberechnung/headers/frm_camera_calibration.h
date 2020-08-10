#ifndef FRM_CAMERA_CALIBRATION_H
#define FRM_CAMERA_CALIBRATION_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"
#include "ui_frm_camera_calibration.h"

namespace frm_Camera_Calibration
{
class C_frm_Camera_Calibration : public QMainWindow
{
    Q_OBJECT

public:
     C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Calibration();

private:
  Ui::C_frm_camera_calibration*     Ui;
  C_GlobalObjects*                  GlobalObjects;
  C_Main*                           Main;
  pthread_mutex_t*  restrict        lock;
  pthread_t*                        camThread;
  QTimer*                           Taktgeber;
  int                               Taktgeber_Intervall;
  int                               Zaehler;
  int                               Timerwait;
   typedef void * (*THREADFUNCPTR)(void *);

  bool                              calibration_running;
  bool                              imgPopOut;
  int                               photo_interval;
  int                               intervall;
  int                               photo_count;
  int                               photo_id;
  int                               method;
  int                               cameraID;
  int                               sm_calibration_state;
  int                               usrInputAbsPhoto;

private:
  void showEvent                    (QShowEvent* ShowEvent) override;
  void closeEvent                   (QCloseEvent* CloseEvent) override;
  bool eventFilter                  (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick               ();
  void FillMat2Lbl                  (cv::Mat& img, QLabel* label);

  static void camera_calibration_thread (void *This);
  void sm_Single_camera_calibration     ();
  void sm_Stereo_camera_calibration     ();


  void on_bt_start_clicked              ();
  void on_bt_exit_clicked               ();
  void on_num_camera_id_valueChanged    (int arg1);
  void on_rb_single_calibration_clicked ();
  void on_rb_stereo_calibration_clicked ();
  void on_bt_photo_clicked              ();
  void ShowTable                        ();

};
}

#endif // FRM_CAMERA_CALIBRATION_H
