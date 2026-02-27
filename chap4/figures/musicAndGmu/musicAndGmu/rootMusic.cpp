// rootMusic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "rootMusic.h"
#include "mex.h"   /* This one is required */
double** processRoots(double **, int *, double);
int* Low2High(int, double*);
double** rootPairs(double **, int*, int*,double);
double** myRoots(complex**, int, int,int*);
complex* polyRoots(complex*, int);
double** findCloseRoots(complex*,int, int *, int , int *,double);
double** CloseRootsOnUnitCircle(complex*,int, complex*,int,int,int*,double);
void LatexFile(double** , int*, double, char*,char*);
int* compact(double* , int, int*);
int** doaFromClusters(double** , int*,int*,double*);

double** myRoots(complex **En, int r, int c, int* rows)
{
    int i, k,rc,kt;
    complex* a, * b;
    complex* total;
    double pi = atan(1.0) * 4.0;
    double** B,theta;
    //printf("double** myRoots()\n");
    rc = r * c;
    a = myAllocComplex(c); total = myAllocComplex(rc);
    B = myAlloc2(rc, 3);
    kt = 0;
    for (i = 0; i < r; i++)
    {
        for (k = 0; k < c; k++) a[k] = En[i][k];
        b = polyRoots(a, c);
        for (k = 0; k < c - 1; k++)
        {
            total[kt] = b[k];
            B[kt][2] = i;
            kt = kt + 1;
        }
    }
    for (k = 0; k < kt; k++)
    {
        B[k][1] = sqrt(total[k].r * total[k].r + total[k].i * total[k].i);
        theta = atan2(total[k].i , total[k].r);
        B[k][0] = theta * 180.0 / pi;
    }
    rows[0] = kt;
    return B;
}

complex* polyRoots(complex* a, int c)
{
    int k;
    double* inputPtr, * inputPti;
    double* br, * bi;
    complex* b;
    mxArray* prhs[1];
    mxArray* plhs[1];
    b = myAllocComplex(c - 1);
    prhs[0] = mxCreateDoubleMatrix(1, c, mxCOMPLEX);
    plhs[0] = mxCreateDoubleMatrix(c - 1, 1, mxCOMPLEX);
    inputPtr = mxGetPr(prhs[0]);   inputPti = mxGetPi(prhs[0]);
    //printf("complex* polyRoots()\n");
    for (k = 0; k < c; k++) { inputPtr[k] = a[k].r; inputPti[k] = a[k].i; }
    mexCallMATLAB(1, plhs, 1, prhs, "roots");

    br = mxGetPr(plhs[0]);     bi = mxGetPi(plhs[0]);
    for (k = 0; k < c - 1; k++)
    {
        b[k].r = br[k]; b[k].i = bi[k];
    }
    mxDestroyArray(prhs[0]);
    mxDestroyArray(plhs[0]);
    return b;
}

double** CloseRootsOnUnitCircle
(
   complex *localPole,
   int pmax,
   complex *poleAngR,
   int kmax,
   int eold,
   int* rows,
   double deltheta
)
{
    int i,p,m,kt,k,pold;
    double dist;
    double** rootsOnUnit;
    kt = 0;
    for(p=0; p<pmax; p++ ) 
       {
               pold = 0;
               for(m=eold+1; m<kmax; m++)
                {    
                    dist = fabs(localPole[p].r - poleAngR[m].r);
                    if (dist < deltheta )
                    {
                        k = eold - pmax + 1 + p;
                        if (pold == 0) pold = -1;
                        kt = kt + 1;
                    }
                }
       }  
    rows[0] = kt;
    rootsOnUnit = myAlloc2(rows[0], 2);
    //printf(" pass 2 angular close roots %d\n", rows[0]);
    i = 0;
    for(p=0; p<pmax; p++ ) 
    {
               pold = 0;
               for(m=eold+1; m<kmax; m++)
                {    
                    dist = fabs(localPole[p].r - poleAngR[m].r);
                    if (dist < 2.0 )
                    {
                        if (pold == 0)
                        {
                            printf(" [%d] %3.4f = (%3.4f %3.4f)\n", pold, dist, poleAngR[k].r, poleAngR[m].r);
                            rootsOnUnit[i][0] = localPole[p].r;
                            rootsOnUnit[i][1] = localPole[p].i;
                            pold = -1;
                        }
                        else {
                            printf(" [%d] %3.4f = (%3.4f %3.4f)\n", pold, dist, poleAngR[k].r, poleAngR[m].r);
                            rootsOnUnit[i][0] = poleAngR[m].r;
                            rootsOnUnit[i][1] = poleAngR[m].i;
                        }
                        //printf("[%d] %3.4f %3.4f\n", i,rootsOnUnit[i][0], rootsOnUnit[i][1]);
                        i = i + 1;
                    }
                }
    } 
    rows[0] = i;
   return rootsOnUnit;
}

