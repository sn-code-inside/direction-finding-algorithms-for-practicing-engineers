#include "stdafx.h"
#include "saveDataFiles.h"
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
//#include "mex.h"
int capture(int block, int flag,int k)
{
	static int flgOpen = 0;
	if (block == flag)
	{
		if (k == 0) 
		{
			printf("!. Opening files at %d.%d\n", block, k);
			flgOpen = 1;
			fopen_s(&fpW, "rangeSpk.csv", "w");    	 fopen_s(&fpCy, "phase.csv", "w");
//			printf("open files %d\n",flgOpen); 
		}
		fprintf(fpLog,"!. --->Capture rangeSpk.csv and phase.csv onto files at [%d][%d]\n", block, k);
	}
	else
	{
		if (flgOpen == 1)
		{
			fclose(fpW); fclose(fpCy);
//			printf("close files\n"); 
			flgOpen = -1;
			fprintf(fpLog,"!. Closing files at %d.%d\n", block, k);
		}
	}
	return flgOpen;
}

void writeFileUnsort(int* rcDf, double** Df, double* config)
{
	int k, i, rows, pf = 0;
	double pi, deg2rad, r = 1.0;
	pi = atan(1.0) * 4.0; deg2rad = pi / 180.0;
	//	if (MATLAB == 1) rows = rcDf[0] - 2; else 
	rows = rcDf[0];
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rcDf[1]; k++)
		{
			if (k != 1)
			{
				fprintf(fpUnSortCluster, "%3.4f ,", Df[i][k]);
			}
			else
			{
				r = Df[i][k] * config[11];
				fprintf(fpUnSortCluster, "%3.4f ,", r);
			}
		}
		fprintf(fpUnSortCluster, "%3.4f ,", r * sin(Df[i][3] * deg2rad));
		fprintf(fpUnSortCluster, "%3.4f ,", r * cos(Df[i][3] * deg2rad));
		fprintf(fpUnSortCluster, "\n");

	}
	fprintf(fpUnSortCluster, "\n");
	return;
}

void writeFile(int* rcDf, double** Df)
{
	int k, i, rows;
	//		if (MATLAB == 1) rows = rcDf[0] - 2; else 
	rows = rcDf[0];
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rcDf[1]; k++)
		{
			fprintf(fpSortCluster, "%3.4f ,", Df[i][k]);
		}
		fprintf(fpSortCluster, "\n");

	} fprintf(fpSortCluster, "\n");
	return;
}



void writeFileNconsole(int* rcClouds, double** clouds)
{
	int i, k, oldk = 0, diff;

	for (i = 0; i < rcClouds[0]; i++)
	{
		diff = (int)(clouds[i][0]) - oldk;
		oldk = (int)(clouds[i][0]);
		if (diff == 1)
		{
			fprintf(fpClouds, "-1 ,");
			for (k = 1; k < rcClouds[1]; k++) fprintf(fpClouds, "0.0 ,");
			fprintf(fpClouds, "\n");
		}

		for (k = 0; k < rcClouds[1]; k++)
		{
			fprintf(fpClouds, "%3.4f ,", clouds[i][k]);
			printf("%3.4f ", clouds[i][k]);
		}   fprintf(fpClouds, "\n"); printf("\n");

	}

	return;
}

int openCSVfiles()
{
	int er;
    printf("!. opening of .csv file\n");
	fprintf(fpLog,"!. opening of files C.csv D.csv unsort.csv CMP.csv\n");
	er = fopen_s(&fpSortCluster, "D.csv", "w");
	if (er != 0) { printf("!. Failed to open file D.csv\n");   return -1; }

	er = fopen_s(&fpClouds, "C.csv", "w");
	if (er != 0) { printf("!. Failed to open file C.csv\n");    return -1; }
	//		update on 22nd Aug 2023 for paper @ Dublin Ohio
	er = fopen_s(&fpUnSortCluster, "unsort.csv", "w");
	if (er != 0) { printf("!. Failed to open file unsort.csv\n");   return -1; }
	er = fopen_s(&fpKMUandGmu, "kMuGmu.csv", "w");
	if (er != 0) { printf("!. Failed to open file cmp.csv\n");    return -1; }
	//	printf("!. DATA files will have only D=data,C=cloud for MATLAB use\n");
	fprintf(fpLog, "\n\n!. DATA files will have only D=data,C=cloud for MATLAB use\n\n");
	fprintf(fpLog, "data columns [indx bin range kDoa muDoa X Y]\n");
	fprintf(fpLog, "clouds [indx start end sigmaX muX sigmaY muY]\n");
	return 1;
}

int closeAllFile()
{
	//	closing all the files ..
	//
	int er = 0;
	printf("!. closing all files\n");
	if (fp != NULL) fclose(fp);                           else er = -5;
	if (fpSortCluster != NULL) fclose(fpSortCluster); 	  else er=-1;
	if (fpClouds != NULL) fclose(fpClouds); 	          else er = -2;
	if (fpLog != NULL) 	fclose(fpLog);	                  else er = -3;;
	//	update on 28th Jun 2023 for paper
	if (fpUnSortCluster != NULL) fclose(fpUnSortCluster); else er = -4;
	if (fpKMUandGmu != NULL) 
	{ 
		fclose(fpKMUandGmu); 
		if (er < 0)
			printf("!. only %d files were close\n", abs(er));			
		else printf("!. closing all files err %d\n",er);
		return er;
	}
	else return er;
}

void traceData(double* sAvg, double** phSpk, double** muSpk, int rows, int numberOfTgts, int numOfPhaseSpecSamples)
{
	int ind, i, k;
	for (ind = 0; ind < rows; ind++)
		fprintf(fpW, "%3.4f, ", sAvg[ind]); fprintf(fpW, "\n");
	for (i = 0; i < numberOfTgts; i++)
	{
		for (k = 0; k < numOfPhaseSpecSamples; k++)
			fprintf(fpCy, "%3.4f ,", phSpk[i][k]); fprintf(fpCy, "\n");
		for (k = 0; k < numOfPhaseSpecSamples; k++)
			fprintf(fpCy, "%3.4f ,", muSpk[i][k]); fprintf(fpCy, "\n");
	}
	return;
}

void writeScene(double** Scene, int ktCluster)
{
	int k, ip;
	for (k = 0; k < ktCluster; k++)
	{
		for (ip = 0; ip < 4; ip++)
		{
			printf("%3.2f\t", Scene[k][ip]);
			fprintf(fpClouds, "%3.4f ,", Scene[k][ip]);
		} printf("\n"); fprintf(fpClouds, "\n");
	}
	return;
}
