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
//double** sortCluster(double**, int, int, int, int*, double*);
//int stripNaddFile(char*, char*, char*, char*);
//char* getDate();
//char* fileDetails(char*, int*);
void pause(int dur);
//double** formClouds(double**, int*, int*,double);
double** segment(double*, int*, int, int, double);
//int** getCloudLinPt(double*, int, int, int*);
//int** getCloudTotalPt(double*, int, int, int*);
//double** pointers2clouds(int**, int*, double*, int);
//int** CompactClouds(double**, int*, int*, double);
//int* sortData(double*, int);
//void muStd(double *, double *, double *, int);
//int lineCluster(int, int, double*, int, double*);
//int * ExchangEpkandPk(double*, int*, int*, double*, int*, int*);
//void sortInd(int**, int);
//int* Low2High(int, double*);
//int** getCloudLinPtUp(double*, int, int, int*);
//int splitLin(double*, int*, double*, int *,double*, int*, double*, int, int*, int*);
//int splitLinUp(double*, int*, double*, double*, int*, double*, int, int*, int*);
//int stdMuLin(double*, double*, double*, int);
void myFree(double*);
int** myAlloc2I(int, int);
void myFree2I(int**, int);
double* myAlloc(int);
int* myAllocI(int);

