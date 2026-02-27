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
#include "intDelay.h"
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
    double *inputN,*inputWinData,*inputDetectData,*inputControl;
    double N, TouC;
    int nSize,Cycles,maxRows,kt,i,p,r,c;
    int control = 1;

    double **winData, *Shift,*Jk,*commonData;
    int winLength,parLen=0;
    double *ToucPtr,*ShiftPtr,*JkPtr;

    if ( (nlhs != 3) || (nrhs != 4) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(3) .. Right Hand Side = %d(4) \n",nlhs,nrhs);
       usageDelay();
       return;
    }
    inputN = mxGetPr(prhs[0]); N = inputN[0];
    inputWinData = mxGetPr(prhs[1]);
    r = mxGetM(prhs[1]); c = mxGetN(prhs[1]);
    winLength = c; maxRows = r;
    inputDetectData = mxGetPr(prhs[2]);
    r = mxGetM(prhs[2]); c = mxGetN(prhs[2]);
    if (r != 1) { printf("try transpose\n"); usageDelay(); }
    parLen = c;
    commonData = myAlloc(parLen);
    for (p = 0; p < parLen; p++) commonData[p] = inputDetectData[p];
    inputControl = mxGetPr(prhs[3]); control = inputControl[0];

    winData = myAlloc2(maxRows,winLength); 
    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < winLength; i++)
        {
            kt = i*maxRows+p;
            winData[p][i]=inputWinData[kt];
        }
    }
    //printf(" Detection Data "); for (i = 0; i < parLen; i++) printf("%3.4f ", commonData[i]); printf("\n");
    //Shift = (double*)malloc(sizeof(double) * winLength);
    Shift = myAlloc(winLength); Jk = myAlloc(winLength/2);
    TouC = mainDelay(winLength,N, commonData, winData, Shift,Jk,control);
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    ToucPtr = mxGetPr(plhs[0]); ToucPtr[0] = TouC;
    plhs[1] = mxCreateDoubleMatrix(1, winLength, mxREAL);
    ShiftPtr = mxGetPr(plhs[1]);
    for (i = 0; i < winLength; i++) ShiftPtr[i]=Shift[i];

    plhs[2] = mxCreateDoubleMatrix(1, winLength/2, mxREAL);
    JkPtr = mxGetPr(plhs[2]);
    for (i = 0; i < winLength/2; i++) JkPtr[i]=Jk[i];
    printf(" Estimated integer Delay %3.4f and %3.4f Cycles\n",N*TouC,TouC);
    free(Jk); free(Shift);
    printf("----------- end of integer delay estimation ------------------\n\n");
    return;
}

void usageDelay()
{
    char* today; int width = 100;
    today = (char*)malloc(sizeof(char) * width);
    today = getDate();
    printf("  %s\n", today);
    printf("  updated on 18th Oct 2024 @ 11:00pm Belle Mead NJ\n");
    printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
    printf("  [tow shift Jk] = intDelay(N,b,detect,control);\n");
    printf("  b is 4 by winLength matrix first row time 2 and 3 are waveforms at two elements\n");
    printf("  detect is detection data\n");
    printf("  control is how integer delay is estimated\n");
    printf("  N is samples/cycle\n");
    printf("  tow is delay in Cylces shift is shifted wave\n");
    printf("  Jk is cross correlation wave\n");
    printf("  Example of MATLAB program\n");
    printf("  .....................use as it is....................\n");
    printf("  clc; clear all;\n");
    printf("  N = 6; Tau = -5.8; Cycles = 10.0; phiD=10.0\n");
    printf("  nSize = 1000; SNR = 25.0;\n");
    printf("  [a tow] = synthData(N,Tau,Cycles,nSize,SNR,phiD);\n");
    printf("  t = a(1,:); x1 = a(2,:); x2 = a(3,:);\n");

    printf("  subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;\n");
    printf("  [b rkDot dir detect] = DetectSigWin(N,a);\n");

    printf("  tw = b(1,:); x1w = b(2,:); x2w = b(3,:);\n");
    printf("  subplot(312); plot(tw,x1w,'.-r',tw,x2w,'.-b');grid;\n");
    printf("  title(' Detection Window $x_A$ and $x_B$','interpreter','latex');\n");
    printf("  [tow shift Jk] = intDelay(N,b,detect,control);\n");
    printf("  subplot(313); plot(tw,x1w,'.-r',tw,x2w,'.-b',tw,shift,'.-k');grid;\n");
    printf("  .....................................................\n");
    return;
    

}

