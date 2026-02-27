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
FILE* fpRgDoa, * fpMusic, * fpW, * fpCy;
FILE* fpSortCluster, * fpClouds, * fpUnSortCluster; // updated on 22nd Aug 2023 for paper
extern FILE* fpLog, *fp, *fpKMUandGmu;
const int PRINT_FLAG = 0;
const int MATLAB = 0;
int capture(int , int , int);
void writeFileUnsort(int*, double**, double*);
void writeFile(int* , double**);
void writeFileNconsole(int*, double**);
