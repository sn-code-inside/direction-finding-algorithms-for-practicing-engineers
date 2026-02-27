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
#include "delayT.h"
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
    double *inputN,*inputTau,*inputCycle,*inputnSz,*inputSnr,*inputControl,*inputFlag;
    double N,Tau,SNR,Tow,TouF,TouC,TouT,rFine=0.5,angleF=20.0;
    double phiD = 180.0;
    int nSize,Cycles,kt,p;
    //double **Data, **True, **winData, *Shift,*ShiftF;
    double** Data{}, ** winData{}, * ShiftC{}, * ShiftF{};
    int winLength,Direction=0,JkLen, control = -1, flag = 1,winLengthBy2;
    double *DatPtr,*winPtr,*ShPtr,*ShfPtr,*TouPtr,*JkPtr,*rkDotPtr,*JkXptr;
    double* Jk{}, * JkRsweep{}, ** rkDot{}, * JkAngleSweep;
    double commonData[10];
    int maxRows = 4, i, er;
    int rkDotRows = 4;
    double windowWidth = 0.05;
    int touPtrLen = 20;
    double del;

    if ( (nlhs != 8) || (nrhs != 7) )
    {
       printf("  Usage Error Parameters LHS = %d(8) .. RHS = %d(7) \n",nlhs,nrhs);
       usage(); 
       return;
    }
    inputN = mxGetPr(prhs[0]); inputTau = mxGetPr(prhs[1]);
    inputCycle = mxGetPr(prhs[2]); inputnSz = mxGetPr(prhs[3]);
    inputSnr = mxGetPr(prhs[4]); inputControl = mxGetPr(prhs[5]);
    inputFlag = mxGetPr(prhs[6]);
    N = inputN[0]; Tau = inputTau[0];
    Cycles = inputCycle[0]; nSize = inputnSz[0];
    SNR = inputSnr[0]; control= inputControl[0];
    flag = inputFlag[0];
    Data = myAlloc2(maxRows,nSize); //True = myAlloc2(maxRows,nSize);
    rkDot = myAlloc2(rkDotRows, nSize);
    printf(" N %3.4f Tau %3.4f Cycles %d nSize %d SNR %3.4f\n", N, Tau, Cycles, nSize, SNR);
//	Synthetic Data Creation ..........
    Data = ExpData(nSize, Tau, N, &SNR, Cycles, phiD, &Tow);
    printf(" control -1(%d) orthogonal detection or control -2(%d) cross correlation method\n", control, control);
    printf(" N %3.4f Tau %3.4f Cycles %d nSize %d SNR %3.4f\n", N, Tau, Cycles, nSize, SNR);
//	printf(" input N %3.4f Tau %3.4f Cycles %d nSize %d SNR %3.4f\n", N, Tow, Cycles, nSize, SNR);
//	...................................
    winData = DetectSignalWindow(&winLength, N, nSize, maxRows, rkDot, Data, commonData);
    Direction = 1; if (winLength < 0) { winLength = abs(winLength); Direction = -1;}
    printf(" Direction sign %d\n",Direction);
    

//  integer delay .................
    winLengthBy2 = winLength / 2;
    ShiftC = myAlloc(winLength); Jk = myAlloc(winLengthBy2);

    TouC = mainDelay(winLength, N, commonData, winData, ShiftC, Jk, control);
// ................................
// 
//  Fine Delay ....................
    ShiftF = myAlloc(winLength);
//    JkRsweep = fineR(winData[2], ShiftC, N, winLength, ShiftF, &rFine, &TouF, &JkLen);
    if (flag == 1)
         JkRsweep = fineR(winData[2], ShiftC, N, winLength, ShiftF, &rFine, &TouF, &JkLen);
    else JkAngleSweep = fineAngle(winData[2], ShiftC, N, winLength, ShiftF, &angleF, &TouF, &JkLen);

