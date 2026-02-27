//	gMUSIC
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
// #include "stdafx.h"
#include "music.h"
#include "mex.h"
double easyMusic(complex **S, int *bins, double *config, double *Mudoas,double **muSpk,complex **eN,int D)
{
	int rForMusic, muS, muE;
	int i, m,cby2, ch,k,bin,rc[2],r;
	int numberOfTgts, numOfPhaseSpecSamples;
	complex** Mu, **En{};
	double doaInDeg;
	double* s;
	Cabs cabs;
	numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
	rc[0] = (int)(config[7]); rc[1] = 8; cby2 = rc[1] / 2;
//	printf("double easyMusic()\n");

//	.......... for music alogorithm .....................
	rForMusic = 10;
	s = (double*)malloc(rForMusic * sizeof(double));
	Mu = myAlloc2Complex(rForMusic, cby2);
	r = cby2 - D; if (r < 1) { printf("Error in evalObj %d %d\n", cby2, D); r = 1; }
	En = myAlloc2Complex(r, cby2);


	for (k = 0; k < numberOfTgts; k++)
	{
		bin = bins[k];
		muS = bin - rForMusic / 2;  muE = bin + rForMusic / 2;
		if (muS < 0) { muS = 0; muE = rForMusic; }
		else if (muE > rc[0]) { muE = rc[0]; muS = rc[0] - 3; }

//		printf("Target %d bin doapar[3] %d bounds[%d %d]\n", k, bin, muS, muE);
		for (i = 0; i < rForMusic; i++)
		{
//			printf("%d %d ", i, i+muS);
			for (ch = 0; ch < cby2; ch++)
			{
				Mu[i][ch] = S[i + muS][ch];
				s[0] = (cabs.cabs(S[i + muS][ch]));
//				printf("%3.4f  ", s[0]);
			}//printf("\n");
		}

		doaInDeg = Hermit(Mu, rc, rForMusic, muSpk[k],numOfPhaseSpecSamples,D,En); //getchar();
		for (i = 0; i < r; i++)
		{
			for (m=0; m < cby2; m++) eN[i+r*k][m] = En[i][m];
		}
//		printComplxMatrix(En, r, cby2);
//	............. this is all for MUSIC .....................
		Mudoas[k] = doaInDeg;
	}
	myFree2Complex(Mu, rForMusic); myFree2Complex(En, r);
//	for (i = 0; i < rForMusic; i++) Mu[i] = (free(Mu[i]), NULL);  // free rows
//	Mu = (free(Mu), NULL); 
	free(s);

	return doaInDeg;

}

double Hermit(complex **A, int *rc, int rForMusic, double *obj,int N,int D,complex **En)
{
	int k,cby2,i,JkL = 60; // this number troubled me ??
	complex **H,**E;
	double *Lh, *Jk;
//	double *obj, doaInDeg;
	double doaInDeg;
	double minMax[2];
	double delth, *phi;
	double pi;
	double dbyl, **AB,ab[2];
	int indxFlag, numberOfPks =2;
	int r;
//	int D;
	double JkMu=0.0, doaMu=0.0;
//	printf("double Hermit(..)\n");
	pi = (double)(atan(1.0)*4.0);
	dbyl = 0.5;
	cby2 = rc[1] / 2; // r = 10; 
//	D = 2;
	H = (complex **)malloc(cby2 * sizeof(complex *));
	for (i = 0; i<cby2; i++) H[i] = (complex *)malloc(cby2 * sizeof(complex));
	E = (complex **)malloc(cby2 * sizeof(complex *));
	for (i = 0; i<cby2; i++) E[i] = (complex *)malloc(cby2 * sizeof(complex));
	Lh = (double *)malloc(cby2 * sizeof(double)); // Eigen Values of Hermitian
	Jk = (double *)malloc(JkL * sizeof(double));
//	obj = (double *)malloc(N * sizeof(double));
	phi = (double *)malloc(N * sizeof(double));
	AB = (double **)malloc(numberOfPks * sizeof(double *)); // number of rows = # Peaks
	for (i = 0; i<numberOfPks; i++) AB[i] = (double *)malloc(4 * sizeof(double)); // 4 columns

	CeqABtrnsp(H, A, rForMusic, cby2, "H = A * (A transpose)");
	eigenvecH(H, E, Lh, Jk, &JkL, cby2);
	//for (i = 0; i < cby2; i++) printf("%3.4f ", Lh[i]); printf("\n");
	doaInDeg = -90.0; obj[0] = 3.1415;
	delth = 360.0F / (N - 1);
	for (k = 0; k < N; k++) phi[k] = k*delth - 180.0;

//	................... new ....
	r = cby2 - D; if (r < 1) { printf("Error in evalObj %d %d\n", cby2, D); return -10.0; }
//	En = myAlloc2Complex(r, cby2);
	for (i = 0; i < r; i++)
	{
		for (k = 0; k < cby2; k++) En[i][k] = E[k][i];
	}
//	.........................................

	for (k = 0; k < N; k++)
	{
		doaInDeg = DegPhase2Doa(phi[k], dbyl);
		obj[k] = evalObj(En, doaInDeg, cby2, D);
//		printf("[%d] obj %3.4f phase %3.4f doa %3.4f\n", k, obj[k], phi[k], doaInDeg);
//		getchar();
	}  
	indxFlag = locateDoaPks(N, numberOfPks, AB, obj);
	ab[0] = DegPhase2Doa(AB[0][0], dbyl); ab[1] = DegPhase2Doa(AB[0][1], dbyl);
//	printf("AB .. %3.4f %3.4f %3.4f %3.4f\n", ab[0], ab[1], AB[0][2], AB[0][3]);
	gMusic(cby2, E, &JkMu, &doaMu, ab, D, 15);
//	printf("!. gold peak %3.4f at %3.4f\n", JkMu, doaMu);
//	getchar();
	myMaxMin(obj, minMax, N);
//	for (i = 0; i < N; i++)
//	fprintf(fpDeg, "%3.4f,", obj[i]/minMax[1]);
//	fprintf(fpDeg, "\n");
//	Free Memory
//	obj = (free(obj), NULL); 
	myFree(Jk); myFree(phi);
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
//	printf("!. void eigenvecH(..)\n");
//	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
//	printf("!. B = [ Hr Hi\n");
//	printf("!.      -Hi Hr ];\n");

//	Allocate Memory //
	M = 2 * rows;
	bi = myAlloc2(M, M); Ev = myAlloc2(M, M); L = myAlloc(M);
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
	big = -1.0F;
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
			if ( (double)(fabs(bi[m][n]) ) > big) big = (double)(fabs(bi[m][n]));
	}
