/*
    abcUla.cpp Program for Signal Generation for 3 ULAs, A, B and C
    Dr Kaluri V Ranga Rao
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
#include "abcUla.h"
//#include "mex.h"   /* This one is required */
//  ......................................
//
double* abcUlaArray(
    int D,              /* number of emitters */
    double* DOAS,       /* doa angles in degrees -180 to +180 */
    double* POWS,       /* signal relative ratios */
    double* PHIS,       /* signal initial phases in degrees */
    int M,              /* each ULA has M elements */
    int maxk,           /* number of snapshots */
    double d_by_lambda, /* d by lambda */
    double r_by_lambda, /* r by lambda */
    double fn,          /* fc/fs or sampling rate */
    double stdNoise,    /* std of noise for data ula */
    double **sA,        /* data matrix A */
    double **sB,        /* data matrix B */
    double **sC,        /* data matrix C */
    double **Ha,        /* covarince matrix Ha */
    double **Hb,        /* covarince matrix Hb */
    double **Hc)        /* covarince matrix Hc */
{
    double* SNR,**ha,**hb,**hc;
    int rcA[2],k;
    SNR = GenerateSignals(
        M,           /* each ULA has M elements */
        maxk,        /* number of snapshots */
        D,           /* number of emitters */
        DOAS,        /* doa angles in degrees -180 to +180 */
        POWS,        /* signal relative ratios */
        PHIS,        /* signal initial phases in degrees */
        d_by_lambda, /* d by lambda */
        r_by_lambda, /* r by lambda */
        fn,          /* fc/fs or sampling rate */
        sA,          /* signal A */
        sB,          /* signal B */
        sC,          /* signal C */
        stdNoise     /* std of noise for data ula */
    );
    printf(" SNR of 3 ULA A %3.4f B %3.4f C %3.4f\n", SNR[0], SNR[1], SNR[2]);
    rcA[0] = 2*M+1; rcA[1] = maxk;
    printf(" size of data matrices %d by %d\n", rcA[0], rcA[1]);
    for (k = 0; k < D; k++)
        printf(" emitters %3.4f ", DOAS[k]); printf(" in degrees\n");
    ha = CeqABtrnsp(sA, rcA, " Covarinace Matrix A");
    matAeqB(Ha, ha, rcA[0]);
    hb = CeqABtrnsp(sB, rcA, " Covarinace Matrix B");
    matAeqB(Hb, hb, rcA[0]);
    hc = CeqABtrnsp(sC, rcA, " Covarinace Matrix C");
    matAeqB(Hc, hc, rcA[0]);
    return SNR;
}

void matAeqB(double** A, double** B, int m)
{
    int k, i;
    for (k = 0; k < m; k++)
    {
        for (i = 0; i < m; i++) A[k][i] = B[k][i];
    }
    return;
}


double* myNoise
(
	int maxk,
	double std
)
{
	int s, k;
	unsigned int seed;
	double rnd;
    double* uN;
    uN = myAlloc(maxk);
	seed = (unsigned int)(time(NULL));
	srand(seed);
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri

//	printf(" Test Random Sequence ");
//	for (m = 0; m<5; m++) { temp = (rand() / 32767.0) - 0.5; printf(" %f ", temp); } printf("\n");

	for (k = 0; k<maxk; k++)
	{
		rnd = 0.0; for (s = 0; s<12; s++) rnd = rnd + ((rand() / 32767.0) - 0.5);
		uN[k] = rnd * std;
	}
	return uN;
}


double** CeqABtrnsp(double** A, int* rcA, const char* anot)
{
    int i, m, k, rows, cols;
    double sum, P; 
    double** C;
    rows = rcA[0]; cols = rcA[1];
    C = myAlloc2(rows, rows);
    printf("!. compute %s\n", anot);
    for (i = 0; i < rows; i++)
    {
        for (m = 0; m < rows; m++)
        {
            sum = 0.0;
            for (k = 0; k < cols; k++)
            {
                P = A[m][k] * A[i][k];
                sum = sum + P;
            }
            C[i][m] = sum;
        }
    }
    return C;
}


double* GenerateSignals(
    int M,          /* each ULA has M elements */
    int maxk,       /* number of snapshots */
    int D,          /* number of emitters */
    double *DOAS,   /* doa angles in degrees -180 to +180 */
    double *POWS,   /* signal relative ratios */
    double *phi,    /* signal initial phases in degrees */
    double dn,      /* d by lambda */
    double rn,      /* r by lambda */
    double fn,      /* fc/fs or sampling rate */
    double **sA,    /* signal A */
    double **sB,    /* signal B */
    double **sC,    /* signal C */
    double stdNoise /* std of noise */
    )
{
    int s;
    double p;
    double theta[2],*SNR;
    
    SNR = myAlloc(3);
    /* normalize powers */
    p = 0.0;
    for (s = 0; s < D; s++) p = p + abs(POWS[s]);

    if (p > 0.0)
    {
        for (s = 0; s < D; s++) POWS[s] = abs(POWS[s]) / p;
    }
        
    /* ula Signals at A */
    theta[0] = 0.0;   theta[1] = 0.0;
    SNR[0] = ula(DOAS, POWS, phi,fn, rn, dn, maxk, D, M,theta,sA,stdNoise);

    /* ula Signals at B */
    theta[0] = 120.0; theta[1] = 60.0;
    SNR[1] = ula(DOAS, POWS, phi,fn, rn, dn, maxk, D, M,theta,sB,stdNoise);

    /* ula Signals at C */
    theta[0] = 60.0;  theta[1] = -60.0;
    SNR[2] = ula(DOAS, POWS, phi,fn, rn, dn, maxk, D, M,theta,sC,stdNoise);
    return SNR;
}

