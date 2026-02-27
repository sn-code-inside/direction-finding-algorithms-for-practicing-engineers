#include "stdafx.h"
#include "myRdrClusters.h"
//#include "mex.h"   
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
double** processRdr(int blocks, char* datafile, double* config, double** D, int* rcD, int *rcSene)
{
	char* fileCloud{}, * fileTemp{};
	int k = 0, kmax;
	int fileOpen = -1;
	int i, j;
	double rgain = 0, bins2range = 1.0;
	int numberOfTgts;// numOfPhaseSpecSamples;
	int maxBlocks, ktCluster = 0;// er;
	static int kt = 0; // this is a must
	double** Df{}, ** clouds{}, ** cluster{};
	double** packD;
	int s, e, DfMaxValidRows = 1;
	double** Scene{};
	int MaxNumOfRowsCluster = 1000;
	int FFTsamples, NumOfColumns, cby2;
	double closeNessFactor = 0.05;
	int rc[2];
	int rows, cols, rcDf[2], rcClouds[2];
	//	int rcD[2];

	numberOfTgts = (int)(config[4]);
	kmax = (int)(config[6]);
	FFTsamples = (int)(config[7]);
	rgain = config[11];
	NumOfColumns = (int)(config[13]);
	maxBlocks = (int)(config[14]); // added on 24th Jul 2023

	rc[0] = FFTsamples; rc[1] = NumOfColumns; 	cby2 = rc[1] / 2;
	cols = 5; rows = kmax * numberOfTgts;
	ktCluster = 0;

	Df = sortCluster(D, rows, cols, numberOfTgts, rcDf, config);
	printf("!.[%d] size of sorted validated matrix [%d by %d]\n", blocks, rcDf[0], rcDf[1]);

	clouds = formClouds(Df, rcDf, rcClouds, closeNessFactor);
	
	printf("!.[%d] compacted to clouds [%d by %d]\n", blocks, rcClouds[0], rcClouds[1]);
	cluster = clouds2cluster(rcClouds, clouds, MaxNumOfRowsCluster, &ktCluster);
	rcSene[0] = ktCluster; rcSene[1] = 4;
	Scene = createSceneMatrix(rcSene, cluster);
	writeScene(Scene, ktCluster);
	packD = myAlloc2(rcDf[0], rcDf[1] - 1);
	for (i = 0; i < rcDf[0]; i++)
	{
		packD[i][2] = Df[i][1]; // range
		packD[i][3] = Df[i][3]; // doak
		packD[i][4] = Df[i][5]; // x
		packD[i][5] = Df[i][6]; // y
	}
	//printf("!. Chi integer pointer matrix\n");
	for (i = 0; i < rcClouds[0]; i++)
	{
		s = (int)(clouds[i][0]);  e = (int)(clouds[i][1]);
		for (j = s; j < e + 1; j++)
		{
			packD[j][0] = Scene[i][0]; packD[j][1] = Scene[i][1];
		}
		//printf("%d\t%d\n", s, e);
	}
	j = 0;
	DfMaxValidRows = (int)(clouds[rcClouds[0] - 1][1]) + 1;
	printf("!. Cloud Data after Validation Rows %d\n", DfMaxValidRows);
	for (i = 0; i < DfMaxValidRows; i++)
	{
		e = (int)(clouds[j][1]); s = (int)(clouds[j][0]);
		if (s == i) 
		{ 
			printf("\tstart %d end %d\n", s, e); 
			printf("mean(r)\tmean(phi)\tr\tphi\tx\ty\n");
		}
		printf("%3.4f\t", packD[i][0]);
		printf("%3.4f\t", packD[i][1]);
		printf("\t%3.4f\t", packD[i][2]);
		printf("%3.4f\t", packD[i][3]);
		printf("\t%3.4f\t", packD[i][4]); 
		printf("%3.4f", packD[i][5]);
		//		if (e == i) { printf("----->%d\n", e); j = j + 1; }
		if (e == i) { printf("\n"); j = j + 1; }
		printf("\n");
	}
	writeFile(rcDf, Df);
	myFree2(Df, rcDf[0]);
	if (blocks < maxBlocks) return Scene;
	else return NULL;
}

double** formClouds(double** A, int* rcA, int* rcClouds, double coupling)
{
	int ip = 0, kmax, newrows;
	int** parts, ** newParts;
	double** clouds, ** cloudsNew;

	parts = getCloudPointers(A, rcA, &kmax);
	rcClouds[0] = kmax; rcClouds[1] = 6;
	clouds = pointers2clouds(parts, rcClouds, A, rcA);
	//	newParts = CloseClouds(clouds, rcClouds, &newrows);
	newParts = CompactClouds(clouds, rcClouds, &newrows, coupling);
	if (newParts != NULL)
	{
		rcClouds[0] = newrows; rcClouds[1] = 6;
		cloudsNew = pointers2clouds(newParts, rcClouds, A, rcA);
		return cloudsNew;
	}
	else
	{
		return clouds;
	}
}

