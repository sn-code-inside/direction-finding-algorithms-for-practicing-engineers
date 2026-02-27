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

void Usage();
double* coefficient(double, double, double, int);
double* linspace(double, double, int);
double wTranposeHmulW(double**, double*, int);

double* linspace(double s, double e, int kmax)
{
    double delx;
    double* x;
    int k;
    x = myAlloc(kmax);
    delx = (e - s) / (double)(kmax-1);
    for (k = 0; k < kmax; k++) x[k] = s + (double)(k)*delx;
    return x;
}

double wTranposeHmulW(double** H, double* w,int m)
{
    double* Hw, Jk;
    int i, k;
    Hw = myAlloc(m);
    for (i = 0; i < m; i++)
    {
        Hw[i] = 0.0;
        for (k = 0; k < m; k++)   Hw[i] = Hw[i] + H[i][k] * w[k];
    }
    Jk = 0.0;
    for (k = 0; k < m; k++) Jk = Jk + Hw[k] * w[k];
    free(Hw);
    return Jk;
}


double* coefficient
(
    double r,     /*Pole position of the narrow band pass filter*/
    double theta, /*spatial angle*/
    double dbl,   /*d/lambda*/
    int m         /*no of sensors*/
)
{
    int i, j, k;
    double phi, pi, a, rPowK, rPowKm2;
    double sinKp1, sinKm1;
    double* w;

    //  compute beam coefficients
    pi = atan(1.0) * 4.0;
    w = myAlloc(m);
    a = (1 - (r * r)) / 2.0;
    phi = 2 * pi * dbl * sin(theta * pi / 180);

    for (k = 0; k < m; k++)
    {
        rPowK = pow(r, k); rPowKm2 = pow(r, k - 2);
        sinKp1 = sin((k + 1) * phi) / sin(phi);
        sinKm1 = sin((k - 1) * phi) / sin(phi);
        // find coefficients 
        if (k >= 2) w[k] = a * (rPowK * sinKp1 - rPowKm2 * sinKm1);
        else w[k] = a * rPowK * sinKp1;
    }
    return w;
}

void Usage()
{
    printf(" Updated on 23rd Mar 2025 at Princeton NJ for Book 5th Chapter\n");
    printf(" [Jk doa] = stfSweep(H,r,dbl,kmax,SE);\n");
    printf(" Inputs: 5\n");
    printf("1. H covariance Matrix m by m\n");
    printf("2. r is pole position of NBP filter .\n");
    printf("3. dbl is the ratio of distance between any two sensors and wavelenth \n");
    printf("4. kmax is the length of Jk\n");
    printf("5. SE is two array SE[0] start SE[1] end in degrees 5 to 88\n");
    printf(" Outputs: 2\n");
    printf("1. Jk  is the spectrum of length kmax\n");
    printf("2. doa is the sweep of length kmax\n");
    return;
}



void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputR, * inputH, * inputDbyL, * inputKmax, *inputSE;
    double* JkPtr,*doaPtr;
    int rcH[2];
    double** H;
    int i, j, m,k,kmax;
    double r, dbl,s,e;
    double* w, *doa,*Jk;


    //Hc,kmax,d_by_lambda,r,se
    if ((nlhs != 2) || (nrhs != 5))
    {
        printf(" Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(5) \n", nlhs, nrhs);
        Usage(); return;
    }


    // par 1 H matrix
    if ( mxGetM(prhs[0]) != mxGetN(prhs[0]) )
    {
        Usage(); printf(" input must be a square matrix \n"); return;
    }
    else
    {
        m = mxGetM(prhs[0]);
        if (m < 2) { Usage(); printf(" input cannot be a scalar\n"); return; }
    }
    
    inputH = mxGetPr(prhs[0]); rcH[0] = m; rcH[1] = m;
    printf(" size of covarinace matrix %d\n", m);
    H = myAlloc2(m, m);
    for (m = 0; m < rcH[0]; m++)
    {
        for (k = 0; k < rcH[1]; k++)
        {
            H[m][k] = inputH[k * rcH[0] + m];
        }
    }

    // par 2 r
    if ((mxGetM(prhs[1]) != 1) || (mxGetN(prhs[1]) != 1))
    {
        Usage();
        printf("prhs[1] theta is not a scalar.\n");
        return;
    }
    inputR = mxGetPr(prhs[1]);
    r = inputR[0];

    // par 3 dbyl
    if ((mxGetM(prhs[2]) != 1) || (mxGetN(prhs[2]) != 1))
    {
        Usage();
        printf("prhs[2] dbyl is not a scalar.\n");
        return;
    }
    inputDbyL = mxGetPr(prhs[2]);
    dbl = inputDbyL[0];

    // par 4 kmax
    if ((mxGetM(prhs[3]) != 1) || (mxGetN(prhs[3]) != 1))
    {
        Usage();
        printf("prhs[3] m is not a scalar.\n");
        return;
    }
    inputKmax = mxGetPr(prhs[3]);
    kmax = inputKmax[0];

    // par 5 start and end
    if ((mxGetM(prhs[4]) != 1) || (mxGetN(prhs[4]) != 2))
    {
        Usage();
        printf("prhs[4] m is not a two vector\n");
        return;
    }
    inputSE = mxGetPr(prhs[4]);
    s = inputSE[0]; e = inputSE[1];
    Jk = myAlloc(kmax);
    doa = linspace(s, e, kmax);
    printf("r = %3.4f dbl %3.4f and kmax %d [%3.4f %3.4f] \n", r, dbl,kmax,s,e);
    
    for (k = 0; k < kmax; k++)
    {
        w = coefficient(r, doa[k], dbl, m);
        if (fabs(doa[k]) > 5)
            Jk[k] = wTranposeHmulW(H, w, m);
        else Jk[k] = rand() / 32767.0;
    }

    /* allocations and initializations */


    plhs[0] = mxCreateDoubleMatrix(1, kmax, mxREAL);
    JkPtr =  mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(1, kmax, mxREAL);
    doaPtr = mxGetPr(plhs[1]);

    /* create and return matrix */
    for (i = 0; i < kmax; i++)
    {
        JkPtr[i]  = Jk[i];
        doaPtr[i] = doa[i];
    }

    free(Jk);

    return;
}

