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
double** ExpData(int, double, double, double, int,double*);
double** DetectSignalWindow(int*, double, int, int,double**,double**,double*);
void myFree2(double**, int);
double** myAlloc2(int, int);
void mainDet(int,double,double,double,int,double**);
double mainDelay(int, double, double, double, int, int, double**,double*);
//double estDelay(double*, double**, int, int, double);
double fineR(double*, double*, double*,double,int,double*,double*);
char* getDate();
void usageSigWin();


