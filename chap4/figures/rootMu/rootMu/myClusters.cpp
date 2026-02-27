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
#include "myClusters.h"
//#include "mex.h"   
extern FILE* fp;
double** segment(double *inputData, int* rcClouds,int lenD, int maxNumberOfPartitions, double closenessFactor)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	int kmax = 8, k, newrows;
	int** pointers, ** newParts;
	int* indx,er;
	double ** clouds,**newClouds;
	double* localData;
	indx = myAllocI(lenD); localData = myAlloc(lenD);
	for (k = 0; k < lenD; k++) localData[k] = inputData[k];

	printf("input data\n");
	printf("P_{0}[");
	for (k = 0; k < lenD; k++)
	{
		printf( "%3.4f ", localData[k]);
	} printf( "]\n");

	indx = sortData(localData, lenD);
	fprintf(fp, "\\begin{center} \n \\begin{enumerate} \n");
	pointers = getCloudTotalPt(localData, lenD, maxNumberOfPartitions, &kmax);
	rcClouds[0] = kmax;
	printf("            size of pointers rows %d columns 2\n", kmax);
	printf("            End getCloudTotalPt \n");
	for (k = 0; k < kmax; k++) printf("            [%d] %d %d\n", k, pointers[k][0], pointers[k][1]);
	clouds = pointers2clouds(pointers, rcClouds, localData, lenD);
	newParts = CompactClouds(clouds, rcClouds, &newrows, closenessFactor);
	if (newParts != NULL)
	{
		printf("            Compacting is Effective\n");
		rcClouds[0] = newrows;
		clouds = pointers2clouds(newParts, rcClouds, localData, lenD);
		newClouds = mapClouds(clouds, rcClouds, lenD);
		fprintf(fp, "\\end{enumerate} \n \\end{center}\n");
		return newClouds;
	}
	else 
	{ 
		printf("            Compacting Clouds has no effect\n");
		newClouds = mapClouds(clouds, rcClouds, lenD);
		fprintf(fp, "\\end{enumerate} \n");
	}

	free(localData); free(indx);
	return newClouds;
}

double** mapClouds(double **clouds,int* rcClouds, int lenD)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	double** newClouds;
	int k,s,e,snew,enew;
	printf("            rows %d cols %d\n", rcClouds[0], rcClouds[1]);
	newClouds = myAlloc2(rcClouds[0], rcClouds[1]);

	for (k = 0; k < rcClouds[0]; k++)
	{
		s = (int)(clouds[k][0]); e = (int)(clouds[k][1]);
		snew = lenD - 1 - e; enew = lenD - 1 - s;
	//	fprintf(fp,"%d %d\n", snew, enew);
		newClouds[k][0] = (double)(snew)+1;
		newClouds[k][1] = (double)(enew)+1;
		newClouds[k][2] = clouds[k][2];
		newClouds[k][3] = clouds[k][3];
	}

	return newClouds;
}


int* sortData(double* range, int M)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	int k, i = 0, kmax,  * ind;
	sort bins;
	ind = myAllocI(M);
	for (k = 0; k < M; k++) ind[k] = k;

	bins.x = range; bins.xI = ind; bins.M = M;
	bins.High2Low();
	kmax = M;
	return ind;
}


double** formClouds(double* A, int rcA, int* rcClouds, double coupling)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	int ip = 0, kmax=0, newrows;
	int** parts{}, ** newParts;
	double** clouds, ** cloudsNew;

	//parts = getCloudPointers(A, rcA, &kmax);
	rcClouds[0] = kmax; rcClouds[1] = 6;
	clouds = pointers2clouds(parts, rcClouds, A, rcA);
	//	newParts = CloseClouds(clouds, rcClouds, &newrows);
	newParts = CompactClouds(clouds, rcClouds, &newrows, coupling);
	if (newParts != NULL)
	{
		rcClouds[0] = newrows; rcClouds[1] = 6;
		cloudsNew = pointers2clouds(newParts, rcClouds, A, rcA);
		return cloudsNew;
	}
	else
	{
		return clouds;
	}
}




