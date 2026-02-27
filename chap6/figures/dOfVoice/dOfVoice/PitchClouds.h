#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"
int* wavBins(int, int, double*, double*);
int detectPeakPeaks(double*, double*, int*);
double** pitchClusters(int, double*, int, int*, int*);
//double** processWav(int, int, int, double*, double*, complex*, int*, int*);
double** processWav(int, int, double*, double*, complex*, int*, int*);
int wavHeader(char*, double*, int*);
//int pitchParts(int, int, double*, char*, double*, int);
complex* myAllocComplex(int);
int detectBins(double*, double*, int*);
int pitchEnergy(int, int*, int, int, int, double*, double*, double**);
int CompactPitch(double*, int**, int*, double);
int** getCloudPointers(double*, int, int*,int);
void mergePitch(int**, int, int);
double distMeasurePitch(double, double);
int myMax(double*, int);
double* myAlloc(int);
void myFree2(double**, int);
double** myAlloc2(int, int);
int* myAllocI(int);
extern FILE* fpWav;
