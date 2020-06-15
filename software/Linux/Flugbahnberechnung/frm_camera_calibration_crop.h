#ifndef FRM_CAMERA_CALIBRATION_CROP_H
#define FRM_CAMERA_CALIBRATION_CROP_H

#include <QDialog>

namespace Ui {
class frm_camera_calibration_crop;
}

class frm_camera_calibration_crop : public QDialog
{
    Q_OBJECT

public:
    explicit frm_camera_calibration_crop(QWidget *parent = nullptr);
    ~frm_camera_calibration_crop();

private:
    Ui::frm_camera_calibration_crop *ui;
};

#endif // FRM_CAMERA_CALIBRATION_CROP_H
