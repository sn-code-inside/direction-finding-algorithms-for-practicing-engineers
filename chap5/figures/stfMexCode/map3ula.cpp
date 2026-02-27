/*COEFFIECIENTS OF NARROW BANDPASS FILTER
*/
#include "math.h"
#include "mex.h"   /* This one is required */
#include "memAlocFree.h"
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
void Usage()
{
    printf(" Updated on 24th Mar 2025 at Princeton NJ for Book 5th Chapter\n");
    printf(" theta = map3ula(thetaUla);\n");
    printf(" Inputs: 1\n");
    printf("1. thetaUla is a 3 row vector of peak DOA angles\n");
    printf(" Outputs: 2\n");
    printf("1. theta estimated from 3 angles\n");
    printf("2. zone number .. A 9 B 3 C 1 and zone = 9*A+3*B+C\n");
    return;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double* inputTheta;
    double* thetaPtr,*zonePtr;
	int k,zone,p,c,*w;
    double *v,phi;

    

    if ((nlhs != 2) || (nrhs != 1))
    {
        printf(" Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(1) \n", nlhs, nrhs);
        Usage(); return;
    }

    // par 1
    if ((mxGetM(prhs[0]) != 1) || (mxGetN(prhs[0]) != 3))
	{
		Usage();
		printf("prhs[0] r is  not a row vector\n");
		return;
	}
    c = mxGetN(prhs[0]);
    if (c != 3) { printf(" must be a 3 row vector\n"); return; }
    inputTheta = mxGetPr(prhs[0]);
    v = myAlloc(c); w = myAllocI(c);
    for (k = 0; k < c; k++)
    {
        v[k] = inputTheta[k];
        if (v[k] < 0)    { printf(" input values must be positve\n"); return; }
        if (v[k] > 90.0) { printf(" input values must be less than 90\n"); return; }
    }

    for (p = 0; p<c; p++)
    {
        if (v[p] > 60.0) w[p] = 3;
        else
        {
           if  (v[p] < 30.0) w[p] = 1;
           else 
           {
               w[p] = 2;
               phi = v[p];
           }
        }
    }
        zone = w[0] * 9 + w[1] * 3 + w[2];
        switch (zone)
        {
        case 20:  phi = -phi + 60.0;  break;
        case 18:  phi = phi - 60.0;   break;
        case 24:  phi = -phi;         break;
        case 32:  phi = phi - 120.0;  break;
        case 34:  phi = -phi + 120.0; break;
        case 28:  phi = phi;          break;
            default:
            zone = -1;    
            printf("failed zones [%d %d %d] = %d\n", w[0],w[1],w[2],zone);
            break;
        }
         
   /* allocations and initializations */


    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
	thetaPtr = mxGetPr(plhs[0]);
    thetaPtr[0] = phi;

    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    zonePtr = mxGetPr(plhs[1]);
    zonePtr[0] = zone;

    free(w); free(v);
	
    return;
}

    