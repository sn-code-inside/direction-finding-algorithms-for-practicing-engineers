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
extern int PRINT_FLAG;
int MATLAB = 1;
class complex
{ public: double r; double i; };
//int mainLocal(int, char **);
//void usage(double *, char *);
//void outonfiles(double *, complex **, double **, double *, double *, int *,double**,double *,double **,complex **);
void myAngleDeg(double *, double *,complex *, int);
//double easyMusic(complex **, int *, double *, double *,double **); 
double kMusic(complex **, complex **, double *, double *,double **);
//void rgSteering(complex **, double *, int *, double **, double *, complex **);
double * rgSteering(complex **, double *, int *, double **, double *, complex **);
double detectBins(double *, double *, int *);
void preProc(complex **, complex **, double *, double *, int);
//int OpenCloseFiles(int,char *);
//int createA(complex **, char *, double *, int, double **, int *);
//int rdRcon(int, char *[], int *, char *, double *, double **, int *);
double ** sortCluster(double**, int, int, int,int *,double *);
double distMeasure(double, double);
//int stripNaddFile(char*, char*, char*, char*);
//char * getDate();
//char* fileDetails(char*, int*);
void pause(int dur);
double ** formClouds(double **, int *, int *, double);
double** pointers2clouds(int**, int*, double**, int*);
int** CompactClouds(double**, int*,int*,double);
int** getCloudPointers(double**, int*, int*);
void writeFileNconsole(int*, double**);
void writeFile(int*, double**);
//int** CloseClouds(double**, int*, int*);
void merge(int**, int, int);
//int split(double*, int*, double*, double*, int*, double*, int, int*, int*);
int stdMuLin(double*, double*, double*, int);
int** getCloudLinPt(double* , int, int, int*);
double* myAlloc(int);
double** myAlloc2(int, int);
complex** myAlloc2Complex(int, int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
extern FILE* fp, * fpSyn;
//extern FILE* fp, * fpSyn, * fpRg, * fpData;
//FILE *fpPhi, *fpAmp, *fpPhSpk,*fpMuSpk,* fpAllChnl, * fpRg, * fpData;
extern FILE* fpSortCluster;
extern FILE* fpLog;
extern FILE* fpClouds;
class Cabs :public complex
{
public:
	complex a;
	double cabs(complex a);
};
class sort
{
public:
	double *x;
	int *xI, M;
	void High2Low();
	void Low2High();
	void showx();
};
