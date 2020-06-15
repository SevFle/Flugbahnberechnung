/********************************************************************************
** Form generated from reading UI file 'frm_camera_positioning_pose.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_POSITIONING_POSE_H
#define UI_FRM_CAMERA_POSITIONING_POSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_positioning_pose
{
public:
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;

    void setupUi(QDialog *C_frm_camera_positioning_pose)
    {
        if (C_frm_camera_positioning_pose->objectName().isEmpty())
            C_frm_camera_positioning_pose->setObjectName(QStringLiteral("C_frm_camera_positioning_pose"));
        C_frm_camera_positioning_pose->resize(1280, 740);
        txb_zaehler = new QTextEdit(C_frm_camera_positioning_pose);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1120, 610, 141, 31));
        bt_exit = new QPushButton(C_frm_camera_positioning_pose);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(1120, 650, 141, 71));

        retranslateUi(C_frm_camera_positioning_pose);

        QMetaObject::connectSlotsByName(C_frm_camera_positioning_pose);
    } // setupUi

    void retranslateUi(QDialog *C_frm_camera_positioning_pose)
    {
        C_frm_camera_positioning_pose->setWindowTitle(QApplication::translate("C_frm_camera_positioning_pose", "Dialog", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_camera_positioning_pose", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_positioning_pose: public Ui_C_frm_camera_positioning_pose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_POSITIONING_POSE_H
