#ifndef FRM_ROBOT_CALIBRATION_H
#define FRM_ROBOT_CALIBRATION_H

#include <QMainWindow>
#include <QTimer>
#include "ui_frm_robot_calibration.h"
#include "headers/Etc/Main.h"


namespace frm_Robot_Calibration
  {
  class C_frm_Robot_Calibration : public QMainWindow
    {
    Q_OBJECT

  public:
     C_frm_Robot_Calibration(C_GlobalObjects* GlobalObjects, Main::C_Main* Main, QWidget *parent = nullptr);
    ~C_frm_Robot_Calibration();

  private:
    Ui::C_frm_robot_calibration*      ui;
    C_GlobalObjects*                  GlobalObjects;
    Main::C_Main*                     Main;
    QTimer*                           Taktgeber;
    cv::Mat*                          camPose;
    C_AbsolutePose*                   robotWorldPose;
    C_RelativePose*                   robotTcpPose;
    CameraManager::S_pipelinePayload* pData;



    int                               Taktgeber_Intervall;
    int                               Zaehler;
    int                               cameraID;

  private:
    void showEvent                    (QShowEvent* ShowEvent) override;
    void closeEvent                   (QCloseEvent* CloseEvent) override;
    bool eventFilter                  (QObject* Object, QEvent* Event) override;


  private:
    void writeCamPose();
    void writeRobotTcpPose();

  private slots:
    void Taktgeber_Tick               ();




    void on_num_camID_valueChanged(int arg1);
    void on_bt_exit_clicked();
    void on_bt_save_pose_clicked();
    };

  }


#endif // FRM_ROBOT_CALIBRATION_H
