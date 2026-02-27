#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <errno.h>
#include <direct.h>
int LatexFile(double**, int*,  char*, char*);
void usageLatexFileMatrix(int, int);
double* myAlloc(int);
double** myAlloc2(int , int);
void myFree2(double**, int);
