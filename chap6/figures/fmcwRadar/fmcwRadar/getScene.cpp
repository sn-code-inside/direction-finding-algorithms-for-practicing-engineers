
#include "getScene.h"
#include "matrix.h"
void usageGetScene(int, int);
#include "mex.h"   // this is required
//  ..................................................................
double** LookObjects(int blocks, char *datafile, double *config, int *rcD)
{
	int rc[2], er=1, Er=1,cby2;
	int maxLengthOfFileName = 80, Len=100;
    int configLen = 20;
//	char* datafile, * fileNew, * fileCloud{}, * fileTemp{}; 
	char* fileNew, * fileCloud{}, * fileTemp{}; 
	static char* LogFile;
    //static double* configLocal;
    double* configLocal;
    double rgain = 0, bins2range=1.0;
	static int control, synthetic, numberOfTgts, numOfPhaseSpecSamples;
	int FFTsamples=512, NumOfColumns=4;
	int cols=0,rows=0;
	int maxBlocks, kmax, endOfDataFile = 1;
	//datafile = (char*)malloc(maxLengthOfFileName * sizeof(char));
	//fileNew = (char*)malloc(maxLengthOfFileName * sizeof(char));
	static double** D{};
    static char** argv{};
	int k,ip;
    printf("!. Look Objects\n");


	//	........ configuration information from file rcon.txt ..................
    if (blocks == 0)
    {
        argv = myAlloc2char(2,40);
	    Len = (int)(strnlen_s(datafile, 100)) + 10; 
	    LogFile = (char*)malloc(Len * sizeof(char));
        strcpy_s(argv[1], 40, datafile);
//	    printf("!. argc %d argv[1] %s\n", argc, argv[1]);
        maxBlocks = (int)(config[14]);
	    configLocal = initRdr(datafile, LogFile,2, argv); 
        for(k=0; k< configLen; k++)  config[k] =configLocal[k];
        printf("!. Logfile %s datafile %s\n",LogFile,datafile);

	    er = (int)(config[0]); //if (er < 0) return NULL;
        if (er < 0) mexErrMsgTxt("failed at initRdr\n");

	    config[3] = 0.0;
	    control = (int)(config[2]); synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);
	    numOfPhaseSpecSamples = (int)(config[5]); 
	    FFTsamples = (int)(config[7]); NumOfColumns = (int)(config[13]);
	    maxBlocks = 50; 
	    //maxBlocks = (int)(config[14]); // added on 24th Jul 2023
        config[14] = maxBlocks;
	    kmax = (int)(config[6]); 	rc[0] = FFTsamples; rc[1] = NumOfColumns; 	cby2 = rc[1] / 2;
	    rgain = config[11];
	    bins2range = (rgain / FFTsamples);

	    printf("!. range gain %3.4f and rThold %3.4f max blocks %d\n", config[11], config[12],maxBlocks);
	    er = openCSVfiles(); //if (er < 0) return NULL;
        if (er < 0) mexErrMsgTxt("failed to open CSV files\n");
	    cols = 5; rows = kmax * numberOfTgts;
	    rcD[0] = rows; rcD[1] = cols; blocks = 0;
    }
//	...........................................................................

	    D = getLooksData(config, datafile, blocks, rcD);
        if (D == NULL)
        {
            if (config[0] < 0) mexErrMsgTxt("File Read Error\n");
        }
	return D;
}
//..........................................................................

//      THIS IS THE MATLAB INTERFACE

//..........................................................................
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    static char *datafile;
    int i,k,p,kt,ip,kmax,r,c,maxNumberOfBlocks = 5;
    int configLen = 20;
    double *inputPr,*inPtr;
    double *ScenePtr,*Dptr,*configPtr;
    int flag,maxLengthOfFileName = 80;
    static double *config;
    static int rcD[2],rcScn[2],blocks=0,chirp=0;
    static double **D;
