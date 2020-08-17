TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=

HEADERS += \
  include/libCuda.h

DISTFILES += \
  src/inRange.cu \
  src/kalmanfilter.cu

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/release/ -lcudart
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/debug/ -lcudart
else:unix: LIBS += -L$$PWD/../../../../../../../usr/local/cuda-10.1/lib64/ -lcudart

INCLUDEPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
DEPENDPATH += $$PWD/../../../../../../../usr/local/cuda-10.1/include
