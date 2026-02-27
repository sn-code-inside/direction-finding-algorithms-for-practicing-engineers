#include "detectPeaks.h"
//#include "mex.h"   /* This one is required */
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
double** stfDoa(double** Ha, double r, double d_by_lambda, int m, int D, double *se, int kmax,double** doaStf)
{
	int k, i, numberOfPks=D, pksNumber,*peaksIndx,NGS = 20;
	double* Jk, s, e, * doa, ** ab;
	double *goldPk,SE[2];
	double** JkTheta;

	s = se[0]; e = se[1];
	Jk = myAlloc(kmax); peaksIndx = myAllocI(20); ab = myAlloc2(kmax, 4);
	JkTheta = myAlloc2(2, kmax);
	
	doa = linspace(s, e, kmax);
	//printf("r = %3.4f dbl %3.4f and kmax %d [%3.4f %3.4f] \n", r, d_by_lambda, kmax, s, e);
	for (k = 0; k < kmax; k++)
	{
		Jk[k] = obj(Ha, r, doa[k], d_by_lambda, m);
		JkTheta[0][k] = Jk[k]; JkTheta[1][k] = doa[k];
	}


	//bounds[0] = s; bounds[1] = e;
	pksNumber = SweeplocateDoaPks(kmax, numberOfPks, ab, Jk,doa);
	if (pksNumber < 0) return NULL;
	//printf(" Number of Peaks %d\n", pksNumber);
	//peaksIndx = findPeaks(kmax,&numOfPeaks,Jk);
	//for (k = 0; k < pksNumber; k++)
	//{
	//	printf("[%d] start %3.4f end %3.4f max value %3.4f\n", (int)(ab[k][2]), ab[k][0], ab[k][1], ab[k][3]);
	//}
	for (i = 0; i < D; i++)
	{
		SE[0] = ab[i][0]; SE[1] = ab[i][1];
		goldPk = goldDoa(m, Ha, d_by_lambda, SE, r, NGS);
		doaStf[i][0] = goldPk[0]; doaStf[i][1] = goldPk[1];
	}
	free(Jk); free(peaksIndx); free(doa); myFree2(ab, kmax);
	//locateDoaPks(kmax, numberOfPks, ab, Jk);
	return JkTheta;
}




int SweeplocateDoaPks // output is number of peaks with sign
(
	int N,            // length of Jkc
	int numberOfPks,  // number of targets
	double** ab,      // peak bounds as theta
	double* JkC,      // Y value (JkC)
	double* doa       // X value (doa)
)
{
	int k, totalNumOfPeaks, pkNumber;
	double max, * JkClOcal;
	int* peaks, s, e, km, flag = 1, pkFlag = 1;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri

	JkClOcal = myAlloc(N); peaks = myAllocI(N);
	km = myMax(JkC, N); max = JkC[km];
	for (k = 0; k < N; k++) JkClOcal[k] = JkC[k] / max;
//	................................................
//	fn = linspace(boundsPhi[0], boundsPhi[1], N);
	peaks = findPeaks(N, &totalNumOfPeaks, JkClOcal);
	//for (k = 0; k < numberOfPks; k++)
	//	printf("peak indx %d theta %3.4f function value %3.4f\n",peaks[k],doa[peaks[k]],JkC[peaks[k]]);
	//printf(" total Number of peaks found %d\n", totalNumOfPeaks);

	//	............ error condition
	if (totalNumOfPeaks < 0)
	{
		printf("!. THERE is NO DOA peak in %d I am exiting %d\n", N, totalNumOfPeaks);
		free(JkClOcal); free(peaks);
		return totalNumOfPeaks;
	}
	if (numberOfPks > totalNumOfPeaks)
	{
		numberOfPks = totalNumOfPeaks;
		printf(" Number of peaks asked is less than actual peaks and limted to max peaks\n");
	}
	//	..............................
//	printf("doa number of peaks -->%d\n", num); getchar();
	for (pkNumber = 0; pkNumber < numberOfPks; pkNumber++)
	{
		k = peaks[pkNumber]; 
		s = k - 1; e = k + 1;
		if (s < 0) s = 0; if (e >= N) e = N - 1; // safety
		ab[pkNumber][0] = doa[s]; ab[pkNumber][1] = doa[e];
		ab[pkNumber][2] = k;     ab[pkNumber][3] = max;
	}
	//	Free memory
	free(JkClOcal);  free(peaks);
	return pkNumber * flag;
}


