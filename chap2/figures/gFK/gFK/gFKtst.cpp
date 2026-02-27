#include "gFKtst.h"
#include "matrix.h"
#include "mex.h"   /* This one is required */
//  ..................................................................
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputAr;
    double *inputAi;
    double *inputPr;
    double *inputPhiFnPtr;
    double *binsPtr;
    double *steerPtr, *steerPti;
//    double *EnPtr, *EnPti;
//    double *steerAvgPtr, *steerAvgPti;
    double *SPtr, *SPti,*APtr,*APti;
    double *sgPtr,*rgMatPtr;
    double *configPtr;
//    double *doasPtr,*MudoasPtr,*sPtr,*sAvgPtr,*ObjPtr,*rgMatPtr;
//    double *dataPtr;
    int p,kt,r,c;
//    
//  .. c code declarations
    int rc[2],rcA[2];
    complex **A,**steering, ** S; 
    double* config, * sg;
    int* bins, numberOfTgts, numOfPhaseSpecSamples;
    int cby2, i;
    int kmax = rcA[0];
    int zerofill = 8, error, LenConfig = 20,flag;
    double * sAvg, ** rgMat;
    double fn = 0.2, phiD = 0.0;
    config = (double*)malloc(LenConfig * sizeof(double));
    for (i = 0; i < LenConfig; i++) config[i] = 0.0;
    
    if ( (nlhs != 7) || (nrhs != 2) )
    {
        printf("  Usage Error Parameters Left Hand Side = %d(6) .. Right Hand Side = %d(2) \n",nlhs,nrhs);
        usage();
        return;
    } 
    r = (int)(mxGetM(prhs[0])); LenConfig = (int)(mxGetN(prhs[0]));

    if ( r != 1) 
    { 
        printf(" try transpose \n");
        printf(" size of input matrix %d by %d\n",r,LenConfig);
        return;
    } else
    {
            inputPr = mxGetPr(prhs[0]); config = myAlloc(LenConfig);
            for (i = 0; i < LenConfig; i++) config[i] = inputPr[i];
    }
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    printf(" size of input matrix %d by %d\n",r,c);
    if (r !=1 ) {printf(" try transpose \n");
        return;}
    if (c != 2 ) {printf("need two parameters fn and phiD\n"); return;}
    else { 
        inputPhiFnPtr=mxGetPr(prhs[1]); 
        fn = inputPhiFnPtr[0]; phiD = inputPhiFnPtr[1];}

    numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
    kmax = (int)(config[6]);  bins = (int*)malloc(numberOfTgts * sizeof(int));
    rc[0] = (int)(config[7]); rc[1] = (int)(config[13]); cby2 = rc[1] / 2;
    rcA[0] = rc[0]; rcA[1] = cby2;
    printf("size of matrix A %d by %d",rcA[0],rcA[1]);
    A = myAlloc2Complex(rcA[0], rcA[1]);

    populate(A, rcA, fn, phiD);

    rgMat = myAlloc2(numberOfTgts, cby2);
    sAvg = myAlloc(rcA[0]);
    S = myAlloc2Complex(rcA[0], cby2);
    steering = myAlloc2Complex(numberOfTgts, cby2);
    sg = (double*)malloc(numberOfTgts * sizeof(double));
    rgMat = getPar(A, config, bins, steering, sAvg, S, rgMat, sg,&error);
    numberOfTgts = (int)(config[4]);
//  ...............................................................    
//  Transfer the output
    plhs[0] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);
    SPtr = mxGetPr(plhs[0]); SPti = mxGetPi(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);
    APtr = mxGetPr(plhs[1]); APti = mxGetPi(plhs[1]); 
   for (p = 0; p < rcA[0]; p++) // rows
    {
        for (i = 0; i < cby2; i++)
        {
                kt = i*rcA[0]+p;
                SPtr[kt]  = S[p][i].r;
                SPti[kt]  = S[p][i].i;
                APtr[kt]  = A[p][i].r; 
                APti[kt]  = A[p][i].i; 
        }
   }

  plhs[2] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxCOMPLEX);
  steerPtr = mxGetPr(plhs[2]); steerPti = mxGetPi(plhs[2]);  
  plhs[3] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxREAL);
  rgMatPtr = mxGetPr(plhs[3]);  
  for (p = 0; p < numberOfTgts; p++) // rows
    {
        for (i = 0; i < cby2; i++)
        {
                kt = i*numberOfTgts+p;
                steerPtr[kt]     = steering[p][i].r;
                steerPti[kt]     = steering[p][i].i;
                rgMatPtr[kt]     = rgMat[p][i];
        }
    } 
    plhs[4] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);
    binsPtr = mxGetPr(plhs[4]);
    plhs[5] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);
    sgPtr = mxGetPr(plhs[5]);
    for (p = 0; p < numberOfTgts; p++) 
    { binsPtr[p] = bins[p]; sgPtr[p] = sg[p];}
    plhs[6] = mxCreateDoubleMatrix(LenConfig, 1, mxREAL);
    configPtr = mxGetPr(plhs[6]);
    for (p = 0; p < LenConfig; p++) configPtr[p]=config[p];
    return;
}
