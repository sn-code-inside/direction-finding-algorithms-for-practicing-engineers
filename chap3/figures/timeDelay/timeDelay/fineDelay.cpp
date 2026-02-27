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
#include "fineDelay.h"
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
    double *inputN,*inputWinData,*inputShift,*inputDir;
    double N,TouF,rFine,angleF;
    int maxRows,i,p,r,c;
    double *winData, *Shift,*ShiftF,*JkRsweep,* JkAngleSweep;
    int winLength,control=0,JkLen;
    double *ShfPtr,*ToufPtr,*JkRPtr,*rFPtr;

    if ( (nlhs != 4) || (nrhs != 4) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(4) .. Right Hand Side = %d(4) \n",nlhs,nrhs);
       usageDelay(); 
       return;
    }
    inputN = mxGetPr(prhs[0]); N = inputN[0];
    inputWinData = mxGetPr(prhs[1]);
    r = mxGetM(prhs[1]); c = mxGetN(prhs[1]);
    winLength = c; maxRows = r;
    inputDir = mxGetPr(prhs[2]); control=inputDir[0];
    winData = myAlloc(winLength); 
    Shift = myAlloc(winLength); ShiftF = myAlloc(winLength);
    for (i = 0; i < winLength; i++)  winData[i]=inputWinData[i];
    inputShift = mxGetPr(prhs[3]);
    for (i = 0; i < winLength; i++) Shift[i] = inputShift[i]; // input
    if (control == 1)
    JkRsweep = fineR(winData, Shift, N, winLength, ShiftF, &rFine,&TouF,&JkLen);
    else 	JkAngleSweep = fineAngle(winData, Shift, N, winLength, ShiftF, &angleF, &TouF, &JkLen);
//    printf(" length of JkRsweep %d\n",JkLen);
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    ToufPtr = mxGetPr(plhs[0]); ToufPtr[0] = TouF;

    plhs[1] = mxCreateDoubleMatrix(1, winLength, mxREAL);
    ShfPtr = mxGetPr(plhs[1]);
//    for (i = 0; i < winLength; i++) ShfPtr[i] = Shift[i];
    for (i = 0; i < winLength; i++) ShfPtr[i] = ShiftF[i];

    plhs[2] = mxCreateDoubleMatrix(1, JkLen, mxREAL);
    JkRPtr = mxGetPr(plhs[2]);
    if (control == 1)
    {
        for (i = 0; i < JkLen; i++) JkRPtr[i] = JkRsweep[i];
    } else { for (i = 0; i < JkLen; i++) JkRPtr[i] = JkAngleSweep[i]; }

    plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
    rFPtr = mxGetPr(plhs[3]); 
    if (control == 1) rFPtr[0] = rFine; else rFPtr[0] = angleF;

    if (control == 1) printf(" rFine %3.4f\n",rFine); else
        printf(" angle fine %3.4f\n", angleF);
    printf(" Fine Delay %3.4f and %3.4f Cycles\n",N*TouF,TouF);

    return;
}

void usageDelay()
{
    char* today; int width = 100;
    today = (char*)malloc(sizeof(char) * width);
    today = getDate();
    printf("  %s\n", today);
    printf("  updated on 20th Oct 2024 @ 11:00am Belle Mead NJ\n");
    printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
    printf("  [touF z JkR rF] = fineDelay(N,x,dir,y);\n");
    printf("  x is reference array\n");
    printf("  y is delayed array\n");
    printf("  z is output array match with y\n");
    printf("  dir is 1 use pole sweep else sweep angle\n");
    printf("  N is samples/cycle\n");
    printf("  towF is fine delay in Cylces shift is shifted wave\n");
    printf("  JkR is Sweep R\n");
    printf("  rF is pole at JkR minima \n");
    printf("  Example of MATLAB program\n");
    printf("  .....................use as it is....................\n");
    printf("  clc; clear all;\n");
    printf("  N = 6; Tau = -5.8; Cycles = 10.0; phiD=10.0\n");
    printf("  nSize = 1000; SNR = 25.0;\n");
    printf("  [a tow] = synthData(N,Tau,Cycles,nSize,SNR,phiD);\n");
    printf("  t = a(1,:); x1 = a(2,:); x2 = a(3,:);\n");

    printf("  subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;\n");
    printf("  [b rkdot dir detect] = DetectSigWin(N,a);\n");
    printf("  tw = b(1,:); x1w = b(2,:); x2w = b(3,:);\n");
    printf("  subplot(312); plot(tw,x1w,'.-r',tw,x2w,'.-b');grid;\n");
    printf("  title(' Detection Window $x_A$ and $x_B$','interpreter','latex');\n");
    printf("  [tow shift Jk rFine] = intDelay(N,b,detect,control);\n");
    printf("  subplot(313); plot(tw,x1w,'.-r',tw,x2w,'.-b',tw,shift,'.-k');grid;\n");
    printf("  .....................................................\n");
    return;
    

}

