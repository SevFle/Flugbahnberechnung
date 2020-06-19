/********************************************************************************
** Form generated from reading UI file 'frm_camera_positioning.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_POSITIONING_H
#define UI_FRM_CAMERA_POSITIONING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_positioning
{
public:
    QWidget *centralwidget;
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QGroupBox *groupBox;
    QLabel *lbl_cam_0;
    QLabel *lbl_cam_2;
    QLabel *lbl_cam_4;
    QSpinBox *num_cam_0;
    QSpinBox *num_cam_2;
    QSpinBox *num_cam_4;
    QGroupBox *groupBox_2;
    QLabel *lbl_cam_1;
    QLabel *lbl_cam_3;
    QLabel *lbl_cam_5;
    QSpinBox *num_cam_1;
    QSpinBox *num_cam_3;
    QSpinBox *num_cam_5;
    QPushButton *bt_apply;

    void setupUi(QMainWindow *C_frm_camera_positioning)
    {
        if (C_frm_camera_positioning->objectName().isEmpty())
            C_frm_camera_positioning->setObjectName(QString::fromUtf8("C_frm_camera_positioning"));
        C_frm_camera_positioning->resize(1414, 826);
        centralwidget = new QWidget(C_frm_camera_positioning);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1090, 770, 141, 31));
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(1260, 740, 141, 71));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 1251, 351));
        lbl_cam_0 = new QLabel(groupBox);
        lbl_cam_0->setObjectName(QString::fromUtf8("lbl_cam_0"));
        lbl_cam_0->setGeometry(QRect(10, 30, 331, 261));
        lbl_cam_2 = new QLabel(groupBox);
        lbl_cam_2->setObjectName(QString::fromUtf8("lbl_cam_2"));
        lbl_cam_2->setGeometry(QRect(360, 30, 331, 261));
        lbl_cam_4 = new QLabel(groupBox);
        lbl_cam_4->setObjectName(QString::fromUtf8("lbl_cam_4"));
        lbl_cam_4->setGeometry(QRect(710, 30, 331, 261));
        num_cam_0 = new QSpinBox(groupBox);
        num_cam_0->setObjectName(QString::fromUtf8("num_cam_0"));
        num_cam_0->setGeometry(QRect(20, 310, 51, 26));
        num_cam_2 = new QSpinBox(groupBox);
        num_cam_2->setObjectName(QString::fromUtf8("num_cam_2"));
        num_cam_2->setGeometry(QRect(370, 310, 51, 26));
        num_cam_4 = new QSpinBox(groupBox);
        num_cam_4->setObjectName(QString::fromUtf8("num_cam_4"));
        num_cam_4->setGeometry(QRect(720, 310, 51, 26));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 360, 1251, 351));
        lbl_cam_1 = new QLabel(groupBox_2);
        lbl_cam_1->setObjectName(QString::fromUtf8("lbl_cam_1"));
        lbl_cam_1->setGeometry(QRect(10, 30, 331, 261));
        lbl_cam_3 = new QLabel(groupBox_2);
        lbl_cam_3->setObjectName(QString::fromUtf8("lbl_cam_3"));
        lbl_cam_3->setGeometry(QRect(360, 30, 331, 261));
        lbl_cam_5 = new QLabel(groupBox_2);
        lbl_cam_5->setObjectName(QString::fromUtf8("lbl_cam_5"));
        lbl_cam_5->setGeometry(QRect(710, 30, 331, 261));
        num_cam_1 = new QSpinBox(groupBox_2);
        num_cam_1->setObjectName(QString::fromUtf8("num_cam_1"));
        num_cam_1->setGeometry(QRect(20, 310, 51, 26));
        num_cam_3 = new QSpinBox(groupBox_2);
        num_cam_3->setObjectName(QString::fromUtf8("num_cam_3"));
        num_cam_3->setGeometry(QRect(370, 310, 51, 26));
        num_cam_5 = new QSpinBox(groupBox_2);
        num_cam_5->setObjectName(QString::fromUtf8("num_cam_5"));
        num_cam_5->setGeometry(QRect(720, 310, 51, 26));
        bt_apply = new QPushButton(centralwidget);
        bt_apply->setObjectName(QString::fromUtf8("bt_apply"));
        bt_apply->setGeometry(QRect(930, 730, 141, 71));
        C_frm_camera_positioning->setCentralWidget(centralwidget);

        retranslateUi(C_frm_camera_positioning);

        QMetaObject::connectSlotsByName(C_frm_camera_positioning);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_camera_positioning)
    {
        C_frm_camera_positioning->setWindowTitle(QCoreApplication::translate("C_frm_camera_positioning", "Dialog", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_camera_positioning", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_camera_positioning", "Links", nullptr));
        lbl_cam_0->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        lbl_cam_2->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        lbl_cam_4->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("C_frm_camera_positioning", "Rechts", nullptr));
        lbl_cam_1->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        lbl_cam_3->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        lbl_cam_5->setText(QCoreApplication::translate("C_frm_camera_positioning", "TextLabel", nullptr));
        bt_apply->setText(QCoreApplication::translate("C_frm_camera_positioning", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_positioning: public Ui_C_frm_camera_positioning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_POSITIONING_H
