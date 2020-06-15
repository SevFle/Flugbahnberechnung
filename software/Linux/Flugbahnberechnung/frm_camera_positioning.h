#ifndef FRM_CAMERA_POSITIONING_H
#define FRM_CAMERA_POSITIONING_H

#include <QDialog>
#include "Main.h"
#include "ui_frm_camera_positioning.h"


class C_frm_camera_positioning : public QDialog
{
    Q_OBJECT

public:
    explicit C_frm_camera_positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget *parent = nullptr);
    ~C_frm_camera_positioning();

private:
  Ui::C_frm_camera_positioning* Ui;



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

#endif // FRM_CAMERA_POSITIONING_H
