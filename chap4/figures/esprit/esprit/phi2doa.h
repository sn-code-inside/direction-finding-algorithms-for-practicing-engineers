#pragma once
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
int* High2Low(int, double*);
void myPrintf(double*, int, int);
complex* eigPhi(complex** , complex** , int);
complex** Hermit(complex**, int*, int, double*);
complex** Svd2Lsq(complex**, int*, int, int*);
complex** MoorePenrose(complex**, int*, int*);
complex** AconjTranspose(complex**, int*);
complex** CeqAB(complex**, int*, complex**, int*, int*, const char*);
double** complex2real(complex**, int, double*);
void MatrixInversion(double**, int, double**);
void CeqABtrnsp(complex**, complex**, int*, const char*);
double DegPhase2Doa(double, double);
//double* gMusic(int, complex**, double*,double*, double*, double*, double,int, int);
//int locateDoaPks(int, int, double **, double *);
void myMaxMin(double*, double*, int);
//double evalObj(complex **, double, int, double,int,double *);
void printComplxMatrix(complex**, int rows, int cols);
void printMatrix(double**, int, int);
void eigenvecR(double**, int, double**, double*, double*, int*); // eigenvecR(bi, M, Ev, L, Jk, JkL);
void eigenvecH(complex**, complex**, double*, double*, int*, int);
void sortEigOnVal(double**, double*, complex**, double*, int);
void sampleSpek(complex*, double*, int, int);
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
void CeqABtrnsp(complex**, complex**, int*, const char*);
//extern FILE *fpDeg;
