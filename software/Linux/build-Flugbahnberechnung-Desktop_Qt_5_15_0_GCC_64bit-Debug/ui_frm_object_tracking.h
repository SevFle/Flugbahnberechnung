/********************************************************************************
** Form generated from reading UI file 'frm_object_tracking.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_OBJECT_TRACKING_H
#define UI_FRM_OBJECT_TRACKING_H

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

class Ui_C_frm_object_tracking
{
public:
    QWidget *centralwidget;
    QPushButton *bt_exit;
    QTextEdit *txb_zaehler;
    QGroupBox *groupBox;
    QLabel *lbl_img_left;
    QLabel *lbl_img_right;
    QPushButton *bt_start;
    QSpinBox *num_camera_id;
    QGroupBox *groupBox_2;
    QTextEdit *txb_position_z;
    QTextEdit *txb_position_x;
    QTextEdit *txb_position_y;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *txb_velocity_z;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *txb_velocity_x;
    QTextEdit *txb_velocity_y;
    QLabel *label_7;
    QLabel *lbl_thread_running;

    void setupUi(QMainWindow *C_frm_object_tracking)
    {
        if (C_frm_object_tracking->objectName().isEmpty())
            C_frm_object_tracking->setObjectName(QString::fromUtf8("C_frm_object_tracking"));
        C_frm_object_tracking->resize(1280, 740);
        centralwidget = new QWidget(C_frm_object_tracking);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(1130, 660, 141, 71));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1130, 620, 141, 31));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 1081, 491));
        lbl_img_left = new QLabel(groupBox);
        lbl_img_left->setObjectName(QString::fromUtf8("lbl_img_left"));
        lbl_img_left->setGeometry(QRect(20, 60, 500, 371));
        lbl_img_right = new QLabel(groupBox);
        lbl_img_right->setObjectName(QString::fromUtf8("lbl_img_right"));
        lbl_img_right->setGeometry(QRect(580, 60, 500, 371));
        bt_start = new QPushButton(centralwidget);
        bt_start->setObjectName(QString::fromUtf8("bt_start"));
        bt_start->setGeometry(QRect(10, 660, 141, 71));
        num_camera_id = new QSpinBox(centralwidget);
        num_camera_id->setObjectName(QString::fromUtf8("num_camera_id"));
        num_camera_id->setGeometry(QRect(170, 690, 71, 41));
        QFont font;
        font.setPointSize(14);
        num_camera_id->setFont(font);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(280, 580, 551, 151));
        txb_position_z = new QTextEdit(groupBox_2);
        txb_position_z->setObjectName(QString::fromUtf8("txb_position_z"));
        txb_position_z->setGeometry(QRect(130, 110, 141, 31));
        txb_position_x = new QTextEdit(groupBox_2);
        txb_position_x->setObjectName(QString::fromUtf8("txb_position_x"));
        txb_position_x->setGeometry(QRect(130, 30, 141, 31));
        txb_position_y = new QTextEdit(groupBox_2);
        txb_position_y->setObjectName(QString::fromUtf8("txb_position_y"));
        txb_position_y->setGeometry(QRect(130, 70, 141, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 101, 21));
        label->setFont(font);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 101, 21));
        label_2->setFont(font);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 101, 21));
        label_3->setFont(font);
        txb_velocity_z = new QTextEdit(groupBox_2);
        txb_velocity_z->setObjectName(QString::fromUtf8("txb_velocity_z"));
        txb_velocity_z->setGeometry(QRect(400, 110, 141, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 80, 101, 21));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 40, 101, 21));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(280, 120, 101, 21));
        label_6->setFont(font);
        txb_velocity_x = new QTextEdit(groupBox_2);
        txb_velocity_x->setObjectName(QString::fromUtf8("txb_velocity_x"));
        txb_velocity_x->setGeometry(QRect(400, 30, 141, 31));
        txb_velocity_y = new QTextEdit(groupBox_2);
        txb_velocity_y->setObjectName(QString::fromUtf8("txb_velocity_y"));
        txb_velocity_y->setGeometry(QRect(400, 70, 141, 31));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(170, 660, 101, 21));
        label_7->setFont(font);
        lbl_thread_running = new QLabel(centralwidget);
        lbl_thread_running->setObjectName(QString::fromUtf8("lbl_thread_running"));
        lbl_thread_running->setGeometry(QRect(10, 620, 141, 31));
        lbl_thread_running->setFont(font);
        C_frm_object_tracking->setCentralWidget(centralwidget);

        retranslateUi(C_frm_object_tracking);

        QMetaObject::connectSlotsByName(C_frm_object_tracking);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_object_tracking)
    {
        C_frm_object_tracking->setWindowTitle(QCoreApplication::translate("C_frm_object_tracking", "Dialog", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_object_tracking", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_object_tracking", "GroupBox", nullptr));
        lbl_img_left->setText(QCoreApplication::translate("C_frm_object_tracking", "TextLabel", nullptr));
        lbl_img_right->setText(QCoreApplication::translate("C_frm_object_tracking", "TextLabel", nullptr));
        bt_start->setText(QCoreApplication::translate("C_frm_object_tracking", "Start", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QCoreApplication::translate("C_frm_object_tracking", "Position [X]", nullptr));
        label_2->setText(QCoreApplication::translate("C_frm_object_tracking", "Position [Y]", nullptr));
        label_3->setText(QCoreApplication::translate("C_frm_object_tracking", "Position [Z]", nullptr));
        label_4->setText(QCoreApplication::translate("C_frm_object_tracking", "Velocity [Y]", nullptr));
        label_5->setText(QCoreApplication::translate("C_frm_object_tracking", "Velocity [X]", nullptr));
        label_6->setText(QCoreApplication::translate("C_frm_object_tracking", "Velocity [Z]", nullptr));
        label_7->setText(QCoreApplication::translate("C_frm_object_tracking", "Kamera", nullptr));
        lbl_thread_running->setText(QCoreApplication::translate("C_frm_object_tracking", "Thread running", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_object_tracking: public Ui_C_frm_object_tracking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_OBJECT_TRACKING_H
