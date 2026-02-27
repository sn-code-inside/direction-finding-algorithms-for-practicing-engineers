#include "stdafx.h"
#include "PitchClouds.h"
//#include "mex.h"   // This one is required 
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
double** processWav
(
	int N, 
	int numberOfPeaksInBins,
//	int k, 
	double *un,
	double *x,
	complex *z,
	int *bins,
	int *pitchRows
)
{
	int maxLengthOfFileName = 20;
	int M,Nby2, i;
	static int maxDataValues, HeaderSize;
	static double* audio{};
	int rows = 3;
	int maxBinPeaks = 1, binsN;
	double* config, threshold = 0.2;
	//int pitchClusterRows;
	double** PitchTable;
	config = myAlloc(20);
	Nby2 = N / 2; M = (int)(log(N) / log(2));
	config[7] = Nby2; config[4] = numberOfPeaksInBins;

	for (i = 0; i < N; i++) { z[i].r = un[i]; z[i].i = 0.0; }

	sampleSpek(z, x, N, M);
	binsN = detectPeakPeaks(x, config, bins);
	if (binsN < 0)
	{
		pitchRows[0] = (int)(config[4]);
		printf("!. Detection of peaks problem\n");
		return NULL;
	}

	printf("!. Asked peaks %d actual peaks %d\n", numberOfPeaksInBins, binsN);
	if (binsN != numberOfPeaksInBins) numberOfPeaksInBins = binsN;

    pitchRows[0] = binsN;
    PitchTable =  myAlloc2(pitchRows[0], 3);
    for (i = 0; i < binsN; i++)
    {
        PitchTable[i][0] = i;
        PitchTable[i][1] = bins[i];
		PitchTable[i][2] = x[ bins[i] ];
    }
	return PitchTable;
}

int* wavBins(int numberOfPeaksInBins,int N,double *un,double *config)
{
	int Nby2,M,i,binsN,*bins,erFlag;
	complex* z{};
	double* x;
	z = myAllocComplex(N); x = myAlloc(N);
	bins = myAllocI(N);

	Nby2 = N / 2; M = (int)(log(N) / log(2));
	config[7] = Nby2; config[4] = numberOfPeaksInBins;

	for (i = 0; i < N; i++) { z[i].r = un[i]; z[i].i = 0.0; }

	sampleSpek(z, x, N, M);
	binsN = detectPeakPeaks(x, config, bins);
//	binsN = detectBins(x, config, bins); //binsN = (int)(threshold);
	if (binsN < 0)
	{
		erFlag = (int)(config[4]);
		printf("!. Detection of peaks problem\n");
		return NULL;
	}

	printf("!. Asked peaks %d actual peaks %d\n", numberOfPeaksInBins, binsN);
	if (binsN != numberOfPeaksInBins) numberOfPeaksInBins = binsN;
	for (i = 0; i < binsN; i++) printf("[%d] bin value at %d = %3.4f\n", i, bins[i],x[bins[i]]);
	getchar();
	return bins;
}

