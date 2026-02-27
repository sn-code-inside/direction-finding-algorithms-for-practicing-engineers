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
/*double ** getPar
(
    complex **, 
    double *, 
    int *,
    complex **,
    double *,
    double *, 
    double **,
    double *,
    double **,
    complex **,
    double **, 
    double **,  
    int *,
    int *);*/
double** LookObjects(int, char*,double *,int*);
double* initRdr(char*, char *,int, char**);
void usage(double *, char *);
complex** myAlloc2Complex(int, int);
double* myAlloc(int);
void myFree2Complex(complex**, int);
double** myAlloc2(int, int);
char** myAlloc2char(int, int);
void myFree2(double**, int);
void myFree(double*);
int* Low2High(int, double*);
double** processRdr(int, char*, double*, double**, int*,int*);
double** getLooksData(double*, char*, int,int *);
int openCSVfiles();
int closeAllFile();

//int createA(complex **, char *, double *, int);
//void preProc(complex **, complex **, double *, double *, int);
//double detectBins(double *, double *, int *);
//void rgSteering(complex **, double *, int *, double **, double *, complex **);
//double * rgSteering(complex **, double *, int *, double **, double *, complex **);
//void rgSteering(complex **, double *, int *, double **, double *, complex **,complex **);
//double kMusic(complex **, complex **, double *, double *, double **);
//double easyMusic(complex **, int *, double *, double *, double **);
//void TransferData(int, int*, double*,double*, double*, double*, double**, int,int);
//void TransferData(int, int*, double*, double*, double*, double**, int,int);
//double ** sortCluster(double**, int, int, int,int *,double *);
//double** formClouds(double**, int*, int*,double);
int seQ=0;
extern FILE * fp;
extern FILE* fpLog;
extern FILE * fpSortCluster;
extern FILE * fpClouds;
//  ..................................................................
