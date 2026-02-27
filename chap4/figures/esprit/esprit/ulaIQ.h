#pragma once
#include <string.h>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
#include <direct.h> /* for _getcwd() and _chdir() */
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ctime>
class complex
{
public: double r; double i;
};
class imagex
{
public:
	int precision, ima_ht, ima_wd, num_of_comps;
	unsigned char*** data;
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
void printComplxMatrix(complex** A, int rows, int cols);
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
double** myAlloc2(int, int);
int** myAlloc2I(int, int);
char** myAlloc2char(int, int);
double* myAlloc(int);
int* myAllocI(int);
void ImageMemAlloc(imagex*);
void myFree3(int, int, int, unsigned char***);
void ImageMemFree(imagex*);
int myAlloc3(int, int, int, unsigned char***);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
void myFree2I(int**, int);
complex ** GenerateSignals(
    int , /* each ULA has M elements */
    int , /* number of snapshots */
    int , /* number of emitters */
    double* , /* doa angles in degrees -180 to +180 */
    double* , /* signal relative ratios */
    double* , /* signal initial phases in degrees */
    double , /* d by lambda */
    double , /* fc/fs or sampling rate */
    double , /* ULA normal angle with true North in degrees */
    double , /* sigma of the WGN */
    double*  /* SNR */
);
void myNoise
(
    int ,
    double ,
    double*
);
complex** gnoise(int, int, double, double*);
double powerOfMat(int , int , complex**);
complex** signalMat
(
    int ,     /* each ULA has M elements */
    int ,     /* number of snapshots */
    double ,  /* fc/fs or sampling rate */
    int** ,   /* integer modulation +1 or -1 */
    double* , /* doa angles in degrees -90 to +90 */
    double* , /* signal relative ratios */
    double* , /* signal initial phases in degrees */
    double ,  /* ULA normal angle with true North in degrees */
    double ,  /* d by lambda */
    double* , /* signal power */
    int D     /* number of emitters */
);
