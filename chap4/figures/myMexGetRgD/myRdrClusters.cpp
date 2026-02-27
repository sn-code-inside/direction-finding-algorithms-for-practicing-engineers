//#include "stdafx.h"
#include "myRdrClusters.h"
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

double** sortCluster(double** D, int rows, int cols, int numberOfTgts, int* rc, double* config)
{
	int k, i = 0, kmax, Kmax, * ind, pt;
	int newCols, rcA[2];
	double* tgts, ** A;
	double r, theta, pi;
	double bins2range = 0.0, rgain, maxBin;
	double rThold = config[12];
//	int flag;
	int lastRow;
	sort bins;
	tgts = (double*)malloc(rows * sizeof(double));
	ind = (int*)malloc(rows * sizeof(int));
	cols = 5;
	pi = (double)(atan(1.0) * 4.0);
	for (k = 0; k < rows; k++)
	{
		if (D[k][2] < rThold) D[k][1] = -1;
		tgts[k] = D[k][1];
		ind[k] = k;
	}
	bins.x = tgts; bins.xI = ind; bins.M = rows;
	bins.High2Low();
	kmax = rows;
	for (k = 0; k < rows; k++)
		if (tgts[k] < 0)
		{
			printf("!. range threshold %3.4f [%d reduced to %d rows]\n", rThold, kmax, k);
			kmax = k;
			break;
		}

	//	bins.showx(); 
	//newCols = cols + 2; Kmax = kmax + 2;
	newCols = cols + 2; Kmax = kmax;
	//A = (double**)malloc(Kmax * sizeof(double*));
	//for (i = 0; i < Kmax; i++) A[i] = (double*)malloc(newCols * sizeof(double));
	A = myAlloc2(Kmax, newCols);

	rcA[0] = Kmax; rcA[1] = newCols;

	rc[0] = Kmax; rc[1] = newCols;
	rgain = config[11]; maxBin = config[7];
	bins2range = (rgain / maxBin);
	printf("!. sortCluster() ->size [%d by %d] bin-gain %3.4f m/bin\n", Kmax, newCols, bins2range);
	printf("!. range gain %3.4f max no of bins %3.4f\n", rgain, maxBin);
	//	Creating two additional columns of X = r.cos(theta) and Y = r.sin(theta)
	for (i = 0; i < kmax; i++)
	{
		for (k = 0; k < cols; k++)
		{
			pt = ind[i]; A[i][k] = D[pt][k];
		}
		A[i][1] = A[i][1] * rgain; // updated on 29th Jun 2023 at Dublin
		r = A[i][1]; theta = A[i][3] * pi / 180.0;
		A[i][cols + 1] = r * cos(theta); A[i][cols] = r * sin(theta);
	}
	lastRow = i;
//	for (k = 0; k < cols; k++) A[lastRow - 1][k] = 0.0;

//	for (k = 0; k < cols; k++) A[lastRow][k] = 0.0;
//	A[lastRow][cols] = 0.5f * rgain; A[lastRow][cols + 1] = rgain;

//	for (k = 0; k < cols; k++) A[lastRow + 1][k] = 0.0;
//	A[lastRow + 1][cols] = -0.5f * rgain; A[lastRow + 1][cols + 1] = rgain;
	return A;
}




void pause(int dur)
{
//	pause in dur seconds
	int temp = (int)(time(NULL)) + dur;
	while (temp > time(NULL));
	return;
}

int** getCloudPointers(double** A, int* rcA, int *kmax)
{
	int i;
	int** parts;
//	int d;
	int M = rcA[0] - 2;
	int maximumNumOfPartions=15;
	double* L;

	L = (double*)malloc(M * sizeof(double));
	for (i = 0; i < M; i++) L[i] = A[i][1];

	parts = getCloudLinPt(L, M, maximumNumOfPartions, kmax);
	free(L);
	return parts;
}

