// clusterLin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "clusterLin.h"
#include "mex.h"   /* This one is required */



int main()
{
    printf("hello\n");
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputData;
    double* numOfPartions;
    double* JkCptr;
    int** pointers;
    int N = 12, k, p, r, c, i,kmax;
    int lenD;
    int rcA[2];



    if ((nlhs != 1) || (nrhs != 2))
    {
        printf("!. Usage Error Parameters Left Hand Side = %d(1) .. Right Hand Side = %d(2) \n", nlhs, nrhs);
	    printf("1. a=clusterLin(L',kmax)\n");
	    printf("2. L is array to be clustered\n");
	    printf("3. kmax is maximum estimated clusters\n");
	    printf("4. a has 2 columns and rows as many clusters\n");
    return;
    }

    r = (int)(mxGetM(prhs[0])); c = (int)(mxGetN(prhs[0]));
//    printf("size of input %d by %d\n",r,c);
    if (r != 1) { printf("!. must be a row vector try to transpose\n"); return; }
    inputData = mxGetPr(prhs[0]); lenD = c;
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if (r != 1) { printf("!. must be a scalar \n"); return; }
    if (c != 1) { printf("!. must be a scalar \n"); return; }
    numOfPartions = mxGetPr(prhs[1]); N = (int)(numOfPartions[0]);
//    for(k=0; k<lenD; k++) printf("%3.4f ",inputData[k]); printf("\n");
    printf("Length of Data %d \nMaximum number of partitions %d\n",lenD,N);
//  .......................................    
//    pointers = getCloudPointers(inputData, lenD, N, &kmax);
    pointers = getCloudTotalPt(inputData, lenD, N, &kmax);
    printf("Actual Number of Partitions %d\n",kmax);
    //kmax = kmax-1;
    plhs[0] = mxCreateDoubleMatrix(kmax, 2, mxREAL);
    JkCptr = mxGetPr(plhs[0]);
    printf("Actual Clusters %d\n",kmax);    
    c = 2; r = kmax;

      for (p = 0; p < r; p++)
      {
          for (i = 0; i < c; i++)
          {
                  JkCptr[i*r+p]  = pointers[p][i] + 1; // this is needed for MATLAB applications
          }
      }
    return;
}
