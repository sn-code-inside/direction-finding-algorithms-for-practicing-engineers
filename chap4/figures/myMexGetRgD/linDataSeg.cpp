//#include "stdafx.h"
#include "linDataSeg.h"
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
int** getCloudLinPt(double* L, int lenD, int maximumNumOfPartions, int* kmax)
{
	double* localL;
	double* pk, * Pk;
	int* Pki, * localLi;
	double sigPk, muPk, thold[2];
	int k, lenL, PkLen, pkLen, i,m;
	int flag, flagA;
	int** parts{}, s = 0, sOld = 0, e = 1, inPut = 0;
	int M = lenD;
	parts = (int**)malloc(maximumNumOfPartions * sizeof(int*));
	for (i = 0; i < maximumNumOfPartions; i++) parts[i] = (int*)malloc(2 * sizeof(int));


	lenL = M;
	localL = (double*)malloc(lenL * sizeof(double));
	pk = (double*)malloc(lenL * sizeof(double));
	Pk = (double*)malloc(lenL * sizeof(double));
	Pki = (int*)malloc(lenL * sizeof(int));
	localLi = (int*)malloc(lenL * sizeof(int));
	//	parts[0][0] = 0; parts[0][1] = 0;



	for (i = 0; i < M; i++)
	{
		localL[i] = L[i]; localLi[i] = i;
	}

	for (k = 0; k < maximumNumOfPartions; k++)
	{

		//	.... mean and std of P_k-1 
		flagA = stdMuLin(localL, &sigPk, &muPk, lenL);
//        printf("p.%d [%d] (%3.4f)-%3.4f \n",k,flagA,sigPk,muPk);
		if (flagA < 0)
		{
	   		printf(" p.%d\n  Data may be zero\n",k);
            if (k == 0)
            {
			    parts[k][0] = -1; parts[k][1] = -1;
			    return NULL;
            }
		}

		//	.... partition into p_k and P_k using std of (P_k-1)
		thold[0] = sigPk; thold[1] = muPk;
		flag = splitLin(localL, localLi, pk, Pk, Pki, thold, lenL, &PkLen, &pkLen);

	    //printf(" [%d] How it is split %d = %d + %d\n", flag,lenL, pkLen, PkLen);
		if (flag > 0) inPut = pkLen; else inPut = PkLen;
		sOld = s; s = s + inPut;
		parts[k][0] = sOld; parts[k][1] = s - 1;
//		if (flag < 0) parts[k][1] = parts[k][1] - 1; // 21st Jan 2023

//		printf("{%d}[%d] %d data s.e[%d.%d]\n", M,flag,k, parts[k][0], parts[k][1]);

		if (flag > 0)
		{
			lenL = PkLen;
			for (m = 0; m < lenL; m++)
			{
				localL[m] = Pk[m]; localLi[m] = Pki[m];
			}
		}
		else break;
	}
//    printf("->Max Partions %d\n",k);
	kmax[0] = k+1;
	myFree(localL); myFree(pk); myFree(Pk);
//	localL = (free(localL), NULL); pk = (free(pk), NULL); Pk = (free(Pk), NULL);
	free(Pki); free(localLi);
//	Pki = (free(Pki), NULL); localLi = (free(localLi), NULL);
	return parts;
}

int splitLin
(
	double* localL,
	int* localLi,
	double* pk,
	double* Pk,
	int* Pki,
	double* thold,
	int lenL,
	int* PkLen,
	int* pkLen
)
{
	double* newL;
	int* newLi;
	int m, k, i, ip, flag;
	newL = (double*)malloc(lenL * sizeof(double));
	newLi = (int*)malloc(lenL * sizeof(int));
	m = 0; k = 0;
	for (i = 0; i < lenL; i++)
	{
		if (fabs(localL[i] - thold[1]) > thold[0]) // THIS IS AN IMPORTANT BUG !! 18-07-2013 15:15 hrs
		{
			pk[k] = localL[i]; k = k + 1;
		}
		else { newL[m] = localL[i]; newLi[m] = localLi[i]; m = m + 1; }
	}
    //printf("->%d.%d\n",m,k);
	PkLen[0] = m; pkLen[0] = k;
	if (k == 0)
	{
		flag = -1;
		for (ip = 0; ip < lenL; ip++) pk[ip] = newL[ip];
		free(newL); free(newLi);
		return flag;
	}
	if (m == 0) { flag = -1; free(newL); free(newLi); return flag; }
	flag = 1;
	for (i = 0; i < lenL; i++) { Pk[i] = newL[i]; Pki[i] = newLi[i]; }


	free(newL); free(newLi);
	return flag;
}

int stdMuLin
(
	double* localL,
	double* sigma,
	double* mu,
	int lenL
)
{
	double sumB, sumA, sigmaA, muA;
	int i, flag = 1;
	switch (lenL)
	{
	case 0: printf("!. NULL DATA\n"); flag = -2; break;
	case 1: sigmaA = 0.0; muA = localL[0]; break;

	default:
		sumB = 0;
		for (i = 0; i < lenL; i++)
		{
			sumB = sumB + localL[i];
		}
		muA = sumB / (double)(lenL);
		if (fabs(sumB) < 1.0E-8) { printf(" Data may be zero %d %3.4f\n", lenL,fabs(sumB)); flag = -1; }
		else flag = 1;
		sumA = 0.0;
		for (i = 0; i < lenL; i++) sumA = sumA + (localL[i] - muA) * (localL[i] - muA);
		sigmaA = sqrt(sumA / (double)(lenL - 1));
		break;
	}
	if (flag > 0) { sigma[0] = sigmaA; mu[0] = muA; }
	return(flag);
}

