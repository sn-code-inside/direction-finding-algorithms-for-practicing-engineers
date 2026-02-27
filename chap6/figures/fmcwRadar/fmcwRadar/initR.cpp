
#include "initR.h"
#include "mex.h"


int main(int argc, char *argv,double *Config, int *lenConfig)
{
	char* datafile, *LogFile;
	double* config;
	int maxLengthOfFileName = 80,LenConfig = 20, er = 0,k; 
    lenConfig[0] = LenConfig;
	LogFile = (char*)malloc(maxLengthOfFileName * sizeof(char));
    datafile = (char*)malloc(maxLengthOfFileName * sizeof(char));
	printf("!. argc %d argv %s\n", argc, argv);
	config = initRdrMatlab(datafile, LogFile, argc, argv);
	er = (int)(config[0]); if (er < 0) return er;
	for (k = 0; k < LenConfig; k++) Config[k] = config[k];
    fclose(fpLog);
    return er;
}



double* initRdrMatlab
(
	char* datafile,
	char* LogFile,
	int argc,
	char* argv
)
{
	double* config{};
	char* date, * dateFile;
	int er, size, numOfPhaseSpecSamples, kmax, numberOfTgts;
	int k,lenConfig=20;
	int maxNumberOfBlocks = 30;
	double threshold = 0.2;
	int blocks;
	int rc[2];

	config = myAlloc(lenConfig);
	printf("!. config array length 20\n");
	for (k = 0; k < lenConfig; k++) config[k] = 0.0;
	date = getDate();
	printf("\n\n!. read configuration information from file rcon.txt\n\n");
	er = rdConfig(config, datafile); // read rcon.txt and get information and name of datafile
	printf("!. initRdrMatlab(%d %s) \n   read from rcon.txt %s\n", argc, argv,datafile);

	if (er < 0) { printf("!. issue with rcon.txt file\n"); config[0] = er; return config; }
	switch (argc)
	{
	case 1:
		printf("!. you are executing program no console input\n");
		blocks = maxNumberOfBlocks;
		break;
	case 2:
		printf("!. you are executing program 1 console input\n");
		strcpy_s(datafile, 50, argv);
		blocks = maxNumberOfBlocks;
		break;
	default:
		printf("!. invalid 2nd argument\n");
		config[0] = -120.0;
		break;
	}
	config[12] = threshold; config[13] = 8; config[14] = blocks;
	printf("!. Threshold of Target Detection is set as %3.4f \n   line 68 initR.cpp\n", config[12]);
	dateFile = fileDetails(datafile, &size);
	if (dateFile == NULL)
	{
		printf("!. No File Details.. %s may not be there\n", datafile);
		config[0] = -120.0;
		return config;
	}

	printf("!. %s of size [%d] %s\n", datafile, size, dateFile);
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
	//usage(config, datafile);
	printf("Alpha Fs  control synthetic numTgts phaseSamples numberOfChirps fileName\n");
	printf("26   4500   1        0        5        180            10      car - car - bike.txt\n");
	printf("!. real data using file %s ", datafile);
	printf(" [%d] by [%d] matrix\n", rc[0], rc[1]);
	printf("!. No Of Tgts %d Max iterations %d sampling phase Spk %d\n", numberOfTgts, kmax, numOfPhaseSpecSamples);
	return config;
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
		usageInitR(nlhs,nrhs);
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
    config = (double *)malloc(30 * sizeof(double)); // 30 is for safety
//	..........................................................
//
    flag = main(console,argvfile,config,&lenConfig);
    if (flag < 0) mexErrMsgTxt("Error Getting Config Data\n");
//
//  ..........................................................
    plhs[0] = mxCreateDoubleMatrix(lenConfig, 1, mxREAL);
    JkCptr = mxGetPr(plhs[0]);
    plhs[1] = mxCreateString(argvfile);
    for (k = 0; k < lenConfig; k++) JkCptr[k] = config[k];
	usageInitR(nlhs, nrhs);
	printf("!. length of Config data array %d\n", lenConfig);
	printf("!. initR.cpp updated on 23rd May 2025 @ Dublin Ohio\n");
    printf("!. alpha = config[0] %3.4f; Fs = config[1] %3.4f; control = (int)(config[2]) %d;\n", config[0], config[1], (int)(config[2]) );
	printf("!. synthetic = (int)(config[3]) %d; numberOfTgts = (int)(config[4]) %d;\n", (int)(config[3]), (int)(config[4]));
    printf("!. numOfPhaseSpecSamples = (int)(config[5]) %d;\n", (int)(config[5]));
	printf("!. kmax = (int)(config[6]) %d; FFTsamples = (int)(config[7]) %d;\n", (int)(config[6]), (int)(config[7]) );
	printf("!. adcSamples = (int)(config[8]) %d; i7Ti = (int)(config[9]) %d;\n", (int)(config[8]), (int)(config[9]) );
	printf("!. FrqGoldRows = (int)(config[10]) %d; rgain = config[11] %3.4f;\n", (int)(config[10]), config[11]);
	printf("!. Threshold of Target Detection is set as %3.4f\n", config[12]);
	printf("!. Threshold used in myRdrCluster.cpp in double** sortCluster() line 207 for detection\n");
	printf("!. Number of Real Channels %d\n", (int)(config[13]));
	printf("!. maxNumberOfBlocks = (int)(config[14]) %d;\n", (int)(config[14]));
    return;
}

void usageInitR(int nlhs, int nrhs)
{
	printf("!. UPDATED on 3rd May 2025 all code is from fmcwRadar.sln\n");
	printf("   Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(2) \n", nlhs, nrhs);
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
	printf("!. D:\\myIndustry\\Dr Kaluri Research House\\newBook\\Book On DF\n");
	printf("   \\chapOne\\myBook\\chap-3\\figures\\myMexInitR for mex use myMexInitR.m\n");
	printf("!. D:\\myIndustry\\Dr Kaluri Research House\\newBook\Book On DF\n");
	printf("!.   \\chapOne\\myBook\\Book\\chap5\\figures\\fmcwRadar\\fmcwRadar\\fmcwRadar.cpp for C solution\n");
	printf("!. This is for figures in the Book 6th Chapter\n");
	return;
}

