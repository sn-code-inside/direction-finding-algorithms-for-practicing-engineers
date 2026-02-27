#pragma once

#include <string.h>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
#include <direct.h> /* for _getcwd() and _chdir() */
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
class complex
{
public: double r; double i;
};
int findPeaks(int, int*, int*, double*);
int myMax(double*, int);
double DegPhase2Doa(double, double);
int SweeplocateDoaPks(int, int, double**, double*, double *);
double evalObj(complex**, double, int, double, int, double*);
double* gMusic(int, complex**, double*, double*, double*, double*, double, int, int);
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
void myFree(double*);
void myFree2(double**, int);
int** myAlloc2I(int, int);
void myFree2I(int**, int);
double* myAlloc(int);
int* myAllocI(int);
double** myAlloc2(int,int);
void myFree2Complex(complex**, int);

