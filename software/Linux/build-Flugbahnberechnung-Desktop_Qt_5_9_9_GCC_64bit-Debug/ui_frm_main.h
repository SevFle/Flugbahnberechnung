/********************************************************************************
** Form generated from reading UI file 'frm_main.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_MAIN_H
#define UI_FRM_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_Main
{
public:
    QWidget *centralwidget;
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QSpinBox *num_cameras;
    QPushButton *bt_apply;
    QPushButton *bt_tracking;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *bt_camera_calibration;
    QPushButton *bt_camera_positioning;
    QPushButton *bt_camera_pose;

    void setupUi(QMainWindow *C_frm_Main)
    {
        if (C_frm_Main->objectName().isEmpty())
            C_frm_Main->setObjectName(QStringLiteral("C_frm_Main"));
        C_frm_Main->resize(421, 539);
        centralwidget = new QWidget(C_frm_Main);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(240, 410, 141, 41));
        QFont font;
        font.setPointSize(14);
        txb_zaehler->setFont(font);
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(240, 450, 141, 71));
        num_cameras = new QSpinBox(centralwidget);
        num_cameras->setObjectName(QStringLiteral("num_cameras"));
        num_cameras->setGeometry(QRect(10, 410, 141, 41));
        num_cameras->setFont(font);
        bt_apply = new QPushButton(centralwidget);
        bt_apply->setObjectName(QStringLiteral("bt_apply"));
        bt_apply->setGeometry(QRect(10, 450, 141, 71));
        bt_tracking = new QPushButton(centralwidget);
        bt_tracking->setObjectName(QStringLiteral("bt_tracking"));
        bt_tracking->setEnabled(false);
        bt_tracking->setGeometry(QRect(10, 10, 181, 71));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(230, 10, 171, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        bt_camera_calibration = new QPushButton(verticalLayoutWidget);
        bt_camera_calibration->setObjectName(QStringLiteral("bt_camera_calibration"));
        bt_camera_calibration->setEnabled(false);

        verticalLayout->addWidget(bt_camera_calibration);

        bt_camera_positioning = new QPushButton(verticalLayoutWidget);
        bt_camera_positioning->setObjectName(QStringLiteral("bt_camera_positioning"));
        bt_camera_positioning->setEnabled(false);

        verticalLayout->addWidget(bt_camera_positioning);

        bt_camera_pose = new QPushButton(verticalLayoutWidget);
        bt_camera_pose->setObjectName(QStringLiteral("bt_camera_pose"));
        bt_camera_pose->setEnabled(false);

        verticalLayout->addWidget(bt_camera_pose);

        C_frm_Main->setCentralWidget(centralwidget);

        retranslateUi(C_frm_Main);

        QMetaObject::connectSlotsByName(C_frm_Main);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_Main)
    {
        C_frm_Main->setWindowTitle(QApplication::translate("C_frm_Main", "Main", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_Main", "Exit", Q_NULLPTR));
        bt_apply->setText(QApplication::translate("C_frm_Main", "Apply", Q_NULLPTR));
        bt_tracking->setText(QApplication::translate("C_frm_Main", "Tracking", Q_NULLPTR));
        bt_camera_calibration->setText(QApplication::translate("C_frm_Main", "Kamerakalibrierung", Q_NULLPTR));
        bt_camera_positioning->setText(QApplication::translate("C_frm_Main", "Kamerapositionierung", Q_NULLPTR));
        bt_camera_pose->setText(QApplication::translate("C_frm_Main", "Kameraposen", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_Main: public Ui_C_frm_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_MAIN_H
