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
  typedef void * (*THREADFUNCPTR)(void *);

public:
  C_frm_Camera_Positioning          (C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
  ~C_frm_Camera_Positioning         ();

private:
  Ui::C_frm_camera_positioning*     Ui;
  C_GlobalObjects*                  GlobalObjects;
  C_Main*                           Main;
  pthread_mutex_t*  restrict        lock;
  QTimer*                           Taktgeber;
  CameraManager::S_threadPayload*       pData;

  int                               Taktgeber_Intervall;
  int                               TimerWait;
  int                               Zaehler;
  std::vector<cv::Mat>*             tData;


private:
  void showEvent                    (QShowEvent* ShowEvent) override;
  void closeEvent                   (QCloseEvent* CloseEvent) override;
  bool eventFilter                  (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick               ();
  void on_bt_apply_clicked          ();
  void on_bt_exit_clicked           ();
  void set_num_value                (std::vector<int> camera_list);
  void set_num_value                ();
  void FillMat2Lbl                  (cv::Mat& img, QLabel* label);

};
}

#endif // FRM_CAMERA_POSITIONING_H
