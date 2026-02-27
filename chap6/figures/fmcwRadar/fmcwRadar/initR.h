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
double* initRdrMatlab(char*, char*, int, char*);
void usage(double*, char*);
int rdRcon(int*, char*, double*);
int rdConfig(double*, char*);
char* getDate();
char* fileDetails(char*, int*);
int stripNaddFile(char*, char*, const char*, const char*);
double* myAlloc(int);
void usageInitR(int,int);

FILE* fpLog;