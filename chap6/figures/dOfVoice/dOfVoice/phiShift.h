#pragma once
#include "string.h"
#include "stdafx.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cMath.h"

complex** ulaMatrix(double , double* , double* , double,double*,int, int,int*,double**);
//complex* filterInTime(double*, complex*, int, double, double*);
void filter(complex*, int, double, double*);
double* nbf(double*, double, int);
double findFn(double*, int);
double* nbf(double*, double, int);
double* apf1(int, double, double*);
double* apf2(int, double, double*);
double* apf3(int, double, double*);
int ChoseAPForder(double, double, int, double*, double*);
int estimateOrder(double, double, double*);
double angle2r(double, double, double, int*);
double* myAlloc(int);
double** myAlloc2(int, int);
complex* myAllocComplex(int);
complex** myAlloc2Complex(int, int);

