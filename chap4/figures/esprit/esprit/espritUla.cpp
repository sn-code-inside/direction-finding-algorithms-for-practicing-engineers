// espritUla.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mex.h"   /* This one is required */
#include "espritUla.h"
complex* myEigenPhi(complex**, int*);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputD,*inputAr,*inputAi,*inputDbyL;
    double *inputNumberOfRows;
    double *doaPtr,*muSpkPtr, *snrPtr,*eigValuePtr;
    double* EPtr, * EPti;
    double* SPtr, * SPti;
    double* phiPtr;
    double* polePtr;

//  ..... Original Variables ............
    //complex** A;
    complex** U{}, ** S, * sk,**Ae,**b;
    complex** Moor, **phi;
    complex* eigv,*eigVc;
	int rcA[2],i,p,kt,numberOfRows;     
    int rcS[2], rcUs[2], rcAe[2],rcMoor[2],rcPhi[2],k;
	double* muSpk, *eigValues;
	double *doaInDeg, d_by_lambda = 0.5;
	double N = 8; double std = 1;
	int D = 3,r,c;
	complex** E;
    double pi,*phase,*pole,arg,*theta,*temp;
    pi = atan(1.0) * 4.0;
    int* indx;


    if ( (nlhs != 5) || (nrhs != 3) )
    {
       printf("  %%Usage Error Parameters Left Hand Side = %d(5) .. Right Hand Side = %d(3) \n",nlhs,nrhs);
       usageGMu();
       return;
    }
//  ....... inputs to the program from MATLAB ...    
    inputD    = mxGetPr(prhs[0]);  D=(int)(inputD[0]);

//  .. complex A    
    inputAr = mxGetPr(prhs[1]); inputAi = mxGetPi(prhs[1]);
    
    /* Check that  input is complex*/
    if( !mxIsComplex(prhs[1]) ) 
    {
        usageGMu();
        mexErrMsgTxt("!. prhs[1] must be complex matrix\n");
    }
    rcA[0] = (int)(mxGetM(prhs[1])); rcA[1] = (int)(mxGetN(prhs[1]));
    if ( rcA[0] != 1 ) { mexErrMsgTxt("!. Must be a complex row vector\n"); }
//  .........................................................    

    //A = myAlloc2Complex(rcA[0], rcA[1]);
    sk = myAllocComplex(rcA[1]);

    printf(".....................................................\n");
    printf(" size of input complex data %d by %d\n",rcA[0],rcA[1]);
    printf(" No of signals %d and D\n",D);
    printf(".....................................................\n");
    
//  ... transfer input complex to sk vector
        for (i = 0; i < rcA[1]; i++)
        {
                sk[i].r = inputAr[i];
                sk[i].i = inputAi[i];
        }
// rows in the Hankel Matrix
    inputNumberOfRows = mxGetPr(prhs[2]);  numberOfRows=(int)(inputNumberOfRows[0]);
    printf(" Number of Rows of Hankel Matrix\n", numberOfRows);
// ...  end of transfer


//	....................................
	printf(" size of array data matrix %d by %d\n", rcA[0], rcA[1]);
    S = covMat(sk, rcA[1], rcS, numberOfRows); numberOfRows = rcS[0];
    printf(" size of Hankel %d %d\n", rcS[0], rcS[1]);
    if (D >= rcA[1]) { mexErrMsgTxt("!. NO SOLUTION\n"); }
//  Singular Value Decomposition
    eigValues = myAlloc(rcS[1]);
    E = myAlloc2Complex(rcS[1], rcS[1]);
    U = mySvd(S, E, rcS, D,eigValues); // signal matrix from left hand vectors
    printf(" size of signal matrix %d by %d\n",rcS[0],D);
//  ..............................
//  Least Square Solution
    phi = Svd2Lsq(U, rcS, D, rcPhi);
//  Eigen Values of Phi
    eigVc = myAllocComplex(D);
    eigVc = eigPhi(phi, E, D);

    eigv = myEigenPhi(phi, rcPhi);
    phase = myAlloc(rcPhi[0]); theta = myAlloc(rcPhi[0]);
    pole = myAlloc(rcPhi[0]); temp = myAlloc(rcPhi[0]);
    for (k = 0; k < rcPhi[0]; k++)
    {
        //arg = eigv[k].i / eigv[k].r;
        pole[k] = sqrt( (eigv[k].r) * (eigv[k].r) + (eigv[k].i) * (eigv[k].i) );
        phase[k] = atan2(eigv[k].i, eigv[k].r) * (180.0 / pi);
        theta[k] = asin(-phase[k] / 180) * (180 / pi);
    }

    indx = Low2High(rcPhi[0], phase);
    for (k = 0; k < rcPhi[0]; k++) temp[k] = pole[indx[k]];
    for (k = 0; k < rcPhi[0]; k++) pole[k] = temp[k];

    printf(" size of phi %d by %d\n", rcPhi[0], rcPhi[1]);
