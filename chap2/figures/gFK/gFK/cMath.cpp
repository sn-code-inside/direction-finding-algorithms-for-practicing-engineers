 /*... complex Maths Library Functions .....
  ... by Prof Kaluri V Ranga Rao,  ... 20th Sep 2017 .. */
//#include "stdafx.h"
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
#include "cMath.h"
complex cadd::add(complex a, complex b)
{
//  Copy Right Protected  written by Prof Kaluri
//  1st May 2017   .
	complex c;
	c.r = a.r + b.r;
	c.i = a.i + b.i;
	return c;
}
complex csub::sub(complex a, complex b)
{
//  Copy Right Protected  written by Prof Kaluri
//  1st May 2017   .
	complex c;
	c.r = a.r - b.r;
	c.i = a.i - b.i;
	return c;
}
complex cmul::mul(complex a, complex b)
{
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	complex c;
	c.r = a.r*b.r - a.i*b.i;
	c.i = a.i*b.r + a.r*b.i;
	return c;
}
complex conjmul::mulconj(complex a, complex b)
{
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	complex c;
	c.r = a.r*b.r + a.i*b.i;
	c.i = a.i*b.r - a.r*b.i;
	return c;
}
complex Conj::conj(complex a)
{
//  Copy Right Protected  written by Prof Kaluri
//  1st May 2017   .
	complex c;
	c.r = a.r; c.i = -a.r;
	return c;
}
double Cabs::cabs(complex a)
{
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	double c;
	c = (double)(sqrt(a.r*a.r + a.i*a.i));
	return c;
}
complex cdiv::div(complex a, complex b)
{
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	complex c; 	double den;

	c.r = b.r; c.i = -b.i;    // c = conj(b);
	c.r = a.r*b.r - c.i*b.i;  // c = cmul(a, c);
	c.i = a.i*b.r + c.r*b.i;
	den = b.r*b.r + b.i*b.i;
 	c.r = c.r / den; c.i = c.i / den;
	return c;
}

void myAngleDeg(double *angle, double *Amp, complex *vec, int cby2)
{
	int k; double x, y,pi;
	pi = (double)(atan(1.0)*4.0);
	for (k = 0; k < cby2; k++)
	{
		x = vec[k].r; y = vec[k].i; angle[k] = atan2(x, y)*180.0 / pi;
		Amp[k] = sqrt(x*x + y*y);
	}
	return;
}


void r2c(double **A, complex **B, int * rc)
{
	int i,k,r,c;
	r = rc[0]; c = rc[1];
//	.......... this conversion also brings conjugations also change of sign at imaginary quantity
//	............... 22 Sep 2017 ...........................
	for (i = 0; i < r; i++)
	{
		for (k = 0; k < c / 2; k++)
		{
			B[i][k].r = A[i][2 * k]; B[i][k].i = A[i][2 * k + 1]; // synthetic
//			B[i][k].r = A[i][2 * k]; B[i][k].i = -A[i][2 * k + 1]; // input has negative sign .. radar
		}
	}
	return;
}

void sampleSpek(complex *X, double *x, int N, int M)
{
	double pi;
	double temp;
	int j, k, l, NM1, le, le1, iP;
	int lsb, i, bitr, iby2, localK, w = 1;
	double Nr;
	complex U, W, T, *Xt;
	cmul mul; csub sub; cadd add; Cabs cabs;
//  Copy Right Protected  written by Prof Kaluri
//  15th Feb 2017   .
//  Fast Fourier Transform in C bug fixed by Prof Kaluri 19 Jan 2017
//  got the FORTRAN code from Openhiem and Schafer Book.
//	printf("7. sampleSpek(complex *X, double *x, int %d, int %d)\n", N, M);
//	printf("!. Original FFT Fortran Code Openheim and Schafer\n");
//	printf("!. I had problems and fixed and written in C\n");
	pi = 4.0*atan(1.0);
	NM1 = N - 1;  j = 0;
	Xt = (complex *)malloc(N * sizeof(complex));
	Nr = ((double)(N)) / (2.0F);
	for (k = 0; k < N; k++) // line 7
	{
		localK = k; bitr = 0; lsb = 0; w = (int)(pow(2, M - 1));
		for (i = 0; i < M + 1; i++)
		{
			iby2 = localK / 2;
			if (iby2 * 2 - localK < 0) lsb = 1; else lsb = 0;
			localK = iby2;
			bitr = bitr + lsb*w; w = w / 2;
		}
		Xt[k] = X[bitr];
	}
	for (k = 0; k < N; k++) X[k] = Xt[k];
	for (l = 0; l < M; l++) // line 20
	{
		le = (int)(pow(2, l + 1)); le1 = (le / 2);
		temp = pi / ((double)(le1));
		U.r = 1.0; U.i = 0.0;
		W.r = cos(temp);  W.i = sin(temp);
		for (j = 0; j < le1; j++)
		{
			for (i = j; i < N; i = i + le)
			{
				iP = (i + le1);
				T = mul.mul(X[iP], U);     // T = X[IP]*you;
				X[iP] = sub.sub(X[i], T);  // X[IP] = X[I] - T;
				X[i] = add.add(X[i], T);   // X[I]  = X[I] + T;
			}
			U = mul.mul(U, W);
		}
		U = mul.mul(U, W);
	}
	for (i = 0; i < N; i++) x[i] = (cabs.cabs(X[i]) / Nr)*0.5F; // on 10th Jun 2018 Princeton NJ .. verified with matlab FFT
//	{
//		xr = X[i].r; xi = X[i].i; 
//		x[i] = (sqrt(xr*xr + xi*xi))*(1.0F / Nr);
		
//	}
	free(Xt);
	return;
}

