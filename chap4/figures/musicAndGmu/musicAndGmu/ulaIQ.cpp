/*
 
    ulaIQ.cpp Program for Signal Generation for ULA
 
*/
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
//#include "mex.h"   /* This one is required */
#include "ulaIQ.h"
complex ** IQ(int *rcA,int d,double *DOAS, double *POWS,double d_by_lambda, double N,double noise_variance, double *SNR)
{
    int D; // NUMBER OF EMITTERS
//    double POWS[3] = { 1.0, 1.0, 1.0 };
    double PHIS[3] = { 0.0, 0.0, 0.0 };
    int maxk; // NUMBER OF SNAPSHOTS
    int M;  // NUMBER OF ELEMENTS
    //double d_by_lambda = 0.5; // SPACING / WAVELENGTH
    //double noise_variance = 0.1;// NOISE VARIANCE
    //double SnapC = 50; // NUMBER OF COARSE SNAPSHOTS
    //double N = 8; // SAMPLES PER CYCLE
    double fn = 1.0 / N; // NORMALIZED FREQUENCY
    double theta = 0.0; // ULA normal angle with true North in degrees
    //double SNR;
    int i, k;
    complex** A, **B;
    maxk = rcA[0]; M = rcA[1]; D = d;
    B = myAlloc2Complex(maxk, M);
    A = GenerateSignals(
    M, /* each ULA has M elements */
    maxk, /* number of snapshots */
    D, /* number of emitters */
    DOAS, /* doa angles in degrees -180 to +180 */
    POWS, /* signal relative ratios */
    PHIS, /* signal initial phases in degrees */
    d_by_lambda, /* d by lambda */
    fn, /* fc/fs or sampling rate */
    theta, /* ULA normal angle with true North in degrees */
    noise_variance, /* sigma of the WGN */
    SNR /* SNR output */
    );
    printf(" SNR 10*log10(signal power/noise power) %f\n", SNR[0]);

    for (i = 0; i < M; i++)
    {
        for (k = 0; k < maxk; k++) B[k][i] = A[i][k];
    }
 //   rcA[0] = maxk; rcA[1] = M;
 //   printComplxMatrix(B, maxk, M);

	return B;
}

complex ** GenerateSignals(
    int M, /* each ULA has M elements */
    int maxk, /* number of snapshots */
    int D, /* number of emitters */
    double* DOAS, /* doa angles in degrees -90 to +90 */
    double* POWS, /* signal relative ratios */
    double* phi, /* signal initial phases in degrees */
    double dn, /* d by lambda */
    double fn, /* fc/fs or sampling rate */
    double theta, /* ULA normal angle with true North in degrees */
    double std, /* sigma of the WGN */
    double* SNR /* SNR */
)
{
    int s, m, k, seed, ** b;
    double p;
    double rnd, np, sp,sk,sn,*gn;
    double pi = atan(1.0) * 4.0;
    complex **A, **noise;
    cadd add;
    printf(" Normalised Frequency %3.4f d by lambda %3.4f\n", fn,dn);
    printf(" Emmiters DOA (deg) and Their Strengths\n");
    for (m = 0; m < D; m++)  printf(" %f ", DOAS[m]);
    printf("\n");
    for (m = 0; m < D; m++)  printf(" %f ", POWS[m]);
    printf("\n");
    printf(" Number of Snap shots %d\n", maxk);
    printf(" Number of Channels %d\n", M);
    seed = (int)(time(NULL));    srand(seed);

    b = myAlloc2I(D, maxk);   
    gn = myAlloc(maxk);


    for (k = 0; k < maxk; k++)
    {
        for (s = 0; s < D; s++)
        {
            rnd = rand(); sk = (rnd / 32767.0) - 0.5;
            if (sk < 0) b[s][k] = -1; else b[s][k] = 1;
//            if (sk < 0) b[s][k] = rand(); else b[s][k] = rand();
        }
    }
    noise = gnoise(M, maxk, std, &np);
    /* normalize powers */
    p = 0.0; /* this will be set to the maximum value */
    for (s = 0; s < D; s++)
    {
        if (p < POWS[s])    p = POWS[s]; 
    }
    if (p > 0.0)
    {
        for (s = 0; s < D; s++) POWS[s] = POWS[s] / p;
    }

    /* Signals at A */
    A = signalMat(M, maxk, fn, b, DOAS, POWS, phi, theta, dn, &sp, D);
    for (m = 0; m < M; m++)
    {
        for (k = 0; k < maxk; k++) A[m][k] = add.add(A[m][k], noise[m][k]);
    }  

//    sp = sp / D;
    printf(" Noise Variance %3.4f\n", std);
    printf(" Noise Power %3.4f \n", np);
    printf(" Signal Power %3.4f\n", sp);
    sn = sp / np;
    printf(" Signal by Noise power Ratio %3.4f\n", sn);
    SNR[0] = 10 * log10(sn);
    printf(" SNR = 10 * log10(sp / np) %3.4f\n", SNR[0]);
    myFree2I(b, D); myFree2Complex(noise, M);
    return A;
}

