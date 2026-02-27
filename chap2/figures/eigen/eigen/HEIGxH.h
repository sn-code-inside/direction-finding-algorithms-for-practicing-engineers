#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class complex
{ public: double r; double i; };
void myPrintf(double* , int , int);
double* eigHermitian(complex**, int*, complex**,double*,int*);
int eigenvecJ(complex**, int, complex**, double*, double*, int*);
void eigenvecR(double **, int, double **, double *,double*,int*); // eigenvecR(bi, M, Ev, L,Jk,JkL);
void eigenvecH(complex **, complex **, double *, double *, int *, int);
void sortEigOnVal(double **, double *, complex **, double *, int);
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
void CeqABtrnsp(complex **, complex **, int, int, const char *);
//extern FILE *fpDeg;
