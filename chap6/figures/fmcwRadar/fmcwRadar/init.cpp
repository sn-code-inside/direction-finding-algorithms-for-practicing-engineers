#include "stdafx.h"
#include "init.h"
//#include "mex.h"
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
double* initRdr
(
	char * datafile, 
	char * LogFile,
	int argc,
	char **argv
)
{
	double* config{};
	char* date, * dateFile;
	int er,size, numOfPhaseSpecSamples,kmax, numberOfTgts;
    int k;
	int maxNumberOfBlocks = 30;
	double threshold = 0.2;
	int blocks;
	int rc[2];

	config = myAlloc(20);
    for (k=0; k<20; k++) config[k] = 0.0;
	er = closeAllFile();
	date = getDate();
	printf("initRdr(%d %s)\n",argc,datafile);
//	printf("initRdr(%d %s)\n",argc,argv[1]);
	printf("\n\n!. read configuration information from file rcon.txt\n\n");
	er = rdConfig(config, datafile); // read rcon.txt and get information and name of datafile
    
	if (er < 0) { printf("!. issue with rcon.txt file\n"); config[0] = er; return config; }
	switch (argc)
	{
		case 1:
		printf("!. you are executing program no console input\n");
		blocks = maxNumberOfBlocks;
		break;
		case 2:
		printf("!. you are executing program 1 console input\n");
		strcpy_s(datafile, 50, argv[1]);
		blocks = maxNumberOfBlocks;
		break;
		case 3:
		printf("!. you are executing program 2 console input\n");
		strcpy_s(datafile, 50, argv[1]);
		blocks = atoi(argv[2]);
		if (blocks > 500) blocks = maxNumberOfBlocks;
		if (blocks <= 0) blocks = 1;
		break;
		default:
		printf("!. you are executing program 3 or more console input\n");
		getchar();
		strcpy_s(datafile, 50, argv[1]);
		blocks = atoi(argv[2]);
		if (blocks > 500) blocks = maxNumberOfBlocks;
		if (blocks <= 0) blocks = 1;
		break;
	}
//	if (argc > 1)
//	{
//		strcpy_s(datafile, 50, argv[1]);
//	}
//	else 
//	printf("wait\n"); getchar();
//	printf("!. datafile %s\n", datafile); getchar();




	config[12] = threshold; config[13] = 8; config[14] = blocks;
	printf("!. Threshold of Target Detection is set as %3.4f line 36 init.cpp\n", config[12]);
	dateFile = fileDetails(datafile, &size);
	if (dateFile == NULL)
	{
		printf("!. No File Details.. %s may not be there\n", datafile);
		config[0] = -120.0;
		return config;
	}

	printf("!. %s of size [%d] %s\n", datafile, size, dateFile);


//	if (argc > 1)
//	{
//		strcpy_s(datafile, sizeof(datafile), argv[1]);
//	}
//	else printf("!. you are executing program no console input\n");
	er = stripNaddFile(datafile, LogFile, ".txt", ".log");
	if (er < 0) { printf("!. missing extension\n"); config[0] = -1.0; return config; }
	er = fopen_s(&fpLog, LogFile, "w");
	if (er == 0) printf("!. file %s opened on %s\n", LogFile, date);
	else printf("!. file %s open failure on %s\n", LogFile, date);
	fprintf(fpLog, "!. Opening a log file %s %s\n", LogFile, date);
	fprintf(fpLog, "!. %s of size [%d] %s\n", datafile, size, dateFile);
	er = rdRcon(rc, datafile, config);
	if (er < 0) { printf("!. issue with files \n"); config[0] = -1.0;  return config; }
	numOfPhaseSpecSamples = (int)(config[5]); kmax = (int)(config[6]);
	numberOfTgts = (int)(config[4]);
	usage(config, datafile);
	printf("!. real data using %s ", datafile);
	printf(" [%d] by [%d] matrix No Of Tgts %d Max iterations %d sampling phase Spk %d\n", rc[0], rc[1], numberOfTgts, kmax, numOfPhaseSpecSamples);
	return config;
}