QT       += core gui
QT       += datavisualization
QT       += quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DESTDIR     = $$system(pwd)
#OBJECTS_DIR = $$DESTDIR/Obj
# C++ flags
#QMAKE_CXXFLAGS_RELEASE =-03
#CONFIG += -O0

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
headers/Etc/App_main.h \
headers/Etc/GlobalObjects.h \
headers/Etc/watchdog.h \
headers/Etc/object.h \
headers/Etc/Main.h \
headers/CSV_Manager/loadmanager.h \
headers/CSV_Manager/savemanager.h \
headers/CSV_Manager/CSV_Datei.h \
headers/Roboter/pidregler.h \
headers/Roboter/robot.h \
headers/Roboter/robotmanager.h \
headers/Roboter/posen.h \
headers/Bildverarbeitung/camera2.h \
headers/Bildverarbeitung/imagefilter.h \
headers/Bildverarbeitung/camera_manager.h \
headers/Positionsbestimmung/trackingManager.h \
headers/Positionsbestimmung/Kalmanfilter.h \
headers/Forms/frm_camera_calibration.h \
headers/Forms/frm_camera_positioning.h \
headers/Forms/frm_camera_positioning_pose.h \
headers/Forms/frm_object_calibration.h \
headers/Forms/frm_object_tracking.h \
headers/Forms/frm_main.h \
headers/Forms/frm_robot_calibration.h

FORMS += \
    forms/frm_camera_calibration.ui \
    forms/frm_camera_positioning.ui \
    forms/frm_camera_positioning_pose.ui \
    forms/frm_main.ui \
    forms/frm_object_calibration.ui \
    forms/frm_object_tracking.ui \
    forms/frm_robot_calibration.ui

################################################## OPENCV INCLUDE ###########################################

unix:!macx: LIBS += -L$$PWD/../../../../../libs/opencv420/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../../libs/opencv420/include
DEPENDPATH += $$PWD/../../../../../libs/opencv420/include

################################################## GSTREAMER INCLUDE ###########################################

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 glib-2.0 gobject-2.0 gstreamer-app-1.0 gstreamer-pbutils-1.0

################################################## TBB INCLUDE ###########################################

unix:!macx: LIBS += -L$$PWD/../../../usr/local/lib/ -ltbb

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

################################################## QMAKE RULES ###########################################
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




############################## CUDA NVCC ############################################
#CUDA_SOURCES += cuda/CudaKernels.cu
#PROJECT_DIR = $$system(pwd)
#OBJECTS_DIR = $$PROJECT_DIR/Obj
#DESTDIR = ../bin
#CUDA_DIR = /usr/local/cuda-10.1
#CUDA_ARCH = sm_75
#NVCCFLAGS = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v
#INCLUDEPATH += $$CUDA_DIR/include
#QMAKE_LIBDIR += $$CUDA_DIR/lib64
#LIBS += -lcudart -lcutil_x86_64
## join the includes in a line
#CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

#cuda.input = CUDA_SOURCES
#cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}.o

#cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -g -G -arch=$$CUDA_ARCH -c $$NVCCFLAGS $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}

#cuda.dependency_type = TYPE_C # there was a typo here. Thanks workmate!
#cuda.depend_command = $$CUDA_DIR/bin/nvcc -g -G -M $$CUDA_INC $$NVCCFLAGS   ${QMAKE_FILE_NAME}
## Tell Qt that we want add more stuff to the Makefile
#QMAKE_EXTRA_UNIX_COMPILERS += cuda


## File(s) containing my CUDA code
#CUDA_SOURCES += cuda/CudaKernels.cu

## Location of CUDA on my system (Arch Linux)
#CUDA_DIR = /usr/local/cuda-10.1

#INCLUDEPATH += $$CUDA_DIR/include
#QMAKE_LIBDIR += $$CUDA_DIR/lib64
#LIBS += -lcudart -lcuda

