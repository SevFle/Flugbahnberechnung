#ifndef FRM_CAMERA_POSITIONING_POSE_H
#define FRM_CAMERA_POSITIONING_POSE_H

#include <QDialog>

namespace Ui {
class frm_camera_positioning_pose;
}

class C_frm_camera_positioning_pose : public QDialog
{
    Q_OBJECT

public:
    explicit C_frm_camera_positioning_pose(QWidget *parent = nullptr);
    ~C_frm_camera_positioning_pose();

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

};

#endif // FRM_CAMERA_POSITIONING_POSE_H
