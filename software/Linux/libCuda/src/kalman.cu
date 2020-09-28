//Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <cuda_runtime.h>

#include "matrix_kernel.cu"
#include "matrix.cu"
#include "../include/libCuda.h"
#include "../src/invert.cpp"


using namespace onCuda::KalmanFilter;

C_kalman::C_kalman()
  {
  this->stat    = new cublasStatus_t;
  this->handle  = new cublasHandle_t;
  cublasCreate  (this->handle);
  }

C_kalman::~C_kalman()
{

}
void C_kalman::allocateMemory()
  {
    //no == zeilen
    //ns == spalten

    //Allocate vectors  in device memory
    cudaMalloc(&d_X, ns*1);
    cudaMalloc(&d_P, ns*ns);
    cudaMalloc(&d_F, ns*ns);
    cudaMalloc(&d_Z, no*1);
    cudaMalloc(&d_S, no*no);
    cudaMalloc(&d_s, no*no);
    cudaMalloc(&d_K, ns*no);
    cudaMalloc(&d_H, no*ns);
    cudaMalloc(&d_E, no*no);
    cudaMalloc(&d_Ft, ns*ns);
    cudaMalloc(&d_Ht, ns*no);
    cudaMalloc(&d_Si, no*no);
    cudaMalloc(&d_Y, no*1);
    cudaMalloc(&d_I, ns*ns);
    cudaMalloc(&d_Hint, no*ns);
    cudaMalloc(&d_Sint, no*no);
    cudaMalloc(&d_Kint, ns*no);
    cudaMalloc(&d_Xint, ns*1);
    cudaMalloc(&d_Pint, ns*ns);
    cudaMalloc(&d_Pint2, ns*ns);
    lda = ((no+15)&~15|16);


    cudaError_t ret = cudaMallocHost( (void**)&A, no*lda*sizeof(float) );
    if( ret != cudaSuccess )
      {
      printf("Failed to allocate %d memory", no*lda*sizeof(float));
      return;
      }//if
    printf("\nAllocation of the Device memory completed...\n");


    for(int i = 0; i<no ; i++)
      {
      for(int j = i; j < no; j++)
        {
        A[i*lda + j] = s[i * no + j];
        A[j*lda+i] = A[i*lda+j];
        }//for
      }//for

  }//allocateMemory()

void C_kalman::initialize (float *F, float *H,float *E,float *s, int ns, int no)
    //X = Estimate
    //P = Uncertainty Covariance Matrix
    //F = State transition Matrix - Prediciton Matrix
    //Z = Measurement
    //H = Measurement Function - observation model which maps the true state space into the observed space
    //E = Measurement/Observation noise
    //I = Identity Matrix

  {
  this->ns = ns;
  this->no = no;
  allocateMemory();

  //Init I
  //malloc(&I,ns,ns);
  float* h_I = &I;
  cudaMemcpy(d_I, h_I, ns*ns, cudaMemcpyHostToDevice);
  Identity(d_I, ns);

  // Copy Input vectors from host memory to device memory
  cudaMemcpy(d_F, F, ns*ns, cudaMemcpyHostToDevice);
  cudaMemcpy(d_H, H, no*ns, cudaMemcpyHostToDevice);
  cudaMemcpy(d_E, E, no*no, cudaMemcpyHostToDevice);

  // Set the kernel arguments
  int threadsPerBlock = 256;
  int Nos = no*ns;
  int Ns =  ns;
  int No = no;
  int Ns2 = ns*ns;
  int No2 = no*no;
  int blocksPerGridNos = (Nos + threadsPerBlock - 1) / threadsPerBlock;
  int blocksPerGridNs = (Ns + threadsPerBlock - 1) / threadsPerBlock;
  int blocksPerGridNo = (No + threadsPerBlock - 1) / threadsPerBlock;
  int blocksPerGridNs2 = (Ns2 + threadsPerBlock - 1) / threadsPerBlock;
  int blocksPerGridNo2 = (No2 + threadsPerBlock - 1) / threadsPerBlock;

  //Transpose
  MatTranspose<<<blocksPerGridNos, threadsPerBlock>>>(d_Ht,d_H,no,ns);
  printf("\n Transpose of H successful\n");

  MatTranspose<<<blocksPerGridNos, threadsPerBlock>>>(d_Ft,d_F,ns,ns);
  printf("\n Transpose of F successful\n");

  //Inverse using CUBLAS

  if( cudaSetDevice( dev ) != cudaSuccess )
    {
    printf( "Failed to set device %d\n", dev );
    return;
    }

  if(   cublasCreate  (this->handle) != CUBLAS_STATUS_SUCCESS )
    {
    printf( "failed to initialize the cublas library\n" );
    return;
    }
  printf("Cublas initialized...\n");

  invert(A, lda, no, handle);

  for(int i = 0; i<no ; i++)
    {
    for(int j = i; j < no; j++)
      {
      si[i * no + j] = A[i * lda + j];
      si[j * no + i] = si[i * no + j];
       }
     }

  cudaMemcpy(d_Si, si, no*no, cudaMemcpyHostToDevice);

  }