int* findPeaks
(
	int N,      /* length of Jk */
	int* num,   /* number of peaks */
	double* Jk  /* input function to find peaks */
)
{
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  updated 11th Nov 2022   Dr Kaluri Reserach House.
	//	printf("8. findPeaks(pM[%d],&num,peaks,JkC,fnC,PhsC,x);\n", N);
	//	FN = (double *)malloc(N * sizeof(double));
	sort objectivefunction;
	double JkSlp = 0.0F, oldJk = 0.0F;
	double pi = (double)atan(1.0) * 4.0F;
	double p = 0.0, * peak;
	int i = 0, k, oldM = 0, * peakI, indx = 0;
	int offset = 6;
	int slpUp = 0, slpDn = 0, pkYes = 0, pkFlag = 0;
	double Jk1 = 0, Jk2 = 0, Jk3 = 0;
	peak = myAlloc(N); peakI = myAllocI(N);

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
			peak[i] = Jk2; peakI[i] = k - 1;
			if ((k - 1) > 0)  i = i + 1;
			break;

		default:
			break;
		}
	}
	if (i == 0)
	{
		free(peak); free(peakI);
		num[0] = -1;
		return NULL;
	}
	num[0] = i;

	//	for (k = 0; k < num[0]; k++) printf("%d %d %3.4f\n", k, peakI[k], peak[k]); 
	//	for (k = 0; k < num[0]; k++) { peaks[k] = peakI[k]; Pk[k] = Jk[peaks[k]]; }
	//	else printf("!. Number of Peaks %d \n", i);
	objectivefunction.x = peak; objectivefunction.xI = peakI; objectivefunction.M = i;
	objectivefunction.High2Low();
	//	objectivefunction.showx(); 

	//	Free memory
	free(peak); //free(peakI);
	return peakI;
}


int myMax(double* JkC, int N)
{
	int k, km = 0; double max = -1.0F;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	for (k = 0; k < N; k++)
	{
		if (fabs(JkC[k]) > max) { max = fabs(JkC[k]); km = k; }
	}
	//	printf("max value max %3.4f@%d - %3.4f\n", max, km, JkC[km]);
	return km;
}


double* goldDoa
(
	int m,             /* size of covariance H matrix*/
	double** H,        /* Covarinace Matrix */
	double d_by_lambda,/* d by lambda */
	double* ab,        /* start and end of interval*/
	double r,          /* pole position of r */
	int NGS            /* number of gold sections */
)
{
	int i;
	double aa, bb, cc, dd;
	double fc{}, fd{}, g;
	//double pi = (double)atan(1.0) * 4.0;
	double *goldPk;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//  27th Jul 2017 for     Dr Kaluri Reserach House. @ Home Office Princeton NJ
	goldPk = myAlloc(2);
	aa = ab[0]; bb = ab[1];
	g = (3 - sqrt(5)) / 2;
	for (i = 0; i < NGS; i++)
	{
		cc = aa + g * (bb - aa);
		dd = cc + g * (bb - cc);

		fc = -obj(H, r, cc, d_by_lambda, m);
		fd = -obj(H, r, cc, d_by_lambda, m); 

		if (fc <= fd) { bb = aa; aa = dd; }
		else { aa = cc; cc = dd; }
	}
	goldPk[0] = aa; goldPk[1] = fabs(fc);
	return goldPk;
}
