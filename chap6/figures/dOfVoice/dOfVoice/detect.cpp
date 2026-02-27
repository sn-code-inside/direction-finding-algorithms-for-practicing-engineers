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
//#include "cMath.h"
int detectBins(double *sAvg, double *config, int *bins)
{
//	printf("double detectBins\n");
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
		for (k = 0; k < numOfPeaks; k++) bins[k] = Peaks[k];
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
//  Copy Right Protected  written by Prof Kaluri
//  updated 11th Nov 2022   .
//	printf("8. findPeaks(pM[%d],&num,peaks,JkC,fnC,PhsC,x);\n", N);
//	FN = (double *)malloc(N * sizeof(double));
	if (PRINT_FLAG == 1) printf("int findPeaks\n");
	sort objectivefunction;
	double JkSlp = 0.0, oldJk = 0.0;
	double pi = (double)atan(1.0)*4.0;
	double p = 0.0, *peak;
	int i=0, k, oldM = 0, *peakI, indx = 0;
	int offset = 6;
	int slpUp = 0, slpDn = 0,pkYes = 0,pkFlag=0;
	double Jk1 = 0, Jk2 = 0, Jk3 = 0;
	peak = (double*)malloc(N * sizeof(double));
	peakI = (int*)malloc(N * sizeof(int));
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

int detectPeakPeaks(double* x, double* config, int* bins)
{
	double  * peaksX{}, * binsX{};
	int* newBins{};
	int binsN, * pitchFreqInd{};
	int i, indx, pt,ptr=0,flag, binsNew = 1, numberOfPeaksofPeaks, temp;
	double** PkpkData{};
	//double sig,mu;
	int N;

	N = (int)(config[7]);
	/*   er = stdMuLin(x, &sig, &mu, N);
	   if ( er < 0 )
	   {
		   printf("!. NO wav energy\n");
		   config[4] = -1.0;
		   return er;
	   }*/

	numberOfPeaksofPeaks = (int)(config[4]);
	binsN = detectBins(x, config, bins); //binsN = (int)(threshold);
	printf("!. First Peaks: Number of Peaks --->%d\n", binsN);
//	for (i = 0; i < binsN; i++) printf("%d %d\t%3.4f\n",i,bins[i],x[ bins[i] ]);
//	getchar();
	if (binsN > 0)
	{
//		pitchFreqInd = (int*)malloc(binsN * sizeof(int));
//		newBins = (int*)malloc(binsN * sizeof(int));
		pitchFreqInd = myAllocI(binsN + 1);
		peaksX = myAlloc(binsN+1); binsX = myAlloc(binsN+1);
		newBins = myAllocI(binsN + 1);

		for (i = 0; i < binsN; i++) binsX[i] = bins[i];
		pitchFreqInd = Low2High(binsN, binsX);

		for (i = 0; i < binsN; i++)
		{
			indx = (int)(binsX[i]);
			peaksX[i] = x[indx];
//			printf("%d %d %3.4f\n", i, indx, peaksX[i]);
		}
		config[7] = binsN; //config[4] = numberOfPeaksofPeaks;
		binsNew = detectBins(peaksX, config, newBins); //binsNew = (int)(threshold);
		printf("!. Second Peaks of Peaks: Number of Peaks Peaks --->%d\n", binsNew);

		if (binsNew < 0)
		{
			printf("!. NO PEAKS of peaks using only peaks (%d)->%d\n", binsNew, binsN);
			for (i = 0; i < binsN; i++) newBins[i] = bins[i];
			free(pitchFreqInd); free(peaksX); free(binsX); free(newBins);
			return binsN;
		}
		PkpkData = myAlloc2(binsNew, 7);
		for (i = 0; i < binsNew; i++)
		{
			pt = newBins[i]; 
			ptr = bins[i];
			indx = (int)(binsX[pt]);
			PkpkData[i][0] = i;
			PkpkData[i][1] = bins[i];
			PkpkData[i][2] = indx;
			PkpkData[i][3] = x[bins[i]];
			PkpkData[i][4] = x[indx];
//			printf("%d\t%d\t%d\t%3.4f\t%3.4f\n", i, ptr, indx, x[ptr],x[indx]);
		}
//		getchar();
		binsN = binsNew;
		fuseAllPeaks(binsNew, PkpkData, N);
		for (i = 0; i < binsNew; i++)
		{
			bins[i] = (int)(binsX[newBins[i]]);
			flag = (int)(PkpkData[i][5]);
			indx = (int)(PkpkData[i][1]);
			if (flag != 0)
			{
//				printf("%d\t%d\t%3.4f\n", i, bins[i], x[bins[i]]);
				if (i + 1 < binsNew)
				{
//					printf("it is OK to insert-->%d\t%3.4f\n", indx, x[indx]);
					temp = bins[i]; bins[i] = indx;
//					printf("%d\t%d\t%3.4f\n", i, bins[i], x[bins[i]]);
					i = i + 1; bins[i] = temp;
//					printf("%d\t%d\t%3.4f\n", i, bins[i], x[bins[i]]);
				}
			}
//			else printf("%d\t%d\t%3.4f\n", i, (int)(PkpkData[i][2]), PkpkData[i][4]);
		}

	}
	else printf("!. NO PEAKS %d\n", binsN);
	if (binsN > 0) myFree2(PkpkData, binsNew);

	free(pitchFreqInd); free(peaksX); free(binsX); free(newBins);
	return binsN;
}

void fuseAllPeaks(int binsNew, double** PkpkData, int N)
{
	int i, ek, flag = 1, j, min = 0, jMin, delN, delM, indx;
	double dist;
	dist = (double)(N) * 0.1; delM = (int)(log(dist) / log(2));
	delN = (int)(pow(2, delM));
	//    printf("-->%d\n",delN);


	for (i = 0; i < binsNew; i++)
	{
		ek = (int)(PkpkData[i][1] - PkpkData[i][2]);
		if (abs(ek) > 10) flag = 1; else { flag = 0; PkpkData[i][5] = 0; PkpkData[i][6] = 0; }

		if (flag == 1)
		{
			for (j = 0; j < i + 1; j++)
			{
				ek = abs((int)(PkpkData[i][1] - PkpkData[i - j][2]));
				if (j == 0) { min = ek; jMin = i - j; }
				if (ek < min) { min = ek; jMin = i - j; }
			} if (min < delN) { PkpkData[i][5] = 0; PkpkData[i][6] = 0; }
			else { PkpkData[i][5] = min; PkpkData[i][6] = jMin; }
		}
	}

	for (i = 0; i < binsNew; i++)
	{
		flag = (int)(PkpkData[i][5]);
		indx = (int)(PkpkData[i][1]);
		if (flag != 0)
		{
			if (PkpkData[i][4] < 0.01) PkpkData[i][5] = 0.0;
		}
	}


	/*    for (i = 0; i < binsNew; i++)
		{
			for (j = 0; j < 3; j++) printf("%d\t",(int)(PkpkData[i][j]));
			for (j = 3; j < 5; j++) printf("%3.4f\t",PkpkData[i][j]);
			for (j = 5; j < 7; j++) printf("%d\t",(int)(PkpkData[i][j]));
			printf("\n");
		}*/

	return;
}
