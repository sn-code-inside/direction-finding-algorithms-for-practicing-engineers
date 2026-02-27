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
#include "kMusic.h"
//#include "mex.h"   // this is required

double kMusic(complex **S, complex **steering, double *doas,double *config, double **s)
{
	int numberOfTgts, rc[2], k,cby2,j,i;
	int numOfPhaseSpecSamples, numberOfPks,kmax,indxFlag;
	int numberOfPksNew = 0;
	int NGS = 10;
	double pi, *theta, **AB;
	double delth, th, doa, *DOA, *beta, *Phi, *JkPk, factor;
	double dByLambda = 0.5, max = -1.0F, ab[2], Jk, phi;
	double  Quality = 1, figureOfMerit = 1.0;
//	double qDoa;
	complex *b;
//	FILE* fpKmusic;
//	er = fopen_s(&fpKmusic, "erKmusic.csv", "a");
//	if (fpKmusic == NULL)  printf("!. Failed to open file erKmusic.csv\n");

//	printf("double kMusic()\n");
	numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
	rc[0] = (int)(config[7]); rc[1] = (int)(config[13]); cby2 = rc[1] / 2;
	numberOfPks = 4; // proposed number of peaks
	
//	numOfPhaseSpecSamples = 30;
//	....................................................................
	b = myAllocComplex(cby2); theta = myAlloc(numOfPhaseSpecSamples);
	beta = myAlloc(numberOfPks); JkPk = myAlloc(numberOfPks);
	Phi =  myAlloc(numberOfPks); DOA  = myAlloc(numberOfPks);
	AB = myAlloc2(numberOfPks, 4);


//	....................................................................
	pi = 4.0*atan(1.0); doa = 10.0;
	factor = (pi / 180.0) / (2 * pi*dByLambda);
	numberOfPks = 3; // this number is important
	delth = 360.0F / (numOfPhaseSpecSamples - 1);
	for (k = 0; k < numOfPhaseSpecSamples; k++) theta[k] = k*delth - 180.0;
	for (i = 0; i < numberOfTgts; i++)
	{
		for (k = 0; k < cby2; k++) b[k] = steering[i][k];
		max = -1.0F;
		for (k = 0; k < numOfPhaseSpecSamples; k++)
		{
			th = theta[k];
			s[i][k] = pObj(b, th, cby2);
			if (s[i][k] > max) { max = s[i][k]; kmax = k; }
		}
		indxFlag = locateDoaPks(numOfPhaseSpecSamples, numberOfPks, AB, s[i]);

		if (indxFlag == 0) 
		{
			printf("!. %d No peaks no DOA in kMUSIC s[%d]\n",indxFlag,i);
			fprintf(fpLog,"%d No peaks no DOA in kMUSIC s[%d]\n",indxFlag,i);
//			if (er > 0)
			{
				for (k = 0; k < numOfPhaseSpecSamples; k++)
					printf("%3.4f ,", s[i][k]); printf("\n");
			}
			doa = 0.0; phi = 0.0; Jk = 0.0;
		}
		else
		{
			if (indxFlag < 0)
			{
//				printf("!. warning: Target [%d] Phase peaks [%d] < (%d)\n",i, abs(indxFlag), numberOfPks);
				fprintf(fpLog, "!. warning: Target [%d] Phase peaks [%d] < (%d)\n",i, abs(indxFlag), numberOfPks);
			}

			numberOfPksNew  = abs(indxFlag);
			for (j = 0; j < numberOfPksNew; j++)
			{
				ab[0] = AB[j][0]; ab[1] = AB[j][1];
				goldDoa(cby2, b, &Jk, &phi, ab, NGS, 1); // if the value is 1 we get maxima between ab[0] and ab[1] 4.12.2017 KVR
				beta[j] = phi * factor; Phi[j] = phi; JkPk[j] = Jk;
				if (fabs(beta[j]) < 1.0F) DOA[j] = asin(beta[j]) * 180 / pi;
			}
			doa = DOA[0]; phi = Phi[0]; Jk = JkPk[0];
//			printf("exact doa peaks [%d] and top phase %3.4f for target [%d]\n", indxFlag,phi,i);
		}
		doas[i] = -doa; // see the change of sign on 3rd May 2025
	}
//	printf("line 108 kMusic \n"); getchar();
//	.......... Free memory ....................................................
	free(b); 
	free(theta); 
	free(beta); free(JkPk); free(Phi);
	free(DOA); 
	myFree2(AB, numberOfPks);
//	fclose(fpKmusic);
	return doa;
}

