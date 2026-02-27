#include "ula3doaStf.h"
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
double** ula3doa
(
	double **Ha, 
	double** Hb, 
	double** Hc, 
	double r, 
	double d_by_lambda, 
	int m, 
	int D, 
	double* se, 
	int kmax, 
	double **doa3stf
)
{
	int i,k,ula = 3,kt;
	double** JkTheta, ** Jk3Theta, ** doaStf, ** doa3;

	double* validPhi{};
	Jk3Theta = myAlloc2(4, kmax); doaStf = myAlloc2(D, 2); 
	doa3 = myAlloc2(ula, D); 
	/*...............................................................................*/
	// Ula A
	JkTheta = stfDoa(Ha, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[0][k] = JkTheta[0][k]; // J(theta) of A
	//printf(" ULA A gold peaks[%d] ",D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[0][i]    = doaStf[i][0];
		doa3stf[0][i] = doaStf[i][0];
		doa3stf[1][i] = doaStf[i][1];
	} //printf("\n");
	
	// Ula B
	JkTheta = stfDoa(Hb, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[1][k] = JkTheta[0][k]; // J(theta) of B
	//printf(" ULA B gold peaks[%d] ", D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[1][i]    = doaStf[i][0];
		doa3stf[2][i] = doaStf[i][0]; 
		doa3stf[3][i] = doaStf[i][1];
	} //printf("\n");

	// Ula C
	JkTheta = stfDoa(Hc, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[2][k] = JkTheta[0][k]; // J(theta) of C
	for (k = 0; k < kmax; k++) 	Jk3Theta[3][k] = JkTheta[1][k]; // theta value
	//printf(" ULA C gold peaks[%d] ", D);
	for (i = 0; i < D; i++)
	{
		//printf("--- %3.4f ", doaStf[i][0]);
		doa3[2][i]    = doaStf[i][0];
		doa3stf[4][i] = doaStf[i][0]; 
		doa3stf[5][i] = doaStf[i][1];
	} //printf("\n");
	/*...............................................................................*/
	kt = 0;
	validPhi = rotateDecode(doa3, D, ula, &kt);
	//validPhi = stateDecode(doa3, D, ula, &kt);

	printf(" OUTPUT Rotate Decode [%d] ",kt);
	for (i = 0; i < D; i++) printf("%3.4f ", validPhi[i]); printf("\n\n");
	//for (k = 0; k < D; k++) fprintf(fp, "%3.4f, ", validPhi[k]); fprintf(fp, "\n");
//	free memory
	myFree2(doa3, ula); myFree2(doaStf, D);
	return Jk3Theta;
}