double ** pitchClusters(int N, double *x,int numberOfPeaks, int *bins, int *pitchClusterRows)
{
    int *pitchFreqInd,**pitchClouds;
	int m, i, s, e, lenP, ind, pt, er;
    double* pitchFreqPiece, * pitchValue;
    double* pitchFreq, stdMu[2], * muk{}, delN;
	double** PitchTable;

    pitchFreq = myAlloc(numberOfPeaks);
	pitchFreqInd = (int*)malloc(numberOfPeaks * sizeof(int));
    delN = 1.0/(double)(N);

	for (i = 0; i < numberOfPeaks; i++) pitchFreq[i] = (double)(bins[i]) / (double)(N);

	pitchFreqInd = Low2High(numberOfPeaks, pitchFreq);
	pitchClouds = getCloudPointers(pitchFreq, numberOfPeaks, pitchClusterRows,N);
	muk = myAlloc(pitchClusterRows[0]);

	for (i = 0; i < pitchClusterRows[0]; i++)
	{
		s = pitchClouds[i][0]; e = pitchClouds[i][1];
		pitchFreqPiece = lineCluster(s, e, pitchFreq, numberOfPeaks, stdMu); 
		if (pitchFreqPiece == NULL)  return NULL; 
		muk[i] = stdMu[1];
	}
	er = CompactPitch(muk, pitchClouds, pitchClusterRows, 10*delN);
	PitchTable =  myAlloc2(pitchClusterRows[0], 5);
	for (i = 0; i < pitchClusterRows[0]; i++)
	{
		s = pitchClouds[i][0]; e = pitchClouds[i][1]; lenP = e - s + 1;
		pitchFreqPiece = lineCluster(s, e, pitchFreq, numberOfPeaks, stdMu); 
		if (pitchFreqPiece == NULL)  return NULL; 
		muk[i] = stdMu[1];
		pitchValue = myAlloc(lenP);

		for (ind = 0; ind < lenP; ind++)
		{
			m = pitchFreqInd[ind + s]; pitchValue[ind] = x[bins[m]];
		}
		pt = myMax(pitchValue, lenP);
		er = stdMuLin(pitchValue, &stdMu[0], &stdMu[1], lenP);
        PitchTable[i][0] = (int)(pitchFreq[s]*N);
        PitchTable[i][1] = (int)(pitchFreq[e]*N);
		PitchTable[i][2] = (int)(pitchFreqPiece[pt]*N);
		PitchTable[i][3] = pitchValue[pt];
		PitchTable[i][4] = stdMu[0];
	}
    return PitchTable;
}


int CompactPitch(double* mean, int** parts, int* rows, double coupling)
{
	double er;
	int newr;
//	double x;
	int k, r, c, kt, flag = 0;
	int** ptsN, ** newParts;

	r = rows[0]; c = 2; newr = 1;
	//muk = (double*)malloc(r * sizeof(double));

	ptsN = (int**)malloc(r * sizeof(int*));
	for (k = 0; k < r; k++) ptsN[k] = (int*)malloc(2 * sizeof(int));

	for (k = 0; k < r; k++) { ptsN[k][0] = parts[k][0]; ptsN[k][1] = parts[k][1]; }
//	{
//		s = parts[k][0]; e = parts[k][1];
//		x = mean[k];

//		ptsN[k][0] = s; ptsN[k][1] = e;
//		muk[k] = mean[k];
//	}
	kt = 0;
	flag = 1;
	for (k = 0; k < r; k++)
	{
		er = distMeasurePitch(mean[k], mean[k + 1]);
//        printf("%d %3.4f -- %3.4f\n",k,er,coupling);
		if (er < coupling)  // important parameter
		{
			mergePitch(ptsN, k, r);
			flag = -1;
		}
		else kt = 0;
//		printf("[%d] (%d %d).%d\n", k, ptsN[k][0], ptsN[k][1],kt);
	}
	if (flag > 0) 
	{ 
		printf("!. NO COMPACTION\n");
		return flag; 
	}

	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] < 0) kt = kt + 1;
	}
	newr = r - kt;
	printf("!. int** CompactPitch(r[%d] -> newr[%d])\n", r, newr);


	newParts = (int**)malloc(newr * sizeof(int*));
	for (k = 0; k < newr; k++) newParts[k] = (int*)malloc(2 * sizeof(int));

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
	for (k = 0; k < newr; k++)
	{
		parts[k][0] = newParts[k][0];
		parts[k][1] = newParts[k][1];
	}
	rows[0] = newr;
	return flag;
}

void mergePitch(int** ptsN, int k, int r)
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


double distMeasurePitch(double x, double y)
{
	double d, er;
	d = fabs(x - y);
	if (x > y) er = d / x; else er = d / y;
	//	printf("(%3.4f %3.4f) measure %3.4f\n", x,y,er);
	return er;
}
