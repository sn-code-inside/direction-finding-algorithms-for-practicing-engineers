#include "getRgDcLuster.h"
#include "matrix.h"
#include "mex.h"   /* This one is required */
//  ..................................................................
double** getPar
(
        complex **A, 
        double *config, 
        int *bins, 
        complex **steering,
        double *doas,
        double *Mudoas,
        double **s,
        double *sAvg,
        double **Obj,
        complex **S,
        double **rgMat,
        double **D,
        int *rcD,
        int *rcClouds,
        int *error,
        int d,
        complex **En
)
{
	int rc[2],cby2;
	int maxLengthOfFileName = 60;
	double *sg;  
    int RC[2] = { 20,3 };
	int i,j;
	int kmax;
    int static k = 0;
	//double threshold; // **M,kmuTime,muTime;
    int newTgts;
    double **Df;
    int rcDf[2];
    double **clouds;
    double *rg;
    //int rcClouds[2];
    int rows,cols;
	double fromDoa,DoaKmu;
    int zerofill = 8;
	int synthetic, numberOfTgts, numOfPhaseSpecSamples, FFTsamples;
    int r,m;
//    complex ** En{};
//    printf("[%d] main - getRgD.cpp\n",seQ); seQ = seQ + 1;
	synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);
	numOfPhaseSpecSamples = (int)(config[5]); FFTsamples = (int)(config[7]);
	kmax = (int)(config[6]);
    rc[0] = FFTsamples; rc[1] = (int)(config[13]); cby2 = rc[1] / 2;
    cols = 5; rows = kmax * numberOfTgts;

    r = cby2 - d; if (r < 1) { printf("issue in number of D %d %d\n", cby2, d); r = 1; }
	m = r * numberOfTgts;


//  ...........................................................   



//  ...........................................................  

    preProc(A, S, sAvg, config, zerofill);
    newTgts = detectBins(sAvg, config, bins);
    printf("!. New Targets %d[%d]\n",newTgts,numberOfTgts);
    if (newTgts < 0) 
    {
        error[0] = -1; 
        return NULL;
    } else error[0] = 1;

    //sg = (double*)malloc(numberOfTgts * sizeof(double));
    numberOfTgts = (int)(config[4]);
    sg = myAlloc(numberOfTgts);
    rg = rgSteering(A, config, bins, rgMat, sg, steering);
    fromDoa = easyMusic(S, bins, config, Mudoas,Obj,En,d);

    DoaKmu = kMusic(S, steering, doas, config,s);
    TransferData(numberOfTgts, bins, rg,sAvg, doas, Mudoas, D, k, kmax);
    k = k + 1;
    if ( k == kmax ) 
    {
        Df = sortCluster(D, rows, cols, numberOfTgts, rcDf, config);
//  ......... print sorted matrix of kmax chirps ..................  
//     
//        printf("!. size of D matrix %d by %d\n", rcD[0], rcD[1]);
        printf("!. size of sorted matrix %d by %d\n", rcDf[0], rcDf[1]);
        if (rcDf[0] > rcD[0])
        {
            printf("!. Allocated Memory is not sufficent rows clamped to %d->%d\n", rcDf[0],rcD[0]);
            rcDf[0] = rcD[0];
        }
        for(i=0; i<rcDf[0]; i++)
        {
            for (j = 0; j < rcDf[1]; j++) 
            { 
                D[i][j] = Df[i][j];
            }
        } rcD[0] = rcDf[0]; rcD[1] = rcDf[1];
//  .........  end of printing ....................................                          
		clouds = formClouds(Df, rcDf, rcClouds,0.05);
        k = 0;
        return clouds;
    }
    return NULL;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int rcA[2] = {8,4};
    double *inputAr;
    double *inputAi;
    double *inputPr;
    double *binsPtr;
    double *steerPtr, *steerPti;
    double *EnPtr, *EnPti;
    double *steerAvgPtr, *steerAvgPti;
    double *SPtr, *SPti,*APtr,*APti;
    double *doasPtr,*MudoasPtr,*sPtr,*sAvgPtr,*ObjPtr,*rgMatPtr;
    double *dataPtr,*sortDataPtr;

    double *config;
    int *bins;
    double *doas,*Mudoas,**s,*sAvg,**Obj,**rgMat;
    static double **D{};
    double **clouds;
    int rcClouds[2],rcD[2];
    int endOfBlocks = 1;
    static int count = 0, matCount = 0, blocks = 0;
  
    int kmax,rows,cols,maxNumberOfBlocks;

    char *datafile;
    int N = 10,k,p,r,c,i,j,flag,er;
    int newr,mm,dd=2;
    int LenConfig = 20,numberOfTgts,cby2,numOfPhaseSpecSamples;
    int maxLengthOfFileName = 80;
    int kt;
    int pksEr;

    complex **A,**steering,**S,**steeringAvg, **En; // added on 30th Apr 2024
    seQ = 0;