int myMax(double *JkC, int N)
{
	int k,km=0; double max=-1.0F;
	//  Copy Right Protected  written by Prof Kaluri
	for (k = 0; k < N; k++)
	{ 
		if (fabs(JkC[k]) > max) { max = fabs(JkC[k]); km = k; }
	}
//	printf("max value max %3.4f@%d - %3.4f\n", max, km, JkC[km]);
	return km;
}

void myMaxMin(double *x, double * minMax, int lenX)
{
	double max = -5000.0, min = 5000.0;
	int k;
	for (k = 0; k < lenX; k++)
	{
		if (x[k] >= max) max = x[k];
		if (x[k] < min)  min = x[k];
//		printf("! [%d](%3.4f) %3.4f %3.4f\n", k, x[k], min, max);
	}
	minMax[0] = min; minMax[1] = max;
	return;
}

int* Low2High(int M, double* x)
{
	int k, ip, i, tempI,*xI;
	double small, temp;
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	//	printf("9. sortLow2High( peak, peakI, %d);\n", M);
	xI = (int*)malloc(M * sizeof(int));
	for (ip = 0; ip < M; ip++) xI[ip] = ip;
	//  very simple bug took time but good do it again .. 23rd Feb 2016 at Hyderabad 11:46pm    
	i = 0; 
	for (ip = 0; ip < M; ip++)
	{
		small = x[ip]; i = ip; // this is important
		for (k = ip; k < M; k++)
		{
			if (x[k] < small) { small = x[k]; i = k; }  // min of x[ip:M] is @ i
		}
		temp = x[ip];   x[ip] = x[i];   x[i] = temp;   // Exchange
		tempI = xI[ip]; xI[ip] = xI[i]; xI[i] = tempI;  // Exchange pointers
	}
	return xI;
}

void myPrintf(double *JkC, int N, int perLine)
{
	int k,remPerLine;
	//  Copy Right Protected  written by Prof Kaluri
//	printf("void myPrintf()\n");
	for (k = 0; k < N; k++)
	{ 
		remPerLine = (k + 1) % perLine;
		printf("%3.4f ",JkC[k]); if (remPerLine == 0) printf("[%d]\n", k);
	} 
	return;
}

void myPrintfCom(complex *JkC, int N, int perLine)
{
	int k; double *JkCr, *JkCi;
	JkCr = (double *)malloc(N * sizeof(double));
	JkCi = (double *)malloc(N * sizeof(double));
	//  Copy Right Protected  written by Prof Kaluri
	for (k = 0; k < N; k++) { JkCr[k] = JkC[k].r; JkCi[k] = JkC[k].i; }
	printf("!. Real Values \n");
	myPrintf(JkCr, N, perLine);
	printf("!. Complex Values \n");
	myPrintf(JkCi, N, perLine);

	free(JkCr); free(JkCi);
	return;
}

void comMatAdd(complex **A, complex **B, int *rc)
{
	int i, k, r, c,cby2;
	cadd add;
	r = rc[0]; c = rc[1]; cby2 = c / 2;
	for (k = 0; k < r; k++)
	{
		for (i = 0; i < cby2; i++) A[k][i] = add.add(A[k][i], B[k][i]);
	}
}

void myPrintfI(int *JkC, int N, int perLine)
{
	int k, remPerLine;
	printf("void myPrintfI()\n");
	//  Copy Right Protected  written by Prof Kaluri
	for (k = 0; k < N; k++)
	{
		remPerLine = (k + 1) % perLine;
		printf("%d ", JkC[k]); if (remPerLine == 0) printf("[%d]\n", k);
	}
	return;
}

