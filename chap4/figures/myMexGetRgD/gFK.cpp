/****************************************************************************
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
 *///#include "stdafx.h"
#include "gFK.h"
double * rgSteering(complex **A, double *config, int * bins, double ** rgMat, double *sg,complex **steering)
{
//	printf("void rgSteering()\n");
	int numberOfTgts, rc[2];
	int i, k,cby2,s,e,ngs=15;
	double *jkG, *FnG, *phase, *gainCh,Qfn,phasor,Amp;
	complex *u, *uScale,abLocal,w; 	Cabs cabs;
	double *fn,delf,*rgAvg,phi,pi;
	numberOfTgts = (int)(config[4]);
	rc[0] = (int)(config[7]); rc[1] = 8; cby2 = rc[1] / 2;
	pi = atan(1.0)*4.0;
//	..............................................................
	u = (complex *)malloc(rc[0] * sizeof(complex));
	uScale = (complex *)malloc(rc[0] * sizeof(complex));
	fn = (double *)malloc(rc[0] * sizeof(double));
	jkG = (double *)malloc(ngs * sizeof(double)); // (double *)malloc(c * sizeof(double))
	FnG = (double *)malloc(ngs * sizeof(double));
	phase = (double *)malloc(ngs * sizeof(double));
	gainCh = (double *)malloc(cby2 * sizeof(double));
	rgAvg = (double *)malloc(numberOfTgts * sizeof(double));
//	..............................................................
	delf = 1.0F / ((double)(rc[0] - 1));        // this is causing an offset in range 25.8.2017 9pm
	for (k = 0; k < rc[0]; k++) fn[k] = k*delf; // replaced earlier N/2 with pM and N-1

	for (k = 0; k < cby2; k++)
	{
		for (i = 0; i < rc[0]; i++) u[i] = A[i][k]; // process each channel 
		gainCh[k] = normalize(rc[0], u, uScale);    // every channel is normalised
		for (i = 0; i < numberOfTgts; i++)
		{
			s = bins[i] - 1; e = bins[i] + 1;
			if (s < 0) s = 0; if (e >= rc[0]) e = rc[0] - 1;    // safety
			abLocal.r = fn[s]; abLocal.i = fn[e];
			Qfn = goldF(rc[0], uScale, jkG, FnG, phase, &abLocal, &phasor, ngs,gainCh[k]);
			steering[i][k] = abLocal; rgMat[i][k] = phasor;
//			printf("[%d] (%3.4f %3.4f)\n", bins[i], steering[i][k].r,steering[i][k].i);
		}
	}
//	14th Jul 2018 Dublin Ohio important correction on phase shifts with unequal time peaks
//	......... synchronized snap shots ...................
	for (i = 0; i < numberOfTgts; i++)
	{
		rgAvg[i] = 0.0F; 
		for (k = 0; k < cby2; k++) rgAvg[i] = rgAvg[i] + rgMat[i][k]; 
		rgAvg[i] = rgAvg[i] / cby2;
	}
	for (k = 0; k < cby2; k++)
	{
		for (i = 0; i < rc[0]; i++) u[i] = A[i][k]; // process each channel 
		for (i = 0; i < numberOfTgts; i++)
		{
			Amp = ObjFn(&phi, rc[0], rgAvg[i], u);
			w.r = Amp * cos(phi * pi / 180.0); w.i = Amp * sin(phi * pi / 180.0);
			steering[i][k] = w;
		}
	}
//	........................... Normalize Steering Vector ......................

	for (i = 0; i < numberOfTgts; i++)
	{
		gainCh[0] = 0.0; for (k = 0; k < cby2; k++) gainCh[k] = cabs.cabs(steering[i][k]);
		s = myMax(gainCh, cby2); sg[i] = gainCh[s];
		for (k = 0; k < cby2; k++)
		{
			steering[i][k].r = steering[i][k].r / sg[i];
			steering[i][k].i = steering[i][k].i / sg[i];
		}
	}
//	Free memory ..
	free(u); free(uScale);
	free(fn); free(jkG);
	free(FnG); free(phase);
	free(gainCh);
	return rgAvg;
}

