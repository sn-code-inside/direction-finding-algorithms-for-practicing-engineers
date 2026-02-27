// rootMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "sweepFine.h"
#include "mex.h"   /* This one is required */





void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputNumberOfSamples,*inputEr,*inputEi,*inputSE;
    double* outTheta, * outObj, *outGoldJk, *outJkMu,*outDoaMu;
    //double** thetaNr,**B,**C,**D;
    double s,e, sPhi,ePhi,doaInDeg,dbyl = 0.5,delth;
    double* phi,*obj,*Lh,*theta;
    double** AB, ab[2],boundsPhi[2];
    double* JkMu, * doaMu,**goldJk;
    double pi = 4.0 * atan(1.0);
    int NumberOfSamples, indxFlag, numberOfPks;
    int p,r,c,i,k,kt,rEn,cEn,cby2,D,NGS=15;
    complex** En;

    if ((nlhs != 5) || (nrhs != 3))
    {
        printf("!. New Function created for book 15th Feb 2025 5pm Princeton NJ\n");
        printf("!. Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(3) \n", nlhs, nrhs);
	    printf("1. [theta muSpk gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples)\n");
        printf("2. En is noise Eigen Vectors of Covariance Matrix\n");
        printf("3. SE is a two vector start and end DOA sweep in degrees\n");
	    printf("4. NumberOfSamples to be evaluated\n");
        printf("5. theta is the DOA sweep vector\n");
        printf("6. muSpk is the MUSIC spectrum in the sweep\n");
        printf("7. gJk gold-convergence\n");
        printf("8. doaMu is gMUSIC output\n");
        printf("9. JkMu is the response at doaMu\n");
        return;
    }

    rEn = (int)(mxGetM(prhs[0])); cEn = (int)(mxGetN(prhs[0]));
    inputEr = mxGetPr(prhs[0]); inputEi = mxGetPi(prhs[0]);
    En = myAlloc2Complex(rEn, cEn);
    for (p = 0; p < rEn; p++) // rows
    {
        for (i = 0; i < cEn; i++)
        {
            kt = i * rEn + p;
            En[p][i].r = inputEr[kt];
            En[p][i].i = inputEi[kt];
        }
    }
    //printf("size of noise eigen matrix %d by %d\n", rEn, cEn);
    cby2 = cEn; D = cEn - rEn; numberOfPks = D;
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if (c != 2) {mexErrMsgTxt("!. prhs[1] must be a two vector\n");}
    else {if (r != 1) {mexErrMsgTxt("!. prhs[1] must be a scalar\n");}}
    inputSE = mxGetPr(prhs[1]); 
    s = inputSE[0]; e =  inputSE[1];
    if (fabs(s) > 90.0) { mexErrMsgTxt("!. invalid range rhs[1]\n"); }
    if (fabs(e) > 90.0) { mexErrMsgTxt("!. invalid range rhs[1]\n"); }
    if ( (e - s) < 0.0 ) { mexErrMsgTxt("!. invalid range range of s and e\n"); }

    r = (int)(mxGetM(prhs[2])); c = (int)(mxGetN(prhs[2]));
    if (r != c) { mexErrMsgTxt("!. prhs[2] must be a scalar\n"); }
    else { if (r != 1) { mexErrMsgTxt("!. prhs[2] must be a scalar\n"); } }
    inputNumberOfSamples = mxGetPr(prhs[2]);
    NumberOfSamples = (int)(inputNumberOfSamples[0]);
    sPhi = 360 * dbyl * sin(s * pi / 180); boundsPhi[0] = sPhi;
    ePhi = 360 * dbyl * sin(e * pi / 180); boundsPhi[1] = ePhi;

 //   printf("s %3.4f e %3.4f %d\n", s, e,NumberOfSamples);
    phi = myAlloc(NumberOfSamples); obj = myAlloc(NumberOfSamples);
    theta = myAlloc(NumberOfSamples);
    AB = myAlloc2(numberOfPks, 4);
    Lh = myAlloc(cby2);
    delth = (ePhi - sPhi) / (double)(NumberOfSamples - 1.0);
    for (k = 0; k < NumberOfSamples; k++)    phi[k] = k * delth + sPhi;

    for (k = 0; k < NumberOfSamples; k++)
    {
        doaInDeg = DegPhase2Doa(phi[k], dbyl);
        theta[k] = doaInDeg;
        obj[k] = evalObj(En, doaInDeg, cby2, dbyl, D, Lh);
    }
    indxFlag = SweeplocateDoaPks(NumberOfSamples, numberOfPks, AB, obj,boundsPhi);
    if (indxFlag < 0)  numberOfPks = abs(indxFlag);

    JkMu = myAlloc(numberOfPks); doaMu = myAlloc(numberOfPks);
    goldJk = myAlloc2(numberOfPks, NGS);
    for (k = 0; k < numberOfPks; k++)
    {
        ab[0] = DegPhase2Doa(AB[k][0], dbyl); ab[1] = DegPhase2Doa(AB[k][1], dbyl);
    //    printf(" %d .. (%3.4f  %3.4f) max obj %3.4f\n", (int)(AB[k][2]),ab[0], ab[1],AB[k][3]);
        goldJk[k] = gMusic(cby2, En, Lh, &JkMu[k], &doaMu[k], ab, dbyl, D, NGS);
    //    printf("!. gold peak[%d] %3.4f at %3.4f\n\n", k,JkMu[k], doaMu[k]);
    }



//  output parameters
    plhs[0] = mxCreateDoubleMatrix(1, NumberOfSamples, mxREAL);
    outTheta = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(1, NumberOfSamples, mxREAL);
    outObj = mxGetPr(plhs[1]);
    for (k = 0; k < NumberOfSamples; k++)
    {
        outTheta[k] = theta[k]; outObj[k] = obj[k];
    }
    plhs[2] = mxCreateDoubleMatrix(numberOfPks, NGS, mxREAL);
    outGoldJk = mxGetPr(plhs[2]);
    for (p = 0; p < numberOfPks; p++) // rows
    {
        for (i = 0; i < NGS; i++)
        {
            kt = i * numberOfPks + p;
            outGoldJk[kt] = goldJk[p][i];
        }
    }
    plhs[3] = mxCreateDoubleMatrix(1,numberOfPks,mxREAL);
    outDoaMu = mxGetPr(plhs[3]);
    plhs[4] = mxCreateDoubleMatrix(1, numberOfPks, mxREAL);
    outJkMu = mxGetPr(plhs[4]);
    for (k = 0; k < numberOfPks; k++)
    {
        outDoaMu[k] =  doaMu[k];
        outJkMu[k] = JkMu[k];
    }

    myFree2Complex(En, rEn); myFree2(goldJk, numberOfPks);
    free(phi); free(theta); free(Lh); free(obj);



    return;
}
