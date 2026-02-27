/*
 Program for finding the Eigenvalues and Eigenvectors
 of a given Hermitian matrix using 
 an extension of the Jacobi method for Real-Symmetric matrices 
 
 Method for Hermitian matrix Date21.05.2012
 optimised code written by Prof K V Rangarao
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
#include "math.h"
#include "eigR.h"
int rotate(double**, double**, int, double**, double**, double*, double*, int*);
//int eigenvecJ(complex **, int, double**, double**, double*, double*);


/*
 eigenvec is a function of type void which checks if the matrix after 
   rotation is diagonalised and if not performs rotations till required.
 
 It contains five parameters
 aR: [IN] It is a double pointer (M*M) to type double containing the real part of input matrix whose
   eigen values and eigen vectors are to be evaluated
 aI: [IN] It is a double pointer (M*M) to type double containing the imag part of input matrix whose
   eigen values and eigen vectors are to be evaluated
 M: [IN] It is of integer type which gives size of input matrix
 ER: [OUT] It is a double pointer (M*M) to type double containing the eigen vectors real part 
 EI: [OUT] It is a double pointer (M*M) to type double containing the eigen vectors imag part 
 L: [OUT]It is a pointer to (M*1) type double containing the eigen values*/
 

int eigenvecJ(complex **a, int M, complex **E, double *L, double *Jk, int *JkL)
{
	int k=0,kmax = 3000;
    int m,n,twoM;
	double v=1,**bo, **ro;
    double **bi, **ri;
    double theta;
    double TOLERANCE = 1E-3;
    double big = 0;
    double PI;
    
    int minpos;
    double temp;
    int tpos,flag = 1;
    int *P;
    PI = 4.0 * atan(1.0);
    twoM = 2 * M;
    printf(" Compute Eigen Values and Eigen Vectors by Jacobi Method");
    printf(" Updated on 8th Jul 2024 23:00 by Prof KVR\n");
    if ( M > 35 ) { printf(" It is difficult to handle contact kaluri@ieee.org\n"); return -1; }

    
    bi = myAlloc2(twoM, twoM); ri = myAlloc2(twoM, twoM);

    for (m = 0; m < M; m++)
    {
        for (n = 0; n < M; n++)
        {
            bi[m][n] = a[m][n].r;			// bi[m][n] = Ar[m][n];
            bi[m + M][n] = -a[m][n].i;		// bi[m + rows][n] = -Ai[m][n];
            bi[m][n + M] = a[m][n].i;		// bi[m][n + rows] = Ai[m][n];
            bi[m + M][n + M] = a[m][n].r;	// bi[m + rows][n + rows] = Ar[m][n];
        }
    }
    printf(" Normalised %d by %d matrix by %f\n", twoM, twoM, big);

    big = -1.0;
    for (m = 0; m < twoM; m++)
    {
        for (n = 0; n < twoM; n++)
            if ((double)(fabs(bi[m][n])) > big) big = (double)(fabs(bi[m][n]));
    }
    for (m = 0; m < twoM; m++)
    {
        for (n = 0; n < twoM; n++)
            if (fabs(big) != 0) bi[m][n] = bi[m][n] / big;
    }

    printf(" start ri with identy matrix\n");
    for (m = 0; m < twoM; m++) { for (n = 0; n < twoM; n++) ri[m][n] = (m == n) ? 1.0 : 0.0; }


    bo = myAlloc2(twoM, twoM); ro = myAlloc2(twoM, twoM);
    k = 0;
	while(v > TOLERANCE)  // verifying if bo is diagonalised 
	{
		flag = rotate(bi, ri, twoM, bo, ro, Jk,&theta,&k);
/*		v = fabs(theta); */
        if (k < JkL[0]) v = Jk[k];
        k = k + 1;
        if ( k > kmax ) break;
 	}
    
    /* selection sort bo[i][i] */
    P = myAllocI(twoM);
    //P = (int *)mxCalloc(2*M, sizeof(int)); /* remember the position */
    for (m = 0; m < twoM; m++)
    {
        P[m] = m;
    }    
    printf(" Sorting Eigen Values and Corresponding Eigen Vectors after %d iterations\n",k); 

    for (m = 0; m < twoM; m++)
    {
        minpos = m;
        for (n = m+1; n < twoM; n++)
        {
            if (bo[minpos][minpos] > bo[n][n]) minpos = n;
        }
        temp = bo[minpos][minpos];
        bo[minpos][minpos] = bo[m][m];
        bo[m][m] = temp;
        tpos = P[minpos];
        P[minpos] = P[m]; 
        P[m] = tpos;
    }
    
    /* set the outputs */
    for (m = 0; m < M; m++)
    {
        L[m] = bo[2*m][2*m];
        
        for (n = 0; n < M; n++)
        {
            E[m][n].r = ro[m][P[2 * n]];
            E[m][n].i = -ro[m + M][P[2 * n]];
 /*           temp = atan(EI[m][n]/ER[m][n])*180/PI;
              if ( fabs(temp) < 1  ) { EI[m][n] = 0; printf("%f %f %f\n",temp,ER[m][n],EI[m][n]);}
              if ( fabs(temp) > 89 ) { ER[m][n] = 0; printf("%f %f %f\n",temp,ER[m][n],EI[m][n]);  } */
        }
    }
    
    printf(" Objective Function[%d]  %f\n",k,v);
    myFree2(bi, twoM); myFree2(ri, twoM);
    myFree2(bo, twoM); myFree2(ro, twoM);
    free(P);
    JkL[0] = k;
    return k;
}

