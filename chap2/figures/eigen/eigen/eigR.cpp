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
#include "eigR.h"
/*Ar, M , ER, L */

double* eigHermitian(complex** A, int* rcA, complex** E, double *Jk, int *JkL)
{
	complex** H;
	double* Lh;
	int r, c;

	r = rcA[0]; c = rcA[1];
	H = myAlloc2Complex(c, c);
	Lh = myAlloc(c); 
	CeqABtrnsp(H, A, r, c, " H = (A Conj Transpose) * A ");
	eigenvecH(H, E, Lh, Jk, JkL, c);
//	eigenvecJ(H, c, E, Lh, Jk,JkL);
	return Lh;
}


void eigenvecR
(
	double **Ar, /* input */
	int M,       /* Size of the input matrix  */
	double **ER, /* output1 :Eigen vectors of input matrix */
	double *L,   /* output2: Eigen values of input matrix */
	double *Jk,  /* output3: Convergence Function */
	int *JkL     /* output4: length Jk */
)

{
//	printf("void eigenvecR()\n");
//	int i, k, m;
	int i=0,m=0;
	double **a, **P;

	int flag = 1;
//	printf("2. void eigenvecR(double **Ar,int M,double **ER,double *L,double *Jk,double *JkL);\n");
//	printf("!. Ar input Matrix of size M(%d) .. ER Eigen Vectors L Eigen Values Jk convergence Function of length JkL\n", M);

	/*input matrix*/
	a = myAlloc2(M, M);
//	a = (double **)malloc(M * sizeof(double *));
//	for (m = 0; m < M; m++) a[m] = (double *)malloc(M * sizeof(double));

	/* P - Transformation matrix  */
	P = myAlloc2(M, M);
//	P = (double **)malloc(M * sizeof(double *));
//	for (m = 0; m < M; m++) P[m] = (double *)malloc(M * sizeof(double));
	/* (Ar, M , Jk ,ER, L); */
	flag = hholdc(Ar, P, a, M);
	qrstc(a, M, P, ER, L, Jk, JkL); /* a = tridiagonal , M - order , P - transformation matrix , ER : eig vector , L = eig value */
									/* Jk is the convergence function and JkL is the length of Jk */

//	for (i = 0; i<M; i++)
//	{ free(a[i]); free(P[i]); }
//	free(a); free(P);
	myFree2(a, M);
//	for (i = 0; i < M; i++) a[i] = (free(a[i]), NULL);  // free rows
//	a = (free(a), NULL);
	myFree2(P, M);
//	for (i = 0; i < M; i++) P[i] = (free(P[i]), NULL);  // free rows
//	P = (free(P), NULL);

	return;

}

/*Householder function : To reduce original matrix to tridiagonal form...*/

int hholdc
(
	double  **A, /* input real symmetric Matrix  */
	double  **P, /* Output Transformation Matrix */
	double  **a,  /* Output Tridiagonal  Matrix */
	int nA       /* Input size of A Matrix */
)