//    printf("[%d] mexFunction - getRgD.cpp\n",seQ); seQ = seQ + 1;
    printf("!. [%d] Entry to mexFunction - getRgDcLuster.cpp\n", count);
    
    if ( (nlhs != 14) || (nrhs != 2) )
    {
        usageGetRgDcLuster(nlhs,nrhs);
        mexErrMsgTxt("!. INPUT Error\n");
        return;
    } //else  { printf("call[%d] input var %d output var %d\n",count,nrhs,nlhs); }

    
    flag = mxIsChar(prhs[0]);
    if ( flag > 0 )
    {
        datafile = (char *)malloc(maxLengthOfFileName * sizeof(char));
        datafile = mxArrayToString(prhs[0]);
    }
    else   mexErrMsgTxt("!. RHS[0] must be a character string\n");
    
    r = (int)(mxGetM(prhs[1])); LenConfig = (int)(mxGetN(prhs[1]));
//    printf(" size of input matrix %d by %d\n",r,LenConfig);
    if ( r != 1) 
    { 
        printf(" try transpose \n");
        printf(" size of input matrix %d by %d\n",r,LenConfig);
        return;
    } else
    {
            inputPr = mxGetPr(prhs[1]);
            //config = (double *)malloc(LenConfig * sizeof(double));
            config = myAlloc(LenConfig);
            for (i = 0; i < LenConfig; i++) config[i] = inputPr[i];
    }
    
    numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
    kmax = (int)(config[6]);
 
    rows = kmax * numberOfTgts+2; cols = 7; // updated on 19th May 2025
    rcD[0] = rows; rcD[1] = cols; // extra two rows were due to additional data compacted in the last rows

    //bins = (int *)malloc(numberOfTgts * sizeof(int));
    bins = myAllocI(numberOfTgts);
    rcA[0] = (int)(config[7]); rcA[1] = (int)(config[13]); cby2 = rcA[1] / 2;
    maxNumberOfBlocks = (int)(config[14]);
    printf("!. [%d] Number of Blocks %d Number of Chirps %d\n", count,maxNumberOfBlocks, kmax);

    A = myAlloc2Complex(rcA[0], cby2);
    er = createA(A, datafile, config, matCount); 
    printf("!. [%d]Matrix A[%d] read from file %s\n", er,matCount, datafile);
    matCount = matCount + 1;
    if ( er < 0 ) 
    {
        printf("!. closing the %s file\n",datafile);
        fclose(fp);
        mexErrMsgTxt("!. DATA READ ERROR ...\n");
        return;
    }

    newr = cby2 - dd; if (newr < 1) { printf("issue in number of D %d %d\n", cby2, dd); newr = 1; }
	mm = newr * numberOfTgts;

//  ........... pointer to out ...............    
    plhs[0] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);
    binsPtr = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxCOMPLEX);
    steerPtr = mxGetPr(plhs[1]); steerPti = mxGetPi(plhs[1]);
    plhs[2] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);
    doasPtr = mxGetPr(plhs[2]);
    plhs[3] = mxCreateDoubleMatrix(numberOfTgts, 1, mxREAL);
    MudoasPtr = mxGetPr(plhs[3]);
    plhs[4] = mxCreateDoubleMatrix(numberOfTgts, numOfPhaseSpecSamples, mxREAL);
    sPtr = mxGetPr(plhs[4]);
    plhs[5] = mxCreateDoubleMatrix(rcA[0], 1, mxREAL);
    sAvgPtr = mxGetPr(plhs[5]);
    plhs[6] = mxCreateDoubleMatrix(numberOfTgts, numOfPhaseSpecSamples, mxREAL);
    ObjPtr = mxGetPr(plhs[6]);

    plhs[7] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);
    SPtr = mxGetPr(plhs[7]); SPti = mxGetPi(plhs[7]);
    plhs[8] = mxCreateDoubleMatrix(rcA[0], cby2, mxCOMPLEX);
    APtr = mxGetPr(plhs[8]); APti = mxGetPi(plhs[8]);

    plhs[9] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxCOMPLEX);
    steerAvgPtr = mxGetPr(plhs[9]); steerAvgPti = mxGetPi(plhs[9]);
    plhs[10] = mxCreateDoubleMatrix(numberOfTgts, cby2, mxREAL);
    rgMatPtr = mxGetPr(plhs[10]);
