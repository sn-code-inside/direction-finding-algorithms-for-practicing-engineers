// rootMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "rootMusic.h"
#include "mex.h"   /* This one is required */
double** processRoots(double **, int *, double);
int* Low2High(int, double*);
double** rootPairs(double **, int);
double** myRoots(complex**, int, int,int*);
complex* polyRoots(complex*, int);

double** myRoots(complex **En, int r, int c, int* rows)
{
    int i, k,rc,kt;
    complex* a, * b;
    complex* total;
    double pi = atan(1.0) * 4.0;
    double** B,theta;
    rc = r * c;
    a = myAllocComplex(c); total = myAllocComplex(rc);
    B = myAlloc2(rc, 3);
    kt = 0;
    for (i = 0; i < r; i++)
    {
        for (k = 0; k < c; k++)
        {
            a[k] = En[i][k];
//            printf("(%3.4f %3.4f)  ", a[k].r, a[k].i);  
        }  //printf("\n");
        b = polyRoots(a, c);
        for (k = 0; k < c - 1; k++)
        {
//            printf("roots %3.4f %3.4f\n", b[k].r, b[k].i);
            total[kt] = b[k];
            B[kt][2] = i;
            kt = kt + 1;
        }
    }
    for (k = 0; k < kt; k++)
    {
        B[k][1] = sqrt(total[k].r * total[k].r + total[k].i * total[k].i);
//        theta = atan2(-total[k].i , total[k].r);
        theta = atan2(total[k].i , total[k].r);
        B[k][0] = theta * 180.0 / pi;
    }
    rows[0] = kt;
    return B;
}

complex* polyRoots(complex* a, int c)
{
    int k;
    double* inputPtr, * inputPti;
    double* br, * bi;
    complex* b;
    mxArray* prhs[1];
    mxArray* plhs[1];
    b = myAllocComplex(c - 1);
    prhs[0] = mxCreateDoubleMatrix(1, c, mxCOMPLEX);
    plhs[0] = mxCreateDoubleMatrix(c - 1, 1, mxCOMPLEX);
    inputPtr = mxGetPr(prhs[0]);   inputPti = mxGetPi(prhs[0]);

    for (k = 0; k < c; k++) { inputPtr[k] = a[k].r; inputPti[k] = a[k].i; }
    mexCallMATLAB(1, plhs, 1, prhs, "roots");

    br = mxGetPr(plhs[0]);     bi = mxGetPi(plhs[0]);
    for (k = 0; k < c - 1; k++)
    {
        b[k].r = br[k]; b[k].i = bi[k];
    }
    mxDestroyArray(prhs[0]);
    mxDestroyArray(plhs[0]);
    return b;

}


double** rootPairs(double **B, int kmax)
{
    int i,k,*indx;
    double *rVal;
    double **C;
    double pi = atan(1.0)*4.0;
    rVal = myAlloc(kmax);
    C = myAlloc2(kmax,4);
    for (i=0; i<kmax; i++) rVal[i] = B[i][1]*sin(B[i][0]*(pi/180.0));
    indx = Low2High(kmax,rVal);
    for (k=0; k<kmax; k++)
    {
        C[k][0] = B[indx[k]][0];
        C[k][1] = B[indx[k]][1];
        C[k][2] = rVal[k];
        C[k][3] = B[indx[k]][2];
    }
    return C;
}

double** processRoots(double **A, int *km, double close2UnitCircle)
{
    int k,i,kt,kmax;
    double r,delr,**B;
    int *indx;
    kmax = km[0];
    indx = myAllocI(kmax);
//  pass 1    
    i = 0;
    for (k=0; k<kmax; k++)
    {
        r = A[k][1]; delr = 1.0-r;
        if (fabs(delr) < close2UnitCircle )
        { indx[i] = k; i = i+1; }
    }
    B = myAlloc2(i,2);
    for (k=0; k<i; k++)
    {
        kt = indx[k];
        B[k][0] = A[kt][0]; B[k][1] = A[kt][1];
    }
    km[0] = i;
    free(indx);
    return B;
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputData,*inputEr,*inputEi,*inputDelr;
    double** thetaNr,**B,**C,**D;
    double* outPtr;
    double close2UnitCircle=0.2;
    int p,r,c,i,k,kt,numOfPoles,rEn,cEn, numOfRoots;
    complex** En;

    if ((nlhs != 1) || (nrhs != 2))
    {
        printf("!. Updated on 26th Jan 2025 11:30pm sign of angle fix\n");
        printf("!. Usage Error Parameters Left Hand Side = %d(1) .. Right Hand Side = %d(2) \n", nlhs, nrhs);
	    printf("1. b=rootMusic(En,delr)\n");
	    printf("2. En is noise Eigen Vectors of Covariance Matrix\n");
	    printf("3. delr is distance away from unit circle say 0.2\n");
	    printf("4. b has 3 columns third column is projection on y-axis r sin(theta)\n");
    return;
    }

    rEn = (int)(mxGetM(prhs[0])); cEn = (int)(mxGetN(prhs[0]));
    inputEr = mxGetPr(prhs[0]); inputEi = mxGetPi(prhs[0]);
    En = myAlloc2Complex(rEn, cEn);
    for (p = 0; p < rEn; p++) // rows
    {
        for (i = 0; i < cEn; i++)
        {
            kt = i * rEn + p;
            En[p][i].r = inputEr[kt];
            En[p][i].i = inputEi[kt];
        }
    }
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if (r != c) {mexErrMsgTxt("!. prhs[1] must be a scalar\n");}
    else {if (r != 1) {mexErrMsgTxt("!. prhs[1] must be a scalar\n");}}
    inputDelr = mxGetPr(prhs[1]); close2UnitCircle = inputDelr[0];
    printf(" Closeness to Unit Circle %3.4f\n",close2UnitCircle);
    D = myRoots(En, rEn, cEn, &numOfPoles);
    printf("1. maximum number of roots %d\n", numOfPoles);
    B = processRoots(D, &numOfPoles,close2UnitCircle);
    C = rootPairs(B, numOfPoles);
    plhs[0] = mxCreateDoubleMatrix(numOfPoles, 4, mxREAL);
    outPtr = mxGetPr(plhs[0]);
//  ....................................... 
for (p = 0; p < numOfPoles; p++)
      {
          for (i = 0; i < 4; i++)
          {
                 outPtr[i* numOfPoles +p]  = C[p][i];
          }
      }


    return;
}
