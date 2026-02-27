// gMusik.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mex.h"   /* This one is required */
#include "gMusik.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputD,*inputAr,*inputAi,*inputDbyL;
    double *doaPtr,*muSpkPtr, *snrPtr;
    double *EnPtr, *EnPti;

//  ..... Original Variables ............
    complex** A;
	int rcA[2],i,p,kt;     
	int numOfPhaseSpecSamples = 180; 
	double* muSpk;
	double *doaInDeg, d_by_lambda = 0.1;
	double N = 8; double std = 0.1;
	int D = 3,r,c;
	complex** En;
	rcA[0] = 128; rcA[1] = 6;
	//double DOAS[3] = { 20, -35, 25 };
    double *DOAS,SNR;

    if ( (nlhs != 4) || (nrhs != 3) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(4) .. Right Hand Side = %d(3) \n",nlhs,nrhs);
       usage(); 
       return;
    }
//  ....... inputs to the program from MATLAB ...    
    inputD    = mxGetPr(prhs[0]); 
    D           =(int)(inputD[0]);

    inputDbyL = mxGetPr(prhs[1]); 
    d_by_lambda =inputDbyL[0];
//  .. complex A    
    inputAr = mxGetPr(prhs[2]); inputAi = mxGetPi(prhs[2]);
    
    /* Check that  input is complex*/
    if( !mxIsComplex(prhs[2]) ) 
    {
        usage();
        mexErrMsgTxt("!. prhs[2] must be complex matrix\n");
    }
    rcA[0] = (int)(mxGetM(prhs[2])); rcA[1] = (int)(mxGetN(prhs[2]));
//  .........................................................    
    if (D >= rcA[1]) { mexErrMsgTxt("!. NO SOLUTION\n"); }
    A = myAlloc2Complex(rcA[0], rcA[1]);
    printf(".....................................................\n");
    printf(" size of input matrix %d by %d\n",rcA[0],rcA[1]);
    printf(" No of Targets %d and D by Lambda %3.4f\n",D,d_by_lambda);
    printf(".....................................................\n");
//  ... transfer input complex to A matrix
    for (p = 0; p < rcA[0]; p++) // rows
    {
        for (i = 0; i < rcA[1]; i++)
        {
                kt = i*rcA[0]+p;
                A[p][i].r = inputAr[kt];
                A[p][i].i = inputAi[kt];
        }
    }
 // ...  end of transfer
	muSpk = myAlloc(numOfPhaseSpecSamples);

//	....................................
	r = rcA[1] - D; if (r < 1) { printf("issue with number of sources %d %d\n", rcA[1], D); r = 1; }
	En = myAlloc2Complex(r, rcA[1]);
	printf(" size of data matrix %d by %d\n", rcA[0], rcA[1]);
	doaInDeg = Hermit(A, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En,d_by_lambda);
	if (doaInDeg == NULL) 
    {
        mexWarnMsgTxt("!. g-MUSIC output failed\n");
        plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
        muSpkPtr = mxGetPr(plhs[0]); muSpkPtr[0] = NULL;
        plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
        doaPtr = mxGetPr(plhs[1]);  doaPtr[0] = NULL;
        plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
        EnPtr = mxGetPr(plhs[2]); EnPtr[0] = NULL;
        plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
        snrPtr = mxGetPr(plhs[3]); snrPtr[0] = -100;
        return;
    }
    printf(" IEEE Transactions on Antennas and Propagation, \n vol. 61, no. 4, pp. 2263-2268, April 2013, doi: 10.1109/TAP.2012.2232893.\n");
	printf(" DOA values by gold MUSIC\n");
	for (i = 0; i < D; i++) printf(" %3.4f ", doaInDeg[i]); printf("\n");

    plhs[0] = mxCreateDoubleMatrix(1, numOfPhaseSpecSamples, mxREAL);
    muSpkPtr = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(1, D, mxREAL);
    doaPtr = mxGetPr(plhs[1]); 
    plhs[2] = mxCreateDoubleMatrix(r, rcA[1], mxCOMPLEX);
    EnPtr = mxGetPr(plhs[2]); EnPti = mxGetPi(plhs[2]);
    for (p = 0; p < r; p++) // rows
    {
        for (i = 0; i < rcA[1]; i++)
        {
                kt = i*r+p;
                EnPtr[kt]  = En[p][i].r; // updated 12th May 2024
                EnPti[kt]  = En[p][i].i; // updated 12th May 2024
        }
    }
    for (i=0; i<numOfPhaseSpecSamples; i++) muSpkPtr[i] = muSpk[i];

    for (i=0; i<D; i++) doaPtr[i] = doaInDeg[i];

    plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
    snrPtr = mxGetPr(plhs[3]); snrPtr[0] = SNR;
	return;
}

    char* getDate()
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
    }

    void usage()
    {
        char* today; int width = 100;
        today = (char*)malloc(sizeof(char) * width);
        today = getDate();
        printf("  %s\n", today);
        printf("  updated on 6th Jun 2024 @ 5:30pm Princeton NJ\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  load('x8M350Hz.mat');\n");
        printf("  A = Ar2Ai(x);\n");
        printf("  D = 2; dbyl = 0.1;\n");
        printf("  B = hilbert(x);\n");
        printf("  [muSpk doa1 En SNR] = gMusik(D,dbyl,A);\n");
        printf("  numberOfSamples = length(muSpk);\n");
        printf("  phi = linspace(-180, 180, numberOfSamples);\n");
        
        printf("  [muSpk doa En SNR] = gMusik(D,dbyl,B);\n");
        printf("  subplot(211);plot(phi,muSpk,'.-b',phi,muSpk1,'.-r');grid;\n");
        printf("  xlabel(' phase ');\n");
        printf("  title(num2str(doa));\n");
        printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
        printf("  .....................................................\n");
        return;
    }

 