//  ......... dimensions change ..    
    mxDestroyArray(plhs[11]);
    plhs[11] = mxCreateDoubleMatrix(1, 1, mxREAL);
    dataPtr = mxGetPr(plhs[11]);

    plhs[12] = mxCreateDoubleMatrix(mm, cby2, mxCOMPLEX); // added on 30th Apr 2024
    EnPtr = mxGetPr(plhs[12]); EnPti = mxGetPi(plhs[12]);

//  ......... dimensions change ..    
    mxDestroyArray(plhs[13]);
    plhs[13] = mxCreateDoubleMatrix(1, 1, mxREAL);
    sortDataPtr = mxGetPr(plhs[13]);





//  .............................memory allocate ................    
    steering = myAlloc2Complex(numberOfTgts, cby2);
    steeringAvg = myAlloc2Complex(numberOfTgts, cby2);
    S = myAlloc2Complex(rcA[0], cby2);
	En = myAlloc2Complex(mm, cby2);

    rgMat = myAlloc2(numberOfTgts, cby2);
    s = myAlloc2(numberOfTgts, numOfPhaseSpecSamples);
    Obj = myAlloc2(numberOfTgts, numOfPhaseSpecSamples);

    doas = myAlloc(numberOfTgts);
    Mudoas = myAlloc(numberOfTgts);
    sAvg = myAlloc(rcA[0]);


    if (count == 0)
    {
        printf("!. [%d] mexFunction - getRgDcLuster.cpp - Allocate static D %d by %d\n", count, rows, cols);
        D = myAlloc2(rows, cols);
    } else  printf("!. [%d] mexFunction - getRgDcLuster.cpp\n", count);

    
//  .............
//  ..   

//  ......... code in c for radar ...................  
//  
    clouds = getPar(A,config,bins,steering,doas,Mudoas,s,sAvg,Obj,S,rgMat,D,rcD,rcClouds,&pksEr,dd,En);
    if (clouds == NULL) printf("!. Chirp %d and kmax %d ...\n",count,kmax);


//
//    printf("rows %d..................\n",mm);
//	printComplxMatrix(En, mm, cby2); printf("cols %d---------------->\n",cby2);

//  ......... end of code in c ......................    

/*    if(pksEr < 0) 
    {
        printf("closing the %s file\n",datafile);
        fclose(fp);
        mexErrMsgTxt("!. No Peaks probably data problem due to file reading or something else ...\n");
    }*/
    count = count + 1; 
    if ( count == kmax ) 
    {
        printf("!. Number of Chirps %d = %d\n", count, kmax);
        printf("!. Ouput arguments[%d] clouds %d by %d\n",nlhs,rcClouds[0],rcClouds[1]);
        count = 0;
        double r, phi, pi, xmu, ymu;
	    pi = atan(1.0) * 4.0;

        rows = rcClouds[0]; cols = rcClouds[1] + 2;
        mxDestroyArray(plhs[11]);
        plhs[11] = mxCreateDoubleMatrix(rows, cols, mxREAL);
        dataPtr = mxGetPr(plhs[11]);
        for (p = 0; p < rows; p++) // rows
        {
            for (i = 0; i < cols; i++)
                {
                    kt = i*rows+p;
                    dataPtr[kt]  = clouds[p][i];
                }
                xmu = clouds[p][3]; ymu = clouds[p][5];
		        r = sqrt(xmu * xmu + ymu * ymu); // note sign change made in kMusic.cpp line 111
		        phi = atan2(ymu, xmu) * 180.0 / pi; // note the sign change made ???
                kt = 6*rows + p; dataPtr[kt] = r;  // added aditional columns
                kt = 7*rows + p; dataPtr[kt] = phi;
        }
        printf("!. Block Count [%d].%d\n", blocks, maxNumberOfBlocks);
        blocks = blocks + 1;
        if (blocks == maxNumberOfBlocks)
        {
            matCount = 0; blocks = 0;
            fclose(fp);
            printf("!. File %s closed and all set to start again\n",datafile);
            endOfBlocks = -1;
        }
        printf("!. Block Count [%d].%d\n",blocks,maxNumberOfBlocks);

//  added on 3rd May 2025 for the 6th Chapter Book
        printf("!. size of sorted matrix %d by %d\n", rcD[0], rcD[1]);
        for (i = 0; i < rcD[0]; i++)
        {
            for (j = 0; j < rcD[1]; j++) printf("%3.4f ", D[i][j] );
            printf("\n");
        }

        rows = rcD[0]-3; cols = rcD[1];
        if (rows < 0) rows = 1;
        mxDestroyArray(plhs[13]);
        plhs[13] = mxCreateDoubleMatrix(rows, cols, mxREAL);
        sortDataPtr = mxGetPr(plhs[13]);

        for (p = 0; p < rows; p++) // rows
        {
            for (i = 0; i < cols; i++)
            {
                kt = i * rows + p;
                sortDataPtr[kt] = D[p][i];
            }
        }
        myFree2(D, rcD[0]);
    }
    else {
        printf("!. Number of Chirps %d != %d\n", count, kmax);
        dataPtr[0] = count; sortDataPtr[0] = count;
    }
    

