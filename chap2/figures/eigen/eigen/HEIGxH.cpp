/*
 Program for finding the Eigenvalues and Eigenvectors
 of a given Hermitian matrix using 
 Householder and QR method for Real symmetric matrix

*/
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
#include "stdafx.h"
#include "HEIGxH.h"
//#include "mex.h"   /* This one is required */

void eigenvecH(complex** H, complex** E, double* Lh, double* Jk, int* JkL, int rows)
{
    //	double **Ar, **Ai;
    double big = -1.0;
    double** Ev, * L, ** bi;
    int i = 0, k = 0, n = 0, m = 0, M;
    //	printf("!. void eigenvecH(..)\n");
    //	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
    //	printf("!. B = [ Hr Hi\n");
    //	printf("!.      -Hi Hr ];\n");

    //	Allocate Memory //
    M = 2 * rows;
    bi = myAlloc2(M, M); Ev = myAlloc2(M, M); L = myAlloc(M);
    //	bi = (double **)malloc(M * sizeof(double *));
    //	for (i = 0; i<M; i++) bi[i] = (double *)malloc(M * sizeof(double));

    //	Ev = (double **)malloc(M * sizeof(double *));
    //	for (i = 0; i < M; i++) Ev[i] = (double *)malloc(M * sizeof(double));
    //	L = (double *)malloc(M * sizeof(double));

    /* bi is the 2n*2n real symmetric matrix (equivalent for a n order hermitian matrix)*/

    //	printf("!. create matrix B[%d by %d] real symmetric matrix (equivalent for a %d order hermitian matrix H)\n", M, M, rows);
    //	printf("!. B = [ Br Bi\n");
    //	printf("!.      -Bi Br ];\n");
    for (m = 0; m < rows; m++)
    {
        for (n = 0; n < rows; n++)
        {
            bi[m][n] = H[m][n].r;				// bi[m][n] = Ar[m][n];
            bi[m + rows][n] = -H[m][n].i;		// bi[m + rows][n] = -Ai[m][n];
            bi[m][n + rows] = H[m][n].i;		// bi[m][n + rows] = Ai[m][n];
            bi[m + rows][n + rows] = H[m][n].r;	// bi[m + rows][n + rows] = Ar[m][n];
        }
    }

    // Find the maximum value in matrix bi
    big = -1.0;
    for (m = 0; m < M; m++)
    {
        for (n = 0; n < M; n++)
            if ((double)(fabs(bi[m][n])) > big) big = (double)(fabs(bi[m][n]));
    }
    printf("!. Matrix H is scaled by %f\n", big);
    for (m = 0; m < M; m++)
    {
        for (n = 0; n < M; n++)
            if (fabs(big) != 0) bi[m][n] = bi[m][n] / big;
    }
    JkL[0] = M;
    eigenvecR(bi, M, Ev, L,Jk,JkL);
    //for (i = 0; i < M; i++) printf("%3.4f ", L[i]); printf("\n");

    sortEigOnVal(Ev, L, E, Lh, M);
//  printing for book screen shot
//    printf(" Eigen Values\t");
//    for (i = 0; i < M; i++) printf("%d\t", i); printf("\n\n");
/*    printf("\t"); for (i = 0; i < M; i++) { printf("%3.4f\t", L[i]); if (i == (M / 2) - 1) printf("\t"); }
    printf("\n\n");
    for (i = 0; i < M; i++)
    {
        printf("\t");
        for (k = 0; k < M; k++)
        {
            printf("%3.4f\t", Ev[i][k]);
            if (k == (M / 2) - 1) printf("\t");
        }
        printf("\n");
        if (i == (M / 2)-1) printf("\n");
    }
    printf("\n");*/

    // Free Memory
    myFree2(bi, M);
    //	for (i = 0; i < M; i++) bi[i] = (free(bi[i]), NULL);  // free rows
    //	bi = (free(bi), NULL);
    return;

}

void sortEigOnVal(double** EV, double* L, complex** E, double* Lh, int rows)
{
    int k, m, n, minpos, tpos, * P, M;
    double temp,**EVbuf;
    //P = (int*)malloc(rows * sizeof(int));
    P = myAllocI(rows); EVbuf = myAlloc2(rows, rows);
    M = rows / 2;
    //	printf("!. void sortEigOnVal(double **EV, double *L, complex **E, double *Lh, int rows(%d));\n", rows);
    //	printf("!. Original Hermitian %d\n", M);
    for (m = 0; m < rows; m++)  P[m] = m;

    for (m = 0; m < rows; m++)
    {
        minpos = m;
        for (n = m + 1; n < rows; n++)
        {
            if (L[minpos] > L[n]) minpos = n;
        }

        temp = L[minpos];  L[minpos] = L[m];
        L[m] = temp;  tpos = P[minpos];
        P[minpos] = P[m]; P[m] = tpos;
    }
   
    for (m = 0; m < M; m++)
    {
        Lh[m] = L[2 * m];
        for (n = 0; n < M; n++)
        {
            k = P[2 * n];
            E[m][n].r = EV[m][k]; E[m][n].i = -EV[m + M][k];
        }
    }
    //  ... just for making sure good for the book
    for (m = 0; m < rows; m++)
    {
        for (n = 0; n < rows; n++)  { k = P[n]; EVbuf[m][n] = EV[m][k]; }
    }
    for (m = 0; m < rows; m++)
    { for (n = 0; n < rows; n++) EV[m][n] = EVbuf[m][n]; }

    free(P); myFree2(EVbuf, rows);
    return;
}

void CeqABtrnsp(complex** C, complex** A, int rows, int cols, const char* anot)
{
    int i, m, k;
    complex sum, P; conjmul mulconj; cadd add;
    printf("!. compute %s\n", anot);
    for (i = 0; i < cols; i++)
    {
        for (m = 0; m < cols; m++)
        {
            sum.r = 0.0; sum.i = 0.0;
            for (k = 0; k < rows; k++)
            {
                P = mulconj.mulconj(A[k][m], A[k][i]);
                sum = add.add(P, sum);
            }
            C[i][m] = sum;
        }
    }
    return;
}
