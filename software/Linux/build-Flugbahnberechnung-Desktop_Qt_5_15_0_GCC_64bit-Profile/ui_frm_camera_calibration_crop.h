/********************************************************************************
** Form generated from reading UI file 'frm_camera_calibration_crop.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_CALIBRATION_CROP_H
#define UI_FRM_CAMERA_CALIBRATION_CROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_calibration_crop
{
public:
    QWidget *centralwidget;
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QLabel *lbl_img_uncropped;
    QLabel *lbl_img_cropped;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *C_frm_camera_calibration_crop)
    {
        if (C_frm_camera_calibration_crop->objectName().isEmpty())
            C_frm_camera_calibration_crop->setObjectName(QString::fromUtf8("C_frm_camera_calibration_crop"));
        C_frm_camera_calibration_crop->resize(1280, 740);
        centralwidget = new QWidget(C_frm_camera_calibration_crop);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1130, 610, 141, 31));
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(1130, 650, 141, 71));
        lbl_img_uncropped = new QLabel(centralwidget);
        lbl_img_uncropped->setObjectName(QString::fromUtf8("lbl_img_uncropped"));
        lbl_img_uncropped->setGeometry(QRect(20, 10, 541, 551));
        lbl_img_cropped = new QLabel(centralwidget);
        lbl_img_cropped->setObjectName(QString::fromUtf8("lbl_img_cropped"));
        lbl_img_cropped->setGeometry(QRect(640, 10, 541, 551));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 579, 1031, 151));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 61, 21));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 61, 21));
        label_2->setFont(font);
        C_frm_camera_calibration_crop->setCentralWidget(centralwidget);

        retranslateUi(C_frm_camera_calibration_crop);

        QMetaObject::connectSlotsByName(C_frm_camera_calibration_crop);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_camera_calibration_crop)
    {
        C_frm_camera_calibration_crop->setWindowTitle(QCoreApplication::translate("C_frm_camera_calibration_crop", "Dialog", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_camera_calibration_crop", "Exit", nullptr));
        lbl_img_uncropped->setText(QCoreApplication::translate("C_frm_camera_calibration_crop", "TextLabel", nullptr));
        lbl_img_cropped->setText(QCoreApplication::translate("C_frm_camera_calibration_crop", "TextLabel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_camera_calibration_crop", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("C_frm_camera_calibration_crop", "Height", nullptr));
        label_2->setText(QCoreApplication::translate("C_frm_camera_calibration_crop", "Width", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_calibration_crop: public Ui_C_frm_camera_calibration_crop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_CALIBRATION_CROP_H