void myNoise
(
	int maxk,
	double std,
	double *uN
)
{
	int s, k;
	unsigned int seed;
	double rnd;
	seed = (unsigned int)(time(NULL));
	srand(seed);
//  Copy Right Protected  written by Prof Kaluri

//	printf(" Test Random Sequence ");
//	for (m = 0; m<5; m++) { temp = (rand() / 32767.0) - 0.5; printf(" %f ", temp); } printf("\n");

	for (k = 0; k<maxk; k++)
	{
		rnd = 0.0; for (s = 0; s<12; s++) rnd = rnd + ((rand() / 32767.0) - 0.5);
//		uN[k] = rnd * sqrt(std / 2);
		uN[k] = rnd * std;
	}
	return;
}

double normalize(int maxk, complex *u, complex *uScale) // u is the input uTemp is scaled and bias removed
{
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
	// this is modified to take care of the complex signals 29.4.2017 - 5pm
	double MuR, MuI, sumR, sumI, EkR, EkI, Ek, A;
	int k;

	sumR = 0.0; sumI = 0.0;
	for (k = 0; k < maxk; k++) // xr = X[i].r; xi = X[i].i;
	{
		sumR = sumR + u[k].r;
		sumI = sumI + u[k].i;
	}
	MuR = sumR / maxk; MuI = sumI / maxk;
	//	printf("mean Real %3.4f .. mean Imag %3.4f\n", MuR, MuI);
	EkR = 0.0; EkI = 0.0;
	for (k = 0; k < maxk; k++)
	{
		uScale[k].r = u[k].r - MuR; // subtract mean
		EkR = EkR + (uScale[k].r) * (uScale[k].r);
		uScale[k].i = u[k].i - MuI; // subtract mean
		EkI = EkI + (uScale[k].i) * (uScale[k].i);
	}
	EkR = EkR / maxk; EkI = EkI / maxk;
	if (EkR > EkI) Ek = EkR; else Ek = EkI; // take the maximum for scaling 29.4.2017 - 5pm
	A = sqrt(2 * Ek);
	//	printf("6. JkScale[%f] = normalize(%d,uTemp,x);\n", A, maxk);
	for (k = 0; k < maxk; k++)
	{
		uScale[k].r = uScale[k].r / A;
		uScale[k].i = uScale[k].i / A;
	}
	//	printf("!. Subtract mean[%3.2f-%3.2f] from uTemp and normalise \n!. by JkScale[%3.2f] to get x\n", MuR, MuI,A);
	return(A);
}


void MatrixInversion(double **A, int order, double **I)
{
	double temp, *sum, total, maxA, maxI;
	int i, j, k;
	// Matrix Inverse By Gauss Jordan Method
	//  Copy Right Protected  written by Prof Kaluri
	sum = (double *)malloc(order * sizeof(double));
	maxA = -1; for (i = 0; i < order; i++)
		for (j = 0; j < order; j++) if (fabs(A[i][j]) > maxA) maxA = fabs(A[i][j]);
	for (i = 0; i < order; i++)
		for (j = 0; j < order; j++) A[i][j] = A[i][j] / maxA;


	for (i = 0; i<order; i++)								//automatically initialize the unit matrix, e.g.
		for (j = 0; j<order; j++)							//	-       -
			if (i == j)	I[i][j] = 1;				  	    // | 1  0  0 |
			else I[i][j] = 0;								// | 0  1  0 |
															// | 0  0  1 |
															//  -       -
															/*---------------Gauss Jordan Method Row Operations ------------------*/
															//procedure to 	make the matrix A to unit matrix
			for (k = 0; k<order; k++)					//by some row operations,and the same row 	operations of
			{											//Unit mat. I gives the inverse of matrix A
				temp = A[k][k];					//'temp' stores the A[k][k] value so that 	A[k][k] will not change
				for (j = 0; j<order; j++)			//during the operation A[i][j]/=A[k][k] when i = j = k
				{
					A[k][j] = A[k][j] / temp;				//it performs the following row operations to 	make A to unit matrix
					I[k][j] = I[k][j] / temp;			//R0=R0/A[0][0],similarly for I also R0 = R0 / A[0][0]
				}									//R1=R1-R0*A[1][0] similarly for I
				for (i = 0; i<order; i++)				//R2=R2-R0*A[2][0]		,,
				{
					temp = A[i][k];						//R1=R1/A[1][1]
					for (j = 0; j<order; j++)			//R0=R0-R1*A[0][1]
					{									//R2=R2-R1*A[2][1]
						if (i == k) break;
						//R2=R2/A[2][2]
						//			A[i][j] -= A[k][j] * temp;		//R0=R0-R2*A[0][2]
						//			I[i][j] -= I[k][j] * temp;		//R1=R1-R2*A[1][2]
						A[i][j] = A[i][j] - A[k][j] * temp;		//R0=R0-R2*A[0][2]
						I[i][j] = I[i][j] - I[k][j] * temp;		//R1=R1-R2*A[1][2]
					}
				}
			}
			/*---------------Gauss Jordan Method Row Operations ends here--------------------*/
			maxI = -1;  for (i = 0; i < order; i++)
				for (j = 0; j < order; j++) if (fabs(I[i][j]) > maxI) maxI = fabs(I[i][j]);
//			printf("!. max value in Inverse %3.4f\n", maxI);
			// getchar();
			//for (i = 0; i < order; i++)
			//for (j = 0; j < order; j++) A[i][j] = A[i][j] / max;


//		printf("The inverse of the matrix is:\n");
//		Print the matrix I that now contains the inverse of mat.A
			for (i = 0; i < order; i++) sum[i] = 0; total = 0;
			for (i = 0; i < order; i++)
			{
				for (j = 0; j < order; j++) sum[i] = sum[i] + fabs(A[i][j]);
				total = total + sum[i];
			}
			if (total >(double)(order))
			{
				for (i = 0; i < order; i++) printf("%3.4f ", sum[i]); printf("\n");
			}

			return;
}

