/*
 
    IQdata.c Program for Signal Generation for ULA
 
*/


#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "mex.h"   /* This one is required */

#define PI 3.14159

void GenerateSignals(
    int M, /* each ULA has M elements */
    int maxk, /* number of snapshots */
    int D, /* number of emitters */
    double *DOAS, /* doa angles in degrees -180 to +180 */
    double *POWS, /* signal relative ratios */
    double *phi, /* signal initial phases in degrees */
    double dn, /* d by lambda */
    double fn, /* fc/fs or sampling rate */
    double theta, /* ULA normal angle with true North in degrees */
    double std, /* sigma of the WGN */
    double *SNR, /* SNR */
    double **sR, /* Real signal  */
    double **sI, /* Imag signal  */
    double **nR, /* Real noise  */
    double **nI /* Imag noise  */
    )
{
    int s, m, k,seed, **b;
    double p;
    double phsAr, phsAi, phs0, phsT;
    double Amp,rnd,np,sp,temp;
    
    mexPrintf(" Emmiters DOA (deg) and Their Strengths\n");
    for (m=0; m<D; m++)
    mexPrintf(" %f ",DOAS[m] );
    mexPrintf("\n");
    for (m=0; m<D; m++)
    mexPrintf(" %f ",POWS[m] );
    mexPrintf("\n");
    
    seed = time(NULL);
    srand(seed);
    
    b = (int **)mxCalloc(D, sizeof(int*));
	for (m = 0; m < D; m++) b[m] = (int *)mxCalloc(maxk, sizeof(int));
    
        for (k = 0; k < maxk; k++)
        {
            for (m = 0; m < D; m++)
            { rnd = rand(); if ( ((rnd/32767.0) - 0.5) < 0 ) b[m][k] = -1; else b[m][k] = 1; }
        }

    np = 0;
    for (m=0; m<M; m++)
    {
        for (k=0; k<maxk; k++)
        {
            rnd = 0.0; for ( s=0; s<12; s++) rnd = rnd + ((rand()/32767.0) - 0.5);
            nR[m][k] = rnd * sqrt(std/2);
            
            rnd = 0.0; for ( s=0; s<12; s++) rnd = rnd + ((rand()/32767.0) - 0.5);
            nI[m][k] = rnd * sqrt(std/2);
            np = np + nR[m][k]*nR[m][k] + nI[m][k]*nI[m][k]; 
        }
    }
    
    /* normalize powers */
    p = 0.0; /* this will be set to the maximum value */
    for (s = 0; s < D; s++)
    {
        if (p < POWS[s])
        {
            p = POWS[s];
        }
    }
    if (p > 0.0)
    {
        for (s = 0; s < D; s++)
        {
            POWS[s] = POWS[s]/p;
        }
    }
        
    /* Signals at A */
    sp = 0;
    for (m = 0; m < M; m++)
    {
        for (k = 0; k < maxk; k++)
        {
            sR[m][k] = 0.0; sI[m][k] = 0.0;
            for (s = 0; s < D; s++)
            {
                phsAr = 2*PI*(m)*dn*sin( DOAS[s]*PI/180 + theta*PI/180);
                phs0 = phi[s]*PI/180;
                phsT = phs0  + phsAr;

                Amp = b[s][k]*POWS[s];
                sR[m][k] = sR[m][k] + Amp * cos( 2*PI*fn*(k) + phsT );

                sI[m][k] = sI[m][k] + Amp * sin( 2*PI*fn*(k) + phsT );
                sp = sp + sR[m][k]*sR[m][k] + sI[m][k]*sI[m][k];        
            }
                temp = sR[m][k];
                sR[m][k] = sR[m][k] + nR[m][k];
                nR[m][k] = temp;
                
                temp = sI[m][k];
                sI[m][k] = sI[m][k] + nI[m][k];
                nI[m][k] = temp;
        }
    }
    sp = sp/D;
    mexPrintf(" Noise Variance  %f\n Noise Power %f Signal Power/Emitter %f\n",std,np,sp);
    *SNR = 10*log10(sp/np);
//    mexPrintf(" SNR 10*log10(signal power/noise power) %f\n",*SNR);
	for (m = 0; m < D; m++) mxFree(b[m]);
    mxFree(b);
}




void Usage()
{
	mexPrintf("Usage: [s,w,snr]=ulaIQ(D, DOAS, POWS, PHIS, M, maxk, d_by_lambda, fn,theta,stdNoise)\n");
	mexPrintf("Inputs: 9 and Ouputs 3 updated on 10th May 2024\n");
	mexPrintf("0. D>=1 is number of emitters.\n");
    mexPrintf("1. DOAS is a row-vector of at least D DOA angles in degrees between -180 and +180.\n");
    mexPrintf("2. POWS is a row-vector with at least D relative strength ratios.\n");
    mexPrintf("3. PHIS is a row-vector with at least D initial phases in degrees.\n");
    mexPrintf("4. Each ULA A,B and C has 2*M+1 elements.\n");
    mexPrintf("5. maxk is the number of snapshots.\n");
    mexPrintf("6. d_by_lambda is ratio of inter-sensor distance of ULA to wavelength.\n");
    mexPrintf("7. fn is normalized frequency of the ALL THE EMITTERS. (i.e. SAME FREQUENCY IS ASSUMED).\n");
    mexPrintf("8. theta is angle of normal of ULA wrt true North.\n");
    mexPrintf("9. Noise Variance.\n");
	
    mexPrintf(" Outputs:\n");
    mexPrintf("0. s is a complex matrix of M X maxk signal with NOISE from ULA\n");
    mexPrintf("1. w is a complex matrix of M X maxk ONLY signal from ULA\n");
    mexPrintf("2. SNR\n");
}
