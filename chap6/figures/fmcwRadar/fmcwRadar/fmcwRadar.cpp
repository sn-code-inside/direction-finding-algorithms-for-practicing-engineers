// fmcwRadar.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 2nd May 2025 11am @ Dublin .. kaluri@ieee.org
// brought from perception engine for the book
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
#include "fmcwRadar.h"
int main(int argc, char** argv)
{
	int er;
	er = mainLocal(argc, argv);
	printf("!. Error Code mainLocal %d\n", er);  getchar();
	if (er < 0)
	{
		printf("!. Error Code  %d ", er); er = abs(er);
		switch (er)
		{
		case 101:
			printf("synthetic data file is not open but trying to close\n");
			break;
		case 2:
			printf("could not open the file\n");
			break;
		case 12:
			printf("end of data in data file\n");
			break;
		default:
			printf("yet to classify the error -%d\n", er);
			break;
		}
	}
	return 1;
}



int mainLocal(int argc, char** argv)
{
	int rc[2], er = 1, Er = 1, cby2;
	int maxLengthOfFileName = 80, Len = 100;
	char* datafile; //* fileNew, * fileCloud{}, * fileTemp{}; 
	char* LogFile;
	double* config;
	double rgain = 0, bins2range = 1.0;
	int control, synthetic, numberOfTgts, numOfPhaseSpecSamples;
	int FFTsamples = 512, NumOfColumns = 4;
	int blocks = 0, cols = 0, rows = 0;
	int maxBlocks, kmax, endOfDataFile = 1;
	datafile = (char*)malloc(maxLengthOfFileName * sizeof(char));
	//fileNew = (char*)malloc(maxLengthOfFileName * sizeof(char));
	static double** D{}, ** Scene{};
	int rcD[2], rcScn[2], k, ip;




	//	........ configuration information from file rcon.txt ..................
	Len = (int)(strnlen_s(datafile, 100)) + 10;
	LogFile = (char*)malloc(Len * sizeof(char));
	printf("!. argc %d argv[1] %s\n", argc, argv[1]);

	config = initRdr(datafile, LogFile, argc, argv);

	er = (int)(config[0]); if (er < 0) return er;

	config[3] = 0.0;
	control = (int)(config[2]); synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);
	numOfPhaseSpecSamples = (int)(config[5]); kmax = (int)(config[6]);
	FFTsamples = (int)(config[7]); NumOfColumns = (int)(config[13]);
	maxBlocks = 2;
	maxBlocks = (int)(config[14]); // added on 24th Jul 2023
	rc[0] = FFTsamples; rc[1] = NumOfColumns; 	cby2 = rc[1] / 2;
	rgain = config[11];
	bins2range = (rgain / FFTsamples);
	printf("!. range gain %3.4f and rThold %3.4f max blocks %d\n", config[11], config[12], maxBlocks);
	getchar();

	//	...........................................................................
	cols = 5; rows = kmax * numberOfTgts;
	rcD[0] = rows; rcD[1] = cols; blocks = 0;
	er = openCSVfiles(); if (er < 0) return er;

	for (blocks = 0; blocks < maxBlocks; blocks++)
	{
		D = getLooksData(config, datafile, blocks, rcD);
		/*		printf("!.[%d] sorted data matrix\n", blocks);
				for (k = 0; k < rcD[0]; k++)
				{
					for (ip = 0; ip < rcD[1]; ip++)
					{
						printf("%3.2f\t", D[k][ip]);
					} printf("\n");
				}*/

		if (D != NULL)
		{
			Scene = processRdr(blocks, datafile, config, D, rcD, rcScn);
			if (Scene == NULL) break;
		}
		else
		{
			Er = (int)(config[0]); if (Er < 0) break;
		}
		for (k = 0; k < rcScn[0]; k++)
		{
			for (ip = 0; ip < rcScn[1]; ip++)
			{
				printf("%3.2f\t", Scene[k][ip]);
			} printf("\n");
		}

	}
	er = closeAllFile();
	printf("!.block[%d] Process Failure %d Data Failure %d\n", blocks, er, Er);
	if (blocks <= 0)
	{
		printf("unable to create not even 1 block reduce kmax %d\n", kmax);
		fprintf(fpLog, "unable to create not even 1 block reduce kmax %d\n", kmax);
	}
	myFree2(D, rcD[0]);
	//	er = closeAllFile();
	getchar();
	return er;
}