double goldF
(
	int maxk,
	complex *u,
	double *jK,
	double *fn,
	double *phase,
	complex *B,
	double * phasor,
	int ngs,
	double gain
)
{
	double aa, bb, cc, dd;
	double fa, fb, fc, fd;
	double fm, mid;
	//	double fc, fd;
	double g, phi;
	double big = -1;
	//	double N;
	double pi = (double)atan(1.0)*4.0;
	double x[3], y[3];
	double d, a, b, c, s, v, qTgt, At;
	double ab[3];
	int i, NGS = 10;
	//  Copy Right Protected  written by Prof Kaluri
	//  1st May 2017   .
//	printf("double goldF()\n");
	NGS = ngs;
	//	printf("!. goldF(M[%d],x[%d],JkG,fnG,ab(%f,%f),ngs[%d]);\n", maxk, maxk, ab[0], ab[1], NGS);
	aa = B[0].r; bb = B[0].i; mid = (aa + bb)*0.5;
	g = (3 - sqrt(5)) / 2;
	fa = -ObjFn(&phi, maxk, aa, u);      //   Jk[k] = ObjFn(&phi,M,fn,u);
	fb = -ObjFn(&phi, maxk, bb, u);
	fm = -ObjFn(&phi, maxk, mid, u);
	for (i = 0; i < NGS; i++)
	{
		cc = aa + g*(bb - aa);
		dd = cc + g*(bb - cc);


		fc = -ObjFn(&phi, maxk, cc, u);
		fd = -ObjFn(&phi, maxk, dd, u); // negative sign to take care of maxima to look like minima 23-2-2016

		if (fc <= fd) { bb = aa; aa = dd; }
		else { aa = cc; cc = dd; }
		if (fabs(aa) > 1.0F) { aa = 1.0F; printf("!. out of bounds forced to %f\n", aa); getchar(); }
//		if (fabs(aa) > 2.0F) { printf("!. out of bounds %f\n", aa); aa = (fabs(aa) / aa)*2.0F; }
//		fn[i] = aa;  jK[i] = fabs(fa);
		fn[i] = aa;  jK[i] = fabs(fc); phase[i] = phi;
	}
	x[0] = 0.0; x[1] = (aa - ab[0]) / (ab[1] - ab[0]);          x[2] = 1.0;
	y[0] = 0.0; y[1] = fabs(fm) - fabs(fa);					  y[2] = fabs(fb) - fabs(fa);

	a = sqrt(1 + y[2] * y[2]); b = sqrt((1.0 - x[1])*(1.0 - x[1]) + (y[2] - y[1])*(y[2] - y[1]));
	c = sqrt(x[1] * x[1] + y[1] * y[1]);
	s = (a + b + c)*0.5; v = (s - a)*(s - b)*(s - c);
	d = a*b*c / (2 * sqrt(v*s));  At = asin(a / d) * 180 / pi;
	qTgt = 60.0 / At; // finds how sharp is the peak and qTgt is quality of peak.
					  //	printf("abc %3.4f %3.4f %3.4f radius %3.4f,[v %3.4f s %3.4f]\n", a, b, c,d,v,s);
					  //	printf("Peak Quality %3.4f\n", qTgt);
					  //	getchar();
	ab[0] = aa; ab[1] = fabs(fc)*gain; ab[2] = phi;
	B[0].r = ab[1] * cos(ab[2] * pi / 180.0F); B[0].i = ab[1] * sin(ab[2] * pi / 180.0F);
	phasor[0] = ab[0];
//	donot delete this .. printf("!. Fn %3.5f Amp %3.5f Phase %3.5f\n", ab[0], ab[1], ab[2]);
	return qTgt;
}

double ObjFn
(
	double *rp,
	int maxk,
	double fn, // this is changed as fn (0 to 1) for complex usage
	complex *u
)
{
//	printf("double ObjFn()\n");
	//	double theta = 0;
	double vK = 0, sum, sumA, sumB, p;
	double pi = (double)atan(1.0F)*4.0F;
	double I1, I2, I3, Q1, Q2, Q3, pC, pS;
	complex sumC, Xk, U, A, B;
	cmul mul; cadd add; Cabs cabs;
	int k;
	//  Copy Right Protected  written by Prof Kaluri
	//  15th Feb 2017   .
	//  Accelerator .. without Sine or Cosine ..  ..
	//        thetaP = 0.5F*p;
	//        theta = acos(thetaP); 
	//	myPrintfCom(u, maxk, 8);
	pC = cos(2.0 * pi*fn); pS = sin(2.0 * pi*fn); // evaluate objective function at fn
	p = 2.0F * pC;
	sumC.r = 0.0; sumC.i = 0.0;
	I2 = pS; I1 = 0;
	Q2 = pC; Q1 = 1;
	for (k = 0; k < maxk; k++)
	{
//		Xk.r = I1; Xk.i = -Q1; U = u[k]; // this will produce the reverse way .. for radar
		Xk.r = I1; Xk.i = Q1; U = u[k]; // the above commented  .. corrected 5th Oct 2017 .. for synthetic
		A = mul.mul(Xk, U); B = add.add(A, sumC); sumC = B;
		I3 = p*I2 - I1; I1 = I2; I2 = I3; // sine
		Q3 = p*Q2 - Q1; Q1 = Q2; Q2 = Q3; // co-sine
	}
	sumA = sumC.r; sumB = sumC.i;
	sum = cabs.cabs(sumC);
	rp[0] = ((atan2(sumB, sumA)));
	rp[0] = rp[0] * 180 / pi;
//	printf("!. OBJ .. @%3.4f,%3.4f .. %3.4f\n", fn, sum, rp[0]);
//	vK = sqrt(sum / maxk); // bug fix on amplitude 12th April 2017 .. 5th Oct 2017 removed mult by 2
	vK = sum / maxk;  //	printf("!. [%d]Fourier Spectrum at %f value %f\n",maxk,fn,vK);
//	why again sqrt on this absolute is taken ?? 11th July 2018 Dublin Ohio
	return(vK);
}
