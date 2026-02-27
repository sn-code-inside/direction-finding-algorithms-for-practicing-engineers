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
double** myAlloc2(int, int);
int** myAlloc2I(int, int);
int* myAllocI(int);
double* myAlloc(int);;
void myFree2(double**, int);
void myFree2I(int**, int r);
void resize(double**, int*, int);
//double* JacobiRotation(double**, int, int);
//double* stateDecode(double**, int, int, int*);
double rotateUla(double, double);
int* rotateAndExtract(double**, double *, int, int);
int rotationMatch(double* , int , int* , double*);
double* rotateDecode(double** , int, int, int*);

