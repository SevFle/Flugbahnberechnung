#include "frm_object_calibration.h"
#include "ui_frm_object_calibration.h"

frm_object_calibration::frm_object_calibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_object_calibration)
{
    ui->setupUi(this);
}

frm_object_calibration::~frm_object_calibration()
{
    delete ui;
}
