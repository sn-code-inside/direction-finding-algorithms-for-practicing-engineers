#include "stdafx.h"
#include "linDataSeg.h"
//#include "mex.h"   // This one is required for MATLAB 
//	..... adding direction flag is a BIG FIX on 25th Aug 2023
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
int** getCloudTotalPt(double* Range, int Mt, int maximumNumOfPartions, int* kmax)
{
	int i, flag, k, newK;
	int** parts, ** newParts, ** finalParts;
	int M = Mt;
	//	int maximumNumOfPartions = 15, maxI;
	double* range{}, stdmu[2];
	int maxI;
	double* std, max;

	range = (double*)malloc(M * sizeof(double));
	for (i = 0; i < M; i++) range[i] = Range[i];

	parts = getCloudLinPt(range, M, maximumNumOfPartions, kmax);
	std = myAlloc(kmax[0]);

	for (i = 0; i < kmax[0]; i++)
	{
		flag = lineCluster(parts[i][0], parts[i][1], range, M, stdmu);
		std[i] = stdmu[0];
		if (i == 0) {max = std[i]; maxI = i;}
		if (std[i] > max) { max = std[i]; maxI = i; }
		printf("[%d %d]->(%3.4f)\n", parts[i][0], parts[i][1], std[i]);
	}
//	printf("!.    maximum variance seg %3.4f[%d]\n", max, maxI);
	if (max > 0.1)
	{
		printf("!. row %d need to be further partioned\n", maxI);
		M = parts[maxI][1] - parts[maxI][0] + 1;
		for (i = 0; i < M; i++)
		{
			k = i + parts[maxI][0];
			range[i] = Range[k];
		}
		newParts = getCloudLinPt(range, M, maximumNumOfPartions, &newK);
		if (newK <= 1)
		{
			printf("!. This row %d couldnot be partioned\n", maxI);
			free(range); free(std);
			return parts;
		}
		finalParts = myAlloc2I(kmax[0] + newK - 1, 2); free(std);
		std = myAlloc(kmax[0] + newK - 1);
		for (i = 0; i < kmax[0]; i++)
		{
			if (i < maxI)
			{
				finalParts[i][0] = parts[i][0]; finalParts[i][1] = parts[i][1];
			}
			if (i == maxI)
			{
				for (k = 0; k < newK; k++)
				{
					finalParts[i + k][0] = newParts[k][0] + parts[maxI][0];
					finalParts[i + k][1] = newParts[k][1] + parts[maxI][0];
				}
			}
			if (i > maxI)
			{
				finalParts[i + newK - 1][0] = parts[i][0]; finalParts[i + newK - 1][1] = parts[i][1];
			}
		}
		M = Mt;
		for (i = 0; i < M; i++) range[i] = Range[i];
		for (i = 0; i < kmax[0] + newK - 1; i++)
		{
			printf("-->[%d %d]->", finalParts[i][0], finalParts[i][1]);
			flag = lineCluster(finalParts[i][0], finalParts[i][1], range, M, stdmu);
			std[i] = stdmu[0];
			printf("(%3.4f)\n",std[i]);
		}
		free(range); free(std);
		kmax[0] = kmax[0] + newK - 1;
		return finalParts;
	}

	free(range); free(std);
	return parts;
}