double pObj(complex *b, double theta, int cby2)
{
	int j;
	double th,pi,s;
	complex w, sum, a;
	cadd add; cmul mul; Cabs cabs;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	pi = 4.0*atan(1.0);
	sum.r = 0.0F; sum.i = 0.0F;
	for (j = 0; j < cby2; j++)
	{
		th = theta * pi / 180.0;
		w.r = cos(th * j); w.i = sin(th * j);
		a = mul.mul(w,b[j]);  // a = cmul(w, b[j]);
		sum = add.add(sum,a); // sum = cadd(sum, a);		 
	}
	s = cabs.cabs(sum); // s = cabs(sum);	
	return(s);
}

void goldDoa
(
	int cby2,
	complex *b,
	double *jK,
	double *doa,
	double *ab,
	int NGS,
	int max
)
{
	int i;
	double aa, bb, cc, dd;
	double fc, fd,g;
	double pi = (double)atan(1.0)*4.0;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
//  27th Jul 2017 for     Dr Kaluri Reserach House. @ Home Office Princeton NJ

	aa = ab[0]; bb = ab[1];
	g = (3 - sqrt(5)) / 2;
	for (i = 0; i < NGS; i++)
	{
		cc = aa + g*(bb - aa);
		dd = cc + g*(bb - cc);

		fc = -pObj(b, cc, cby2)*max;
		fd = -pObj(b, dd, cby2)*max; // negative sign to take care of maxima to look like minima 23-2-2016

		if (fc <= fd) { bb = aa; aa = dd; }
		else { aa = cc; cc = dd; }
	}
	doa[0] = aa;  jK[0] = fabs(fc);
	return;
}

int locateDoaPks // output is a scalefactor for normalisation
(
	int N,            // Number of Sample Points
	int numberOfPks,  // number of targets
	double **ab,      // peak bounds as theta
	double *JkC       // Phase spectrum
)
{
	int k, num, numOfPeaks, pkNumber, pkNumberLocal;
//	double *pK, *fn, delf, max = -1.0F, *JkClOcal;
	double *fn, delf, max = -1.0F, *JkClOcal;
	int *peaks, s, e, km, flag = 1, pkFlag = 1;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
//	JkClOcal = (double *)malloc(N * sizeof(double));
	JkClOcal = myAlloc(N); fn = myAlloc(N); 
	peaks = (int*)malloc(N * sizeof(int));
//	fn = (double *)malloc(N * sizeof(double));
//	pK = (double *)malloc(N * sizeof(double));
//	Normalise JkC
	if (PRINT_FLAG == 1) printf("int locateDoaPks()\n");
	km = myMax(JkC, N); max = JkC[km];
	for (k = 0; k < N; k++) JkClOcal[k] = JkC[k] / max;
	//	................................................
	delf = 360.0F / ((double)(N - 1));              // -180 to +180
	for (k = 0; k < N; k++) fn[k] = k*delf - 180.0; // original locatePks is rehashed for this app

	numOfPeaks = findPeaks(N, &num, peaks, JkClOcal);
//	for (k = 0; k < num; k++)
//		printf("%d [%3.2f].[%3.4f]\n", k,fn[peaks[k]], JkClOcal[peaks[k]]);
	if (numOfPeaks < 0) 
	{ 
		printf("!. THERE is NO DOA peak in %d I am exiting %d\n", N,numOfPeaks);
		fprintf(fpLog,"!. THERE is NO DOA peak in %d I am exiting %d\n", N,numOfPeaks);

		free(JkClOcal); free(fn); free(peaks);
		return num;
	}
//	printf("doa number of peaks -->%d\n", num); getchar();
	for (pkNumber = 0; pkNumber < numberOfPks; pkNumber++)
	{
		pkNumberLocal = pkNumber;
		if (pkNumber > numOfPeaks - 1) 
		{ 
			pkNumberLocal = numOfPeaks - 1; 
			flag = -1;
		}
		k = peaks[pkNumberLocal]; // <- this normally same as target number other wise clamped to max peaks
		s = k - 1; e = k + 1;
		if (s < 0) s = 0; if (e >= N) e = N - 1; // safety
		ab[pkNumber][0] = fn[s]; ab[pkNumber][1] = fn[e];
		ab[pkNumber][2] = k; ab[pkNumber][3] = max;
	}
//	Free memory
	free(JkClOcal); free(fn); free(peaks); 
//	pK = (free(pK), NULL);
//	return km*flag;
//	printf("line 232 kMusic [%d.%d]\n", flag, numberOfPks); getchar();

	return numOfPeaks*flag;
}


