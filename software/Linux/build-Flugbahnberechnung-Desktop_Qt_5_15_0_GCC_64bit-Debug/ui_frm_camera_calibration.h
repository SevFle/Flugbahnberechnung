/********************************************************************************
** Form generated from reading UI file 'frm_camera_calibration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_CALIBRATION_H
#define UI_FRM_CAMERA_CALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_calibration
{
public:
    QWidget *centralwidget;
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *txb_img_count;
    QGroupBox *groupBox_2;
    QRadioButton *rb_single_calibration;
    QRadioButton *rb_stereo_calibration;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *txb_edge_length;
    QLineEdit *txb_edge_width;
    QLineEdit *txb_edge_height;
    QLineEdit *txb_usrInput_images;
    QGroupBox *grpb_single_output;
    QTableView *tblv_single_parameters;
    QGroupBox *grpb_stereo_output;
    QTableView *tblv_stereo_output;
    QLabel *lbl_img_single_calibration;
    QLabel *lbl_img_stereo_left;
    QLabel *lbl_img_stereo_right;
    QPushButton *bt_start;
    QLabel *lbl_calibration_running;
    QSpinBox *num_camera_id;
    QPushButton *bt_photo;

    void setupUi(QMainWindow *C_frm_camera_calibration)
    {
        if (C_frm_camera_calibration->objectName().isEmpty())
            C_frm_camera_calibration->setObjectName(QString::fromUtf8("C_frm_camera_calibration"));
        C_frm_camera_calibration->resize(1618, 840);
        centralwidget = new QWidget(C_frm_camera_calibration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1470, 720, 141, 31));
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(1470, 760, 141, 71));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 321, 821));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 110, 301, 191));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 330, 301, 191));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 550, 301, 191));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 40, 201, 17));
        QFont font;
        font.setPointSize(14);
        label_4->setFont(font);
        txb_img_count = new QTextEdit(groupBox);
        txb_img_count->setObjectName(QString::fromUtf8("txb_img_count"));
        txb_img_count->setGeometry(QRect(210, 30, 104, 31));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 0, 271, 361));
        rb_single_calibration = new QRadioButton(groupBox_2);
        rb_single_calibration->setObjectName(QString::fromUtf8("rb_single_calibration"));
        rb_single_calibration->setGeometry(QRect(10, 30, 191, 23));
        rb_single_calibration->setFont(font);
        rb_stereo_calibration = new QRadioButton(groupBox_2);
        rb_stereo_calibration->setObjectName(QString::fromUtf8("rb_stereo_calibration"));
        rb_stereo_calibration->setGeometry(QRect(10, 60, 201, 23));
        rb_stereo_calibration->setFont(font);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 100, 251, 21));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 170, 251, 21));
        label_6->setFont(font);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 230, 251, 21));
        label_7->setFont(font);
        txb_edge_length = new QLineEdit(groupBox_2);
        txb_edge_length->setObjectName(QString::fromUtf8("txb_edge_length"));
        txb_edge_length->setGeometry(QRect(10, 200, 101, 31));
        txb_edge_width = new QLineEdit(groupBox_2);
        txb_edge_width->setObjectName(QString::fromUtf8("txb_edge_width"));
        txb_edge_width->setGeometry(QRect(10, 270, 101, 31));
        txb_edge_height = new QLineEdit(groupBox_2);
        txb_edge_height->setObjectName(QString::fromUtf8("txb_edge_height"));
        txb_edge_height->setGeometry(QRect(130, 270, 91, 31));
        txb_usrInput_images = new QLineEdit(groupBox_2);
        txb_usrInput_images->setObjectName(QString::fromUtf8("txb_usrInput_images"));
        txb_usrInput_images->setGeometry(QRect(10, 130, 101, 31));
        grpb_single_output = new QGroupBox(centralwidget);
        grpb_single_output->setObjectName(QString::fromUtf8("grpb_single_output"));
        grpb_single_output->setEnabled(false);
        grpb_single_output->setGeometry(QRect(340, 360, 271, 461));
        tblv_single_parameters = new QTableView(grpb_single_output);
        tblv_single_parameters->setObjectName(QString::fromUtf8("tblv_single_parameters"));
        tblv_single_parameters->setGeometry(QRect(10, 30, 251, 421));
        grpb_stereo_output = new QGroupBox(grpb_single_output);
        grpb_stereo_output->setObjectName(QString::fromUtf8("grpb_stereo_output"));
        grpb_stereo_output->setEnabled(false);
        grpb_stereo_output->setGeometry(QRect(0, 0, 271, 461));
        tblv_stereo_output = new QTableView(grpb_stereo_output);
        tblv_stereo_output->setObjectName(QString::fromUtf8("tblv_stereo_output"));
        tblv_stereo_output->setGeometry(QRect(10, 30, 251, 421));
        lbl_img_single_calibration = new QLabel(centralwidget);
        lbl_img_single_calibration->setObjectName(QString::fromUtf8("lbl_img_single_calibration"));
        lbl_img_single_calibration->setEnabled(false);
        lbl_img_single_calibration->setGeometry(QRect(650, 20, 771, 681));
        lbl_img_stereo_left = new QLabel(centralwidget);
        lbl_img_stereo_left->setObjectName(QString::fromUtf8("lbl_img_stereo_left"));
        lbl_img_stereo_left->setGeometry(QRect(650, 10, 441, 441));
        lbl_img_stereo_right = new QLabel(centralwidget);
        lbl_img_stereo_right->setObjectName(QString::fromUtf8("lbl_img_stereo_right"));
        lbl_img_stereo_right->setGeometry(QRect(1120, 10, 441, 441));
        bt_start = new QPushButton(centralwidget);
        bt_start->setObjectName(QString::fromUtf8("bt_start"));
        bt_start->setGeometry(QRect(1320, 760, 141, 71));
        lbl_calibration_running = new QLabel(centralwidget);
        lbl_calibration_running->setObjectName(QString::fromUtf8("lbl_calibration_running"));
        lbl_calibration_running->setEnabled(false);
        lbl_calibration_running->setGeometry(QRect(810, 780, 361, 31));
        lbl_calibration_running->setFont(font);
        num_camera_id = new QSpinBox(centralwidget);
        num_camera_id->setObjectName(QString::fromUtf8("num_camera_id"));
        num_camera_id->setGeometry(QRect(660, 715, 71, 31));
        num_camera_id->setFont(font);
        bt_photo = new QPushButton(centralwidget);
        bt_photo->setObjectName(QString::fromUtf8("bt_photo"));
        bt_photo->setGeometry(QRect(650, 750, 141, 71));
        C_frm_camera_calibration->setCentralWidget(centralwidget);

        retranslateUi(C_frm_camera_calibration);

        QMetaObject::connectSlotsByName(C_frm_camera_calibration);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_camera_calibration)
    {
        C_frm_camera_calibration->setWindowTitle(QCoreApplication::translate("C_frm_camera_calibration", "Dialog", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_camera_calibration", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_camera_calibration", "Aufgenommene Bilder", nullptr));
        label->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("C_frm_camera_calibration", "Aufgenommene Bilder", nullptr));
        txb_img_count->setPlaceholderText(QCoreApplication::translate("C_frm_camera_calibration", "0", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("C_frm_camera_calibration", "Parameter", nullptr));
        rb_single_calibration->setText(QCoreApplication::translate("C_frm_camera_calibration", "Single Calibration", nullptr));
        rb_stereo_calibration->setText(QCoreApplication::translate("C_frm_camera_calibration", "Stereo Calibration", nullptr));
        label_5->setText(QCoreApplication::translate("C_frm_camera_calibration", "Anzahl  Kalibrierungsbilder", nullptr));
        label_6->setText(QCoreApplication::translate("C_frm_camera_calibration", "Kantenl\303\244nge", nullptr));
        label_7->setText(QCoreApplication::translate("C_frm_camera_calibration", "Anzahl Kanten (B x H)", nullptr));
        grpb_single_output->setTitle(QCoreApplication::translate("C_frm_camera_calibration", "Output", nullptr));
        grpb_stereo_output->setTitle(QCoreApplication::translate("C_frm_camera_calibration", "Output", nullptr));
        lbl_img_single_calibration->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        lbl_img_stereo_left->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        lbl_img_stereo_right->setText(QCoreApplication::translate("C_frm_camera_calibration", "TextLabel", nullptr));
        bt_start->setText(QCoreApplication::translate("C_frm_camera_calibration", "Start", nullptr));
        lbl_calibration_running->setText(QCoreApplication::translate("C_frm_camera_calibration", "Calibration being calculated. Please wait.", nullptr));
        bt_photo->setText(QCoreApplication::translate("C_frm_camera_calibration", "Bild aufnehmen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_calibration: public Ui_C_frm_camera_calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_CALIBRATION_H
