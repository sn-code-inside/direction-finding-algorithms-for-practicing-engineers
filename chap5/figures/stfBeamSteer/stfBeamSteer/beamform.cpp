#include "beamform.h"
//#include "mex.h"   /* This one is required */
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
double* coefficient
(
    double r,     /*Pole position of the narrow band pass filter*/
    double theta, /*spatial angle*/
    double dbl,   /*d/lambda*/
    int m         /*no of sensors*/
)
{
    int  k;
    double phi, pi, a, rPowK, rPowKm2;
    double sinKp1, sinKm1;
    double* w;
    //  compute beam coefficients
    pi = atan(1.0) * 4.0;
    w = myAlloc(m);
    a = (1 - (r * r)) / 2.0;
    phi = 2 * pi * dbl * sin(theta * pi / 180);

    for (k = 0; k < m; k++)
    {
        rPowK = pow(r, k); rPowKm2 = pow(r, k - 2);
        sinKp1 = sin((k + 1) * phi) / sin(phi);
        sinKm1 = sin((k - 1) * phi) / sin(phi);
     // find coefficients 
        if (k >= 2) w[k] = a * (rPowK * sinKp1 - rPowKm2 * sinKm1);
        else w[k] = a * rPowK * sinKp1;
    }
    return w;
}

double* linspace(double s, double e, int kmax)
{
    double delx;
    double* x;
    int k;
    x = myAlloc(kmax);
    delx = (e - s) / (double)(kmax - 1);
    for (k = 0; k < kmax; k++) x[k] = s + (double)(k)*delx;
    return x;
}

double wTranposeHmulW(double** H, double* w, int m)
{
    double* Hw, Jk;
    int i, k;
    Hw = myAlloc(m);
    for (i = 0; i < m; i++)
    {
        Hw[i] = 0.0;
        for (k = 0; k < m; k++)   Hw[i] = Hw[i] + H[i][k] * w[k];
    }
    Jk = 0.0;
    for (k = 0; k < m; k++) Jk = Jk + Hw[k] * w[k];
    free(Hw);
    return Jk;
}

double obj(double **H, double r, double theta, double d_by_lambda, int m)
{
    double Jk,*w;
    w = coefficient(r, theta, d_by_lambda, m);
    if (fabs(theta) > 5.0)
    {
        Jk = wTranposeHmulW(H, w, m);
    }
    else Jk = rand() / 32767.0;
    return Jk;
}

