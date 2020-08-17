/********************************************************************************
** Form generated from reading UI file 'frm_object_calibration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_OBJECT_CALIBRATION_H
#define UI_FRM_OBJECT_CALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_frm_object_calibration
{
public:
    QWidget *centralwidget;
    QLabel *lbl_src_img;
    QLabel *lbl_img_gray;
    QLabel *lbl_hsv_filtered;
    QLabel *lbl_img_contoured;
    QGroupBox *groupBox;
    QSpinBox *num_opening_iterations;
    QSpinBox *num_closing_iterations;
    QSpinBox *num_erode_iterations;
    QSpinBox *num_dilate_iterations;
    QSpinBox *num_morph_iterations;
    QSpinBox *num_morph_kernelsize;
    QSpinBox *num_dilate_kernelsize;
    QSpinBox *num_erode_kernelsize;
    QSpinBox *num_closing_kernelsize;
    QSpinBox *num_opening_kernelsize;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QSpinBox *num_gaussian_sigma;
    QSpinBox *num_gaussian_kernelsize;
    QSpinBox *num_bilateral_kernelsize;
    QSpinBox *num_bilateral_spatial;
    QSpinBox *num_bilateral_color;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QCheckBox *chkb_erode;
    QCheckBox *chkb_dilate;
    QCheckBox *chkb_morph;
    QCheckBox *chkb_bilateral;
    QGroupBox *groupBox_2;
    QSlider *sld_hue_min;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QSlider *sld_hue_max;
    QTextEdit *txb_hue_min;
    QTextEdit *txb_hue_max;
    QTextEdit *txb_saturation_min;
    QLabel *label_20;
    QSlider *sld_saturation_max;
    QTextEdit *txb_saturation_max;
    QLabel *label_21;
    QSlider *sld_saturation_min;
    QLabel *label_22;
    QSlider *sld_value_max;
    QTextEdit *txb_value_min;
    QTextEdit *txb_value_max;
    QLabel *label_23;
    QSlider *sld_value_min;
    QSlider *sld_objectsize_min;
    QLabel *label_24;
    QTextEdit *txb_objectsize_min;
    QLabel *label_25;
    QSlider *sld_objectsize_max;
    QTextEdit *txb_objectsize_max;
    QLabel *label_26;
    QGroupBox *groupBox_3;
    QLabel *label_27;
    QLabel *label_28;
    QTextEdit *txb_s_x;
    QTextEdit *txb_s_y;
    QTextEdit *txb_delta_y;
    QLabel *label_29;
    QTextEdit *txb_delta_x;
    QLabel *label_30;
    QLabel *label_31;
    QTextEdit *txb_timestamp;
    QLabel *label_33;
    QLabel *label_34;
    QTextEdit *txb_frametime;
    QTextEdit *txb_fps;
    QSpinBox *num_camera;
    QLabel *label_32;
    QPushButton *bt_exit;
    QTextEdit *txb_zaehler;
    QPushButton *bt_apply_all;
    QPushButton *bt_apply;
    QPushButton *bt_tracking;

    void setupUi(QMainWindow *C_frm_object_calibration)
    {
        if (C_frm_object_calibration->objectName().isEmpty())
            C_frm_object_calibration->setObjectName(QString::fromUtf8("C_frm_object_calibration"));
        C_frm_object_calibration->resize(1567, 832);
        centralwidget = new QWidget(C_frm_object_calibration);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lbl_src_img = new QLabel(centralwidget);
        lbl_src_img->setObjectName(QString::fromUtf8("lbl_src_img"));
        lbl_src_img->setGeometry(QRect(40, 20, 341, 291));
        lbl_img_gray = new QLabel(centralwidget);
        lbl_img_gray->setObjectName(QString::fromUtf8("lbl_img_gray"));
        lbl_img_gray->setGeometry(QRect(410, 20, 341, 291));
        lbl_hsv_filtered = new QLabel(centralwidget);
        lbl_hsv_filtered->setObjectName(QString::fromUtf8("lbl_hsv_filtered"));
        lbl_hsv_filtered->setGeometry(QRect(760, 20, 341, 291));
        lbl_img_contoured = new QLabel(centralwidget);
        lbl_img_contoured->setObjectName(QString::fromUtf8("lbl_img_contoured"));
        lbl_img_contoured->setGeometry(QRect(1120, 20, 341, 291));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 320, 341, 441));
        num_opening_iterations = new QSpinBox(groupBox);
        num_opening_iterations->setObjectName(QString::fromUtf8("num_opening_iterations"));
        num_opening_iterations->setGeometry(QRect(130, 70, 51, 31));
        QFont font;
        font.setPointSize(14);
        num_opening_iterations->setFont(font);
        num_closing_iterations = new QSpinBox(groupBox);
        num_closing_iterations->setObjectName(QString::fromUtf8("num_closing_iterations"));
        num_closing_iterations->setGeometry(QRect(130, 110, 51, 31));
        num_closing_iterations->setFont(font);
        num_erode_iterations = new QSpinBox(groupBox);
        num_erode_iterations->setObjectName(QString::fromUtf8("num_erode_iterations"));
        num_erode_iterations->setGeometry(QRect(130, 150, 51, 31));
        num_erode_iterations->setFont(font);
        num_dilate_iterations = new QSpinBox(groupBox);
        num_dilate_iterations->setObjectName(QString::fromUtf8("num_dilate_iterations"));
        num_dilate_iterations->setGeometry(QRect(130, 190, 51, 31));
        num_dilate_iterations->setFont(font);
        num_morph_iterations = new QSpinBox(groupBox);
        num_morph_iterations->setObjectName(QString::fromUtf8("num_morph_iterations"));
        num_morph_iterations->setGeometry(QRect(130, 230, 51, 31));
        num_morph_iterations->setFont(font);
        num_morph_kernelsize = new QSpinBox(groupBox);
        num_morph_kernelsize->setObjectName(QString::fromUtf8("num_morph_kernelsize"));
        num_morph_kernelsize->setGeometry(QRect(250, 230, 51, 31));
        num_morph_kernelsize->setFont(font);
        num_dilate_kernelsize = new QSpinBox(groupBox);
        num_dilate_kernelsize->setObjectName(QString::fromUtf8("num_dilate_kernelsize"));
        num_dilate_kernelsize->setGeometry(QRect(250, 190, 51, 31));
        num_dilate_kernelsize->setFont(font);
        num_erode_kernelsize = new QSpinBox(groupBox);
        num_erode_kernelsize->setObjectName(QString::fromUtf8("num_erode_kernelsize"));
        num_erode_kernelsize->setGeometry(QRect(250, 150, 51, 31));
        num_erode_kernelsize->setFont(font);
        num_closing_kernelsize = new QSpinBox(groupBox);
        num_closing_kernelsize->setObjectName(QString::fromUtf8("num_closing_kernelsize"));
        num_closing_kernelsize->setGeometry(QRect(250, 110, 51, 31));
        num_closing_kernelsize->setFont(font);
        num_opening_kernelsize = new QSpinBox(groupBox);
        num_opening_kernelsize->setObjectName(QString::fromUtf8("num_opening_kernelsize"));
        num_opening_kernelsize->setGeometry(QRect(250, 70, 51, 31));
        num_opening_kernelsize->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 40, 101, 20));
        label->setFont(font);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 40, 91, 20));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 80, 91, 20));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 120, 91, 20));
        label_6->setFont(font);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 160, 61, 20));
        label_7->setFont(font);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 200, 51, 20));
        label_8->setFont(font);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 240, 61, 20));
        label_9->setFont(font);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(130, 270, 61, 20));
        label_10->setFont(font);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 310, 81, 20));
        label_11->setFont(font);
        num_gaussian_sigma = new QSpinBox(groupBox);
        num_gaussian_sigma->setObjectName(QString::fromUtf8("num_gaussian_sigma"));
        num_gaussian_sigma->setGeometry(QRect(130, 300, 51, 31));
        num_gaussian_sigma->setFont(font);
        num_gaussian_kernelsize = new QSpinBox(groupBox);
        num_gaussian_kernelsize->setObjectName(QString::fromUtf8("num_gaussian_kernelsize"));
        num_gaussian_kernelsize->setGeometry(QRect(250, 300, 51, 31));
        num_gaussian_kernelsize->setFont(font);
        num_bilateral_kernelsize = new QSpinBox(groupBox);
        num_bilateral_kernelsize->setObjectName(QString::fromUtf8("num_bilateral_kernelsize"));
        num_bilateral_kernelsize->setGeometry(QRect(250, 390, 51, 31));
        num_bilateral_kernelsize->setFont(font);
        num_bilateral_spatial = new QSpinBox(groupBox);
        num_bilateral_spatial->setObjectName(QString::fromUtf8("num_bilateral_spatial"));
        num_bilateral_spatial->setGeometry(QRect(180, 390, 51, 31));
        num_bilateral_spatial->setFont(font);
        num_bilateral_color = new QSpinBox(groupBox);
        num_bilateral_color->setObjectName(QString::fromUtf8("num_bilateral_color"));
        num_bilateral_color->setGeometry(QRect(120, 390, 51, 31));
        num_bilateral_color->setFont(font);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(120, 370, 51, 20));
        label_12->setFont(font);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(180, 370, 61, 20));
        label_13->setFont(font);
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(40, 400, 81, 20));
        label_14->setFont(font);
        chkb_erode = new QCheckBox(groupBox);
        chkb_erode->setObjectName(QString::fromUtf8("chkb_erode"));
        chkb_erode->setGeometry(QRect(20, 160, 21, 21));
        chkb_erode->setFont(font);
        chkb_erode->setToolTipDuration(-6);
        chkb_erode->setIconSize(QSize(19, 19));
        chkb_dilate = new QCheckBox(groupBox);
        chkb_dilate->setObjectName(QString::fromUtf8("chkb_dilate"));
        chkb_dilate->setGeometry(QRect(20, 200, 21, 21));
        chkb_dilate->setFont(font);
        chkb_dilate->setToolTipDuration(-6);
        chkb_dilate->setIconSize(QSize(19, 19));
        chkb_morph = new QCheckBox(groupBox);
        chkb_morph->setObjectName(QString::fromUtf8("chkb_morph"));
        chkb_morph->setGeometry(QRect(20, 240, 21, 21));
        chkb_morph->setFont(font);
        chkb_morph->setToolTipDuration(-6);
        chkb_morph->setIconSize(QSize(19, 19));
        chkb_bilateral = new QCheckBox(groupBox);
        chkb_bilateral->setObjectName(QString::fromUtf8("chkb_bilateral"));
        chkb_bilateral->setGeometry(QRect(20, 400, 21, 21));
        chkb_bilateral->setFont(font);
        chkb_bilateral->setToolTipDuration(-6);
        chkb_bilateral->setIconSize(QSize(19, 19));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(380, 320, 461, 441));
        sld_hue_min = new QSlider(groupBox_2);
        sld_hue_min->setObjectName(QString::fromUtf8("sld_hue_min"));
        sld_hue_min->setGeometry(QRect(100, 61, 231, 16));
        sld_hue_min->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 30, 91, 20));
        label_15->setFont(font);
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 140, 91, 20));
        label_16->setFont(font);
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 240, 91, 20));
        label_17->setFont(font);
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(60, 60, 41, 21));
        QFont font1;
        font1.setPointSize(11);
        label_18->setFont(font1);
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(60, 100, 41, 21));
        label_19->setFont(font1);
        sld_hue_max = new QSlider(groupBox_2);
        sld_hue_max->setObjectName(QString::fromUtf8("sld_hue_max"));
        sld_hue_max->setGeometry(QRect(100, 100, 231, 16));
        sld_hue_max->setOrientation(Qt::Horizontal);
        txb_hue_min = new QTextEdit(groupBox_2);
        txb_hue_min->setObjectName(QString::fromUtf8("txb_hue_min"));
        txb_hue_min->setGeometry(QRect(340, 50, 104, 31));
        txb_hue_min->setFont(font1);
        txb_hue_min->setReadOnly(true);
        txb_hue_max = new QTextEdit(groupBox_2);
        txb_hue_max->setObjectName(QString::fromUtf8("txb_hue_max"));
        txb_hue_max->setGeometry(QRect(340, 90, 104, 31));
        txb_hue_max->setFont(font1);
        txb_hue_max->setReadOnly(true);
        txb_saturation_min = new QTextEdit(groupBox_2);
        txb_saturation_min->setObjectName(QString::fromUtf8("txb_saturation_min"));
        txb_saturation_min->setGeometry(QRect(340, 159, 104, 31));
        txb_saturation_min->setFont(font1);
        txb_saturation_min->setReadOnly(true);
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(60, 209, 41, 21));
        label_20->setFont(font1);
        sld_saturation_max = new QSlider(groupBox_2);
        sld_saturation_max->setObjectName(QString::fromUtf8("sld_saturation_max"));
        sld_saturation_max->setGeometry(QRect(100, 209, 231, 16));
        sld_saturation_max->setOrientation(Qt::Horizontal);
        txb_saturation_max = new QTextEdit(groupBox_2);
        txb_saturation_max->setObjectName(QString::fromUtf8("txb_saturation_max"));
        txb_saturation_max->setGeometry(QRect(340, 199, 104, 31));
        txb_saturation_max->setFont(font1);
        txb_saturation_max->setReadOnly(true);
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(60, 169, 41, 21));
        label_21->setFont(font1);
        sld_saturation_min = new QSlider(groupBox_2);
        sld_saturation_min->setObjectName(QString::fromUtf8("sld_saturation_min"));
        sld_saturation_min->setGeometry(QRect(100, 170, 231, 16));
        sld_saturation_min->setOrientation(Qt::Horizontal);
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(60, 269, 41, 21));
        label_22->setFont(font1);
        sld_value_max = new QSlider(groupBox_2);
        sld_value_max->setObjectName(QString::fromUtf8("sld_value_max"));
        sld_value_max->setGeometry(QRect(100, 309, 231, 16));
        sld_value_max->setOrientation(Qt::Horizontal);
        txb_value_min = new QTextEdit(groupBox_2);
        txb_value_min->setObjectName(QString::fromUtf8("txb_value_min"));
        txb_value_min->setGeometry(QRect(340, 259, 104, 31));
        txb_value_min->setFont(font1);
        txb_value_min->setReadOnly(true);
        txb_value_max = new QTextEdit(groupBox_2);
        txb_value_max->setObjectName(QString::fromUtf8("txb_value_max"));
        txb_value_max->setGeometry(QRect(340, 299, 104, 31));
        txb_value_max->setFont(font1);
        txb_value_max->setReadOnly(true);
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(60, 309, 41, 21));
        label_23->setFont(font1);
        sld_value_min = new QSlider(groupBox_2);
        sld_value_min->setObjectName(QString::fromUtf8("sld_value_min"));
        sld_value_min->setGeometry(QRect(100, 270, 231, 16));
        sld_value_min->setOrientation(Qt::Horizontal);
        sld_objectsize_min = new QSlider(groupBox_2);
        sld_objectsize_min->setObjectName(QString::fromUtf8("sld_objectsize_min"));
        sld_objectsize_min->setGeometry(QRect(100, 371, 231, 16));
        sld_objectsize_min->setOrientation(Qt::Horizontal);
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 341, 111, 20));
        label_24->setFont(font);
        txb_objectsize_min = new QTextEdit(groupBox_2);
        txb_objectsize_min->setObjectName(QString::fromUtf8("txb_objectsize_min"));
        txb_objectsize_min->setGeometry(QRect(340, 360, 104, 31));
        txb_objectsize_min->setFont(font1);
        txb_objectsize_min->setReadOnly(true);
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(60, 410, 41, 21));
        label_25->setFont(font1);
        sld_objectsize_max = new QSlider(groupBox_2);
        sld_objectsize_max->setObjectName(QString::fromUtf8("sld_objectsize_max"));
        sld_objectsize_max->setGeometry(QRect(100, 410, 231, 16));
        sld_objectsize_max->setOrientation(Qt::Horizontal);
        txb_objectsize_max = new QTextEdit(groupBox_2);
        txb_objectsize_max->setObjectName(QString::fromUtf8("txb_objectsize_max"));
        txb_objectsize_max->setGeometry(QRect(340, 400, 104, 31));
        txb_objectsize_max->setFont(font1);
        txb_objectsize_max->setReadOnly(true);
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(60, 370, 41, 21));
        label_26->setFont(font1);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(860, 320, 241, 321));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(20, 40, 41, 21));
        label_27->setFont(font1);
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(20, 80, 41, 21));
        label_28->setFont(font1);
        txb_s_x = new QTextEdit(groupBox_3);
        txb_s_x->setObjectName(QString::fromUtf8("txb_s_x"));
        txb_s_x->setGeometry(QRect(90, 30, 104, 31));
        txb_s_x->setFont(font1);
        txb_s_x->setReadOnly(true);
        txb_s_y = new QTextEdit(groupBox_3);
        txb_s_y->setObjectName(QString::fromUtf8("txb_s_y"));
        txb_s_y->setGeometry(QRect(90, 70, 104, 31));
        txb_s_y->setFont(font1);
        txb_s_y->setReadOnly(true);
        txb_delta_y = new QTextEdit(groupBox_3);
        txb_delta_y->setObjectName(QString::fromUtf8("txb_delta_y"));
        txb_delta_y->setGeometry(QRect(90, 150, 104, 31));
        txb_delta_y->setFont(font1);
        txb_delta_y->setReadOnly(true);
        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(20, 120, 51, 21));
        label_29->setFont(font1);
        txb_delta_x = new QTextEdit(groupBox_3);
        txb_delta_x->setObjectName(QString::fromUtf8("txb_delta_x"));
        txb_delta_x->setGeometry(QRect(90, 110, 104, 31));
        txb_delta_x->setFont(font1);
        txb_delta_x->setReadOnly(true);
        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(20, 160, 61, 21));
        label_30->setFont(font1);
        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(10, 200, 81, 21));
        label_31->setFont(font1);
        txb_timestamp = new QTextEdit(groupBox_3);
        txb_timestamp->setObjectName(QString::fromUtf8("txb_timestamp"));
        txb_timestamp->setGeometry(QRect(90, 190, 104, 31));
        txb_timestamp->setFont(font1);
        txb_timestamp->setReadOnly(true);
        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(10, 280, 81, 21));
        label_33->setFont(font1);
        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(10, 240, 81, 21));
        label_34->setFont(font1);
        txb_frametime = new QTextEdit(groupBox_3);
        txb_frametime->setObjectName(QString::fromUtf8("txb_frametime"));
        txb_frametime->setGeometry(QRect(90, 230, 104, 31));
        txb_frametime->setFont(font1);
        txb_frametime->setReadOnly(true);
        txb_fps = new QTextEdit(groupBox_3);
        txb_fps->setObjectName(QString::fromUtf8("txb_fps"));
        txb_fps->setGeometry(QRect(90, 270, 104, 31));
        txb_fps->setFont(font1);
        txb_fps->setReadOnly(true);
        num_camera = new QSpinBox(centralwidget);
        num_camera->setObjectName(QString::fromUtf8("num_camera"));
        num_camera->setGeometry(QRect(1410, 650, 71, 41));
        num_camera->setFont(font);
        label_32 = new QLabel(centralwidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(1410, 620, 101, 21));
        label_32->setFont(font);
        bt_exit = new QPushButton(centralwidget);
        bt_exit->setObjectName(QString::fromUtf8("bt_exit"));
        bt_exit->setGeometry(QRect(1410, 750, 141, 71));
        txb_zaehler = new QTextEdit(centralwidget);
        txb_zaehler->setObjectName(QString::fromUtf8("txb_zaehler"));
        txb_zaehler->setGeometry(QRect(1410, 710, 141, 31));
        txb_zaehler->setReadOnly(true);
        bt_apply_all = new QPushButton(centralwidget);
        bt_apply_all->setObjectName(QString::fromUtf8("bt_apply_all"));
        bt_apply_all->setGeometry(QRect(1260, 750, 141, 71));
        bt_apply = new QPushButton(centralwidget);
        bt_apply->setObjectName(QString::fromUtf8("bt_apply"));
        bt_apply->setGeometry(QRect(1110, 750, 141, 71));
        bt_tracking = new QPushButton(centralwidget);
        bt_tracking->setObjectName(QString::fromUtf8("bt_tracking"));
        bt_tracking->setGeometry(QRect(1410, 530, 141, 71));
        C_frm_object_calibration->setCentralWidget(centralwidget);
        bt_apply->raise();
        lbl_src_img->raise();
        lbl_img_gray->raise();
        lbl_hsv_filtered->raise();
        lbl_img_contoured->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        num_camera->raise();
        label_32->raise();
        bt_exit->raise();
        txb_zaehler->raise();
        bt_apply_all->raise();
        bt_tracking->raise();

        retranslateUi(C_frm_object_calibration);

        QMetaObject::connectSlotsByName(C_frm_object_calibration);
    } // setupUi

    void retranslateUi(QMainWindow *C_frm_object_calibration)
    {
        C_frm_object_calibration->setWindowTitle(QCoreApplication::translate("C_frm_object_calibration", "Dialog", nullptr));
        lbl_src_img->setText(QCoreApplication::translate("C_frm_object_calibration", "Originalbild", nullptr));
        lbl_img_gray->setText(QCoreApplication::translate("C_frm_object_calibration", "Originalbild", nullptr));
        lbl_hsv_filtered->setText(QCoreApplication::translate("C_frm_object_calibration", "Originalbild", nullptr));
        lbl_img_contoured->setText(QCoreApplication::translate("C_frm_object_calibration", "Originalbild", nullptr));
        groupBox->setTitle(QCoreApplication::translate("C_frm_object_calibration", "Filtering", nullptr));
        label->setText(QCoreApplication::translate("C_frm_object_calibration", "Kernel Size", nullptr));
        label_4->setText(QCoreApplication::translate("C_frm_object_calibration", "Iterations", nullptr));
        label_5->setText(QCoreApplication::translate("C_frm_object_calibration", "Opening", nullptr));
        label_6->setText(QCoreApplication::translate("C_frm_object_calibration", "Closing", nullptr));
        label_7->setText(QCoreApplication::translate("C_frm_object_calibration", "Erode", nullptr));
        label_8->setText(QCoreApplication::translate("C_frm_object_calibration", "Dilate", nullptr));
        label_9->setText(QCoreApplication::translate("C_frm_object_calibration", "Morph", nullptr));
        label_10->setText(QCoreApplication::translate("C_frm_object_calibration", "Sigma", nullptr));
        label_11->setText(QCoreApplication::translate("C_frm_object_calibration", "Gaussian", nullptr));
        label_12->setText(QCoreApplication::translate("C_frm_object_calibration", "Color", nullptr));
        label_13->setText(QCoreApplication::translate("C_frm_object_calibration", "Spatial", nullptr));
        label_14->setText(QCoreApplication::translate("C_frm_object_calibration", "Bilateral", nullptr));
        chkb_erode->setText(QString());
        chkb_dilate->setText(QString());
        chkb_morph->setText(QString());
        chkb_bilateral->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("C_frm_object_calibration", "HSV-Filter", nullptr));
        label_15->setText(QCoreApplication::translate("C_frm_object_calibration", "Hue", nullptr));
        label_16->setText(QCoreApplication::translate("C_frm_object_calibration", "Saturation", nullptr));
        label_17->setText(QCoreApplication::translate("C_frm_object_calibration", "Value", nullptr));
        label_18->setText(QCoreApplication::translate("C_frm_object_calibration", "min", nullptr));
        label_19->setText(QCoreApplication::translate("C_frm_object_calibration", "max", nullptr));
        label_20->setText(QCoreApplication::translate("C_frm_object_calibration", "max", nullptr));
        label_21->setText(QCoreApplication::translate("C_frm_object_calibration", "min", nullptr));
        label_22->setText(QCoreApplication::translate("C_frm_object_calibration", "min", nullptr));
        label_23->setText(QCoreApplication::translate("C_frm_object_calibration", "max", nullptr));
        label_24->setText(QCoreApplication::translate("C_frm_object_calibration", "Objektgr\303\266\303\237e", nullptr));
        label_25->setText(QCoreApplication::translate("C_frm_object_calibration", "max", nullptr));
        label_26->setText(QCoreApplication::translate("C_frm_object_calibration", "min", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("C_frm_object_calibration", "Image Data", nullptr));
        label_27->setText(QCoreApplication::translate("C_frm_object_calibration", "S_x", nullptr));
        label_28->setText(QCoreApplication::translate("C_frm_object_calibration", "S_y", nullptr));
        label_29->setText(QCoreApplication::translate("C_frm_object_calibration", "Delta_x", nullptr));
        label_30->setText(QCoreApplication::translate("C_frm_object_calibration", "Delta_y", nullptr));
        label_31->setText(QCoreApplication::translate("C_frm_object_calibration", "Timestamp", nullptr));
        label_33->setText(QCoreApplication::translate("C_frm_object_calibration", "FPS", nullptr));
        label_34->setText(QCoreApplication::translate("C_frm_object_calibration", "Frametime", nullptr));
        label_32->setText(QCoreApplication::translate("C_frm_object_calibration", "Kamera", nullptr));
        bt_exit->setText(QCoreApplication::translate("C_frm_object_calibration", "Exit", nullptr));
        bt_apply_all->setText(QCoreApplication::translate("C_frm_object_calibration", "Apply all", nullptr));
        bt_apply->setText(QCoreApplication::translate("C_frm_object_calibration", "Apply", nullptr));
        bt_tracking->setText(QCoreApplication::translate("C_frm_object_calibration", "Tracking", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_frm_object_calibration: public Ui_C_frm_object_calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_OBJECT_CALIBRATION_H