// 
//  ................. transfer data to MATLAB
    // par eigen vectors
    plhs[0] = mxCreateDoubleMatrix(rcPhi[0], rcPhi[1], mxCOMPLEX);
    EPtr = mxGetPr(plhs[0]); EPti = mxGetPi(plhs[0]);
    for (p = 0; p < rcPhi[0]; p++) // rows
    {
        for (i = 0; i < rcPhi[1]; i++)
        {
                kt = i* rcPhi[0] + p;
                EPtr[kt]  = phi[p][i].r; // updated 12th May 2024
                EPti[kt]  = phi[p][i].i; // updated 12th May 2024
        }
    }
    // par eigen values
    plhs[1] = mxCreateDoubleMatrix(1, rcS[1], mxREAL);
    eigValuePtr = mxGetPr(plhs[1]);
    for (i = 0; i < rcS[1]; i++) eigValuePtr[i] = eigValues[i];

    // par data matrix
    plhs[2] = mxCreateDoubleMatrix(rcS[0], rcS[1], mxCOMPLEX);
    SPtr = mxGetPr(plhs[2]); SPti = mxGetPi(plhs[2]);
    for (p = 0; p < rcS[0]; p++) // rows
    {
        for (i = 0; i < rcS[1]; i++)
        {
            kt = i * rcS[0] + p;
            SPtr[kt] = S[p][i].r; // updated 12th May 2024
            SPti[kt] = S[p][i].i; // updated 12th May 2024
        }
    }
// par Phase angles Vector
    plhs[3] = mxCreateDoubleMatrix(rcPhi[0], 1, mxREAL);
    phiPtr = mxGetPr(plhs[3]); 
    for (i = 0; i < rcPhi[0]; i++) phiPtr[i] = phase[i];


 // par Pole Position Vector
    plhs[4] = mxCreateDoubleMatrix(rcPhi[0], 1, mxREAL);
    polePtr = mxGetPr(plhs[4]); 
    for (i = 0; i < rcPhi[0]; i++) polePtr[i] = pole[i];


	return;
}

complex* myEigenPhi(complex** phi, int* rcPhi)
{
    int k,n,i,kt,p;
    double* inputPtr, * inputPti;
    double* br, * bi;
    complex* b;
    mxArray* prhs[1];
    mxArray* plhs[1];
    n = rcPhi[0];
    b = myAllocComplex(n);
    prhs[0] = mxCreateDoubleMatrix(n, n, mxCOMPLEX);
    plhs[0] = mxCreateDoubleMatrix(n, 1, mxCOMPLEX);
    inputPtr = mxGetPr(prhs[0]);   inputPti = mxGetPi(prhs[0]);
    for (p = 0; p < rcPhi[0]; p++) // rows
    {
        for (i = 0; i < rcPhi[1]; i++)
        {
            kt = i * rcPhi[0] + p;
            inputPtr[kt] = phi[p][i].r; 
            inputPti[kt] = phi[p][i].i; 
        }
    }
    mexCallMATLAB(1, plhs, 1, prhs, "eig");
    br = mxGetPr(plhs[0]);     bi = mxGetPi(plhs[0]);
    for (k = 0; k < n; k++)
    {
        b[k].r = br[k]; b[k].i = bi[k];
    }
    mxDestroyArray(prhs[0]);
    mxDestroyArray(plhs[0]);
    return b;
}


    void usageGMu()
    {
        char* today; int width = 100;
        today = (char*)malloc(sizeof(char) * width);
//        today = getDate();
//        printf("  %s\n", today);
        printf("  %%updated on 21st Jun 2025 @ 11:38pm Belle Mead NJ\n");
        printf("  %% IMPORTANT ESPRIT LHS number of parameters\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  DOAS =[20, -35, 30]; POWS = [1 1 1]; muSamples = 90;\n");
        printf("  snapShots = 16; NumOfElements =31;\n");
        printf("  std = 1; SamplesPerCycle = 8;\n");
        printf("  D = 3;  dbyl = 0.5;\n");
        printf("  numberOfRows = 10;);\n");
        printf("  rcA =[snapShots NumOfElements];\n");
        printf("  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);\n");
        printf("  sk = A(k, :);\n");
        printf("  Number of Inputs 3\n");
        printf("  1. D number of sources\n");
        printf("  2. sk complex time or space shifted series\n");
        printf("  3. Number of rows in the Hankel Matrix\n");
        printf("  [phimat L Sh omega pole] = espritUla(D, sk, numberOfRows);\n");
        printf("  Number of Outputs 5\n");
        printf("  1. phimat is the LSQ output matrix\n");
        printf("  2. L eigen values of Hermitian\n");
        printf("  3. Sh Signal Hankel Matrix\n");
        printf("  4. Phase in degrees\n");
        printf("  5. Pole position\n");
        printf("  theta = asind(-omega / 180);\n");
        printf("  %%You may reach kaluri@ieee.org Dr Kaluri Princeton NJ\n");
        printf("  .....................................................\n");
        return;
    }

    



  


   
    
    
    
    
    


 











