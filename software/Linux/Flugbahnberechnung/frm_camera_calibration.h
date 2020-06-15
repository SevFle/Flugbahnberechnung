#ifndef FRM_CAMERA_CALIBRATION_H
#define FRM_CAMERA_CALIBRATION_H

#include <QDialog>

namespace Ui {
class frm_camera_calibration;
}

class frm_camera_calibration : public QDialog
{
    Q_OBJECT

public:
    explicit frm_camera_calibration(QWidget *parent = nullptr);
    ~frm_camera_calibration();

private:
    Ui::frm_camera_calibration *ui;
};

#endif // FRM_CAMERA_CALIBRATION_H
