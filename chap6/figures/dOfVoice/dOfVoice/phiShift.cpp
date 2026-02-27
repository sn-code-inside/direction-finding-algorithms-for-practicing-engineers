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

#include "phiShift.h"
//#include "mex.h"   /* This one is required */

complex** ulaMatrix
(
    double angle, 
    double *un,
    double *F,
    double fs, 
    double *DbyL,
    int maxk,// number of snap shots 
    int MM, // ula size
    int *rc,
    double **A)
{
    double* yR, * yf, *s; //*s,*ulaAngles;
    double* x;
    complex* z{};
    //double** sI, ** sR;
    int k, i,m,order,M,pkI,width=20;
    int b, e;
    double phiD;
    double dbl, pi, phiR,v;
    double lambda,d,fc,fn=0.25,Fn,Fc;
    //double Bpf[2];
    complex **B;
    pi = 4.0 * atan(1.0);

    yR = myAlloc(maxk); yf = myAlloc(maxk); x = myAlloc(maxk);
    B = myAlloc2Complex(MM, width); z = myAllocComplex(maxk);

    d = 3.8; // cm
    d = 10;
    v = 332; // m/sec

    fn = findFn(un, maxk); 
    fc = fn * fs;
    s = nbf(un, fn, maxk); // narrow band signal
    F[0] = fn; F[1] = fn;   Fn = fn;  
    //Fn = 0.2; 
    F[1] = Fn;
    Fc = fs * Fn;
    printf("peak energy %3.4f Hz Sliced Freq %3.4f Hz\n",fc,Fc);
    lambda = (v / Fc) * 100; // cm
    DbyL[0] = d / lambda;


   
//    printf(" wavelength at 300 Hz 110 cm and at 100 Hz 332 cm\n");
//    printf(" Sampling freq %3.4f Peak NB frequency %3.4f and fn %3.4f\n", fs, fc, fn);
//    printf(" Wavelength at %3.4f Hz is %3.4f cm\n",fc,lambda);
    lambda = (v / fc) * 100; // cm
    dbl = d / lambda; 
    printf("peak dbyl %3.4f freq %3.4f Fc %3.4f dbyl at Fc %3.4f\n", dbl, fc, Fc, DbyL[0]);

    phiR = 2 * pi * dbl * sin(angle * pi / 180.0); // this is for sign matching
    phiD = phiR * 180 / pi;
//    printf(" Speed of sound %3.4f m/s distance  and d_by_lambda %f\n", v,dbl);
      printf(" ULA size %d phase shift in Deg %f for a DOA %f\n", MM, phiD, angle);
//    printf("....maxk %d fn %3.4f\n", maxk,fn);

/*  There is an important change I have made take the input as signal decimated but not narrow band
    but limited band signal after creating a matrix Narrow Band Filter is applied to all the array elements*/
    M = (int)(log(maxk) / log(2));
    rc[0] = MM; rc[1] = width;
    pkI = (int)(fn * maxk);
    b = pkI - rc[1] / 2; e = pkI + rc[1] / 2;
    if (b < 0) b = 0; if (e > maxk) e = maxk;

    for (m = 0; m < MM; m++)
    {
        if (m == 0)
        {
            for (k = 0; k < maxk; k++) { z[k].r = un[k]; z[k].i = 0.0; yf[k] = un[k]; A[m][k] = un[k]; }
        }
        else
        {
            order = ChoseAPForder(phiD, fn, maxk, yf, yR); // yR is the output
            for (k = 0; k < maxk; k++) {
                z[k].r = yR[k]; z[k].i = 0.0; yf[k] = yR[k];
                A[m][k] = yR[k];
            }
        }
        sampleSpek(z, x, maxk, M); 
        i = 0;
        for (k = b; k < e; k++)
        {
            B[m][i] = z[k];
            i = i + 1;
        }
    }
    for (k = 0; k < maxk; k++) un[k] = s[k];
    free(s); free(x);
    return B;
}




/* ChoseAPForder: Chooses either APF once or APF twice with half the angle */
/* Also, Chooses between APF-1 and APF-2 */
int ChoseAPForder
(
    double angle, /* the phase angle delay required */
    double fn, /* normalized frequency */
    int maxk, /* total number of samples needed */
    double* u, /* input sequence size maxk */
    double* yL /* the output sequences size maxk */
)
{
    double   r;
    int k,   order;
    double rmax = 0.95, rmin = 0.1;
    double* y;
    printf( " Shift %f Degrees\n",angle);
    if (angle < 0) angle = 360 + angle;
    if (fabs(angle) < 1)
    {
        for (k = 0; k < maxk; k++) yL[k] = u[k];
        return 1;
    }
    order = estimateOrder(fn, angle, &r);
    switch (order)
    {
    case 1:
    {
        y = apf1(maxk, r, u);
    //    printf(" Normal APF pole at %f\n", r);
        break;
    }
    case 2:
    {
        y = apf2(maxk, r, u);
    //    printf(" Double APF pole at %f\n", r);
        break;
    }
    case 3:
    {
        y = apf3(maxk, r, u);
    //    printf(" Tripple APF pole at %f\n", r);
        break;
    }
    default: printf(" failed \n");
        return -1;
    }
    for (k = 0; k < maxk; k++) yL[k] = y[k];
    free(y);
    return order;
}



