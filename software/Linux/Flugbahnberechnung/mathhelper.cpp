#include "mathhelper.h"

C_mathHelper::C_mathHelper()
  {

  }

void C_mathHelper::multiply(double* A[], double* B[],double* out[], int dimension)

  {
  for(int i = 0; i < dimension; ++i)
      for(int j = 0; j < dimension; ++j)
        {
          out[j][i] = 0.0;
        }
  for(int i = 0; i < dimension; ++i)
      for(int j = 0; j < dimension; ++j)
          for(int k = 0; k < dimension; ++k)
          {
              out[i][j] += A[i][k] * B[k][j];
          }
  }
