#include "stdafx.h" // THIS IS A MUST
#include "detect.h"
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
//#include "mex.h"   /* This one is required */
int detectBins(double *sAvg, double *config, int *bins)
{
	printf("!. double detectBins\n");
	sort detectedBins;
	double *JkClOcal,*pK,max;
	int km,k, numOfPeaks,num,rc[2];
	int numberOfTgts,*Peaks,*peaks;
	double threshold,Lo,Hi;
	numberOfTgts = (int)(config[4]);
	rc[0] = (int)(config[7]); rc[1] = 8;
//	..................................................................
	JkClOcal = myAlloc(rc[0]);  Peaks = myAllocI(rc[0]);
	pK = myAlloc(numberOfTgts); peaks = myAllocI(numberOfTgts);
//	..................................................................
	km = myMax(sAvg, rc[0]); max = sAvg[km];
	for (k = 0; k < rc[0]; k++) 
	{ 
		JkClOcal[k] = sAvg[k] / max; sAvg[k] = JkClOcal[k]; 
//		printf("%d %3.4f\n", k, sAvg[k]);
	}
	numOfPeaks = findPeaks(rc[0], &num, Peaks, JkClOcal);
	printf("!. Number of Peaks %d\n", numOfPeaks);
	if (numOfPeaks < 0)
	{
		printf("!. There is NO Spectral peak I am exiting to main %d\n", numOfPeaks);
		free(JkClOcal); free(Peaks);
		free(peaks); free(pK);
//		myPrintf(JkClOcal, N, 8); getchar();
		return -1;
	} // else 	printf("!. after finding %d peaks top %d peaks are \n", numOfPeaks,numberOfTgts);


	if (numberOfTgts < numOfPeaks) { for (k = 0; k < numberOfTgts; k++) pK[k] = Peaks[k]; }
	else
	{
		printf("!. Spectral peaks %d are less than targets %d exiting to main\n", numOfPeaks, numberOfTgts);
		config[4] = numOfPeaks;
		free(JkClOcal); free(Peaks);
		free(peaks); free(pK);
		return numOfPeaks;
	}
	for (k = 0; k < numberOfTgts; k++)
	{
		peaks[k] = (int)(pK[k]);
//		printf("   peaks %d %3.4f[%3.4f]\n", peaks[k], JkClOcal[peaks[k]], sAvg[peaks[k]]);
	}
	Lo = JkClOcal[peaks[numberOfTgts - 1]]; Hi = JkClOcal[peaks[0]];
//	printf("Low and High Peaks %3.4f %3.4f\n", Lo, Hi);
	threshold = Lo / Hi;
	detectedBins.x = pK; detectedBins.xI = Peaks; detectedBins.M = numberOfTgts;
	detectedBins.Low2High();
//	detectedBins.showx();	
	for (k = 0; k < numberOfTgts; k++) bins[k] = (int)(pK[k]);
//	........... Free Memory ..........................................
	free(JkClOcal); free(Peaks);
	free(peaks); free(pK);

	return numberOfTgts;
}

int findPeaks
(
	int N,
	int *num,
	int *peaks,
	double *Jk
)
{
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
//  updated 11th Nov 2022   Dr Kaluri Reserach House.
//	printf("8. findPeaks(pM[%d],&num,peaks,JkC,fnC,PhsC,x);\n", N);
//	FN = (double *)malloc(N * sizeof(double));
//	printf("int findPeaks\n");
	sort objectivefunction;
	double JkSlp = 0.0F, oldJk = 0.0F;
	double pi = (double)atan(1.0)*4.0F;
	double p = 0.0, *peak;
	int i=0, k, oldM = 0, *peakI, indx = 0;
	int offset = 6;
	int slpUp = 0, slpDn = 0,pkYes = 0,pkFlag=0;
	double Jk1 = 0, Jk2 = 0, Jk3 = 0;
	peak = myAlloc(N); peakI = myAllocI(N);
	//peak = (double*)malloc(N * sizeof(double));
	//peakI = (int*)malloc(N * sizeof(int));
	i = 0;
	for (k = 0; k < N; k++)
	{
		Jk1 = Jk2; Jk2 = Jk3; Jk3 = Jk[k];
		if ((Jk2 - Jk1) > 0) slpUp = 1; else slpUp = 0;
		if ((Jk2 - Jk3) > 0) slpDn = 1; else slpDn = 0;
		pkYes = slpUp + slpDn;
		switch (pkYes)
		{
			case 2: 
				peak[i] = Jk2; peakI[i] = k-1; 
				if ( (k - 1) > 0 )  i = i + 1;
			break;

			default:
			break;
		}
	}
	if (i == 0) 
	{ 
		free(peak); free(peakI);
		num[0] = i;
		return -1; 
	}
	num[0] = i;

//	for (k = 0; k < num[0]; k++) printf("%d %d %3.4f\n", k, peakI[k], peak[k]); 
//	for (k = 0; k < num[0]; k++) { peaks[k] = peakI[k]; Pk[k] = Jk[peaks[k]]; }
//	else printf("!. Number of Peaks %d \n", i);
	objectivefunction.x = peak; objectivefunction.xI = peakI; objectivefunction.M = i;
	objectivefunction.High2Low();
//	objectivefunction.showx(); 
	for (k = 0; k < num[0]; k++) 
	{
		peaks[k] = peakI[k]; // printf("%d %3.4f\n", peaks[k],Jk[peaks[k]]);
	}
	for (k = num[0]; k < N; k++) { peaks[k] = 0; }
//	Free memory
	free(peak); free(peakI);
	return i;
}
