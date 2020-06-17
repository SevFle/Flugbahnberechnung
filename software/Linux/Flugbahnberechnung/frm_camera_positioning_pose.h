#ifndef FRM_CAMERA_POSITIONING_POSE_H
#define FRM_CAMERA_POSITIONING_POSE_H

#include <QDialog>
#include "Main.h"
#include "ui_frm_camera_positioning_pose.h"

namespace frm_Camera_Positioning_Pose
{
class C_frm_Camera_Positioning_Pose : public QMainWindow
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
  int camera_id;


  double phi;
  double theta;
  double psi;

  bool convert_to_degree_active;

  int t_x;
  int t_y;
  int t_z;

  int method;

  double nx, ny, nz, n0, ox, oy, oz, o0, ax, ay, az, a0, px, py, pz, p0;

  C_AbsolutePose* pose_;

private:
  void showEvent (QShowEvent* ShowEvent) override;
  void closeEvent (QCloseEvent* CloseEvent) override;
  bool eventFilter (QObject* Object, QEvent* Event) override;
private slots:
  void Taktgeber_Tick();


  void tait_extrinsic_zyx ();
  void tait_intrinsic_zyx ();
  void euler_extrinsic_zyz ();
  void euler_intrinsic_zyz ();
  void calculation_method ();
  void get_textbox_data ();
  void set_textbox_data ();
  void convert_rad_to_degree ();
  void convert_degree_to_rad ();



};

}

#endif // FRM_CAMERA_POSITIONING_POSE_H
