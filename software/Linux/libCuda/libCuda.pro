TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=

HEADERS += \
  include/libCuda.h \
  kalman.h
  src/config.h

DISTFILES += \
  src/inRange.cu \
  src/kalman.cu \
  src/invert.cpp \
  src/matrix.cu \
  src/matrix_kernel.cu

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/release/ -lcudart
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/debug/ -lcudart
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include

unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/samples/common/inc
DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
