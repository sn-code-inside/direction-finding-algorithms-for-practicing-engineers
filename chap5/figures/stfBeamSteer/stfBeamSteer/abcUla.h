#pragma once
#include "math.h"
//#include "mex.h"   /* This one is required */
#include "memAlocFree.h"
double* abcUlaArray(
    int,
    double*,
    double*,
    double*,
    int,
    int,
    double,
    double,
    double,
    double,
    double**,
    double**,
    double**,
    double**,
    double**,
    double**);
double** CeqABtrnsp(double**, int*, const char*);
double ula(double*, double*, double*, double, double, double, int, int, int, double*, double**, double);
double* GenerateSignals(int, int, int, double*, double*, double*, double, double, double, double**, double**, double**, double);
void Usage();
double* myNoise(int, double);
void matAeqB(double**, double**, int);
double obj(double**, double, double, double, int);
