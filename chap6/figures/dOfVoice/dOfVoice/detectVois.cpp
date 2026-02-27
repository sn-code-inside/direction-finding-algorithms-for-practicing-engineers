#include "stdafx.h"
#include "detectVois.h"
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
//void DetectVoice(int,double*,double*,int *,int *);
//void ortho(int, double*, double*);
//void NBF(int,double*,double*);
/* DetectVoice: Detedt Voice Segments in the Data and Picks of maximum size */
/* Output filtered at 2Khz with 100 Hz Band-Width */
int DetectVoice
(
	int Maxk, /* total number of samples needed */
    double *Uk, /* input sequence size Maxk */
	double *yTemp, /* the output sequences detected and filtered */
	//int *maxk, /* the output sequences size maxk */
	int *startx /* the output sequences size maxk */
)
{
    int start = 0, last = Maxk;
    int slp;
    double *u;
	int k,kt,big = -1,flag = 0,bigS=0;
    int voice=0,maxk = 0;
        ortho(Maxk,Uk,yTemp);         
        kt = 0;
        for (k = 0; k < Maxk-1; k++) 
        {
            slp = (int)(yTemp[k+1] - yTemp[k]); // yTemp[k] 0 or 1;
 //           printf("[%d] slope %3.4f (%3.4f %3.4f)\n", k, slp, yTemp[k + 1], Uk[k]);
            if ( slp ==  1 ) { start = k; flag = 1; }
            if ( slp == -1 ) { last = k;  flag = -1; }
            
            if ( flag == 1 ) kt = kt + 1;
            if ( flag == -1 ) 
            { 
                if ( kt > big ) { big = kt; last = k; bigS = start; }
 //               printf(" Starting Edge %d Falling Edge at %d\n",start,k);
 //               printf(" width = %d last big width %d index %d\n",kt,big,last);
                voice = voice + 1;
                kt = 0; flag = 0;
            }
        }
        if (flag == 1) 
        { 
            printf("Only Starting Edge Detected .. NO Falling Edge\n");
            big = kt; last = k; bigS = start; voice = voice + 1;  
        }
        if ( big < 0 ) 
        { 
                printf(" start = %d last %d\n",start,last);
                printf(" Dynamic Error No Voice Detected .. Some Problem \n"); 
                return maxk; 
        }
        maxk = big; start = bigS;

//        u = (double *)mxCalloc(big, sizeof(double));
        u = myAlloc(big);
        
//        yfx = (double *)mxCalloc(big, sizeof(double));
        for ( k = 0; k < big; k++) u[k] = Uk[k+start];
//        printf(" %d Voice Segments were Detected and maxmimum is taken as\n",voice);
//        printf(" Voice Detected from %d to %d and maxk %d and Total %d\n",start,last,maxk,Maxk);
//        NBF(big,u,yTemp); 
//        printf(" Extracted 600 Hz slice at 2Khz from the Voice\n");
        startx[0] = start;
        free(u);
        return maxk;
}

void ortho
(
	int maxk, /* total number of samples needed */
    double *u, /* input sequence size maxk */
	double *y /* the output sequences size maxk */
)
{
 	double uk1=0, uk0=0, xk1=0, xk0=0, zk=0, ek=0, pk =0.0,rk;
	double dly[40], bufer[41];
    double loopGain = 0.008F, shift = 0.0;
	int delay = 39,i,k; // Integration window of MA Filter
    double big = -9876543210.0,Uk=0,Zk=0,Lpf = 0.9;
    double *temp;
    
    //temp  = (double *)mxCalloc(maxk, sizeof(double));
    temp = myAlloc(maxk);
    for (i= 0; i<= delay; i++) 	{bufer[i] = 0.0; dly[i] = 0.0;}

	uk0 = 0.0; xk1 = 0.0; pk=0.0; uk1 =0.0; rk=0.1F;
	for (k=0; k < maxk; k++)
	{ 

		uk1=uk0; xk1=xk0;
		uk0=u[k]; //% FSK contains the input data and Phase shifted in Xk by pi/2
		
		xk0=rk*xk1 - rk*uk0 + uk1; //% uk0 --> APF --> xk0
		zk=uk0*xk0;
		
		//1. transfer dly into bufer [1 to 40].
		for (i= 0; i<= delay; i++) 	bufer[i+1] = dly[i];
		
		//2. bufer[0] equates to zk.
		bufer[0] = zk;
		
		//3. transfer bufer [0 to 39] into dly.
		for (i= 0; i<= delay; i++) 	dly[i] = bufer[i];
		
		
		ek = (dly[delay]-dly[0])/(delay);
//		A = (float)(fabs(pk)); 	if ( A > 10.0 ) pk = 10.0*pk/A;
        if (k == 0) big = fabs(pk);
        else
        {
            if (fabs(pk) > big) big = fabs(pk);
        }
        
        y[k] = pk; temp[k] = rk;
		pk = pk+ek; rk = rk - loopGain*(pk+shift);
		
		if (fabs(rk) > 0.95) rk=0.95;

	}
   for (k=0; k < maxk; k++) 
    { 
        pk = y[k]; 
        if (fabs(pk / big) < 0.01) Uk = 0; else Uk = 1.0;
        Zk = Zk*Lpf + (1-Lpf)*Uk; 
        if ( Zk > 0.01 ) y[k] = 1; else y[k] = 0;
    }
   free(temp);
   return;
}

