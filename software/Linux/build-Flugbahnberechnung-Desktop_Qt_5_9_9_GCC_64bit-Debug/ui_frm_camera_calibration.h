/********************************************************************************
** Form generated from reading UI file 'frm_camera_calibration.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_CALIBRATION_H
#define UI_FRM_CAMERA_CALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_calibration
{
public:
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;

    void setupUi(QDialog *C_frm_camera_calibration)
    {
        if (C_frm_camera_calibration->objectName().isEmpty())
            C_frm_camera_calibration->setObjectName(QStringLiteral("C_frm_camera_calibration"));
        C_frm_camera_calibration->resize(1280, 740);
        txb_zaehler = new QTextEdit(C_frm_camera_calibration);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1130, 620, 141, 31));
        bt_exit = new QPushButton(C_frm_camera_calibration);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(1130, 660, 141, 71));

        retranslateUi(C_frm_camera_calibration);

        QMetaObject::connectSlotsByName(C_frm_camera_calibration);
    } // setupUi

    void retranslateUi(QDialog *C_frm_camera_calibration)
    {
        C_frm_camera_calibration->setWindowTitle(QApplication::translate("C_frm_camera_calibration", "Dialog", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_camera_calibration", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_calibration: public Ui_C_frm_camera_calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_CALIBRATION_H
