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
double** sortCluster(double**, int, int, int, int*, double*);
int stripNaddFile(char*, char*, char*, char*);
char* getDate();
char* fileDetails(char*, int*);
void pause(int dur);
double** formClouds(double**, int*, int*,double);
int** getCloudLinPt(double*, int, int, int*,int);
//int** getCloudLinPtUp(double*, int, int, int*);
int splitLin(double*, int*, double*, double*, int*, double*, int, int*, int*,int);
//int splitLinUp(double*, int*, double*, double*, int*, double*, int, int*, int*);
int stdMuLin(double*, double*, double*, int);
int myMax(double *, int);
double* myAlloc(int);
void myFree(double*);
int** getCloudPointers(double*, int, int*,int);