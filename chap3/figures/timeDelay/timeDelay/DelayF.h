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
double orthoRfine(int, double*, double*, double*, double*, double);
double r2angle(double , double);
double* apf2(int, double, double*);
double* apfNew(int, double, double, double*);
double* sweepR(int, double*, double*, double*, int);
double* sweepAngle(int, double*, double*, double*, double, int);
//double* fineR(double*, double*, double, int, double*, double*, int);
double* fineR(double*, double*, double, int, double*, double*, double*, int*);
double* fineAngle(double*, double*, double, int, double*, double*, double*, int*);
double* myAlloc(int);
//void ShiftF(double* , double* , double , int);
void filter( double , double *, double*,int);
double Tau(double);
double findR(double);
double ObjJkF(double*, double*, int);
void moveX2Y(double*, double*, int);
double ortho(int, double*, double*,double,double*);
