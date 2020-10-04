TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \

HEADERS += \
  include/libCuda.h \
  kalman.h
  src/config.h

DISTFILES += \
  src/inRange.cu \
  src/kalman.cu \
  src/invert.cpp \
  src/matrix.cu \
  src/matrix_kernel.cu \
  src/kalman2.cu



unix:!macx: LIBS += -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas

INCLUDEPATH += $$PWD/../../../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../../../usr/include
