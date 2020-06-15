#ifndef FRM_CAMERA_POSITIONING_POSE_H
#define FRM_CAMERA_POSITIONING_POSE_H

#include <QDialog>

namespace Ui {
class frm_camera_positioning_pose;
}

class frm_camera_positioning_pose : public QDialog
{
    Q_OBJECT

public:
    explicit frm_camera_positioning_pose(QWidget *parent = nullptr);
    ~frm_camera_positioning_pose();

private:
    Ui::frm_camera_positioning_pose *ui;
};

#endif // FRM_CAMERA_POSITIONING_POSE_H
