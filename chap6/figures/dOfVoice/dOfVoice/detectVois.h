#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//extern  FILE *fpWav;
int DetectVoice(int, double*, double*, int*);
void ortho(int, double*, double*);
void NBF(int, double*, double*);
//int VoiceChunk(int , char *, double *, int);
//int wavHeader(char *, double *, int *);
//int wavData(char *, double *, int, double *, int *,int);
//int pitchParts(int, int, double*, char*, double*, int);
double* myAlloc(int);
