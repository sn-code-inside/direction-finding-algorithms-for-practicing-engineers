
#include "initR.h"
#include "mex.h"
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
int main(int argc, char *argv,double *config, int *lenConfig)
{
	char* datafile, * fileNew, * fileCloud, * fileTemp, *LogFile; 
	int maxLengthOfFileName = 80,LenConfig = 14, er = 0; 
    lenConfig[0] = LenConfig;
	LogFile = (char*)malloc(maxLengthOfFileName * sizeof(char));
	printf("argc %d argv[1] %s\n", argc, argv);

    datafile = (char*)malloc(maxLengthOfFileName * sizeof(char));
	fileNew = (char*)malloc(maxLengthOfFileName * sizeof(char));
	fileCloud = (char*)malloc(maxLengthOfFileName * sizeof(char));
	fileTemp = (char*)malloc(maxLengthOfFileName * sizeof(char));
    er = initRdr(datafile, fileNew, fileCloud, fileTemp, LogFile,config,LenConfig,argc, argv);
    //fclose(fpLog);
    return er;
}

int initRdr
(
	char * datafile, 
	char * fileNew, 
	char * fileCloud, 
	char * fileTemp, 
	char * LogFile,
    double * Config,
    int  lenConfig,
	int argc,
	char *argv
)
{
	double* config;
	char* date, * dateFile;
	int er,size, numOfPhaseSpecSamples,kmax, numberOfTgts;
	int rc[2],k;
	printf("!. initRdr(%d %s)\n",argc,argv);

	config = myAlloc(lenConfig);
    for (k=0; k< lenConfig; k++) config[k] = 0.0;
	date = getDate();
	printf("\n\n!. read configuration information from file rcon.txt\n\n");
	er = rdConfig(config, datafile); // read rcon.txt and get information and name of datafile
	if (er < 0) { printf("!. issue with rcon.txt file\n"); return er; }
	if (argc > 1)
	{
		strcpy_s(datafile, 50, argv);
	}
	else printf("!. you are executing program no console input\n");
    //printf("------configuration data\n");
	config[12] = 0.2f; config[13] = 8;
 

	printf("!. Threshold of Target Detection is set as %3.4f line 61 myRdr.cpp\n", config[12]);




	dateFile = fileDetails(datafile, &size);
	if (dateFile == NULL)
	{
		printf("!. No File Details.. %s\n!. File may not be there\n", datafile);
		return -120;
	}

	printf("!. %s of size [%d] %s\n", datafile, size, dateFile);
 
	er = stripNaddFile(datafile, LogFile, ".txt", ".log");


	if (er < 0) { printf("!. missing extension\n"); return er; }
	er = rdRcon(rc, datafile, config);

//    for (k=0; k< lenConfig; k++) printf("%3.4f \n",config[k]);
    for (k=0; k< lenConfig; k++) Config[k] = config[k];

	if (er < 0) { printf("!. issue with files \n"); return er; }
	numOfPhaseSpecSamples = (int)(config[5]); kmax = (int)(config[6]);
	numberOfTgts = (int)(config[4]);
	usage(config, datafile);
	printf("!. real data using %s ", datafile);
	printf(" [%d] by [%d] matrix No Of Tgts %d Max iterations %d sampling phase Spk %d\n", rc[0], rc[1], numberOfTgts, kmax, numOfPhaseSpecSamples);
	return er;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int rcA[2] = {8,4};
    double *inputAr;
    double *inputPr;
    double *JkCptr;
    double SNR; int a,b;
    char *argvfile;
    int maxLengthOfFileName = 60,lenConfig=14;
    int k,p,r,c,i,flag,console=0;
    char *datafile;
    double *config;


    
    if ((nlhs != 2) || (nrhs != 2))
    {
        printf("!. UPDATED on 1st Feb 2023 all code is from rdrImg.sln");
        printf("   Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(2) \n",nlhs,nrhs);
        printf("   [configPar fileName] = initR('rcon.txt',1);\n");
        printf("   fileName(ADC data) is read from rcon.txt\n");
        printf("   data format blank seperated 9 columns sample row given below\n");
        printf("   68.0 -307.0 8.0 -462.0 173.0 -149.0 308.0 182.0 8202\n");
        printf("   configPar Output\n");
        printf("   alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
        printf("   synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n"); 
        printf("   numOfPhaseSpecSamples = (int)(config[5]);\n");
        printf("   kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");
	    printf("   rcon[12] amplitude threshold in double** sortCluster(..)\n");
	    printf("   rcon[13] number of real columns of matrix\n");
	    printf("!. You may locate the source at\n");
	    printf("!. Updated on 3rd Mar 2025 4:30pm at Princeton NJ\n");
        printf("!. D:\\myIndustry\\Dr Kaluri Research House\\newBook\\Book On DF");
            printf("\\chapOne\\myBook\\chap-3\\figures\\myMexInitR for mex use myMexInitR.m\n");
        printf("!. D:\\Edu-Institutions\\UOH\\Research\\iRadar\\rdrImg\\rdrImg\\rdrImg.cpp for C solution\n");
        printf("!. This is for figures in the Book 4th Chapter\n");

        return;
    }
    
    rcA[0] = (int)(mxGetM(prhs[0])); rcA[1] = (int)(mxGetN(prhs[0]));
    flag = mxIsChar(prhs[0]);
    if ( flag > 0 )
    {
        datafile = (char *)malloc(maxLengthOfFileName * sizeof(char));
        argvfile = (char *)malloc(maxLengthOfFileName * sizeof(char));
        argvfile = mxArrayToString(prhs[0]);
    }
    else   mexErrMsgTxt("!. RHS[0] must be a character string\n");
 //   for (p = 0; p < rcA[1]; p++) datafile[p] = inputAr[p];
 //   printf("Hello %s %d %d\n",datafile,rcA[0],rcA[1]);
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if ( r != 1) printf("!. this must be a scalar\n");
    if ( c != 1) printf("!. this must be a scalar\n");
    inputPr = mxGetPr(prhs[1]);
    console = (int)(inputPr[0]);
    config = (double *)malloc(30 * sizeof(double));
    flag = main(console,argvfile,config,&lenConfig);
    if (flag < 0) mexErrMsgTxt("Error Getting Config Data\n");

    plhs[0] = mxCreateDoubleMatrix(lenConfig, 1, mxREAL);
    JkCptr = mxGetPr(plhs[0]);
    printf("!. length of Config data array %d\n",lenConfig);
    plhs[1] = mxCreateString(argvfile);
    for (k = 0; k < lenConfig; k++) JkCptr[k] = config[k];
    printf("!. alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
	printf("!. synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n"); 
    printf("!. numOfPhaseSpecSamples = (int)(config[5]);\n");
	printf("!. kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");
	printf("!. Threshold of Target Detection is set as %3.4f\n", config[12]);
	printf("!. Number of Real Channels %d\n", (int)(config[13]));
    return;
}