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

//#include "mex.h"   // This one is required for MATLAB 
//	..... adding direction flag is a BIG FIX on 25th Aug 2023
extern FILE* fp;
int** getCloudTotalPt(double* Range, int Mt, int maximumNumOfPartions, int* kmax)
{
	int i, flag, k, newK;
	int** parts{}, ** newParts{}, ** finalParts{};
	int M = Mt;
	//	int maximumNumOfPartions = 15, maxI;
	double* range{}, stdmu[2];
	int maxI=0;
	double* std, max=-1;
	int callNumber = 1;

	//range = (double*)malloc(M * sizeof(double));
	range = myAlloc(M);
	printf("Sorted Data For Partition - START\n");
//	fprintf(fp, "P_{-1}[");
	for (i = 0; i < M; i++)
	{
		range[i] = Range[i];
//		fprintf(fp, "%3.4f ", range[i]);
	} //fprintf(fp, "]\n");
	parts = getCloudLinPt(range, M, maximumNumOfPartions, kmax, callNumber); callNumber = callNumber + 1;
	if (parts == NULL) { fprintf(fp, "output is NULL\n"); getchar(); }
	std = myAlloc(kmax[0]);
	fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline \n");
	for (i = 0; i < kmax[0]; i++)
	{
		flag = lineCluster(parts[i][0], parts[i][1], range, M, stdmu);
		std[i] = stdmu[0];
		if (i == 0) {max = std[i]; maxI = i;}
		if (std[i] > max) { max = std[i]; maxI = i; }
		fprintf(fp, "            [%d] $\\sigma(P_0($[%d %d])$\\rightarrow$(%3.4f)\n", i,parts[i][0], parts[i][1], std[i]);
	}
	fprintf(fp, "            \\\\ maximum variance seg %3.4f[%d]\n", max, maxI);
	if (max > 0.1)
	{
		fprintf(fp, "            row %d need to be further partioned \\\\ \n", maxI);
		fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
		M = parts[maxI][1] - parts[maxI][0] + 1;
		for (i = 0; i < M; i++)
		{
			k = i + parts[maxI][0];
			range[i] = Range[k];
		}
		newParts = getCloudLinPt(range, M, maximumNumOfPartions, &newK,callNumber); callNumber = callNumber + 1;
		if (newK <= 1)
		{
			printf("            This row %d couldnot be partioned\n", maxI);
			free(range); free(std);
			return parts;
		}

		finalParts = myAlloc2I(kmax[0] + newK - 1, 2); free(std);
		std = myAlloc(kmax[0] + newK - 1);
		for (i = 0; i < kmax[0]; i++)
		{
			if (i < maxI)
			{
				finalParts[i][0] = parts[i][0]; 
				finalParts[i][1] = parts[i][1];
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
//			printf("[%d] before -->[%d %d]->\n", i,finalParts[i][0], finalParts[i][1]);
			flag = lineCluster(finalParts[i][0], finalParts[i][1], range, M, stdmu);
			std[i] = stdmu[0];
			fprintf(fp, "            [row %d] [%d %d] (%3.4f)\n", i,finalParts[i][0], finalParts[i][1],std[i]);
		}
		fprintf(fp, "            End of First Phase\n\n");
		free(range); free(std);
		kmax[0] = kmax[0] + newK - 1;
		return finalParts;
	}

	free(range); free(std);
	return parts;
}


int** getCloudLinPt(double* L, int lenD, int maximumNumOfPartions, int* kmax, int callNumber)
{
	double* localL;
	double* pk, * Pk;
	int* Pki, *pki, * localLi;
	double sigPk, muPk, thold[2] = { 1,1 };
//	double PkSig,pkSig;
	int k, lenL, PkLen, pkLen, i,m;
	int kpk, kPk;
	int flag = 1, flagA = 1, breakFlag = 1;
//	int** parts{}, ** temp{}, s = 0, sOld = 0, e = 1, inPut = 0;
	int** parts{}, s = 0, sOld = 0, e = 1, inPut = 0;
	int** splits{};
//	int lastPt;
	int M = lenD;
	parts = myAlloc2I(maximumNumOfPartions, 2);
	splits = myAlloc2I(M, 4);
	printf("            Maximum Number of Partitions %d\n", maximumNumOfPartions);

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
// 
		
		
			
		fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline\\{$P_{%d}$\\} ",k);
		if (k == 0)
		{
			if (callNumber == 1) fprintf(fp, "Initial Set of Normalized Eigen Values \\\\ \n");
		} else fprintf(fp, "Eigen Values \\\\ \n");
		fprintf(fp,"\{$P_{%d}$\}=\\{",k); for (kPk = 0; kPk < lenL; kPk++) fprintf(fp, "%3.4f ", localL[kPk]);

		if (k == 0)
		{
			if (callNumber == 1) fprintf(fp, "\\} Initial Set \\\\ \n");
		}
		else fprintf(fp, "\\} as in equation \\ref{eq:4_22} \\\\ \n");

		flagA = stdMuLin(localL, &sigPk, &muPk, lenL);
		fprintf(fp, "            $P_{%d}$ (flag %d) ($\\sigma_{%d}$ %3.4f) ($\\mu_{%d}$ %3.4f) split \\{%d\\} \\\\ \n", k, flagA, k,sigPk, k,muPk, lenL);
		fprintf(fp, "$P_{%d}-\\mu_{%d}$ = [ ", k,k);
		for (kPk = 0; kPk < lenL; kPk++) fprintf(fp, "%3.4f ", (localL[kPk] - muPk)); 
		fprintf(fp, "]  \\\\ \n");
		//printf("            print pk[0 - %d]\n",pkLen);
		//fprintf(fp, "            row %d-->[%d %d] \\\\ \n", k, parts[k][0], parts[k][1]);
		fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
		if (flagA == -2)
		{
			fprintf(fp, " p.%d\n  NULL DATA\n",k);
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
//		printf("[%d] print localL[0 - %d]\n",k,lenL);
		flag = 1;
//		if (sigPk < 0.001)
		if (sigPk < 0.1)
		{
			flag = -1;
			printf("            [%d] NO NEED to Split the array --->%3.4f\n", flag,sigPk);
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
		fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline\\{$P_{%d}$\\} \n", k);
		fprintf(fp, "            (flag %d) How it is split %d = \\{$p_{%d}$\\}%d + \\{$P_{%d}$\\}%d\\\\ \n", flag, lenL, k+1,pkLen, k+1,PkLen);
		splits[k][0] = flag; splits[k][1] = lenL; splits[k][2] = pkLen; splits[k][3] = PkLen;
		fprintf(fp, "$p_{%d}$=\\{ ",k+1);
		for (kpk = 0; kpk < pkLen; kpk++) fprintf(fp, "%3.4f ", pk[kpk]); 
		fprintf(fp, "\\} as in equation \\ref{eq:4_21} \\\\ \n");
//		fprintf(fp, "P_{%d}[ ",k);
//		for (kPk = 0; kPk < PkLen; kPk++) fprintf(fp, "%3.4f ", Pk[kPk]); fprintf(fp, "]\n");

		
		//for (kpk = 0; kpk < pkLen; kpk++) fprintf(fp, "\\|P_{%d}-\\mu\\| =",k);
		if (flag > 0)
		{
//			fprintf(fp, "$\\|P_{%d}-\\mu\\|$ = [ ", k+1);
//			for (kPk = 0; kPk < PkLen; kPk++) fprintf(fp, "%3.4f ", fabs(Pk[kPk]) - muPk); fprintf(fp, "] \\\\ \n");
			//printf("            print pk[0 - %d]\n",pkLen);
			fprintf(fp, "            $\\chi$(%d) $\\longrightarrow~~P_{0}$([%d %d]) \\\\ \n", k, parts[k][0], parts[k][1]);
			fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
			lenL = PkLen; 
			for (m = 0; m < lenL; m++)
			{
				localL[m] = Pk[m]; localLi[m] = Pki[m];
			}
		}
		else { 
			fprintf(fp, "            break loop \\\\ \n"); 
			fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
			breakFlag = -1;	 break; 
		}
	}
//	kmax[0] = k + 1;
	if (breakFlag > 0) kmax[0] = k; else kmax[0] = k + 1;// bug fix on 9th Jan 2025 at Hyderabad
	if (kmax[0] < 2) 
	{ 
		myFree(localL); myFree(pk); myFree(Pk);
		free(Pki); free(pki);  free(localLi);
		fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline\\{$P_{%d}$\\} \n", k);
		fprintf(fp, "            There is Only One Row [flag %d]%d\n", flag, kmax[0]);
		fprintf(fp, "            End of Phase %d(%d) \\\\ \n\n", callNumber,lenD);
		fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
		return parts;
	}
	fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline\\{$P_{%d}$\\} \n", k);
	fprintf(fp, "            Number of Rows %d\n", kmax[0]);
//	for (k = 0; k < kmax[0]; k++) printf("[%d  %d]\n", parts[k][0], parts[k][1]);
	fprintf(fp, "            sorted on 1st column\n");
	sortInd(parts, kmax[0]);
	parts[0][1] = parts[1][0] - 1; 
	if (flag > 0)
	{
		if (kmax[0] > 2)
		{
			parts[k - 1][1] = lenD - 1;
			parts[0][1] = parts[1][0] - 1;
		}
	}
	for (k = 0; k < kmax[0]; k++) fprintf(fp,"            [%d  %d] ", parts[k][0], parts[k][1]);
	fprintf(fp, "\\\\ \n");
//	fprintf(fp,"end of getCloudLinPt\n"); getchar();
	//	free memory
	myFree(localL); myFree(pk); myFree(Pk);
	free(Pki); free(pki);  free(localLi); free(splits);
	fprintf(fp, "            Number of rows [flag %d]%d\n", flag, kmax[0]);
	fprintf(fp, "            End of Phase %d(%d) \\\\ \n\n", callNumber, lenD);
	fprintf(fp, "\\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
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
//	newL = (double*)malloc(lenL * sizeof(double));
	newL = myAlloc(lenL); newLi = myAllocI(lenL);
//	newLi = (int*)malloc(lenL * sizeof(int));
	sig = thold[0]; mu = thold[1];
	m = 0; k = 0;

	for (i = 0; i < lenL; i++)
	{
//		aboveMean = fabs(localL[i] - mu);
		aboveMean = (localL[i] - mu);

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
	printf("            [PkLen %d  pkLen %d]\n",m,k);
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
