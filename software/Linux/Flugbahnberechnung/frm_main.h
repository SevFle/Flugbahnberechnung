#pragma once
#ifndef FRM_MAIN_H
#define FRM_MAIN_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>

#include "Main.h"
#include "ui_frm_main.h"

using namespace Main;

namespace frm_Main
  {
  class C_frm_Main : public QMainWindow
    {
    Q_OBJECT

    public:
    C_frm_Main(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent = nullptr);

    ~C_frm_Main();


  private:
    Ui::C_frm_Main* Ui;
    QMessageBox* MsgBox;



    C_GlobalObjects* GlobalObjects;
    C_Main*         Main;
    int Zaehler;
    QTimer*         Taktgeber;
    int             Taktgeber_Intervall;

    int state;

  private:
    void showEvent (QShowEvent* ShowEvent) override;
    void closeEvent (QCloseEvent* CloseEvent) override;
    bool eventFilter (QObject* Object, QEvent* Event) override;

  private slots:
    void Taktgeber_Tick();
    void on_bt_exit_clicked();

    void on_bt_apply_clicked();
    void on_bt_tracking_clicked();
    void on_bt_camera_calibration_clicked();
    void on_bt_camera_pose_clicked();
  };//class C_frm_Main

  }//namespace frm_Main
#endif // FRM_MAIN_H
