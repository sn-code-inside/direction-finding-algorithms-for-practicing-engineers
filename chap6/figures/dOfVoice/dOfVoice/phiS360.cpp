#include "cMath.h"
#include "phiShift.h"   
#include "mex.h" /* This one is required */
void Usage();
//int ChoseAPForder(double, double ,	int , double *, double *);
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputU, *inputTau, *inputFn; 
	int maxk, N;
	double angle;
    double fc,fs,fn;
    double *y;
	int k,r,c;
    int status = -1;
    double *sptr,*yptr;
    if ( (nlhs != 2) || (nrhs != 3) )
    {
       printf(" Usage Error Parameters Left Hand Side = %d(2) .. Right Hand Side = %d(3) \n",nlhs,nrhs);
       Usage(); 
       return;
    }

    r = (int)(mxGetM(prhs[0])); maxk = (int)(mxGetN(prhs[0]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[0] must be a row vector try transpose\n");
	inputU = mxGetPr(prhs[0]);

    r = (int)(mxGetM(prhs[1]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[1] must be scalar\n");
    inputTau = mxGetPr(prhs[1]); angle = inputTau[0];

    r = (int)(mxGetM(prhs[2]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[2] must be scalar\n");

    inputFn = mxGetPr(prhs[2]); fn = inputFn[0];


    y = (double*)malloc(maxk * sizeof(double));
    plhs[0] = mxCreateDoubleMatrix(1, maxk, mxREAL);
	yptr = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
    sptr = mxGetPr(plhs[1]);
    sptr[0] = status;
    status = ChoseAPForder(angle, fn, maxk, inputU , y);
    if (status < 0) mexErrMsgTxt("!. Problem in Shifting\n");
    for (k = 0; k < maxk; k++) yptr[k] = y[k];
   

    sptr[0] = status;
	/* towards freedom! */
	free(y);
    return;
}

void Usage()
{
   printf(" updated on 23rd Jun 2024 9:40pm Dublin Ohio\n"); 
   printf(" [y, status]=phiS360(u, Shift, fn)\n");
   printf(" Inputs: 3\n");
   printf(" 1. u is input vector (sequence) Narrow Band Signal\n");
   printf(" 2. Shift is the delay in Degrees.\n");
   printf(" 3. fn is normalised center frequency of u\n");
   printf(" Outputs: 2\n 1. y is the delayed/shifted sequence.\n");
   printf(" 2. status 0 success, -1 failed.\n");
}


    