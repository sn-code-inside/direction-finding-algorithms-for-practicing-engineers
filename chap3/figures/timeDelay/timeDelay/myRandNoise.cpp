#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
#include "mex.h"   /* This one is required */
/*
 * Author: Kaluri V. Ranga Rao
 * Visiting Scholar, Department of Computer Science,
 * The Ohio State University
 *
 * Copyright (c) 2025 Kaluri V. Ranga Rao
 * All rights reserved.
 *
 * This code is part of the material for the book:
 * "Direction Finding Algorithms for Practicing Engineers,"
 * published by Springer Nature.
 *
 * This material is intended for academic and research purposes only.
 */
double randn();
double* myAlloc(int);
void myNoise(int,double,double *);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputN,*inputStd;
    int N,i;
    double *noise,*noisePtr,std;

    if ( (nlhs != 1) || (nrhs != 2) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(1) .. Right Hand Side = %d(2) \n",nlhs,nrhs);
       return;
    }
    inputN =   mxGetPr(prhs[0]);   N = inputN[0];
    inputStd = mxGetPr(prhs[1]); std = inputStd[0];
    noise = myAlloc(N);
    myNoise(N,std,noise);
    plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
    noisePtr = mxGetPr(plhs[0]);
    for (i = 0; i < N; i++) noisePtr[i]=noise[i];

    return;
}

double randn()
{
	double intmax, udf, sum;
	int rnd, k;

	intmax = 65535;
	sum = 0.0;

	for (k = 0; k < 12; k++)
	{
		rnd = rand();
		udf = (double)rnd;
		udf = (double)((udf / intmax) - 0.5);
		sum = sum + udf;
	}

	return sum;
}
double* myAlloc(int c)
{
	double* A;
	A = (double*)malloc(c * sizeof(double));
	return A;
}
void myNoise
(
	int maxk,
	double std,
	double *uN
)
{
	int s, k;
	unsigned int seed;
	double rnd;
	seed = (unsigned int)(time(NULL));
	srand(seed);
//  Copy Right Protected  written by Prof Kaluri

//	printf(" Test Random Sequence ");
//	for (m = 0; m<5; m++) { temp = (rand() / 32767.0) - 0.5; printf(" %f ", temp); } printf("\n");

	for (k = 0; k<maxk; k++)
	{
		rnd = 0.0; for (s = 0; s<12; s++) 
        rnd = rnd + ((rand() / 32767.0) - 0.5);
		uN[k] = rnd * std;
	}
	return;
}


