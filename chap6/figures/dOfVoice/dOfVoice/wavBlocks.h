#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"
int wavHeader(char*, double*, int*);
int wavData(char*, double*, int, double*, int *,int*, int);
int pitchParts(int, int, double*, double*, int *,char*, double*, int,double *);
int blockOfWav(int, int, double*, int *,char*, double*);
double* filterInTime(double* , double*, int, double, double*);
void filter(complex*, int,double,double*);
int subsample(double*, int, int, double*);
//double detectBins(double*, double*, int*);
double* myAlloc(int);
int stdMuLin(double*, double*, double*, int);
int wavlet(double*, int, int*, int, int, double*);
int pitchEnergy(int, int*, int, int, int, double*, double*, double**);
int myMax(double*, int);
void Kalman(double*, int, int);
double** myAlloc2(int, int);
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
double* myAlloc(int);
void myFree2(double**, int);
void myFree2Complex(complex**, int);

extern FILE* fpWav;
