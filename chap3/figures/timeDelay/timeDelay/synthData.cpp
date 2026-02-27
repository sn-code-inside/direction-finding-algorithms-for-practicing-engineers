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
#include "synthData.h"
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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputN,*inputTau,*inputCycle,*inputnSz,*inputSnr,*inputPhiD;
    double N,Tau,SNR,Tow,TouF,TouC,TouT,rFine,phiD;
    int nSize,Cycles,maxRows,kt,i,p;
    double **Data, **True, **winData, *Shift,*ShiftF;
    int winLength,Direction=0;
    double *DatPtr,*winPtr,*ShPtr,*ShfPtr,*TouPtr,*snrPtr;

    if ( (nlhs != 3) || (nrhs != 6) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(3) .. Right Hand Side = %d(6) \n",nlhs,nrhs);
       usageSyn(); 
       return;
    }
    inputN = mxGetPr(prhs[0]);     inputTau = mxGetPr(prhs[1]);
    inputCycle = mxGetPr(prhs[2]); inputnSz = mxGetPr(prhs[3]);
    inputSnr = mxGetPr(prhs[4]);  inputPhiD = mxGetPr(prhs[5]);
    N = inputN[0]; Tau = inputTau[0];
    Cycles = inputCycle[0]; nSize = inputnSz[0]; phiD = inputPhiD[0];
    SNR = inputSnr[0]; //safeNsize = nSize + 1;
    maxRows = 4;
    Data = myAlloc2(maxRows,nSize); True = myAlloc2(maxRows,nSize);
//  printf("N %3.4f Tau %3.4f Cycles %d nSize %d SNR %3.4f\n",N,Tau,Cycles,nSize,SNR);
//  output
//  printf("N %3.4f Tau %3.4f Cycles %d nSize %d SNR %3.4f\n", N, Tau, Cycles, nSize, SNR);
	Data = ExpData(nSize, Tau, N, &SNR, Cycles,phiD,&Tow);
	printf("!. input N %3.4f Samples/Cycle\n", N);
	printf("!. input Tau %3.4f(%3.4f)\n", Tow, Tau);
	printf("!. input integer %3.4f(%3.4f)\n", N*Tow, N*Tau);
	printf("!. input Cycles %d nSize %d SNR %3.4f\n", Cycles, nSize, SNR);
    printf("!. input phiD %3.4f\n", phiD);

    plhs[0] = mxCreateDoubleMatrix(maxRows, nSize, mxREAL);
    DatPtr = mxGetPr(plhs[0]); 
    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < nSize; i++)
        {
            kt = i*maxRows+p;
            DatPtr[kt]=Data[p][i];
        }
    }
    plhs[1] = mxCreateDoubleMatrix(1,1, mxREAL);
    TouPtr = mxGetPr(plhs[1]);
    TouPtr[0] = Tow;
    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    snrPtr = mxGetPr(plhs[2]); snrPtr[0] = SNR;
    printf("------------ end of data generation --------------\n\n");
    return;
}

void usageSyn()
{
    char* today; int width = 100;
    today = (char*)malloc(sizeof(char) * width);
    today = getDate();
    printf("  %s\n", today);
    printf("  updated on 24th Sep 2024 @ 11:00am Dublin Ohio\n");
    printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
    printf("  [a tow snr] = synthData(N,Tau,Cycles,nSize,SNR,phiD);\n");
    printf("  a is 3 by nSize matrix first row time 2 and 3 are waveforms at two elements\n");
    printf("  Example of MATLAB program\n");
    printf("  .....................use as it is....................\n");
    printf("  clc; clear all;\n");
    printf("  N = 6; Tau = -5.8; Cycles = 10.0; phiD=10.0\n");
    printf("  nSize = 1000; SNR = 25.0;\n");
    printf("  [a tow] = synthData(N,Tau,Cycles,nSize,SNR,phiD);\n");
    printf("  t = a(1,:); x1 = a(2,:); x2 = a(3,:);\n");
    
    printf("  subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;\n");

    printf("  .....................................................\n");
    return; 
}

