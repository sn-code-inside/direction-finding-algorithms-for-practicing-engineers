#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class complex
{ public: double r; double i; };
void myAngleDeg(double *, double *,complex *, int);
//void sortHigh2Low(double *, int *, int);
//void sortLow2High(double *, int *, int);
void muStd(double *, double *, double *, int);
double ortho(int, complex *);
double normalize(int, complex *, complex *);
void MatrixInversion(double **, int, double **);
void myNoise(int, double, double *);
void myPrintfCom(complex *, int, int);
void myPrintf(double *, int, int);
void myPrintfI(int *, int, int);
int myMax(double *, int);
void myMaxMin(double *, double *, int);
int * Low2High(int , double*);
void sampleSpek(complex *, double *, int, int);
void comMatAdd(complex **, complex **, int *);
int stdMuLin(double*, double*, double*, int);
int lineCluster(int, int, double*, int, double*);
//double cabs(complex);
class cadd :public complex
{
public:
	complex a, b;
	complex add(complex a, complex b);
};
class csub :public complex
{
public:
	complex a, b;
	complex sub(complex a, complex b);
};
class cmul :public complex
{
public:
	complex a, b;
	complex mul(complex a, complex b);
};
class conjmul :public complex
{
public:
	complex a, b;
	complex mulconj(complex a, complex b);
};
class Conj :public complex
{
public:
	complex a;
	complex conj(complex a);
};
class Cabs :public complex
{
public:
	complex a;
	double cabs(complex a);
};
class cdiv :public complex
{
public:
	complex a,b;
	complex div(complex a, complex b);
};
void r2c(double **, complex **, int *);
