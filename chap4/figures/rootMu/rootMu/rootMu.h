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
class complex
{ public: double r; double i; };
//int mainLocal(int, char **);
//double* initRdr(char*, char*, char*, char*, char*, int, char**);
//double* initRdr(char*, char*, int, char**);
//void usage(double *, char *);
//void outonfiles(double *, complex **, double **, double *, double *, int *,double**,double *,double **,complex **);
//void myAngleDeg(double *, double *,complex *, int);
//int* sortData(double* , int );
//int** getCloudTotalPt(double*, int, int, int*);
//double** pointers2clouds(int**, int*, double*, int);
//int** CompactClouds(double**,int*, int*,double);
void myNoise(int, double, double*);
double** segment(double*, int*,int, int,double);
//complex** myAlloc2Complex(int, int);
double* myAlloc(int);
//void myFree2Complex(complex**, int);
double** myAlloc2(int, int);
int* myAllocI(int);
void myFree2(double**, int);
void myFree(double*);
int* Low2High(int, double*);

