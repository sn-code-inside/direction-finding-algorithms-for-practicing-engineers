#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
//#include "mex.h"   /* This one is required */
class complex
{ public: double r; double i; };
//  ............ prototype ...........................................
void printConfig(double*);
void usage();
double** getPar(complex**, double*, int*, complex**, double*, complex**, double**, double*,int*); 
void populate(complex**, int*, double, double);
int gFKmain(complex**, int* rcA);
int createA(complex **, char *, double *, int);
void preProc(complex **, complex **, double *, double *, int);
double detectBins(double *, double *, int *);
//void rgSteering(complex **, double *, int *, double **, double *, complex **);
double * rgSteering(complex **, double *, int *, double **, double *, complex **);
//void rgSteering(complex **, double *, int *, double **, double *, complex **,complex **);
double kMusic(complex **, complex **, double *, double *, double **);
double easyMusic(complex **, int *, double *, double *, double **,complex **, int);
void printComplxMatrix(complex **A, int rows, int cols);
void TransferData(int, int*, double*,double*, double*, double*, double**, int,int);
//void TransferData(int, int*, double*, double*, double*, double**, int,int);
double ** sortCluster(double**, int, int, int,int *,double *);
double** formClouds(double**, int*, int*,double);
double* myAlloc(int);
double** myAlloc2(int , int);
complex** myAlloc2Complex(int, int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
int seQ=0;
FILE * fp;
FILE* fpLog;
FILE * fpSortCluster;
FILE * fpClouds;
//  ..................................................................