//    double **dRaw;
    static double **Scene;
    int er,Er;
    printf("!. Mex entry number %d\n", blocks);
    if ( (nlhs != 2) || (nrhs != 3) )
    {
        usageGetScene(nlhs, nrhs);
        return;
    }
    flag = mxIsChar(prhs[0]);
    if ( flag > 0 )
    {
        datafile = (char *)malloc(maxLengthOfFileName * sizeof(char));
        datafile = mxArrayToString(prhs[0]);
    }
    else   mexErrMsgTxt("!. RHS[0] must be a character string\n");

    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if ( (r != 1) || (c != 1) ) 
    {
        mexErrMsgTxt("prhs[1] must be scalar\n");
    }
    inputPr = mxGetPr(prhs[1]);

    r = (int)(mxGetM(prhs[2])); c = (int)(mxGetN(prhs[2]));
    if ( (r != 1) || (c != 1) ) 
    {
        mexErrMsgTxt("prhs[2] must be scalar\n");
    }
    inPtr = mxGetPr(prhs[2]);
    maxNumberOfBlocks = (int)(inPtr[0]); 

// Check Status and close the files
    printf("!. Matrix Count %d and Earlier Mex Calls %d\n", chirp,blocks);
    printf("!. file %s block %d(%d)\n",datafile,blocks,maxNumberOfBlocks);
    if ((int)(inputPr[0]) == 0)  
    {
        if (chirp != 0) 
        { 
            chirp = 0; blocks = 0;
            free(config);
            myFree2(D, rcD[0]);
            myFree2(Scene, rcScn[0]);
            mxDestroyArray(plhs[0]);
            mxDestroyArray(plhs[1]);
        }
        config = myAlloc(configLen);
    } else   blocks = (int)(inputPr[0]);

    if (blocks >= 0)   
    {
        chirp = (int)(config[15]);
        printf("!. Matrix Count %d\n", chirp);
    }
    
    config[14] = inPtr[0];
    D = LookObjects(blocks, datafile, config,rcD);
    if (D == NULL) mexErrMsgTxt("!. Data Problem\n");

//  ....... par D [1]    
        mxDestroyArray(plhs[0]);
        plhs[0] = mxCreateDoubleMatrix(rcD[0], rcD[1], mxREAL);
        Dptr = mxGetPr(plhs[0]);
        for (p = 0; p < rcD[0]; p++) // rows
        {
            for (i = 0; i < rcD[1]; i++) // cols
                {
                    kt = i*rcD[0]+p;
                    if (i == 1)
                        Dptr[kt] = D[p][i] * config[11]; // get the actual range
                    else Dptr[kt] = D[p][i];
                }
        }


        maxNumberOfBlocks = (int)(config[14]);
		if (D != NULL) 
		{
            printf("!. Looking at Objects %d size of D %d by %d\n",blocks,rcD[0],rcD[1]);
			Scene = processRdr(blocks, datafile, config, D, rcD,rcScn);




			if (Scene == NULL)
            {
                er = closeAllFile();
                if (er < 0) mexErrMsgTxt("files could not be closed\n");
                mxDestroyArray(plhs[0]);
                plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
                Dptr = mxGetPr(plhs[0]); Dptr[0] = -1;

                mxDestroyArray(plhs[1]);
                plhs[1] = mxCreateDoubleMatrix(1,1, mxREAL);
                ScenePtr = mxGetPr(plhs[1]); ScenePtr[0] = -1;

                return;
            }
            		for (k = 0; k < rcScn[0]; k++)
		            {
			            for (ip = 0; ip < rcScn[1]; ip++)
			            {
				            printf("%3.2f\t", Scene[k][ip]);
			            } printf("\n");
		            }

		}
		else
		{
			Er = (int)(config[0]);
                er = closeAllFile();
                mxDestroyArray(plhs[0]);
                plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
                Dptr = mxGetPr(plhs[0]); Dptr[0] = -1;

                mxDestroyArray(plhs[1]);
                plhs[1] = mxCreateDoubleMatrix(1,1, mxREAL);
                ScenePtr = mxGetPr(plhs[1]); ScenePtr[0] = -1;
            printf("Er %d\n",Er);
            return;
		}
    
	printf("!.block[%d] Process Failure %d Data Failure\n", blocks,er);
	if (blocks <= 0)
	{
		printf("unable to create not even 1 block reduce kmax %d\n", kmax);
		fprintf(fpLog, "unable to create not even 1 block reduce kmax %d\n", kmax);
	}

