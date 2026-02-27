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
complex** IQ(int *,int,double *,double*,double,double,double,double *);
//double* Hermit(complex**, int*, int, double*, int, int, complex**,double);
char* getDate();
void usageIQ();
