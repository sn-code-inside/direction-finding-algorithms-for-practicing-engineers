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
double* apf1(int, double, double*);
int myMax(double*, int);
void myMaxMin(double* , double*, int);
double** setWinDat(double**, int, int, int, int);
int fixWindow(double , int* , int* , int , int, int);
double** DetectSignalWindow(int*, double, int, int,double**,double**,double*);
int ChoseAPForder(double, double, int, double*, double*);
int phase(double* , double , int,double*);
int phiShift(double*, int, double*, double*, double,double*);
int processRkdot(double* , int);
//void mainDet(int, double, double, double, int, double**);
void myFree2(double**, int);
double** myAlloc2(int, int);
double* myAlloc(int c);


