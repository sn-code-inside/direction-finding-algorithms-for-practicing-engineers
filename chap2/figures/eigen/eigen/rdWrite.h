#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
class complex
{ public: double r; double i; };
//void preProc(complex **, complex **, complex *, double **, double *, int *, int);
int createA(complex**, char*, double*, int);
//int genTgts(complex **, int, int *, double, double *, double *, double *, double);
//int myTgtData(complex **, int *, double, int, int, double **, int *);
void myNoise(int, double, double *);
//int getA(complex **, int *, int,double *);
//int rdTgtFile(double **, int *, char *);
int rdRadar(complex **, int *, char *, int *, int, int);
void r2c(double **, complex **, int *);
void comMatAdd(complex **, complex **, int *);
double** myAlloc2(int, int);
void myFree2(double**, int);
extern FILE *fp;
extern FILE *fpSyn;


