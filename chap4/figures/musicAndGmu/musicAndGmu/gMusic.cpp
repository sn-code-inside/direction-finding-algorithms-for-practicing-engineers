// gMusik.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mex.h"   /* This one is required */
#include "gMusik.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputD,*inputAr,*inputAi,*inputDbyL;
    double *inputNumberOfMuSamples;
    double *doaPtr,*muSpkPtr, *snrPtr,*eigValuePtr;
    double *EnPtr, *EnPti;

//  ..... Original Variables ............
    complex** A;
	int rcA[2],i,p,kt;     
	int numOfPhaseSpecSamples = 180; 
	double* muSpk, *eigValues;
	double *doaInDeg, d_by_lambda = 0.5;
	double N = 8; double std = 1;
	int D = 3,r,c;
	complex** En;
	rcA[0] = 128; rcA[1] = 6;
    double SNR;

    if ( (nlhs != 4) || (nrhs != 4) )
    {
       printf("  %%Usage Error Parameters Left Hand Side = %d(4) .. Right Hand Side = %d(4) \n",nlhs,nrhs);
       usageGMu();
       return;
    }
//  ....... inputs to the program from MATLAB ...    
    inputD    = mxGetPr(prhs[0]); 
    D           =(int)(inputD[0]);

    inputDbyL = mxGetPr(prhs[1]); 
    d_by_lambda =inputDbyL[0];

    inputNumberOfMuSamples = mxGetPr(prhs[2]);
    numOfPhaseSpecSamples  = inputNumberOfMuSamples[0];

//  .. complex A    
    inputAr = mxGetPr(prhs[3]); inputAi = mxGetPi(prhs[3]);
    
    /* Check that  input is complex*/
    if( !mxIsComplex(prhs[3]) ) 
    {
        usageGMu();
        mexErrMsgTxt("!. prhs[3] must be complex matrix\n");
    }
    rcA[0] = (int)(mxGetM(prhs[3])); rcA[1] = (int)(mxGetN(prhs[3]));
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
    eigValues=myAlloc(rcA[1]);
	doaInDeg = Hermit(A, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En,eigValues,d_by_lambda);
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
    //plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
    //snrPtr = mxGetPr(plhs[3]); snrPtr[0] = SNR;

    plhs[3] = mxCreateDoubleMatrix(1, rcA[1], mxREAL);
    eigValuePtr = mxGetPr(plhs[3]);
    for (i = 0; i < rcA[1]; i++) eigValuePtr[i] = eigValues[i];
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

    void usageGMu()
    {
        char* today; int width = 100;
        today = (char*)malloc(sizeof(char) * width);
//        today = getDate();
//        printf("  %s\n", today);
        printf("  %%updated on 24th Jan 2025 @ 10:55pm Hyderabad TG\n");
        printf("  %% IMPORTANT CHANGE gMUSIC LHS number of parameters\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  DOAS =[20, -35, 30]; POWS = [1 1 1]; muSamples = 90;\n");
        printf("  snapShots = 128; NumOfElements =6;\n");
        printf("  std = 1; SamplesPerCycle = 8;\n");
        printf("  D = 3;  dbyl = 0.5;\n");
        printf("  rcA =[snapShots NumOfElements];\n");
        printf("  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);\n");
        printf("  [muSpk doa En eV] = gMusic(D,dbyl,muSamples,A);\n");
        printf("  doas =[sort(DOAS(1:D))' sort(doa)']';\n");
        printf("  phi = linspace(-180, 180, muSamples);\n");
        printf("  theta = asind(phi/180);\n");
        printf("  omega = linspace(-pi,pi,muSamples);\n");
        printf("  for k=1:NumOfElements-D\n");
        printf("  e = En(k,:);\n");
        printf("  if (k==1)\n");
        printf("  m = abs(freqz(e,1,omega)); mE(k,:) = m; r = roots(e)'; else\n");
        printf("  m = m + abs(freqz(e,1,omega));\n");
        printf("  mE(k,:) = m; r = [r roots(e)'];\n");
        printf("  end;\n");
        printf("  end;\n");        
        printf("  rA = angle(r)*180/pi; rV = abs(r); A = [rA' rV'];\n");
        printf("  B = rootMusic(A); rVn = B(:,2); rAn = B(:,1);\n");
        printf("  t=-asind(rAn/180);\n");
        printf("  subplot(311); plot(theta,1./m,'o',theta,muSpk,'.-r');grid;\n");
        printf("  title(num2str(doas,4),'interpreter','latex');\n");
        printf("  subplot(312); plot(theta,mE,t,rVn,'o');grid;\n");
        printf("  yticks([0 1 ceil(max(max(mE)))]);\n");
        printf("  %%You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
        printf("  .....................................................\n");
        return;
    }





  


   
    
    
    
    
    


 











