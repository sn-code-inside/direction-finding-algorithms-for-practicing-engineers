// musicAndGmu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// gMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "musicAndGmu.h"
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
int main()
{
	complex** A;
	int rcA[2], i;
	int numOfPhaseSpecSamples = 180;
	double* muSpk,* eigValues;
	double* doaInDeg, d_by_lambda;
	double SamplesPerCycle;
	double std, SNR = 1;
	int D = 2, r;
	complex** En;
	rcA[0] = 128; rcA[1] = 32;
	if (D >= rcA[1]) { printf(" no solution %d %d\n", D, rcA[1]); return -1; }

	double DOAS[3] = { 20, -35, 25 };
	double POWS[3] = { 1.0, 1.0, 1.0 };
	doaInDeg = myAlloc(D);
	eigValues = myAlloc(rcA[1]);
	muSpk = myAlloc(numOfPhaseSpecSamples);
	//	........ generate data matrix ......
	d_by_lambda = 0.5; std = 0.5; D = 2; SamplesPerCycle = 5.0; // samples per cycle
	A = IQ(rcA, D, DOAS, POWS,d_by_lambda, SamplesPerCycle, std, &SNR);
	printf(" SNR 10*log10(signal power/noise power) %f\n", SNR);
	//	....................................
	r = rcA[1] - D; if (r < 1) { printf("issue with number of sources %d %d\n", rcA[1], D); r = 1; }
	En = myAlloc2Complex(r, rcA[1]);
	printf(" size of data matrix %d by %d\n", rcA[0], rcA[1]);
	doaInDeg = Hermit(A, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En, eigValues,d_by_lambda);
	printf(" DOA values by gold MUSIC\n");
	for (i = 0; i < D; i++) printf(" %3.4f ", doaInDeg[i]); printf("\n");
	if (doaInDeg == NULL) return -1;
	getchar();

	return 1;
}