//  .......... output parameters ....

//  ....... par Scene [2]    
        mxDestroyArray(plhs[1]);
        plhs[1] = mxCreateDoubleMatrix(rcScn[0], rcScn[1], mxREAL);
        ScenePtr = mxGetPr(plhs[1]);
        for (p = 0; p < rcScn[0]; p++) // rows
        {
            for (i = 0; i < rcScn[1]; i++) // cols
                {
                    kt = i*rcScn[0]+p;
                    ScenePtr[kt]  = Scene[p][i];
                }
        }


//  ....................Free Memory ........................................
    return;
}

void usageGetScene(int nlhs, int nrhs)
{
    printf("  Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(3) \n", nlhs, nrhs);
    printf("  NOTE SIGN CHANGE WAS MADE in DOA at line 111 in kMusic.cpp 3rd May 2025\n");
    printf("  fileName(ADC data) is read from rcon.txt\n");
    printf("  data format blank seperated 9 columns sample row given below\n");
    printf("  68.0 -307.0 8.0 -462.0 173.0 -149.0 308.0 182.0 8202\n");

    printf("  updated on 23rd  May 2025 @ Dublin Ohio for Book\n");
    printf("  alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
    printf("  synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n");
    printf("  numOfPhaseSpecSamples = (int)(config[5]);\n");
    printf("  kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");
    printf("  adcSamples = (int)(config[8]); i7Ti = (int)(config[9]);\n");
    printf("  FrqGoldRows = config[10]; rgain = config[11]; amplitude threshold = config[12];\n");
    printf("  Threshold used in myRdrCluster.cpp in double** sortCluster() line 207 for detection\n");
    printf("  cby2 = (int)(config[13])/2 number of columns of complex matrix;\n");
    printf("  maxNumberOfBlocks = (int)(config[14]);\n");
    printf("  matrix count read from file = (int)(config[15]);\n");


    printf("  [D S] = getScene(file,blockNumber,maxblocks);\n");
    printf("  1. D = data matrix  5 columns] ...\n");
    printf("  2. S = scene matrix 4 columns\n");
    printf("  The parameter cloud has as many rows as Objects in the scene\n");
    printf("  s .. e .. sigX .. muX .. sigY .. muY .. r .. phi total 8 columns\n");

    printf("  0. binsPtr of numberOfTgts, 1, mxREAL\n");
    printf("  1. steerPt numberOfTgts, cby2, mxCOMPLEX\n");
    printf("  2. doasPtr numberOfTgts, 1, mxREAL\n");
    printf("  3. MudoasPtr numberOfTgts, 1, mxREAL\n");
    printf("  4. sPtr numberOfTgts, numOfPhaseSpecSamples, mxREAL\n");
    printf("  5. sAvgPtr rcA[0], 1, mxREAL\n");
    printf("  6. ObjPtr numberOfTgts, numOfPhaseSpecSamples, mxREAL\n");
    printf("  7. SPt rcA[0], cby2, mxCOMPLEX\n");
    printf("  8. APt rcA[0], cby2, mxCOMPLEX\n");
    printf("  9. steerAvgPt numberOfTgts, cby2, mxCOMPLEX\n");
    printf("  10 rgMatPtr numberOfTgts, cby2, mxREAL\n");
    printf("  11 dataPtr numberClusters 8, mxREAL\n");
    printf("  12 En MUSIC steering Vector, numberRows cby2, mxCOMPLEX\n");
    printf("  13 sortDataPtr sorted data 7, mxREAL\n");
    return;
}