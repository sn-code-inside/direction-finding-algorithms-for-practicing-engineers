#include "goldSweepAng.h"
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

double* sweepAngle
(
    int maxk,
    double* x2,
    double* shift,
    double* angleF,
    double fn,
    int n
)
{
    double* phi;
    double* Jk, min, angle;
    int i, minI = 0, ai, bi;
    Jk = myAlloc(n);
    phi = linspace(5,350.0, n);
    for (i = 0; i < n; i++)
    {
        angle = phi[i];
//        Jk[i] = obj(maxk, rp, x2, shift);
        Jk[i] = objAngle(maxk, fn, angle, x2, shift);
        if (i == 0) { min = Jk[i]; minI = 0; }
        else { if (Jk[i] < min) { min = Jk[i]; minI = i; } }
//        printf("%3.4f %3.4f %3.4f %3.4f\n",phi[i],Jk[i],phi[minI], min);
    }
    ai = minI - 10; if (ai < 0) ai = 0;
    bi = minI + 10; if (bi > n) bi = n - 1;
    printf(" gold start %3.4f (%3.4f) end %3.4f\n", phi[ai], phi[minI], phi[bi]);
    angle = goldAngle(maxk, fn, x2, shift, phi[ai], phi[bi], 20);
    angleF[0] = angle;
    return Jk;
}

double goldAngle(int maxk, double fn, double* x2, double* shift, double a, double b, int ngs)
{
    double g, aa, bb, cc, dd, fa, fb, fc, fd;
    int i;
    //    printf("start %3.4f %3.4f\n", a, b);
    aa = a; bb = b;
    g = (3 - sqrt(5)) / 2;
    fa = objAngle(maxk, fn, aa, x2, shift);      //   Jk[i] = obj(maxk, rp, x2, shift);
    fb = objAngle(maxk, fn, bb, x2, shift);
    for (i = 0; i < ngs; i++)
    {
        cc = aa + g * (bb - aa);
        dd = cc + g * (bb - cc);


        fc = objAngle(maxk, fn, cc, x2, shift);
        fd = objAngle(maxk, fn, dd, x2, shift); // negative sign to take care of maxima to look like minima 23-2-2016

        if (fc <= fd) { bb = aa; aa = dd; }
        else { aa = cc; cc = dd; }
        //       printf("%3.4f %3.4f %3.4f\n",cc,fc,fd);
        if (fabs(aa) > 360.0) { aa = 360.0; printf("!. out of bounds forced to %f\n", aa); getchar(); }
    }
    return aa;
}


double objAngle(int maxk, double fn, double angle, double* x2, double* shift)
{
    double* y, sum, ek;
    int k;
    y = apfNew(maxk, angle, fn, x2);
    sum = 0.0;
    for (k = 0; k < maxk; k++)
    {
        ek = y[k] - shift[k];
        sum = sum + ek * ek;
    } sum = sum / (double)(maxk);
    return sum;
}


double* apfNew
(
    int maxk, /* total number of samples needed */
    double angle, /* the angles in degrees for incoming signals */
    double fn, /* normalized frequency */
    double* u /* the input sequence containing maxk values */
)
{
    double r_max = 0.95;
    double r_min = 0.05;
    double pi = 4 * atan(1.0);
    double omega = 2 * pi * fn;
    double theta, t, r;
    double* y;
    y = myAlloc(maxk);/* the output sequences size maxk */
    /* try apf=1 */
    theta = omega - angle * pi / 180.0;
    t = tan(theta / 2);
    r = t / (cos(omega) * t - sin(omega));
    if (((r < r_max) && (r > r_min)) || ((r > -r_max) && (r < -r_min)))
    {
        ApplyFilter(1,  maxk, r, u, y);
    }
    else
    {
        /* r is out of range! */
//       printf("r is out of range\n");
//        printf("r %3.4f omega %3.4f angle %3.4f theta %3.4f\n", r, omega, angle, theta);
//        printf("Trying 2 filters with half the angle\n");
        theta = omega - angle * pi / 360;
        t = tan(theta / 2);
        r = t / (cos(omega) * t - sin(omega));
        if (((r < r_max) && (r > r_min)) || ((r > -r_max) && (r < -r_min)))
        {
            ApplyDoubleFilter(1, maxk, r, u, y);
        }
        else
        {
            /* try apf=2 */
//            printf("trying APF-2\n");
            theta = pi + omega - angle * pi / 180.0;
            t = tan(theta / 2);
            r = t / (cos(omega) * t - sin(omega));
            if (((r < r_max) && (r > r_min)) || ((r > -r_max) && (r < -r_min)))
            {
                ApplyFilter(2, maxk, r, u, y);
            }
            else
            {
                /* r is out of range! */
//                printf("r is out of range\n");
//                printf("r %3.4f omega %3.4f angle %3.4f theta %3.4f\n", r, omega, angle, theta);
//                printf("Trying 2 filters with half the angle\n");
                theta = pi + omega - angle * pi / 360;
                t = tan(theta / 2);
                r = t / (cos(omega) * t - sin(omega));
                if (((r < r_max) && (r > r_min)) || ((r > -r_max) && (r < -r_min)))
                {
                    ApplyDoubleFilter(2, maxk, r, u, y);
                }
                else
                {
                    /* try apf=2 */
                    printf("Sorry, r is still out of range\n");
                }
            }
        }
    }
//    printf("r %3.4f\n", r);
    return y;
}



void ApplyFilter(int apf, int maxk, double r, double* u, double* y)
{
    int k;
    double uk0, uk1, yk0, yk1;

//    for (m = 0; m < M; m++) /* for each sensor element */
    {
        /* filter implementation */
        uk0 = uk1 = yk0 = yk1 = 0.0;

        y[0] = 0.0;
        for (k = 1; k < maxk; k++)
        {
 //           if (m == 0)
                uk1 = u[k];
 //           else
 //               uk1 = y[k];

            if (apf == 1)
                yk1 = r * yk0 - r * uk1 + uk0;
            else
                yk1 = r * yk0 + r * uk1 - uk0;

            uk0 = uk1;
            yk0 = yk1;

            y[k] = yk1;
        }
    }
    return;
}

void ApplyDoubleFilter(int apf, int maxk, double r, double* u, double* y)
{
    int  k;
    double u1k0, u1k1, u2k0, u2k1, y1k0, y1k1, y2k0, y2k1;

//    for (m = 0; m < M; m++) /* for each sensor element */
    {
        /* double filter implementation */
        u1k0 = u1k1 = y1k0 = y1k1 = 0.0; /* first filter */
        u2k0 = u2k1 = y2k0 = y2k1 = 0.0; /* second filter */

        y[0] = 0.0;

        for (k = 1; k < maxk; k++)
        {
            /* first filter */
//            if (m == 0)
//            {
                u1k1 = u[k];
//            }
//            else
//            {
//                u1k1 = y[k];
//            }

            if (apf == 1)
                y1k1 = r * y1k0 - r * u1k1 + u1k0;
            else
                y1k1 = r * y1k0 + r * u1k1 - u1k0;

            u1k0 = u1k1;
            y1k0 = y1k1;

            /* second filter */
            u2k1 = y1k1;

            if (apf == 1)
                y2k1 = r * y2k0 - r * u2k1 + u2k0;
            else
                y2k1 = r * y2k0 + r * u2k1 - u2k0;

            u2k0 = u2k1;
            y2k0 = y2k1;

            y[k] = y2k1;
        }
    }
    return;
}
