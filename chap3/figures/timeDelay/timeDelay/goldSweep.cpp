
// gold minimization for fine delay
#include "goldSweep.h"
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
double* sweepR
(
    int maxk,
    double* x2,
    double* shift,
    double* rC,
    int n
)
{
    double * r;
    double* Jk, min, rp;
    int i, minI=0, ai, bi;
    Jk = myAlloc(n);
    r = linspace(-0.95, 0.95, n);
    for (i = 0; i < n; i++)
    {
        rp = r[i];
        Jk[i] = obj(maxk, rp, x2, shift);
        if (i == 0) { min = Jk[i]; minI = 0; }
        else { if (Jk[i] < min) { min = Jk[i]; minI = i; } }
        //        printf("%3.4f %3.4f %3.4f %3.4f\n",r[i],Jk[i],r[minI], min);
    }
    ai = minI - 5; if (ai < 0) ai = 0;
    bi = minI + 5; if (bi > n) bi = n-1;
    printf(" gold start %3.4f (%3.4f) end %3.4f\n", r[ai], r[minI], r[bi]);
    rp = goldR(maxk, x2, shift, r[ai], r[bi], 20);
    rC[0] = rp;
    return Jk;
}

double goldR(int maxk, double* x2, double* shift, double a, double b, int ngs)
{
    double g, aa, bb, cc, dd, fa, fb, fc, fd;
    int i;
    //    printf("start %3.4f %3.4f\n", a, b);
    aa = a; bb = b;
    g = (3 - sqrt(5)) / 2;
    fa = obj(maxk, aa, x2, shift);      //   Jk[i] = obj(maxk, rp, x2, shift);
    fb = obj(maxk, bb, x2, shift);
    for (i = 0; i < ngs; i++)
    {
        cc = aa + g * (bb - aa);
        dd = cc + g * (bb - cc);


        fc = obj(maxk, cc, x2, shift);
        fd = obj(maxk, dd, x2, shift); // negative sign to take care of maxima to look like minima 23-2-2016

        if (fc <= fd) { bb = aa; aa = dd; }
        else { aa = cc; cc = dd; }
        //        printf("%3.4f %3.4f %3.4f\n",cc,fc,fd);
        if (fabs(aa) > 1.0F) { aa = 1.0F; printf("!. out of bounds forced to %f\n", aa);  }
    }
    return aa;
}

double obj(int maxk, double rp, double* x2, double* shift)
{
    double* y, sum, ek;
    int k;
    y = apf2(maxk, rp, x2); // x2 is the input to apf2
    sum = 0.0;
    for (k = 0; k < maxk; k++)
    {
        ek = y[k] - shift[k];
        sum = sum + ek * ek;
    } sum = sum / (double)(maxk);
    return sum;
}

double r2angle(double r, double fn)
{
    double angle, num, den, omega, theta;
    double pi = 4.0 * atan(1.0);

    omega = 2.0 * pi * fn;
    num = -r * sin(omega); den = 1.0 - r * cos(omega);
//    theta = 2.0 * atan(num / den);
    theta = 2.0 * atan2(num , den);
    angle = omega - theta;
    angle = angle * 180 / pi;
    return angle;
}

double angle2r(double fn, double angle, double order, int* flag)
{
    double pi, omega, theta, t, r;
    double rmax = 0.95;
    double rmin = 0.1;
    pi = 4.0 * atan(1.0);
    omega = 2 * pi * fn;
    theta = omega - (angle / order) * pi / 180;
    t = tan(theta / 2);
    r = t / (cos(omega) * t - sin(omega));
    if (((r < rmax) && (r > rmin)) || ((r > -rmax) && (r < -rmin)))
        flag[0] = 1; else flag[0] = -1;
    return r;
}

double* linspace(double a, double b, int N)
{
    double* x, delta;
    int k;
    x = myAlloc(N); delta = (b - a) / (double)(N - 1);
    for (k = 0; k < N; k++)  x[k] = a + delta * (double)(k);
    return x;
}

double* apf2(int maxk, double r, double* u)
{
    int k;
    double u1k0, u1k1, y1k0, y1k1;
    double u2k0, u2k1, y2k0, y2k1;
    double* y;
    y = myAlloc(maxk);
    for (k = 0; k < maxk; k++) y[k] = 0.0;

    /* filter implementation */
    u1k0 = u1k1 = y1k0 = y1k1 = 0.0;
    u2k0 = u2k1 = y2k0 = y2k1 = 0.0;

    for (k = 0; k < maxk; k++)
    {
        u1k1 = u[k];
        y1k1 = r * y1k0 - r * u1k1 + u1k0;
        u1k0 = u1k1;   y1k0 = y1k1;
        u2k1 = y1k1;

        y2k1 = r * y2k0 - r * u2k1 + u2k0;
        y2k0 = y2k1;
        u2k0 = u2k1;
        y[k] = y2k1;
    }
    return y;
}

