#ifndef FRM_OBJECT_CALIBRATION_H
#define FRM_OBJECT_CALIBRATION_H

#include <QDialog>

namespace Ui {
class frm_object_calibration;
}

class frm_object_calibration : public QDialog
{
    Q_OBJECT

public:
    explicit frm_object_calibration(QWidget *parent = nullptr);
    ~frm_object_calibration();

private:
    Ui::frm_object_calibration *ui;
};

#endif // FRM_OBJECT_CALIBRATION_H
