#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"
int* wavBins(int, int, double*, double*);
double* anf(double*, int,double);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
double* Hermit(complex**, int*, int, double*, int, int, complex**,double);
complex** ulaMatrix(double, double*, double*, double,double*,int, int,int*,double**);
int VoiceChunk(int, char*, double*, double *,int *, int,double *,double *);
double findFn(double* , int);
int audioBlock(int , double* , int *, char* , int );
double* myAlloc(int);
double** myAlloc2(int, int);
int* myAllocI(int);
complex* myAllocComplex(int);
complex** myAlloc2Complex(int,int);
void myPrintfX(int*, int, int);

FILE* fpWav;