double* apf1(int maxk, double r, double *u)
{
    int k;
    double uk0, uk1, yk0, yk1;
    double *y;
    y = (double*)malloc(maxk * sizeof(double));
    for (k = 0; k < maxk; k++) y[k] = 0.0;

    
    /* filter implementation */
    uk0 = uk1 = yk0 = yk1 = 0.0;

    for (k = 0; k < maxk; k++)
    {
        uk1 = u[k]; 
        yk1 = r*yk0 - r*uk1 + uk0;
     
        uk0 = uk1;  yk0 = yk1; y[k] = yk1;
    }
    return y;
}

double* apf2( int maxk, double r, double *u)
{
    int k;
    double u1k0, u1k1, y1k0, y1k1;
    double u2k0, u2k1, y2k0, y2k1;
    double *y;
    y = (double*)malloc(maxk * sizeof(double));
    for (k = 0; k < maxk; k++) y[k] = 0.0;

    /* filter implementation */
    u1k0 = u1k1 = y1k0 = y1k1 = 0.0;
    u2k0 = u2k1 = y2k0 = y2k1 = 0.0;

    for (k = 0; k < maxk; k++)
    {
        u1k1 = u[k];      
        y1k1 = r*y1k0 - r*u1k1 + u1k0;
        u1k0 = u1k1;   y1k0 = y1k1;
        u2k1 = y1k1;

        y2k1 = r*y2k0 - r*u2k1 + u2k0;
       
        u2k0 = u2k1;   y2k0 = y2k1;
        y[k] = y2k1;
    }
    return y;
}

double* apf3( int maxk, double r, double *u)
{
    int k;
    double u1k0, u1k1, y1k0, y1k1;
    double u2k0, u2k1, y2k0, y2k1;
    double u3k0, u3k1, y3k0, y3k1;
    double *y;
    y = (double*)malloc(maxk * sizeof(double));
    for (k = 0; k < maxk; k++) y[k] = 0.0;

    /* filter implementation */
    u1k0 = u1k1 = y1k0 = y1k1 = 0.0;
    u2k0 = u2k1 = y2k0 = y2k1 = 0.0;
    u3k0 = u3k1 = y3k0 = y3k1 = 0.0;

    for (k = 0; k < maxk; k++)
    {
        u1k1 = u[k];
        
        y1k1 = r*y1k0 - r*u1k1 + u1k0; // first APF
       
        u1k0 = u1k1;   y1k0 = y1k1;  u2k1 = y1k1;

        y2k1 = r*y2k0 - r*u2k1 + u2k0; // second APF
       
        u2k0 = u2k1;   y2k0 = y2k1;  u3k1 = y2k1;

        y3k1 = r*y3k0 - r*u3k1 + u3k0; // Third APF
  
        u3k0 = u3k1;   y3k0 = y3k1;

        y[k] = y3k1;
    }
    return y;
}

int estimateOrder(double fn, double angle, double *r)
{
    double N,temp,big;
    double apfR[3]{0,0,0};
    int apfOrder[3]{1,2,3},tempI,k,flag;
    flag = 0;

    for (k=0; k<3; k++)
    {
        N = (double)(k+1);
        apfR[k] = angle2r(fn, angle, N, &flag);
        if (flag < 0 ) apfR[k] = 0.0;
        if (k == 0) big=fabs(apfR[k]);
        else 
        {
            if (big < fabs(apfR[k])) 
            {
                big=fabs(apfR[k]); 
                temp = apfR[0]; apfR[0] = apfR[k];
                apfR[k] = temp;
                tempI =apfOrder[0]; apfOrder[0] = apfOrder[k];
                apfOrder[k] = tempI;
            }
        } 
    }
    if ( fabs(apfR[2]) > fabs(apfR[1]) )
    {
        temp = apfR[1]; apfR[1] = apfR[2];
        apfR[2] = temp;
        tempI = apfOrder[1]; apfOrder[1] = apfOrder[2];
        apfOrder[2] = tempI;
    }
    for (k=0; k<3; k++)
    //printf("[%d] Shift %f Degrees, flag %d, pole %f\n", apfOrder[k],angle, flag, apfR[k]);
    r[0] = apfR[0];
    return apfOrder[0];
}

double angle2r(double fn,double angle,double N,int *flag)
{
    double pi, omega, theta, t,r;
    double rmax = 0.95;
    double rmin = 0.1;
    pi = 4.0*atan(1.0);
    omega = 2*pi*fn;
    theta = omega - (angle / N) * pi / 180;
    t = tan(theta / 2);
    r = t / (cos(omega) * t - sin(omega));
    if (((r < rmax) && (r > rmin)) || ((r > -rmax) && (r < -rmin))) 
    flag[0] = 1; else flag[0] = -1;
    return r;
}