double ula(
        double *DOAS,   /* doa angles in degrees -180 to +180 */
        double *POWS,   /* signal relative ratios */
        double *phi,    /* signal initial phases in degrees */
        double fn,      /* fc/fs or sampling rate */
        double rn,      /* r by lambda */
        double dn,      /* d by lambda */
        int maxk,       /* number of snapshots */
        int D,          /* number of emitters */
        int M,          /* number of elements */
        double *theta,  /* two angles of rotations for each ula */
        double** sA,    /* data matrix of ula */ 
        double stdNoise /* std of noise for data ula */
            )
{
    int m, k, s,rows;
    double pi,phiA,phiB,phiC;
    double a, b, c;
    double* noise, *sigPower,*noisePower,*snr,SNR;
    pi = atan(1.0) * 4.0;
    rows = 2*M+1;
    sigPower = myAlloc(rows); noisePower = myAlloc(rows); snr = myAlloc(rows);
    for (m = 0; m < rows; m++)
    {
        noise = myNoise(maxk, stdNoise);
        sigPower[m] = 0.0; noisePower[m] = 0.0;
        for (k = 0; k < maxk; k++)
        {
            sA[m][k] = 0.0;
            for (s = 0; s < D; s++)
            {
                a = phi[s] * (pi / 180.0);
                phiA = 2 * pi * fn * (k + 1) + a;

                b = (theta[0] - DOAS[s]) * (pi / 180.0); // phase shift due to translation
                phiB = 2 * pi * rn * cos( b ); 

                c = (DOAS[s] + theta[1]) * (pi / 180.0); // phase shift due to rotation
                phiC = 2 * pi * (m - M) * dn * sin( c ); 

                sA[m][k] = sA[m][k] + POWS[s] * sin(phiA - phiB + phiC );
            }
            sigPower[m] = sigPower[m] + sA[m][k] * sA[m][k];
            sA[m][k] = sA[m][k] + noise[k];
            noisePower[m] = noisePower[m] + noise[k] * noise[k];
        }
        snr[m] = 10 * log10(sigPower[m] / noisePower[m]);
        //printf("[%d] noise power %3.4f sig power %3.4f snr dB %3.4f\n", m, noisePower[m], sigPower[m],snr[m]);
    }
    SNR = 0.0;  for (m = 0; m < rows; m++)  SNR = SNR + snr[m]; SNR = SNR / (double)(m);
    printf(" mean SNR over all the %d rows %3.4f\n",m, SNR);
    return SNR;
}

void Usage()
{
    printf("   Updated on 20th Mar 2025 for the book at Princeton NJ\n");
	printf("   [sA, sB, sC,Ha,Hb,Hc,SNR]=abcUla(D, DOAS, POWS, PHIS, M, maxk, d_by_lambda, r_by_lambda, fn,stdNoise)\n");
    printf("   Inputs: 10\n");
    printf("1. D>=1 is number of emitters.\n");
    printf("2. DOAS is a row-vector of at least D DOA angles in degrees between -180 and +180.\n");
    printf("3. POWS is a row-vector with at least D relative strength ratios.\n");
    printf("4. PHIS is a row-vector with at least D initial phases in degrees.\n");
    printf("5. M .. each ULA A,B and C has 2*M + 1 elements.\n");
    printf("6. maxk is the number of snapshots.\n");
    printf("7. d_by_lambda is ratio of inter-sensor distance of ULA to wavelength.\n");
    printf("8. r_by_lambda is ratio of radius of incircle of ULAs  to wavelength.\n");
    printf("9. fn is normalized frequency of the ALL THE EMITTERS. (i.e. SAME FREQUENCY IS ASSUMED).\n");
    printf("0. std of noise to be added.\n");
    printf("   Outputs: 7\n");
    printf("1. sA ula A data 2*M+1 by maxk matrix\n");
    printf("2. sB ula B data 2*M+1 by maxk matrix\n");
    printf("3. sC ula C data 2*M+1 by maxk matrix\n");
    printf("4. Ha Covarinace 2*M+1 by 2*M + 1 matrix\n");
    printf("5. Hb Covarinace 2*M+1 by 2*M + 1 matrix\n");
    printf("6. Hc Covarinace 2*M+1 by 2*M + 1 matrix\n");
    printf("7. SNR in dB of all 3 ULA\n");
}

