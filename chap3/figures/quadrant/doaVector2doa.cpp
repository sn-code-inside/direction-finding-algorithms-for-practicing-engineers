/*

quadrant resolution algorithm

*/

#include "math.h"
#include "mex.h"   /* This one is required */
void Usage();

void Usage()
{
    printf("Non linear algorithm\n");
    printf("updated 29th Oct 2024 Belle Mead NJ For Book Writing\n");
	printf("Usage: [thetaA thetaB obj]=doaVector2doa[thetavector]\n"); 
    printf("thetavector is a 3 vector\n");    
    printf("thetaA is azimuth angle channel 1\n");
    printf("thetaB is azimuth angle channel 2\n");
    printf("obj is the objective function\n");
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputThetaV;
	double *thetaptrAB, *thetaptrAC,*objptr,thetaC ,thetaA , thetaB;  
    double thetaAB,thetaAC;
    int w[3],obj;
	int k,r,c;

    if ((nlhs != 3) || (nrhs != 1))
    {
        printf("  Usage Error Parameters LHS = %d(3) .. RHS= %d(1) \n", nlhs, nrhs);
        Usage();
		return;
	}
    
       
    r = mxGetM(prhs[0]); c = mxGetN(prhs[0]);
	if (r != 1)
	{
		Usage(); 
        printf("In this call, u is a vector try transpose error (%d by %d)\n",r,c);
		return;
	}
    if (c != 3) {printf(" error"); return;}
    inputThetaV = mxGetPr(prhs[0]);
    thetaC = inputThetaV[0]; thetaA = inputThetaV[1];
    thetaB = inputThetaV[2];
	plhs[0] = mxCreateDoubleMatrix(1,1, mxREAL);
	thetaptrAB = mxGetPr(plhs[0]);
	plhs[1] = mxCreateDoubleMatrix(1,1, mxREAL);
	thetaptrAC = mxGetPr(plhs[1]);
    plhs[2] = mxCreateDoubleMatrix(1,1, mxREAL);
	objptr = mxGetPr(plhs[2]);
    if (thetaA > 0 ) w[0] = 1; else w[0] = 0;
    if (thetaB > 0 ) w[1] = 1; else w[1] = 0;
    if (thetaC > 0 ) w[2] = 1; else w[2] = 0;
    obj = w[0]*4 + w[1]*2 + w[2];
   
    objptr[0] = obj;
    
    switch(obj)
    {
        // (-180 to -120)
        case 4:
        thetaAB =  - thetaA - 120.0; thetaAC =  - thetaC - 180.0;
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        // -120 to -60
        case 0:
        thetaAB = thetaB - 60.0; thetaAC = - thetaA - 120.0;
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        // -60 to 0
        case 2:
        thetaAB = thetaB - 60.0; thetaAC = thetaC;
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        // 0 to 60
        case 3:
        thetaAB = thetaA + 60.0; thetaAC = thetaC;
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        // 60 to 120
        case 7:
        thetaAB = -thetaB +120.0;  thetaAC = thetaA + 60.0; 
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        // 120 to 180
        case 5:
        thetaAB = -thetaB +120.0;  thetaAC = -thetaC + 180.0; 
        thetaptrAB[0] = thetaAB;   
        thetaptrAC[0] = thetaAC;   
        break;
        default:
        thetaptrAB[0] = 0.0;   
        thetaptrAC[0] = 0.0;   
    }

    return;
}
