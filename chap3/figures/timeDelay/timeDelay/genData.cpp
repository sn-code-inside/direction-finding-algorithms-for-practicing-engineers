// genData.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "genData.h"
//#include "mex.h"
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

//Generate experimental data.
double** ExpData(int nSize, double Tow, double N, double *SNR, double Cycles, double phiD,double *tau)
{
	int delay = 0;
//  Tow is the delay to be created in the pulse in cycles	
	double delt = 1.0,snr;
	double theta,n,Delay;
	double fn = 1.0 / (N);
	int k, offset;
	double** Data{}, ** True{};
	int maxRows = 4,order;
	snr = SNR[0];
	Data = myAlloc2(maxRows, nSize); True = myAlloc2(maxRows, nSize);
	offset = RxSig(Data[1], True[1], nSize, delay, N, &snr, Cycles); // zero delay
	delay = (int)(Tow * N); // obtain equivalent integral multiples of samples time  ( Cycle * Samples/Cycle )
	Delay = delay;
	printf("!. Tow %3.4f Integer Samples %3.4f\n", Tow*N, Delay);
	n = Tow * N - delay;
	theta = n*(360.0/N);
	printf("!. Integer %d Samples Shifting 2nd Column\n", delay);
	offset = RxSig(Data[2], True[2], nSize, delay, N, SNR, Cycles); // introduce desired delay
	printf("!. Fractional Shifting %3.4f Samples 2nd Column\n",n);
	order = ChoseAPForder(theta, fn, nSize, Data[2], Data[3]); // Data[3] is the output
	printf("!. (%3.4f)+Fraction Delay Samples %3.4f\n", Delay, n);
	for (k = 0; k < nSize; k++) Data[2][k] = Data[3][k];
	tau[0] = (double)(delay / N); // recompute true Tau
	for (k = 0; k < nSize; k++) {
		Data[0][k] = (double)(k * delt); True[0][k] = Data[0][k];
		//		printf("%3.4f %3.4f %3.4f\n", Data[0][k], Data[1][k], Data[2][k]);
	}
	myFree2(True, maxRows);
	return Data;
}


//....... Function 1
//
void myNoise
(
	int maxk,
	double std,
	double* uN
)
{
	int s, k;
	unsigned int seed;
	double rnd;
	seed = (unsigned int)(time(NULL));
	srand(seed);
//  Copy Right Protected  written by Prof Kaluri

//	printf(" Test Random Sequence ");
//	for (m = 0; m<5; m++) { temp = (rand() / 32767.0) - 0.5; printf(" %f ", temp); } printf("\n");

	for (k = 0; k < maxk; k++)
	{
		rnd = 0.0; 
        for (s = 0; s < 12; s++) rnd = rnd + ((rand() / 32767.0) - 0.5);
//		uN[k] = rnd * sqrt(std / 2);
		uN[k] = rnd * std;
	}
	return;
}




//....... Function 3
//
//
//Generate syntehtic data. Returns a signal and noise added signal.
//Delay has a maximum value of 1 corresponds size of the array * sample time
//Uk Corresponds noisy signal with an SNR deined by the variable SNR.
int RxSig(double* Uk, double* trueUk, int nSize, int delay, double N, double *SNR, double Cycles)
{
	int startA,w1,w2,width,k;
	double sigma; // compute noise SD
	double *noise,  * x,stdNoise,stdSignal,mu,snr;
	snr = SNR[0];
	sigma = (double)(pow(10.0, -snr / 20.0));
	noise = myAlloc(nSize);
	for (k = 0; k < nSize; k++) trueUk[k] = 0.0;
	x = narrowPulse(Cycles, N, &width); // generate narrow pulse of Cycles and N samples
	startA = (nSize / 2) - width; 
	w1 = startA + delay; w2 = w1 + width;
//	Transfer the Window back into Signal.
	for (k = w1; k < w2; k++) 	trueUk[k] = x[k - w1];
	myNoise(nSize, sigma, noise);
	printf(" sigma of the noise = %3.4f \n", sigma);
	muStd(trueUk, &stdSignal, &mu, nSize);
	printf(" signal power %3.4f(%3.4f)\n", stdSignal, mu);
	muStd(noise, &stdNoise, &mu, nSize);
	printf(" noise power %3.4f(%3.4f)\n", stdNoise, mu);
	SNR[0] = 10 * log10(stdSignal / stdNoise);
	printf(" SNR of Signal %3.4fdB\n",SNR[0]);
	printf(" [%3.4f Cycles] Total Samples %d int delay %d Samples %3.4f\n", Cycles, nSize, delay, N);
	printf(" SNR changed from %3.4f to %3.4f\n", snr, SNR[0]);
	printf(" Start pulse at %d and end pulse at %d offset is %d \n", w1, w2, delay);
	//	Transfer (trueUk + Noise) into  Uk,
	for (k = 0; k < nSize; k++)
	{
		Uk[k] = trueUk[k] + noise[k];
	}

	free(x);
	return delay;
}

double* narrowPulse(double Cycles, double N, int* Width)
{
	int k;
	double pi, * W, *m, *x,fm,f;
	int width = (int)(Cycles * N);
	Width[0] = width;
	pi = atan(1.0) * 4.0;
	fm = (double)(1.0 / width); f = 1.0 / N;
//  Create Hamming Window Function.
	W = myAlloc(width); x = myAlloc(width); m = myAlloc(width);
	for (k = 0; k < width; k++) W[k] = (double)(0.54 - 0.46 * cos(2 * pi * k / (width)));
	for (k = 0; k < width; k++)
	{
		m[k] = (double)cos(2 * pi * fm * k);
		x[k] = (double)(sin(2 * pi * f * k) * W[k] * m[k]);
	}
	free(W); free(m);
	return x;
}

void muStd(double* x, double* std, double* mu, int lenX)
{
	int k; double sum, ek;
	sum = 0.0;
	for (k = 0; k < lenX; k++) sum = sum + x[k]; mu[0] = sum / lenX;
	ek = 0.0;
	for (k = 0; k < lenX; k++) ek = ek + (x[k] - mu[0]) * (x[k] - mu[0]);
	std[0] = ek / lenX;
	return;
}

double** myAlloc2(int r, int c)
{
	double** A;
	int i;
	A = (double**)malloc(r * sizeof(double*));
	for (i = 0; i < r; i++)
	{
		A[i] = (double*)malloc(c * sizeof(double));
	}
	return A;
}

void myFree2(double** A, int r)
{
	int i;
	for (i = 0; i < r; i++)
	{
		free(A[i]);
		A[i] = NULL;
	}
	free(A);
	A = NULL;
	return;
}

double* myAlloc(int c)
{
	double* A;
	A = (double*)malloc(c * sizeof(double));
	return A;
}


char* getDate()
{
	//	......... local time ...................................
	int er;
	time_t now;
	struct tm bufT {};
	char* dtNtime;
	dtNtime = (char*)malloc(60 * sizeof(char));

	now = time(NULL);
	er = localtime_s(&bufT, &now);
	er = asctime_s(dtNtime, 60, &bufT);
	return dtNtime;
}