double powerOfMat(int M,int maxk,complex **A)
{ 
    int k, m;
    complex sum;
    conjmul mulconj;
    double *sp,spower;
    sp = myAlloc(M);
    spower = 0.0;
    for (m = 0; m < M; m++)
    {
        sp[m] = 0.0;
        for (k = 0; k < maxk; k++)
        {
            sum = mulconj.mulconj(A[m][k], A[m][k]);
            sp[m] = sp[m] + sum.r; // signal power
        }
        sp[m] = sp[m]/(double)(maxk);
        spower = spower + sp[m];
    }
    spower = spower/(double)(M);
    return spower;
}

complex** signalMat
(
    int M,        /* each ULA has M elements */
    int maxk,     /* number of snapshots */
    double fn,    /* fc/fs or sampling rate */  
    int **b,      /* integer modulation +1 or -1 */
    double *DOAS, /* doa angles in degrees -90 to +90 */
    double *POWS, /* signal relative ratios */
    double *phi,  /* signal initial phases in degrees */
    double theta, /* ULA normal angle with true North in degrees */
    double dn,    /* d by lambda */
    double* sigP, /* signal power */
    int D         /* number of emitters */
)
{
    int k, m, s;
    double thetaT,phiT,phsAr,phs0,phsT;
    double Amp;
    double pi = 4.0 * atan(1.0);
    complex** A, x, y, phix; 
    cmul mul; cadd add;
    A = myAlloc2Complex(M, maxk);
 
    for (m = 0; m < M; m++)
    {
        for (k = 0; k < maxk; k++)
        {
            A[m][k].r = 0.0; A[m][k].i = 0.0;
            for (s = 0; s < D; s++)
            {
                thetaT = -DOAS[s] + theta;
                phiT = 2 * pi * dn * sin(thetaT * pi / 180);
                phsAr = (double)(m)*phiT; // physical orientation
                phs0 = phi[s] * pi / 180;
                phsT = phs0 + phsAr;

                Amp = b[s][k] * POWS[s];
                x.r = Amp * cos(2 * pi * fn * (double)(k)); // x = e^(j2 pi fn k)
                x.i = Amp * sin(2 * pi * fn * (double)(k));

                phix.r = cos(phsT); // phix = e^(j phix)
                phix.i = sin(phsT);

                y = mul.mul(x, phix); // y = x * phix
                A[m][k] = add.add(A[m][k], y);
            }
        }
    }
    sigP[0] =  powerOfMat(M,maxk,A);
    return A;
}

complex** gnoise(int M, int maxk, double std, double *noisePower)
{
    int m, k,s;
    double rnd;
    complex** noise; 
    noise = myAlloc2Complex(M, maxk);
    for (m = 0; m < M; m++)
    {
        for (k = 0; k < maxk; k++)
        {
            rnd = 0.0; for (s = 0; s < 12; s++) rnd = rnd + ((rand() / 32767.0) - 0.5);
            noise[m][k].r = rnd * std;

            rnd = 0.0; for (s = 0; s < 12; s++) rnd = rnd + ((rand() / 32767.0) - 0.5);
            noise[m][k].i = rnd * std;
        }
    }
    noisePower[0] =  powerOfMat(M,maxk,noise);
    return noise;
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
        printf("  updated on 11th May 2024 @ 11:59pm Princeton NJ\n");
        printf("  clc; clear all;\n");
        printf("  close all;\n");
        printf("  DOAS = [20, -35, 25];\n");
        printf("  std = 1;\n");
        printf("  fn = 1; N = 1 / fn;\n");
        printf("  D = 2; snapShots = 32;\n");
        printf("  NumOfElements = 6;\n");
        printf("  rcA = [snapShots NumOfElements];\n");
        printf("  [muSpk doa] = gMusic(DOAS, std, N, D, rcA);\n");
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