/*rotate is a function of type void which performs rotation (transformation)
  It contains six parameters
 It calls three functions abso,inv,my_multiply
 bi:It is a double pointer to type double containing the real symmetric
    input matrix to be diagonalised
 ri:It is a double pointer to type double containing the product of
    tranformation matrices till previous rotations and initially identity matrix
 n:It is an integer type parameter which gives size of the matrices
 bo:It is a double pointer to type double which contains the result of rotation
 ro:It is a double pointer to type double which contains the product
    of transformation matrices after each rotation.
 theta:It is an output parameter of type double which gives the rotation angle*/
int rotate(double** bi, double** ri, int n, double** bo, double** ro, double* Jk, double* theta, int* indx)
/*	rotate(bi,ri,n,bo,ro);*/
{
    int i, j, l = 0, k = 1, flag = 0, pt;
    double local_theta, Cth, Sth, minL;
    double t, tau;
    double** prodT;
    double PIby4;
    double p1, p2, p3, maxA;
    double aT[4];
    PIby4 = atan(1.0);
    pt = indx[0];

    prodT = myAlloc2(n, n);
    //prodT=(double **)mxCalloc(n,sizeof(double *));
    //for(i=0;i<n;i++) prodT[i]=(double *)mxCalloc(n,sizeof(double));


/*Finding the maximum off diagonal element location */
    maxA = -9876543210.0;
    minL = 9876543210;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (fabs(bi[i][j]) > maxA)
            {
                maxA = fabs(bi[i][j]); 	l = i;  k = j;
            }
        }
        /*        printf(" minL %d .. %f .. %f\n",i,minL,bi[i][i]);*/
        if (fabs(bi[i][i]) < minL) minL = fabs(bi[i][i]);
    }

    /*Evaluating rotation angle(theta) at maximum value */
    p2 = (bi[k][k] - bi[l][l]);
    p1 = fabs(p2);
    p3 = 2.0 * bi[l][k];
    if (p2 == 0) { if (p3 < 0) *theta = -PIby4; else *theta = PIby4; }
    else *theta = 0.5 * atan(p3 / p1);
    Cth = cos(*theta); Sth = sin(*theta);
    tau = Sth / (1 + Cth); t = Sth / Cth;
    local_theta = *theta;


    /*Obtaining bo by rotation*/
/*      cK(k,:) = bi(m,:)*sInv(k,m) + bi(k,:)*(sInv(k,k)-1); matlab prototype (pre-multply type ) */

