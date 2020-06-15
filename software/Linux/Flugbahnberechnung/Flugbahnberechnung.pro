QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App_main.cpp \
    Code/CSV_Datei.cpp \
    Code/Camera_managed.cpp \
    Code/Camera_unmanaged.cpp \
    Code/GlobalObjects.cpp \
    Code/Kalmanfilter.cpp \
    Code/Main.cpp \
    Code/OpenCV_unmanaged.cpp \
    Code/frm_Camera_Calibration.cpp \
    Code/frm_Camera_Calibration_crop.cpp \
    Code/frm_Camera_Positioning.cpp \
    Code/frm_Camera_Positioning_Pose.cpp \
    Code/frm_Main.cpp \
    Code/frm_Object_Calibration.cpp \
    Code/frm_Object_Tracking.cpp \
    Code/object.cpp \
    Code/posen.cpp \
    Code/tracking.cpp \
    Main.cpp \
    frm_camera_calibration.cpp \
    frm_camera_calibration_crop.cpp \
    frm_camera_positioning.cpp \
    frm_camera_positioning_pose.cpp \
    frm_object_calibration.cpp \
    frm_object_tracking.cpp \
    frm_main.cpp

HEADERS += \
    Code/CSV_Datei.h \
    Code/Camera_managed.h \
    Code/Camera_unmanaged.h \
    Code/CudaKernels.cuh \
    Code/GlobalObjects.h \
    Code/Kalmanfilter.h \
    Code/Main.h \
    Code/frm_Camera_Calibration.h \
    Code/frm_Camera_Calibration_crop.h \
    Code/frm_Camera_Positioning.h \
    Code/frm_Camera_Positioning_Pose.h \
    Code/frm_Main.h \
    Code/frm_Object_Calibration.h \
    Code/frm_Object_Tracking.h \
    Code/kalman_cuda.cuh \
    Code/object.h \
    Code/opencv_unmanaged.h \
    Code/point.h \
    Code/posen.h \
    Code/tracking.h \
    Main.h \
    frm_camera_calibration.h \
    frm_camera_calibration_crop.h \
    frm_camera_positioning.h \
    frm_camera_positioning_pose.h \
    frm_main.h \
    frm_object_calibration.h \
    frm_object_tracking.h

FORMS += \
    frm_camera_calibration.ui \
    frm_camera_calibration_crop.ui \
    frm_camera_positioning.ui \
    frm_camera_positioning_pose.ui \
    frm_main.ui \
    frm_object_calibration.ui \
    frm_object_tracking.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/include/opencv/4_2_0/install/include
LIBS += -L"/usr/include/opencv/4_2_0/install/x64/vc15/lib" -lopencv_world420d



DISTFILES += \
  Code/CudaKernels.cu \
  Code/kalman.cu
