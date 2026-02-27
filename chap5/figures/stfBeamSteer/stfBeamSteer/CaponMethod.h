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

double** myAlloc2(int, int);
int** myAlloc2I(int, int);
int* myAllocI(int);
double* myAlloc(int);
//void myFree2Complex(complex**, int);
void myFree2(double**, int);
void myFree2I(int**, int r);
double obj(double**, double, double, double, int);
double* linspace(double, double, int);
int* findPeaks(int, int*, double*);
int myMax(double*, int);
//int locateDoaPks(int, int, double**, double*);
int SweeplocateDoaPks(int, int, double**, double*, double*);
double** stfDoaCapon(double**, double, double, int, int, double*, int, double**);
double* goldDoa(int, double**, double, double*, double, int);
double* CaponWeight(double, double, double, int);
double* linspace(double, double, int);
double wTranposeHmulW(double**, double*, int);
double objCapon(double**, double, double, double, int);