double ortho
(
	int maxk,		// total number of samples needed 
	complex *z	// complex sequence
)
{
	double uk1 = 0, uk0 = 0;
	double xk1 = 0, xk0 = 0, zk = 0, xK;
	double zk1 = 0, zk0 = 0;
	double ek = 0, pk = 0.0F, rk;
	double *dly, *bufer;
	//    double loopGain = 0.01F, shift = 0.0F;
	double loopGain = 0.05F, shift = 0.0F;
	int delay = 20, i, k,dPlus;// Integration window of MA Filter
	double *u, *x;
	double pi,gain,angle;
	//  Copy Right Protected  written by Prof Kaluri

	complex *zO;
	pi = (double)(4.0*atan(1.0F));
	dPlus = delay + 2;
	u = (double *)malloc(maxk * sizeof(double));
	x = (double *)malloc(maxk * sizeof(double));
	dly = (double *)malloc(dPlus * sizeof(double));
	bufer = (double *)malloc(dPlus * sizeof(double));
	zO = (complex *)malloc(maxk * sizeof(complex));
	//  Copy Right Protected  written by Prof Kaluri
	for (i = 0; i <= delay; i++) { bufer[i] = 0.0F; dly[i] = 0.0F; }
//	printf("!. creating 180 deg phase shift using orthogonal decomposer-18Mar2014\n");
	gain = normalize(maxk,z,zO);
	for (k = 0; k < maxk; k++) { u[k] = zO[k].r; x[k] = zO[k].i; }
	uk0 = 0.0F; xk1 = 0.0F; pk = 0.0F; uk1 = 0.0F; rk = 0.1F;
	for (k = 0; k < maxk; k++)
	{

		uk1 = uk0; xk1 = xk0; zk1 = zk0;
		uk0 = x[k]; // input sequence uk 
		xK = u[k]; //  input sequence xk

		xk0 = rk*xk1 - rk*uk0 + uk1; //% uk0 --> APF --> xk0
//		zk0 = rk*zk1 - rk*xk0 + xk1; //% xk0 --> APF --> zk0
		zk = uk0*xK;
		//y[k] = xk0;

		//1. transfer dly into bufer [1 to 40].
		for (i = 0; i <= delay; i++) 	bufer[i + 1] = dly[i];

		//2. bufer[0] equates to zk.
		bufer[0] = zk;

		//3. transfer bufer [0 to 39] into dly.
		for (i = 0; i <= delay; i++) 	dly[i] = bufer[i];


		ek = (dly[delay] - dly[0]) / (delay);
//        if ( fabs(pk) > big ) big = fabs(pk);
		pk = pk + ek; rk = rk - loopGain*(pk + shift);

		if (fabs(rk) > 0.99F) rk = 0.99F;
//		gain = uk0 + zk0;
//        yTemp[k] = pk; 

        angle =(double)( (acos(sin(2.0*atan(rk))))/(2*pi) );


//        y[k] = zk0; //28 May 2014 sarita
//        y[k] = pk;
	}
	free(u); free(x); free(dly); free(bufer);
	free(zO);

	return(angle*180/pi);
}

void muStd(double *x, double *std, double *mu, int lenX)
{
	int k; double sum,ek;
	sum = 0.0;
	for (k = 0; k < lenX; k++) sum = sum + x[k]; mu[0] = sum / lenX;
	ek = 0.0;
	for (k = 0; k < lenX; k++) ek = ek + (x[k] - mu[0])*(x[k] - mu[0]);
	std[0] = ek / lenX;
	return;
}





