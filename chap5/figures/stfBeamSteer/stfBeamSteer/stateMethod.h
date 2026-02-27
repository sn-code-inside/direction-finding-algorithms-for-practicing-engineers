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
complex** myAlloc2Complex(int, int);
complex* myAllocComplex(int);
double** myAlloc2(int, int);
int** myAlloc2I(int, int);
int* myAllocI(int);
double* myAlloc(int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
void myFree2I(int**, int r);
double** stfDoa(double**, double, double, int, int, double*, int, double**);
int map3ula(complex*, int, double*);
//int scanAllDoa(double**,double*,int,int*);
int* extractTgt(double**, double*, int, int*);
complex doa2weights(double);
double  fixPeaks(complex*, int);
int distCheck(complex*, int);
void resize(double**, int*, int);
double* JacobiRotation(double**, int, int);
double* stateDecode(double** , int , int , int*);
//void allDist(double** , int, int);
double rotateUla(double, double);
