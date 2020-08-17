/********************************************************************************
** Form generated from reading UI file 'frm_camera_positioning_pose.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_CAMERA_POSITIONING_POSE_H
#define UI_FRM_CAMERA_POSITIONING_POSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_positioning_pose
{
public:
    QWidget *centralwidget;
    QTextEdit *txb_zaehler;
    QPushButton *bt_exit;
    QGroupBox *groupBox;
    QLabel *lbl_phi_rot;
    QTextEdit *txb_phi;
    QLabel *lbl_theta_rot;
    QTextEdit *txb_theta;
    QLabel *lbl_psi_rot;
    QTextEdit *txb_psi;
    QGroupBox *groupBox_2;
    QTextEdit *txb_transl_x;
    QLabel *lbl_psi_rot_2;
    QLabel *lbl_phi_rot_2;
    QTextEdit *txb_transl_y;
    QLabel *lbl_theta_rot_2;
    QTextEdit *txb_transl_z;
    QGroupBox *groupBox_3;
    QRadioButton *rb_tait_extrinsic_zyx;
    QLabel *label;
    QRadioButton *rb_tait_intrinisc_zyx;
    QRadioButton *rb_euler_intrinsic_zyz;
    QRadioButton *rb_euler_extrinsic_zyz;
    QLabel *label_2;
    QGroupBox *groupBox_4;
    QRadioButton *rb_unit_grad;
    QRadioButton *rb_unit_radiant;
    QGroupBox *groupBox_5;
    QTextEdit *txb_nx;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *txb_ox;
    QTextEdit *txb_ax;
    QTextEdit *txb_px;
    QTextEdit *txb_py;
    QTextEdit *txb_ay;
    QTextEdit *txb_ny;
    QTextEdit *txb_oy;
    QTextEdit *txb_pz;
    QTextEdit *txb_az;
    QTextEdit *txb_nz;
    QTextEdit *txb_oz;
    QTextEdit *txb_p0;
    QTextEdit *txb_a0;
    QTextEdit *txb_n0;
    QTextEdit *txb_o0;
    QPushButton *bt_appy;
    QSpinBox *num_camera;
    QLabel *label_7;

    void setupUi(QMainWindow *C_frm_camera_positioning_pose)
    {
        if (C_frm_camera_positioning_pose->objectName().isEmpty())
            C_frm_camera_positioning_pose->setObjectName(QString::fromUtf8("C_frm_camera_positioning_pose"));
        C_frm_camera_positioning_pose->resize(1070, 450);
        centralwidget = new QWidget(C_frm_camera_positioning_pose);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(910, 320, 141, 31));
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(910, 360, 141, 71));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 281, 161));
        lbl_phi_rot = new QLabel(groupBox);
        lbl_phi_rot->setObjectName(QString::fromUtf8("lbl_phi_rot"));
        lbl_phi_rot->setGeometry(QRect(10, 40, 111, 17));
        QFont font;
        font.setPointSize(14);
        lbl_phi_rot->setFont(font);
        txb_phi = new QTextEdit(groupBox);
        txb_phi->setObjectName(QString::fromUtf8("txb_phi"));
        txb_phi->setGeometry(QRect(140, 30, 131, 31));
        lbl_theta_rot = new QLabel(groupBox);
        lbl_theta_rot->setObjectName(QString::fromUtf8("lbl_theta_rot"));
        lbl_theta_rot->setGeometry(QRect(10, 80, 111, 17));
        lbl_theta_rot->setFont(font);
        txb_theta = new QTextEdit(groupBox);
        txb_theta->setObjectName(QString::fromUtf8("txb_theta"));
        txb_theta->setGeometry(QRect(140, 70, 131, 31));
        lbl_psi_rot = new QLabel(groupBox);
        lbl_psi_rot->setObjectName(QString::fromUtf8("lbl_psi_rot"));
        lbl_psi_rot->setGeometry(QRect(10, 120, 111, 17));
        lbl_psi_rot->setFont(font);
        txb_psi = new QTextEdit(groupBox);
        txb_psi->setObjectName(QString::fromUtf8("txb_psi"));
        txb_psi->setGeometry(QRect(140, 110, 131, 31));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 20, 281, 161));
        txb_transl_x = new QTextEdit(groupBox_2);
        txb_transl_x->setObjectName(QString::fromUtf8("txb_transl_x"));
        txb_transl_x->setGeometry(QRect(140, 30, 131, 31));
        lbl_psi_rot_2 = new QLabel(groupBox_2);
        lbl_psi_rot_2->setObjectName(QString::fromUtf8("lbl_psi_rot_2"));
        lbl_psi_rot_2->setGeometry(QRect(10, 120, 111, 17));
        lbl_psi_rot_2->setFont(font);
        lbl_phi_rot_2 = new QLabel(groupBox_2);
        lbl_phi_rot_2->setObjectName(QString::fromUtf8("lbl_phi_rot_2"));
        lbl_phi_rot_2->setGeometry(QRect(10, 40, 111, 17));
        lbl_phi_rot_2->setFont(font);
        txb_transl_y = new QTextEdit(groupBox_2);
        txb_transl_y->setObjectName(QString::fromUtf8("txb_transl_y"));
        txb_transl_y->setGeometry(QRect(140, 70, 131, 31));
        lbl_theta_rot_2 = new QLabel(groupBox_2);
        lbl_theta_rot_2->setObjectName(QString::fromUtf8("lbl_theta_rot_2"));
        lbl_theta_rot_2->setGeometry(QRect(10, 80, 111, 17));
        lbl_theta_rot_2->setFont(font);
        txb_transl_z = new QTextEdit(groupBox_2);
        txb_transl_z->setObjectName(QString::fromUtf8("txb_transl_z"));
        txb_transl_z->setGeometry(QRect(140, 110, 131, 31));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(610, 20, 441, 161));
        rb_tait_extrinsic_zyx = new QRadioButton(groupBox_3);
        rb_tait_extrinsic_zyx->setObjectName(QString::fromUtf8("rb_tait_extrinsic_zyx"));
        rb_tait_extrinsic_zyx->setGeometry(QRect(20, 70, 161, 23));
        rb_tait_extrinsic_zyx->setFont(font);
        rb_tait_extrinsic_zyx->setAutoExclusive(false);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 171, 16));
        label->setFont(font);
        rb_tait_intrinisc_zyx = new QRadioButton(groupBox_3);
        rb_tait_intrinisc_zyx->setObjectName(QString::fromUtf8("rb_tait_intrinisc_zyx"));
        rb_tait_intrinisc_zyx->setGeometry(QRect(20, 100, 161, 23));
        rb_tait_intrinisc_zyx->setFont(font);
        rb_tait_intrinisc_zyx->setAutoExclusive(false);
        rb_euler_intrinsic_zyz = new QRadioButton(groupBox_3);
        rb_euler_intrinsic_zyz->setObjectName(QString::fromUtf8("rb_euler_intrinsic_zyz"));
        rb_euler_intrinsic_zyz->setGeometry(QRect(220, 100, 161, 23));
        rb_euler_intrinsic_zyz->setFont(font);
        rb_euler_intrinsic_zyz->setAutoExclusive(false);
        rb_euler_extrinsic_zyz = new QRadioButton(groupBox_3);
        rb_euler_extrinsic_zyz->setObjectName(QString::fromUtf8("rb_euler_extrinsic_zyz"));
        rb_euler_extrinsic_zyz->setGeometry(QRect(220, 70, 161, 23));
        rb_euler_extrinsic_zyz->setFont(font);
        rb_euler_extrinsic_zyz->setAutoExclusive(false);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 40, 171, 16));
        label_2->setFont(font);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(610, 190, 441, 101));
        rb_unit_grad = new QRadioButton(groupBox_4);
        rb_unit_grad->setObjectName(QString::fromUtf8("rb_unit_grad"));
        rb_unit_grad->setGeometry(QRect(20, 50, 112, 23));
        rb_unit_grad->setFont(font);
        rb_unit_grad->setAutoExclusive(false);
        rb_unit_radiant = new QRadioButton(groupBox_4);
        rb_unit_radiant->setObjectName(QString::fromUtf8("rb_unit_radiant"));
        rb_unit_radiant->setGeometry(QRect(220, 50, 112, 23));
        rb_unit_radiant->setFont(font);
        rb_unit_radiant->setAutoExclusive(false);
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 170, 571, 261));
        txb_nx = new QTextEdit(groupBox_5);
        txb_nx->setObjectName(QString::fromUtf8("txb_nx"));
        txb_nx->setGeometry(QRect(20, 50, 101, 31));
        txb_nx->setReadOnly(true);
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 30, 67, 17));
        label_3->setFont(font);
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 30, 67, 17));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(280, 30, 67, 17));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(390, 30, 67, 17));
        label_6->setFont(font);
        txb_ox = new QTextEdit(groupBox_5);
        txb_ox->setObjectName(QString::fromUtf8("txb_ox"));
        txb_ox->setGeometry(QRect(130, 50, 101, 31));
        txb_ox->setReadOnly(true);
        txb_ax = new QTextEdit(groupBox_5);
        txb_ax->setObjectName(QString::fromUtf8("txb_ax"));
        txb_ax->setGeometry(QRect(240, 50, 101, 31));
        txb_ax->setReadOnly(true);
        txb_px = new QTextEdit(groupBox_5);
        txb_px->setObjectName(QString::fromUtf8("txb_px"));
        txb_px->setGeometry(QRect(350, 50, 101, 31));
        txb_px->setReadOnly(true);
        txb_py = new QTextEdit(groupBox_5);
        txb_py->setObjectName(QString::fromUtf8("txb_py"));
        txb_py->setGeometry(QRect(350, 90, 101, 31));
        txb_py->setReadOnly(true);
        txb_ay = new QTextEdit(groupBox_5);
        txb_ay->setObjectName(QString::fromUtf8("txb_ay"));
        txb_ay->setGeometry(QRect(240, 90, 101, 31));
        txb_ay->setReadOnly(true);
        txb_ny = new QTextEdit(groupBox_5);
        txb_ny->setObjectName(QString::fromUtf8("txb_ny"));
        txb_ny->setGeometry(QRect(20, 90, 101, 31));
        txb_ny->setReadOnly(true);
        txb_oy = new QTextEdit(groupBox_5);
        txb_oy->setObjectName(QString::fromUtf8("txb_oy"));
        txb_oy->setGeometry(QRect(130, 90, 101, 31));
        txb_oy->setReadOnly(true);
        txb_pz = new QTextEdit(groupBox_5);
        txb_pz->setObjectName(QString::fromUtf8("txb_pz"));
        txb_pz->setGeometry(QRect(350, 130, 101, 31));
        txb_pz->setReadOnly(true);
        txb_az = new QTextEdit(groupBox_5);
        txb_az->setObjectName(QString::fromUtf8("txb_az"));
        txb_az->setGeometry(QRect(240, 130, 101, 31));
        txb_az->setReadOnly(true);
        txb_nz = new QTextEdit(groupBox_5);
        txb_nz->setObjectName(QString::fromUtf8("txb_nz"));
        txb_nz->setGeometry(QRect(20, 130, 101, 31));
        txb_nz->setReadOnly(true);
        txb_oz = new QTextEdit(groupBox_5);
        txb_oz->setObjectName(QString::fromUtf8("txb_oz"));
        txb_oz->setGeometry(QRect(130, 130, 101, 31));
        txb_oz->setReadOnly(true);
        txb_p0 = new QTextEdit(groupBox_5);
        txb_p0->setObjectName(QString::fromUtf8("txb_p0"));
        txb_p0->setGeometry(QRect(350, 170, 101, 31));
        txb_p0->setReadOnly(true);
        txb_a0 = new QTextEdit(groupBox_5);
        txb_a0->setObjectName(QString::fromUtf8("txb_a0"));
        txb_a0->setGeometry(QRect(240, 170, 101, 31));
        txb_a0->setReadOnly(true);
        txb_n0 = new QTextEdit(groupBox_5);
        txb_n0->setObjectName(QString::fromUtf8("txb_n0"));
        txb_n0->setGeometry(QRect(20, 170, 101, 31));
        txb_n0->setReadOnly(true);
        txb_o0 = new QTextEdit(groupBox_5);
        txb_o0->setObjectName(QString::fromUtf8("txb_o0"));
        txb_o0->setGeometry(QRect(130, 170, 101, 31));
        txb_o0->setReadOnly(true);
        bt_appy = new QPushButton(centralwidget);
        bt_appy->setObjectName(QString::fromUtf8("bt_appy"));
        bt_appy->setGeometry(QRect(750, 360, 141, 71));
        num_camera = new QSpinBox(centralwidget);
        num_camera->setObjectName(QString::fromUtf8("num_camera"));
        num_camera->setGeometry(QRect(610, 390, 51, 31));
        num_camera->setFont(font);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(610, 370, 71, 21));
        label_7->setFont(font);
        C_frm_camera_positioning_pose->setCentralWidget(centralwidget);

        retranslateUi(C_frm_camera_positioning_pose);

        QMetaObject::connectSlotsByName(C_frm_camera_positioning_pose);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_camera_positioning_pose)
    {
        C_frm_camera_positioning_pose->setWindowTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "Dialog", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "Rotation [Grad]", nullptr));
        lbl_phi_rot->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Rot (x, phi)", nullptr));
        lbl_theta_rot->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Rot (y, theta)", nullptr));
        lbl_psi_rot->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Rot (z, psi)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "Translation [mm]", nullptr));
        lbl_psi_rot_2->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Transl. Z", nullptr));
        lbl_phi_rot_2->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Transl. X", nullptr));
        lbl_theta_rot_2->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Transl. Y", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "Methode", nullptr));
        rb_tait_extrinsic_zyx->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Extrinsisch ZYX", nullptr));
        label->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Tait-Bryan-Rotation", nullptr));
        rb_tait_intrinisc_zyx->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Intrinsisch ZY'X''", nullptr));
        rb_euler_intrinsic_zyz->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Intrinsisch ZY'Z''", nullptr));
        rb_euler_extrinsic_zyz->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Extrinsisch ZYX", nullptr));
        label_2->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Euler-Rotation", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "Absolute Pose Einheit", nullptr));
        rb_unit_grad->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Grad", nullptr));
        rb_unit_radiant->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Radiant", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("C_frm_camera_positioning_pose", "GroupBox", nullptr));
        txb_nx->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "n", nullptr));
        label_4->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "o", nullptr));
        label_5->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "a", nullptr));
        label_6->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "p", nullptr));
        txb_ox->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_ax->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_px->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_py->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_ay->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_ny->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_oy->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_pz->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_az->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_nz->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_oz->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_p0->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", nullptr));
        txb_p0->setPlaceholderText(QCoreApplication::translate("C_frm_camera_positioning_pose", "1", nullptr));
        txb_a0->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_a0->setPlaceholderText(QCoreApplication::translate("C_frm_camera_positioning_pose", "0", nullptr));
        txb_n0->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_n0->setPlaceholderText(QCoreApplication::translate("C_frm_camera_positioning_pose", "0", nullptr));
        txb_o0->setHtml(QCoreApplication::translate("C_frm_camera_positioning_pose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", nullptr));
        txb_o0->setPlaceholderText(QCoreApplication::translate("C_frm_camera_positioning_pose", "0", nullptr));
        bt_appy->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Apply", nullptr));
        label_7->setText(QCoreApplication::translate("C_frm_camera_positioning_pose", "Kamera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_positioning_pose: public Ui_C_frm_camera_positioning_pose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_POSITIONING_POSE_H
