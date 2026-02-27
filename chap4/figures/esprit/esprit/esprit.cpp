// esprit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "esprit.h"
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
	int rcA[2], rcS[2],rcPhi[2],k,i;
	int numOfPhaseSpecSamples = 180;
	double * eigValues;
	double* doaInDeg, d_by_lambda;
	double SamplesPerCycle;
	double std, SNR = 1;
	double* Jk;
	double* phase, *theta, *pole;
	int D = 3, r, numberOfRows,JkL = 5000;
	complex** U{}, ** S, * sk, ** E, ** phi, ** Et{};
	complex* eigv;
	rcA[0] = 16; rcA[1] = 31;
	if (D >= rcA[1]) { printf(" no solution %d %d\n", D, rcA[1]); return -1; }

	double DOAS[3] = { 20, -35, 25 };
	double POWS[3] = { 1.0, 1.0, 1.0 };
	double pi;
	pi = atan(1.0) * 4.0;
	doaInDeg = myAlloc(D);
	Jk = myAlloc(JkL);
	//
	//	........ generate data matrix ......
	numberOfRows = 12;
	sk = myAllocComplex(rcA[1]); 
	d_by_lambda = 0.5; std = 0.5; D = 3; SamplesPerCycle = 5.0; // samples per cycle
	A = IQ(rcA, D, DOAS, POWS, d_by_lambda, SamplesPerCycle, std, &SNR);

	for (i = 0; i < rcA[0]; i++)
	{
		for (k = 0; k < rcA[1]; k++) sk[k] = A[i][k];
		//	....................................
		printf("!. Size of array data matrix %d by %d\n", rcA[0], rcA[1]);
		S = covMat(sk, rcA[1], rcS, numberOfRows); numberOfRows = rcS[0];
		eigValues = myAlloc(rcS[1]);
		printf("!. Size of Hankel %d %d\n", rcS[0], rcS[1]);
		if (D >= rcA[1]) printf("!. NO SOLUTION\n");
		//  Singular Value Decomposition
		eigValues = myAlloc(rcS[1]);
		E = myAlloc2Complex(rcS[1], rcS[1]);
		U = mySvd(S, E, rcS, D, eigValues); // signal matrix from left hand vectors
		printf("!. Size of signal matrix %d by %d\n", rcS[0], D);
		//  ..............................
		//  Least Square Solution
		phi = Svd2Lsq(U, rcS, D, rcPhi);
		//	Eigen Values of phi
		Et = myAlloc2Complex(D, D);
		eigv = myAllocComplex(D);
		eigv = eigPhi(phi, Et, D);
		phase = myAlloc(rcPhi[0]); theta = myAlloc(rcPhi[0]);
		pole = myAlloc(rcPhi[0]);
		for (k = 0; k < rcPhi[0]; k++)
		{
			pole[k] = sqrt((eigv[k].r) * (eigv[k].r) + (eigv[k].i) * (eigv[k].i));
			phase[k] = atan2(eigv[k].i, eigv[k].r) * (180.0 / pi);
			theta[k] = asin(-phase[k] / 180) * (180 / pi);
			printf("!. DOA[%d] %3.4f\n", k, theta[k]);
		}
		getchar();
	}
	return 1;
}


