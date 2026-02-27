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
double* myAlloc(int);
double** myAlloc2(int , int);
complex** myAlloc2Complex(int, int);
void myFree2Complex(complex**, int);
void myFree2(double**, int);
