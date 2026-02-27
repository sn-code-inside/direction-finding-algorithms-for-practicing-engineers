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

//#define PI 3.14159

#define R_MAX 0.98
#define R_MIN 0.1
void ApplyFilter(int , int , int , double , double *, double **);
void ApplyDoubleFilter(int , int, int , double , double *, double **);
void Usage();
double APFDG
(
	double ,  /* the angles in degrees for incoming signals */
	double ,  /* normalized frequency */
	int ,     /* number of sensor elements */
	int ,     /* total number of samples needed */
	double *, /* the input sequence containing maxk values */
	double ** /* the output sequences size M*maxk */
);


void ReportError(char *msg, int s)
{
	printf("ERROR: %s%d\n", msg, s);
}

void ApplyFilter(int apf, int M, int maxk, double r, double *u, double **y)
{
    int m, k;
    double uk0, uk1, yk0, yk1;
    
    for (m = 0; m < M; m++) /* for each sensor element */
    {
        /* filter implementation */
        uk0 = uk1 = yk0 = yk1 = 0.0;

        y[m][0] = 0.0;
        for (k = 1; k < maxk; k++)
        {
            if (m == 0)
                uk1 = u[k];
            else
                uk1 = y[m-1][k];

            if (apf == 1)
                yk1 = r*yk0 - r*uk1 + uk0;
            else
                yk1 = r*yk0 + r*uk1 - uk0;
            
            uk0 = uk1;
            yk0 = yk1;

            y[m][k] = yk1;
        }
	}
}

void ApplyDoubleFilter(int apf, int M, int maxk, double r, double *u, double **y)
{
    int m, k;
    double u1k0, u1k1, u2k0, u2k1, y1k0, y1k1, y2k0, y2k1;
    
    for (m = 0; m < M; m++) /* for each sensor element */
    {
        /* double filter implementation */
        u1k0 = u1k1 = y1k0 = y1k1 = 0.0; /* first filter */
        u2k0 = u2k1 = y2k0 = y2k1 = 0.0; /* second filter */

        y[m][0] = 0.0;
        
        for (k = 1; k < maxk; k++)
        {
            /* first filter */
            if (m == 0)
            {
                u1k1 = u[k];
            }
            else
            {
                u1k1 = y[m-1][k];
            }

            if (apf == 1)
                y1k1 = r*y1k0 - r*u1k1 + u1k0;
            else
                y1k1 = r*y1k0 + r*u1k1 - u1k0;
            
            u1k0 = u1k1;
            y1k0 = y1k1;
            
            /* second filter */
            u2k1 = y1k1;
            
            if (apf == 1)
                y2k1 = r*y2k0 - r*u2k1 + u2k0;
            else
                y2k1 = r*y2k0 + r*u2k1 - u2k0;
            
            u2k0 = u2k1;
            y2k0 = y2k1;
            
            y[m][k] = y2k1;
        }
	}
}


double APFDG
(
	double angle, /* the angles in degrees for incoming signals */
	double fn, /* normalized frequency */
	int M, /* number of sensor elements */
	int maxk, /* total number of samples needed */
	double *u, /* the input sequence containing maxk values */
	double **y /* the output sequences size M*maxk */
)
{
    double pi = 4 * atan(1.0);
    double omega = 2*pi*fn;
	double theta, t, r;
    
    /* try apf=1 */
    theta = omega-angle*pi/180.0;
	t = tan(theta/2);
	r = t /(cos(omega)*t-sin(omega));
	if (((r < R_MAX) && (r > R_MIN)) || ((r > -R_MAX) && (r < -R_MIN)))
	{
        ApplyFilter(1, M, maxk, r, u, y);
	}
	else
	{
		/* r is out of range! */
		printf("r is out of range\n");
        printf("r %3.4f omega %3.4f angle %3.4f theta %3.4f\n", r, omega, angle, theta);
        printf("Trying 2 filters with half the angle\n");
        theta = omega-angle*pi/360;
        t = tan(theta/2);
        r = t /(cos(omega)*t-sin(omega));
        if (((r < R_MAX) && (r > R_MIN)) || ((r > -R_MAX) && (r < -R_MIN)))
        {
            ApplyDoubleFilter(1, M, maxk, r, u, y);
        }
        else
        {
            /* try apf=2 */
            printf("trying APF-2\n");
            theta = pi+omega-angle*pi/180.0;
            t = tan(theta/2);
            r = t /(cos(omega)*t-sin(omega));
            if (((r < R_MAX) && (r > R_MIN)) || ((r > -R_MAX) && (r < -R_MIN)))
            {
                ApplyFilter(2, M, maxk, r, u, y);
            }
            else
            {
                /* r is out of range! */
                printf("r is out of range\n");
                printf("r %3.4f omega %3.4f angle %3.4f theta %3.4f\n", r, omega, angle, theta);
                printf("Trying 2 filters with half the angle\n");
                theta = pi+omega-angle*pi/360;
                t = tan(theta/2);
                r = t /(cos(omega)*t-sin(omega));
                if (((r < R_MAX) && (r > R_MIN)) || ((r > -R_MAX) && (r < -R_MIN)))
                {
                    ApplyDoubleFilter(2, M, maxk, r, u, y);
                }
                else
                {
                    /* try apf=2 */
                    printf("Sorry, r is still out of range\n");
                }
            }
        }
	}
    printf("r %3.4f\n",r);
    return r;
}

