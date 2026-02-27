/*

APF Data Generation Program APF.c for DASC 2011

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
#include "math.h"
#include "mex.h"   /* This one is required */


double* apf2(int , double , double* );
double* sweepR(int,double*,double*,double*,int);
double obj(int , double , double* , double*);
double goldR(int , double* , double* , double , double , int );
double* linspace(double , double , int);
double* myAlloc(int);
void Usage();

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
        if (fabs(aa) > 1.0) { aa = 1.0; printf("!. out of bounds forced to %f\n", aa); getchar(); }
    }
    return aa;
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
    //printf(" gold start %3.4f (%3.4f) end %3.4f\n", r[ai], r[minI], r[bi]);
    rp = goldR(maxk, x2, shift, r[ai], r[bi], 20);
    rC[0] = rp;
    return Jk;
}


double* myAlloc(int c)
{
	double* A;
	A = (double*)malloc(c * sizeof(double));
	return A;
}

double* linspace(double a, double b, int N)
{
    double* x, delta;
    int k;
    x = myAlloc(N); delta = (b - a) / (double)(N - 1);
    for (k = 0; k < N; k++)  x[k] = a + delta * (double)(k);
    return x;
}

void Usage()
{
    printf("2nd Order APF paper\n");
    printf("updated 26th Sep 2024 Dublin Ohio For Book Writing\n");
	printf("Usage: [y jk rfine]=apf2[u, r,shift]\n"); 
    printf("y is an maxk vector\n");    
    printf("r is the pole of the APF\n");
	printf("u is input signal with maxk samples\n");
    printf("jk is the ouput\n");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputU, *inputShift, *inputR;
	double *yptr,*jptr,*y,*Jk,*u,*shift,rFine,rp,objk;
    double *rptr;
	int maxk,k,r,c,jkLen=50;

    if ((nlhs != 3) || (nrhs != 3))
    {
        printf("  Usage Error Parameters Left Hand Side = %d(3) .. Right Hand Side = %d(3) \n", nlhs, nrhs);
        Usage();
		return;
	}
    
       
    r = mxGetM(prhs[0]); c = mxGetN(prhs[0]);
	if (r != 1)
	{
		Usage(); 
        printf("In this call, u is a vector try transpose error (%d by %d)\n",r,c);
		return;
	}

    inputU = mxGetPr(prhs[0]);
	maxk = mxGetN(prhs[0]);

    u =myAlloc(maxk);  shift =myAlloc(maxk);
    Jk = myAlloc(jkLen);
    for (k = 0; k < maxk; k++) u[k] = inputU[k];

    inputR = mxGetPr(prhs[1]);
    r = mxGetM(prhs[1]); c = mxGetN(prhs[1]);
	if ( (r != 1) || (c != 1) )
	{
		Usage();
        printf("In this call, r is a scalar error (%d by %d)\n", r, c);
	} 
    rp = inputR[0];

    inputShift = mxGetPr(prhs[2]);
	//maxk = mxGetN(prhs[2]);
    for (k = 0; k < maxk; k++) shift[k] = inputShift[k];


	/* call the data generation */
    Jk = sweepR(maxk,u,shift,&rFine,jkLen);
    objk = obj(maxk, rp, u, shift);
	y = apf2(maxk, rp, u);
	/* create and return matrix */
	plhs[0] = mxCreateDoubleMatrix(1, maxk, mxREAL);
	yptr = mxGetPr(plhs[0]);
	for (k = 0; k < maxk; k++) yptr[k] = y[k];


    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    jptr = mxGetPr(plhs[1]);  jptr[0] = objk;

    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    rptr = mxGetPr(plhs[2]);  rptr[0] = rFine;
	/* towards freedom! */
	free(y); 
    return;
}
