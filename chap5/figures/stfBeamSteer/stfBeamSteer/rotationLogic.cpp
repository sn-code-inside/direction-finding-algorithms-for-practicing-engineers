#include "rotationLogic.h"
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

double* rotateDecode(double** doa3, int D, int ula, int* Kt)
{
	int i, j, kt, k, * tgtIndx{};
	double* validPhi;
	validPhi = myAlloc(D); 
	for (k = 0; k < D; k++)  validPhi[k] = 0.0;
	for (j = 0; j < ula; j++)
	{
		printf("[%d] ", j); for (i = 0; i < D; i++) printf("%3.4f ", doa3[j][i]); printf("\n");
	}
	kt = 0;
	for (k = 0; k < D; k++)
	{
		tgtIndx = rotateAndExtract(doa3, &validPhi[k], ula, D - k);
		if (tgtIndx[0] < 0)  break; 
		printf("[%d][%d]---------------------------------------------%d\n", tgtIndx[0],D-k, k);
		if (k < D-1) resize(doa3, tgtIndx, D - k);
	} kt = k + 1;
	//getchar();
	Kt[0] = kt;
	return validPhi;
}
 

int* rotateAndExtract(double** doa3, double *validPhi, int ula, int D)
{
	int i, k, j, kt,er=1,* tgtIndx;
	int zone;
	double* v, a, dist,validphi;
	double angle,distThreshold=20;
	v = myAlloc(ula); 
	tgtIndx = myAllocI(ula); for (i = 0; i < ula; i++) tgtIndx[i] = 0;
	kt = 0; 
	for (i = 0; i < D; i++)
	{
		v[0] = doa3[0][i]; // target i ula A
		for (k = 0; k < D; k++)
		{
			
			v[1] = doa3[1][k]; // target k ula B
			for (j = 0; j < D; j++)
			{
				
				v[2] = doa3[2][j];// target j ula C
				a = (v[0] + v[1] + v[2]);
				dist = fabs(130 - a);
				if (D == 1) distThreshold = 100; 
				if (D == 2) distThreshold = 80;
				if (D == 3) distThreshold = 10;
				printf("[%d]------%3.4f %3.4f %3.4f--(%3.4f)\n", D, v[0], v[1], v[2],a);
				if (dist < distThreshold)
				{
					er = rotationMatch(v, ula, &kt,&angle);
					//printf("--------------------------------------%3.4f\n", angle);
					if (er > 0) 
					{
						tgtIndx[0] = i; tgtIndx[1] = k; tgtIndx[2] = j;
						free(v);
						//printf("----------[%d] %3.4f\n", kt, angle);
						validPhi[0] = angle;
						return tgtIndx;
					}
				}
			}
		}
	}
	if (er > 0) return tgtIndx; else
	{
		tgtIndx[0] = -1;
		printf(" error out put condition \n");
		return tgtIndx;
	}
}

