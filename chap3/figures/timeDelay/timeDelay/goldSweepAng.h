#pragma once
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//double* nbf(double*, double, int);
//double findFn(double*, int);
//double* nbf(double*, double, int);
//double goldR(int , double* , double*, double, double, int);
double goldAngle(int, double, double*, double*, double, double, int);
double objAngle(int, double, double, double*, double*);
double* sweepAngle(int , double* , double* ,double*, double, int);
double* linspace(double , double , int);
double r2angle(double , double);
double* apfNew(int, double, double, double*);
void ApplyFilter(int , int , double , double* , double*);
void ApplyDoubleFilter(int , int , double , double* , double*);
//int ChoseAPForder(double, double, int, double*, double*);
//int estimateOrder(double, double, double*);
//double angle2r(double, double, double, int*);
double* myAlloc(int);
double** myAlloc2(int, int);

