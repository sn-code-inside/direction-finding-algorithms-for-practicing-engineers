#pragma once
#include "math.h"
//#include "mex.h"   /* This one is required */
#include "memAlocFree.h"
//void Usage();
double* coefficient(double, double, double, int);
double* linspace(double, double, int);
double wTranposeHmulW(double**, double*, int);
double obj(double** , double , double , double, int);
