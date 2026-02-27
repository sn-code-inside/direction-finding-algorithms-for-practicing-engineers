// wavBlocks.cpp : Defines the entry point for the console application.
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
#include "wavBlocks.h"
//#define MATLAB 1
//#include "mex.h"    //This one is required 

int blockOfWav(int k, int N, double* un, int * data, char* wavfile, double* p)
{
    int err, nSmp[2];
    static int b, e, HeaderSize;
    static int maxDataValues = 44;
    maxDataValues = (int)(p[8] / 2); HeaderSize = (int)(p[9]);
    if (k == 0) b = 0;
    e = b + N - 1;
    nSmp[0] = b; nSmp[1] = e;
    err = wavData(wavfile, p, HeaderSize, un, data, nSmp, k);
    b = e + 1;
    if (err < 0) return err;
    return N;
}

int pitchParts(int k, int N, double* un, double *uwav,int * data, char* wavfile, double* p, int decimate, double *Bpf)
{
    int er, i, Ns;
    complex* z{};
    double minmax[2],max;
    double* x{}, sigma, mu, fs;
    //x = myAlloc(N);
    
    Ns = N;  fs = p[4];
    

    er = blockOfWav(k, N, uwav, data,wavfile,p);
    if (er < 0)
    {
        printf("!. error in reading data from file\n");
        return er;
    }

    x = filterInTime(uwav, un, N, fs, Bpf);

    Ns = subsample(x, N, decimate, un);
    for (i = Ns; i < N; i++) { un[i] = 0.0;}

    er = stdMuLin(un, &sigma, &mu, Ns);
    if (er < 0) 
    {
        if (er == -1) 
        { printf("!. No Energy in The Time Series %d\n",Ns); sigma = 1.0; return -Ns;} 
         else
         {
              printf("!. DATA LENGTH ZERO\n");
              return -100;
         }
    }
    
    myMaxMin(un, minmax, Ns);
    if (fabs(minmax[0]) > fabs(minmax[1])) max = fabs(minmax[0]);
    else max = fabs(minmax[1]);
    //printf(" min %3.4f max %3.4f max - %3.4f\n",minmax[0],minmax[1],max);
    printf("[%d] Normalizing by max %3.4f Decimated Complex Sequence[%d]->[%d]\n", k, max, N, Ns);
    for (i = 0; i < Ns; i++) un[i] = un[i] / max; 
    free(x);
    return Ns;
}

double * filterInTime(double *uwav, double* un, int N, double fs, double *Bpf)
{
    complex* z{};
    double minmax[2], max;
    double* x{};
    int i,M;

    myMaxMin(uwav, minmax, N);
    if (fabs(minmax[0]) > fabs(minmax[1])) max = fabs(minmax[0]);
    else max = fabs(minmax[1]);
    for (i = 0; i < N; i++) { uwav[i] = uwav[i] / max; un[i] = uwav[i]; }

    z = (complex*)malloc(N * sizeof(complex));
    x = (double*)malloc(N * sizeof(double));

    for (i = 0; i < N; i++)
    {
        z[i].r = un[i]; z[i].i = 0.0;
    }

    M = (int)(log(N) / log(2));

    sampleSpek(z, x, N, M);
    filter(z, N, fs, Bpf);
    sampleSpek(z, x, N, M); for (i = 0; i < N; i++) x[i] = z[i].r;
    free(z);
    return x;
}

void filter(complex* z, int N, double fs, double *Bpf)
{
    int s1, e1, i,k;
    int s, e, se[3][2];
    double fStart, fEnd;
   
    double delf;
    delf = fs / (double)(N);
//    printf("!. Number of sample %d Sampling Rate %3.4f and delf %3.4f\n", N, fs,delf);
//    fStart = 100.0; fEnd = 500.0;
    fStart = Bpf[0]; fEnd = Bpf[1];
    s = (int)(ceil(fStart / delf)); e = (int)(ceil(fEnd / delf)) + 1;
    se[0][0] = 0; se[0][1] = s;
    se[1][0] = e; se[1][1] = N-e-1;
    se[2][0] = N-s-1; se[2][1] = N;
//    for (i = 0; i < 3; i++)  
//    printf("fill spectrum %d to %d with zeros\n", se[i][0], se[i][1]);


    for (k = 0; k < 3; k++)
    {
        s1 = se[k][0]; e1 = se[k][1];
        for (i = s1; i < e1; i++)
        {
            z[i].r = 0.0; z[i].i = 0.0;
        }
    }

    return;
}

int subsample(double* x, int N, int decimate, double* un)
{
    int i, kt=0;
    for (i = 0; i < N; i++)
    {
        if (i % decimate == 0)
        {
            kt = i / decimate;
            un[kt] = x[i];
        }
    }
    kt = kt + 1;
    return kt;
}