double** findCloseRoots(complex* poleAngR,int kmax, int *block, int len, int *rows, double deltheta)
{
   int i,k,j,p,s,e,m,kt,r;
   int sold,eold,pmax,rowsPerBlock=0;
   double** rootsPerBlock,**roots;
   complex *localPole;
   localPole = myAllocComplex(kmax);
//   printf("double** findCloseRoots()\n");
//  pass 1 since the combinations are too many we don't know how many will come
   s = 0; rows[0] = 0; r = 0;
   for(i=0; i<len; i++)
   {
        e = block[i];
        j = 0;
        for (k=s; k<e+1; k++)
        {
          localPole[j] = poleAngR[k]; j=j+1;
        } sold = s; eold = e; pmax = j; s = e+1;
       rowsPerBlock = 0;
       rootsPerBlock = CloseRootsOnUnitCircle(localPole,pmax,poleAngR,kmax,eold,&rowsPerBlock,deltheta);
       for(kt=0; kt<rowsPerBlock; kt++) r = r + 1;
   }
   rows[0] = r;
   if (r > kmax) printf(" WARNING:NUMBER of ROWS needed found in pass 1 %d[%d]\n", r, kmax);

// end pass 1 ..............

//  ......................................................
//  .......................................................

//  pass 2 since the combinations are too many we don't know how many will come
   roots = myAlloc2(rows[0], 2);
   printf(" blocks "); for (i = 0; i < len; i++) printf("%d ", block[i]); printf("\n");
   s = 0;  r = 0;
   for (i = 0; i < len; i++)
   {
       e = block[i];
       j = 0;
       for (k = s; k < e + 1; k++)
       {
           localPole[j] = poleAngR[k]; j = j + 1;
       } sold = s; eold = e; pmax = j; s = e + 1;
       printf(" eig vector number [%d] ", i);
       for (p = 0; p < pmax; p++) printf("%3.4f ", localPole[p].r);
       printf("\n");
       rowsPerBlock = 0;
       rootsPerBlock = CloseRootsOnUnitCircle(localPole, pmax, poleAngR, kmax, eold, &rowsPerBlock,deltheta);
       printf("[%d] rows per block %d\n", i,rowsPerBlock);
       for (kt = 0; kt < rowsPerBlock; kt++)
       {
           roots[r][0] = rootsPerBlock[kt][0];
           roots[r][1] = rootsPerBlock[kt][1];
           r = r + 1;
       }
   }
   rows[0] = r;
   // end pass 2 ..............
   free(localPole);
   return roots;
}



