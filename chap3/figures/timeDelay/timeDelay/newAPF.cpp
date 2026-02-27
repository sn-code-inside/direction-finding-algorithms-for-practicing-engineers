/*

APF Data Generation Program APF.c for DASC 2011

*/

#include "math.h"
#include "mex.h"   /* This one is required */
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
void Usage();
double APFDG
(
	double ,  /* the angles in degrees for incoming signals */
	double ,  /* normalized frequency */
    int*  ,   /* output type of filter applied */
    double  ,   /* rmin */
    double    /* rmax */
);



double APFDG
(
	double angle, /* the angles in degrees for incoming signals */
	double fn, /* normalized frequency */
    int* type, /* the output modified number */
    double R_MIN, /* rmin */
    double R_MAX /* rmax */
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
//        ApplyFilter(1, M, maxk, r, u, y);
          type[0]=1;
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
//            ApplyDoubleFilter(1, M, maxk, r, u, y);
            type[0] = 2;            
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
//                ApplyFilter(2, M, maxk, r, u, y);
                  type[0] = 3;  
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
//                    ApplyDoubleFilter(2, M, maxk, r, u, y);
                      type[0] = 4; 
                }
                else
                {
                    /* try apf=2 */
                    printf("Sorry, r is still out of range\n");
                    type[0] = -1;
                }
            }
        }
	}
//    printf("r %3.4f\n",r);
    return r;
}

void Usage()
{
    printf("used in DASC 2011 paper\n");
    printf("updated 28th Sep 2024 Dublin Ohio For Book Writing\n");
	printf("Usage: [r type]=newAPF[fn,a,rmin,rmax]\n"); 
    printf("type of filter applied\n");
    printf("1 normal APF\n");
    printf("2 2nd Order APF\n");
    printf("3 normal APF with input sign changed\n");
    printf("4 2nd Order APF with input sign changed\n");
    printf("r is the pole of the APF\n");
	printf("a is the angle for phase-shift delay in degrees between 0 and 360 (scalar)\n");
	printf("fn is the normalized frequency for sinusoid (scalar)\n");
    printf("rmin is minimum value of r 0.1\n");
    printf("rmax is maximum value of r 0.95\n");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputA, *inputF,*inputRmin,*inputRmax;
	double angle, fn,R,*rptr,*typePtr;
	int maxk,numOfColumns,m,k,r,c,type=0;
    double R_MIN, R_MAX;

    if ((nlhs != 2) || (nrhs != 4))
    {
        printf("  Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(4) \n", nlhs, nrhs);
        Usage();
		return;
	}
    
       
    inputF = mxGetPr(prhs[0]);
    r = mxGetM(prhs[0]); c = mxGetN(prhs[0]);
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

    inputRmin = mxGetPr(prhs[2]);
    r = mxGetM(prhs[2]); c = mxGetN(prhs[2]);
    if ((r != 1) || (c != 1))
    {
        Usage();
        printf("In this call, rmin is a scalar error (%d by %d)\n", r, c);
        return;
    }
    R_MIN = inputRmin[0];

    inputRmax = mxGetPr(prhs[3]);
    r = mxGetM(prhs[3]); c = mxGetN(prhs[3]);
    if ((r != 1) || (c != 1))
    {
        Usage();
        printf("In this call, rmax is a scalar error (%d by %d)\n", r, c);
        return;
    }
    R_MAX = inputRmax[0];



	/* call the data generation */
	R = APFDG(angle, fn,&type,R_MIN,R_MAX);

	/* create and return matrix */
	plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    typePtr = mxGetPr(plhs[0]);
    typePtr[0] = type;
    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    rptr = mxGetPr(plhs[1]); rptr[0]=R;

    return;
}
