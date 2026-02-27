// gMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "gMu.h"
//#include "mex.h"   /* This one is required */
int main()
{
	complex** A;
	int rcA[2],i;
	int numOfPhaseSpecSamples = 180; 
	double* muSpk;
	double *doaInDeg, d_by_lambda;
	double SamplesPerCycle;
	double std , SNR = 1;
	int D = 2,r;
	complex** En;
	rcA[0] = 128; rcA[1] = 6;
	if (D >= rcA[1]) { printf(" no solution %d %d\n", D, rcA[1]); return -1; }

	double DOAS[3] = { 20, -35, 25 };
	doaInDeg = myAlloc(D);
	muSpk = myAlloc(numOfPhaseSpecSamples);
//	........ generate data matrix ......
	d_by_lambda = 0.5; std = 0.1; D = 2; SamplesPerCycle = 8.0; // samples per cycle
	A = IQ(rcA,D,DOAS,d_by_lambda, SamplesPerCycle,std,&SNR);
	printf(" SNR 10*log10(signal power/noise power) %f\n", SNR);
//	....................................
	r = rcA[1] - D; if (r < 1) { printf("issue with number of sources %d %d\n", rcA[1], D); r = 1; }
	En = myAlloc2Complex(r, rcA[1]);
	printf(" size of data matrix %d by %d\n", rcA[0], rcA[1]);
	doaInDeg = Hermit(A, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En,d_by_lambda);
	printf(" DOA values by gold MUSIC\n");
	for (i = 0; i < D; i++) printf(" %3.4f ", doaInDeg[i]); printf("\n");
	if (doaInDeg == NULL) return -1;
	getchar();

	return 1;
}

