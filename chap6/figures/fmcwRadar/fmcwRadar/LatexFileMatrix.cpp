#include "LatexFileMatrix.h"
//#include "matrix.h"
#include "mex.h"   /* This one is required */
//  ..................................................................
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int rcA[2] = {8,4};
    double *inputData;
    char* latexFile, *title;
    double** data;
    int rcData[2];
    int r, c, i, p,kt,flag, maxLengthOfFileName=40;
    
    if ( (nlhs != 0) || (nrhs != 3) )
    {
        usageLatexFileMatrix(nlhs,nrhs);
        mexErrMsgTxt("!. INPUT Error\n");
        return;
    } 

    
    flag = mxIsChar(prhs[0]);
    if ( flag > 0 )
    {
        latexFile = (char *)malloc(maxLengthOfFileName * sizeof(char));
        latexFile = mxArrayToString(prhs[0]);
    }
    else   mexErrMsgTxt("!. RHS[0] must be a character string\n");

    flag = mxIsChar(prhs[1]);
    if (flag > 0)
    {
        title = (char*)malloc(maxLengthOfFileName * sizeof(char));
        title = mxArrayToString(prhs[1]);
    }
    else   mexErrMsgTxt("!. RHS[1] must be a character string\n");



    
    r = (int)(mxGetM(prhs[2])); c = (int)(mxGetN(prhs[2]));
    printf("!. size of input matrix %d by %d\n",r,c);
    inputData = mxGetPr(prhs[2]);
    rcData[0] = r; rcData[1] = c;
    data = myAlloc2(r, c);
    for (p = 0; p < r; p++) // rows
    {
        for (i = 0; i < c; i++)
        {
            kt = i * r + p;
            data[p][i] = inputData[kt];
            //printf("%3.4f ", data[p][i]);
        } //printf("\n");
    }//printf("\n");
    LatexFile(data, rcData, latexFile, title);

    return;
}

int LatexFile(double** A, int* rcA, char* filename, char* title)
{
    int er, k, i, r, c, sign, tableCols, kt;
    FILE* fp;
    r = rcA[0]; c = rcA[1];
    tableCols = c - 1;
    er = fopen_s(&fp, filename, "w"); if (er < 0) return er;
    fprintf(fp, "\\begin{center}\n");
    
    fprintf(fp, "\\begin{tabular}{ ");
    for (i = 0; i < c; i++) fprintf(fp, "|c"); fprintf(fp, "| }\n");
    fprintf(fp, "\\hline \\multicolumn{ %d }{ | c | } {%s} \\\\ \\hline\n", c, title);
    for (i = 0; i < tableCols; i++) fprintf(fp, " %d & ", i);
    fprintf(fp, "%d \\\\ \\hline\n", tableCols);
    for (k = 0; k < r; k++)
    {
        for (i = 0; i < tableCols; i++) fprintf(fp, " %3.3f & ", A[k][i]);
        fprintf(fp, "%3.3f \\\\ \\hline\n", A[k][c-1]);
    }

    fprintf(fp, "\\end{tabular}\n");

    fprintf(fp, "\\end{center}\n");

    fclose(fp);
    return 1;
}


void usageLatexFileMatrix(int nlhs, int nrhs)
{
    printf("  Creates a Latex File of a Matrix as a Table 4th May 2025\n");
    printf("  Usage Error Parameters Left Hand Side = %d(1) .. Right Hand Side = %d(3) \n", nlhs, nrhs);
    printf("  er = LatexFileMatrix(datafile,title,matrix\n");
    return;
}