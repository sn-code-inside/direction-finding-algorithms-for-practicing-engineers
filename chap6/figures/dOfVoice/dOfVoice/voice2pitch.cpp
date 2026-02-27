// getP.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "voice2pitch.h"
#include "mex.h"   /* This one is required */


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
//  ......... MATLAB Variables ..........   
    double *inputPrN, *inputPrK,*inputPrw,*pitchPtr, *kPtr, *unPtr,*un;
    double *xPtr,*yPti,*sPtr,*binPtr,*pClstPtr, *pPtr, * pPti;
//  .....................................    
    int maxLengthOfFileName = 20;
    int r,c,Ni,N,M,Nby2,i,flag,k,er,kt;
    int waveletWindow = 64;

    complex *z;
    int rows = 3;
    double *x, **p, **pitchTable;
    double* config;
    int numberOfPeaksInBins=60,*bins,pitchClusterRows;
    char *wavfile;
    config = myAlloc(20);
    

    if ( (nlhs != 6 ) || (nrhs != 4) )
    {
            printf("!. Right Hand Side 4 parametrs\n");
            printf("!.[1] voice input u\n");
            printf("!.[2] Number of Pitch Peaks rows\n");
            printf("!.[3] block index k\n"); 
            printf("!.[4] Waveletwindow say 32 \n"); 
            printf("!. Left Hand Side 5 parametrs\n");
            printf("!.[1] voice data N\n");
            printf("!.[2] Mag Spectrum N/2\n");
            printf("!.[3] complex Spectrum N\n");
            printf("!.[4] Wavelet Transform Output N\n");
            printf("!.[5] spectral peak bin numbers\n");
            printf("!.[6] Pitch Cluster Pointers\n");
            mexErrMsgTxt("LHS or RHS parameters donot match");
            return;
    }
    r = (int)(mxGetM(prhs[0])); c = (int)(mxGetN(prhs[0]));
    if ( r !=1 ) { printf("rhs[0] must be a row vector try transpose\n"); return; }
    unPtr = mxGetPr(prhs[0]); N = c; // important

    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if ( r !=1 )
    { if (c != 1) printf("rhs[1] must be a scalar\n"); return; }
    inputPrN = mxGetPr(prhs[1]); rows =(int)(inputPrN[0]);

    r = (int)(mxGetM(prhs[2])); c = (int)(mxGetN(prhs[2]));
    if ( r !=1 )
    { if (c != 1) printf("rhs[1] must be a scalar\n"); return; }
    inputPrK = mxGetPr(prhs[2]); k =(int)(inputPrK[0]);

    r = (int)(mxGetM(prhs[3])); c = (int)(mxGetN(prhs[3]));
    if ( r !=1 )
    { if (c != 1) printf("rhs[1] must be a scalar\n"); return; }
    inputPrw = mxGetPr(prhs[3]); waveletWindow =(int)(inputPrw[0]);

 //  ........................................................................
 //   printf("[%d] ---> \n!. [x,s,z,p,bins] = voice2pitch(%d,%d,%d,%d);\n",k,N,M,k,waveletWindow);
    printf("[x, sp, z, p, bins, pg] = voice2pitch(u[%d], rows[%d], k[%d], waveletWindow[%d]);\n",N,rows,k, waveletWindow);

    N = abs(N);
    Nby2 = N/2; M = (int)(log(N)/log(2));
    un = myAlloc(N);
    for (i = 0; i < N; i++) un[i] = unPtr[i];

    plhs[0] = mxCreateDoubleMatrix(N, 1, mxREAL);
    pitchPtr = mxGetPr(plhs[0]);
    for (i=0; i<N; i++) pitchPtr[i] = un[i];

//  allocate memory
//    bins = (int*)malloc(numberOfPeaksInBins * sizeof(int));
    bins = myAllocI(numberOfPeaksInBins);
    x = myAlloc(N);
    z = myAllocComplex(N);
    p = myAlloc2(rows, N); 
    pitchTable = processWav(N, numberOfPeaksInBins,un,x,z,bins,&pitchClusterRows);


//  ... 2nd and 3rd parameters ......    
//    if (pitchTable == NULL) return;
    if (pitchClusterRows < 0 ) 
    {
        plhs[1] = mxCreateDoubleMatrix(1,1, mxREAL);
        sPtr = mxGetPr(plhs[1]); sPtr[0] = -1;

        plhs[2] = mxCreateDoubleMatrix(1,1, mxREAL);
        xPtr = mxGetPr(plhs[2]); xPtr[0] = -1;
    } 
    else
    {
        plhs[1] = mxCreateDoubleMatrix(Nby2,1, mxREAL);
        sPtr = mxGetPr(plhs[1]); 
        for (i=0; i<Nby2; i++) sPtr[i] = x[i];

        plhs[2] = mxCreateDoubleMatrix(N,1, mxCOMPLEX);
        xPtr = mxGetPr(plhs[2]); yPti = mxGetPi(plhs[2]); 
        for (i=0; i<N; i++) {xPtr[i] = z[i].r;  yPti[i] = z[i].i; }
    }
    if (pitchTable == NULL)
    {
        printf("!. DETECTION FAILED\n");
        plhs[3] = mxCreateDoubleMatrix(1,1, mxREAL);
        pPtr = mxGetPr(plhs[3]);  pPtr[0] = 0.0;

        plhs[4] = mxCreateDoubleMatrix(1, 1, mxREAL);
        binPtr = mxGetPr(plhs[4]); binPtr[0] = 0.0;

        plhs[5] = mxCreateDoubleMatrix(1, 1, mxREAL);
        pClstPtr = mxGetPr(plhs[5]); pClstPtr[0] = 0.0;
        free(x); free(z); free(bins); myFree2(p,rows);
        return;
    }

    if (pitchClusterRows > 0)
    {
        er = pitchEnergy(pitchClusterRows, bins, rows, N, waveletWindow, x, un, p);
        printf("er (%d) Pitch Cluster Rows %d rows %d\n", er,pitchClusterRows,rows);
        rows = er;
    }

    mxDestroyArray(plhs[3]);
 //   plhs[3] = mxCreateDoubleMatrix(rows, N, mxREAL);
    plhs[3] = mxCreateDoubleMatrix(rows, N, mxCOMPLEX);
    pPtr = mxGetPr(plhs[3]); pPti = mxGetPi(plhs[3]);
    for (k = 0; k < rows; k++) // rows = 3
    {
        for (i = 0; i < N; i++) // cols = N
        { 
            kt = i*rows+k; 
            pPtr[kt]  = p[k][i];
            pPti[kt]  = pitchTable[k][1];
        }                
    }

    mxDestroyArray(plhs[4]);
    plhs[4] = mxCreateDoubleMatrix(numberOfPeaksInBins, 1, mxREAL);
    binPtr = mxGetPr(plhs[4]); 
    for (i=0; i<numberOfPeaksInBins; i++)  binPtr[i] = bins[i];

    mxDestroyArray(plhs[5]);
    if (pitchClusterRows > rows) pitchClusterRows = rows;
    plhs[5] = mxCreateDoubleMatrix(pitchClusterRows, 3, mxREAL);
    pClstPtr = mxGetPr(plhs[5]); 
    for (k = 0; k < pitchClusterRows; k++) // rows = pitchClusterRows
    {
        for (i = 0; i < 3; i++) // cols = 3
        { 
            kt = i*pitchClusterRows+k; 
            pClstPtr[kt]  = pitchTable[k][i];
        }                
    }
    free(x); free(z); free(bins); myFree2(p,rows);
    free(un);

    return;
}


