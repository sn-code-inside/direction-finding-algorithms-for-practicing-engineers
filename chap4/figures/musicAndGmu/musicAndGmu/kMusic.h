#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include "cMath.h"
class complex
{
public: double r; double i;
};
typedef struct _Target
{
	int bin[3];			// Target bin number ( gFK.cpp line 96 ) and ID and extra reserved 7.12.2017
	double doa;			// DOA of the target ( mLern.cpp ..118 .. from kMusic.cpp )
	double doaPks[3];	// DOA peaks in kMusic.cpp ( mLern.cpp ..118 .. from kMusic.cpp )
	double amp;			// spectral average at the bin # ( gFK.cpp line 97)
	double range;		// mean frequency or range ( gFK.cpp line 101 .. postman)
	double fn[10];		// gFK frequency at each channel ( gFK.cpp line 96 )
	double fnQ[10];		// gFK frequency at each channel Sharpness ( gFK.cpp line 96 )
	double gain[10];	// scale factor of each channel in normalisation ( gFK.cpp line 93 )
	double phi[10];		// phase of the phasor ( gFK.cpp line 94 )
	double A[10];		// amplitude of the phasor ( gFK.cpp line 95 )
	double mlR[10];		// real part of model parameters ( mLern.cpp ..120 .. from kP.cpp )
	double mlI[10];		// imag part of model parameters ( mLern.cpp ..121 .. from kP.cpp )
	double extent[3];   // dimensions of the target vector ( kMusic.cpp .. line 110 and 111 )
	double velocity[3]; // Velocity x and y and radial Velocity
	double x;
	double y;
} Target;
//class complex
//{ public: double r; double i; };
complex* myAllocComplex(int);
double** myAlloc2(int, int);
double* myAlloc(int);
void myFree2(double**, int);

extern const int PRINT_FLAG = 0;
void myPrintf(double *, int, int);
//void TransferTgtPar(Target *, double *, int);
double tgtDoa(double *, double *, double *, double *, complex *, int, double *, int,double *);
double QofDOA(double *, complex *,  int, double *, double *, double *, double *, int, int,int);
void getExtent(double *, double *, double);
double howGoodDoa(double *, int);
double DoaDistortion(double *, complex *, double *, double *,int, int,int);
int findPeaks(int, int *, int *, double *);
int myMax(double *, int);
int locateDoaPks(int, int, double **, double *);
int SweeplocateDoaPks(int, int, double**, double*, double*);
//void sortLow2High(double *, int *, int);
//void getDoa(double **, double *, double *, double *, int);
double pObj(complex *, double, int);
//complex cadd(complex, complex);
//complex cmul(complex, complex);
//double cabs(complex);
void goldDoa(int, complex *, double *, double *, double *, int,int);
class sort
{
public:
	double *x;
	int *xI, M;
	void High2Low();
	void Low2High();
	void showx();
};
class cadd :public complex
{
public:
	complex a, b;
	complex add(complex a, complex b);
};
class cmul :public complex
{
public:
	complex a, b;
	complex mul(complex a, complex b);
};
class Cabs :public complex
{
public:
	complex a;
	double cabs(complex a);
};

//extern FILE *fpLog;
//extern FILE *fpMusic;