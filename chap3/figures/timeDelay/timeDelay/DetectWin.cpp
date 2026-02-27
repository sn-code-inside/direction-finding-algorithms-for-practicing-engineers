# include "DetectWin.h"
//# include "mex.h"
	double windowWidth = 0.05;
	int DataFileLength = 0;
	int myCommonI[10];
	double myCommonF[10];
//
// .. double Common Variables..
//
// .. myCommonF[4] is Frac
// .. myCommonF[3] is JkCmin
// .. myCommonF[2] is total Estimated Delay
// .. myCommonF[1] is one before JkCmin
// .. myCommonF[0] is JkFmin
//
// .. Integer Common Variables..
//
// .. myCommonI[0] is w1
// .. myCommonI[1] is w2
// .. myCommonI[2] is peakIndex_2
// .. myCommonI[3] is peakIndex_3
// .. myCommonI[4] is Lead the difference between two peaks
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
	double** DetectSignalWindow
	(
		int* winLength, 
		double N, 
		int nSize, 
		int maxRows, 
		double** rkDot, 
		double** Data,
		double* commonData
	)
	{
	//	first column = Time
	//	second column = Up
	//	third column = Down

		double width = 0.0;
		double windowFactor = 20.0;
		int peakIndex_2, peakIndex_3;
		int w1, w2, i;
		int Direction = 1;

		double** winData{}, loopGain[2];
		peakIndex_2 = phiShift(Data[1], nSize, rkDot[0], rkDot[2], N,loopGain); // detect phase shift
		peakIndex_3 = phiShift(Data[2], nSize, rkDot[1], rkDot[3], N,loopGain); // detect phase shift
		//3.1 From peak value, compute a window.
		Direction = fixWindow(N, &w1, &w2, peakIndex_2, peakIndex_3, nSize);
		winLength[0] = (w2 - w1 + 1);
		printf("[%d] values of w1 %d w2 %d peak2 %d peak3 %d \n", Direction,w1, w2, peakIndex_2, peakIndex_3);

		winData = setWinDat(Data, maxRows, winLength[0], w1,Direction);
//	Detection Parameters
		myCommonI[0] = w1;          myCommonI[1] = w2;
		myCommonI[2] = peakIndex_2; myCommonI[3] = peakIndex_3;
		for (i = 0; i < 5; i++) commonData[i] = myCommonI[i]; 
		commonData[4] = loopGain[0]; commonData[5] = loopGain[1];

		winLength[0] = (w2 - w1 + 1) * Direction;
		printf(" start = %d end = %d Detected window %d\n", w1, w2, winLength[0]);
		myCommonI[4] = Direction;
		return winData;
	}

	int fixWindow(double N,int*W1,int*W2,int peakIndex_2,int peakIndex_3,int nSize)
	{
		int Lead,Direction=0,peakIndex;
		double windowFactor = 20.0;
		int Ofset, Ofsetw1, Ofsetw2;
		int w1, w2;
		//  Decide if the data is placed in the right way
		Lead = peakIndex_2 - peakIndex_3;
		printf(" peak value of column 2 = %d and column 3 =%d \n", peakIndex_2, peakIndex_3);
		//
		//................. Bug Fix on 4th July 2006..................
		if (peakIndex_2 == 0)
		{
			peakIndex_2 = 1;
			printf(" peakIndex_2 is set to 1 since it is zero \n");
		}
		if (peakIndex_3 == 0)
		{
			peakIndex_3 = 1;
			printf(" peakIndex_3 is set to 1 since it is zero \n");
		}
		Ofset = (int)(windowFactor * N);
		Ofsetw1 = (int)(windowFactor * N * 1.4);
		Ofsetw2 = (int)(windowFactor * N * 0.7);

		printf(" ofset from peak = %d\n", Ofset);
		if (peakIndex_2 < peakIndex_3) // original
		{
			Direction = 1;
			peakIndex = peakIndex_3; // ... commented 4th Sep 2006
			w1 = peakIndex - Ofsetw1;
			w2 = peakIndex + Ofsetw2;
			if (w1 < 0)
			{
				peakIndex = peakIndex_2; 
				w1 = peakIndex - Ofsetw1;
				w2 = peakIndex + Ofsetw2;
			}

		} 
		else
		{
			Direction = -1;
			peakIndex = peakIndex_2; 
			//
			w1 = peakIndex - Ofsetw1;
			w2 = peakIndex + Ofsetw2;
			if (w1 < 0)
			{
				peakIndex = peakIndex_3;
				w1 = peakIndex - Ofsetw1;
				w2 = peakIndex + Ofsetw2;
			}
		}
		if (w2 > nSize) w2 = nSize - 5; 
		//
		// End of Data placement
		W1[0] = w1; W2[0] = w2;
		return Direction;
	}

	double ** setWinDat(double** Data, int maxRows,int winLength, int w1, int Direction)
	{
		int i;
		double** winData;
		winData = myAlloc2(maxRows, winLength);
		for (i = 0; i < winLength; i++)
		{
			winData[3][i] = Data[3][i + w1];
			if (Direction > 0)
			{
				winData[1][i] = Data[1][i + w1];
				winData[2][i] = Data[2][i + w1];
			}
			if (Direction < 0)
			{
				winData[1][i] = Data[2][i + w1];
				winData[2][i] = Data[1][i + w1];
			}
			winData[0][i] = Data[0][i + w1];
		}

		return winData;
	}


	int phase(double *uk,double N,int nSize,double *rkdot)
	{
		double angle = -90.0,fn;
		double *yk,zk,ek,pk=0.0;
		int flag,k,i,delay = 39,peakIndex;
		double *dly, *bufer,maxRkdot;
		fn = 1 / N;
		yk = myAlloc(nSize); 
		dly = myAlloc(delay); bufer = myAlloc(delay + 1);
		flag = ChoseAPForder(angle, fn, nSize, uk, yk);
		for (i = 0; i < delay; i++) dly[i] = 0.0;
		for (i = 0; i < delay+1; i++) bufer[i] = 0.0;
		for (k = 0; k < nSize; k++)
		{
			zk = uk[k] * yk[k];

			//1. transfer dly into bufer [1 to 40].
			for (i = 0; i <= delay; i++)
				bufer[i + 1] = dly[i];

			//2. bufer[0] equates to zk.
			bufer[0] = zk;

			//3. transfer bufer [0 to 39] into dly.
			for (i = 0; i <= delay; i++)
				dly[i] = bufer[i];


			ek = (dly[delay] - dly[0]) / (delay);
			pk = pk + ek; rkdot[k] = pk;
//			rk = rk - loopGain * (pk + shift);

//			if (fabs(rk) > 0.95) rk = 0.95;

//			Rk[k] = rk;
//			rkdot[k] = pk;
		}
		peakIndex = myMax(rkdot, nSize);
		maxRkdot = fabs(rkdot[peakIndex]);
		for (k = 0; k < nSize; k++)
		{
			rkdot[k] = rkdot[k] / maxRkdot;
//			printf("[%d] %3.4f(%3.4f)\n", k, rkdot[k],maxRkdot);
		}
		return 1;
	}