{
	int i=0, j=0, m=0, k=0;
	double *c, *b, *u, *w;
	double **Q, **mul, **res, **res1;
	int eFlag = 1;
	double sum = 0, q, v;
	int ir=0, jc=0, kr=0;
//	printf("3. int hholdc(double  **Ar,double  **P,double  **a,int nA\n");
//	printf("!. Ar input real symmetric Matrix, **P Output Transformation Matrix, **a Output Tridiagonal  Matrix, nA size(A)\n");
	c = myAlloc(nA); b = myAlloc(nA); u = myAlloc(nA); w = myAlloc(nA);
	Q = myAlloc2(nA, nA); mul = myAlloc2(nA, nA);
	res = myAlloc2(nA, nA); res1 = myAlloc2(nA, nA);
	eFlag = 1;
	if (nA <= 2) { eFlag = -1; return eFlag; }
//	printf("!. Converting into tri-diagonal form\n");
	/* P = diag(diag(ones(n))); */
	/* making identity matrix  */
	for (i = 0; i < nA; i++)                
	{
		for (j = 0; j < nA; j++) 
		{ a[i][j] = A[i][j]; P[i][j] = 0.0; if (i == j)  P[i][j] = 1; }
	}

	for (m = 0; m<nA - 2; m++)
	{

		/* c =zeros(nA,1);  %% column-vector of zeros  */

		for (i = 0; i<nA; i++) { c[i] = 0; }

		/* set up c
		/ c(i+1:n)=a(i+1:n,i); %removing first element of first row and first column */
		i = m;  for (j = i + 1; j<nA; j++) { c[j] = a[j][m]; }
		/* %q=norm(c); */
		sum = 0.0;  for (j = i + 1; j< nA; j++) sum = sum + (c[j] * c[j]);

		q = sqrt(fabs(sum));

		/* %b=zeros(n,1); */
		for (i = 0; i<nA; i++)  b[i] = 0;

		i = m;  if (a[i + 1][i] >= 0)  b[i + 1] = -q; else b[i + 1] = q;

		/* %w=(c-b)/norm(c-b);
		// u = c-b ; norm(c-b) = v So, w = u/v */
		/* updated after sending to prof */

		for (i = 0; i<nA; i++) u[i] = c[i] - b[i];

		sum = 0.0;  for (i = 0; i<nA; i++) sum = sum + (u[i] * u[i]);

		v = sqrt(fabs(sum));
		/* printf("v = %f sum = %f\n",v,sum);  */

		/* w = u/v ; changed after sending to prof... */

		for (i = 0; i <nA; i++) w[i] = u[i] / v;
		/* Q=eye(n)-2*w*w'; */
		for (k = 0; k<nA; k++)
		{
			for (j = 0; j<nA; j++)
			{
				if (k == j) Q[k][j] = 1 - 2 * w[j] * w[k]; else Q[k][j] = -2 * w[j] * w[k];
			}
		}

		/* mul = P*Q */
		for (ir = 0; ir < nA; ir++)
		{
			for (jc = 0; jc < nA; jc++)
			{
				mul[ir][jc] = 0.0;
				for (kr = 0; kr<nA; kr++) { mul[ir][jc] = mul[ir][jc] + P[ir][kr] * Q[kr][jc]; }
			}
		}

		/* P = mul */
		for (ir = 0; ir <nA; ir++)
		{
			for (jc = 0; jc < nA; jc++) P[ir][jc] = mul[ir][jc];
		}



		/*   %a=Q*a*Q;  */

		/* res = Q*a */
		for (ir = 0; ir < nA; ir++)
		{
			for (jc = 0; jc < nA; jc++)
			{
				res[ir][jc] = 0.0;
				for (kr = 0; kr < nA; kr++) { res[ir][jc] = res[ir][jc] + Q[ir][kr] * a[kr][jc]; }
			}

		}
		/* res1 = res*Q */
		for (ir = 0; ir< nA; ir++)
		{
			for (jc = 0; jc< nA; jc++)
			{
				res1[ir][jc] = 0.0;   /*changed third time final change */
				for (kr = 0; kr < nA; kr++) { res1[ir][jc] = res1[ir][jc] + res[ir][kr] * Q[kr][jc]; }
			}
		}

		/*a = res1 */

		for (ir = 0; ir <nA; ir++)
		{
			for (jc = 0; jc < nA; jc++)  a[ir][jc] = res1[ir][jc];
		}

		/* changed second time after sending to prof */


		for (k = m + 2; k < nA; k++) { a[k][m] = 0.0; }

		/*** resulting a is the tridiagonal matrix and P is the householder transformation matrix ****/
		
	}

	return eFlag;
//	Free memory
	myFree2(Q, nA); myFree2(mul, nA);
	myFree2(res, nA); myFree2(res1, nA);
/*	for (i = 0; i<nA; i++)
	{
		free(Q[i]);	// free rows
		free(mul[i]); 
		free(res[i]);
		free(res1[i]);
	}
	free(Q);
	free(mul);
	free(res);
	free(res1);*/

	free(c); free(b); free(u);  free(w);
	return eFlag;
}


void qrstc
(
	double **a, /* Tridiagonal matrix (output of hholdc function */
	int nA,    /* order of input matrix */
	double **P, /* Transformation matrix */
	double **v, /* Eigenvector */
	double *lambda, /* Eigenvalue */
	double *Jk, /* Convergence Function */
	int *JkL /* Length of Jk */
)

