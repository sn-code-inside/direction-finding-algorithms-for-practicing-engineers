//	gMUSIC
//#include "mex.h"   /* This one is required */
#include "stdafx.h"
#include "music.h"
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
double* Hermit(complex **A, int *rc, int rForMusic, double *obj,int N,int D,complex **En,double *eigValues,double dbyl)
{
	int k,cby2,i,JkL = 600; // this number troubled me ?? yes again
	complex **H,**E;
	double *Lh, *Jk;
//	double *obj, doaInDeg;
	double doaInDeg;
//	double minMax[2];
	double delth, *phi,*theta;
	double pi;
	double  **AB,ab[2];
	int indxFlag, numberOfPks = D;
	int r;
//	int D;
	double *JkMu, *doaMu, *goldJk;
	int NGS = 15;
//	printf("double Hermit(..)\n");
	pi = (double)(atan(1.0)*4.0);
	cby2 = rc[1]; 
	H = myAlloc2Complex(cby2, cby2);
	E = myAlloc2Complex(cby2, cby2);
	Lh = myAlloc(cby2); Jk = myAlloc(JkL);
	phi = myAlloc(N); theta = myAlloc(N);
	AB = myAlloc2(numberOfPks, 4); // this has on 4 columns start end indx max(obj) for each peak
	JkMu = myAlloc(D); doaMu = myAlloc(D);


	CeqABtrnsp(H, A, rForMusic, cby2, "H = A * (A transpose)");
	eigenvecH(H, E, Lh, Jk, &JkL, cby2);
	printf(" Eigen Values of Hermitian\n");
	for (i = 0; i < cby2; i++)
	{
		printf("%3.4f ", Lh[i]);
		eigValues[i] = Lh[i];
	}printf("\n");
	doaInDeg = -90.0; obj[0] = 3.1415;
	delth = 360.0 / (N - 1);
	for (k = 0; k < N; k++) phi[k] = k*delth - 180.0;

//	................... new ....
	r = cby2 - D; 
	if (r < 1) 
	{ 
		printf("--->Error in evalObj %d %d\n", cby2, D); 
		return NULL; 
	}
	//	En = myAlloc2Complex(r, cby2);
	printf("size of E %d by %d\n", cby2, cby2);
	printf("size of En %d by %d\n", r, rc[1]);
	for (i = 0; i < r; i++)
	{
		for (k = 0; k < cby2; k++)
		{
			En[i][k] = E[k][i];
		}
	}
	//printComplxMatrix(En, r, cby2);
	//return doaMu;
	//	.........................................
	printf(" Evaluate Coarse Objective Function\n");

	for (k = 0; k < N; k++)
	{
		doaInDeg = DegPhase2Doa(phi[k], dbyl);
		theta[k] = doaInDeg;
		obj[k] = evalObj(En, doaInDeg, cby2, dbyl,D,Lh);
	}  
	indxFlag = locateDoaPks(N, numberOfPks, AB, obj);
	printf(" Locate Peaks and bounds\n");
	//	printf(" s=AB[i][0]  e=AB[i][1] indx = AB[i][2] max of obj = AB[i][3]\n");
	for (k = 0; k < numberOfPks; k++)
	{
		ab[0] = DegPhase2Doa(AB[k][0], dbyl); ab[1] = DegPhase2Doa(AB[k][1], dbyl);
//		printf(" %d .. (%3.4f  %3.4f) max obj %3.4f\n", (int)(AB[k][2]),ab[0], ab[1],AB[k][3]);
		goldJk = gMusic(cby2, En, Lh,&JkMu[k], &doaMu[k], ab, dbyl,D, NGS);
//		printf("!. gold peak[%d] %3.4f at %3.4f\n\n", k,JkMu[k], doaMu[k]);
	}

//	Free Memory
	myFree(Jk); myFree(phi); myFree(theta);
	myFree(Lh);
	myFree2Complex(H, cby2);
	myFree2Complex(E, cby2);
	myFree2(AB, numberOfPks);
	return doaMu;
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

void CeqABtrnsp(complex **C, complex **A, int rows, int cols, const char *anot)
{
	int i, m, k;
	complex sum, P; conjmul mulconj; cadd add;
	printf("!. compute %s\n", anot);
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

double evalObj(complex **En, double doaInDeg, int cby2, double dbyl, int D, double *Lh)
{
	complex  * w{}, * h{}, psum;
	cadd add;  conjmul mulconj; Cabs cabs;
//	double pi, dbyl, doa, A, omega;
	double pi, doa, A, omega;
	double Jk = 1.0, sum = 1.0;
	int k,r,i;
	//dbyl = 0.5;
	pi = (double)(atan(1.0)*4.0);
	w = myAllocComplex(cby2); h = myAllocComplex(cby2);

	r = cby2 - D; if (r < 1) { printf("Error in evalObj %d %d\n", cby2, D); return -10.0; }
//	for (k = 0; k < r; k++) printf("%3.4f\t", Lh[k]); printf("\n");
//	En = myAlloc2Complex(r, cby2);
//	for (i = 0; i < r; i++)
//	{
//		for (k = 0; k < cby2; k++) En[i][k] = EV[k][i];
//	}
	//printComplxMatrix(En, r, cby2);

	A = 2 * pi*dbyl;
	doa = (double)(doaInDeg*pi / 180.0);
	omega =(double)( A*sin(doa) );	// omega is the phase 
	for (k = 0; k < cby2; k++) { w[k].r = (double)(cos(omega*k)); w[k].i =(double)( sin(omega*k) ); }
	for (i = 0; i < r; i++)
	{
		h[i].r = 0.0; h[i].i = 0.0;
		for (k = 0; k < cby2; k++) 
		{ 
//			psum = mul.mul(w[k], En[i][k]); h[i] = add.add(psum, h[i]);
			psum = mulconj.mulconj(w[k], En[i][k]); h[i] = add.add(psum, h[i]); // kMUSIC and MUSIC sign fix
		}
//		printf("h[%d] %3.4f ", i,cabs(h[i]));
	}   //printf("\n");
	sum = 0.0;  for (i = 0; i < r; i++) sum = sum + cabs.cabs(h[i]);
	Jk = 1.0 / sum;
//	Free Memory ..
//	myFree2Complex(En, r);
//	for (i = 0; i < r; i++) En[i] = (free(En[i]), NULL);  // free rows
//	En = (free(En), NULL);
	free(h); free(w);

	return Jk;
}

double * gMusic
(
	int cby2,
	complex **EV,
	double *Lh,
	double *jK,
	double *doa,
	double *ab,
	double dbyl,
	int D,
	int NGS
)
{
	int i;
	double aa, bb, cc, dd;
	double fc=0, fd=0, g;
	double pi = (double)(atan(1.0)*4.0);
	double* goldJk;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  27th Jul 2017 Dr Kaluri Reserach House. @ Home Office Princeton NJ
	goldJk = myAlloc(NGS);
	aa = ab[0]; bb = ab[1];
	g =(double)( (3 - sqrt(5)) / 2 );
	for (i = 0; i < NGS; i++)
	{
		cc = aa + g*(bb - aa);
		dd = cc + g*(bb - cc);

		fc = -evalObj(EV, cc, cby2,dbyl,D,Lh); // double evalObj(complex **EV, double doaInDeg, int cby2, int D)
		fd = -evalObj(EV, dd, cby2,dbyl,D,Lh); // negative sign to take care of maxima to look like minima 23-2-2016

		if (fc <= fd) { bb = aa; aa = dd; }
		else { aa = cc; cc = dd; }
		goldJk[i] = aa;
	}
	doa[0] = aa;  jK[0] = (double)(fabs(fc));
	return goldJk;
}