void getExtent(double *TgtPar, double *DOA, double ratio)
{
	double delx, dely, diagonal, direction,pi;
	pi = 4.0*atan(1.0);
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
//	compute extent .. some issues still ..
	if (ratio < 2.0)
	{
		delx = sin(DOA[0] * pi / 180) - sin(DOA[1] * pi / 180);
		dely = cos(DOA[0] * pi / 180) - cos(DOA[1] * pi / 180);
		diagonal = (sqrt(delx*delx + dely*dely))*TgtPar[0];
		direction = atan2(dely, delx) * 180 / pi;
	}
	else { diagonal = 0.0; direction = 0.0; }
	if (diagonal > 0.1) { TgtPar[2] = 0.0; TgtPar[3] = 0.0; } // 10% of range gain
	else { TgtPar[2] = diagonal; TgtPar[3] = direction; }
	return;
}

double QofDOA
(
	double *TgtPar,
	complex *b,
	int indxFlag, 
	double *DOA, 
	double *Phi, 
	double *JkPk,
	double *beta,
	int numberOfPks,
	int cby2,
	int NGS
)
{
	double Pr, rg, rcs, gAvg,ratio;
	double spekGain = 8000.0;
	double noiseFig = 0.0, quality, Quality;
	int k;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	ratio = JkPk[0] / JkPk[1]; 	
	getExtent(TgtPar, DOA, ratio);
	gAvg = 0.0;  
//	for (k = 0; k < cby2; k++) gAvg = gAvg + Tgt[0].gain[k]; // this must be divided by cby2 it is OK
	for (k = 0; k < cby2; k++) gAvg = gAvg + TgtPar[9+k];    // this must be divided by cby2 it is OK
	quality = DoaDistortion(TgtPar, b, Phi, JkPk, cby2, NGS, indxFlag);

	rg = TgtPar[0]; //  rg = Tgt[0].range;
	Pr = (TgtPar[8] / gAvg) * spekGain; // Pr = (Tgt[0].amp / gAvg) * spekGain; 
	rcs = rg*rg*rg*rg*Pr;
	printf("!. Channel Gain %3.4f ", gAvg); printf("\n");
	printf("!. Normalised range %3.4f .. Normalised Scaled Received Power %3.4f\n", rg, Pr);
	Quality = rcs*quality; // this is an important factor ..
//	if (indxFlag < 0)
	printf("!. RCS %3.4f DOA Quality %3.4f Target Quality %3.4f\n", rcs, quality, Quality);
//	else printf("!. RCS %3.4f quality %3.4f Quality %3.4f\n", rcs, quality, Quality);
	if (quality < 6.0) Quality = 0.0; else Quality = 1.0;
//	Tgt[0].extent[2] = Quality; Tgt[0].extent[0] = rcs;
	TgtPar[4] = Quality; TgtPar[2] = rcs;

	return(Quality);
}

