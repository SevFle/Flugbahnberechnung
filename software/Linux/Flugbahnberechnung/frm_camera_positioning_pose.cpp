#include "frm_camera_positioning_pose.h"
#include "ui_frm_camera_positioning_pose.h"

frm_camera_positioning_pose::frm_camera_positioning_pose(QWidget *parent) :
    QDialog(parent),
{
    this->Ui = new Ui::frm_camera_positioning_pose();
    Ui->setupUi(this);
}

frm_camera_positioning_pose::~frm_camera_positioning_pose()
{
    delete ui;
}