void Usage()
{
    printf("used in DASC 2011 paper\n");
    printf("updated 26th Sep 2024 Dublin Ohio For Book Writing\n");
	printf("Usage: [y r]=APF[u, a, M, fn]\n"); 
    printf("y is an maxk by M matrix\n");    
    printf("r is the pole of the APF\n");
	printf("u is an array of signals with maxk samples\n");
	printf("a is the angle for phase-shift delay in degrees between 0 and 360 (scalar)\n");
	printf("M is the number of sensor elements (scalar)\n");
	printf("fn is the normalized frequency for sinusoid (scalar)\n");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputU, *inputA, *inputM, *inputF;
	double *yptr, angle, * u, ** y,fn,R,*rptr;
	int maxk,numOfColumns,m,k,r,c;

    if ((nlhs != 2) || (nrhs != 4))
    {
        printf("  Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(4) \n", nlhs, nrhs);
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
    u = (double*)malloc(maxk * sizeof(double));
    for (k = 0; k < maxk; k++) u[k] = inputU[k];

    inputM = mxGetPr(prhs[2]);
    r = mxGetM(prhs[2]); c = mxGetN(prhs[2]);
	if ( (r != 1) || (c != 1) )
	{
		Usage();
        printf("In this call, M is a scalar error (%d by %d)\n", r, c);
	} 
    numOfColumns = inputM[0];

    inputF = mxGetPr(prhs[3]);
    r = mxGetM(prhs[3]); c = mxGetN(prhs[3]);
    if ((r != 1) || (c != 1))
	{
		Usage();
		printf("In this call, fn is a scalar error (%d by %d)\n", r, c);
	}

    fn = inputF[0]; 	

    inputA = mxGetPr(prhs[1]);
    r = mxGetM(prhs[1]); c = mxGetN(prhs[1]);
    if ((r != 1) || (c != 1))
	{
		Usage();
		printf("In this call, angle a is a scalar error (%d by %d)\n", r, c);
		return;
	} 
    angle = inputA[0];

    /*if ((angle < 0) || (angle > 360))
    {
        Usage();
        Log("\n\nPhase-delay angle must be between 0 and 360 degrees only\n");
    }*/

	/* allocations and initializations */
    y = (double**)malloc(numOfColumns * sizeof(double*));
	for (m = 0; m < numOfColumns; m++)
	{
        y[m] = (double*)malloc(maxk * sizeof(double));
	}

	/* call the data generation */
	R = APFDG(angle, fn, numOfColumns, maxk, u, y);

	/* create and return matrix */
	plhs[0] = mxCreateDoubleMatrix(numOfColumns, maxk, mxREAL);
	yptr = mxGetPr(plhs[0]);
	for (m = 0; m < numOfColumns; m++)
	{
		for (k = 0; k < maxk; k++)
		{
			yptr[m+k* numOfColumns] = y[m][k];
		}
	}
    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    rptr = mxGetPr(plhs[1]); rptr[0]=R;
	/* towards freedom! */
	for (m = 0; m < numOfColumns; m++)
	{
		free(y[m]);
	}
	free(y);	
    return;
}
