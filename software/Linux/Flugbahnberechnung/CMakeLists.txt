cmake_minimum_required(VERSION 3.16)
project(Flugbahnberechnung)
set(CMAKE_PREFIX_PATH /home/severin/Qt/5.15.0/gcc_64/lib/cmake/Qt5)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})


find_package(CUDA  REQUIRED)
include_directories("${CUDA_INCLUDE_DIRS}")

list(APPEND CUDA_NVCC_FLAGS "-c")

find_package( Threads )



include_directories(.)
include_directories(cuda)
include_directories(forms)
include_directories(headers)
include_directories(sources)

add_executable(Flugbahnberechnung
        cuda/CudaKernels.cu
        cuda/CudaKernels.cuh
        cuda/kalman.cu
        cuda/kalman_cuda.cuh
        forms/frm_camera_calibration.ui
        forms/frm_camera_calibration_crop.ui
        forms/frm_camera_positioning.ui
        forms/frm_camera_positioning_pose.ui
        forms/frm_main.ui
        forms/frm_object_calibration.ui
        forms/frm_object_tracking.ui
        headers/camera.h
        headers/camera_manager.h
        headers/CSV_Datei.h
        forms/frm_camera_calibration.h
        forms/frm_camera_calibration_crop.h
        forms/frm_camera_positioning.h
        forms/frm_camera_positioning_pose.h
        forms/frm_main.h
        forms/frm_object_calibration.h
        forms/frm_object_tracking.h
        headers/GlobalObjects.h
        headers/Kalmanfilter.h
        headers/Main.h
        headers/object.h
        headers/point.h
        headers/posen.h
        headers/tracking.h
        sources/App_main.cpp
        sources/camera.cpp
        sources/camera_manager.cpp
        sources/CSV_Datei.cpp
        forms/frm_camera_calibration.cpp
        forms/frm_camera_calibration_crop.cpp
        forms/frm_camera_positioning.cpp
        forms/frm_camera_positioning_pose.cpp
        forms/frm_main.cpp
        forms/frm_object_calibration.cpp
        forms/frm_object_tracking.cpp
        sources/GlobalObjects.cpp
        sources/Kalmanfilter.cpp
        sources/Main.cpp
        sources/object.cpp
        sources/posen.cpp
        sources/tracking.cpp)




# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Use the Widgets module from Qt 5.
target_link_libraries(Flugbahnberechnung Qt5::Widgets Qt5::Core ${CMAKE_THREAD_LIBS_INIT})

