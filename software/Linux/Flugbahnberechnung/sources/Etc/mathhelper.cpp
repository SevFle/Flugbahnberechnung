#include "headers/Etc/mathhelper.h"

C_mathHelper::C_mathHelper()
  {

  }

C_mathHelper::calcMedian(float Matrix[][])
  {
  int sum = 0;
  int validNum = 0;

   for (int i=0; i<N; i++)
     {
     for (int j=0; j<N; j++)
       {
       if(Matrix[i][j] != 0)
         {
         sum += Matrix[i][j];
         validNum++;
         }
       else
         {
         //DO NOTHING
         }
       }
     }
   return sum/(validNum);
   }


