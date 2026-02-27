	# include "DelayC.h"
    //# include "mex.h"
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
	double mainDelay
	(
		int winLength, 
		double N, 
		double* commonData,
		double** winData, 
		double *Shift,
		double* Jk,
		int control
	)
	{
		double estTow = 0.0;
	//	double par[3];
		int argN = 1;

	//	par[0] = 0.0; par[1] = 0.0; par[2] = 0.0;
	//	printf(" N %3.4f winLen %d  %d\n", N,   winLength, Direction);
	//
	//		Estimate delay
	//
		estTow = estDelay(commonData, winData, winLength,N,Shift,Jk,control); // Function 10
		printf(" N=%3.4f winLength %d\n", N,  winLength);
	//	printf(" Coarse Delay in Cycles %f\n",estTow);
        return estTow;
	}


	double estDelay
	(
		double* commonData, 
		double** winData, 
		int winLength, 
//		int Direction, 
		double N,
		double *Shift,
		double *Jk,
		int control
	)
	{
		double r = 0.0; // initilise to zero and set in flag =1 or 0 blocks.
		int minJkIndex, i, parLen = 4;
		double TauC = 0.0, zMone,angleC;
		int DetectPar[4],delay;
		zMone = (double)(1.0 / N);
//		printf(" How Delay is Estimated %d\n", control);
		for (i = 0; i < parLen; i++) DetectPar[i] = (int)(commonData[i]);
//3. Estimate the integer shifting
		printf(" Detection Data Index "); for (i = 0; i < parLen; i++) printf("%d ", DetectPar[i]); printf("\n");
		delay = DetectPar[3] - DetectPar[2];
		minJkIndex = xCross(winLength, winData[1], winData[2], Shift, Jk);
		angleC = ((double)(delay) / N)*360.0;
		printf(" Delay by detection %d and delay by Cross Correlation %d\n", delay, minJkIndex);
		if (control == -1)
		{
			printf(" Delay is Estimated by Orthognal Detection (%d  %d)\n",delay,minJkIndex);
			if (delay > 0) minJkIndex = abs(delay);
			else
			{ 
				if (abs(delay) > (int)(N)) 	minJkIndex = abs(delay) + (int)(N / 2);
				else minJkIndex = abs(delay) + 1;
			}
		}
		else
		{
			printf(" Delay is Estimated by Cross Correlation %d\n",minJkIndex);
		}
		minJkIndex = shiftByDelay(winData[1], Shift, winLength, minJkIndex);

		TauC = (double)(zMone * minJkIndex);
		return TauC;
	}


//....... Function 9
//
//
// Function obtains the objective function value
// Given two vectors Yup and Shift of length winLength
//
double ObjJk( double *Ydwn, double *Shift, int winLength)
{
	int i;
	double ek,sum;
	sum = 0.0;
		for (i=0; i < winLength; i++)
		{
			ek= Ydwn[i]*Shift[i]; // this is due to values are phase shifted
			sum= sum + ek;
		}
	return sum;
}
//
// Function Shifts the time series temp by a delay defined
// by the pole position r. Series is of length winLength
// and puts into Shift
//
void ShiftC( double *Shift,int winLength)
{
	int i,k;
	double last;
	//	circular shift right
		k=winLength-1; last = Shift[k];  // bug fix 7th April 2024 for book writing Princeton
		for (i= 0; i< winLength - 1; i++) 
		{ 
			Shift[k] = Shift[k-1]; 
			k = k-1;
		} 
		Shift[0] = last;

return ;
}


//
// Function moves array X to Y
// of length winLength
//
void moveX2Y( double *X, double *Y, int winLength)
{
	int i;
	for (i= 0; i< winLength; i++) 	Y[i]=X[i]; 
	return ;
}


//....... Function 7
//.... Shifts the input signal Yup to minimize the error
//
//
int CoarseN 
(
	double *Yup, 
	double *Ydwn, 
	double *Shift, 
	double *Jk, 
	int winLength
	//	double r, 
//	int Direction
//	double N
)
{
//	double *temp;
//	double JkInd = 0.0,Ind = 0.0;
//	double maxR;
//	double uk=0.0, oldJk=0.0;
//	int k,M=0;
	int adjust=0;
	int minJkIndex = 0,minJkInd; 
//	....................
// Locating maxmimu value of coarse Jk
// This is equivalent to shifting the waveform Yup right and compare with Ydwn
// in least square sense a minima is found.
	minJkIndex = xCross(winLength, Yup, Ydwn, Shift, Jk);
	printf(" located maxima at %d by sweeping from 0 to %d and adjusted by %d\n", minJkIndex, winLength/2, adjust);

	minJkInd = shiftByDelay(Yup, Shift,winLength,minJkIndex);
//
	return minJkInd;
	
}

int xCross(int winLength, double *Yup, double *Ydwn,double* Shift,double *Jk)
{
	int M, minJkIndex,k;
	double maxR;
	M = winLength / 2; //delTc = 1.0 / N;
	moveX2Y(Yup, Shift, winLength); // Yup --> Shift
	for (k = 0; k < M; k++)
	{
		Jk[k] = ObjJk(Ydwn, Shift, winLength);
		if (k == 0) { maxR = Jk[k]; minJkIndex = 0; }

		//			Tc = (double)(k * delTc);
		if (Jk[k] > maxR)
		{
			maxR = Jk[k];
			minJkIndex = k;
			//				printf(" current maxima is %f at %d\n",maxR, minJkIndex);
		}
		// 			printf("Shift = %f cycles JkC[%d] = %f \n",Tc,k,Jk[k]);
		//			fprintf(fpObjC, "%d, %f\n", k, Jk[k]);
		ShiftC(Shift, winLength); // Shift temp by 1 sample and post it in Shift
	}

	return minJkIndex;
}

int shiftByDelay(double* Yup, double* Shift, int winLength, int minJkIndex)
{
	int adjust,k,M;
//..................................................................................
	adjust = 0; M = winLength / 2;
	//	printf(" samples per cycle %3.4f\n", N);
	minJkIndex = minJkIndex + adjust;
	//    printf(" Moved ahead by %d by samples and new index %d\n",adjust,minJkIndex);
	if (minJkIndex > 0)
	{
		moveX2Y(Yup, Shift, winLength); // Yup --> Shift
		for (k = 0; k < minJkIndex; k++)
		{
//			Jk[k] = ObjJk(Ydwn, Shift, winLength); // Yup is fixed and Ydwn is shifted
			ShiftC(Shift, winLength); // Shift temp by r and post it in Shift
			//			printf("[%d] %3.4f\n", k, Jk[k]);
		}
	}
	else minJkIndex = 0;
	return minJkIndex;
}








