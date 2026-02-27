//#include "mex.h"   /* This one is required */
#include "stdafx.h"
#include "phi2doa.h"
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

complex* eigPhi(complex** H, complex** E,int rows)
{
	double big = -1.0;
	double** Ev, * L, ** bi;
	double* Jk;
	int i = 0, k = 0, n = 0, m = 0, M = 2 * rows;
	int JkL = 5000,pt,*indx;
	complex** He, ** Ho,temp;
	complex* eigVofH;
	He = myAlloc2Complex(rows, rows);
	Ho = myAlloc2Complex(rows, rows);
	Jk = myAlloc(JkL); M = 2 * rows;
	Ev = myAlloc2(M, M); L = myAlloc(M);
	indx = myAllocI(M);

//	even matrix
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rows; k++)
		{
			He[i][k].r =  (H[k][i].r + H[i][k].r)*0.5; // (phi' + phi)/2;
			He[i][k].i = (-H[k][i].i + H[i][k].i)*0.5;
		}
	}
	bi = complex2real(He, rows, &big);
	eigenvecR(bi, M, Ev, L, Jk, &JkL);
	//indx = High2Low(M, L);
	printf("!. EVEN ROOTS\n");
	for (i = 0; i < M; i++) printf("%3.4f ", L[i] * big);
	printf("\n");
//	..........................
//	odd matrix
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rows; k++)
		{
			Ho[i][k].i = (H[k][i].r   - H[i][k].r)*0.5; //(phi' - phi)/2;
			Ho[i][k].r = (-H[k][i].i  - H[i][k].i)*0.5;
		}
	}
	/*for (i = 0; i < rows; i++)
	{
		for (k = 0; k < rows; k++)
		{
			temp = Ho[i][k];
			Ho[i][k].r = temp.i;
			Ho[i][k].i = temp.r;
		}
	}*/

	bi = complex2real(Ho, rows, &big);
	eigenvecR(bi, M, Ev, L, Jk, &JkL);
	//for (i = 0; i < M; i++) L[i] = -L[i];
	//indx = High2Low(M, L);
	printf("!. ODD ROOTS\n");
	for (i = 0; i < M; i++) printf("%3.4f ", L[i] * big);
	printf("\n");

//	.......................................................

	eigVofH = myAllocComplex(rows);
	printf("!. Eig Values \n");
	for (i = 0; i < rows; i++)
	{
		pt = 2*i;      eigVofH[i].r = L[pt]*big;
		pt = 2*i+1;    eigVofH[i].i = L[pt]*big;
		//printf("  [%d](%3.4f %3.4fi) ",i, eigVofH[i].r, eigVofH[i].i); printf("\n");
	}

	// Free Memory
	myFree2(bi, M);
	free(Jk);
	return eigVofH;

}
