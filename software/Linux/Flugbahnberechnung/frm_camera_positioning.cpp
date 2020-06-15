#include "frm_camera_positioning.h"
#include "ui_frm_camera_positioning.h"

frm_camera_positioning::frm_camera_positioning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_camera_positioning)
{
    ui->setupUi(this);
}

frm_camera_positioning::~frm_camera_positioning()
{
    delete ui;
}
