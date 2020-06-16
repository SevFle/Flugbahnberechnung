#ifndef FRM_CAMERA_POSITIONING_H
#define FRM_CAMERA_POSITIONING_H

#include <QMainWindow>
#include <QTimer>
#include "Main.h"
#include "ui_frm_camera_positioning.h"

namespace frm_Camera_Positioning
{
class C_frm_Camera_Positioning : public QDialog
{
    Q_OBJECT

public:
     C_frm_Camera_Positioning(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Positioning();

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

}

#endif // FRM_CAMERA_POSITIONING_H
