#pragma once
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//double* nbf(double*, double, int);
//double findFn(double*, int);
//double* nbf(double*, double, int);
double goldR(int , double* , double*, double, double, int);
double obj(int , double , double*, double*);
double* sweepR(int , double* , double* ,double*,int);
double* linspace(double , double , int);
double r2angle(double , double);
double* linspace(double, double, int);
double angle2r(double, double, double, int*);
//double* apf1(int, double, double*);
double* apf2(int, double, double*);
//double* apf3(int, double, double*);
//int ChoseAPForder(double, double, int, double*, double*);
//int estimateOrder(double, double, double*);
//double angle2r(double, double, double, int*);
double* myAlloc(int);
double** myAlloc2(int, int);

