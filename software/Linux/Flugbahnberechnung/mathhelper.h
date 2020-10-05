#ifndef C_MATHHELPER_H
#define C_MATHHELPER_H

namespace mathhelper
  {
  class C_mathHelper
    {
    public:
      C_mathHelper();
      ~C_mathHelper();
      void multiply(double* A[], double* B[],double* out[], int dimension);
    };
  }

#endif // C_MATHHELPER_H
