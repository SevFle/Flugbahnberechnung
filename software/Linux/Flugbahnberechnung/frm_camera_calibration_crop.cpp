#include "frm_camera_calibration_crop.h"
#include "ui_frm_camera_calibration_crop.h"

frm_camera_calibration_crop::frm_camera_calibration_crop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_camera_calibration_crop)
{
    ui->setupUi(this);
}

frm_camera_calibration_crop::~frm_camera_calibration_crop()
{
    delete ui;
}