/*    printf("bi-Matrix (%d,%d) %f\n",l+1,k+1,*maxA); */
/*    for (i=0; i<n; i++) {for (j=0; j<n; j++) printf("%f ", bi[i][j]); printf("\n");} */

    for (i = 0; i < n; i++) for (j = 0; j < n; j++) prodT[i][j] = bi[i][j];

    for (i = 0; i < n; i++)
    {
        if (fabs(bi[l][i]) < 1.0E-6) { aT[0] = 0; aT[3] = 0; }
        else
        {
            aT[0] = -bi[l][i] * Sth; aT[3] = bi[l][i] * Cth;
        }


        if (fabs(bi[k][i]) < 1.0E-6) { aT[1] = 0; aT[2] = 0; }
        else
        {
            aT[1] = bi[k][i] * Cth; aT[2] = bi[k][i] * Sth;
        }

        prodT[k][i] = aT[0] + aT[1];
        prodT[l][i] = aT[2] + aT[3];
    }

    /*    bK(:,m) = Ct(:,k)*s(k,m) +  Ct(:,m)*(s(m,m)-1); matlab prototype (post-multply type )
          my_multiply(prodT, s, n, bo); */

    for (i = 0; i < n; i++) for (j = 0; j < n; j++) bo[i][j] = prodT[i][j];

    for (i = 0; i < n; i++)
    {
        if (fabs(prodT[i][l]) < 1.0E-6) { aT[0] = 0; aT[3] = 0; }
        else
        {
            aT[0] = -prodT[i][l] * Sth; aT[3] = prodT[i][l] * Cth;
        }

        if (fabs(prodT[i][k]) < 1.0E-6) { aT[1] = 0; aT[2] = 0; }
        else
        {
            aT[1] = prodT[i][k] * Cth;  aT[2] = prodT[i][k] * Sth;
        }

        bo[i][k] = aT[0] + aT[1];    if (fabs(bo[i][k] / minL) < 0.00001) { bo[i][k] = 0.0; }
        bo[i][l] = aT[2] + aT[3];    if (fabs(bo[i][l] / minL) < 0.00001) { bo[i][l] = 0.0; }
    }

    for (i = 0; i < n; i++) for (j = 0; j < n; j++) bi[i][j] = bo[i][j];

    /*    printf("bo-Matrix (%d,%d) %f\n",l+1,k+1,*maxA);
        for (i=0; i<n; i++) {for (j=0; j<n; j++) printf("%f ", bo[i][j]); printf("\n");} */



        /*    Generate the Objective function for performance Check .. can be removed.  */
    pt = indx[0];
    Jk[pt] = 0.0;
    for (i = 0; i < n; i++) for (j = i + 1; j < n; j++) Jk[pt] = Jk[pt] + fabs(bi[i][j]); /*Jk[pt] = Jk[pt]/minL;*/



    /*	bo = sInv*bi*s
        my_multiply(ri,s,n, ro); */

    for (i = 0; i < n; i++) for (j = 0; j < n; j++) ro[i][j] = ri[i][j];
    for (i = 0; i < n; i++)
    {
        /*                ro[i][k] = -ri[i][l]*Sth + ri[i][k]*Cth;
                        ro[i][l] =  ri[i][k]*Sth + ri[i][l]*Cth;
                            aT[0] = -ri[i][l]*Sth; aT[1] = ri[i][k]*Cth;
                            aT[2] =  ri[i][k]*Sth; aT[3] = ri[i][l]*Cth;*/
        if (fabs(ri[i][l]) < 1.0E-6) { aT[0] = 0; aT[3] = 0; }
        else
        {
            aT[0] = -ri[i][l] * Sth; aT[3] = ri[i][l] * Cth;
        }

        if (fabs(ri[i][k]) < 1.0E-6) { aT[1] = 0; aT[2] = 0; }
        else
        {
            aT[1] = ri[i][k] * Cth; aT[2] = ri[i][k] * Sth;
        }

        ro[i][k] = aT[0] + aT[1];
        ro[i][l] = aT[2] + aT[3];

    }
    for (i = 0; i < n; i++) for (j = 0; j < n; j++) ri[i][j] = ro[i][j];

    /*        for (i=0; i<n; i++) ro[i][l] = ri[i][k]*s[k][l] + ri[i][l]*s[l][l]; */


        /*Obtaining ro by multiplying the transformation matrix*/

    //	for (i=0;i<n;i++) mxFree(prodT[i]);
    //	mxFree(prodT);
    myFree2(prodT, n);

    flag = *indx;
    return flag;
}
