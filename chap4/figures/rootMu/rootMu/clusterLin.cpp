// clusterLin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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
#include "stdafx.h"
#include "clusterLin.h"
char* getDate();
#include "mex.h"   /* This one is required */
FILE* fp;



void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputData;
    double* localData;
    double* numOfPartitions{};
    double* JkCptr;
    double** clouds,closenessFactor=0.3;
    int** pointers,** newParts;
    int maxNumberOfPartitions = 12, k, p, r, c, i,kmax;
    int lenD,s,e,er;
    int rcA[2];
    int *rcClouds;
    int* indx,newrows,flag=1;
    char* date{};


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
    printf("size of input data %d by %d\n", r, c);
    localData = myAlloc(lenD); indx = myAllocI(lenD);
    for (k=0; k<lenD; k++) localData[k]=inputData[k];

    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if (r != 1) { printf("!. must be a scalar \n"); return; }
    if (c != 1) { printf("!. must be a scalar \n"); return; }
    er = fopen_s(&fp, "partition.tex", "w");
    numOfPartitions = mxGetPr(prhs[1]); 
    maxNumberOfPartitions = (int)(numOfPartitions[0]);
    date = getDate();
    fprintf(fp, "%%            Date %s\n", date);
    printf("            Length of Data %d\n",lenD);
    printf("            Maximum number of partitions %d\n",maxNumberOfPartitions);
    for(k=0; k<lenD; k++) printf("            [%d] %3.4f \n",k,localData[k]);
    rcClouds = myAllocI(2); rcClouds[0] = 6; rcClouds[1] = 6;

//  ....................................... 
    clouds = segment(localData, rcClouds, lenD, maxNumberOfPartitions, closenessFactor);
//    for (k = 0; k < rcClouds[0]; k++)
//    {
//        for (i = 0; i < 4; i++) printf("%3.4f ", clouds[k][i]); printf("\n");
//    }

    //kmax = kmax-1;
    c = 4; r = rcClouds[0];
    fprintf(fp, "            Actual Clusters %d\n",r);

    plhs[0] = mxCreateDoubleMatrix(r, c, mxREAL);
    JkCptr = mxGetPr(plhs[0]);


      for (p = 0; p < r; p++)
      {
          for (i = 0; i < c; i++)
          {
                  JkCptr[i*r+p]  = clouds[p][i]; // this is needed for MATLAB applications
          }
      }
      free(localData);
      fclose(fp);
    return;
}
