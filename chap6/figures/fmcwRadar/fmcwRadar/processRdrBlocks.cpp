// iRdrFootPrint.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 23rdth Jul 2023 11am @ Dublin .. kaluri@ieee.org
// started a fresh from iRdrFootPrint.cpp for timing
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
#include "stdafx.h"
#include "processRdrBlocks.h"
//#include "mex.h"   // this is required

double** getLooksData(double *config, char * datafile, int blocks,int *rcD)
{
	static int kt = 0;
	int k=0, er, indx,fileOpen;
	int numberOfTgts, FFTsamples, NumOfColumns, numOfPhaseSpecSamples,cby2;
	int NumberOfTgts;
	int rc[2], zerofill = 8,kmax,cols,rows,d,r,m;
	int* bins;
	complex** A, ** S, ** steering, ** En{};
	double* sAvg{}, ** rgMat{}, * sg{}, * rg{};
	double fromDoa, DoaKmu, * doas{}, * Mudoas{}, ** phSpk{}, ** muSpk{};
	double fn, sPeak, threshold;
	static double** D{};

	printf("!. double** getLooksData()\n");
//	config[4] = (double)(numberOfTgts); // this is to take care changing detecetd peaks
	numberOfTgts = (int)(config[4]); NumberOfTgts = (int)(config[4]);
	FFTsamples = (int)(config[7]);
	NumOfColumns = (int)(config[13]);
	rc[0] = FFTsamples; rc[1] = NumOfColumns; 	cby2 = rc[1] / 2;
	numOfPhaseSpecSamples = (int)(config[5]);
	threshold = config[12]; kmax = (int)(config[6]);
	cols = 5; rows = kmax * numberOfTgts;
	rcD[0] = rows; rcD[1] = cols;
	if (blocks == 0)
	{
		D = myAlloc2(rows, cols);
		kt = 0; // 25th May 2025 @ Dublin Ohio
	}

	printf("_______________________%d_______________________\n",blocks);
	printf("!. Allocate Memory\n");

	A = myAlloc2Complex(FFTsamples, cby2);
	S = myAlloc2Complex(FFTsamples, cby2);
	steering = myAlloc2Complex(numberOfTgts, cby2);
	sAvg = myAlloc(FFTsamples);

	rgMat = myAlloc2(numberOfTgts, cby2);
	doas = myAlloc(numberOfTgts);
	sg = myAlloc(numberOfTgts);
	phSpk = myAlloc2(numberOfTgts, numOfPhaseSpecSamples);
	doas = myAlloc(numberOfTgts);
	Mudoas = myAlloc(numberOfTgts);
	muSpk = myAlloc2(numberOfTgts, numOfPhaseSpecSamples);
	bins = myAllocI(numberOfTgts);
	d = 2; // updated on 30th Apr 2024
	r = cby2 - d; if (r < 1) { printf("issue in number of D %d %d\n", cby2, d); r = 1; }
	m = r * numberOfTgts;
	En = myAlloc2Complex(m, cby2);


	for (k = 0; k < kmax; k++)
	{
		printf("!. Chirp %d Matrix Count %d\n", k, kt);
		er = createA(A, datafile, config, kt);
		if (er < 0)
		{
			printf("!. File Read Error ----->%d\n", er);
			config[0] = -1.0;
//			fclose(fp); 
			return NULL;
		}
		kt = kt + 1;
		preProc(A, S, sAvg, config, zerofill);
		numberOfTgts = detectBins(sAvg, config, bins); config[4] = numberOfTgts;
		if (numberOfTgts < 0)
		{
			printf("!. Data Problem No Peaks %d blocks %d matrix %d\n", numberOfTgts,blocks,kt);
			fclose(fp);
			myFree2Complex(A, rc[0]);
			myFree2Complex(S, rc[0]);
			myFree2Complex(steering, numberOfTgts);

			myFree2(rgMat, numberOfTgts);
			myFree2(phSpk, numberOfTgts);
			myFree2(muSpk, numberOfTgts);

			myFree(sAvg); free(bins);
			myFree(sg); myFree(Mudoas);
			myFree(rg); myFree(doas);
			return NULL;
		}

		rg = rgSteering(A, config, bins, rgMat, sg, steering);
		DoaKmu = kMusic(S, steering, doas, config, phSpk);


		fromDoa = easyMusic(S, bins, config, Mudoas, muSpk,En,d);
//		printf("rows %d..................\n",m);
//		printComplxMatrix(En, m, cby2); printf("cols %d---------------->\n",cby2);

		printf("!. %d Target peaks > %3.4f\n", numberOfTgts, threshold);
		for (indx = 0; indx < numberOfTgts; indx++)
		{
			fn = (double)(bins[indx]) / (double)(FFTsamples);
			sPeak = sAvg[bins[indx]];
			if (sPeak > threshold)
			{
				fprintf(fpKMUandGmu, "%3.4f, % 3.4f, % 3.4f, % 3.4f\n", fn, Mudoas[indx], rg[indx], doas[indx]);
				printf("  [%d] fn %3.4f\t muDoa %3.4f\t kMuFn %3.4f\t kMuDoa %3.4f\n", indx, fn, Mudoas[indx], rg[indx], doas[indx]);
			}
		}

		TransferData(numberOfTgts, bins, rg, sAvg, doas, Mudoas, D, k, kmax);

		fileOpen = capture(blocks, 2, k);
		if (fileOpen > 0) traceData(sAvg, phSpk, muSpk, rc[0], numberOfTgts, numOfPhaseSpecSamples);
		config[4] = (double)(NumberOfTgts); // this is to take care changing detecetd peaks
	}

//	printf("!. r and DOA time (%d)\n\n", k);
//	printf("!.[%d] Data Complex Matrix A[%d] read from %s of size %d by %d\n", blocks, k, datafile, rc[0], cby2);
	printf("!.[%d] indx[0] r[1] q[2] doak[3] doamu[4] x[5] y[6] data over %d chirps size [%d by %d]\n", blocks, k, rows, cols + 2);
	writeFileUnsort(rcD, D, config);

	myFree2Complex(A, rc[0]);
	myFree2Complex(S, rc[0]);
	myFree2Complex(steering, numberOfTgts);
	myFree2Complex(En, m);

	myFree2(rgMat, numberOfTgts);
	myFree2(phSpk, numberOfTgts);
	myFree2(muSpk, numberOfTgts);

	myFree(sAvg); free(bins);
	myFree(sg); myFree(Mudoas);
	myFree(rg); myFree(doas);
	printf("!. Free memory after [%d] chirps and look[%d]\n", k, blocks);
	printf("______________________________________________\n");
	return D;
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
//		D[pt][1] = (double)(bins[i]);
		D[pt][2] = sAvg[bins[i]];
//		D[pt][3] = doas[i];
		D[pt][3] = -doas[i]; // sign issue fixed on 26th Jul 2023 Dublin
		D[pt][4] = Mudoas[i]; pt = pt + 1;
	}
	printf("[%d] at line 162 TransferData() processRdrBlocks.cpp [%d]\n",k,kmax); 
	//getchar();
	return;
}