int** CompactClouds(double** clouds, int* rcClouds, int* newr, double coupling)
{
	double* muk,er;
	int k,r,c,kt,flag = 0;
	int** ptsN, ** newParts;

	r = rcClouds[0]; c = rcClouds[1];
	muk = (double*)malloc(r * sizeof(double));

	ptsN = (int**)malloc(r * sizeof(int*));
	for (k = 0; k < r; k++) ptsN[k] = (int*)malloc(2 * sizeof(int));

	for (k = 0; k < r; k++)
	{
		ptsN[k][0] = (int)(clouds[k][0]); ptsN[k][1] = (int)(clouds[k][1]);
		muk[k] = sqrt(clouds[k][3] * clouds[k][3] + clouds[k][5] * clouds[k][5]);
	}
//	kt = 0;
	flag = 1;
	for (k = 0; k < r; k++)
	{
		er = distMeasure(muk[k], muk[k + 1]);
		if (er < coupling)  // important parameter
		{
			merge(ptsN, k, r);
			flag = -1;
		}
		else kt = 0;
//		printf("[%d] (%d %d).%d\n", k, ptsN[k][0], ptsN[k][1],kt);
	} 
	if (flag > 0) return NULL;

	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] < 0) kt = kt + 1;
	}
	newr[0] = r - kt;
	printf("!. int** CompactClouds(r[%d] -> newr[%d])\n", r, newr[0]);


	newParts = (int**)malloc(newr[0] * sizeof(int*));
	for (k = 0; k < newr[0]; k++) newParts[k] = (int*)malloc(2 * sizeof(int));

	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] >= 0)
		{
			newParts[kt][0] = ptsN[k][0];
			newParts[kt][1] = ptsN[k][1];
//			printf("[%d] %d  %d\n", kt, newParts[kt][0], newParts[kt][1]);
			kt = kt + 1;
		}
	}
	for (k = 0; k < r; k++) { free(ptsN[k]); ptsN[k] = NULL; }
	free(ptsN);

	return newParts;
}

void merge(int** ptsN, int k, int r)
{
	if (k < r)
	{
		ptsN[k + 1][0] = ptsN[k][0];
		ptsN[k][0] = -1; ptsN[k][1] = -1;
	}
	else
	{
		printf("last\n");
	}
	return;
}


double distMeasure(double x, double y)
{
	double d,er;
	d = abs(x - y);
	if (x > y) er = d / x; else er = d / y;
//	printf("measure %3.4f\n", er);
	return er;
}

double** formClouds(double ** A, int * rcA, int *rcClouds, double coupling)
{
	int ip=0,kmax,newrows;
	int** parts,**newParts;
	double** clouds,**cloudsNew;

	parts = getCloudPointers(A, rcA, &kmax);
	rcClouds[0] = kmax; rcClouds[1] = 6;
	clouds = pointers2clouds(parts, rcClouds,A, rcA);
//	newParts = CloseClouds(clouds, rcClouds, &newrows);
	newParts = CompactClouds(clouds, rcClouds,&newrows,coupling);
	if (newParts != NULL)
	{
		rcClouds[0] = newrows; rcClouds[1] = 6;
		cloudsNew = pointers2clouds(newParts, rcClouds, A, rcA);
		return cloudsNew;
	}
	else return clouds;
}