int** getCloudPointers(double** A, int* rcA, int* kmax)
{
	int** parts,i,M;
	int maximumNumOfPartions = 15;
	double* range{};
	M = rcA[0] - 3;
	range = (double*)malloc(M * sizeof(double));

	for (i = 0; i < M; i++) range[i] = A[i][1];
	parts = getCloudTotalPt(range, M, maximumNumOfPartions, kmax);

	free(range);
	return parts;
}


int** CompactClouds(double** clouds, int* rcClouds, int* newr, double coupling)
{
	double* muk{}, er;
	int s, e;
	double x, y;
	int k, r, c, kt, flag = 0;
	int** ptsN{}, ** newParts{};

	r = rcClouds[0]; c = rcClouds[1];
//	printf("----------->Compact rows %d cols %d\n", r, c);
	muk = myAlloc(r);
	//	muk = (double*)malloc(r * sizeof(double));
	ptsN = myAlloc2I(r, 2);

	//	ptsN = (int**)malloc(r * sizeof(int*));
	//	for (k = 0; k < r; k++) ptsN[k] = (int*)malloc(2 * sizeof(int));

	for (k = 0; k < r; k++)
	{
		s = (int)(clouds[k][0]); e = (int)(clouds[k][1]);
		x = clouds[k][3]; y = clouds[k][5];

		ptsN[k][0] = s; ptsN[k][1] = e;
		muk[k] = sqrt(x * x + y * y);
//		printf("!.[%d] %d - %d - distance %3.4f\n", k,s, e,muk[k]);
	}
	//	kt = 0;
	flag = 1;
	for (k = 0; k < r-1; k++) // one more fine bug earlier it was r
	{
		er = distMeasure(muk[k], muk[k + 1]);
		if (er < coupling)  // important parameter
		{
			merge(ptsN, k, r);
			flag = -1;
		}
		else kt = 0;
//		printf("[%d] (%d %d).%d\n", k, ptsN[k][0], ptsN[k][1], kt);
	}
	if (flag > 0)
	{
		myFree2I(ptsN, r); free(muk);
		return NULL;
	}
	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] < 0) kt = kt + 1;
	}
	newr[0] = r - kt;
//	printf("!. int** CompactClouds(r[%d] -> newr[%d])\n", r, newr[0]);


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
	myFree2I(ptsN, r); free(muk);
	//	for (k = 0; k < r; k++) { free(ptsN[k]); ptsN[k] = NULL; }
	//	free(ptsN);

	return newParts;
}


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
	{
		if (tgts[k] < 0)
		{
			//			printf("!. range threshold %3.4f [%d reduced to %d rows]\n", rThold, kmax, k);
			kmax = k;
			break;
		}
	}
	//	bins.showx(); 
	newCols = cols + 2; Kmax = kmax + 2;
	//A = (double**)malloc(Kmax * sizeof(double*));
	//for (i = 0; i < Kmax; i++) A[i] = (double*)malloc(newCols * sizeof(double));

	rcA[0] = Kmax; rcA[1] = newCols;
	A = myAlloc2(rcA[0], rcA[1]);

	rc[0] = Kmax; rc[1] = newCols;
	rgain = config[11]; maxBin = config[7];
	bins2range = (rgain / maxBin);
	printf("!. No of Chirps %d and Max Targets %d\n", (int)(config[6]), (int)(config[4]));
	printf("!. sortCluster() ->size [%d by %d] bin-gain %3.4f m/bin\n", Kmax, newCols, bins2range);
	printf("!. range gain %3.4f max no of bins %3.4f\n", rgain, maxBin);
	//	Creating two additional columns of X = r.cos(theta) and Y = r.sin(theta)
	for (i = 0; i < kmax; i++)
	{
		for (k = 0; k < cols; k++)
		{
			pt = ind[i]; A[i][k] = D[pt][k];
		}
//		A[i][1] = A[i][1] * bins2range;
		A[i][1] = A[i][1] * rgain; // updated on 29th Jun 2023 @ Dublin Ohio
		r = A[i][1]; theta = A[i][3] * pi / 180.0f;
		A[i][cols + 1] = r * cos(theta); A[i][cols] = r * sin(theta);
	}
	lastRow = i;
	for (k = 0; k < cols; k++) A[lastRow - 1][k] = 0.0;

	for (k = 0; k < cols; k++) A[lastRow][k] = 0.0;
	A[lastRow][cols] = 0.5f * rgain; A[lastRow][cols + 1] = rgain;

	for (k = 0; k < cols; k++) A[lastRow + 1][k] = 0.0;
	A[lastRow + 1][cols] = -0.5 * rgain; A[lastRow + 1][cols + 1] = rgain;
	return A;
}




