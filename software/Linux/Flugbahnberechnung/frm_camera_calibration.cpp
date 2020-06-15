#include "frm_camera_calibration.h"
#include "ui_frm_camera_calibration.h"

frm_camera_calibration::frm_camera_calibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_camera_calibration)
{
    ui->setupUi(this);
}

frm_camera_calibration::~frm_camera_calibration()
{
    delete ui;
}
