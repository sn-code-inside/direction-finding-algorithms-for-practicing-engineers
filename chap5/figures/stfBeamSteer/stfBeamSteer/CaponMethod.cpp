#include "CaponMethod.h"
//extern FILE* fp;
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
double** ula3doaCapon
(
	double** Ha, 
	double** Hb, 
	double** Hc, 
	double r, 
	double d_by_lambda, 
	int m, 
	int D, 
	double* se, 
	int kmax, 
	double** doa3stf
)
{
	int i, k, ula = 3, kt;
	double** JkTheta, ** Jk3Theta, ** doaStf, ** doa3;

	double* validPhi{};
	Jk3Theta = myAlloc2(4, kmax); doaStf = myAlloc2(D, 2);
	doa3 = myAlloc2(ula, D);
	/*...............................................................................*/
	// Ula A
	JkTheta = stfDoaCapon(Ha, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[0][k] = JkTheta[0][k]; // J(theta) of A
	//printf(" ULA A gold peaks[%d] ",D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[0][i] = doaStf[i][0];
		doa3stf[0][i] = doaStf[i][0];
		doa3stf[1][i] = doaStf[i][1];
	} //printf("\n");

	// Ula B
	JkTheta = stfDoaCapon(Hb, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[1][k] = JkTheta[0][k]; // J(theta) of B
	//printf(" ULA B gold peaks[%d] ", D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[1][i] = doaStf[i][0];
		doa3stf[2][i] = doaStf[i][0];
		doa3stf[3][i] = doaStf[i][1];
	} //printf("\n");

	// Ula C
	JkTheta = stfDoaCapon(Hc, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[2][k] = JkTheta[0][k]; // J(theta) of C
	for (k = 0; k < kmax; k++) 	Jk3Theta[3][k] = JkTheta[1][k]; // theta value
	//printf(" ULA C gold peaks[%d] ", D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[2][i] = doaStf[i][0];
		doa3stf[4][i] = doaStf[i][0];
		doa3stf[5][i] = doaStf[i][1];
	} //printf("\n");
	/*...............................................................................*/
	kt = 0;
	//validPhi = rotateDecode(doa3, D, ula, &kt);
	//validPhi = stateDecode(doa3, D, ula, &kt);

	//printf(" OUTPUT Rotate Decode [%d] ", kt);
	//for (i = 0; i < D; i++) printf("%3.4f ", validPhi[i]); printf("\n\n");
	//for (k = 0; k < D; k++) fprintf(fp, "%3.4f, ", validPhi[k]); fprintf(fp, "\n");
//	free memory
	myFree2(doa3, ula); myFree2(doaStf, D);
	return Jk3Theta;
}

double** stfDoaCapon(double** Ha, double r, double d_by_lambda, int m, int D, double* se, int kmax, double** doaStf)
{
	int k, i, numberOfPks = D, pksNumber, * peaksIndx, NGS = 20;
	double* Jk, s, e, * doa, ** ab;
	double* goldPk, SE[2];
	double** JkTheta;

	s = se[0]; e = se[1];
	Jk = myAlloc(kmax); peaksIndx = myAllocI(20); ab = myAlloc2(kmax, 4);
	JkTheta = myAlloc2(2, kmax);

	doa = linspace(s, e, kmax);
	//printf("r = %3.4f dbl %3.4f and kmax %d [%3.4f %3.4f] \n", r, d_by_lambda, kmax, s, e);
	for (k = 0; k < kmax; k++)
	{
		Jk[k] = objCapon(Ha, r, doa[k], d_by_lambda, m);
		JkTheta[0][k] = Jk[k]; JkTheta[1][k] = doa[k];
	}


	//bounds[0] = s; bounds[1] = e;
	pksNumber = SweeplocateDoaPks(kmax, numberOfPks, ab, Jk, doa);
	if (pksNumber < 0) return NULL;
	//printf(" Number of Peaks %d\n", pksNumber);
	//peaksIndx = findPeaks(kmax,&numOfPeaks,Jk);
	//for (k = 0; k < pksNumber; k++)
	//{
	//	printf("[%d] start %3.4f end %3.4f max value %3.4f\n", (int)(ab[k][2]), ab[k][0], ab[k][1], ab[k][3]);
	//}
	for (i = 0; i < D; i++)
	{
		SE[0] = ab[i][0]; SE[1] = ab[i][1];
		goldPk = goldDoa(m, Ha, d_by_lambda, SE, r, NGS);
		doaStf[i][0] = goldPk[0]; doaStf[i][1] = goldPk[1];
	}
	free(Jk); free(peaksIndx); free(doa); myFree2(ab, kmax);
	//locateDoaPks(kmax, numberOfPks, ab, Jk);
	return JkTheta;
}

double objCapon(double** H, double r, double theta, double d_by_lambda, int m)
{
	double Jk, * w;
	double nearZero = 10;
	w = CaponWeight(r, theta, d_by_lambda, m);
	if (fabs(theta) > nearZero)
	{
		Jk = wTranposeHmulW(H, w, m);
	}
	else Jk = rand() / 32767.0;
	return Jk;
}

double* CaponWeight
(
	double r,     /*Pole position of the narrow band pass filter*/
	double theta, /*spatial angle*/
	double dbl,   /*d/lambda*/
	int m         /*no of sensors*/
)
{
	int  k=0;
	double phi, pi, a, rPowK, rPowKm2;
	double sinKp1, sinKm1;
	double* w,kBym;
	//  compute beam coefficients
	pi = atan(1.0) * 4.0;
	w = myAlloc(m);
	a = (1 - (r * r)) / 2.0;
	phi = 2 * pi * dbl * sin(theta * pi / 180);
	kBym = (double)(k) / (double)(m);

	for (k = 0; k < m; k++)
	{
		kBym = (double)(k) / (double)(m);
		w[k] = 1.0 + 0.5 * sin(2 * pi * kBym);
	}
	return w;
}

