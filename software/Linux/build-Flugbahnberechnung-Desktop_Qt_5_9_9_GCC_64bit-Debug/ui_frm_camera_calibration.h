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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_C_frm_camera_calibration
{
public:
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
    QTextEdit *txb_count_images_to_take;
    QLabel *label_5;
    QTextEdit *txb_edge_length;
    QLabel *label_6;
    QLabel *label_7;
    QTextEdit *txb_edge_width;
    QTextEdit *txb_edge_height;
    QGroupBox *grpb_single_output;
    QTableView *tblv_single_parameters;
    QGroupBox *grpb_stereo_output;
    QTableView *tblv_stereo_output;
    QLabel *lbl_img_single_calibration;
    QLabel *lbl_img_stereo_left;
    QLabel *lbl_img_stereo_right;
    QPushButton *bt_start;
    QLabel *lbl_calibration_running;

    void setupUi(QDialog *C_frm_camera_calibration)
    {
        if (C_frm_camera_calibration->objectName().isEmpty())
            C_frm_camera_calibration->setObjectName(QStringLiteral("C_frm_camera_calibration"));
        C_frm_camera_calibration->resize(1618, 840);
        txb_zaehler = new QTextEdit(C_frm_camera_calibration);
        txb_zaehler->setObjectName(QStringLiteral("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1470, 720, 141, 31));
        bt_exit = new QPushButton(C_frm_camera_calibration);
        bt_exit->setObjectName(QStringLiteral("bt_exit"));
        bt_exit->setGeometry(QRect(1470, 760, 141, 71));
        groupBox = new QGroupBox(C_frm_camera_calibration);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 321, 821));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 110, 301, 191));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 330, 301, 191));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 550, 301, 191));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 201, 17));
        QFont font;
        font.setPointSize(14);
        label_4->setFont(font);
        txb_img_count = new QTextEdit(groupBox);
        txb_img_count->setObjectName(QStringLiteral("txb_img_count"));
        txb_img_count->setGeometry(QRect(210, 30, 104, 31));
        groupBox_2 = new QGroupBox(C_frm_camera_calibration);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 0, 271, 361));
        rb_single_calibration = new QRadioButton(groupBox_2);
        rb_single_calibration->setObjectName(QStringLiteral("rb_single_calibration"));
        rb_single_calibration->setGeometry(QRect(10, 30, 191, 23));
        rb_single_calibration->setFont(font);
        rb_stereo_calibration = new QRadioButton(groupBox_2);
        rb_stereo_calibration->setObjectName(QStringLiteral("rb_stereo_calibration"));
        rb_stereo_calibration->setGeometry(QRect(10, 60, 201, 23));
        rb_stereo_calibration->setFont(font);
        txb_count_images_to_take = new QTextEdit(groupBox_2);
        txb_count_images_to_take->setObjectName(QStringLiteral("txb_count_images_to_take"));
        txb_count_images_to_take->setGeometry(QRect(10, 130, 104, 31));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 100, 251, 21));
        label_5->setFont(font);
        txb_edge_length = new QTextEdit(groupBox_2);
        txb_edge_length->setObjectName(QStringLiteral("txb_edge_length"));
        txb_edge_length->setGeometry(QRect(10, 200, 104, 31));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 170, 251, 21));
        label_6->setFont(font);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 230, 251, 21));
        label_7->setFont(font);
        txb_edge_width = new QTextEdit(groupBox_2);
        txb_edge_width->setObjectName(QStringLiteral("txb_edge_width"));
        txb_edge_width->setGeometry(QRect(10, 260, 104, 31));
        txb_edge_height = new QTextEdit(groupBox_2);
        txb_edge_height->setObjectName(QStringLiteral("txb_edge_height"));
        txb_edge_height->setGeometry(QRect(130, 260, 104, 31));
        grpb_single_output = new QGroupBox(C_frm_camera_calibration);
        grpb_single_output->setObjectName(QStringLiteral("grpb_single_output"));
        grpb_single_output->setEnabled(false);
        grpb_single_output->setGeometry(QRect(340, 360, 271, 461));
        tblv_single_parameters = new QTableView(grpb_single_output);
        tblv_single_parameters->setObjectName(QStringLiteral("tblv_single_parameters"));
        tblv_single_parameters->setGeometry(QRect(10, 30, 251, 421));
        grpb_stereo_output = new QGroupBox(grpb_single_output);
        grpb_stereo_output->setObjectName(QStringLiteral("grpb_stereo_output"));
        grpb_stereo_output->setEnabled(false);
        grpb_stereo_output->setGeometry(QRect(0, 0, 271, 461));
        tblv_stereo_output = new QTableView(grpb_stereo_output);
        tblv_stereo_output->setObjectName(QStringLiteral("tblv_stereo_output"));
        tblv_stereo_output->setGeometry(QRect(10, 30, 251, 421));
        lbl_img_single_calibration = new QLabel(C_frm_camera_calibration);
        lbl_img_single_calibration->setObjectName(QStringLiteral("lbl_img_single_calibration"));
        lbl_img_single_calibration->setEnabled(false);
        lbl_img_single_calibration->setGeometry(QRect(650, 20, 771, 681));
        lbl_img_stereo_left = new QLabel(C_frm_camera_calibration);
        lbl_img_stereo_left->setObjectName(QStringLiteral("lbl_img_stereo_left"));
        lbl_img_stereo_left->setGeometry(QRect(650, 10, 441, 441));
        lbl_img_stereo_right = new QLabel(C_frm_camera_calibration);
        lbl_img_stereo_right->setObjectName(QStringLiteral("lbl_img_stereo_right"));
        lbl_img_stereo_right->setGeometry(QRect(1120, 10, 441, 441));
        bt_start = new QPushButton(C_frm_camera_calibration);
        bt_start->setObjectName(QStringLiteral("bt_start"));
        bt_start->setGeometry(QRect(660, 750, 141, 71));
        lbl_calibration_running = new QLabel(C_frm_camera_calibration);
        lbl_calibration_running->setObjectName(QStringLiteral("lbl_calibration_running"));
        lbl_calibration_running->setEnabled(false);
        lbl_calibration_running->setGeometry(QRect(810, 780, 361, 31));
        lbl_calibration_running->setFont(font);

        retranslateUi(C_frm_camera_calibration);

        QMetaObject::connectSlotsByName(C_frm_camera_calibration);
    } // setupUi

    void retranslateUi(QDialog *C_frm_camera_calibration)
    {
        C_frm_camera_calibration->setWindowTitle(QApplication::translate("C_frm_camera_calibration", "Dialog", Q_NULLPTR));
        bt_exit->setText(QApplication::translate("C_frm_camera_calibration", "Exit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("C_frm_camera_calibration", "Aufgenommene Bilder", Q_NULLPTR));
        label->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("C_frm_camera_calibration", "Aufgenommene Bilder", Q_NULLPTR));
        txb_img_count->setPlaceholderText(QApplication::translate("C_frm_camera_calibration", "0", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("C_frm_camera_calibration", "Parameter", Q_NULLPTR));
        rb_single_calibration->setText(QApplication::translate("C_frm_camera_calibration", "Single Calibration", Q_NULLPTR));
        rb_stereo_calibration->setText(QApplication::translate("C_frm_camera_calibration", "Stereo Calibration", Q_NULLPTR));
        txb_count_images_to_take->setPlaceholderText(QApplication::translate("C_frm_camera_calibration", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("C_frm_camera_calibration", "Anzahl  Kalibrierungsbilder", Q_NULLPTR));
        txb_edge_length->setPlaceholderText(QApplication::translate("C_frm_camera_calibration", "mm", Q_NULLPTR));
        label_6->setText(QApplication::translate("C_frm_camera_calibration", "Kantenl\303\244nge", Q_NULLPTR));
        label_7->setText(QApplication::translate("C_frm_camera_calibration", "Anzahl Kanten (B x H)", Q_NULLPTR));
        txb_edge_width->setPlaceholderText(QApplication::translate("C_frm_camera_calibration", "Breite", Q_NULLPTR));
        txb_edge_height->setPlaceholderText(QApplication::translate("C_frm_camera_calibration", "H\303\266he", Q_NULLPTR));
        grpb_single_output->setTitle(QApplication::translate("C_frm_camera_calibration", "Output", Q_NULLPTR));
        grpb_stereo_output->setTitle(QApplication::translate("C_frm_camera_calibration", "Output", Q_NULLPTR));
        lbl_img_single_calibration->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        lbl_img_stereo_left->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        lbl_img_stereo_right->setText(QApplication::translate("C_frm_camera_calibration", "TextLabel", Q_NULLPTR));
        bt_start->setText(QApplication::translate("C_frm_camera_calibration", "Start", Q_NULLPTR));
        lbl_calibration_running->setText(QApplication::translate("C_frm_camera_calibration", "Calibration being calculated. Please wait.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class C_frm_camera_calibration: public Ui_C_frm_camera_calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_CAMERA_CALIBRATION_H
