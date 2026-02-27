#include "stdafx.h"
#include "sliceVoice.h"
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
double findFn(double* un, int N)
{
    complex* z;
    double* s{};
    int i, Nby2, pkI, M;
    double uk0 = 0,  xk0 = 0, xk1 = 0;
    double r = 0.95;
    double pi = 4.0 * atan(1.0);
    double fn;
    Nby2 = N / 2; M = (int)(log(N) / log(2));
    z = myAllocComplex(N); s = myAlloc(N);
    for (i = 0; i < N; i++) { z[i].r = un[i]; z[i].i = 0.0; }
    sampleSpek(z, s, N, M); 
    for (i = Nby2; i < N; i++) s[i] = 0.0;

    pkI = myMax(s, N); 
    fn = pkI /(double) (N);
//    s = nbf(un, fn[0], N);
//    printf("! peak Index %d and N %d Normalised Peak Freq %3.4f\n", pkI,N,fn[0]);
    //  .... Narrow Band Filter
/*    p = 2 * cos(2 * pi * fn[0]); g = (1 - r * r) * 0.5;
    for (i = 0; i < N; i++)
    {
        uk1 = un[i];
        xk2 = r * p * xk1 - r * r * xk0 + (uk1 - uk0);
        xk0 = xk1; xk1 = xk2;
        uk0 = uk1; s[i] = xk2;
    }
    myMaxMin(s, minmax, N);
    if (fabs(minmax[0]) > fabs(minmax[1])) max = fabs(minmax[0]);
    else max = fabs(minmax[1]);
    for (i = 0; i < N; i++) s[i] = s[i] / max;*/
//    printf(" Normalise NB signal my %3.4f\n",max);
    return fn;
}

double* anf(double* un, int N, double fs)
{
    double lambda, mu, r, vk, qk, delp,ek,grad,p;
    double xk2,xk1, xk, sk2,sk1, sk, uk2,uk1, uk;
    double pi;
    double* vp,fp;
    int k;
    pi = 4.0 * atan(1.0);
    lambda = 0.8; mu = 0.05;  r = 0.8;
    vk = 0; qk = 0; delp = 0;

    xk1 = 0; xk = 0;
    sk1 = 0; sk = 0;
    uk1 = 0; uk = 0;
    p = 0; vp = myAlloc(N);

    for (k = 0; k < N; k++)
    {
        uk2 = uk1; uk1 = uk;

        uk = un[k];
 //....... nbf
        xk2 = xk1; xk1 = xk;
        xk = r * p * xk1 - r * r * xk2 + (uk - uk2) * (1 - r * r) * 0.5;
//........ GRADIENT FILTER
        sk2 = sk1; sk1 = sk;
        sk = r * p * sk1 - r * r * sk2 + r * xk;

        ek = xk - uk;
        vk = vk * (lambda)+(1 - lambda) * (ek * ek);
        grad = 2 * ek * sk1;
        if (k > 1) delp = mu * grad / (vk + 0.0001);
        if (fabs(p) > 2.0) p = 1.9;
        p = p - delp;
        if (p < 2.0) fp = (acos(p / 2)) / (2 * pi); else fp = 0.0;
        vp[k] = fp*fs;
    }
//    myPrintf(vp, N, 8);
    return vp;
}

double* nbf(double* un, double fn,int N)
{
    double p, r, g, pi;
    double* s;
    double uk0 = 0, uk1, xk0 = 0, xk1 = 0, xk2;
    double minmax[2], max;
    int i;
    pi = 4.0 * atan(1.0); r = 0.95;
    s = myAlloc(N);
//  .... Narrow Band Filter
    p = 2 * cos(2 * pi * fn); g = (1 - r * r) * 0.5;
    for (i = 0; i < N; i++)
    {
        uk1 = un[i];
        xk2 = r * p * xk1 - r * r * xk0 + (uk1 - uk0);
        xk0 = xk1; xk1 = xk2;
        uk0 = uk1; s[i] = xk2;
    }
    myMaxMin(s, minmax, N);
    if (fabs(minmax[0]) > fabs(minmax[1])) max = fabs(minmax[0]);
    else max = fabs(minmax[1]);
    for (i = 0; i < N; i++) s[i] = s[i] / max;
    return s;
}

int audioBlock(int k, double* un, int * data, char* wavfile, int N)
{
    static double* audio{};
    static int maxDataValues, HeaderSize;
    double sigma = 1, mu = 1;
    int er;
    if (k == 0)
    {
        audio = myAlloc(30);
        er = wavHeader(wavfile, audio, &HeaderSize);
        if (er < 0)
        {
            printf("!. Error in opening the .wav file\n");
            return -100;
//            exit(-1);
        }
        maxDataValues = (int)(audio[8] / 2);
    }
    er = blockOfWav(k, N, un, data, wavfile, audio);
 //   er = stdMuLin(un, &sigma, &mu, N);
    //printf("error %d mean %3.4f std %3.4f\n",er,sigma,mu);
//    if (sigma < 0.001)
 //   {
 //       printf(" No Energy \n"); return -1;
 //   }
    return er;
}
