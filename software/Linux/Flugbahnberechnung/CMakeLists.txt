cmake_minimum_required(VERSION 3.16)
project(Linux)

set(CMAKE_CXX_STANDARD 20)

add_executable(App_Main.cpp Main.h Main.cpp Camera_unmanaged.cpp Camera_unmanaged.h opencv_unmanaged.h OpenCV_unmanaged.cpp CSV_Datei.cpp
CSV_Datei.h CudaKernels.cu CudaKernels.cuh kalman.cu kalman_cuda.cuh Kalmanfilter.cpp Kalmanfilter.h object.cpp object.h point.h
posen.cpp posen.h tracking.cpp tracking.h)

find_package(Qt5Widgets REQUIRED)
target_link_libraries(myqtproject Qt5::Widgets)