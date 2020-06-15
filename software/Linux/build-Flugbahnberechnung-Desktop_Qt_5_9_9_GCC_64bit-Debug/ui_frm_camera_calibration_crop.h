/********************************************************************************
** Form generated from reading UI file 'frm_camera_calibration_crop.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_CALIBRATION_CROP_H
#define UI_FRM_CAMERA_CALIBRATION_CROP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_calibration_crop
{
public:
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QLabel *lbl_img_uncropped;
    QLabel *lbl_img_cropped;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *C_frm_camera_calibration_crop)
    {
        if (C_frm_camera_calibration_crop->objectName().isEmpty())
            C_frm_camera_calibration_crop->setObjectName(QStringLiteral("C_frm_camera_calibration_crop"));
        C_frm_camera_calibration_crop->resize(1280, 740);
        txb_zaehler = new QTextEdit(C_frm_camera_calibration_crop);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1130, 610, 141, 31));
        bt_exit = new QPushButton(C_frm_camera_calibration_crop);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(1130, 650, 141, 71));
        lbl_img_uncropped = new QLabel(C_frm_camera_calibration_crop);
        lbl_img_uncropped->setObjectName(QStringLiteral("lbl_img_uncropped"));
        lbl_img_uncropped->setGeometry(QRect(20, 10, 541, 551));
        lbl_img_cropped = new QLabel(C_frm_camera_calibration_crop);
        lbl_img_cropped->setObjectName(QStringLiteral("lbl_img_cropped"));
        lbl_img_cropped->setGeometry(QRect(640, 10, 541, 551));
        groupBox = new QGroupBox(C_frm_camera_calibration_crop);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 579, 1031, 151));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 61, 21));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 61, 21));
        label_2->setFont(font);

        retranslateUi(C_frm_camera_calibration_crop);

        QMetaObject::connectSlotsByName(C_frm_camera_calibration_crop);
    } // setupUi

    void retranslateUi(QDialog *C_frm_camera_calibration_crop)
    {
        C_frm_camera_calibration_crop->setWindowTitle(QApplication::translate("C_frm_camera_calibration_crop", "Dialog", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_camera_calibration_crop", "Exit", Q_NULLPTR));
        lbl_img_uncropped->setText(QApplication::translate("C_frm_camera_calibration_crop", "TextLabel", Q_NULLPTR));
        lbl_img_cropped->setText(QApplication::translate("C_frm_camera_calibration_crop", "TextLabel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("C_frm_camera_calibration_crop", "GroupBox", Q_NULLPTR));
        label->setText(QApplication::translate("C_frm_camera_calibration_crop", "Height", Q_NULLPTR));
        label_2->setText(QApplication::translate("C_frm_camera_calibration_crop", "Width", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_calibration_crop: public Ui_C_frm_camera_calibration_crop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_CALIBRATION_CROP_H
