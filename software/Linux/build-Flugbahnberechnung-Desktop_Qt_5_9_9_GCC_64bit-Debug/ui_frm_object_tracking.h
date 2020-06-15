/********************************************************************************
** Form generated from reading UI file 'frm_object_tracking.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_OBJECT_TRACKING_H
#define UI_FRM_OBJECT_TRACKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_C_frm_object_tracking
{
public:
    QPushButton *bt_exit;
    QTextEdit *txb_zaehler;
    QGroupBox *groupBox;
    QLabel *lbl_img_left;
    QLabel *lbl_img_right;
    QPushButton *bt_start;
    QSpinBox *spinBox;
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

    void setupUi(QDialog *C_frm_object_tracking)
    {
        if (C_frm_object_tracking->objectName().isEmpty())
            C_frm_object_tracking->setObjectName(QStringLiteral("C_frm_object_tracking"));
        C_frm_object_tracking->resize(1280, 740);
        bt_exit = new QPushButton(C_frm_object_tracking);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(1130, 660, 141, 71));
        txb_zaehler = new QTextEdit(C_frm_object_tracking);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1130, 620, 141, 31));
        groupBox = new QGroupBox(C_frm_object_tracking);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 1081, 491));
        lbl_img_left = new QLabel(groupBox);
        lbl_img_left->setObjectName(QStringLiteral("lbl_img_left"));
        lbl_img_left->setGeometry(QRect(20, 60, 500, 371));
        lbl_img_right = new QLabel(groupBox);
        lbl_img_right->setObjectName(QStringLiteral("lbl_img_right"));
        lbl_img_right->setGeometry(QRect(580, 60, 500, 371));
        bt_start = new QPushButton(C_frm_object_tracking);
        bt_start->setObjectName(QStringLiteral("bt_start"));
        bt_start->setGeometry(QRect(10, 660, 141, 71));
        spinBox = new QSpinBox(C_frm_object_tracking);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(170, 690, 71, 41));
        QFont font;
        font.setPointSize(14);
        spinBox->setFont(font);
        groupBox_2 = new QGroupBox(C_frm_object_tracking);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(280, 580, 551, 151));
        txb_position_z = new QTextEdit(groupBox_2);
        txb_position_z->setObjectName(QStringLiteral("txb_position_z"));
        txb_position_z->setGeometry(QRect(130, 110, 141, 31));
        txb_position_x = new QTextEdit(groupBox_2);
        txb_position_x->setObjectName(QStringLiteral("txb_position_x"));
        txb_position_x->setGeometry(QRect(130, 30, 141, 31));
        txb_position_y = new QTextEdit(groupBox_2);
        txb_position_y->setObjectName(QStringLiteral("txb_position_y"));
        txb_position_y->setGeometry(QRect(130, 70, 141, 31));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 101, 21));
        label->setFont(font);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 101, 21));
        label_2->setFont(font);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 120, 101, 21));
        label_3->setFont(font);
        txb_velocity_z = new QTextEdit(groupBox_2);
        txb_velocity_z->setObjectName(QStringLiteral("txb_velocity_z"));
        txb_velocity_z->setGeometry(QRect(400, 110, 141, 31));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 80, 101, 21));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 40, 101, 21));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(280, 120, 101, 21));
        label_6->setFont(font);
        txb_velocity_x = new QTextEdit(groupBox_2);
        txb_velocity_x->setObjectName(QStringLiteral("txb_velocity_x"));
        txb_velocity_x->setGeometry(QRect(400, 30, 141, 31));
        txb_velocity_y = new QTextEdit(groupBox_2);
        txb_velocity_y->setObjectName(QStringLiteral("txb_velocity_y"));
        txb_velocity_y->setGeometry(QRect(400, 70, 141, 31));
        label_7 = new QLabel(C_frm_object_tracking);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(170, 660, 101, 21));
        label_7->setFont(font);

        retranslateUi(C_frm_object_tracking);

        QMetaObject::connectSlotsByName(C_frm_object_tracking);
    } // setupUi

    void retranslateUi(QDialog *C_frm_object_tracking)
    {
        C_frm_object_tracking->setWindowTitle(QApplication::translate("C_frm_object_tracking", "Dialog", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_object_tracking", "Exit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("C_frm_object_tracking", "GroupBox", Q_NULLPTR));
        lbl_img_left->setText(QApplication::translate("C_frm_object_tracking", "TextLabel", Q_NULLPTR));
        lbl_img_right->setText(QApplication::translate("C_frm_object_tracking", "TextLabel", Q_NULLPTR));
        bt_start->setText(QApplication::translate("C_frm_object_tracking", "Start", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label->setText(QApplication::translate("C_frm_object_tracking", "Position [X]", Q_NULLPTR));
        label_2->setText(QApplication::translate("C_frm_object_tracking", "Position [Y]", Q_NULLPTR));
        label_3->setText(QApplication::translate("C_frm_object_tracking", "Position [Z]", Q_NULLPTR));
        label_4->setText(QApplication::translate("C_frm_object_tracking", "Velocity [Y]", Q_NULLPTR));
        label_5->setText(QApplication::translate("C_frm_object_tracking", "Velocity [X]", Q_NULLPTR));
        label_6->setText(QApplication::translate("C_frm_object_tracking", "Velocity [Z]", Q_NULLPTR));
        label_7->setText(QApplication::translate("C_frm_object_tracking", "Kamera", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_object_tracking: public Ui_C_frm_object_tracking {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_OBJECT_TRACKING_H
