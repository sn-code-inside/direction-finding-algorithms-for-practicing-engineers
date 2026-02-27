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
const int PRINT_FLAG = 0;
const int MATLAB = 0;
class complex
{ public: double r; double i; };
int mainLocal(int, char **);
//double* initRdr(char*, char*, char*, char*, char*, int, char**);
double* initRdr(char*, char*, int, char**);
void usage(double *, char *);
//void outonfiles(double *, complex **, double **, double *, double *, int *,double**,double *,double **,complex **);
//void myAngleDeg(double *, double *,complex *, int);
complex** myAlloc2Complex(int, int);
double* myAlloc(int);
void myFree2Complex(complex**, int);
double** myAlloc2(int, int);
void myFree2(double**, int);
void myFree(double*);
int* Low2High(int, double*);
double** processRdr(int, char*, double*, double**, int*,int*);
double** getLooksData(double*, char*, int,int *);
int openCSVfiles();
//double easyMusic(complex **, int *, double *, double *,double **);
//double kMusic(complex **, complex **, double *, double *,double **);
//double * rgSteering(complex **, double *, int *, double **, double *, complex **);
//double* rgAvg(double**, double*);
//int detectBins(double *, double *, int *);
//void preProc(complex **, complex **, double *, double *, int);
//int OpenCloseFiles(int,char *);
int closeAllFile();
int createA(complex **, char *, double *, int);
int rdRcon(int *, char *, double *);
//double ** sortCluster(double**, int, int, int,int *,double *);
//double** formClouds(double**, int*, int*,double);
//int** CompactClouds(double**, int*,double);
//int** getCloudPointers(double**, int*, int*);
//double** clouds2cluster(int*, double**, int, int*);
//double** createSceneMatrix(int, double**, FILE*);
//void pause(int dur);
//void writeFileNconsole(int*, double**);
//int capture(int, int, int);
//void writeFile(int*, double**);
//void writeFileUnsort(int*, double**,double *); // updated on 28th Jun 2023 for paper
//void TransferData(int, int*, double*,double*, double*, double*, double**, int,int);
//void createRdrImg(int*, double**, int, char *);
//int stripNaddFile(char*, char*, char*, char*);
//int stripNaddFile(char*, char*, const char*, const char*);
//int rdConfig(double*, char*);
//char* getDate();
//char * fileDetails(char*, int *);
extern FILE* fpLog;
class Cabs :public complex
{
public:
	complex a;
	double cabs(complex a);
};