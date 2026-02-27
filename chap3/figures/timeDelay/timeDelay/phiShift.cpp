
#include "phiShift.h"
//#include "mex.h"   /* This one is required */

//order = ChoseAPForder(phiD, fn, maxk, yf, yR); // yR is the output


/* ChoseAPForder: Chooses either APF once or APF twice with half the angle */
/* Also, Chooses between APF-1 and APF-2 */
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
    int k,  order;
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
    printf("[%d] Shift %f Degrees, flag %d, pole %f\n", apfOrder[k],angle, flag, apfR[k]);
    r[0] = apfR[0];
    return apfOrder[0];
}




