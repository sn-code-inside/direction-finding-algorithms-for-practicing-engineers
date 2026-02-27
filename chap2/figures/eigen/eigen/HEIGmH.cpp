#include "mex.h"   /* This one is required */
#include "eigR.h"
void usage();
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *inputAr,*inputAi;
    double *EnPtr, *EnPti,*Lptr, *JkPtr;
//  ...............
    complex** H, ** E;
    double* Lh, * Jk;
    int r, c,JkL,JkLen;
    JkL = 200;
    complex **A;
    int rcA[2],i,p,kt;


    if ( (nlhs != 3) || (nrhs != 1) )
    {
       printf("  Usage Error Parameters Left Hand Side = %d(3) .. Right Hand Side = %d(1) \n",nlhs,nrhs);
       usage(); 
       return;
    }
    /* Check that  input is complex*/
    if( !mxIsComplex(prhs[0]) ) 
    {
        usage();
        mexErrMsgTxt("!. prhs[0] must be complex matrix\n");
    }
    rcA[0] = (int)(mxGetM(prhs[0])); rcA[1] = (int)(mxGetN(prhs[0]));
    inputAr = mxGetPr(prhs[0]); inputAi = mxGetPi(prhs[0]);
    r = rcA[0]; c = rcA[1];
    A = myAlloc2Complex(rcA[0], rcA[1]);
    printf(".....................................................\n");
    printf(" size of input matrix %d by %d\n",rcA[0],rcA[1]);
    printf(".....................................................\n");
//  ... transfer input complex to A matrix
    for (p = 0; p < rcA[0]; p++) // rows
    {
        for (i = 0; i < rcA[1]; i++)
        {
                kt = i*rcA[0]+p;
                A[p][i].r = inputAr[kt];
                A[p][i].i = inputAi[kt];
        }
    }
    H = myAlloc2Complex(c, c);
    E = myAlloc2Complex(c, c);
    //Lh = myAlloc(c); 
   
    //CeqABtrnsp(H, A,r, c, "H = A * (A transpose)");
    //printComplxMatrix(H, c,c);
    //eigenvecH(H, E, Lh, Jk, &JkL, c);
    Jk = myAlloc(JkL); JkLen = JkL;
    Lh = eigHermitian(A, rcA, E,Jk,&JkLen);
    myFree2Complex(A, r); myFree2Complex(H, c);
    plhs[0] = mxCreateDoubleMatrix(c, c, mxCOMPLEX);
    EnPtr = mxGetPr(plhs[0]); EnPti = mxGetPi(plhs[0]);
    for (p = 0; p < c; p++) // rows
    {
        for (i = 0; i < c; i++)
        {
                kt = i*c+p;
                EnPtr[kt]  = E[p][i].r; 
                EnPti[kt]  = E[p][i].i; 
        }
    }
    plhs[1] = mxCreateDoubleMatrix(1, c, mxREAL);
    Lptr = mxGetPr(plhs[1]); for (i = 0; i < c; i++) Lptr[i] = Lh[i];
    plhs[2] = mxCreateDoubleMatrix(1, JkL, mxREAL);
    JkPtr = mxGetPr(plhs[2]); for (i = 0; i < JkLen; i++) JkPtr[i] =Jk[i];
    return;
}


void usage()
{
    printf("[E, L, Jk] = HEIGmH(A)\n");
    printf("A is a square Hermitian matrix\n");
    printf("E is the matrix containing eigenvectors\n");
    printf("L contains the eigenvalues\n");
    printf("Jk performance function\n");
    printf("Uses House Holder Method\n");
    printf("Use the Command mex HEIGmH.c HEIGxH.c for getting HEIGmH \n");
    printf("Updated on 6th Jul 2024 only Usage part\n");
    printf("test the code by using TESTHEIG.m generates a Hermitian\n");
}

