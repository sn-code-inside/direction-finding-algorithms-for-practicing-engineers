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
#include "DetectSigWin.h"
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
    double *inputN,*inputData;
    double N;
    int nSize,Cycles,maxRows,kt,i,p,r,c;
    double **Data, **winData,**rkDot;
//    double **Data, **True, **winData, *Shift,*ShiftF;
    int winLength,Direction=0;
    double *DatPtr,*winPtr,*dirPtr,*rkDotPtr,*commonDataPtr;
    int rkDotRows = 4; int detDataSize = 6;
    double commonData[10];
//    double *DatPtr,*winPtr,*ShPtr,*ShfPtr,*TouPtr;

    if ( (nlhs != 4) || (nrhs != 2) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(4) .. Right Hand Side = %d(2) \n",nlhs,nrhs);
       usageSigWin(); 
       return;
    }
    inputN = mxGetPr(prhs[0]); N = inputN[0];
    inputData = mxGetPr(prhs[1]);
    r = mxGetM(prhs[1]); c = mxGetN(prhs[1]);
    nSize = c; maxRows = r;
    if ( maxRows > 4 ){ printf("size %d by %d\n",r,c);usageSigWin(); return;}
    printf("!. size of data matrix %d by %d\n",maxRows,nSize);
    Data = myAlloc2(maxRows,nSize); rkDot = myAlloc2(rkDotRows, nSize);
    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < nSize; i++)
        {
            kt = i*maxRows+p;
            Data[p][i]=inputData[kt];
        }
    }
	winData = DetectSignalWindow(&winLength, N, nSize, maxRows,rkDot,Data,commonData);
    Direction = 1; if (winLength < 0) { winLength = abs(winLength); Direction = -1;}
    printf(" Direction sign %d\n",Direction);
    printf(" Length of Detected Window %d\n",winLength);
    if ( winLength < 0 ) return;
    plhs[0] = mxCreateDoubleMatrix(maxRows, winLength, mxREAL);
    winPtr = mxGetPr(plhs[0]); 
    plhs[1] = mxCreateDoubleMatrix(rkDotRows, nSize, mxREAL);
    rkDotPtr = mxGetPr(plhs[1]);

    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    dirPtr = mxGetPr(plhs[2]); dirPtr[0] = Direction;

    plhs[3] = mxCreateDoubleMatrix(1, detDataSize, mxREAL);
    commonDataPtr = mxGetPr(plhs[3]); 
    for (i = 0; i < detDataSize; i++) commonDataPtr[i] =commonData[i];
    
    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < winLength; i++)
        {
            kt = i*maxRows+p;
            winPtr[kt]=winData[p][i];
        }
    }

    for (p = 0; p < rkDotRows; p++)
    {
        for (i = 0; i < nSize; i++)
        {
            kt = i * rkDotRows + p;
            rkDotPtr[kt] = rkDot[p][i];
        }
    }


    dirPtr[2] = Direction;
//    myFree2(Data, maxRows); myFree2(True, maxRows);
    printf("------------ end of signal window detection -----------------\n\n");
    return;
}

void usageSigWin()
{
    char* today; int width = 100;
    today = (char*)malloc(sizeof(char) * width);
    today = getDate();
    printf("  %s\n", today);
    printf("  updated on 30th Sep 2024 @ 11:00am Dublin Ohio\n");
    printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
    printf("  [wData rkDot dir detect] = DetectSigWin(N,data)\n");
    printf("  wData is 4 by nSize matrix first row time 2 and 3 are waveforms at two elements\n");
    printf("  rkDot is 4 by nSize matrix rkdot and r\n");
    printf("  dir is Direction of Signal Lead or Lag\n");
    printf("  detect is detected information\n");
    printf("  Example of MATLAB program\n");
    printf("  .....................use as it is....................\n");
    printf("  clc; clear all;\n");
    printf("  N = 6; Tau = -5.8; Cycles = 10.0; phiD=10.0\n");
    printf("  nSize = 1000; SNR = 25.0;\n");
    printf("  [a tow] = synthData(N,Tau,Cycles,nSize,SNR,phiD);\n");
    printf("  t = a(1,:); x1 = a(2,:); x2 = a(3,:);\n");

    printf("  subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;\n");
    printf("  [b dir] = DetectSigWin(N,a);\n");
    printf("  tw = b(1,:); x1w = b(2,:); x2w = b(3,:);\n");
    printf("  subplot(312); plot(tw,x1w,'.-r',tw,x2w,'.-b');grid;\n");
    printf("  title(' Detection Window $x_A$ and $x_B$','interpreter','latex');\n");
    printf("  .....................................................\n");
    return;
}
