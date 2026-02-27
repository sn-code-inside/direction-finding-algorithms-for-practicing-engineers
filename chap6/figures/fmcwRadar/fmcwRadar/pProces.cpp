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
#include "stdafx.h" // THIS IS A MUST
#include "pProces.h"
//#include "mex.h"   /* This one is required */
void preProc
(
	complex ** B, 
	complex **S, 
	double *sAvg, 
	double *config, 
	int zerofill
)
{
	int i, j, k, s, e,N,M;
	int cby2,rc[2];
	double *x,temp,**Mag;
	complex* u{}, ** A{};
	rc[0] = (int)(config[7]); rc[1] = 8;

	cby2 = rc[1] / 2;
	printf("!. void preProc %d numOfTgts\n", (int)(config[4]));
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
//	N = rc[0]; // we have moved to complex FFT and the spectrum is full N bins
	temp = (double)(rc[0]);
	M = (int)(log10(temp) / log10(2.0F));
	N = (int)(pow(2, M)); // check if it is 2^integer
//	if (N != 128) { printf("!. issue of FFT\n"); getchar(); }
	if (N != rc[0]) { printf("!. issue of FFT [%d]%d \n",N,rc[0]); getchar(); }

//	Allocate Memory ...
	u = myAllocComplex(rc[0]); 
	x = myAlloc(rc[0]);
	A = myAlloc2Complex(rc[0], cby2);
	Mag = myAlloc2(rc[0], cby2);
//	Start Execution ...
	for (k = 0; k < cby2; k++) { for (i = 0; i < rc[0]; i++) A[i][k] = B[i][k]; }
	s = zerofill; e = rc[0] - zerofill; if (e < 0) e = rc[0]; // safety
/*	........... Preprocessing of removing the short range and long range ..... 
	.. in this all channels are processed with no normalisation ...18th Sep 2017.....  */
	for (k = 0; k < cby2; k++)
	{

		for (i = 0; i < N; i++) u[i]= A[i][k];
//		angle = ortho(N, u); printf("%3.4f ", angle);
		sampleSpek(u, x, N, M);
		for (j = 0; j < s; j++) { u[j].r = 0; u[j].i = 0; x[j] = 0.0;} // complex spectrum is forced zero at the ends
		for (j = e; j < N; j++) { u[j].r = 0; u[j].i = 0; x[j] = 0.0;} // abs spectrum is also made zero at the ends
		for (j = 0; j < N; j++) 
		{ 
			Mag[j][k] = x[j];
			u[j].r = (u[j].r) / N; 	u[j].i = (u[j].i) / N; 
			S[j][k] = u[j];
		} 
// this is for IFFT
		sampleSpek(u, x, N, M);
		for (i = 0; i < N; i++) B[i][k] = u[i]; 
	} 
//	getchar();
//	timeAvg(B, u, rc, N);
//	for (i = 0; i < N; i++) { u[i].r = u[i].r; u[i].i = u[i].i; }
//	Amp = normalize(N, u, uScale);
//	printf("! start .. normalisation factor %3.4f\n", Amp); 
//	getchar();
//	......... Normalise the matrix B by a factor Amp .........
	for (k = 0; k < cby2; k++)
	{
		for (i = 0; i < rc[0]; i++) { B[i][k].r = B[i][k].r; B[i][k].i = B[i][k].i; }
	}
	SpekAvg(Mag, sAvg, rc);
// ...........................................................

/*	...     Free Memory ... */

	myFree2Complex(A, rc[0]);
	myFree2(Mag, rc[0]);
	free(u); u = NULL;  free(x); x = NULL;
	return;
}

void SpekAvg(double **Mag, double *x, int *rc)
{
	int i, k, r, c, cby2;
//	int km; double max;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	r = rc[0]; c = rc[1]; cby2 = c / 2;
	//	printf("!. timeAvg(double **A, complex *u, int *rc[%d.%d], int Un[%d])\n", r, c, Un);
	//	I faced problems with missing peaks in the c channels so is this
	//	Add all real arrays and imaginary arrays seperately and divide by the number of channels c/2
	for (i = 0; i < r; i++)
	{
		x[i] = 0.0F;
		for (k = 0; k < cby2; k++) x[i] = x[i] + Mag[i][k];
		x[i] = x[i] / cby2;
	}
//	km = myMax(x, r); max = x[km];
//	for (k = 0; k < r; k++) x[k] = (x[k] / max)*2000.0;
	return;
}

void timeAvg(complex **A, complex *u, int *rc, int Un)
{
	int i, k, r, c;
	r = rc[0]; c = rc[1];
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//	printf("!. timeAvg(double **A, complex *u, int *rc[%d.%d], int Un[%d])\n", r, c, Un);
	//	I faced problems with missing peaks in the c channels so is this
	//	Add all real arrays and imaginary arrays seperately and divide by the number of channels c/2
	for (i = 0; i < Un; i++)
	{
		u[i].r = 0.0F; u[i].i = 0.0F;
		for (k = 0; k < c / 2; k++)
		{
			u[i].r = u[i].r + A[i][k].r; u[i].i = u[i].i + A[i][k].i;
		}
		u[i].r = (u[i].r) * 2.0F / c; u[i].i = (u[i].i) * 2.0F / c;
	}
	return;
}