double** rootPairs(double **B, int* rcInB, int* rcInC,double deltheta)
{
    int i,k,*indx,colInC,rowsInC,flag, newRowsInC;
    int lengthOfBlock,kmax,diff;
    int *eigIndx,*blocks,*unknown,*newAnglesIndx;
    complex *poleAngR;
    double** C,*angles;
    kmax = rcInB[0];
    //printf(" double** rootPairs()\n");
    eigIndx = myAllocI(kmax);
    poleAngR = myAllocComplex(kmax);
    
    unknown = myAllocI(kmax);
    for (k=0; k<kmax; k++)
    {
        poleAngR[k].r = B[k][0];
        poleAngR[k].i = B[k][1];
        eigIndx[k] = (int)(B[k][2]);
    }
    //printf(" eigIndx "); for (k = 0; k < kmax; k++) printf("%d ", eigIndx[k]); printf("\n");
    i = 0;
    for (k=0; k<kmax-1; k++)
    {
        diff = eigIndx[k] - eigIndx[k + 1];
        //printf(" [%d %d] %d\n", eigIndx[k], eigIndx[k + 1],diff);
        if ( diff  != 0 )
        {
            unknown[i] = k;   i = i + 1;
        }
    } unknown[i] = kmax-1;
    lengthOfBlock = i+1;
    blocks = myAllocI(lengthOfBlock);
//    printf(" blocks ");
    for (k = 0; k < lengthOfBlock; k++)
    {
        blocks[k] = unknown[k];
//        printf("%d ", blocks[k]);
    } //printf("\n");

    C = findCloseRoots(poleAngR,kmax,blocks,lengthOfBlock,&rowsInC,deltheta);
    angles = myAlloc(rowsInC); indx = myAllocI(rowsInC);
    for (k = 0; k < rowsInC; k++) angles[k] = C[k][0];
    indx = Low2High(rowsInC, angles);
    for (k = 0; k < rowsInC; k++) C[k][0] = angles[k];
    for (k = 0; k < rowsInC; k++) angles[k] = C[indx[k]][1];
    for (k = 0; k < rowsInC; k++) C[k][1] = angles[k];
    //for (k = 0; k < rowsInC; k++) printf("[%d] %3.4f %3.4f\n", k, C[k][0], C[k][1]);


    for (k = 0; k < rowsInC; k++) angles[k] = C[k][0];
    newAnglesIndx = compact(angles, rowsInC, &newRowsInC);
    for (k = 0; k < newRowsInC; k++) C[k][0] = angles[newAnglesIndx[k]];

    for (k = 0; k < rowsInC; k++) angles[k] = C[k][1];
    for (k = 0; k < newRowsInC; k++) C[k][1] = angles[newAnglesIndx[k]];
    for (k = 0; k < newRowsInC; k++) printf("[%d] %3.4f %3.4f\n", k, C[k][0], C[k][1]);

    colInC = 2;
    rcInC[0] = newRowsInC;  rcInC[1] = colInC;
    free(unknown); free(eigIndx); free(poleAngR); free(angles);
    return C;
}

int** doaFromClusters(double** A, int* rcInA, int *lenParts, double *phi)
{
    int k, i, j,p,r, c,s,e;
    double* angles,dist,sum;
    int* indx,**parts;
    double pi = 4.0 * atan(1.0);
    r = rcInA[0]; c = rcInA[1];
    indx = myAllocI(r);
    angles = myAlloc(r);
    for (k = 0; k < r; k++)  angles[k] = A[k][0];

    i = 1; j = 0; p = 0;
    for (k = 0; k < r; k++)
    {
        dist = fabs(angles[p] - angles[i]);
        if (dist > 3.5)
        {
            indx[j] = p;
            printf("[%d] partition %d\n", j, p);
            j = j + 1;
        }
        p = p + 1;  i = i + 1;
        if (p > r) break;
    } indx[j] = r; lenParts[0] = j;
    parts = myAlloc2I(j, 2);
    s = 0;
    for (k = 0; k < j; k++)
    {
        e = indx[k];
        parts[k][0] = s; parts[k][1] = e;
        printf("start %d end %d\n", s, e);
        phi[k] = 0.0;
        for (i = s; i < e + 1; i++)
            phi[k] = phi[k] + angles[i]; 

        phi[k] = phi[k] / (double)(e - s + 1);
        phi[k] = (180.0 / pi) * asin(phi[k] / 180.0);
        printf("[%d] mean %3.4f \n", k, phi[k]);
        s = e + 1;
    }
    free(angles); free(indx);
    return parts;
}

int* compact(double* angles, int rowsInC, int* newRowsInC)
{
    double dist;
    int* newAnglesIndx;
    int k,i,j,p;
    //printf(" int* compact()\n");
    newAnglesIndx = myAllocI(rowsInC);
    i = 1; j = 0; p = 0;
    newAnglesIndx[j] = p;
    for (k = 0; k < rowsInC; k++)
    {
        dist = fabs(angles[p] - angles[i]);
        if (dist > 0.001)
        { 
            newAnglesIndx[j] = p;
            j = j + 1;
        }
        p = p + 1;  i = i + 1;
        if (p > rowsInC) break;
    }
    newRowsInC[0] = j;
    //for (k = 0; k < newRowsInC[0]; k++)
    //    printf("newAngles [%d] %3.4f\n", k, angles[newAnglesIndx[k]]);
    return newAnglesIndx;
}

