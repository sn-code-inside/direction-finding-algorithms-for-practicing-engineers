#pragma once
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
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
class complex
{ public: double r; double i; };
//int myMax(double *, int);
double ortho(int, complex *);
double normalize(int, complex *, complex *);
void timeAvg(complex **, complex *, int *, int);
void SpekAvg(double **, double *, int *);
void sampleSpek(complex *, double *, int, int);
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
double** myAlloc2(int, int);
double* myAlloc(int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);


