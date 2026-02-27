
#include "getRgD.h"
#include "matrix.h"
#include "mex.h"   /* This one is required */
//  ..................................................................
double** getPar
(
        complex **A,       // look matrix
        double *config,    // configuration parameters
        int *bins,         // peaks in bins
        complex **steering,// steering vector in kMUSIC
        double *doas,      // kMUSIC doas
        double *Mudoas,    // gMUSIC doas
        double **s,        // phase spectrum
        double *sAvg,      // average Fourier Spectrum all 4
        double **Obj,      // MUSIC spectrum
        complex **S,       // complex spectrum all channels
        double **rgMat,    // range values all channels and peaks
        double **D,        // Data over a block
        int *rcClouds,     // cloud rows and columns
        int *error,        // Error
        int d,             // Number of Targets in MUSIC
        complex **En       // Complex Noise Eigen Vectors
)
{
	int rc[2],cby2;
	int maxLengthOfFileName = 60;
	double *sg;  
    int RC[2] = { 20,3 };
	int i,j;
	int kmax;
    int static k = 0;
	double threshold; // **M,kmuTime,muTime;
    int detectFlag;
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
//	En = myAlloc2Complex(m, cby2);

//  ...........................................................   

	sg = (double *)malloc(numberOfTgts * sizeof(double));


//  ...........................................................  

    preProc(A, S, sAvg, config, zerofill);
    detectFlag = detectBins(sAvg, config, bins);
    threshold = detectFlag;
//    printf("!. lo/Hi peaks %3.4f\n",threshold);
    if (threshold < 0.0) 
    {
        error[0] = -1; 
        return NULL;
    } else error[0] = 1;

    
    rg = rgSteering(A, config, bins, rgMat, sg, steering);
    fromDoa = easyMusic(S, bins, config, Mudoas,Obj,En,d);

    DoaKmu = kMusic(S, steering, doas, config,s);
    TransferData(numberOfTgts, bins, rg,sAvg, doas, Mudoas, D, k, kmax);
    k = k + 1;
    if ( k == kmax ) 
    {
        Df = sortCluster(D, rows, cols, numberOfTgts, rcDf, config);
//  ......... print sorted matrix of kmax chirps ..................        
        printf("!. size of sorted matrix %d by %d\n",rcDf[0],rcDf[1]);
        printf("!. index - range - strength - doaK - doaMu - r*sin(doaK) - r*cos(doaK)\n");
        for(i=0; i<rcDf[0]; i++)
        {
            for(j=0; j<rcDf[1]; j++) printf("%3.4f ",Df[i][j]); printf("\n");
        }
//  .........  end of printing ....................................                          
		clouds = formClouds(Df, rcDf, rcClouds,0.05);
        k = 0;
//        return clouds;
        rcClouds[0] = rcDf[0]; rcClouds[1] = rcDf[1];
        return Df;
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
    double *dataPtr;
    //double *dataPtr;
    double *config;
    int *bins;
    double *doas,*Mudoas,**s,*sAvg,**Obj,**rgMat;
    static double **D{};
    double **clouds;
    int rcClouds[2];
    static int count = 0, matCount = 0, blocks = 0;
  
    int kmax,rows,cols,maxNumberOfBlocks;
 //   char argvfile[100];
    char *datafile;
    int N = 10,k,p,r,c,i,flag,er;
    int newr,mm,dd=2; // Number of Targets in MUSIC
    int LenConfig = 20,numberOfTgts,cby2,numOfPhaseSpecSamples;
    int maxLengthOfFileName = 80;
    int kt;
    complex **A,**steering,**S,**steeringAvg, **En; // added on 30th Apr 2024
    seQ = 0;
//    printf("[%d] mexFunction - getRgD.cpp\n",seQ); seQ = seQ + 1;
    
    if ( (nlhs != 13) || (nrhs != 2) )
    {
        printf("  Usage Error Parameters Left Hand Side = %d(10) .. Right Hand Side = %d(2) \n",nlhs,nrhs);
        printf("  fileName(ADC data) is read from rcon.txt\n");
        printf("  data format blank seperated 9 columns sample row given below\n");
        printf("  68.0 -307.0 8.0 -462.0 173.0 -149.0 308.0 182.0 8202\n");
//        printf("  configPar Output\n");
        printf("  updated on 8th  Mar 2025 @ Belle Mead NJ for Book\n");
        printf("  updated on 4th  July 2023 @ Dublin Ohio\n");
        printf("  updated on 30th  Apr 2024 @ Belle Mead NJ\n");
        printf("  alpha = config[0]; Fs = config[1]; control = (int)(config[2]);\n");
        printf("  synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]);\n"); 
        printf("  numOfPhaseSpecSamples = (int)(config[5]);\n");
        printf("  kmax = (int)(config[6]); FFTsamples = (int)(config[7]);\n");

        printf("  [13 parameters given below] = getRgD(ComplexADCdata,config);\n");
        printf("  [bins,str,doas,muDoas,s,spk,muS,S,A,strAvg,rgMat,clouds,En] ...\n");
        printf("  = getRgD(file,config');\n");

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
        printf("  11 data of all targets, 7 columns mxREAL\n");
        printf("     index - range - strength - doaK - doaMu - r*sin(doaK) - r*cos(doaK)\n");
        printf("  12 En MUSIC steering Vector, numberRows cby2, mxCOMPLEX\n");
        printf("     number of Rows in En = numberOfTgts times 2\n");
        printf("!. Updated on 8th Mar 2025 at 5:30pm Princeton NJ\n");
        printf("!. D:\\myIndustry\\Dr Kaluri Research House\\newBook\\Book On DF");
        printf("\\chapOne\\myBook\\chap-3\\figures\\myMexGetRgD for mex use myMexGetRgD.m\n");
        printf("!. D:\\Edu-Institutions\\UOH\\Research\\iRadar\\rdrImg\\rdrImg\\rdrImg.cpp for C solution\n");
        printf("!. This is for figures in the Book 4th Chapter\n");
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
            config = (double *)malloc(LenConfig * sizeof(double));
            for (i = 0; i < LenConfig; i++) config[i] = inputPr[i];
    }
    
    numberOfTgts = (int)(config[4]); numOfPhaseSpecSamples = (int)(config[5]);
    kmax = (int)(config[6]);
    cols = 5; rows = kmax * numberOfTgts;

    bins = (int *)malloc(numberOfTgts * sizeof(int));
    rcA[0] = (int)(config[7]); rcA[1] = (int)(config[13]); cby2 = rcA[1] / 2;
    maxNumberOfBlocks = (int)(config[14]);

    A = myAlloc2Complex(rcA[0], cby2);
    er = createA(A, datafile, config, matCount); matCount = matCount + 1;
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


	if (count == 0) D = myAlloc2(rows,cols);
    
//  .............
//  ..   

    int pksEr;
//  ......... code in c for radar ...................    
    clouds = getPar(A,config,bins,steering,doas,Mudoas,s,sAvg,Obj,S,rgMat,D,rcClouds,&pksEr,dd,En);
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
        count = 0;
        printf("!. ouput arguments[%d] clouds %d by %d\n",nlhs,rcClouds[0],rcClouds[1]);
        double r, phi, pi, xmu, ymu;
	    pi = atan(1.0) * 4.0;

        rows = rcClouds[0]; cols = rcClouds[1];
//        rows = rcClouds[0]; cols = rcClouds[1] + 2;
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
 //               xmu = clouds[p][3]; ymu = clouds[p][5]; // changes made on 8th Mar 2025 for book
 //		        r = sqrt(xmu * xmu + ymu * ymu);
//		        phi = atan2(ymu, xmu) * 180.0 / pi;
//               kt = 6*rows + p; dataPtr[kt] = r;  // added aditional columns
//               kt = 7*rows + p; dataPtr[kt] = phi;
        }
        blocks = blocks + 1;
        if (blocks == maxNumberOfBlocks)
        {
            matCount = 0; blocks = 0;
            fclose(fp);
            printf("!. File %s closed and all set to start again\n",datafile);
        }
        printf("!. Block Count [%d].%d\n",blocks,maxNumberOfBlocks);
    } else dataPtr[0] = count;
    

//  .............................................................    
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
    myFree2Complex(A, rcA[0]);
    myFree2Complex(S, rcA[0]);
    myFree2Complex(steering, numberOfTgts);
    myFree2Complex(steeringAvg, numberOfTgts);
    myFree2Complex(En, mm);

    myFree2(rgMat, numberOfTgts);
    myFree2(s, numberOfTgts);
    myFree2(Obj, numberOfTgts);

    free(sAvg); free(doas); free(Mudoas);
    return;
}