//	gMUSIC
//#include "mex.h"   /* This one is required */
#include "stdafx.h"
#include "eigHermit.h"
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
complex** Hermit(complex **A, int *rc, int D,double *Lh)
{
	int k,cby2,i,JkL = 5000; // this number troubled me ?? yes again
	complex **H,**E,**Et;
	double  *Jk;
	double pi;
	int c,*indx,kt;
	pi = (double)(atan(1.0)*4.0);
	cby2 = rc[1]; 
	H = myAlloc2Complex(cby2, cby2);

	E = myAlloc2Complex(cby2, cby2);
	Et = myAlloc2Complex(cby2, cby2);
 
	Jk = myAlloc(JkL);
	for (k = 0; k < cby2; k++) Lh[k] = 0.0;

	CeqABtrnsp(H, A, rc, "H = A * (A transpose)");
	// ...................
	eigenvecH(H, Et, Lh, Jk, &JkL, cby2);
	indx = High2Low(cby2, Lh);
	for (k = 0; k < cby2; k++)
	{
		for (i = 0; i < cby2; i++)
		{
			kt = indx[k];
			E[i][k] = Et[i][kt];
		}
	}
	myFree2Complex(Et, cby2);
	return E;
}

double DegPhase2Doa(double phi, double dbyl)
{
	double arg, pi2dbyl, pi, doaInDeg;
	pi = atan(1.0)*4.0;
	pi2dbyl = 360.0*dbyl; // this is beacuse I am using in degrees
	arg = phi / pi2dbyl; if (fabs(arg) > 1.0) arg = arg / fabs(arg);
	doaInDeg = (double)(asin(arg)*(180 / pi));
	return doaInDeg;
}


void eigenvecH(complex **H, complex **E, double *Lh, double *Jk, int *JkL, int rows)
{
//	double **Ar, **Ai;
	double big = -1.0F;
	double **Ev, *L, **bi;
	int i = 0, k = 0, n = 0, m = 0, M = 2*rows;
	printf("!. void eigenvecH(..)\n");
	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
	printf("!. B = [ Hr Hi\n");
	printf("!.      -Hi Hr ];\n");

//	Allocate Memory //
	M = 2 * rows;
	bi = myAlloc2(M, M); Ev = myAlloc2(M, M); L = myAlloc(M);

/* bi is the 2n*2n real symmetric matrix (equivalent for a n order hermitian matrix)*/

	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
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
	big = -1.0;
	big = fabs(bi[0][0]);
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
		{
			if ( fabs(bi[m][n]) > big) big = fabs(bi[m][n]);
		}
	}
	printf("!. Matrix bi is a composite matrix is scaled by %f\n", big);
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
			if (fabs(big) != 0) bi[m][n] = bi[m][n] / big;
	}
	JkL[0] = M;
	eigenvecR(bi, M, Ev, L, Jk, JkL);
	printf("!. Eig Values ");
	for (i = 0; i < M; i++) printf("%3.4f ", L[i]); printf("\n");
	sortEigOnVal(Ev, L, E, Lh, M);
	for (m = 0; m < rows; m++) Lh[m] = Lh[m] * big; // scale back

// Free Memory
	myFree2(bi, M);
//	for (i = 0; i < M; i++) free(bi[i]);  // free rows
//	free(bi);
	return;

}

void sortEigOnVal(double **EV, double *L, complex **E, double *Lh, int rows)
{
	int k, m, n, minpos, tpos, *P, M;
	double temp;
	P = (int *)malloc(rows * sizeof(int));
	M = rows / 2;
	printf("!. void sortEigOnVal(double **EV, double *L, complex **E, double *Lh, int rows(%d));\n", rows);
	printf("!. Original Hermitian %d\n", M);
	for (m = 0; m < rows; m++)  P[m] = m;

	for (m = 0; m < rows; m++)
	{
		minpos = m;
		for (n = m + 1; n < rows; n++)
		{
			if (L[minpos] > L[n]) minpos = n;
		}

		temp = L[minpos];  L[minpos] = L[m];
		L[m] = temp;  tpos = P[minpos];
		P[minpos] = P[m]; P[m] = tpos;
	}

	for (m = 0; m < M; m++)
	{
		Lh[m] = L[2 * m];
		for (n = 0; n < M; n++)
		{
			k = P[2 * n];
			E[m][n].r = EV[m][k]; E[m][n].i = -EV[m + M][k];
		}
	}
	free(P);
	return;
}

void CeqABtrnsp(complex **C, complex **A, int* rcA, const char *anot)
{
	int i, m, k;
	complex sum, P; conjmul mulconj; cadd add;
	int cols, rows;
	rows = rcA[0];  cols = rcA[1];
	printf("!. size of A %d by %d compute %s\n", rows,cols,anot);
	for (i = 0; i < cols; i++)
	{
		for (m = 0; m < cols; m++)
		{
			sum.r = 0.0; sum.i = 0.0;  
			for (k = 0; k < rows; k++)
			{
				P = mulconj.mulconj(A[k][m], A[k][i]);
				sum = add.add(P, sum);
			}
			C[i][m] = sum;
		}
	}
	return;
}

void printComplxMatrix(complex **A, int rows, int cols)
{
	int i, k;
	double a, b;
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < cols - 1; k++)
		{
			a = A[i][k].r; b = A[i][k].i;
			if (b > 0) printf("%6.4f + %6.4fi, ", a, b);
			else printf("%6.4f - %6.4fi, ", a, fabs(b));
		}
		a = A[i][k].r; b = A[i][k].i;
		if (b > 0) printf("%6.4f + %6.4fi ", a, b);
		else printf("%6.4f - %6.4fi", a, fabs(b));
		printf("\n");
	}
//	printf("\n");
	return;
}

void printMatrix(double** A, int rows, int cols)
{
	int i, k;
	double a, b;
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < cols; k++)
			printf("%3.4f ", A[i][k]); 	printf("\n");
	}
	return;
}