## Compute capability of my GPU
#CUDA_ARCH = sm_75 # 75 RTX 2070 / GTX 1650          # 61 GTX 1080

#NVCCFLAGS     = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

#CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
#cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS \
#                $$CUDA_INC $$LIBS  ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} \
#                2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
#cuda.dependency_type = TYPE_C

#cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS ${QMAKE_FILE_NAME}| sed \"s/^.*: //\"
#cuda.input = CUDA_SOURCES
#cuda.output = $${OBJECTS_DIR}/${QMAKE_FILE_BASE}$${QMAKE_EXT_OBJ}

#QMAKE_EXTRA_COMPILERS += cuda
#DEFINES += PROJECT_PATH=\\"$_PRO_FILE_PWD_\\"
##----------------------------------------------------------------
##-------------------------Cuda setup-----------------------------
##----------------------------------------------------------------

#CUDA_SOURCES += \
#          cuda/CudaKernels.cu

## Path to cuda toolkit install (System specific)
#CUDA_DIR = /usr/local/cuda-10.1
#INCLUDEPATH += $CUDA_DIR/include
#INCLUDEPATH += $CUDA_DIR/samples/common/inc

## Cuda libs dir
#QMAKE_LIBDIR += $CUDA_DIR/lib64

### note: for dynamic parallelism you need libcudadevrt
#LIBS += -lcudart -lcudadevrt -lcuda

## GPU ARCH
## This gets passed as the gpu-architecture flag to nvcc compiler
## specifying particular architectures enable certain features, limited to the compute capability
## of the GPU. compute capabilities listed here http://en.wikipedia.org/wiki/CUDA
#CUDA_ARCH = 75

## Join the includes in a line
#CUDA_INC = $join(INCLUDEPATH,' -I','-I',' ') -I$_PRO_FILE_PWD_

## Flags used by the CUDA compiler
#NVCCFLAGS = 	--compiler-options -fno-strict-aliasing \
#    --ptxas-options=-v \
#    -rdc=true \
#    -prec-div=true -ftz=false -prec-sqrt=true -fmad=true

## Flags used by both the CUDA compiler and linker
#NVCCFLAG_COMMON = -m64 -arch=sm_$CUDA_ARCH
#CONFIG(debug, debug|release) {
#  #DEBUG
#  NVCCFLAG_COMMON += -g -G
#} else {
#  #RELEASE
#  NVCCFLAG_COMMON += -O2
#}

##------------------------- Cuda intermediat compiler
## Prepare intermediat cuda compiler
#cudaIntr.input = CUDA_SOURCES
##cudaIntr.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
#cudaIntr.output = ${QMAKE_FILE_BASE}_cuda.o

#cudaIntr.commands = 	$CUDA_DIR/bin/nvcc $NVCCFLAG_COMMON \
#      -dc $NVCCFLAGS $CUDA_INC $LIBS \
#      ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}

##Set our variable out. These obj files need to be used to create the link obj file and used in our final gcc compilation
#cudaIntr.variable_out = CUDA_OBJ
#cudaIntr.variable_out += OBJECTS

## Tell Qt that we want add more stuff to the Makefile
#QMAKE_EXTRA_UNIX_COMPILERS += cudaIntr

##------------------------- Cuda linker (required for dynamic parallelism)
## Prepare the linking compiler step
#cuda.input = CUDA_OBJ
#cuda.output = link.o
#cuda.CONFIG += combine	# Generate 1 output file

## Tweak arch according to your hw's compute capability
#cuda.commands = $CUDA_DIR/bin/nvcc $NVCCFLAG_COMMON \
#    -dlink *_cuda.o -o link.o
#cuda.dependency_type = TYPE_C
#cuda.depend_command = 	$CUDA_DIR/bin/nvcc -g -G \
#      -M $CUDA_INC $NVCCFLAGS ${QMAKE_FILE_NAME}

## Tell Qt that we want add more stuff to the Makefile
#QMAKE_EXTRA_UNIX_COMPILERS += cuda





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