double DoaDistortion(double *TgtPar,complex *b, double *Phi,double * JkPk,int cby2,int NGS,int indxFlag)
{
	sort phase;
	double doaDips[2], JkDips[2],span,spanA;
	double ab[2], Jk, phi;
	double doaFigOfMerit,figQ,qOfDips;
	double localPhi[3];
	int PhiI[3];
	int k,PeaksNum;
	PeaksNum = abs(indxFlag); 
	if (PeaksNum > 3) PeaksNum = 3; // clamp to 3
	for (k = 0; k < PeaksNum; k++) localPhi[k] = Phi[k];

//	if (indxFlag > 0)	twoDips = 2; else twoDips = 1;
	if (PeaksNum > 1)
	{
		spanA = fabs(Phi[0] - Phi[1]) / 180.0;
		figQ = spanA*(JkPk[0] - JkPk[1]);
	} 	else figQ = JkPk[0];
	phase.x = Phi; phase.xI = PhiI; phase.M = 3;
	phase.Low2High();


//	printf("[%d] spanA %3.4f figQ %3.4f\n", indxFlag,spanA, figQ);
	for (k = 0; k < PeaksNum-1; k++)
	{
		ab[0] = Phi[k]; ab[1] = Phi[k + 1];
//		printf("!.. bounds %3.4f %3.4f\n", ab[0], ab[1]);
		goldDoa(cby2, b, &Jk, &phi, ab, NGS, -1);
		JkDips[k] = Jk; doaDips[k] = phi;
//		printf("!. [%d] minima value %3.4f at %3.4f\n", k, Jk, phi);
	}


	if (indxFlag > 0)
	{
		span = fabs((doaDips[0] - doaDips[1])) / 180.0;
		qOfDips = ((JkDips[0] + JkDips[1])*span*0.5);
	}	else qOfDips = JkDips[0];

	if ( PeaksNum != 1)   doaFigOfMerit = figQ / qOfDips;
	else doaFigOfMerit = figQ;

//	Tgt[0].doaPks[0] = qOfDips; Tgt[0].doaPks[1] = figQ; Tgt[0].doaPks[2] = doaFigOfMerit;
	TgtPar[5] = qOfDips; TgtPar[6] = figQ; TgtPar[7] = doaFigOfMerit;
//	printf("!. [%d] qOfDips %3.4f Quality of Peaks %3.4f\n", PeaksNum, qOfDips, figQ);
	for (k = 0; k < PeaksNum; k++) Phi[k] = localPhi[k];
	return doaFigOfMerit;
}

double howGoodDoa(double *Phi, int pks)
{
	int k; double max, *PhiLocal, m, c, sum;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	if (pks > 3) { printf("!. why is it > than 3\n"); pks = 3; }
	PhiLocal = myAlloc(pks);
//	PhiLocal = (double *)malloc(pks * sizeof(double));
	if (fabs(Phi[0]) > fabs(Phi[1])) max = fabs(Phi[0]); else max = fabs(Phi[1]);
	if (max < fabs(Phi[2])) max = fabs(Phi[2]);
	printf("!. Phase @Peak ");  for (k = 0; k < pks; k++) printf("%3.4f ", Phi[k]); printf("(%3.4f)\n", max);
	for (k = 0; k < pks; k++) PhiLocal[k] = Phi[k] / max;
	m = (PhiLocal[2] - PhiLocal[0])*0.5;
	c = (5.0 * PhiLocal[0] + 2.0*PhiLocal[1] - PhiLocal[2]) / 6.0;
	sum = fabs(PhiLocal[0] - c) + fabs(PhiLocal[1] - m - c) + fabs(PhiLocal[2] - 2 * m - c);
	sum = sum / (fabs(PhiLocal[0]) + fabs(PhiLocal[1]) + fabs(PhiLocal[2]));
		printf("slope %3.4f .. intercept %3.4f\n", m, c);
		for (k = 0; k < pks; k++) printf("%3.4f[%3.4f] ..", PhiLocal[k],m*k + c); printf("\n");
		printf("est %3.4f .. true ..%3.4f .. eror %3.4f\n", m+c, PhiLocal[1],sum);
	return sum;
	free(PhiLocal);
	//	if (sum > 0.2) return -1; else 	return 1;
}


