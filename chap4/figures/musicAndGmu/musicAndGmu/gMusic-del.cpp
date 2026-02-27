// gMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mex.h"   /* This one is required */
#include "gMusic.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputDOAS,*inputStd,*inputN,*inputD,*inputRCA;
    double *doaPtr,*muSpkPtr, *snrPtr;
    double *EnPtr, *EnPti;

//  ..... Original Variables ............
    complex** A;
	int rcA[2],i,p,kt;     
	int numOfPhaseSpecSamples = 180; 
	double* muSpk;
	double *doaInDeg, d_by_lambda = 0.5;
	double N = 8; double std = 0.1;
	int D = 3,r,c;
	complex** En;
	//rcA[0] = 128; rcA[1] = 6;
	//double DOAS[3] = { 20, -35, 25 };
    double *DOAS,SNR;

    if ( (nlhs != 4) || (nrhs != 5) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(4) .. Right Hand Side = %d(5) \n",nlhs,nrhs);
       usageGmuT();
       return;
    }
//  ....... inputs to the program from MATLAB ...    
    inputDOAS = mxGetPr(prhs[0]); inputStd = mxGetPr(prhs[1]);
    inputN = mxGetPr(prhs[2]); inputD = mxGetPr(prhs[3]);
    inputRCA = mxGetPr(prhs[4]);

    std = inputStd[0]; N = inputN[0]; D =(int)(inputD[0]);
	//doaInDeg = myAlloc(D);
	if (D >= rcA[1]) { mexErrMsgTxt("!. NO SOLUTION\n"); }

    r = (int)(mxGetM(prhs[4])); c = (int)(mxGetN(prhs[4]));
    if ( r != 1) 
    { 
        printf(" try transpose prhs[4] \n");
        printf(" size of input matrix %d by %d\n",r,c);
        return;
    } else {rcA[0] =(int)(inputRCA[0]); rcA[1] = (int)(inputRCA[1]);}
    
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
        DOAS = myAlloc(c);
        for (i=0; i<c; i++) 
        {
            DOAS[i] = inputDOAS[i];
  //          printf("%3.4f ",DOAS[i]);
        }   //printf("\n");
    }
    //printf("N %3.4f D %d STD %3.4f\n",N,D,std);
    //printf("rcA[0] %d rcA[1] %d\n",rcA[0],rcA[1]);



	muSpk = myAlloc(numOfPhaseSpecSamples);
//	........ generate data matrix ......
	A = IQ(rcA,D,DOAS,d_by_lambda,N,std,&SNR);
//	....................................
	r = rcA[1] - D; if (r < 1) { printf("issue with number of sources %d %d\n", rcA[1], D); r = 1; }
	En = myAlloc2Complex(r, rcA[1]);
	printf(" size of data matrix %d by %d\n", rcA[0], rcA[1]);
	doaInDeg = Hermit(A, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En,d_by_lambda);
	if (doaInDeg == NULL) mexErrMsgTxt("!. g-MUSIC output failed\n");
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

 /*   char* getDate()
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

    void usageGmuT()
    {
        char* today; int width = 100;
 //       today = (char*)malloc(sizeof(char) * width);
 //       today = getDate();
        printf("  %s\n", today);
        printf("  updated on 22nd May 2024 @ 1pm Princeton NJ\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  DOAS = [20, -35, 25];\n");
        printf("  std = 1;\n");
        printf("  fn = 1; N = 1 / fn;\n");
        printf("  D = 2; snapShots = 32;\n");
        printf("  NumOfElements = 6;\n");
        printf("  rcA = [snapShots NumOfElements];\n");
        printf("  [muSpk doa En SNR] = gMusic(DOAS,std,N,D,rcA);\n");
        
        printf("  numberOfSamples = length(muSpk);\n");
        printf("  phi = linspace(-180, 180, numberOfSamples);\n");
        printf("  theta = asind(phi / 180);\n");
        printf("  subplot(211); plot(theta, muSpk); grid;\n");
        printf("  xlabel(num2str(DOAS));\n");
        printf("  title(num2str(doa));\n");
        printf("  You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
        printf("  .....................................................\n");
        return;
    }

