#ifndef FRM_CAMERA_POSITIONING_POSE_H
#define FRM_CAMERA_POSITIONING_POSE_H

#include <QDialog>
#include "Main.h"
#include "ui_frm_camera_positioning_pose.h"

namespace frm_Camera_Positioning_Pose
{
class C_frm_Camera_Positioning_Pose : public QDialog
{
    Q_OBJECT

public:
     C_frm_Camera_Positioning_Pose(C_GlobalObjects* GlobalObjects, C_Main* Main, QWidget* parent = Q_NULLPTR);
    ~C_frm_Camera_Positioning_Pose();

private:
  Ui::C_frm_camera_positioning_pose* Ui;



  C_GlobalObjects* GlobalObjects;
  C_Main*         Main;
  int Zaehler;
  QTimer*         Taktgeber;
  int             Taktgeber_Intervall;


private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();

};

}

#endif // FRM_CAMERA_POSITIONING_POSE_H