int** CompactClouds(double** clouds, int* rcClouds, int* newr, double coupling)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	double* muk{}, er;
	int s, e,indxMu;
	double  maxMu;
	int k, r, c, kt, flag = 0;
	int** ptsN{}, ** newParts{};

	r = rcClouds[0]; c = rcClouds[1];
	printf("            Compact Pointers (%d rows  %d cols)\n", r, c);
	muk = myAlloc(r);
	ptsN = myAlloc2I(r, 2);

	//	ptsN = (int**)malloc(r * sizeof(int*));
	//	for (k = 0; k < r; k++) ptsN[k] = (int*)malloc(2 * sizeof(int));

	for (k = 0; k < r; k++)
	{
		s = (int)(clouds[k][0]); e = (int)(clouds[k][1]);
//		x = clouds[k][3]; y = clouds[k][5];

		ptsN[k][0] = s; ptsN[k][1] = e;
		muk[k] = clouds[k][3];
		printf("            [row %d] [start To end] [%d %d] - muK %3.4f\n", k,s, e,muk[k]);
	}
	//	kt = 0;
	flag = 1;
	indxMu = myMax(muk, r); maxMu = muk[indxMu];
	for (k = 0; k < r-1; k++) 
	{
		er = distMeasure(muk[k], muk[k + 1],maxMu);
		printf("            er %3.4f coupling %3.4f\n", er, coupling);
		if (er < coupling)  // important parameter
		{
			merge(ptsN, k, r);
			flag = -1;
		}
	//	else kt = 0;
		printf("            [flag %d] (%d %d)\n", flag, ptsN[k][0], ptsN[k][1]);
	}
	if (flag > 0)
	{
		myFree2I(ptsN, r); free(muk);
		return NULL;
	}
	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] < 0) kt = kt + 1;
	}
	newr[0] = r - kt;
	printf("            int** CompactClouds(r[%d] -> newr[%d])\n", r, newr[0]);


	newParts = (int**)malloc(newr[0] * sizeof(int*));
	for (k = 0; k < newr[0]; k++) newParts[k] = (int*)malloc(2 * sizeof(int));
	printf("            Final Compacted\n");
	kt = 0;
	for (k = 0; k < r; k++)
	{
		if (ptsN[k][0] >= 0)
		{
			newParts[kt][0] = ptsN[k][0];
			newParts[kt][1] = ptsN[k][1];
			printf("            [%d] %d  %d\n", kt, newParts[kt][0], newParts[kt][1]);
			kt = kt + 1;
		}
	}
	myFree2I(ptsN, r); free(muk);
	//	for (k = 0; k < r; k++) { free(ptsN[k]); ptsN[k] = NULL; }
	//	free(ptsN);

	return newParts;
}






/* void pause(int dur)
{
//	pause in dur seconds
	int temp = (int)(time(NULL)) + dur;
	while (temp > time(NULL));
	return;
}*/


void merge(int** ptsN, int k, int r)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	if (k < r)
	{
		ptsN[k + 1][0] = ptsN[k][0];
		ptsN[k][0] = -1; ptsN[k][1] = -1;
	}
	else
	{
		fprintf(fp, "last\n");
	}
	return;
}


double distMeasure(double x, double y,double maxMu)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	double d,er;
	d = abs(x - y);
	er = d / maxMu;
//	if (x > y) er = d / x; else er = d / y;
//	printf("measure %3.4f\n", er);
	return er;
}


