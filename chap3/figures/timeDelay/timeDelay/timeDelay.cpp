// timeDelay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "timeDelay.h"
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
int main()
{
	double N, Tau, SNR, Cycles,TouT,*TauK,angle,TouF;
	int nSize,kmax,k,er,i,dir,flag;
	FILE* fp;

	N = 6.0; Tau = 8.3; Cycles = 10.0; nSize = 1000; SNR = 25.0;
	kmax = 100;
	TauK = linspace(-0.1*Tau, -Tau, kmax);

	er = fopen_s(&fp, "Data.csv", "w");

	for (k = 0; k < kmax; k++)
	{
		Tau = TauK[k];
		TouT = totalDelay(N, Tau, SNR, Cycles, nSize,&dir,&TouF);
		angle = (TouT - Tau) * 360;
		if (fabs(TouF * 360.0) > 90.0) flag = 1; else flag = 0;
		fprintf(fp, "%3.4f, %3.4f, %3.4f, %3.4f, %d\n", Tau*N, TouT*N, angle, TouF *N,dir);
		printf(" %3.4f %3.4f angle %3.4f\n", Tau*N, TouT*N, angle);
		if (fabs(angle) > 100) getchar();
	}
	fclose(fp);
	return 1;
}


double totalDelay(double N, double Tau, double SNR, double Cycles, int nSize,int *dir, double *tF)
{
//	double N, Tau, SNR, Tow,Cycles;
	double Tow,TouC, TouF, TouT, rFine,angleF;
	double phiD = 180.0;
	int winLength, Direction = 0,JkLen,control=-1;
	double** Data{}, ** winData{}, * ShiftC{}, * ShiftF{};
	double* Jk{}, * JkRsweep{}, ** rkDot{},* JkAngleSweep;
	double commonData[10];
	int maxRows = 4, i, er;
	int rkDotRows = 4;
	double windowWidth = 0.05;

	//N = 6.0; Tau = -8.3; Cycles = 10.0; nSize = 1000; SNR = 25.0;
	//N = 10.0; Tau = -4.8; Cycles = 10.0;  nSize = 1000; SNR = 20.0;


	rkDot = myAlloc2(rkDotRows,nSize);
	Data = ExpData(nSize, Tau, N, &SNR, Cycles, phiD, &Tow);
	printf(" control -1(%d) orthogonal detection or control -2(%d) cross correlation method\n", control, control);
	printf(" N %3.4f Tau %3.4f Cycles %3.4f nSize %d SNR %3.4f\n", N, Tau, Cycles, nSize, SNR);



	printf(" N %3.4f Tau %3.4f Cycles %3.4f nSize %d SNR %3.4f\n", N, Tow, Cycles, nSize, SNR);
	printf("---------------------------------------------\n\n");
	//	..................................................
	//	Detect Signal Window
	winData = DetectSignalWindow(&winLength, N, nSize,maxRows, rkDot,Data,commonData);
//	for (i = 0; i < nSize; i++)
//	{
//		printf("[%d] %3.4f %3.4f\n", i, rkDot[0][i], rkDot[1][i]);
//	}
	Direction = 1; if (winLength < 0)
	{
		Direction = -1; winLength = abs(winLength);
		printf(" Direction = %d\n", Direction);
	}
	dir[0] = Direction;
//	er = fopen_s(&fp, "Window.csv", "w");
//	for (i = 0; i < winLength; i++) fprintf(fp, "%f, %f, %f\n", winData[0][i], winData[1][i], winData[2][i]);
//	fclose(fp);
	//	...................................................
	//	Estimate Course Delay
	ShiftC = myAlloc(winLength); Jk = myAlloc(winLength/2);
	myFree2(Data, maxRows);
	printf("---------------------------------------------\n\n");
	TouC = mainDelay(winLength,N, commonData, winData, ShiftC,Jk,control);

//	er = fopen_s(&fp, "Coarse.csv", "w");
//	for (i = 0; i < winLength; i++) fprintf(fp, "%f, %f, %f\n", winData[1][i], winData[2][i], ShiftC[i]);


	//	...........................................................
	//	fine delay
	//ShiftF = (double*)malloc(sizeof(double) * winLength);
	ShiftF = myAlloc(winLength);
	printf("---------------------------------------------\n\n");
	JkRsweep = fineR(winData[2], ShiftC, N, winLength, ShiftF, &rFine,&TouF,&JkLen);
	tF[0] = TouF;
	printf(" gold Minima apf2 r %3.4f\n", rFine);
	printf(" Coarse Delay %3.4f Fine Delay %3.4f samples\n", TouC*N, TouF * N);
	TouT = (TouC - TouF) * Direction;
	printf(" Total Delay %3.4f  and Actual %3.4f samples\n", TouT*N,Tau*N);
	printf("---------------------------------------------\n\n");
	//JkAngleSweep = fineAngle(winData[2], ShiftC, N, winLength, ShiftF, &angleF, &TouF, &JkLen);
	//printf(" gold Minima Angle  %3.4f\n", angleF);
	//printf(" Coarse Delay in Cycles %f\n", TouC);
	//printf(" Fine Delay %f in Cycles and Samples %3.4f\n", TouF, TouF * N);
	//TouT = (TouC - TouF) * Direction;
	//printf(" Total Delay %3.4f\n", TouT);

//	fclose(fp);


	return TouT;
}

