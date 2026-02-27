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
int passA(char*, char**, int*, int*);
int getLine(unsigned char*, unsigned char*, char*, int*);
int processLineForMatch(char*, char**, int*, int, int);
int lineA2B(char*, int, int);
int getKey(char*, char**);
