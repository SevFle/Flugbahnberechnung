#ifndef FRM_CAMERA_POSITIONING_H
#define FRM_CAMERA_POSITIONING_H

#include <QDialog>

namespace Ui {
class frm_camera_positioning;
}

class frm_camera_positioning : public QDialog
{
    Q_OBJECT

public:
    explicit frm_camera_positioning(QWidget *parent = nullptr);
    ~frm_camera_positioning();

private:
    Ui::frm_camera_positioning *ui;
};

#endif // FRM_CAMERA_POSITIONING_H
