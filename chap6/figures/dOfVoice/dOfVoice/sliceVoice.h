#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"
double* anf(double* , int,double);
int DetectVoice(int, double*, double*, int*);
//int VoiceChunk(int, char*, double*, int,double*);
void myPrintf(double* , int , int );
int audioBlock(int , double* , int *, char* , int);
int blockOfWav(int, int, double*, int *, char*, double*);
double findFn(double* , int);
double* nbf(double* , double, int);
//double** processWav(int, int, int, int, double*, double*, complex*, int*,double**,int *);
//double** processWav(int, int, int, double*, double*, complex*, int*, int*);
int wavHeader(char*, double*, int*);
//int pitchParts(int, int, double*, char*, double*, int);
complex* myAllocComplex(int);
int detectBins(double*, double*, int*);
//double** pitchEnergy(int, int*, int, int, int, double*, double*);
int pitchEnergy(int, int*, int, int, int, double*, double*, double**);
//int** getCloudPointers(double*, int, int*,int);
//int** CompactPitch(double*, int**, int, int*, double);
double* myAlloc(int);
double** myAlloc2(int, int);
void myFree2(double**, int);