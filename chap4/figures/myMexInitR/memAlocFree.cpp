//#include "stdafx.h"
#include "memAlocFree.h"
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

//	....... memory allocate and free functions ............
complex ** myAlloc2Complex(int r, int c)
{
	complex** A;
	int i;
	A = (complex**)malloc(r * sizeof(complex*));
	for (i = 0; i < r; i++) A[i] = (complex*)malloc(c * sizeof(complex));
	return A;
}

complex* myAllocComplex(int c)
{
    complex* A;
    A = (complex*)malloc(c * sizeof(complex));
    return A;
}


double** myAlloc2(int r, int c)
{
	double** A;
	int i;
	A = (double**)malloc(r * sizeof(double*));
    for (i = 0; i < r; i++)
    {
        A[i] = (double*)malloc(c * sizeof(double));
    }
	return A;
}

double* myAlloc(int c)
{
	double* A;
	A = (double*)malloc(c * sizeof(double));
	return A;
}



int myAlloc3(int M, int N, int O, unsigned char*** A)
{
    int i, j;
    //    printf("image memory matrix allocation %d %d %d\n", M, N, O);
    //    A = (unsigned char***)malloc(M * sizeof(unsigned char**));
    for (i = 0; i < M; i++)
    {
        A[i] = (unsigned char**)malloc(N * sizeof(unsigned char*));
        if (A[i] == NULL) { printf("Out of memory\n");	return -1; }

        for (j = 0; j < N; j++)
        {
            A[i][j] = (unsigned char*)malloc(O * sizeof(unsigned char));

            if (A[i][j] == NULL) { printf("Out of memory\n"); return -1; }
        }
    }
    return 1;
}

void myFree3(int M, int N, int O, unsigned char*** A)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
    return;
}


void ImageMemAlloc(imagex* jpg)
{
    int num_of_coms, ima_ht, ima_wd;
    unsigned char*** components;
    int flag;
    num_of_coms = jpg[0].num_of_comps;
    ima_ht = jpg[0].ima_ht; ima_wd = jpg[0].ima_wd;
    components = jpg[0].data;

    //    flag = myAlloc3(num_of_comps, ima_ht, ima_wd, components);
    flag = myAlloc3(ima_ht, ima_wd, num_of_coms, components);
    if (flag < 0)
    {
        printf("!. IMAGE MEMORY ALLOCATION FAILURE [%d.%d.%d]\n", ima_ht, ima_wd, num_of_coms);
        exit(0);
    }
    else  printf("!. Allocate unsigned char Image Memory[%d.%d.%d]\n", ima_ht, ima_wd, num_of_coms);



    return;
}

void ImageMemFree(imagex* jpg)
{
    int num_of_comps, ima_ht, ima_wd;
    int i, j;
    unsigned char*** components{};
    num_of_comps = jpg[0].num_of_comps;
    ima_ht = jpg[0].ima_ht; ima_wd = jpg[0].ima_wd;
    components = jpg[0].data;
    printf("!.  Free Image Memory[%d.%d.%d]\n", ima_ht, ima_wd, num_of_comps);

    for (i = 0; i < ima_ht; i++)
    {
        for (j = 0; j < ima_wd; j++)
        {
            free(components[i][j]);
            //            printf("free components[%d][%d]\n",i,j);
        }
    } free(components);

    //    myFree3(num_of_comps, ima_ht, ima_wd, components);
    return;
}

void myFree2Complex(complex** A, int r)
{
    int i;
    for (i = 0; i < r; i++)
    {
        free(A[i]); A[i] = NULL;
    }
    free(A);
    A = NULL;
    return;
}

void myFree2(double** A, int r)
{
    int i;
    for (i = 0; i < r; i++)
    {
        free(A[i]); A[i] = NULL;
    }
    free(A);
    A = NULL;
    return;
}

void myFree(double* A)
{
    free(A); A = NULL;
    return;
}



