#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cuda.h>
#include <cstring>
#include <math.h>
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "point.h"

#ifdef __INTELLISENSE__
void __syncthreads();
#endif

extern "C" void predict_single(float* predict, float* cov, float* new_predict, float* new_cov, int point_num, float delta_t);

extern "C" void update_single(float* data, float* predict, float* cov, float* new_predict, float* new_cov, int point_num, float delta_t, int ite_nem);
