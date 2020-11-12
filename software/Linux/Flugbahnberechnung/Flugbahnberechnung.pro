QT       += core gui
QT       += datavisualization
QT       += quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SYSTEM_TYPE = 64
DESTDIR     = $$system(pwd)
#CUDA_OBJECTS_DIR = ./
OBJECTS_DIR = $$DESTDIR/Obj



############################################### CUDA SOURCES ################################################
#CUDA_SOURCES += cuda/cudaKalman.cu

SOURCES += \
  sources/Etc/mathhelper.cpp \
  sources/Etc/plotter.cpp \
  sources/Etc/App_main.cpp \
  sources/Etc/GlobalObjects.cpp \
  sources/Etc/watchdog.cpp \
  sources/Etc/object.cpp \
  sources/Etc/Main.cpp \
  sources/CSV_Manager/loadmanager.cpp \
  sources/CSV_Manager/savemanager.cpp \
  sources/CSV_Manager/CSV_Datei.cpp \
  sources/Roboter/robot.cpp \
  sources/Roboter/robotmanager.cpp \
  sources/Roboter/posen.cpp \
  sources/Bildverarbeitung/camera2.cpp \
  sources/Bildverarbeitung/imagefilter.cpp \
  sources/Bildverarbeitung/camera_manager.cpp \
  sources/Positionsbestimmung/trackingManager.cpp \
  sources/Positionsbestimmung/Kalmanfilter.cpp \
  #sources/Positionsbestimmung/kalmanoncuda.cpp \
  sources/Forms/frm_camera_calibration.cpp \
  sources/Forms/frm_camera_positioning.cpp \
  sources/Forms/frm_camera_positioning_pose.cpp \
  sources/Forms/frm_object_calibration.cpp \
  sources/Forms/frm_object_tracking.cpp \
  sources/Forms/frm_main.cpp \
  sources/Forms/frm_robot_calibration.cpp

HEADERS += \
headers/Etc/mathhelper.h \
headers/Etc/plotter.h \
headers/Etc/GlobalObjects.h \
headers/Etc/watchdog.h \
headers/Etc/object.h \
headers/Etc/Main.h \
headers/CSV_Manager/loadmanager.h \
headers/CSV_Manager/savemanager.h \
headers/CSV_Manager/CSV_Datei.h \
headers/Roboter/robot.h \
headers/Roboter/robotmanager.h \
headers/Roboter/posen.h \
headers/Bildverarbeitung/camera2.h \
headers/Bildverarbeitung/imagefilter.h \
headers/Bildverarbeitung/camera_manager.h \
headers/Positionsbestimmung/trackingManager.h \
headers/Positionsbestimmung/Kalmanfilter.h \
#headers/Positionsbestimmung/kalmanoncuda.h \
headers/Forms/frm_camera_calibration.h \
headers/Forms/frm_camera_positioning.h \
headers/Forms/frm_camera_positioning_pose.h \
headers/Forms/frm_object_calibration.h \
headers/Forms/frm_object_tracking.h \
headers/Forms/frm_main.h \
headers/Forms/frm_robot_calibration.h \

FORMS += \
    forms/frm_camera_calibration.ui \
    forms/frm_camera_positioning.ui \
    forms/frm_camera_positioning_pose.ui \
    forms/frm_main.ui \
    forms/frm_object_calibration.ui \
    forms/frm_object_tracking.ui \
    forms/frm_robot_calibration.ui



################################################ CUDA NVCC ###################################################
#CUDA_DIR = /usr/local/cuda-10.1

#SYSTEM_TYPE =64
#CUDA_ARCH = sm_75


#INCLUDEPATH  += $$CUDA_DIR/include
#LIBS += -L$$CUDA_DIR/lib64 -lcudart -lcuda -lcublas

## Here are some NVCC flags I've always used by default.
#NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
#CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
#cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH  $$NVCCFLAGS \
#                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
#                2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
#cuda.dependency_type = TYPE_C
#cuda.depend_command = $$CUDA_DIR/bin/nvcc -M $$CUDA_INC $$NVCCFLAGS ${QMAKE_FILE_NAME}| sed \"s/^.*: //\"
#cuda.input = CUDA_SOURCES
#cuda.output = $${OBJECTS_DIR}/${QMAKE_FILE_BASE}$${QMAKE_EXT_OBJ}
#QMAKE_EXTRA_COMPILERS += cuda

#CUDA_DIR = /usr/local/cuda-10.1
#CUDA_ARCH = sm_75
#NVCC_OPTIONS = --use_fast_math
#HOST_COMPILER=$$QMAKE_CXX
#LIB_PATH=x86_64-linux

#equals(HOST_COMPILER, "aarch64-linux-gnu-g++") {
#    LIB_PATH=aarch64-linux
#}

#INCLUDEPATH += $$CUDA_DIR/include
#QMAKE_LIBDIR += $$CUDA_DIR/lib64
#LIBS += -L$$CUDA_DIR/lib64 -lcudart -lcuda -lcublas

#CONFIG(debug, debug|release) { #debug
#    cuda_d.commands = $$CUDA_DIR/bin/nvcc -ccbin $$HOST_COMPILER -D_DEBUG $$NVCC_OPTIONS -m64  -arch=$$CUDA_ARCH -dc -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda_d.dependency_type = TYPE_C
#    cuda_d.input = CUDA_SOURCES
#    cuda_d.output = cuda/${QMAKE_FILE_BASE}.o
#    QMAKE_EXTRA_COMPILERS += cuda_d
#} else { #release
#    cuda.commands = $$CUDA_DIR/bin/nvcc -ccbin $$HOST_COMPILER $$NVCC_OPTIONS -m64 -arch=$$CUDA_ARCH -dc -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
#    cuda.dependency_type = TYPE_C
#    cuda.input = CUDA_SOURCES
#    cuda.output = cuda/${QMAKE_FILE_BASE}.o
#    QMAKE_EXTRA_COMPILERS += cuda
#}


################################################## OPENCV INCLUDE ##############################################
unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include/opencv4
DEPENDPATH += $$PWD/../../../../../../../usr/local/include/opencv4

################################################## GSTREAMER INCLUDE ###########################################

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 glib-2.0 gobject-2.0 gstreamer-app-1.0 gstreamer-pbutils-1.0

################################################## TBB INCLUDE #################################################

unix:!macx: LIBS += -L$$PWD/../../../usr/local/lib/ -ltbb

#INCLUDEPATH += $$PWD/../../../usr/local/include
#DEPENDPATH += $$PWD/../../../usr/local/include



################################################## OTHER INCLUDE #################################################
unix:!macx: LIBS += -L$$PWD/../libCuda/lib/ -lgpu

INCLUDEPATH += $$PWD/../libCuda/include
DEPENDPATH += $$PWD/../libCuda/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../libCuda/lib/libgpu.a

unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/cuda/lib64/ -lcudart -lcudadevrt -lcuda

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda/include
INCLUDEPATH += $$PWD/../../../../../../../usr/local/include/eigen3

DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda/include

unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lfranka

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/include

################################################## QMAKE RULES ###########################################

#DISTFILES += \
#    sources/Cuda/cudaKalman.cu