/* NBF: Butter Worth NB Filter for fs = 16Khz and at center frequency 2Khz*/
/* Coefficients are fixed */
void NBF
(
	int maxk, /* total number of samples needed */
    double *u, /* input sequence size maxk */
	double *y /* the output sequences size maxk */
)
{
    
/* Butter-Worth Filter Coeffcients and States 
    Compute Sections Of Second order
    fs = 16000; f1 = 2E3; f2 = f1 + 100;
    fc = (f1 + f2)/2; fcN = fc/fs;
    Wn = [f1/fs f2/fs]*2;

    [bL,aL]=butter(2,Wn); 
    [sos,g] = tf2sos(bL,aL);
    format long
    sos
    g  
 */    
    
    double X[6], Y[6], BUb[4], BUa[4];
    double sumA, sumB,g,big = -9876543210.0;
    int k;
    
            X[2] = 0; X[1] = 0; Y[1] = 0; Y[2] = 0;
            X[5] = 0; X[4] = 0; Y[4] = 0; Y[5] = 0;
            
            BUb[0] = 2.0;  BUb[1] = 1.0;
            
            BUa[0] = -1.01649695776247;  // 600 Hz
            BUa[1] = 0.83714137522651;  // 600 Hz
            BUa[0] = -1.34720218651493;  // 100 Hz
            BUa[1] = 0.97225328143306;  // 100 Hz

            BUb[2] = -2.0;  BUb[3] = 1.0;
            
            BUa[2] = -1.27093997437284; // 600 Hz
            BUa[3] = 0.85604880455258; // 600 Hz
            g =  1.185768264324e-002; // 600 Hz 
            BUa[2] = -1.38719251053070;  // 100 Hz
            BUa[3] = 0.97297479401453; // 100 Hz
            g =  3.750696162970606e-004;  // 100 Hz
            
        for ( k = 0; k < maxk; k++)
        {
   // First Section Second Order 
            Y[0] = Y[1];  Y[1] = Y[2];
        	X[0] = X[1];  X[1] = X[2];
            X[2] = u[k]; // INPUT
		
            sumB =( X[2] + (BUb[0]*X[1] )+( BUb[1]*X[0] )); 
            // Numerator Coefficients uk(1 + z-1BUb(1) + z-2BUb(2)) .. b01 +  b11 z^-1 +  b21  z^-2
            sumA = (BUa[0]*Y[1]) + (BUa[1]*Y[0]); 
            // Denominator Coeffcients yk(1 + z-1BUa[1] + z-2BUa(2))..  1  +  a1k z^-1 +  a2k  z^-2
            Y[2]= sumB - sumA;

            
   // Second  Section Second Orde
            Y[3] = Y[4];  Y[4] = Y[5];
        	X[3] = X[4];  X[4] = X[5];
            X[5] = Y[2]; // INPUT output of the previous filter
		
            sumB =( X[5] + (BUb[2]*X[4] )+( BUb[3]*X[3] )); // Numerator Coefficients
            sumA = (BUa[2]*Y[4]) + (BUa[3]*Y[3]); // Denominator Coeffcients
            Y[5]= (sumB - sumA);
            
            y[k] = Y[5]*g;
            if ( fabs(y[k]) > big ) big = fabs(y[k]);
        }
        for ( k = 0; k < maxk; k++ ) y[k] = y[k]/big;

}