double** processRoots(double **A, int *rcInB, double close2UnitCircle)
{
    int k,i,kt,kmax,colsInB;
    double r,delr,**B;
    int *indx;
    colsInB = 3;  kmax = rcInB[0]; rcInB[1] = colsInB;
    indx = myAllocI(kmax);
//    printf(" double** processRoots()\n");
//  pass 1    
    i = 0;
    for (k=0; k<kmax; k++)
    {
        r = A[k][1]; delr = 1.0-r;
        if (fabs(delr) < close2UnitCircle )
        { indx[i] = k; i = i+1; }
    }
//  pass 2
    B = myAlloc2(i,colsInB); // eigen vector number is included
    for (k=0; k<i; k++)
    {
        kt = indx[k];
        B[k][0] = A[kt][0]; B[k][1] = A[kt][1];
        B[k][2] = A[kt][2];
    }
    rcInB[0] = i;
    //km[0] = i;
    free(indx);
    return B;
}

void LatexFile(double** A, int* rcA, double parameter, char * filename, char * title)
{
    int er, k, i,r,c,sign,tableCols,kt;
    FILE* fp;
    tableCols = 6;
    r = rcA[0]; c = rcA[1];
    er = fopen_s(&fp, filename, "w");
    fprintf(fp, "\\begin{center}\n");

    for (k = 0; k < r; k++)
    {
        if (k == 0) 
        {
            fprintf(fp, "\\begin{tabular}{ ");
            for (i = 0; i < tableCols; i++) fprintf(fp, "|l"); fprintf(fp, "| }\n");
            if (parameter > 0)
            fprintf(fp, "\\hline \\multicolumn{ %d }{ | c | } {%s(%2.1f) %d} \\\\ \\hline\n",tableCols,title,parameter,r);
            else fprintf(fp, "\\hline \\multicolumn{ %d }{ | c | } {%s %d} \\\\ \\hline\n", tableCols, title,r);
        }

        sign =(int)(A[k][0] / fabs(A[k][0]));
        if (sign > 0)
        fprintf(fp, "$%3.2fe^{(j%3.2f)^",A[k][1],A[k][0]);
        else fprintf(fp, "$%3.2fe^{(-j%3.2f)^", A[k][1], fabs(A[k][0]));

        if ((k + 1) % tableCols == 0) { fprintf(fp, "\\circ}$ \\\\ \\hline \n"); kt = 0; }
        else { fprintf(fp, "\\circ}$ & "); kt = kt + 1; }
    }

    if (kt != 0)
    {
        for (k = 0; k < tableCols - kt-1; k++) fprintf(fp, "&");
        fprintf(fp, "\\\\ \\hline \n");
    }
    fprintf(fp, "\n \\end{tabular}\n");
    fprintf(fp, "\\end{center}\n");

    fclose(fp);
    return;
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    double* inputData,*inputEr,*inputEi,*inputDelr,*inputDelth;
    double** thetaNr,**B,**C,**D;
    double* outPtrD,*outPtrC,*outPtrB,*outPtrParts,*outPtrDoa;
    double close2UnitCircle=0.2, deltheta = 2.0;
    double doa[20];
    int p,r,c,i,k,kt,numOfPoles,rEn,cEn, numOfRoots;
    int partsLen,**parts;
    double pi = 4.0 * atan(1.0);

    int rcInD[2],rcInC[2],rcInB[2],rcInParts[2];
    complex** En;

    if ((nlhs != 5) || (nrhs != 3))
    {
        printf("!. Updated on 25th Feb 2025 9:30pm total update Princeton NJ\n");
        printf("!. Usage Error Parameters Left Hand Side = %d(3) .. Right Hand Side = %d(3) \n", nlhs, nrhs);
	    printf("1. [b,c,d,p,doa]=rootMusic(En,delr,deltheta)\n");
	    printf("2. En is noise Eigen Vectors of Covariance Matrix\n");
        printf("3. delr is distance away from unit circle say 0.2\n");
        printf("4. deltheta in degrees say 2\n");
        printf("5. b has 2 columns angle and radial position\n");
        printf("6. c has 3 columns angle and radial position and indx\n");
        printf("7. d has 2 columns angle and radial position all roots\n");
        printf("8. p has 2 columns start and end of root clusters\n");
        printf("9. doa root MUSIC output\n");
        return;
    }

    rEn = (int)(mxGetM(prhs[0])); cEn = (int)(mxGetN(prhs[0]));
    inputEr = mxGetPr(prhs[0]); inputEi = mxGetPi(prhs[0]);
    En = myAlloc2Complex(rEn, cEn);
    for (p = 0; p < rEn; p++) // rows
    {
        for (i = 0; i < cEn; i++)
        {
            kt = i * rEn + p;
            En[p][i].r = inputEr[kt];
            En[p][i].i = inputEi[kt];
        }
    }
    r = (int)(mxGetM(prhs[1])); c = (int)(mxGetN(prhs[1]));
    if (r != c) {mexErrMsgTxt("!. prhs[1] must be a scalar\n");}
    else {if (r != 1) {mexErrMsgTxt("!. prhs[1] must be a scalar\n");}}
    inputDelr = mxGetPr(prhs[1]); close2UnitCircle = inputDelr[0];
    printf(" Closeness to Unit Circle %3.4f\n",close2UnitCircle);

    r = (int)(mxGetM(prhs[2])); c = (int)(mxGetN(prhs[2]));
    if (r != c) { mexErrMsgTxt("!. prhs[1] must be a scalar\n"); }
    else { if (r != 1) { mexErrMsgTxt("!. prhs[2] must be a scalar\n"); } }
    inputDelth = mxGetPr(prhs[2]); deltheta = inputDelth[0];
    printf(" Angular Closeness in Degrees %3.4f\n", deltheta);


    D = myRoots(En, rEn, cEn, &numOfPoles); // complex roots in polar form
    rcInD[0] = numOfPoles; rcInD[1] = 2;
    LatexFile(D, rcInD, -1.0,"totalroots.tex","Total Roots");
    printf("1. maximum number of roots %d\n", numOfPoles);

    rcInB[0] = numOfPoles;
    B = processRoots(D,rcInB,close2UnitCircle);
    LatexFile(B, rcInB, close2UnitCircle, "UnitCircle.tex","Roots Close to Unit Circle");

    C = rootPairs(B, rcInB, rcInC,deltheta);
    LatexFile(C, rcInC, deltheta, "rootclusters.tex","Root Clusters");

    parts = doaFromClusters(C, rcInC, &partsLen,doa);
    rcInParts[0] = partsLen; rcInParts[1] = 2;
    for (k = 0; k < partsLen; k++)
    {
        printf("%d %d %3.4f\n", parts[k][0], parts[k][1],doa[k]); //(180.0/pi)*asin(phi[k]/180.0)
    }

    printf("row %d cols %d of output matrix C\n",rcInC[0],rcInC[1]);
    plhs[0] = mxCreateDoubleMatrix(rcInC[0], rcInC[1], mxREAL);
    outPtrC = mxGetPr(plhs[0]);

    printf("row %d cols %d of output matrix B\n", rcInB[0], rcInB[1]);
    plhs[1] = mxCreateDoubleMatrix(rcInB[0], rcInB[1], mxREAL);
    outPtrB = mxGetPr(plhs[1]);

    printf("row %d cols %d of output matrix D\n", rcInD[0], rcInD[1]);
    plhs[2] = mxCreateDoubleMatrix(rcInD[0], rcInD[1], mxREAL);
    outPtrD = mxGetPr(plhs[2]);

    printf("row %d cols %d of output matrix parts\n", rcInParts[0], rcInParts[1]);
    plhs[3] = mxCreateDoubleMatrix(rcInParts[0], rcInParts[1], mxREAL);
    outPtrParts = mxGetPr(plhs[3]);

    printf("length of DOA %d \n", rcInParts[0]);
    plhs[4] = mxCreateDoubleMatrix(rcInParts[0], 1, mxREAL);
    outPtrDoa = mxGetPr(plhs[4]);
    for (p = 0; p < rcInParts[0]; p++) outPtrDoa[p] = doa[p];


//  ...............Output two Parameters B and C and D........................ 
//
    for (p = 0; p < rcInC[0]; p++) // rows
    {
          for (i = 0; i < rcInC[1]; i++)
          {
                 outPtrC[i* rcInC[0] +p]  = C[p][i];
          }
    }

    for (p = 0; p < rcInB[0]; p++) // rows
    {
        for (i = 0; i < rcInB[1]; i++)
        {
            outPtrB[i * rcInB[0] + p] = B[p][i];
        }
    }

    for (p = 0; p < rcInD[0]; p++) // rows
    {
        for (i = 0; i < rcInD[1]; i++)
        {
            outPtrD[i * rcInD[0] + p] = D[p][i];
        }
    }

    for (p = 0; p < rcInParts[0]; p++) // rows
    {
        for (i = 0; i < rcInParts[1]; i++)
        {
            outPtrParts[i * rcInParts[0] + p] = parts[p][i];
        }
    }


    return;
}
