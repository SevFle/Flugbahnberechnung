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
    Code/Camera_unmanaged.cpp \
    Code/GlobalObjects.cpp \
    Code/Kalmanfilter.cpp \
    Code/OpenCV_unmanaged.cpp \
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
    Code/Camera_unmanaged.h \
    Code/CudaKernels.cuh \
    Code/GlobalObjects.h \
    Code/Kalmanfilter.h \
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

# Cuda sources
CUDA_SOURCES += CudaKernels.cu \
                kalman.cu

# Path to cuda toolkit install
CUDA_DIR      = $$PWD/../../../../../../../usr/local/cuda-10.1
# Path to header and libs files
INCLUDEPATH  += $$PWD/../../../../../../../usr/local/cuda-10.1/include
QMAKE_LIBDIR += $$PWD/../../../../../../../usr/local/cuda-10.1/lib64     # Note I'm using a 64 bits Operating system
# libs used in your code
LIBS += -lcudart -lcuda
# GPU architecture
CUDA_ARCH     = sm_75                # Yeah! I've a new device. Adjust with your compute capability
# Here are some NVCC flags I've always used by default.
NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

# Prepare the extra compiler configuration (taken from the nvidia forum - i'm not an expert in this part)
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS \
                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
                2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
# nvcc error printout format ever so slightly different from gcc
# http://forums.nvidia.com/index.php?showtopic=171651

cuda.dependency_type = TYPE_C # there was a typo here. Thanks workmate!
cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS   ${QMAKE_FILE_NAME}

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cuda


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/cuda-10.1/include

DISTFILES += \
  Code/CudaKernels.cu \
  Code/kalman.cu


unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/release/ -lcudart
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/debug/ -lcudart
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/lib64
DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/lib64
