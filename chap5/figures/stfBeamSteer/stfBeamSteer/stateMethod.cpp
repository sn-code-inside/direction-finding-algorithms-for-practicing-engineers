#include "stateMethod.h"
extern FILE* fp;
//#include "mex.h"   /* This one is required */
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
double* stateDecode(double** doa3, int D, int ula, int*Kt)
{
	int kt, k,*tgtIndx,zone;
	double* validPhi;
	validPhi = myAlloc(4); //estPhi = myAlloc(D);
	for (k = 0; k < D; k++)  validPhi[k] = 0.0;
	kt = 0;
	for (k = 0; k < D; k++)
	{
		tgtIndx = extractTgt(doa3, &validPhi[k], D - k, &zone);
		if (tgtIndx[0] < 0) break;
		if (k < D - 1) resize(doa3, tgtIndx, D - k);
	} kt = k + 1;
	Kt[0] = kt;
	return validPhi;
}

int* extractTgt(double** doa3, double* validphi, int D, int* Zone)
{
	int kt, i, j, k,   ula, zone;
	complex** doa3Pair, * v;
	int * tgtIndx, flagDist;
	kt = 0; ula = 3;
	doa3Pair = myAlloc2Complex(ula, D); 
	tgtIndx = myAllocI(ula);
	printf(" -----------------------------\n");
	printf(" ULA-A peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[0][k]); printf("\n");
	printf(" ULA-B peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[1][k]); printf("\n");
	printf(" ULA-C peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[2][k]); printf("\n");


	for (k = 0; k < D; k++)
	{
		for (i = 0; i < ula; i++)
			doa3Pair[i][k] = doa2weights(doa3[i][k]);
	}
	v = myAllocComplex(ula);


	kt = 0;
	for (i = 0; i < D; i++)
	{
		v[0] = doa3Pair[0][i]; // target i ula A
		for (k = 0; k < D; k++)
		{
			v[1] = doa3Pair[1][k]; // target k ula B
			for (j = 0; j < D; j++)
			{
				v[2] = doa3Pair[2][j];// target j ula C
				flagDist = distCheck(v, ula);
				if (flagDist >= 0)
				{
					zone = map3ula(v, ula, validphi);
					Zone[0] = zone;
					if (zone > 0)
					{
						//flagDist = distCheck(v, ula);
						//printf(" flag %d\n", flag);
						if (flagDist > 0)
						{
							tgtIndx[0] = i; tgtIndx[1] = k; tgtIndx[2] = j;
							myFree2Complex(doa3Pair, ula); 
							printf("...............................\n");
							printf("(%d) used [%3.4f %3.4f %3.4f]-->(%3.4f)\n", zone, v[0].r, v[1].r, v[2].r, validphi[0]);
							printf("...............................\n");
							free(v);
							return tgtIndx;
						}
					}
				}
			}
		}
	}
	tgtIndx[0] = -1; return tgtIndx;
}




int map3ula(complex* v, int c, double* theta)
{
	int    zone;
	double phi, psi;

	phi = 0.0;
	psi = fixPeaks(v, c);
	zone = (int)(v[0].i) * 9 + (int)(v[1].i) * 3 + (int)(v[2].i) * 1;
	//printf(" zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
	//printf(" zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);

	switch (zone)
	{
	case 20:  //132
		phi = -psi + 60.0;
		//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
		break;
	case 18:  //123
		phi = psi - 60.0;
		//printf("zone %d [%3.4f]----->(%3.4f)\n", zone, v[2].r-v[1].r, phi);
		break;
	case 24:  //213
		phi = -psi;
		//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
		break;
	case 32:  //312
		phi = psi - 120.0;
		//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
		break;
	case 34:  //321
		phi = -psi + 120.0;
		//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
		break;
	case 28:  //231
		phi = psi;
		//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
		break;
	default:
		zone = -zone;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		//getchar();
		break;
	}
	//if (fabs(dist) > 5) zone = -1;
	//else
	//{
		//printf("[%3.4f]\n", dist);
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
	//}

	theta[0] = phi;
	printf(" outcome after decoding %3.4f\n", phi);
	return zone;
}

complex doa2weights(double theta)
{
	complex thetaPair;
	thetaPair.r = theta;
	if (theta > 60) thetaPair.i = 3;
	else
	{
		if (theta < 30.0) thetaPair.i = 1;
		else
		{
			thetaPair.i = 2;
		}
	}
	return thetaPair;
}


int distCheck(complex* v, int ula)
{
	int flag;
	double  dist, a, b, pk;
	double thresold = 60;
	a = (v[0].r + v[1].r + v[2].r);
	dist = fabs(130 - a);
	if (dist < thresold) flag = 1; else flag = -1;
	b = v[1].r - v[2].r;
	if (b < 0) pk = -v[0].r; else pk = v[0].r;
	//printf(" flag(%d) distance %3.4f estimated peak %3.4f\n", flag, dist, pk);
	return flag;
}

double  fixPeaks(complex* v, int c)
{
	double psi;
	int k, zone;
	psi = 0.0;
	//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
	zone = (int)(v[0].i) * 9 + (int)(v[1].i) * 3 + (int)(v[2].i) * 1;
	switch (zone)
	{
	case 23:
		if (v[0].r > v[2].r) v[0].i = 3; else v[2].i = 3;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 25:
		if (v[0].r > v[1].r) v[0].i = 3; else v[1].i = 3;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 27:
		if (v[0].r > v[1].r) v[0].i = 1; else v[1].i = 1;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 17: // 122
		if (v[1].r > v[2].r) v[1].i = 3; else v[2].i = 3;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 33: // 313
		if (v[0].r < v[2].r) v[0].i = 2; else v[2].i = 2;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 37: // 331
		if (v[0].r < v[1].r) v[0].i = 2; else v[1].i = 2;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 21: // 133
		if (v[1].r < v[2].r) v[1].i = 2; else v[2].i = 2;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	case 29: // 232
		if (v[0].r < v[2].r) v[0].i = 1; else v[2].i = 1;
		//printf("     zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
		//zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
		//printf("new->zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);
		break;
	default:
		break;
	}
	for (k = 0; k < c; k++)
	{
		if ((int)(v[k].i) == 2)
			psi = v[k].r;
	}
	printf(" CHECK FOR %d IN (23,25,27,17,33,37,21,29) FOR SINGULAR VALUES\n", zone);
	return psi;
}






double* JacobiRotation(double** doa3, int D, int ula)
{
	double* a, * b, * c, * phi;
	double pkB, pkC, temp;
	int i;
	a = myAlloc(D); b = myAlloc(D); c = myAlloc(D);
	phi = myAlloc(D);
	printf(" peaks A ");
	for (i = 0; i < D; i++)
	{
		a[i] = doa3[0][i];
		b[i] = doa3[1][i];
		c[i] = doa3[2][i];
		printf(" %3.4f ", a[i]);
	} printf("\n");
	for (i = 0; i < D; i++)
	{
		pkC = rotateUla(60.0, c[i]);
		printf(" peak C[%3.4f]-->A  %3.4f\n", c[i], pkC);
		pkC = pkC + 30.0;
		if (pkC < 0) pkC = 0.0;

		pkB = rotateUla(-60.0, b[i]);
		printf(" peak B[%3.4f]-->A  %3.4f\n", b[i], pkB);
		pkB = 90.0 - pkB;
		if (pkB > 0) pkB = 0.0;

		if (c[i] < 20)
		{
			if (pkB < 0) { pkB = -pkB + 60; pkC = 0; }
		}

		if (pkB < 0)
		{
			if (pkC > 0) { pkB = 0; pkC = -pkC - 60; }
		}
		phi[i] = pkB + pkC;
		printf(" ..%3.4f %3.4f\n", pkB, pkC);
		//	............... correction
		if (phi[i] > 90.0)  phi[i] = phi[i] - 180.0;
		else
		{
			if (phi[i] < -90.0) phi[i] = phi[i] + 180.0;
		}
		printf(" ..%3.4f %3.4f\n", pkB, pkC);

	}
	printf(" peaks A           "); for (i = 0; i < D; i++) printf("%3.4f ", a[i]); printf("\n");
	return phi;
}
