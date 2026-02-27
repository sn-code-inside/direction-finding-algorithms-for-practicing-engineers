#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class complex
{
public: double r; double i;
};

void fillA(complex**, int*);
int rdConfig(double*, char *);
int createA(complex** , char* , double* , int );
double* eigHermitian(complex** , int* , complex**,double*,int*);
void eigenvecH(complex**, complex**, double*, double*, int*, int);
void CeqABtrnsp(complex**, complex**, int, int, const char*);
void sortEigOnVal(double **, double *, complex **, double *, int);
void myNoise(int , double , double* );
void printComplxMatrix(complex** , int, int);
complex** myAlloc2Complex(int, int);
double** myAlloc2(int, int);
complex* myAllocComplex(int);
double* myAlloc(int);
int* myAllocI(int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
void myFree(double*);


class Cabs :public complex
{
public:
	complex a;
	double cabs(complex a);
};
class cmul :public complex
{
public:
	complex a, b;
	complex mul(complex a, complex b);
};
class cadd :public complex
{
public:
	complex a, b;
	complex add(complex a, complex b);
};
class conjmul :public complex
{
public:
	complex a, b;
	complex mulconj(complex a, complex b);
};
void CeqABtrnsp(complex**, complex**, int, int, const char*);
FILE* fp; FILE* fpLog;