{

	/*
	*
	* Input  :
	* a = Tridiagonal matrix (result of hholdc function ) from which d and Of are extracted
	*
	* d =  vector containing elements along the main diagonal
	of the symmetric tridiagonal matrix;

	Of =  vector containing elements along the off diagonal of the symmetric
	tridiagonal matrix

	*nA = size of input matrix
	TOL = convergence tolerance
	Nmax =   maximum number of iterations
	P  = householder transformation
	matrix for the original real symmetric

	output:
	lambda = vector containing the eigenvalues of the symmetric
	tridiagonal matrix
	v      = matrix containing the eigenvectors of the symmetric
	tridiagonal matrix determined
	*
	*
	*
	*/

//	int i, j, ir, jc, kr, irv, irn, togo, its, m, k;
	int i, j, ir, jc, kr, irv, irn, togo, its;

	double *d, *Of, *vnew, *result1, *result2, *col1, *result3, *result4, *addres, *c, *s, *Oftemp;

	double TOL = 1.0E-20, shift, trace, det, oldb, disc, r, temp1, temp2, mu1, mu2, sadd;
	double sc, ss, ss1, sc1;
	int Nmax = 10000;

//	printf("4. void qrstc(double **a,int nA,double **P,double **v,double *lambda,double *Jk,int *JkL)\n");
//	printf("!. Output [a] Tridiagonal matrix of size nA(%d),P Transformation matrix\n",nA);
//	printf("!. v Eigenvector, lambda Eigenvalues, Jk Convergence Function of Length JkL\n");

	d = (double *)malloc(nA * sizeof(double));
	Of = (double *)malloc(nA * sizeof(double));
	vnew = (double *)malloc(nA * sizeof(double));
	result1 = (double *)malloc(nA * sizeof(double));
	result2 = (double *)malloc(nA * sizeof(double));
	col1 = (double *)malloc(nA * sizeof(double));
	result3 = (double *)malloc(nA * sizeof(double));
	result4 = (double *)malloc(nA * sizeof(double));
	addres = (double *)malloc(nA * sizeof(double));
	c = (double *)malloc(nA * sizeof(double));
	s = (double *)malloc(nA * sizeof(double));
	Oftemp = (double *)malloc(nA * sizeof(double));

//	printf("!. Eigen Values and Vectors of Tridiagonal real %d by %d matrix\n", nA, nA);

	/*  d = diag(T)   %% diagonal elements of tridiagonal matrix   a */
		for (ir = 0; ir <nA; ir++)
		{
			for (jc = 0; jc < nA; jc++) { if (ir == jc) { d[ir] = a[ir][jc]; } }
		}

	/**** disp('off diagnol elements of tridiagnol form')  Of = diag(T,1); */

		for (ir = 0; ir < nA - 1; ir++)
		{
			for (jc = 0; jc < nA - 1; jc++) { if (ir == jc) { Of[ir] = a[ir + 1][jc]; } }
		}


	/* number of diagonal elements is nA   // to repeat the first element twice //  */

	/*Oftemp = Of;  Of(2:nA) = Of(1:nA-1) */

		for (i = 0; i<nA; i++) { Oftemp[i] = Of[i]; }

	/*      // to repeat the first element twice //   */
		for (i = 1; i <nA; i++) { Of[i] = Oftemp[i - 1]; }
	/*  v = P; */

		for (ir = 0; ir <nA; ir++)
		{
			for (jc = 0; jc < nA; jc++)
			{
				v[ir][jc] = P[ir][jc];
			}
		}

	/*  %c = zeros ( 1, n )  % Row of zeros  */
		for (jc = 0; jc<nA; jc++) { c[jc] = 0; }

	/*    % s = zeros ( 1, n ) */

		for (jc = 0; jc<nA; jc++) { s[jc] = 0; }

	/* printf("s =");
	for (i = 0; i <nA ; i++)  printf("%f ",s[i]); printf("\n"); */

		shift = 0.0;
		togo = nA - 1;


	/* for (its = 0 ; its <  Nmax ; its++) */
	for (its = 0; its < Nmax; its++)
	{

//		        for (k=0; k<nA; k++) printf("%d %d %f \n",its,k,lambda[k]); 
				Jk[its] = lambda[nA-1];

		if (togo == 0)
		{
			/* printf("here togo is 0, to find first eigvalue ");*/

			lambda[0] = d[0] + shift;

			/* this is the final eigen values (lambda) and vectors (v) that is to be returned //
			printf("The final eigen values are ");*/
//			printf("!. Exit from finding Eig Val and Vec function at JkL(%d)\n", its);
			JkL[0] = its;
			return;
		}
		trace = d[togo - 1] + d[togo];


		det = d[togo - 1] * d[togo] - Of[togo] * Of[togo];

		disc = sqrt(fabs(trace*trace - 4 * det));

		mu1 = (trace + disc) / 2;

		mu2 = (trace - disc) / 2;


		/* if (fabs(mu1 - d[togo-1]) < fabs(mu2 - d[togo-1]) ) */
		if (fabs(mu1 - d[togo]) < fabs(mu2 - d[togo])) sadd = mu1; else sadd = mu2;
		shift = shift + sadd;
		for (i = 0; i<togo + 1; i++) { d[i] = d[i] - sadd; }
		oldb = Of[1];
		for (i = 1; i< togo + 1; i++)
		{

			j = i - 1;  r = sqrt(d[j] * d[j] + oldb*oldb);
//			Jk[its] = r;
			c[i] = d[j] / (r + TOL);  s[i] = oldb / (r + TOL);

			d[j] = r;  temp1 = c[i] * Of[i] + s[i] * d[i];
			temp2 = -s[i] * Of[i] + c[i] * d[i];
			Of[i] = temp1;  d[i] = temp2;

			if (i != togo) { oldb = Of[i + 1]; Of[i + 1] = c[i] * Of[i + 1]; }

		}  /* i = 1 to togo ending */

		   /*d[1] = c[2]*d[1] + s[2]*Of[2]; */
		d[0] = c[1] * d[0] + s[1] * Of[1];


		/* Of[2] = s[2]*d[2];*/

		Of[1] = s[1] * d[1];

		/*  1 to 3  togo = 4*/
		for (i = 1; i< togo; i++) { d[i] = s[i + 1] * Of[i + 1] + c[i] * c[i + 1] * d[i]; Of[i + 1] = s[i + 1] * d[i + 1]; }
		d[togo] = c[togo] * d[togo];


		for (i = 1; i< togo + 1; i++)
		{
			/* %col1 = v(:,i-1) * c(i) + v(:,i) * s(i) */

			for (irv = 0; irv< nA; irv++) {  /* j = i-1; */ vnew[irv] = v[irv][i - 1]; }
			sc = c[i];
			for (ir = 0; ir< nA; ir++)
			{
				result1[ir] = 0;
				for (kr = 0; kr < 1; kr++) { result1[ir] = result1[ir] + vnew[ir] * sc; }

			}
			for (irv = 0; irv <nA; irv++) { vnew[irv] = v[irv][i]; }
			ss = s[i];
			for (ir = 0; ir < nA; ir++)
			{
				result2[ir] = 0;
				for (kr = 0; kr< 1; kr++) { result2[ir] = result2[ir] + vnew[ir] * ss; }
			}

			/* col1 = result1+result2;   addition of two nAx1 matrices  */

			for (ir = 0; ir < nA; ir++) { col1[ir] = result1[ir] + result2[ir]; }
			ss1 = -s[i];
			for (irv = 0; irv<nA; irv++)
			{
				for (irn = 0; irn < nA; irn++) { /*j = i-1; */ vnew[irv] = v[irv][i - 1]; }
			}
			for (ir = 0; ir < nA; ir++)
			{
				result3[ir] = 0;
				for (kr = 0; kr < 1; kr++) { result3[ir] = result3[ir] + vnew[ir] * ss1; }
			}

			/*               %c(i) * v(:,i)  */

			for (irv = 0; irv< nA; irv++) { vnew[irv] = v[irv][i]; }
			sc1 = c[i];
			for (ir = 0; ir < nA; ir++)
			{
				result4[ir] = 0;
				for (kr = 0; kr < 1; kr++) { result4[ir] = result4[ir] + vnew[ir] * sc1; }
			}
			/* addres = result3+result4 */ /* addition of two nAx1 matrices */

			for (ir = 0; ir < nA; ir++) { addres[ir] = result3[ir] + result4[ir]; }
			for (ir = 0; ir < nA; ir++) { v[ir][i] = addres[ir]; }
			/*  %v(:,i) = -s(i) * v(:,i-1) + c(i) * v(:,i) */
			/* 	%  v(:,i-1) = col1 */
			for (irv = 0; irv < nA; irv++) { /* for j = i-1; */ v[irv][i - 1] = col1[irv]; }



		}   /* i : 2 to togo end (that is 1 to togo-1) */





		if (fabs(Of[togo]) < TOL)
		{
			lambda[togo] = d[togo] + shift; togo = togo - 1;
		}
//		                  Jk[its] = lambda[togo];
//						  printf("!. %d %f\n", its, Jk[its]);


	} /* end of its loop */




	  /*free(lambda);*/
	//d = (free(d), NULL);  
	free(d);
	//Of = (free(Of), NULL); // 
	free(Of);
	//vnew = (free(vnew), NULL);  // 
	free(vnew);
	//result1 = (free(result1), NULL); //
	free(result1);
	//result2 = (free(result2), NULL); //
	free(result2);
	//result3 = (free(result3), NULL); //
	free(result3);
	//result4 = (free(result4), NULL); //
	free(result4);
	//col1 = (free(col1), NULL); //
	free(col1);
	//addres = (free(addres), NULL); //
	free(addres);
	//c = (free(c), NULL); //
	free(c);
	//s = (free(s), NULL); //
	free(s);
	//Oftemp = (free(Oftemp), NULL); //
	free(Oftemp);
	return;
}  /*Funtion end */


