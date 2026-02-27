#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class complex
{ public: double r; double i; };

//void myPrintfCom(complex *, int, int);
//void myPrintfI(int *, int, int); 
//void myPrintf(double *, int, int);
int myMax(double *, int);
double normalize(int, complex *, complex *);
//int findPeaks(int, int *, int *, double *);
double ObjFn(double *, int, double, complex *);
double goldF(int, complex *, double *, double *, double *,complex *,double *, int,double);
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
class cdiv :public complex
{
public:
	complex a, b;
	complex div(complex a, complex b);
};
class Cabs : public complex
{
public:
	complex a;
	double cabs(complex a);
};
