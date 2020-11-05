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


DESTDIR     = $$system(pwd)
OBJECTS_DIR = $$DESTDIR/Obj
# C++ flags
QMAKE_CXXFLAGS_RELEASE =-03


############################################### CUDA SOURCES ################################################
CUDA_SOURCES += cuda/cudaKalman.cu

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
  sources/Positionsbestimmung/kalmanoncuda.cpp \
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
headers/Positionsbestimmung/kalmanoncuda.h \
headers/Forms/frm_camera_calibration.h \
headers/Forms/frm_camera_positioning.h \
headers/Forms/frm_camera_positioning_pose.h \
headers/Forms/frm_object_calibration.h \
headers/Forms/frm_object_tracking.h \
headers/Forms/frm_main.h \
headers/Forms/frm_robot_calibration.h \
cuda/cudaKalman.cuh

FORMS += \
    forms/frm_camera_calibration.ui \
    forms/frm_camera_positioning.ui \
    forms/frm_camera_positioning_pose.ui \
    forms/frm_main.ui \
    forms/frm_object_calibration.ui \
    forms/frm_object_tracking.ui \
    forms/frm_robot_calibration.ui



################################################ CUDA NVCC ###################################################
CUDA_DIR = /usr/local/cuda

INCLUDEPATH  += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64
LIBS += -lcudart -lcuda -lcublas
CUDA_ARCH = sm_75


# Here are some NVCC flags I've always used by default.
NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS \
                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
                2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
cuda.dependency_type = TYPE_C
cuda.depend_command = $$CUDA_DIR/bin/nvcc -M $$CUDA_INC $$NVCCFLAGS ${QMAKE_FILE_NAME}| sed \"s/^.*: //\"
cuda.input = CUDA_SOURCES
cuda.output = $${OBJECTS_DIR}/${QMAKE_FILE_BASE}$${QMAKE_EXT_OBJ}
QMAKE_EXTRA_COMPILERS += cuda

################################################## OPENCV INCLUDE ##############################################

unix:!macx: LIBS += -L$$PWD/../../../../../libs/opencv420/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../libs/opencv420/include
DEPENDPATH += $$PWD/../../../../../libs/opencv420/include

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

unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart -lcudadevrt -lcuda

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
INCLUDEPATH += $$PWD/../../../../../../../usr/local/include/eigen3

DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include

unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/lib/ -lfranka

INCLUDEPATH += $$PWD/../../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/include

################################################## QMAKE RULES ###########################################

#DISTFILES += \
#    sources/Cuda/cudaKalman.cu