void pause(int dur)
{
//	pause in dur seconds
	int temp = (int)(time(NULL)) + dur;
	while (temp > time(NULL));
	return;
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


double** pointers2clouds(int** parts, int* rcClouds, double** A, int* rcA)
{
	double** clouds;
	double* x,*y,*r;
	int s = 0, sOld = 0, e = 1, ePlus1 = 0, inPut = 0, kmax = 0, kt = 0;
	int k, i, ip = 0;
	double* stdmu;

	int flag;
	stdmu = (double*)malloc(2 * sizeof(double));

//	printf("!. double** pointers2clouds()\n");
	x = (double*)malloc(rcA[0] * sizeof(double));
	y = (double*)malloc(rcA[0] * sizeof(double));
	r = (double*)malloc(rcA[0] * sizeof(double));
	kmax = rcClouds[0];
	clouds = (double**)malloc(kmax * sizeof(double*));
	for (i = 0; i < kmax; i++) clouds[i] = (double*)malloc(rcClouds[1] * sizeof(double));
	for (k = 0; k < rcA[0]; k++) { x[k] = A[k][5]; y[k] = A[k][6]; r[k] = A[k][1]; }

	for (ip = 0; ip < kmax; ip++)
	{
		s = parts[ip][0];   e = parts[ip][1];
		clouds[ip][0] = s;  clouds[ip][1] = e;
//	... check for r
//		flag = lineCluster(s, e, r, rcA[0], stdmu);
//		for (k = s; k < e; k++) printf("%3.4f ", r[k]); printf("\n");
//		printf("[%d:%d] -> sigr %3.4f meanr %3.4f\n", s,e,stdmu[0], stdmu[1]);
// 	... first X
		flag = lineCluster(s, e, x, rcA[0], stdmu);
		if (flag < 0)
		{
			for (k = 2; k < rcClouds[1]; k++) clouds[ip][k] = 0.0;
		}
		else { clouds[ip][2] = stdmu[0]; clouds[ip][3] = stdmu[1]; }
//	... second Y
		flag = lineCluster(s, e, y, rcA[0], stdmu);
		if (flag < 0)
		{
			for (k = 2; k < rcClouds[1]; k++) clouds[ip][k] = 0.0;
		}
		else { clouds[ip][4] = stdmu[0]; clouds[ip][5] = stdmu[1]; }

//		printf("%d data s.e[%d.%d]\t", ip, (int)(clouds[ip][0]), (int)(clouds[ip][1])); 
//		printf("X stdMu[%3.4f.%3.4f]\t Y stdMu[%3.4f.%3.4f]\n", clouds[ip][2], clouds[ip][3], clouds[ip][4], clouds[ip][5]);
		if (flag < 0) rcClouds[0] = rcClouds[0] - 1; // new bug
	}
	free(x); free(y); free(stdmu); free(r);
	return clouds;
}


double** createSceneMatrix(int *rcSene, double** cluster)
{
	int k,ktCluster,cols;
	double xmu, ymu, delx, dely, rad2deg, pi;
	double** Scene;
	ktCluster = rcSene[0]; cols = rcSene[1];
	Scene = myAlloc2(ktCluster, cols);
	pi = atan(1.0) * 4.0; rad2deg = 180.0 / pi;
	printf("!. Scene Matrix\n");
	for (k = 0; k < ktCluster; k++)
	{
		xmu = cluster[k][4]; ymu = cluster[k][6];
		delx = cluster[k][3]; dely = cluster[k][5];
		Scene[k][0] = sqrt(xmu * xmu + ymu * ymu);
		Scene[k][1] = atan(xmu / ymu) * rad2deg;
		Scene[k][2] = sqrt(delx * delx + dely * dely);
		if (isnan(Scene[k][2])) Scene[k][2] = 0.0;
		Scene[k][3] = atan(delx / dely) * rad2deg;
		if (isnan(Scene[k][3])) Scene[k][3] = 0.0;
	}
	return Scene;
}

double** clouds2cluster(int* rcClouds, double** clouds, int MaxNumOfRowsCluster, int* kt)
{
	int k, i, ip, ktCluster;
	double** cluster;
	cluster = myAlloc2(MaxNumOfRowsCluster, rcClouds[1] + 1);
	ktCluster = kt[0];
	printf("!. integer matrix chi with pointers\n");
	for (k = 0; k < rcClouds[0]; k++)
	{
		cluster[ktCluster][0] = k;
		for (i = 0; i < rcClouds[1]; i++)
		{
			cluster[ktCluster][i + 1] = clouds[k][i];
		}
		for (ip = 1; ip < rcClouds[1] - 3; ip++) printf("%d\t", (int)(cluster[ktCluster][ip]));
		printf("\n");
		ktCluster = ktCluster + 1; kt[0] = ktCluster;
		if (ktCluster > MaxNumOfRowsCluster) break;
	}
	return cluster;
}

