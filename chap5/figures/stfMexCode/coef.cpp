/*COEFFIECIENTS OF NARROW BANDPASS FILTER
*/
#include "math.h"
#include "mex.h"   /* This one is required */
#include "memAlocFree.h"
void Usage();
double* coefficient(double, double, double, int);
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
//coefficient(r,theta,dbl,m,w);
double* coefficient
(
    double r,     /*Pole position of the narrow band pass filter*/
    double theta, /*spatial angle*/
    double dbl,   /*d/lambda*/
    int m         /*no of sensors*/
)
{
    int i,j,k;
    double phi,pi,a, rPowK,rPowKm2;
    double sinKp1, sinKm1;
    double* w;
 
//  compute beam coefficients
    pi = atan(1.0) * 4.0;
    w = myAlloc(m);
    a = (1 - (r * r)) / 2.0;
    phi = 2 * pi * dbl * sin(theta * pi / 180);
    
    for(k=0;k<m;k++)
    { 
        rPowK = pow(r, k); rPowKm2 = pow(r, k - 2);
        sinKp1 = sin( (k + 1) * phi ) / sin(phi);
        sinKm1 = sin( (k - 1) * phi ) / sin(phi);
        // find coefficients 
        if (k>=2) w[k] = a * (rPowK * sinKp1 - rPowKm2 * sinKm1);
        else w[k] = a * rPowK * sinKp1;
    }
    return w;
}

void Usage()
{
    printf(" Updated on 19th Mar 2025 at Princeton NJ for Book 5th Chapter\n");
    printf(" w = coef(r,theta,dbl,m);\n");
    printf(" Inputs: 4\n");
    printf("1. r is pole position of NBP filter .\n");
    printf("2. theta is the spatial angle (DOA) in Deg\n");
    printf("3. dbl is the ratio of distance between any two sensors and wavelenth \n");
    printf("4. m is the no of sensors\n");
    printf(" Outputs: 1\n1. w is vector containing coefficients at a particular theta\n");
    return;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
//W=coef(r,theta,dbl,M);
{
    double* inputR, * inputTheta, * inputDbyL, * inputM;
    double* wptr;
	int i,j,m;
	double r,dbl,theta;
    double *w;

    

    if ((nlhs != 1) || (nrhs != 4))
    {
        printf(" Usage Error Parameters Left Hand Side = %d(1) .. Right Hand Side = %d(4) \n", nlhs, nrhs);
        Usage(); return;
    }

    // par 1
    if ((mxGetM(prhs[0]) != 1) || (mxGetN(prhs[0]) != 1))
	{
		Usage();
		printf("prhs[0] r is  not a scalar.\n");
		return;
	}
    inputR = mxGetPr(prhs[0]);
    r = inputR[0];

    // par 2
    if ((mxGetM(prhs[1]) != 1) || (mxGetN(prhs[1]) != 1))
	{
		Usage();
		printf("prhs[1] theta is not a scalar.\n");
		return;
	}
    inputTheta = mxGetPr(prhs[1]);
    theta = inputTheta[0];

    // par 3
    if ((mxGetM(prhs[2]) != 1) || (mxGetN(prhs[2]) != 1))
	{
		Usage();
		printf("prhs[2] dbyl is not a scalar.\n");
		return;
	}
    inputDbyL = mxGetPr(prhs[2]);
    dbl = inputDbyL[0];
    
    // par 4
    if ((mxGetM(prhs[3]) != 1) || (mxGetN(prhs[3]) != 1))
	{
		Usage();
		printf("prhs[3] m is not a scalar.\n");
		return;
	}
    inputM = mxGetPr(prhs[3]);
    m = inputM[0];
    
         
   /* allocations and initializations */


    plhs[0] = mxCreateDoubleMatrix(1, m, mxREAL);
	wptr = mxGetPr(plhs[0]);
      
    w = coefficient(r,theta,dbl,m);
     
	/* create and return matrix */
	for(i=0;i<m; i++) wptr[i] = w[i];

	free(w);
	
    return;
}

    