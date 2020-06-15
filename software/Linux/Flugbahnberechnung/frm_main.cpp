#include "frm_main.h"
#include "ui_frm_main.h"

frm_main::frm_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::frm_main)
{
    ui->setupUi(this);
}

frm_main::~frm_main()
{
    delete ui;
}