int rotationMatch(double* v, int ula, int* Kt, double* doa)
{
	double xa, xb, xc, xp60, xp90, yn60, yn90;
	double thresholdB, thresholdC;
	int er, kt, band, * bin, k, state;
	kt = Kt[0];
	bin = myAllocI(4);
	doa[0] = 0;
	
	xa = rotateUla(60.0, v[0]) - 30;
	xb = rotateUla(-60.0, v[1]) - 90;
	xc = rotateUla(60.0, v[2]) + 30;
	if (v[0] > 60)
	{
		xb = -xb + 120;
		xc = -xc + 120;
	}
	// ...................................................................
	xp60 = 0; xp90 = 0; yn60 = 0; yn90 = 0; 
	thresholdC = 5.0; thresholdB = 5.0;
	if (xb > 90) bin[0] = 1; else bin[0] = 0;
	if (xc > 90) bin[1] = 1; else bin[1] = 0;
	if (fabs(v[0] - xb) < thresholdB) bin[2] = 1; else bin[2] = 0;
	if (fabs(v[0] - xc) < thresholdC) bin[3] = 1; else bin[3] = 0;
	state = 8 * bin[0] + 4 * bin[1] + 2 * bin[2] + 1 * bin[3];

	//fprintf(fp, "%d, ", state);
	//for (k = 0; k < 4; k++) fprintf(fp, "%d, ", bin[k]); fprintf(fp, "\n");

	er = 1; band = 0;
	printf("-----[b]. %3.4f  %3.4f %3.4f\n", v[0], xb, xc);
	//	........... Negative conditions -90 to 0
	switch (state)
	{
		case 4: //if (xc > 90)
		printf("-----[1]. %3.4f  %3.4f %3.4f\n", v[0], xb, xc);
		if (xb > 60 && xb < 90)
		{
			xc = 180.0 - xc;
			yn90 = -(xc + xb) / 2.0;
		}
		{
			band = 1;
			doa[0] = yn90;
		}
		break;

		case 2: //if (fabs(v[0] - xb) < thresholdB)
		printf("-----[2]. %3.4f  %3.4f %3.4f\n", v[0], xb, xc);
		if (v[0] < 60.0)
		{
			yn60 = -(v[0]+xb)/2.0;
			//if (yn60 < -60) er = -1;
		}
		//if (er > 0)
		{
			band = 2;
			doa[0] = yn60;
		}
		break;

		//	........... Positive conditions 0 to 90

		case 1: //if (fabs(v[0] - xc) < thresholdC)
		printf("-----[3]. %3.4f  %3.4f  %3.4f\n", v[0], xb, xc);
		if (v[0] < 60.0)
		{
			xp60 = (v[0]+xc)/2.0;
			band = 3; 	doa[0] = xp60;
		}
		break;

		case 8: //if (xb > 90)
		printf("-----[4]. %3.4f  %3.4f  %3.4f\n", v[0], xb, xc);
		if (xc > 60 && xc < 90)
		{
			xb = 180.0 - xb;
			xp90 = (xc + xb) / 2.0;
		}
		//else er = -1;
		//if (er > 0)
		{
			band = 3;
			doa[0] = xp90;
		}
		break;

		case 9:
			printf("-----[4]. %3.4f  %3.4f  %3.4f\n", v[0], xb, xc);
			xb = 180.0 - xb;
			xp90 = (xc + xb) / 2.0;
			doa[0] = xp90;
		break;

		case 6:
			printf("-----[1]. %3.4f  %3.4f  %3.4f\n", v[0], xb, xc);
			xc = 180.0 - xc;
			yn90 = -(xc + xb) / 2.0;
			doa[0] = yn90;
		break;


		default:
			er = -1;
			//if (xc > xb) { doa[0] = xc; xp60 = xc; }
			//if (xb > xc) { doa[0] = -xb; yn60 = -xb; }
		printf("-----[?]. %3.4f  %3.4f  %3.4f\n", v[0], xb, xc);
		//printf("state[%d] ", state); for (k = 0; k < 4; k++) printf("%d ", bin[k]); printf("\n");
		//getchar();
		break;
	}

	//if (doa[0] == 0.0) er = -1;
	if (er > 0)
	{
		printf("     [%d] %3.4f  %3.4f  %3.4f  %3.4f .. (%3.4f)\n", state, yn90, yn60, xp60, xp90,doa[0]);
		kt = kt + 1;
	}
	else printf(" error in decoding\n");
	//fprintf(fp, "%d,%3.4f, %3.4f, %3.4f, %3.4f\n",band, v[0], xb, xc,doa[0]);
	//fprintf(fp, "%3.4f,  %3.4f,  %3.4f, %3.4f\n", yn90, yn60, xp60, xp90);
	Kt[0] = kt;
	return er;
}


void resize(double** doa3, int* tgtIndx, int D)
{
	int j, k,i,ula=3;
	double temp;
	for (j = 0; j < ula; j++)
	{
		k = tgtIndx[j];
		temp = doa3[j][D - 1];  doa3[j][D - 1] = doa3[j][k];
		doa3[j][k] = temp;
		printf("[%d] ", j); for (i = 0; i < D; i++) printf("%3.4f ", doa3[j][i]); printf("\n");
	}
	return;
}


double rotateUla(double rotAng, double ci)
{
	double xc, yc, pi, num, den, pkC;
	pi = atan(1.0) * 4.0;
	rotAng = rotAng * pi / 180.0;
	xc = cos(ci * pi / 180.0); yc = sin(ci * pi / 180.0);
	num = xc * cos(rotAng) - yc * sin(rotAng);
	den = xc * sin(rotAng) + yc * cos(rotAng);
	pkC = atan2(num, den);
	pkC = pkC * 180.0 / pi;
	return pkC;
}
