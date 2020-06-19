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
    Code/CudaKernels.h \
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


#CUDA Compilation relevant
#CUDA_SOURCES += Code/CudaKernels.cu
#CUDA_SDK = -L$$PWD/../../../../../../../usr/local/cuda-10.1/
#CUDA_DIR = -L$$PWD/../../../../../../../usr/local/cuda-10.1/

#unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart

#INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/lib64
#DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/lib64


#INCLUDEPATH += $$CUDA_DIR/include

#LIBS += $$CUDA_DIR/lib64/

#CUDA_OBJECTS_DIR = ./

#CUDA_LIBS = -lcuda -lcudart

#CUDA_INC = $$join(INCLUDEPATH, '" -I"','-I"','"')
#LIBS += $$CUDA_LIBS

##CONFIG(debug, debug|release){
#{
###DEBUG
#cuda_d.input = CUDA_SOURCES
#cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
##cuda.output = ${QMAKE_FILE_BASE}.o
#cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$ SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#cuda_d.dependency_type = TYPE_C
#QMAKE_EXTRA_COMPILERS += cuda_d
#}
#else{
###RELEASE
#cuda_.input = CUDA_SOURCES
#cuda_.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
#cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#cuda.dependency_type = TYPE_C
#QMAKE_EXTRA_COMPILERS += cuda

#}
CUDA_SOURCES = \
              Code/CudaKernels.cu
CUDA_DIR = /usr/local/cuda-10.1

CUDA_ARCH = sm_75 # as supported by the Tegra K1

INCLUDEPATH += $$CUDA_DIR/include

LIBS += -L $$CUDA_DIR/lib64 -lcudart -lcuda

osx: LIBS += -F/Library/Frameworks -framework CUDA

cuda.commands = $$CUDA_DIR/bin/nvcc -c -arch=$$CUDA_ARCH -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}

cuda.dependency_type = TYPE_C

cuda.depend_command = $$CUDA_DIR/bin/nvcc -M ${QMAKE_FILE_NAME}

cuda.input = CUDA_SOURCES

cuda.output = ${QMAKE_FILE_BASE}_cuda.o

QMAKE_EXTRA_COMPILERS += cuda




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
  Code/CudaKernels.cu \
  Code/kalman.cu



unix:!macx: LIBS += -L$$PWD/../../../../../libs/opencv420/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../libs/opencv420/include
DEPENDPATH += $$PWD/../../../../../libs/opencv420/include
