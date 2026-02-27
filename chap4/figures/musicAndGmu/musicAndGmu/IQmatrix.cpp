// IQmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mex.h"   /* This one is required */
#include "IQmatrix.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputRCA,*inputD,*inputDOAS,*inputStd,*inputDbyL,*inputSamplesPerCycle;
    double* inputPOWS;
    double *snrPtr;
//    double *doaPtr,*muSpkPtr, *snrPtr;
    double *APtr, *APti;
//A = IQ(rcA,D,DOAS,d_by_lambda,N,std,&SNR)
//  ..... Original Variables ............
    complex** A;
	int rcA[2],i,p,kt;     
	double  d_by_lambda;
	double std;
	int D ,r,c;
    double *DOAS,*POWS,SNR, SamplesPerCycle;

    if ( (nlhs != 2) || (nrhs != 7) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(7) \n",nlhs,nrhs);
       usageIQ(); 
       return;
    }
//  ....... inputs to the program from MATLAB ...    
    inputDOAS = mxGetPr(prhs[0]); inputStd = mxGetPr(prhs[1]);
    inputD = mxGetPr(prhs[2]); inputRCA = mxGetPr(prhs[3]);
    inputDbyL=mxGetPr(prhs[4]); inputSamplesPerCycle = mxGetPr(prhs[5]);
    inputPOWS = mxGetPr(prhs[6]);

    std = inputStd[0]; D =(int)(inputD[0]); d_by_lambda=inputDbyL[0];
    SamplesPerCycle = inputSamplesPerCycle[0];
    printf(" dbyl %3.4f D %d STD %3.4f,Samples Per Cycle %3.4f\n", d_by_lambda, D, std, SamplesPerCycle);


    r = (int)(mxGetM(prhs[3])); c = (int)(mxGetN(prhs[3]));
    if ( r != 1) 
    { 
        printf(" try transpose prhs[3] \n");
        printf(" size of input matrix %d by %d\n",r,c);
        return;
    } else {rcA[0] =(int)(inputRCA[0]); rcA[1] = (int)(inputRCA[1]);}
    if (D >= rcA[1]) { mexErrMsgTxt("!. NO SOLUTION\n"); }

    r = (int)(mxGetM(prhs[0])); c = (int)(mxGetN(prhs[0]));
    if ( r != 1) 
    { 
        printf(" try transpose \n");
        printf(" size of input matrix %d by %d\n",r,c);
        return;
    }


    if ( c < D ) mexErrMsgTxt("!. Insufficient DOA data\n");
    else 
    {
        DOAS = myAlloc(c); POWS = myAlloc(c);
        for (i=0; i<c; i++) 
        {
            DOAS[i] = inputDOAS[i];
            POWS[i] = inputPOWS[i];
            printf(" %3.4f(%3.4f) ",DOAS[i],POWS[i]);
        }   printf("\n");
    }




//	........ generate data matrix ......
	A = IQ(rcA,D,DOAS,POWS,d_by_lambda,SamplesPerCycle,std,&SNR);
//    printComplxMatrix(A, rcA[0], rcA[1]);
//	....................................
	r = rcA[1] - D; if (r < 1) { printf(" issue with number of sources %d %d\n", rcA[1], D); r = 1; }

    plhs[0] = mxCreateDoubleMatrix(rcA[0], rcA[1], mxCOMPLEX);
    APtr = mxGetPr(plhs[0]); APti = mxGetPi(plhs[0]);
    for (p = 0; p < rcA[0]; p++) // rows
    {
        for (i = 0; i < rcA[1]; i++)
        {
                kt = i* rcA[0] + p;
                APtr[kt]  = A[p][i].r; // updated 12th May 2024
                APti[kt]  = A[p][i].i; // updated 12th May 2024
        }
    }
    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    snrPtr = mxGetPr(plhs[1]); snrPtr[0] = SNR;
    printf(" Signal to Noise Ratio %3.4f dB\n",SNR);
	return;
}

/*    char* getDate()
    {
        //	......... local time ...................................
        int er;
        time_t now;
        struct tm bufT {};
        char* dtNtime;
        dtNtime = (char*)malloc(60 * sizeof(char));

        now = time(NULL);
        er = localtime_s(&bufT, &now);
        er = asctime_s(dtNtime, 60, &bufT);
        return dtNtime;
    }*/

    void usageIQ()
    {
        char* today; int width = 100;
        today = (char*)malloc(sizeof(char) * width);
        //today = getDate();
        //printf("  %s\n", today);
        printf("  updated on 2nd Feb 2025 @ 1pm Princeton NJ\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  DOAS = [20, -35, 25];\n");
        printf("  POWS = [1, 1, 1]; \n");
        printf("  std = 1;\n");
        printf("  D = 2; snapShots = 32;\n");
        printf("  NumOfElements = 6;\n");
        printf("  rcA = [snapShots NumOfElements];\n");
        printf("  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);\n");
        

        printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
        printf("  .....................................................\n");
        return;
    }