void Kalman(double* x, int N, int n)
{
    /****************************************************************************/
    /*																			*/
    /* ... Kalman Filter for Smoothing // DSP for Practicing Engineers	*/
    /* ... page 75 by K V Rangarao from John Wiley .. 17th Oct 2008				*/
    /*																			*/
    /****************************************************************************/
    int ip, k;
    double sA, sB, er, g;
    double smooth = 0;
    double* s;
    s = myAlloc(n + 1);
    for (ip = 0; ip < n + 1; ip++) s[ip] = 0.0;

    for (k = 0; k < N; k++)
    {
        for (ip = 0; ip < n; ip++) s[ip] = s[ip + 1];
        s[ip] = x[k]; // <-- input

        sA = 0; sB = 0;
        for (ip = 0; ip < n; ip++)
        {
            sA = sA + s[ip];
            sB = sB + 2 * (ip + 1) * s[ip];
        }

        er = (sB - sA * (n + 1));
        g = 6.0 / (n * (n * n - 1.0));

        smooth = smooth + g * er; // --> output
        if (k > n) x[k] = smooth;
    }
    for (k = 0; k < n + 1; k++)  x[k] = x[n + 1];
    free(s);
    return;
}

int pitchEnergy
(
    int binsN,
    int* bins,
    int rows,
    int N,
    int waveletWindow,
    double* x,
    double* un,
    double **p
)
{
    int numberOfPeaks, i, er, peak, k,localRow;
//    int km;
    double sum = 0.0, gain = 1.0;
    double* scale,fn;
//    double** p, * scale;

    if (binsN > 0)
    {
        numberOfPeaks = binsN;
        if (rows < numberOfPeaks)
        {
            localRow = rows;
            printf("!. Pitch Energy for %d peaks out of %d\n", localRow, numberOfPeaks);
        }
        else
        {
            localRow = numberOfPeaks;
            printf("!. Pitch Energy for %d peaks instead of %d\n", localRow, rows);
        }
        scale = myAlloc(localRow);
        for (i = 0; i < numberOfPeaks; i++)
        {
            peak = bins[i];
            if (i < rows)
            {
                fn = (double)(bins[i]) / (double)(N);
                printf("%d ---> {bin(%d)->%3.4f} %3.4f\n", i,bins[i],fn,x[peak]);
                er = wavlet(un, N, bins, waveletWindow, i, p[i]);
                sum = 0.0; for (k = 0; k < N; k++) sum = sum + p[i][k];
                sum = sum / N; gain = x[peak] / sum;
                for (k = 0; k < N; k++) p[i][k] = gain * p[i][k];
                     for (k = 0; k < N; k++) p[i][k] = p[i][k] / scale[0];
//                printf("max value for %d -> %3.4f\n", i, scale[i]);
//              printf("!. average pitch energy at bins[%d] = %3.4f scale it by %3.4f\n",peak,sum,gain);
                if (er < 0)
                {
                    #ifdef MATLAB
                    mexErrMsgTxt("!. exiting pitchEnergy .. problem in computing std\n");
                    #else
                    printf("!. exiting pitchEnergy .. problem in computing std\n");
                    return -1;
                    #endif
                }
            }
        }
    }
    else { printf("!. No peaks"); return -1; }
    return localRow;
}

int wavlet(double* z, int N, int* bins, int n, int peak, double* x)
{
    int i;
    double* xi{}, * xq{};
    double lastValueR;
    double pi, sumI, sumQ, fn, A;
    int KalmanFilterSection = 16;
    int s, e;
//    if (peak > 3) peak = 3;

    fn = (double)(bins[peak]) / (double)(N);

//    printf("bin[%d] %d\n", peak, bins[peak], fn);

    xi = (double*)malloc(n * sizeof(double));
    xq = (double*)malloc(n * sizeof(double));
    pi = 4.0 * atan(1.0);
    for (i = 0; i < n; i++) { xi[i] = sin(2 * pi * fn * i); xq[i] = cos(2 * pi * fn * i); }

    for (s = 0; s < N - n; s++)
    {
        sumI = 0.0; sumQ = 0.0;
        e = s + n - 1;
        for (i = 0; i < n; i++)
        {
            sumI = xi[i] * z[i + s] + sumI;
            sumQ = xq[i] * z[i + s] + sumQ;
        }
        sumI = sumI / (double)(n); sumQ = sumQ / (double)(n);
        A = sqrt((sumI * sumI + sumQ * sumQ) * 2.0);
        x[s] = A;
    } lastValueR = x[s - 1];
    for (s = N - n; s < N; s++) { x[s] = lastValueR; }
    Kalman(x, N, KalmanFilterSection);
    return 1;
}