//
//	Accepts: Array of signal values Uk. Samples per cycle N.
//	Returns: rkdot rate of change of phase. Orthogonal signal samples Xk array.
//	int phiShift (double * Uk, int nSize, int N, double * rkdot, double * Xk)
int phiShift (double * Uk, int nSize, double * rkdot, double * Rk,double N,double * g)
{
	double uk1, uk0, xk1, xk0, zk, ek, pk=0.0;
	double *dly, *bufer;
	double loopGain = 0.1, shift = 0.0;

//	double Uk1, Uk0, yk1, yk0;
//	double lpf = 0;
	double *temp;
	int delay = 30; // Integration window of MA Filter
	int i,k;
	int peakMaxIndex = -1;
	int peakMinIndex = -1;
	int peakIndex = -1,flag =0;
//	double* uk180;

	double rk = 0.1, f = 1.0 / N;
	g[0] = loopGain; g[1] = delay;
	dly = myAlloc(delay+1); bufer = myAlloc(delay + 2);
	for (i = 0; i < delay+1; i++) dly[i] = 0.0;
	for (i = 0; i < delay + 2; i++) bufer[i] = 0.0;

//	uk180 = myAlloc(nSize);
// ..........k loop begining all below is looped till end 
//
	uk0 = 0.0; xk0 = 0.0;
	xk1 = 0.0;
	for (k = 0; k < nSize ; k++)
	{
//..........................................		
		uk1=uk0; 	xk1=xk0;
		uk0=Uk[k]; //% Uk contains the input data and Phase shifted in Xk by pi/2
		
		xk0=rk*xk1 - rk*uk0 + uk1; //% uk0 --> APF --> xk0
		zk=uk0*xk0;
		
		//1. transfer dly into bufer [1 to 40].
		for (i= 0; i<= delay; i++)
			bufer[i+1] = dly[i];
		
		//2. bufer[0] equates to zk.
		bufer[0] = zk;
		
		//3. transfer bufer [0 to 39] into dly.
		for (i= 0; i<= delay; i++)
			dly[i] = bufer[i];
		
		
		ek = (dly[delay]-dly[0])/(delay);
		pk = pk+ek; rk = rk - loopGain*(pk+shift);
		
		if (fabs(rk) > 0.95) rk=0.95;
		
		Rk[k] = rk;
		rkdot[k] = pk;
	}
	//	correction initial delay due to integration time of 'delay' samples
	temp = myAlloc(delay + 2);
	for (k = 0; k < delay + 2; k++) temp[k] = rkdot[delay + 2 + k];
	for (k = 0; k < delay + 2; k++) rkdot[k] = temp[k];
	peakIndex = processRkdot(rkdot, nSize);
	free(dly); free(bufer); free(temp);
	return peakIndex;
}

