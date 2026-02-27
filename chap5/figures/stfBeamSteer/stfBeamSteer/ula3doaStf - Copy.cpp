#include "ula3doaStf.h"
//#include "mex.h"   /* This one is required */

double** ula3doa(double **Ha, double** Hb, double** Hc, double r, double d_by_lambda, int m, int D, double* se, int kmax, double **doa3stf)
{
	int i, k,j,zone,ula = 3,kt,p,*tgtIndx;
	double** JkTheta, ** Jk3Theta, ** doaStf, ** doa3;

	double v[3],phi,dist,*validPhi;
	Jk3Theta = myAlloc2(4, kmax); doaStf = myAlloc2(D, 2); 
	doa3 = myAlloc2(3, D); 
	// Ula A
	JkTheta = stfDoa(Ha, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[0][k] = JkTheta[0][k];

	printf("ULA A gold peaks ");
	for (i = 0; i < D; i++) 
	{ 
		printf("--- %3.4f ", doaStf[i][0]); 
		doa3[0][i] = doaStf[i][0];
		doa3stf[0][i] = doaStf[i][0]; 
		doa3stf[1][i] = doaStf[i][1]; 
	} printf("\n");

	// Ula B
	JkTheta = stfDoa(Hb, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[1][k] = JkTheta[0][k];

	printf("ULA B gold peaks ");
	for (i = 0; i < D; i++)
	{
		printf("--- %3.4f ", doaStf[i][0]);
		doa3stf[2][i] = doaStf[i][0]; doa3[1][i] = doaStf[i][0];
		doa3stf[3][i] = doaStf[i][1];
	} printf("\n");

	// Ula C
	JkTheta = stfDoa(Hc, r, d_by_lambda, m, D, se, kmax, doaStf);
	for (k = 0; k < kmax; k++) 	Jk3Theta[2][k] = JkTheta[0][k];
	for (k = 0; k < kmax; k++) 	Jk3Theta[3][k] = JkTheta[1][k];
	printf("ULA C gold peaks ");
	for (i = 0; i < D; i++)
	{
		printf("--- %3.4f ", doaStf[i][0]);
		doa3stf[4][i] = doaStf[i][0]; doa3[2][i] = doaStf[i][0];
		doa3stf[5][i] = doaStf[i][1];
	} printf("\n");

	validPhi = myAlloc(4);
	//kt = scanAllDoa(doa3,validPhi,D,&zone);
	for (k = 0; k < ula; k++)
	{
		tgtIndx = extractTgt(doa3, &validPhi[k], D - k, &zone);
		if (tgtIndx == NULL) break;
		if (k == 2) break;
		resize(doa3, tgtIndx, D - k);
	}
	getchar;
	/*tgtIndx = extractTgt(doa3, &validPhi[1], D - 1, &zone);
	printf("%d %d %d\n", tgtIndx[0], tgtIndx[1], tgtIndx[2]);
	resize(doa3, tgtIndx, D-1);
	tgtIndx = extractTgt(doa3, &validPhi[2], D - 2, &zone);
			printf("%d %d %d\n", tgtIndx[0], tgtIndx[1], tgtIndx[2]);
*/

/*	for (k = 0; k < kt; k++)
	{
		printf("[%3.4f] -- ", validPhi[k][0]);
		for (i = 1; i < 4; i++) printf("%3.4f ", validPhi[k][i]); printf("\n");
	}*/

	return Jk3Theta;
}

void resize(double** doa3, int* tgtIndx,int D)
{
	int i, j, k;
	double temp;
	for (j = 0; j < 3; j++)
	{
		k = tgtIndx[j]; 
		temp = doa3[j][D-1];  doa3[j][D-1] = doa3[j][k];
		doa3[j][k] = temp;
		printf("[%d] ", j); for (i = 0; i < D; i++) printf("%3.4f ", doa3[j][i]); printf("\n");
	}
	return;
}

int* extractTgt(double** doa3, double* validphi, int D, int* Zone)
{
	int kt, i, j, k, p, m, ula, zone;
	double phi, dist;
	complex** doa3Pair, * v;
	int indx[3], flag, ** doa3PairFlag,  * tgtIndx, flagDist;
	kt = 0; ula = 3;
	doa3Pair = myAlloc2Complex(ula, D); doa3PairFlag = myAlloc2I(ula, D);
	tgtIndx = myAllocI(ula);
	printf(" -----------------------------\n");
	printf(" ULA-A peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[0][k]); printf("\n");
	printf(" ULA-B peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[1][k]); printf("\n");
	printf(" ULA-C peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[2][k]); printf("\n");

	for (k = 0; k < D; k++)
	{
		for (i = 0; i < ula; i++) doa3PairFlag[i][k] = 0;
	}

	for (k = 0; k < D; k++)
	{
		for (i = 0; i < ula; i++)
			doa3Pair[i][k] = doa2weights(doa3[i][k]);
	}
	//indx[0] = -1; indx[1] = -1; indx[2] = -1;
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
				flag = doa3PairFlag[0][i] + doa3PairFlag[1][k] + doa3PairFlag[2][j];
				if (flag >= 0)
				{
					zone = map3ula(v, ula, validphi);
					Zone[0] = zone;
					if (zone > 0)
					{
						flagDist = distCheck(v, ula);
						//printf(" flag %d\n", flag);
						if (flagDist > 0)
						{
							doa3PairFlag[0][i] = -1; doa3PairFlag[1][k] = -1;
							doa3PairFlag[2][j] = -1;
							tgtIndx[0] = i; tgtIndx[1] = k; tgtIndx[2] = j;
							myFree2Complex(doa3Pair, ula);
							myFree2I(doa3PairFlag, ula);
							printf("(%d) used [%3.4f %3.4f %3.4f]-->(%3.4f)\n", zone, v[0].r, v[1].r, v[2].r,validphi[0]);
							free(v);
							return tgtIndx;
						}
					}
				}
			}
		}
	} 
	return NULL;
}



int scanAllDoa(double ** doa3, double* validphi,int D, int*Zone)
{
	int kt, i, j, k, p,m,ula,zone;
	double phi, dist;
	complex** doa3Pair,*v;
	int indx[3],flag,**doa3PairFlag,flagDist;
	kt = 0; ula = 3;
	doa3Pair = myAlloc2Complex(ula, D); doa3PairFlag = myAlloc2I(ula, D);
	printf(" -----------------------------\n");
	printf(" ULA-A peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[0][k]); printf("\n");
	printf(" ULA-B peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[1][k]); printf("\n");
	printf(" ULA-C peaks "); for (k = 0; k < D; k++) printf(" %3.4f ", doa3[2][k]); printf("\n");

	for (k = 0; k < D; k++)
	{
		for (i = 0; i < ula; i++) doa3PairFlag[i][k] = 0;
	}
	
	for (k = 0; k < D; k++)
	{
		for (i = 0; i < ula; i++)
			doa3Pair[i][k] = doa2weights(doa3[i][k]);
	}
	indx[0] = -1; indx[1] = -1; indx[2] = -1;
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
						if (flagDist > 0)
						printf(" %3.4f %3.4f %3.4f \n", v[0].r, v[1].r, v[2].r);
			}
		}
	} printf("\n");
	return kt;
}

int distCheck(complex* v, int ula)
{
	int k,flag;
	double max, min,dist,a,b,pk;
	a = (v[0].r + v[1].r + v[2].r);
	dist = fabs(130 - a);
	if (dist < 5) flag = 1; else flag = -1;
	b = v[1].r - v[2].r;
	if (b < 0) pk = -v[0].r; else pk = v[0].r;
	printf("flag(%d) distance %3.4f estimated peak %3.4f\n", flag, dist,pk);
	return flag;
}

double  fixPeaks(complex* v, int c)
{
	double psi;
	int k,zone;
	psi = 0.0;
	zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
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

int map3ula(complex *v,int c, double *theta)
{
	int k, p, flag,zone;
	double phi,psi,dist;

	phi = 0.0;
	psi = fixPeaks(v, c);
	zone = v[0].i * 9 + v[1].i * 3 + v[2].i * 1;
	printf(" zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].i, v[1].i, v[2].i);
	printf(" zone %d [%3.4f %3.4f %3.4f]\n", zone, v[0].r, v[1].r, v[2].r);

	switch (zone)
	{
		case 20:  //132
			phi = -psi + 60.0;
			//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
			break;
		case 18:  //123
			phi =  psi - 60.0;   
			//printf("zone %d [%3.4f]----->(%3.4f)\n", zone, v[2].r-v[1].r, phi);
			break;
		case 24:  //213
			phi = -psi;         
			//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
			break;
		case 32:  //312
			phi =  psi - 120.0;  
			//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
			break;
		case 34:  //321
			phi = -psi + 120.0; 
			//printf("zone %d(%3.4f) [%3.4f %3.4f %3.4f]----->(%3.4f)\n", zone, psi, v[0].r, v[1].r, v[2].r, phi);
			break;
		case 28:  //231
			phi =  psi;          
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
