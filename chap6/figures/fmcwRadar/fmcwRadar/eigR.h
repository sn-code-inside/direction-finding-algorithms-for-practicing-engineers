#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class complex
{ public: double r; double i; };
void eigenvecH(complex **, complex **, double *, double *, int *, int);
void sortEigOnVal(double **, double *, complex **, double *, int);
int hholdc(double  **, double  **, double  **, int);
void qrstc(double**, int, double**, double**, double*, double*, int*);
complex ** myAlloc2Complex(int, int);
double** myAlloc2(int, int);
double* myAlloc(int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);