//  ............................................................. 
    printf("!. TRANSFER DATA to MATLAB\n");
//  ..................... transfer out of Matlab ...............    
    for (k = 0; k < numberOfTgts; k++) 
    { binsPtr[k] = bins[k]; doasPtr[k] = doas[k]; MudoasPtr[k] = Mudoas[k];}
    for (p = 0; p < numberOfTgts; p++) // rows
    {
        for (i = 0; i < cby2; i++)
        {
                kt = i*numberOfTgts+p;
                steerPtr[kt]     = steering[p][i].r;
                steerPti[kt]     = steering[p][i].i;
                steerAvgPtr[kt]  = steering[p][i].r;
                steerAvgPti[kt]  = steering[p][i].i;
//                steerAvgPtr[kt]  = steeringAvg[p][i].r;
//                steerAvgPti[kt]  = steeringAvg[p][i].i;
                rgMatPtr[kt]     = rgMat[p][i];
        }
    }
    for (p = 0; p < numberOfTgts; p++) // rows
    {
         for (i = 0; i < numOfPhaseSpecSamples; i++) 
         {
             kt = i*numberOfTgts+p;
             sPtr[kt]   = s[p][i];
             ObjPtr[kt] = Obj[p][i];
         }
    }


    for (k = 0; k < rcA[0]; k++) sAvgPtr[k] = sAvg[k];
    for (p = 0; p < rcA[0]; p++) // rows
    {
        for (i = 0; i < cby2; i++)
        {
                kt = i*rcA[0]+p;
                SPtr[kt]  = S[p][i].r;
                SPti[kt]  = S[p][i].i;
                APtr[kt]  = A[p][i].r; // updated 4th Jul 2023
                APti[kt]  = A[p][i].i; // updated 4th Jul 2023
        }
    }

    for (p = 0; p < mm; p++) // rows
    {
        for (i = 0; i < cby2; i++)
        {
                kt = i*mm+p;
                EnPtr[kt]  = En[p][i].r; // updated 30th Apr 2024
                EnPti[kt]  = En[p][i].i; // updated 30th Apr 2024
        }
    }
 

//  ....................Free Memory ........................................
    printf("!. FREE MEMORY\n");
    myFree2Complex(A, rcA[0]);
    myFree2Complex(S, rcA[0]);
    myFree2Complex(steering, numberOfTgts);
    myFree2Complex(steeringAvg, numberOfTgts);
    myFree2Complex(En, mm);

    myFree2(rgMat, numberOfTgts);
    myFree2(s, numberOfTgts);
    myFree2(Obj, numberOfTgts);

    free(sAvg); free(doas); free(Mudoas);
    printf("!. END OF BLOCKS FLAG %d\n", endOfBlocks);
    if (endOfBlocks < 0) mexErrMsgTxt("!. COMPLETED ALL THE BLOCKS ...\n");
    return;
}

void usageGetRgDcLuster(int nlhs, int nrhs)
{
    printf("  NOTE SIGN CHANGE WAS MADE in DOA at line 111 in kMusic.cpp 3rd May 2025\n");
    printf("  Usage Error Parameters Left Hand Side = %d(14) .. Right Hand Side = %d(2) \n", nlhs, nrhs);
    printf("  fileName(ADC data) is read from rcon.txt\n");
    printf("  data format blank seperated 9 columns sample row given below\n");
    printf("  68.0 -307.0 8.0 -462.0 173.0 -149.0 308.0 182.0 8202\n");

    printf("  updated on 4th  July 2023 @ Dublin Ohio\n");
    printf("  updated on 3rd  May 2025 @ Dublin Ohio for Book\n");
    printf("  alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
    printf("  synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n");
    printf("  numOfPhaseSpecSamples = (int)(config[5]);\n");
    printf("  kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");

    printf("  [14 parameters given below] = getRgD(ComplexADCdata,config);\n");
    printf("  [bins,str,doas,muDoas,s,spk,muS,S,A,strAvg,rgMat,clouds,En,data] ...\n");
    printf("  = getRgDcLuster(file,config');\n");
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