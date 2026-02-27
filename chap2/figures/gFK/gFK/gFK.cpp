// gFK.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include "gFK.h"
//#include "mex.h" 
int main()
{
    complex** A;
    int er,rcA[2];
    double fn = 0.2, phiD = 20.0;
    rcA[0] = 128; rcA[1] = 2;
    A = myAlloc2Complex(rcA[0], rcA[1]);
    populate(A, rcA, fn, phiD);
    er = gFKmain(A,rcA);
    return er;
}

double** getPar
(
    complex** A,
    double* config,
    int* bins,
    complex** steering,
    double* sAvg,
    complex** S,
    double** rgMat,
    double *sg,
    int* error
)
{
    int rc[2], cby2;
    int maxLengthOfFileName = 60;
//    double* sg;
    int RC[2] = { 20,3 };
    int kmax;
    int k ,j;
    double threshold; // **M,kmuTime,muTime;


    double* rg;
    int zerofill = 8;
    int synthetic, numberOfTgts, numOfPhaseSpecSamples, FFTsamples;

    synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);
    numOfPhaseSpecSamples = (int)(config[5]); FFTsamples = (int)(config[7]);
    kmax = (int)(config[6]);
    rc[0] = FFTsamples; rc[1] = (int)(config[13]); cby2 = rc[1] / 2;
 //   sg = (double*)malloc(numberOfTgts * sizeof(double));
    preProc(A, S, sAvg, config, zerofill);
    threshold = detectBins(sAvg, config, bins);
    printf("!. lo/Hi peaks %3.4f\n", threshold);
    if (threshold < 0.0) error[0] = -1; else error[0] = 1;
    numberOfTgts = (int)(config[4]);
    rg = rgSteering(A, config, bins, rgMat, sg, steering);
 //   for (j = 0; j < cby2; j++)
 //   {
 //       for (k = 0; k < numberOfTgts; k++) printf("[%d] r.%3.4f i.%3.4f\n", k,steering[k][j].r, steering[k][j].i);
 //   }
    return rgMat;
}

void printConfig(double *config)
{

    printf("!. 1. rcon[0] alpha slope in MhZ per micro second [%3.4f]\n", config[0]);
    printf("!. 2. rcon[1] Fs sampling frequency in KhZ [%3.4f]\n", config[1]);
    printf("!. 3. rcon[2] control program control 1  0 -1 -2 [%d]\n", (int)(config[2]));
    printf("!. 4. rcon[3] synthetic data 0 or 1 [%d]\n", (int)(config[3]));
    printf("!. 5. rcon[4] numberOfTgts [%d]\n", (int)(config[4]));
    printf("!. 6. rcon[5] N number of samples in the phase sepctrum kMUSIC [%d]\n", (int)(config[5]));
    printf("!. 7. rcon[6] kmax is the number of time A matrix is read from file [%d]\n", (int)(config[6]));
    printf("!. 8. rcon[7] numberOfTgts [%d]\n", (int)(config[7]));
    printf("!. 9. rcon[8] samples for FFT [%d]\n", (int)(config[8]));
    printf("!. 0. rcon[9] acquired ADC samples [%d]\n", (int)(config[9]));
    printf("!. 1. rcon[10] a flag needed [%d]\n", (int)(config[10]));
    printf("!. 2. rcon[11] range gain [%3.4f]\n", config[11]);
    printf("!. 3. rcon[12] amplitude threshold in double** sortCluster(..) [%3.4f]\n", config[12]);
    printf("!. 4. rcon[13] number of real columns of matrix [%d]\n", (int)(config[13]));
    printf("!. 5. rcon[14] number of gold section iterations [%d]\n", (int)(config[14]));
}


int gFKmain(complex **A, int *rcA)
{
    complex **steering, ** S; 
    double* config, * sg;
    int* bins, numberOfTgts, numOfPhaseSpecSamples;
    int cby2, i;
    int kmax = rcA[0];
    int zerofill = 8, error, LenConfig = 20;
    double * sAvg, ** rgMat;

    config = (double*)malloc(LenConfig * sizeof(double));
    for (i = 0; i < LenConfig; i++) config[i] = 0.0;
    //  .. initilise config
    config[4] = 10; config[5] = 180.0; config[6] = rcA[0];
    config[7] = config[6]; config[13] = rcA[1]*2;
    //  ..........................

    
    numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
    kmax = (int)(config[6]);  bins = (int*)malloc(numberOfTgts * sizeof(int));
    rcA[0] = (int)(config[7]); rcA[1] = (int)(config[13]); cby2 = rcA[1] / 2;

    sg = (double*)malloc(numberOfTgts * sizeof(double));
    rgMat = myAlloc2(numberOfTgts, cby2);
    sAvg = myAlloc(rcA[0]);
    S = myAlloc2Complex(rcA[0], cby2);
    steering = myAlloc2Complex(numberOfTgts, cby2);
    sg = (double*)malloc(numberOfTgts * sizeof(double));
    rgMat = getPar(A, config, bins, steering, sAvg, S, rgMat, sg, &error);
    return error;
}

void populate(complex** A, int *rcA, double fn, double phiD)
{
    int i, k,kmax,c;
    double pi,aC,aS,phi,phiR;
    double phi0 = -37.169;
    pi = 4.0 * atan(1.0);
    kmax = rcA[0]; c = rcA[1];
    for (i = 0; i < c; i++)
    {
        phi = phi0 + i * phiD; phiR = phi * pi / 180.0;
        printf("[%d] phi degrees %3.4f\n",i,phi);
        for (k = 0; k < kmax; k++)
        {
            A[k][i].r = sin(2 * pi * fn * k+phiR);
            A[k][i].i = cos(2 * pi * fn * k+phiR);
        }
    }
    return;
}

void usage()
{
    printf("  config = zeros([1 20]);\n");
    printf("  rcA(1) = 128; rcA(2) = 4; f = 0.2; phiD = 20;\n");
    printf("  config(5) = 10; config(6) = 180.0; config(7) = rcA(1);\n");
    printf("  config(8) = config(7); config(14) = rcA(2) * 2;\n");
    

    printf("  alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
    printf("  synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n");
    printf("  numOfPhaseSpecSamples = (int)(config[5]);\n");
    printf("  kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");

    printf("[S A b fn bins, peak] = gFKtst(config, [f phiD]);\n");


    printf("  S. plhs[0] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);\n");
    printf("  S. SPtr = mxGetPr(plhs[0]); SPti = mxGetPi(plhs[0]);\n");
    printf("  A. plhs[1] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);\n");
    printf("  A. APtr = mxGetPr(plhs[1]); APti = mxGetPi(plhs[1]);\n");


    printf("  b. plhs[2] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxCOMPLEX);\n");
    printf("  b. steerPtr = mxGetPr(plhs[2]); steerPti = mxGetPi(plhs[2]);\n");
    printf(" fn. plhs[3] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxREAL);\n");
    printf(" fn. rgMatPtr = mxGetPr(plhs[3]);\n");

    printf("bins. plhs[4] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);\n");
    printf("bins. binsPtr = mxGetPr(plhs[4]);\n");
    printf("peak. plhs[5] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);\n");
    printf("peak. sgPtr = mxGetPr(plhs[5]);\n");
    return;
}