int processRkdot(double *rkdot, int nSize)
{
	int peakIndex,peakI,k,kt,i,flag =0;
	double maxRkdot;
	double minMax[2], mid, prob;
	peakIndex = myMax(rkdot, nSize);
	maxRkdot = fabs(rkdot[peakIndex]);
	for (k = 0; k < nSize; k++) 	rkdot[k] = fabs((rkdot[k] / maxRkdot));	//normalize rdot vector.
	myMaxMin(rkdot, minMax, nSize);
	mid = (minMax[0] + minMax[1]) / 2.0;
	printf(" min %3.4f [%3.4f] max %3.4f\n", minMax[0], mid, minMax[1]);
	kt = 0;
	for (i = 0; i < nSize; i++) { if (rkdot[i] > mid) kt = kt + 1; }
	prob = (double)(kt) / (double)(nSize);
	printf(" points %d probability %3.4f\n", kt, prob);
	if (prob > 0.2)
	{
		printf(" %3.4f > 0.2 inverting\n", prob);
		for (i = 0; i < nSize; i++) rkdot[i] = minMax[1] - rkdot[i];
	}
	flag = 0; peakI = peakIndex;
	for (i = 0; i < nSize; i++)
	{
//		printf("[%d] %3.4f %3.4f\n", i, rkdot[i], rkdot[i]);
		if (rkdot[i] > mid) { flag = flag + 1; }
		if (flag == 1)
			{
				peakIndex = i;
				printf(" first raising edge [%d] and peak [%d]\n", i,peakI);
			}
	}
	return peakIndex;
}

int myMax(double* JkC, int N)
{
	int k, km = 0; double max = -1.0F;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	for (k = 0; k < N; k++)
	{
		if (k == 0) { max = fabs(JkC[k]); km = 0; }
		else
		{
			if (fabs(JkC[k]) > max) { max = fabs(JkC[k]); km = k; }
		}
	}
	return km;
}

void myMaxMin(double* x, double* minMax, int lenX)
{
	double max = -5000.0, min = 5000.0;
	int k;
	for (k = 0; k < lenX; k++)
	{
		if (k == 0) { max = x[0]; min = x[0]; }
		else {
			if (x[k] >= max) max = x[k];
			if (x[k] < min)  min = x[k];
		}
//		printf("! [%d](%3.4f) %3.4f %3.4f\n", k, x[k], min, max);
	}
	minMax[0] = min; minMax[1] = max;
	return;
}






