#include "stdafx.h"
#include "linDataSeg.h"
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
//#include "mex.h"   /* This one is required for MATLAB */
//	..... adding direction flag is a BIG FIX on 25th Aug 2023

int** getCloudPointers(double* frq, int lenFrq, int* numberOfRows, int N)
{
	int i, temp;
	int s, e;
	int** parts, ** partsUp, direction = 1;
	int maximumNumOfPartions = 15;
    double *frqTemp;
    frqTemp = myAlloc(lenFrq);
    //for (i=0; i<N; i++) frqTemp[i] = 0.0;
	for (i = 0; i < lenFrq; i++)
	{
		frqTemp[i] = frq[i]*(i+1);
	}

	direction = 1;
	parts = getCloudLinPt(frq, lenFrq, maximumNumOfPartions, numberOfRows, direction); 

//    for(i=0; i<numberOfRows[0]; i++) printf("[%3.4f %3.4f]\n",frq[parts[i][0]],frq[parts[i][1]] ); 

	temp = numberOfRows[0];
	direction = -1;
	partsUp = getCloudLinPt(frq, lenFrq, maximumNumOfPartions, numberOfRows, direction);

	if (temp < numberOfRows[0])
	{
		for (i = 0; i < numberOfRows[0]; i++)
		{
			s = partsUp[i][0]; e = partsUp[i][1];
			parts[i][0] = s;
			parts[i][1] = e;
		}
	}
	else numberOfRows[0] = temp;
    free(frqTemp);
	return parts;
}


int** getCloudLinPt(double* L, int lenD, int maximumNumOfPartions, int* kmax, int direction)
{
	double* localL;
	double* pk, * Pk;
	int* Pki, * localLi;
	double sigPk, muPk, thold[2];
	int k, lenL, PkLen, pkLen, i,m;
//	int k1, k2;
	int flag, flagA;
	int** parts{}, **temp{},s = 0, sOld = 0, e = 1, inPut = 0;
	int lastPt;
	int M = lenD;
	parts = (int**)malloc(maximumNumOfPartions * sizeof(int*));
	for (i = 0; i < maximumNumOfPartions; i++) parts[i] = (int*)malloc(2 * sizeof(int));
	temp = (int**)malloc(maximumNumOfPartions * sizeof(int*));
	for (i = 0; i < maximumNumOfPartions; i++) temp[i] = (int*)malloc(2 * sizeof(int));


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
//        printf("p.%d [%d] (%3.4f)-%3.4f %d\n",k,flagA,sigPk,muPk,lenL);
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
//	..... choose direction of partioning ...........
		flag = splitLin(localL, localLi, pk, Pk, Pki, thold, lenL, &PkLen, &pkLen,direction);

//	    printf(" [%d] How it is split %d = %d + %d\n", flag,lenL, pkLen, PkLen);
//		for (k1 = 0; k1 < pkLen; k1++) printf("%3.4f ",pk[k1]); printf("\n");
//		for (k2 = 0; k2 < PkLen; k2++) printf("%3.4f ",Pk[k2]); printf("\n");
		if (flag > 0) inPut = pkLen; else inPut = PkLen;


			sOld = s; s = s + inPut;
			parts[k][0] = sOld; parts[k][1] = s - 1;
//			printf("!. 1 {%d}[%d] %d data s.e[%d.%d]\n", M, flag, k, parts[k][0], parts[k][1]);
			if (PkLen == 0) parts[k][1] = parts[k][1] + lenL; // 25th Aug 2023

//			printf("!. 2 {%d}[%d] %d data s.e[%d.%d]\n", M, flag, k, parts[k][0], parts[k][1]);

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
	kmax[0] = k + 1;
//	free memory
	myFree(localL); myFree(pk); myFree(Pk);
	free(Pki); free(localLi);
//	... an important bug fix 26th Aug 2023
	if (direction < 0)
	{
		lastPt = parts[k][1];
		for (i = 0; i < kmax[0]; i++)
		{
			s = parts[i][0]; e = parts[i][1];
			temp[k - i][0] = lastPt - e;
			temp[k - i][1] = lastPt - s;
		}
		free(parts);
		return temp;
	}
	else { free(temp); return parts; }
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
	int* pkLen,
	int direction
)
{
	double* newL;
	int* newLi;
	int m, k, i, ip, flag;
	double sig, mu;
	int flagLess, flagGe,flagOn;
	double aboveMean;
	newL = (double*)malloc(lenL * sizeof(double));
	newLi = (int*)malloc(lenL * sizeof(int));
	sig = thold[0]; mu = thold[1];
	m = 0; k = 0;
	for (i = 0; i < lenL; i++)
	{
		aboveMean = fabs(localL[i] - mu);
		if (aboveMean < sig) flagLess = 1; else flagLess = -1;
		if (aboveMean >= sig) flagGe = 1;   else flagGe = -1;
		if (direction > 0) flagOn = flagLess; else flagOn = flagGe;

		if (flagOn > 0) // Oh My God what a bug it is 6th Aug 2023 10:17am at Dublin Ohio
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
