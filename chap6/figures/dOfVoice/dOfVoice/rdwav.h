#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
extern  FILE *fpWav;
//int VoiceChunk(int , char *, double *, double *,int);
int VoiceChunk(int, char*, double*, double*, int*, int, double*,double *);
int wavHeader(char *, double *, int *);
int wavData(char *, double *, int, double *, int *,int *,int);
int pitchParts(int, int, double*, double*,int *, char*, double*, int,double *);
double* myAlloc(int);
