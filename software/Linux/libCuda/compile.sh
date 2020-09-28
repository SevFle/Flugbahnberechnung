#!/bin/sh
SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/lib
pwd
echo "linking"

/usr/local/cuda-10.1/bin/nvcc -arch=sm_75 -rdc=true -c -o temp1.o ../src/inRange.cu -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas

/usr/local/cuda-10.1/bin/nvcc -arch=sm_75 -rdc=true -c -o temp2.o ../src/kalman.cu -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas
/usr/local/cuda-10.1/bin/nvcc -arch=sm_75 -rdc=true -c -o temp3.o ../src/kalman2.cu -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas

/usr/local/cuda-10.1/bin/nvcc -arch=sm_75 -rdc=true -c -o temp4.o ../src/matrix.cu -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas
/usr/local/cuda-10.1/bin/nvcc -arch=sm_75 -rdc=true -c -o temp5.o ../src/matrix_kernel.cu -L$$PWD/../../../../../../../usr/lib/x86_64-linux-gnu/ -lcublas

/usr/local/cuda-10.1/bin/nvcc -dlink -arch=sm_75 -o inRange.o temp1.o -lcudart 

/usr/local/cuda-10.1/bin/nvcc -dlink -arch=sm_75 -o kalman.o temp2.o -lcudart 
/usr/local/cuda-10.1/bin/nvcc -dlink -arch=sm_75 -o kalman2.o temp3.o -lcudart 

/usr/local/cuda-10.1/bin/nvcc -dlink -arch=sm_75 -o matrix.o temp4.o -lcudart 
/usr/local/cuda-10.1/bin/nvcc -dlink -arch=sm_75 -o matrix_kernel.o temp5.o -lcudart 



echo "removing old libraries"
rm -f libgpu.a
ar cru libgpu.a inRange.o temp1.o kalman.o temp2.o kalman2.o temp3.o matrix.o temp4.o matrix_kernel.o temp5.o 
ranlib libgpu.a
cd ..
echo "Done"
