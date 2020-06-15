#include "frm_object_tracking.h"
#include "ui_frm_object_tracking.h"

frm_object_tracking::frm_object_tracking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frm_object_tracking)
{
    ui->setupUi(this);
}

frm_object_tracking::~frm_object_tracking()
{
    delete ui;
}