double** pointers2clouds(int** parts, int* rcClouds, double** A, int* rcA)
{
	double** clouds;
	double *tgtCluster;
	int s = 0, sOld = 0, e = 1, ePlus1 = 0, inPut = 0, kmax = 0, kt = 0;
	int k, i, ip = 0;
	double sigPk, muPk;
	int flagA;
	printf("!. double** pointers2clouds()\n");
	kmax = rcClouds[0];
	clouds = (double**)malloc(kmax * sizeof(double*));
	for (i = 0; i < kmax; i++) clouds[i] = (double*)malloc(rcClouds[1] * sizeof(double));

	for (ip = 0; ip < kmax; ip++)
	{
		s = parts[ip][0];   e = parts[ip][1];
		clouds[ip][0] = s;  clouds[ip][1] = e;
		ePlus1 = e + 1;

		tgtCluster = (double*)malloc(ePlus1 * sizeof(double));
		//	... first

		kt = 0;
//		printf("%d-X[%d].%d.%d \n", kmax, ip, s, ePlus1);
		for (k = s; k < ePlus1; k++)
		{
			tgtCluster[kt] = A[k][5];
//			printf("[%d]%3.4f ", kt, tgtCluster[kt]);
			kt++;
		}  // printf("...len %d\n", kt);
		flagA = stdMuLin(tgtCluster, &sigPk, &muPk, kt);

		if (flagA < 0)
		{
			for (k = 2; k < rcClouds[1]; k++) clouds[ip][k] = 0.0;
		}
		else { clouds[ip][2] = sigPk; clouds[ip][3] = muPk; }
		//	... second
		kt = 0;
//		printf("Y[%d].%d.%d \n", ip, s, ePlus1);
		for (k = s; k < ePlus1; k++)
		{
			tgtCluster[kt] = A[k][6];
//			printf("%3.4f ", tgtCluster[kt]);
			kt++;
		} // printf("....len %d\n", kt);
		flagA = stdMuLin(tgtCluster, &sigPk, &muPk, kt);
		if (flagA < 0) { for (k = 0; k < rcClouds[1]; k++) clouds[ip][k] = 0.0; }
		else
		{
			clouds[ip][4] = sigPk; clouds[ip][5] = muPk;
		}
		printf("%d data s.e[%d.%d]  \t", ip, (int)(clouds[ip][0]), (int)(clouds[ip][1]));
		printf("X stdMu[%3.4f.%3.4f] Y stdMu[%3.4f.%3.4f]\n", clouds[ip][2], clouds[ip][3], clouds[ip][4], clouds[ip][5]);

		free(tgtCluster);
	}
	return clouds;
}

void writeFile(int* rcDf, double** Df)
{
	int k, i,rows;
		if (MATLAB == 1) rows = rcDf[0] - 2; else rows = rcDf[0];
		for (i = 0; i < rows; i++)
		{
			if (PRINT_FLAG == 1) printf("%d ", i);
			for (k = 0; k < rcDf[1]; k++)
			{
				fprintf(fpSortCluster, "%3.4f ,", Df[i][k]);
				if (PRINT_FLAG == 1) printf("%3.4f ", Df[i][k]);
			}
			if (PRINT_FLAG == 1) printf("\n");  fprintf(fpSortCluster, "\n");

		} if (PRINT_FLAG == 1) printf("\n");  fprintf(fpSortCluster, "\n");
		if (PRINT_FLAG == 1) printf("pause at line 104 rdrImg.cpp\n");
		return;
}

void writeFileNconsole(int* rcClouds, double** clouds)
{
	int i, k,oldk=0,diff;

	for (i = 0; i < rcClouds[0]; i++)
	{
		diff = (int)(clouds[i][0]) - oldk;
		oldk = (int)(clouds[i][0]);
		if (diff == 1)
		{
			fprintf(fpClouds, "-1 ,");
			for (k = 1; k < rcClouds[1]; k++) fprintf(fpClouds, "0.0 ,");
			fprintf(fpClouds, "\n");
		}

		for (k = 0; k < rcClouds[1]; k++)
		{
			fprintf(fpClouds, "%3.4f ,", clouds[i][k]);
			printf("%3.4f ", clouds[i][k]);
		}   fprintf(fpClouds, "\n"); printf("\n");

	}

	return;
}

void TransferData
(
	int numberOfTgts,
	int* bins,
	double* rg,
	double* sAvg,
	double* doas,
	double* Mudoas,
	double** D,
	int k,
	int kmax
)
{
	int i;
	int static pt = 0;
	if (k == 0) pt = 0;
	for (i = 0; i < numberOfTgts; i++)
	{
		D[pt][0] = (double)(i); 
		D[pt][1] = rg[i]; 
		D[pt][2] = sAvg[bins[i]];
		D[pt][3] = doas[i]; 
		D[pt][4] = Mudoas[i]; 
		pt = pt + 1;
	}
//	printf("at line 96 myRdr.cpp %d[%d]\n",k,kmax); getchar();
	return;
}
