#ifndef FRM_CAMERA_CALIBRATION_H
#define FRM_CAMERA_CALIBRATION_H

#include <QMainWindow>
#include <QTimer>
#include "headers/Etc/Main.h"
#include "ui_frm_camera_calibration.h"

namespace frm_Camera_Calibration
{
class C_frm_Camera_Calibration : public QMainWindow
{
    Q_OBJECT
  typedef void * (*THREADFUNCPTR)(void *);


public:
     C_frm_Camera_Calibration(C_GlobalObjects* GlobalObjects, Main::C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Calibration();

private:
  Ui::C_frm_camera_calibration*     Ui;
  C_GlobalObjects*                  GlobalObjects;
  Main::C_Main*                           Main;
  pthread_t*                        camThread;
  CameraManager::S_pipelinePayload* pData;
  QTimer*                           Taktgeber;
  cv::Mat*                          imgBuffer[2];
  cv::Mat*                          Camera0ToWorld;
  cv::Mat*                          Camera1ToWorld;
  cv::Mat*                          Camera0ToCamera1;


  int                               Taktgeber_Intervall;
  int                               Zaehler;

  bool                              calibration_running;
  int                               photo_id;
  int                               method;
  int                               cameraID;
  int                               sm_calibration_state;
  int                               usrInputAbsPhoto;
  double rms;
  double intrinsic[3][3];
  double distcoeffs[1][5];

  std::atomic<bool>                 finished;


private:
  void showEvent                    (QShowEvent* ShowEvent) override;
  void closeEvent                   (QCloseEvent* CloseEvent) override;
  bool eventFilter                  (QObject* Object, QEvent* Event) override;

private slots:
  void Taktgeber_Tick               ();
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

  void on_num_TimerIntervall_valueChanged(int arg1);
  void on_bt_pose_estimation_clicked();
  };
}

#endif // FRM_CAMERA_CALIBRATION_H