//  ...............................
    plhs[0] = mxCreateDoubleMatrix(maxRows, nSize, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(maxRows, winLength, mxREAL);
    plhs[2] = mxCreateDoubleMatrix(1, winLength, mxREAL);
    plhs[3] = mxCreateDoubleMatrix(1, winLength, mxREAL);
    plhs[4] = mxCreateDoubleMatrix(1, touPtrLen, mxREAL);
    plhs[5] = mxCreateDoubleMatrix(1, JkLen, mxREAL);
    plhs[6] = mxCreateDoubleMatrix(maxRows, nSize, mxREAL);
    plhs[7] = mxCreateDoubleMatrix(1, winLengthBy2, mxREAL);
    DatPtr =   mxGetPr(plhs[0]); winPtr = mxGetPr(plhs[1]); 
    ShPtr =    mxGetPr(plhs[2]); ShfPtr = mxGetPr(plhs[3]); 
    TouPtr =   mxGetPr(plhs[4]);  JkPtr = mxGetPr(plhs[5]);
    rkDotPtr = mxGetPr(plhs[6]); JkXptr = mxGetPr(plhs[7]);
    for (i = 0; i < touPtrLen; i++) TouPtr[i] = 0.0;
    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < nSize; i++)
        {
            kt = i*maxRows+p;
            DatPtr[kt]=Data[p][i];
            rkDotPtr[kt] = rkDot[p][i];
        }
    }

    for (p = 0; p < maxRows; p++)
    {
        for (i = 0; i < winLength; i++)
        {
            kt = i*maxRows+p;
            winPtr[kt]=winData[p][i];
        }
    }
    for (i = 0; i < winLength; i++) {ShPtr[i] = ShiftC[i]; ShfPtr[i] = ShiftF[i];}
    for (i = 0; i < winLengthBy2; i++) JkXptr[i] = Jk[i];


    if (flag == 1)
    {
        for (i = 0; i < JkLen; i++)    JkPtr[i] = JkRsweep[i];
    }
    else { for (i = 0; i < JkLen; i++) JkPtr[i] = JkAngleSweep[i]; }

 //   for (i = 0; i < JkLen; i++) JkPtr[i] = JkRsweep[i];
    TouT = (TouC-TouF)*Direction;
    TouPtr[0] = TouT*N;  TouPtr[1] = TouC*N; TouPtr[2] = TouF*N;
    TouPtr[3] = Tau * N; TouPtr[4] = rFine;  TouPtr[5] = SNR;
    TouPtr[6] = Direction;
    if (flag == 1) TouPtr[4] = rFine; else TouPtr[4] = angleF;

    for (i = 0; i < touPtrLen - 13; i++) TouPtr[i+7] = commonData[i];
    printf(" gold Minima apf2 r %3.4f\n", rFine);
    printf(" Coarse Delay %3.4f Fine Delay %3.4f samples\n", TouC * N, TouF * N);
    printf(" Total Estimated Delay %3.4f and actual delay %3.4f\n",TouT*N,Tau*N);
//    myFree2(Data, maxRows); myFree2(True, maxRows);
    myFree2(Data, maxRows);
    return;
}

void usage()
{
    char* today; int width = 100;
    today = (char*)malloc(sizeof(char) * width);
    today = getDate();
    printf("  %s\n", today);
    printf("  updated on 1st Nov 2024 @ 05:04pm Princeton NJ\n");
    printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
    printf("  [a, b, c, f, par, Jkr,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);\n");
    printf("  a is 4 by nSize matrix first row time 2 and 3 are waveforms at two elements\n");
    printf("  b is 4 by winLength matrix first row time 2 and 3 are waveforms at two elements\n");
    printf("  c is a coarse vector moved close to waveform in 3\n");
    printf("  f is a fine vector moved close to waveform in 3\n");
    printf("  ......................................................\n");
    printf("  Jkr is coarse sweep of pole in APF2 befor minimization\n");
    printf("  Jkx is cross correlation function\n");
    printf("  rkdot is 4 by nSize matrix with detection enevlope and pole variation.\n");
    printf("  N 6.0000 Tau -5.1 Cycles 10 nSize 1000 SNR 25.0000\n");
    printf("  par[0] estimated delay par[1] integer delay par[2] fraction delay in samples\n");
    printf("  par[3] created delay in samples\n");
    printf("  par[4] is gold minima pole position of APF2 par[5] is actual SNR \n");
    printf("  par[6] to par[9] integer detection parameters \n");
    printf("  par[10] loop gain and par[11] integration window in detection \n");
    printf("  Example of MATLAB program\n");
    printf("  .....................use as it is....................\n");
    printf("  clc; clear all;\n");
    printf("  N = 6; Tau = -5.1; Cycles = 10.0;\n");
    printf("  nSize = 1000; SNR = 25.0; control = -1; flag = 1;\n");  
    printf("  [a, b, c, f, par, Jkr,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);\n");
    printf("  t = a(1,:); x1 = a(2,:); x2 = a(3,:);\n");
    printf("  T = b(1,:); y1 = b(2,:); y2 = b(3,:);\n");
    printf("  subplot(311); plot(t,x1,'.-r',t,x2,'.-b');grid;\n");
    printf("  r = tou(4);\n");
    printf("  subplot(312); plot(T,y1,'b',T,y2,'.-r',T,c,'-.k');grid;\n");
    printf("  subplot(313); plot(T,y1,'b',T,y2,'.-r',T,c,'-.k',T,f,'.-k');grid;\n");
    printf("  title([num2str(par) ' r = ' num2str(r)]);\n");
    printf("  .....................................................\n");
    return;
}