int** getCloudLinPt(double* L, int lenD, int maximumNumOfPartions, int* kmax)
{
	double* localL;
	double* pk, * Pk;
	int* Pki, *pki, * localLi;
	double sigPk, muPk, thold[2];
//	double PkSig,pkSig;
	int k, lenL, PkLen, pkLen, i,m;
//	int k1;
	int flag=1, flagA=1;
//	int** parts{}, ** temp{}, s = 0, sOld = 0, e = 1, inPut = 0;
	int** parts{}, s = 0, sOld = 0, e = 1, inPut = 0;
//	int lastPt;
	int M = lenD;
	parts = myAlloc2I(maximumNumOfPartions, 2);

	lenL = M;
	localL = myAlloc(lenL); localLi = myAllocI(lenL);
	pk = myAlloc(lenL); Pk = myAlloc(lenL);
	pki = myAllocI(lenL); Pki = myAllocI(lenL);


	for (i = 0; i < M; i++)
	{
		localL[i] = L[i]; localLi[i] = i;
	}

	for (k = 0; k < maximumNumOfPartions; k++)
	{

//	.... mean and std of P_k-1 
		flagA = stdMuLin(localL, &sigPk, &muPk, lenL);
//		printf("p.%d [%d] (%3.4f)-%3.4f %d\n", k, flagA, sigPk, muPk, lenL);
//		printf("!. p.%d [%d] (%3.4f) %d\n", k, flagA, sigPk,lenL);
		if (flagA == -2)
		{
	   		printf(" p.%d\n  NULL DATA\n",k);
            if (k == 0)
            {
			    parts[k][0] = -1; parts[k][1] = -1;
				myFree(localL); myFree(pk); myFree(Pk);
				free(Pki); free(pki);  free(localLi);
			    return NULL;
            }
		}

//	.... partition into p_k and P_k using std of (P_k-1)
		thold[0] = sigPk; thold[1] = muPk;
//	..... Use variance of input array before split ...........
//		for (k1 = 0; k1 < lenL; k1++) printf("%3.4f ", localL[k1]); printf("\n");
		flag = 1;
//		if (sigPk < 0.001)
		if (sigPk < 0.1)
			{
			flag = -1;
			printf("[%d] NO NEED to Split the array --->%3.4e\n", flag,sigPk);
			pkLen = lenL; 
			PkLen = 0; Pk[0] = 0.0;
			for (i = 0; i < lenL; i++)
			{
				pk[i] = localL[i]; pki[i] = localLi[i]; 
			} 
			parts[k][0] = pki[0];  parts[k][1] = pki[pkLen-1];
		}
		else
		{
			flag = splitLin(localL, localLi, pk, pki, Pk, Pki, thold, lenL, &PkLen, &pkLen);
			if (flag < 0)
			{
				parts[k][0] = Pki[0];  parts[k][1] = Pki[PkLen - 1];
			}
			else parts[k] = ExchangEpkandPk(Pk, Pki, &PkLen, pk, pki, &pkLen);
		}
//		printf(" [%d] How it is split %d = %d + %d\n", flag, lenL, pkLen, PkLen);
//		for (k1 = 0; k1 < pkLen; k1++) printf("%3.4f ", pk[k1]);
//		printf("[%d]-->[%d %d]\n", k,parts[k][0], parts[k][1]);
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
	sortInd(parts, kmax[0]);
//	free memory
	myFree(localL); myFree(pk); myFree(Pk);
	free(Pki); free(pki);  free(localLi);
//	printf("!. Number of rows [%d]%d\n", flag, kmax[0]);
	return parts;
}

void sortInd(int** parts, int rows)
{
	int i, **temp,*indx;
	double* s;
	s = myAlloc(rows);
	temp = myAlloc2I(rows, 2);

	for (i = 0; i < rows; i++) s[i] = (double)(parts[i][0]);
	indx = Low2High(rows, s);
	for (i = 0; i < rows; i++)
	{
		temp[i][0] = parts[indx[i]][0];
		temp[i][1] = parts[indx[i]][1];
	}
	for (i = 0; i < rows; i++)
	{
		parts[i][0] = temp[i][0];
		parts[i][1] = temp[i][1];
	}
	myFree2I(temp, rows);
	free(s);
	return;
}

int * ExchangEpkandPk(double *Pk, int *Pki, int *PkLen, double *pk, int *pki, int *pkLen)
{
	int  *tempInd,Len,er,*pt;
	int i, k1=0, k2=0;
	double* temp;
	double pkSig, PkSig, mu;
	er = stdMuLin(pk, &pkSig, &mu, pkLen[0]); pkSig = pkSig / fabs(mu);
	er = stdMuLin(Pk, &PkSig, &mu, PkLen[0]); PkSig = PkSig / fabs(mu);
	if (pkLen[0] > PkLen[0]) Len = pkLen[0]; else Len = PkLen[0];
	temp = myAlloc(Len); tempInd = myAllocI(Len); pt = myAllocI(2);
//	temp = (double*)malloc(Len * sizeof(double));
//	tempInd = (int*)malloc(Len * sizeof(int));
//	pt = (int*)malloc(2 * sizeof(int));
	if (pkSig > PkSig)
	{
		for (i = 0; i < pkLen[0]; i++) { temp[i] = pk[i]; tempInd[i] = pki[i]; } // pk -> temp
		for (i = 0; i < PkLen[0]; i++) { pk[i] = Pk[i]; pki[i] = Pki[i]; }     // Pk -> pk
		for (i = 0; i < pkLen[0]; i++) { Pk[i] = temp[i]; Pki[i] = tempInd[i]; } // temp -> Pk
		Len = pkLen[0];  pkLen[0] = PkLen[0]; PkLen[0] = Len; // exchange pkLen and PkLen
	}
	pt[0] = pki[0]; pt[1] = pki[pkLen[0] - 1];

	free(temp); free(tempInd);
	return pt;
}

int splitLin
(
	double* localL,
	int* localLi,
	double* pk,
	int *pki,
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
	double sig, mu;
//	int flagLess, flagGe,flagOn;
	double aboveMean;
	newL = (double*)malloc(lenL * sizeof(double));
	newLi = (int*)malloc(lenL * sizeof(int));
	sig = thold[0]; mu = thold[1];
	m = 0; k = 0;

	for (i = 0; i < lenL; i++)
	{
		aboveMean = fabs(localL[i] - mu);

//		Oh My God what a bug it is 6th Aug 2023 10:17am at Dublin Ohio
//		but this kicked into many bugs all fixed on 3rd Oct 2023 at Princeton NJ
//		if (aboveMean >= sig)
		if (aboveMean > sig)
		{
			pk[k] = localL[i]; pki[k] = localLi[i];
			k = k + 1;
		}
		else { newL[m] = localL[i]; newLi[m] = localLi[i]; m = m + 1; }
	}
//printf("->%d.%d\n",m,k);
	PkLen[0] = m; pkLen[0] = k;
	if (k == 0)
	{
		flag = -1;
		for (ip = 0; ip < lenL; ip++)
		{
			pk[ip] = newL[ip];
			pki[ip] = newLi[ip];
		}
		free(newL); free(newLi);
		return flag;
	}
	if (m == 0) { flag = -1; free(newL); free(newLi); return flag; }
	flag = 1;
	for (i = 0; i < lenL; i++) { Pk[i] = newL[i]; Pki[i] = newLi[i]; }


	free(newL); free(newLi);
	return flag;
}
