cmake_minimum_required(VERSION 3.10)
project(libCuda_v2 LANGUAGES CUDA CXX)

find_package(CUDA 11 REQUIRED)
if (CUDA_FOUND)
    message("CUDA found")
endif()

string(APPEND CMAKE_CUDA_FLAGS " -gencode arch=compute_75,code=compute_75")
set (CMAKE_CUDA_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CUDA_STANDARD_REQUIRED 11)
set (CMAKE_CXX_STANDARD_REQUIRED 11)
set (CMAKE_CUDA_ARCHITECTURES 75)
set (CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")


set(CMAKE_CUDA_COMPILER_TOOLKIT_ROOT "/usr/local/cuda")
set(CMAKE_CUDA_COMPILER_LIBRARY_ROOT "/usr/local/cuda")
set(CUDA_ADD_CUBLAS_TO_TARGET( libCuda_v2 ))


include_directories(test_cuda PRIVARE
                    ${CUDA_INCLUDE_DIRS}
                    ${CUDA_CUBLAS_DIRS}
                    ${PROJECT_SOURCE_DIR})

add_library(libCuda_v2 STATIC cudaKalman.cu cudaKalman.cuh)
set_target_properties(libCuda_v2 PROPERTIES CUDA_SEPARABLE_COMPILATION OFF)
set_target_properties(libCuda_v2 PROPERTIES POSITION_INDEPENDENT_CODE OFF)



set_target_properties(
libCuda_v2
PROPERTIES
CUDA_SEPARABLE_COMPILATION ON)

set_target_properties(libCuda_v2 PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON)


target_link_libraries(libCuda_v2 ${CUDA_LIBRARIES})