void C_kalman::correct       (float *measurement)
  {

//  Update Phase
//  kalmanGain =Pk-*HT [ H*Pk-HT+Ek]-1
//  newEstimate = xk-+kalmanGain[zk –H*xk-]
//  Pk = (I –kalmanGain*H)Pk-

  //Update
  //S = HPHt + E
  //K = PHtSi
  //Y = Z-HX
  //X = X + KY
  //P = [I - KH]P

  cudaMemcpy(d_F, F, ns*ns, cudaMemcpyHostToDevice);
  //step 1  to calculate Y = Z - HX
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Y, d_H, d_X, no, ns);
  MatSub<<<blocksPerGridNo, threadsPerBlock>>>(d_Y, d_Z, d_Y, no, 1);

  //step 2 to calculate  S = HPHt + E
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Hint, d_H, d_P, no, ns);
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Sint, d_Hint, d_Ht, no, ns);
  MatAdd<<<blocksPerGridNo2, threadsPerBlock>>>(d_S, d_Sint, d_E, no, no);

  //step 3 to calcualte K = PHtSi
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Kint, d_P, d_Ht, no, ns);
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_K, d_Kint, d_Si, ns, no);

  //step4 to calculate  X = X+ KY
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Xint, d_K, d_Y, ns, no);
  MatAdd<<<blocksPerGridNs, threadsPerBlock>>>(d_X, d_X, d_Xint, ns, 1);

  //step5 to calculate [I - KH]P
  MatMult<<<blocksPerGridNos, threadsPerBlock>>>(d_Pint, d_K, d_H, ns, no);
  MatSub<<<blocksPerGridNs2, threadsPerBlock>>>(d_Pint, d_I, d_Pint, ns, ns);
  MatMult<<<blocksPerGridNs2, threadsPerBlock>>>(d_Pint2, d_Pint, d_P, ns, ns);
  MatCopy<<<blocksPerGridNs2, threadsPerBlock>>>(d_P, d_Pint2, ns, ns);

  // Host wait for the kernel to finish
  cudaDeviceSynchronize();
  }

float C_kalman::predict()
{

  // Predict Phase
  //  xk-= Fk*xk-1 + Bk*uk
  //  Pk-= FkPk-1FkT+ QK

  //Prediction Phase
  // X = FX
  // P = FPFt

  //step 1 to calculate X = F*X
  MatMult<<<blocksPerGridNs2, threadsPerBlock>>>(d_Xint, d_F, d_X, ns, ns);
  MatCopy<<<blocksPerGridNs, threadsPerBlock>>>(d_X, d_Xint, ns, 1);

  //step2 to calculate P = FPFt
  MatMult<<<blocksPerGridNs2, threadsPerBlock>>>(d_Pint, d_F, d_P, ns, ns);
  MatMult<<<blocksPerGridNs2, threadsPerBlock>>>(d_P, d_Pint, d_Ft, ns, ns);
  // Host wait for the kernel to finish
  cudaDeviceSynchronize();

  // Copy result from device memory to host memory
  // h_X contains the result in host memory
  cudaMemcpy(h_X, d_X, ns*1, cudaMemcpyDeviceToHost);
  float estimate;
  estimate = *h_X;
  return estimate;
}


void C_kalman::cleanup()
  {
  // stop and destroy timer
  cudaFreeHost( A );
  cublasDestroy(*handle);

  // Free host memory
  if(X)
      free(X);
  if(P)
      free(P);
  if(F)
      free(F);
  if(Ztemp)
      free(Ztemp);
  if(S)
      free(S);
  if(s)
      free(s);
  if(K)
      free(K);
  if(H)
      free(H);
  if(E)
      free(E);
  if(Ft)
      free(Ft);
  if(Ht)
      free(Ht);
  if(Si)
      free(Si);
  if(Y)
      free(Y);
  if(Hint)
      free(Hint);
  if(Sint)
      free(Sint);
  if(Kint)
      free(Kint);
  if(Xint)
      free(Xint);
  if(Pint)
      free(Pint);
  if(Pint2)
      free(Pint2);
  //printf("\n Host Cleanup Successful\n");

  // Free device memory

  if(d_X)
      cudaFree(d_X);
  if(d_P)
      cudaFree(d_P);

  if(d_F)
      cudaFree(d_F);
  if(d_Ztemp)
      cudaFree(d_Ztemp);
  if(d_S)
      cudaFree(d_S);
  if(d_s)
      cudaFree(d_s);
  if(d_K)
      cudaFree(d_K);
  if(d_H)
      cudaFree(d_H);
  if(d_E)
      cudaFree(d_E);
  if(d_Ft)
      cudaFree(d_Ft);
  if(d_Ht)
      cudaFree(d_Ht);
  if(d_Si)
      cudaFree(d_Si);
  if(d_Y)
      cudaFree(d_Y);
  if(d_I)
      cudaFree(d_I);
  if(d_Hint)
      cudaFree(d_Hint);
  if(d_Sint)
      cudaFree(d_Sint);
  if(d_Kint)
      cudaFree(d_Kint);
  if(d_Xint)
      cudaFree(d_Xint);
  if(d_Pint)
      cudaFree(d_Pint);
  if(d_Pint2)
      cudaFree(d_Pint2);

  printf("\nDevice Cleanup Successful\n");


  cudaDeviceReset() ;

  exit(0);

}




