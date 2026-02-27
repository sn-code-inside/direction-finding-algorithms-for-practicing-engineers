# include "DelayF.h"
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

//....... Function 8
//... Fine Shifting of the sequence Yup to match Ydwn...
//
//...
double* fineR
(
	double* Ydwn, 
	double* Shift,
	double N,
	int winLength,
	double * ShiftF, 
	double *rF,
	double *TouF,
	int *JKLen
)
{
		int JkLen = 50,k;
		double* Jk;
		double*	localShiftF;
		double angle, fn,del;
		printf(" apf2 method pole variation\n");
		fn = 1 / N;
		JKLen[0] = JkLen;
		Jk = sweepR(winLength, Ydwn, Shift,rF,JkLen);
		angle = r2angle(rF[0], 1 / N);
		printf(" angle exact %3.4f\n", angle * 2);
		if (angle > 90.0) angle = angle - 180.0;
		TouF[0] = angle / 180.0;
		del = fabs(fabs(angle) - 90.0)*2.0;
		if (del < 10.0) // why this number 10 ?
		{
			if (angle < 0.0)
			{
				TouF[0] = -angle / 180.0;
			}
		}
		printf(" angle %3.4f Degrees\n",angle*2);
		localShiftF = apf2(winLength, rF[0], Ydwn);
		for (k = 0; k < winLength; k++) ShiftF[k] = localShiftF[k];
		//free(localShiftF);
		return Jk;
}

double* fineAngle
(
	double* Ydwn,
	double* Shift,
	double N,
	int winLength,
	double* ShiftF,
	double* angleF,
	double* TouF,
	int* JKLen
)
{
	int JkLen = 50;
	double* JkAngle;
	double sign;
	double angle, fn;
	fn = 1 / N;
	JKLen[0] = JkLen;
	JkAngle = sweepAngle(winLength, Ydwn, Shift, angleF, fn, JkLen);
	angle = angleF[0]; 
	sign = angle / fabs(angle);
	if (angle > 180.0) angle = angle - 360.0;
	TouF[0] = angle / 360.0;
	ShiftF = apfNew(winLength, angleF[0], fn, Shift);
	printf(" newApf method angle variation\n");
	return JkAngle;
}


//....... Function 6
//
//

double orthoRfine(int winLength, double * Ydwn, double * Shift, double * ShiftF, double *rF, double N)
{
		double rA, rB,angle,rFine, TouF;
		int  M = 25, flag = 0, indx[2] = { 0,0 }, val = 0;
		rB = ortho(winLength, Ydwn, Shift, N, &angle);
		rA = ortho(winLength, Shift, Ydwn, N, &angle);
		if (fabs(rA) < 0.95) indx[0] = 1; else indx[0] = 0;
		if (fabs(rB) < 0.95) indx[1] = 1; else indx[1] = 0;
		val = 2 * indx[0] + indx[1];
		printf("[%d] Choose either %3.4f or %3.4f\n", val,rA, rB);
		switch (val)
		{
		case 0:	printf(" There is no solution rA %3.4f rB %3.4f\n", rA, rB); break;
		case 1: printf(" Choose rA %3.4f\n", rB); break;
		case 2: printf(" Choose rB %3.4f\n", rA); break;
		case 3: printf(" Choose either rA or rB which ever is lowest \n");
			if (fabs(rA) < fabs(rB)) printf(" Choose rA %3.4f\n", rA);
			else printf(" Choose rB %3.4f\n", rB); break;
		default:
			break;
		}


		flag = 1; rFine = ortho(winLength, Ydwn, Shift,N,&angle);
		if (fabs(rFine) > 0.95)
		{
			printf(" Unstable Estimate rFine %f rework\n",rFine);
			flag = -1; rFine = ortho(winLength, Shift,Ydwn, N,&angle);
			if (fabs(rFine) > 0.95)
			{
				TouF = angle / 360.0 * flag;
				printf(" Fine Delay may not reliable APF r %f\n",rFine);
				return (TouF);
			}
			printf(" New Estimate rFine %f\n",rFine);
			angle = angle + 180.0;
		}
		if (flag < 0 ) filter(rFine, Ydwn,ShiftF,winLength);
		else filter(rFine, Shift,ShiftF,winLength);

		TouF = angle / 360.0 * flag; rF[0] = rFine;
		printf(" phase shift angle %f degrees and fine delay %f\n", angle,TouF);
		return ( TouF );
}

void filter( double r, double *u, double*x,int maxk)
{
	double uk1, uk0=0;
	double xk1, xk0=0;
	int k;
	for (k = 0; k < maxk; k++)
	{
		uk1 = uk0; xk1 = xk0;
		uk0 = u[k]; // this is too senitive don't change this place
		xk0 = r * xk1 - r * uk0 + uk1;
		x[k] = xk0;
	}
	return;
}




double ortho
(
	int maxk,		// total number of samples needed 
	double *x,
	double *u,
	double N,
	double *angleD
)
{
	double uk1 = 0, uk0 = 0;
	double xk1 = 0, xk0 = 0, zk = 0, xK;
	double zk1 = 0, zk0 = 0;
	double ek = 0, pk = 0.0, rk;
	double* dly, * bufer;
//    double loopGain = 0.01F, shift = 0.0F;
	double loopGain = 0.05, shift = 0.0;
	int delay = 20, i, k, dPlus;// Integration window of MA Filter
//	double* u, * x;
	double pi, angle;
	double omega, theta, r=0.8, num,den,fn;

//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri

	pi = (double)(4.0 * atan(1.0));
	dPlus = delay + 2;
	dly = (double*)malloc(dPlus * sizeof(double));
	bufer = (double*)malloc(dPlus * sizeof(double));
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	for (i = 0; i <= delay; i++) { bufer[i] = 0.0; dly[i] = 0.0; }
	uk0 = 0.0; xk1 = 0.0; pk = 0.0; uk1 = 0.0; rk = 0.1;
	fn = 1.0 / N;
	omega = 2 * pi * fn;
	for (k = 0; k < maxk; k++)
	{

		uk1 = uk0; xk1 = xk0; zk1 = zk0;
		uk0 = x[k]; // input sequence uk 
		xK  = u[k]; // input sequence xk

		xk0 = rk * xk1 - rk * uk0 + uk1;     //% uk0 --> APF --> xk0
		zk = xk0 * xK;

		//1. transfer dly into bufer [1 to 40].
		for (i = 0; i <= delay; i++) 	bufer[i + 1] = dly[i];

		//2. bufer[0] equates to zk.
		bufer[0] = zk;

		//3. transfer bufer [0 to 39] into dly.
		for (i = 0; i <= delay; i++) 	dly[i] = bufer[i];


		ek = (dly[delay] - dly[0]) / (delay);
		pk = pk + ek; rk = rk - loopGain * (pk + shift);

		if (fabs(rk) > 0.99) rk = 0.99;
		num = -rk * sin(omega); den = 1.0 - rk * cos(omega);
		theta = 2 * atan(num / den) + pi / 2;
		angle = theta - omega;
		num = tan(theta * 0.5); den = num * cos(omega) - sin(omega);
		r = num / den;
		angleD[0] = angle * 180 / pi;
	}
	//printf("angle in degrees %f --r %f rk %f\n", angleD[0],r,rk);
	free(dly); free(bufer);

	return(r);
}
