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
void printComplxMatrix(complex**, int rows, int cols);
void printMatrix(double**, int, int);
complex** myAlloc2Complex(int, int);
double** myAlloc2(int, int);
complex* myAllocComplex(int);
double* myAlloc(int);
int* myAllocI(int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
void myFree(double*);
int* High2Low(int, double*);
complex** mySvd(complex**, complex**,int*, int,double*);
complex** Hermit(complex**, int*, int, double*);
void eigenvecH(complex**, complex**, double*, double*, int*, int);
void myPrintfCom(complex*, int, int);
complex** covMat(complex*, int,int*,int);
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
void CeqABtrnsp(complex**, complex**, int*, const char*);
complex** CeqAB(complex**, int*, complex**, int*, int*, const char*);
void LSQ(complex**, int*);
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
complex** SquareMatMul(complex** , complex** , int , const char*);