#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"

int VoiceChunk(int , char *, double *, int);
double** processWav(int, int, double*, double*, complex*, int*, int*);
int wavHeader(char*, double*, int*);
int pitchParts(int, int, double*, char*, double*, int);
int subsample(complex*, int, int, double*);
double detectBins(double*, double*, int*);
int pitchEnergy(int, int*, int, int, int, double*, double*, double**);
int** getCloudPointers(double*, int, int*);
double* lineCluster(int, int, double*, int, double*);
int** CompactPitch(double *, int** , int , int* , double);
void mergePitch(int**, int, int);
double distMeasurePitch(double, double);
int myMax(double *, int);
int* Low2High(int, double *);
int* Low2HighComplexOnReal(int , complex*);
double* myAlloc(int);
int* myAllocI(int);
double** myAlloc2(int,int);
complex* myAllocComplex(int);
void myFree2(double**, int);
FILE *fpWav;
