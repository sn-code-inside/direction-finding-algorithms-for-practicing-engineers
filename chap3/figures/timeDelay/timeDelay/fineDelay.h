#pragma once
#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
//#include "mex.h"   /* This one is required */
//int ChoseAPForder(double, double, int, double*, double*);
//double** ExpData(int, double, double, double, double,double,double*);
//double** DetectSignalWindow(int*, double, int, int,double**);
void myFree2(double**, int);
double** myAlloc2(int, int);
double* myAlloc(int c);
//double fineR(double*, double*,double,int,double*,double*,int);
double* fineR(double*, double*, double, int, double*, double*, double *,int*);
double* fineAngle(double*, double*, double, int, double*, double*, double*, int*);
char* getDate();
void usageDelay();

