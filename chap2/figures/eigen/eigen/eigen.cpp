// eigen.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "eigen.h"
/*
 * Author: Kaluri V. Ranga Rao
 * Visiting Scholar, Department of Computer Science,
 * The Ohio State University
 *
 * Copyright (c) 2025 Kaluri V. Ranga Rao
 * All rights reserved.
 *
 * This code is part of the material for the book:
 * "Direction Finding Algorithms for Practicing Engineers,"
 * published by Springer Nature.
 *
 * This material is intended for academic and research purposes only.
 */
int main(int argc, char** argv)
{
    complex** A,**E;
    double* L,config[30],*Jk;
    int rcA[2],k,kt,er;
    rcA[0] = 512; rcA[1] = 4;
    char *datafile;
    int Len = 100,JkL = 5000;
    int JkLen = JkL;

    A = myAlloc2Complex(rcA[0], rcA[1]);
    E = myAlloc2Complex(rcA[1], rcA[1]);
    Jk = myAlloc(JkL);
    
    //Len = (int)(strnlen_s(datafile, 100)) + 10;
    datafile = (char*)malloc(Len * sizeof(char));
    strcpy_s(datafile, 20, "closeDoa.txt");
    er = rdConfig(config, datafile); config[7] = rcA[0];
    for (kt = 0; kt < 8; kt++)
    {
//        fillA(A, rcA);
        JkLen = JkL;
        er = createA(A, datafile, config, kt);
        L = eigHermitian(A, rcA, E,Jk,&JkLen);
        printComplxMatrix(E, rcA[1], rcA[1]);
        printf("\n Eigen Values "); for (k = 0; k < rcA[1]; k++) printf("%3.4f ", L[k]); printf("\n");
        getchar();
    }
    myFree2Complex(A, rcA[0]); myFree2Complex(E, rcA[1]);
    free(Jk);
    return 1;
}

void fillA(complex** A, int* rcA)
{
    int i, k;
    for (i = 0; i < rcA[1]; i++)
    {
        for (k = 0; k < rcA[0]; k++)
        {
            A[k][i].r = ((rand() / 32767.0) - 0.5); A[k][i].i = ((rand() / 32767.0) - 0.5);
        }
    }
    return;
}








