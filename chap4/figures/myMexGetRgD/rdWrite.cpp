#include "rdWrite.h"
#include "mex.h"
void myPrintfCom(complex*, int, int);
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
int createA(complex **A, char * datafile, double *config, int k)
{
	int numberOfTgts, r, c, cby2, flag;
	static int count[2];
//	double trueVal[4];
	int FFTsamples, i7Ti, rc[2], synthetic;
	FFTsamples = (int)(config[7]); i7Ti = (int)(config[9]);
	rc[0] = FFTsamples; rc[1] = 8;
	numberOfTgts = (int)(config[4]); synthetic = (int)(config[3]);
	synthetic = 0;
	r = rc[0]; c = rc[1]; cby2 = c / 2;
	//printf("!. int createA(%d)\n",k);
	if (k == 0) count[0] = 0;
	flag = rdRadar(A, rc, datafile, count, FFTsamples, i7Ti); // Obtain data from AFE
	printf("!. Data Complex Matrix A[%d] read from %s of size %d by %d\n",k,datafile,rc[0],cby2);

	return flag;
}



int rdRadar(complex **B, int *rc, char * fname, int * count, int FFTsamples, int i7Ti)
{
	float val = 0.0f; // !!. don't change this to double
	double *row;
	int k, r, c, i, flag = 1, rKt;
	int s, iMax, fEr;
	int fftsamples;
	double sum;
	//	int r1, c1;
	double** A{};
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//printf("!. int rdRadar(%d)\n",count[0]);
	r = rc[0]; c = rc[1]; flag = 0; rKt = 0;
	if (A == NULL) 	A = myAlloc2(r, c);
//	A = (double **)malloc(r * sizeof(double *));
//	for (i = 0; i<r; i++) A[i] = (double *)malloc(c * sizeof(double));

	//	char line[200];
	//  1st May 2017   Dr Kaluri Reserach House.
	//	row = (double *)malloc(225 * sizeof(double));
	//	iMax = 225; // that is how ti captures !!! 
	iMax = 128; // for i7 data !!!
	iMax = 512;
	if (FFTsamples == 512) iMax = 512;
	if (FFTsamples == 128)
	{
		if (i7Ti == 1) iMax = 128; // i7 data
		if (i7Ti == 0) iMax = 225; // ti data
	}
	row = (double *)malloc(c * sizeof(double));
	sum = 0.0;
	s = (iMax - rc[0]) / 2;
	if (count[0] == 0) 
    { 
        fEr = fopen_s(&fp, fname, "r"); 
        printf("!. opened file %s\n",fname);
    } 
    count[0] = count[0] + 1;
	if (fp == NULL) { printf("!.. Error opening file %s(%d)\n", fname, fEr); return -11; }
	else
	{
		rKt = 0;
		while (feof(fp) == 0)
		{
			for (i = 0; i < iMax; i++)
			{
				for (k = 0; k < c; k++)
				{
					fscanf_s(fp, "%f", &val);
					if (i >= s) { if (rKt < rc[0]) { A[rKt][k] = (double)(val); row[k] = (double)(val); } }
				}
				if (i >= s) { if (rKt < rc[0]) rKt = rKt + 1; }
				fscanf_s(fp, "%f", &val); // one more time stamp .. 31st May 2017
										  //				fscanf_s(fp, "%f", &val); // one more time stamp .. 31st May 2017
				count[1] = (int)(val);
				sum = sum + count[1];
								count[1] = i;
				//				printf("%d ..\n", i);
				//				for (k = 0; k < c; k++) printf("%3.4f ",row[k]);
				//				printf("time stamp %3.2f\n", val);
				//	complete reading a row
                if (feof(fp) != 0) break;
			}
            //printf("time stamp %3.2f\n", val);
            if (feof(fp) != 0) break;
            r2c(A, B, rc);
		    //printf("!. Normal End of loop %s[%d.%d] look %d\n", fname, rKt, k, count[1]); flag = 1; 
            return flag;
		}
	}
	if (feof(fp) != 0)
	{
		printf("!. End of File %s[%d.%d]@%d\n", fname, rKt, k, count[1]);
		fclose(fp);
		flag = -12;
//		getchar();
	}
	else
	{
		r2c(A, B, rc);
		printf("!. Normal End of loop %s[%d.%d] look %d\n", fname, rKt, k, count[1]); flag = 1; 
	}
	fftsamples = (int)(sum / iMax);
	if (fftsamples != count[1])
	{
		printf("!. Check %d match %d\n", fftsamples, count[1]);
		getchar(); 
		flag = -13;
	}
//	myFree2(A, r);
	return flag;
}


