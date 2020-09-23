#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//print the matrix
void matPrint(float *A, int h, int w)
{
	int i,j;
	for(i = 0;i < h;i++)
		{
		for(j = 0;j < w;j++)
			{
			printf("%f ", A[i * w + j]);
			}
		printf("\n");}
}
 

//Random Initialize
void RandomInit(float* data, int n1, int n2)
{   
	srand(1);
    for (int i = 0; i < (n1*n2); ++i)
        data[i] = (rand() % 10) + 1;
}

//Ideintity Matrix Generation
void Identity(float *data, int n)
{
	for (int i = 0; i < (n*n); i=i+1)
		{
		if((i%(n+1))==0)
			data[i] = 1;
		else
			data[i] = 0;
		}        
}






