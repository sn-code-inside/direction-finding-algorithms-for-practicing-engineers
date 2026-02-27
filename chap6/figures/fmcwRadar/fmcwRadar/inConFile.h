#pragma once
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
#include <direct.h> /* for _getcwd() and _chdir() */
#include <sys/types.h>
#include <sys/stat.h>
#include "string.h"
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */

class complex
{ public: double r; 	double i; };
int rdTgtFile(double **, int *, char *);
int rdConfig(double *, char *);
int rdRcon(int *, char *, double *);
char * fileDetails(char *,int *);
int CheckrdRadar(int, char *);
double getRgain(double, double);
int CreatNewDataFile(int , char*, int);
int stripNaddFile(char*, char*, const char*,const char *);
void usage(double*, char*);
char* getDate();
extern FILE* fpLog;
