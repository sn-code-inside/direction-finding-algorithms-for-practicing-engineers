//#include "mex.h"   /* This one is required */
#include "stdafx.h"
#include "LsQComplex.h"
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
complex** Svd2Lsq(complex** U, int*rcS,int D,int *rcPhi)
{
	int rcUs[2], rcAe[2],rcMoor[2],k,i;
	complex** Ae, ** b,**Moor,**phi;
	rcUs[0] = rcS[0]; rcUs[1] = D;
	rcAe[0] = rcUs[0] - 1; rcAe[1] = rcUs[1];
	Ae = myAlloc2Complex(rcAe[0], rcAe[1]);
	b = myAlloc2Complex(rcAe[0], rcAe[1]);
	for (k = 0; k < rcAe[1]; k++)
	{
		for (i = 0; i < rcAe[0]; i++)
		{
			Ae[i][k] = U[i][k];    // for LSQ left hand side
			b[i][k] = U[i + 1][k]; // for LSQ right hand side
		}
	}
	Moor = MoorePenrose(Ae, rcAe, rcMoor); // inv(Ae'*Ae)*Ae';
	phi = CeqAB(Moor, rcMoor, b, rcAe, rcPhi, "Lsq Solution");
	return phi;
}

complex** MoorePenrose(complex** A, int* rcA, int *rcMoor)
{
	int n,twoN,j,k,i;
	complex** H,**invH,**At,**Moor;
	int rcH[2], rcAt[2];
	double** b,scale;
	double** invB{};
	n = rcA[1]; twoN = 2 * n;
	H = myAlloc2Complex(n, n); invH = myAlloc2Complex(n, n);
	printf("!. size of input matrix in moore %d %d\n", rcA[0], rcA[1]);
	CeqABtrnsp(H, A, rcA, "H = A * (A transpose)-MoorePen");
	b = complex2real(H, n, &scale);
	invB = myAlloc2(twoN, twoN);
	MatrixInversion(b, twoN, invB);

	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			k = i;
			invH[j][i].r = invB[j][k]/scale; invH[j][i].i = -invB[j + n][k]/scale;
		}
	}
	At = AconjTranspose(A, rcA); // At = Ae' and invH = inv(Ae*Ae')
	rcH[0]  = n; rcH[1]  = n;
	rcAt[0] = n; rcAt[1] = rcA[0];
	Moor = CeqAB(invH, rcH, At, rcAt, rcMoor, "Moore Penrose Psuedo Inverse");
	return Moor;
}

complex** AconjTranspose(complex** A, int* rcA)
{
	int j, k,m,n;
	complex** At;
	m = rcA[0]; n = rcA[1];
	At = myAlloc2Complex(n, m);
	for (k = 0; k < n; k++)
	{
		for (j = 0; j < m; j++)
		{
			At[k][j].r =  A[j][k].r;
			At[k][j].i = -A[j][k].i;
		}
	}
	return At;
}

double** complex2real(complex** H, int rows, double* scale)
{
	int M=1, m, n;
	double** bi, big;
	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
	printf("!. B = [ Hr Hi\n");
	printf("!.      -Hi Hr ];\n");
	//	Allocate Memory //
	M = 2 * rows;
	bi = myAlloc2(M, M);
	/* bi is the 2n*2n real symmetric matrix (equivalent for a n order hermitian matrix)*/

	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order complex matrix H)\n", M, M, rows);
	printf("!. B = [ Br Bi\n");
	printf("!.      -Bi Br ];\n");
	for (m = 0; m < rows; m++)
	{
		for (n = 0; n < rows; n++)
		{
			bi[m][n] = H[m][n].r;				// bi[m][n] = Ar[m][n];
			bi[m + rows][n] = -H[m][n].i;		// bi[m + rows][n] = -Ai[m][n];
			bi[m][n + rows] = H[m][n].i;		// bi[m][n + rows] = Ai[m][n];
			bi[m + rows][n + rows] = H[m][n].r;	// bi[m + rows][n + rows] = Ar[m][n];
		}
	}

	// Find the maximum value in matrix bi
	//big = -1.0;
	big = fabs(bi[0][0]);
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
		{
			if (fabs(bi[m][n]) > big) big = fabs(bi[m][n]);
		}
	}
	printf("!. Matrix bi is a composite matrix is scaled by %f\n", big);
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
			if (fabs(big) != 0) bi[m][n] = bi[m][n] / big;
	}
	scale[0] = big;
	return bi;
}
