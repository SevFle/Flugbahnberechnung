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
    sources/App_main.cpp \
    sources/CSV_Datei.cpp \
    sources/GlobalObjects.cpp \
    sources/Kalmanfilter.cpp \
    sources/camera.cpp \
    sources/camera_manager.cpp \
    sources/object.cpp \
    sources/posen.cpp \
    sources/tracking.cpp \
    sources/Main.cpp \
    sources/frm_camera_calibration.cpp \
    sources/frm_camera_calibration_crop.cpp \
    sources/frm_camera_positioning.cpp \
    sources/frm_camera_positioning_pose.cpp \
    sources/frm_object_calibration.cpp \
    sources/frm_object_tracking.cpp \
    sources/frm_main.cpp

HEADERS += \
    headers/CSV_Datei.h \
    headers/GlobalObjects.h \
    headers/Kalmanfilter.h \
    headers/camera.h \
    headers/camera_manager.h \
    cuda/CudaKernels.cuh \
    cuda/kalman_cuda.cuh \
    headers/object.h \
    headers/point.h \
    headers/posen.h \
    headers/tracking.h \
    headers/Main.h \
    headers/frm_camera_calibration.h \
    headers/frm_camera_calibration_crop.h \
    headers/frm_camera_positioning.h \
    headers/frm_camera_positioning_pose.h \
    headers/frm_main.h \
    headers/frm_object_calibration.h \
    headers/frm_object_tracking.h

FORMS += \
    forms/frm_camera_calibration.ui \
    forms/frm_camera_calibration_crop.ui \
    forms/frm_camera_positioning.ui \
    forms/frm_camera_positioning_pose.ui \
    forms/frm_main.ui \
    forms/frm_object_calibration.ui \
    forms/frm_object_tracking.ui

################################# CUDA INCLUDES #################################
#CUDA_SOURCES = \
#     Code/CudaKernels.cu

#CUDA_DIR = /usr/local/cuda-10.1

#CUDA_ARCH = sm_75       # 75 RTX 2070 / GTX 1650          # 61 GTX 1080

#INCLUDEPATH += $$CUDA_DIR/include

#LIBS += -L $$CUDA_DIR/lib64 -lcudart -lcuda


############################## CUDA NVCC ############################################



# The following makes sure all path names (which often include spaces) are put between quotation marks
#CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')

#cuda.input = CUDA_SOURCES

#cuda.output = ${QMAKE_FILE_BASE}_cuda.o


#cuda.commands = $$CUDA_DIR/bin/nvcc -c -arch=$$CUDA_ARCH -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}

#cuda.dependency_type = TYPE_C

#cuda.depend_command = $$CUDA_DIR/bin/nvcc -M ${QMAKE_FILE_NAME}


#CUDA_DIR = $$system(which nvcc | sed 's,/bin/nvcc$,,')

# INCLUDEPATH += $$CUDA_DIR/include

# QMAKE_LIBDIR += $$CUDA_DIR/lib

# LIBS += -lcudart -lcuda

#cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.obj

# cuda.commands = nvcc -c -Xcompiler $$join(QMAKE_CXXFLAGS,",") $$join(INCLUDEPATH,'" -I "','-I "','"') ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}

# cuda.depends = nvcc -M -Xcompiler $$join(QMAKE_CXXFLAGS,",") $$join(INCLUDEPATH,'" -I "','-I "','"') ${QMAKE_FILE_NAME} | sed "s,^.*: ,," | sed "s,^ *,," | tr -d '\\n'

#QMAKE_EXTRA_COMPILERS += cuda

## Cuda sources
#CUDA_SOURCES += Code/CudaKernels.cu

## Path to cuda toolkit install
#CUDA_DIR      = /usr/local/cuda-10.1
## Path to header and libs files
#INCLUDEPATH  += $$CUDA_DIR/include
#QMAKE_LIBDIR += $$CUDA_DIR/lib64     # Note I'm using a 64 bits Operating system
## libs used in your code
#LIBS += -lcudart -lcuda
## GPU architecture
#CUDA_ARCH     = sm_75                # Yeah! I've a new device. Adjust with your compute capability
## Here are some NVCC flags I've always used by default.
#NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
## Prepare the extra compiler configuration (taken from the nvidia forum - i'm not an expert in this part)
#CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

#cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -g -G -arch=$$CUDA_ARCH -c $$NVCCFLAGS $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
## nvcc error printout format ever so slightly different from gcc
## http://forums.nvidia.com/index.php?showtopic=171651

#cuda.dependency_type = TYPE_C # there was a typo here. Thanks workmate!
#cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS   ${QMAKE_FILE_NAME}

#cuda.input = CUDA_SOURCES
#cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
## Tell Qt that we want add more stuff to the Makefile
#QMAKE_EXTRA_COMPILERS += cuda
CUDA_SOURCES += cuda/CudaKernels.cu

CUDA_SDK += "/usr/local/cuda-10.1"
CUDA_DIR += "/usr/local/cuda-10.1"

SYSTEM_NAME = unix
SYSTEM_TYPE = 64
CUDA_ARCH = sm_75
NVCC_OPTIONS = --use_fast_math -O2

INCLUDEPATH += $$CUDA_DIR/include

QMAKE_LIBDIR += $$CUDA_DIR/lib64/

CUDA_OBJECTS_DIR = ./

CUDA_LIBS = -lcuda -lcudart
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')

LIBS += $$CUDA_LIBS

cuda_d.input = CUDA_SOURCES
cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}.o
cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o {QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_d.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_d




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


################################################## OPENCV INCLUDE ###########################################

DISTFILES += \
  Code/CudaKernels.cu \
  Code/kalman.cuCudaKernels



unix:!macx: LIBS += -L$$PWD/../../../../../libs/opencv420/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../libs/opencv420/include
DEPENDPATH += $$PWD/../../../../../libs/opencv420/include

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 glib-2.0 gobject-2.0 gstreamer-app-1.0 gstreamer-pbutils-1.0