//	printf("!. Matrix A is scaled by %f\n", big);
	for (m = 0; m < M; m++)
	{
		for (n = 0; n < M; n++)
			if (fabs(big) != 0) bi[m][n] = bi[m][n] / big;
	}
	JkL[0] = M;
	eigenvecR(bi, M, Ev, L, Jk, JkL);
//	for (i = 0; i < M; i++) printf("%3.4f ", L[i]); printf("\n");

	sortEigOnVal(Ev, L, E, Lh, M);
//	for (m = 0; m < rows; m++) Lh[m] = Lh[m] * big; // scale back

// Free Memory
	myFree2(bi, M);
//	for (i = 0; i < M; i++) bi[i] = (free(bi[i]), NULL);  // free rows
//	bi = (free(bi), NULL);
	return;

}

void sortEigOnVal(double **EV, double *L, complex **E, double *Lh, int rows)
{
	int k, m, n, minpos, tpos, *P, M;
	double temp;
	P = (int *)malloc(rows * sizeof(int));
	M = rows / 2;
//	printf("!. void sortEigOnVal(double **EV, double *L, complex **E, double *Lh, int rows(%d));\n", rows);
//	printf("!. Original Hermitian %d\n", M);
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
//	printf("!. compute %s\n", anot);
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

double evalObj(complex **En, double doaInDeg, int cby2, int D)
{
	complex  * w{}, * h{}, psum;
	cadd add;  conjmul mulconj; Cabs cabs;
	double pi,dbyl,doa,A,omega;
	double Jk = 1.0, sum = 1.0;
	int k,r,i;
	dbyl = 0.5;
	pi = (double)(atan(1.0)*4.0);
	w = myAllocComplex(cby2); h = myAllocComplex(cby2);

	r = cby2 - D; if (r < 1) { printf("Error in evalObj %d %d\n", cby2, D); return -10.0; }

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
	sum = 0.0f;  for (i = 0; i < r; i++) sum = sum + cabs.cabs(h[i]);
	Jk = 1.0f / sum;
	free(h); free(w);

	return Jk;
}

void gMusic
(
	int cby2,
	complex **EV,
	double *jK,
	double *doa,
	double *ab,
	int D,
	int NGS
)
{
	int i;
	double aa, bb, cc, dd;
	double fc, fd, g;
	double pi = (double)(atan(1.0)*4.0);
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  27th Jul 2017 Dr Kaluri Reserach House. @ Home Office Princeton NJ

	aa = ab[0]; bb = ab[1];
	g =(double)( (3 - sqrt(5)) / 2 );
	for (i = 0; i < NGS; i++)
	{
		cc = aa + g*(bb - aa);
		dd = cc + g*(bb - cc);

		fc = -evalObj(EV, cc, cby2,D); // double evalObj(complex **EV, double doaInDeg, int cby2, int D)
		fd = -evalObj(EV, dd, cby2,D); // negative sign to take care of maxima to look like minima 23-2-2016

		if (fc <= fd) { bb = aa; aa = dd; }
		else { aa = cc; cc = dd; }
	}
	doa[0] = aa;  jK[0] = (double)(fabs(fc));
	return;
}