double** pointers2clouds(int** parts, int* rcClouds, double* A, int M)
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
	double** clouds{};
	double* x;
	int s = 0, sOld = 0, e = 1, ePlus1 = 0, inPut = 0, kmax = 0, kt = 0;
	int k,  ip = 0;
	double* stdmu;

	int flag;

	printf("            double** pointers2clouds(%d %d)\n", rcClouds[0], rcClouds[1]);
	x = myAlloc(M); stdmu = myAlloc(2);

	kmax = rcClouds[0];
	clouds = myAlloc2(kmax, rcClouds[1]);
	for (k = 0; k < M; k++)  x[k] = A[k]; 
	fprintf(fp, "\\item \\begin{tabular}{ | p{15cm} | }\\hline \n");
	for (ip = 0; ip < kmax; ip++)
	{
		s = parts[ip][0];   e = parts[ip][1];
		clouds[ip][0] = s;  clouds[ip][1] = e;
		flag = lineCluster(s, e, x, M, stdmu);
	//for (k = s; k < e; k++) fprintf(fp,"%3.4f ", x[k]); printf("\n");
	//fprintf(fp,"            [%d] print x[%d - %d]\n", ip,s, e);;
	//fprintf(fp,"            [start %d  end %d] -> sigr %3.4f meanr %3.4f\n", s, e, stdmu[0], stdmu[1]);
		if (flag < 0)
		{
			for (k = 2; k < rcClouds[1]; k++) clouds[ip][k] = 0.0;
		}
		else { clouds[ip][2] = stdmu[0]; clouds[ip][3] = stdmu[1]; }
		fprintf(fp, "            [%d] $P_0$[%d.%d]\t", ip, (int)(clouds[ip][0]), (int)(clouds[ip][1]));
		fprintf(fp, "[$\\sigma$ %3.4f\t$\\mu$ %3.4f]\n", clouds[ip][2], clouds[ip][3]);
		if (flag < 0) rcClouds[0] = rcClouds[0] - 1; // new bug
	}
	fprintf(fp, "\\\\ \\hline \n\\end{tabular}\\\\ \\vspace{3mm}\n\n");
	free(x); ;
	return clouds;
}


/* double** createSceneMatrix(int* rcSene, double** cluster)
{
	int k,ktCluster,cols;
	double xmu, ymu, delx, dely, rad2deg, pi;
	double** Scene;
	ktCluster = rcSene[0]; cols = rcSene[1];
	Scene = myAlloc2(ktCluster, cols);
	pi = atan(1.0) * 4.0; rad2deg = 180.0 / pi;
	printf("!. Scene Matrix\n");
	for (k = 0; k < ktCluster; k++)
	{
		xmu = cluster[k][4]; ymu = cluster[k][6];
		delx = cluster[k][3]; dely = cluster[k][5];
		Scene[k][0] = sqrt(xmu * xmu + ymu * ymu);
		Scene[k][1] = atan(xmu / ymu) * rad2deg;
		Scene[k][2] = sqrt(delx * delx + dely * dely);
		if (isnan(Scene[k][2])) Scene[k][2] = 0.0;
		Scene[k][3] = atan(delx / dely) * rad2deg;
		if (isnan(Scene[k][3])) Scene[k][3] = 0.0;
	}
	return Scene;
}*/

/*double** clouds2cluster(int* rcClouds, double** clouds, int MaxNumOfRowsCluster, int* kt)
{
	int k, i, ip, ktCluster;
	double** cluster;
	cluster = myAlloc2(MaxNumOfRowsCluster, rcClouds[1] + 1);
	ktCluster = kt[0];
	printf("!. integer matrix chi with pointers\n");
	for (k = 0; k < rcClouds[0]; k++)
	{
		cluster[ktCluster][0] = k;
		for (i = 0; i < rcClouds[1]; i++)
		{
			cluster[ktCluster][i + 1] = clouds[k][i];
		}
		for (ip = 1; ip < rcClouds[1] - 3; ip++) printf("%d\t", (int)(cluster[ktCluster][ip]));
		printf("\n");
		ktCluster = ktCluster + 1; kt[0] = ktCluster;
		if (ktCluster > MaxNumOfRowsCluster) break;
	}
	return cluster;
}*/

char* getDate()
{
	//  Copyright (c) 2025 Kaluri V. Ranga Rao
		//	......... local time ...................................
	int er;
	time_t now;
	struct tm bufT {};
	char* dtNtime;
	dtNtime = (char*)malloc(60 * sizeof(char));

	now = time(NULL);
	er = localtime_s(&bufT, &now);
	er = asctime_s(dtNtime, 60, &bufT);
	return dtNtime;
}

