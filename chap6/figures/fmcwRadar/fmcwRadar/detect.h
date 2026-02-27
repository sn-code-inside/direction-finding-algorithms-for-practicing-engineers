#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
int PRINT_FLAG = 0;

#include "cMath.h"
int findPeaks(int, int *, int *, double *);
int myMax(double *, int);
void myFree(double*);
int** myAlloc2I(int, int);
void myFree2I(int**, int);
double* myAlloc(int);
int* myAllocI(int);
//extern class sort
class sort
{
public:
	double *x;
	int *xI, M;
	void High2Low();
	void Low2High();
	void showx();
};
void sort::showx()
{
	int k, r = 10;
	printf("in class sort showx()\n");
	for (k = 0; k < M; k++)
	{
		printf("%3.2f ", x[k]); if (k % r == r - 1) printf("\n");
	}
}
void sort::High2Low()
{
	int k, ip, i, tempI;
	double big, temp;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  1st May 2017   Dr Kaluri Reserach House.
	//	in descending order ..
	//	for (ip = 0; ip < M; ip++) xI[ip] = ip; // this was removed on 20th Sep 2022
	//  very simple bug took time but good do it again .. 23rd Feb 2016 at Hyderabad 11:46pm    
	for (ip = 0; ip < M; ip++)
	{
		big = x[ip]; i = ip; // this is important
		for (k = ip; k < M; k++)
		{
			if (x[k] > big) { big = x[k]; i = k; }      // max of x[ip:M] is @ i
		}
		temp = x[ip];   x[ip] = x[i];   x[i] = temp;   // Exchange
		tempI = xI[ip]; xI[ip] = xI[i]; xI[i] = tempI;  // Exchange pointers
	}

	return;
}
void sort::Low2High()
{
	int k, ip, i, tempI;
	double small, temp;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  1st May 2017   Dr Kaluri Reserach House.
	//	printf("9. sortLow2High( peak, peakI, %d);\n", M);
//	for (ip = 0; ip < M; ip++) xI[ip] = ip; // this was removed on 20th Sep 2022
	//  very simple bug took time but good do it again .. 23rd Feb 2016 at Hyderabad 11:46pm    
	i = 0; for (ip = 0; ip < M; ip++)
	{
		small = x[ip]; i = ip; // this is important
		for (k = ip; k < M; k++)
		{
			if (x[k] < small) { small = x[k]; i = k; }  // min of x[ip:M] is @ i
		}
		temp = x[ip];   x[ip] = x[i];   x[i] = temp;   // Exchange
		tempI = xI[ip]; xI[ip] = xI[i]; xI[i] = tempI;  // Exchange pointers
	}
	return;
}

