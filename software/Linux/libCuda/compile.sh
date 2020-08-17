#!/bin/sh
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/lib
pwd
echo "linking"

nvcc -arch=sm_75 -rdc=true -c -o temp1.o ../src/inRange.cu
nvcc -dlink -arch=sm_75 -o inRange.o temp1.o -lcudart
nvcc -arch=sm_75 -rdc=true -c -o temp2.o ../src/kalmanfilter.cu
nvcc -dlink -arch=sm_75 -o kalmanfilter.o temp2.o -lcudart

echo "removing old libraries"
rm -f libgpu.a
ar cru libgpu.a inRange.o temp1.o kalmanfilter.o temp2.o
ranlib libgpu.a
cd ..
echo "Done"
