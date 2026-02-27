// stfSteer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
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
#include "stfSteer.h"
//#include "mex.h"   /* This one is required */
FILE* fp;
double*  abcUlaArray(int, double*, double*, double*, int, int, double, double, double, double, double**, double**, double**, double**, double**, double**);
int main()
{
	double *SNR;
	int D = 3, maxk,m,M,kmax,k,i;
	int loopk = 30,er;
	double d_by_lambda, r_by_lambda, fn, N, stdNoise;
	double** sA, ** sB, ** sC;
	double** Ha, ** Hb, ** Hc;
	double se[2], r;
	double**Jk3Theta, ** doa3stf;
	double* doa;

	double DOAS[3] = { -70,  45,   50 }; //[40, -70, 50] [ -70,-35, 65];
	
	double POWS[3] = { 1.0, 1.0, 1.0 };
	double PHIS[3] = { 0.0, 0.0, 0.0 };
	M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
	N = 10.0; fn = 1 / N;  
	m = 2 * M + 1; stdNoise = 0.2; 
	sA = myAlloc2(m, maxk); Ha = myAlloc2(m, m);
	sB = myAlloc2(m, maxk); Hb = myAlloc2(m, m);
	sC = myAlloc2(m, maxk); Hc = myAlloc2(m, m);



	se[0] = 5.0; se[1] = 85.0; kmax = 80; r = 0.95;
	doa3stf = myAlloc2(6, D);


	loopk = 100; k = 0;
	doa = myAlloc(loopk);
	doa = linspace(-70.0, 70.0, loopk);
	er = fopen_s(&fp,"data.csv", "w");
	D = 3;
	for (k = 0; k < loopk; k++)
	{	
		//DOAS[0]= doa[k]; 
		//DOAS[1] = (rand() % 160)-80; DOAS[2] = (rand() % 160) - 80;
		//DOAS[0] = -80+k; DOAS[1] = 45; DOAS[2] = -70;
		SNR = abcUlaArray(D, DOAS, POWS, PHIS, M, maxk, d_by_lambda, r_by_lambda, fn, stdNoise, sA, sB, sC, Ha, Hb, Hc);
		printf("...........................................................................\n");
		printf("[%d]Actual Target Angles %3.4f %3.4f %3.4f\n",k,DOAS[0], DOAS[1], DOAS[2]);
		printf("...........................................................................\n");
		//	for (k = 0; k < D; k++)
	//		printf("%3.4f ", DOAS[k]); printf("\n");
		Jk3Theta = ula3doa(Ha, Hb, Hc, r, d_by_lambda, m, D, se, kmax, doa3stf);
	//	printf("%3.4f %3.4f %3.4f %3.4f\n", doa[k], doa3stf[0][0], doa3stf[2][0], doa3stf[4][0]);
		//getchar();
	}
	fclose(fp);

	/*for (i = 0; i < kmax; i++)
	{
		printf("3 ULA %d %3.4f %3.4f %3.4f %3.4f\n", i, Jk3Theta[0][i], Jk3Theta[1][i], Jk3Theta[2][i], Jk3Theta[3][i]);
	}*/
	for (k = 0; k < 3; k++)
	{
		printf("[%d] ", k);
		for (i = 0; i < D; i++) printf("%3.4f ", doa3stf[2*k][i]); //printf("\n");
	}

	return 1;
}

