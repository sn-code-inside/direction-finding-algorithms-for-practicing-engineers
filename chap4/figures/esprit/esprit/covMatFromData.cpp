//#include "mex.h"   /* This one is required */
#include "stdafx.h"
#include "covMatFromData.h"
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
complex** covMat(complex* sk, int lenSk, int*rcS,int numberOfRows)
{
	int m,n,N,k,s,kt=0,i;
	complex** R;
	N = lenSk;
	m = numberOfRows; n = N - m + 1;
	if (m < n){  rcS[0] = n; rcS[1] = m;} else
	{ rcS[0] = m; rcS[1] = n; }

	m = rcS[0]; n = rcS[1];
	printf("!. size of Hankel %d by %d\n", rcS[0], rcS[1]);
	R = myAlloc2Complex(m, n);
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			R[i][k] = sk[i + k];
		} 
		kt = kt + 1;
	}
	return R;
}

complex** mySvd(complex** S, complex** E, int* rcS, int D, double* eigValues)
{
	int i, k, m,n, JkL = 600, * indx;
	int rcE[2],rcU[2];
	double** Sig, * Jk;
	complex** U, ** Us{}, ** Elocal;
	m = rcS[0];  n = rcS[1];
	printf("!. Compute Left Eigen Vectors using SVD\n");
	Elocal = Hermit(S, rcS, D, eigValues);
	for (i = 0; i < n; i++)
	{
		for (k = 0; k < n; k++)
		{
			E[i][k] = Elocal[i][k];
		}
	}
	rcE[0] = rcS[1]; rcE[1] = rcS[1];

	for (i = 0; i < n; i++) eigValues[i] = sqrt(fabs(eigValues[i]));
	printf("!. Sqrt Eigen Values of Hermitian\n");
	for (i = 0; i < n; i++)
	{
		printf("%3.4f ", eigValues[i]);
	}
	printf("\n");

	Sig = myAlloc2(n, n);
	for (i = 0; i < n; i++)
	{
		for (k = 0; k < n; k++)
		{
			if (i == k)
				Sig[i][k] = 1.0 / eigValues[i];
			else Sig[i][k] = 0.0;
			//printf("%3.4f ", Sig[i][k]);
		} //printf("\n");
	}
	//getchar();

	U = CeqAB(S, rcS, E, rcE,rcU, "U = S * (E transpose)");
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < n; k++)
		{
			U[i][k].r = Sig[k][k] * U[i][k].r;
			U[i][k].i = Sig[k][k] * U[i][k].i;
		}
	}
	Us = myAlloc2Complex(m, D);
	//rcS[0] = m; rcS[1] = D;
	for (i = 0; i < m; i++)
	{
		for (k = 0; k < D; k++)
		{
			Us[i][k] = U[i][k];
			//printf("%3.4f %3.4fi  \t", Us[i][k].r, Us[i][k].i);
		}   //printf("\n");
	}
	return Us;
}


complex** SquareMatMul(complex** A, complex** B, int n, const char* anot)
{
	int i, k,m;
	complex sum, P; cmul mul; cadd add;
	complex** C;
	int cols, rows;
	rows = n;  cols = n;
	C = myAlloc2Complex(n, n);
	printf("!. size of A %d by %d compute %s\n", rows, cols, anot);
	for (i = 0; i < cols; i++)
	{
		for (m = 0; m < cols; m++)
		{
			sum.r = 0.0; sum.i = 0.0;
			for (k = 0; k < rows; k++)
			{
				P = mul.mul(A[k][m], A[k][i]);
				sum = add.add(P, sum);
			}
			C[i][m] = sum;
			//printf("%3.4f %3.4fi ", sum.r, sum.i);
		}//printf("\n");
	}
	//getchar();
	return C;
}

complex** CeqAB(complex** A, int* rcA, complex** B, int* rcB, int* rc, const char* anot)
{

	int m, n, p, q; // Dimensions of matrices
	int i, j, k;
	complex sum, P; cmul mul; cadd add;
	complex** C;
	m = rcA[0]; n = rcA[1]; p = rcB[0]; q = rcB[1];
	rc[0] = m; rc[1] = q;
	// result matrix C (m x q)
	C = myAlloc2Complex(m, q);
	// Input dimensions and matrix elements for A and B

	if (n != p) 
	{
		printf("incompatible multiplication.\n");
		return NULL; 
	}

	printf("!. size of A (%d by %d) B (%d by %d) C (%d by %d) compute %s\n", m,n,p,q,m,q, anot);
	for (int i = 0; i < m; i++) 
	{
		for (int j = 0; j < q; j++) 
		{
			sum.r = 0.0; sum.i = 0.0; // Initialize element
			for (int k = 0; k < n; k++) 
			{ 
				P = mul.mul(A[i][k], B[k][j]); //A[i][k] * B[k][j]
				sum = add.add(P, sum);
			}
			C[i][j] = sum;
		}
	}
	return C;
}

void LSQ(complex** Es, int* rcE)
{
	complex** A, **H;
	int m,D,k,i,rcA[2];
	m = rcE[0]; D = rcE[1];
	rcA[0] = m - 1; rcA[1] = D;
	A = myAlloc2Complex(rcA[0], rcA[1]);
	printf("size of A matrix %d by %d\n", rcA[0], rcA[1]);
	for (i = 0; i < rcA[1]; i++)
	{
		for (k = 0; k < rcA[0]; k++) A[k][i] = Es[k][i];
	}
	H = myAlloc2Complex(rcA[1], rcA[1]);
	CeqABtrnsp(H, A, rcA, "H = A * (A transpose)");
	printComplxMatrix(H, D, D);

	return;
}
