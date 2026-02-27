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
double* myAlloc(int c);
//double filter(double, double);
//double Tau(double);
//double findR(double);
int xCross(int , double* , double* , double* , double*);
int shiftByDelay(double* , double* , int , int);
double ObjJk(double*, double*, int);
void ShiftC(double*,int);
void moveX2Y(double*, double*, int);
int CoarseN(double* , double* , double*, double* , int);
double estDelay(double*,double**,int,double,double*,double*,int);



