/*
 Program for finding the Eigenvalues and Eigenvectors
 of a given Hermitian matrix using 
 an Householder and QR transformation for Real-Symmetric matrices 
 */
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
#include "mex.h"
#include "math.h"

/*Ar, M , ER, L */
int eigenvec
(
    double **Ar, /* input */
    int M,       /* Size of the input matrix  */
    double **ER, /* output1 :Eigen vectors of input matrix */
    double *L   /* output2: Eigen values of input matrix */
)

{
    int i,k,val,m;
    double **a,**P;
    
    int flag = 1;
    
    /*input matrix*/
    a = (double **)mxCalloc(M, sizeof(double *)); 
    for (m = 0; m < M; m++) a[m] = (double *)mxCalloc(M, sizeof(double));
    
    /* P - Transformation matrix  */
    P = (double **)mxCalloc(M, sizeof(double *)); 
    for (m = 0; m < M; m++) P[m] = (double *)mxCalloc(M, sizeof(double));

    /* (Ar, M , Jk ,ER, L); */
    flag = hholdc(Ar,P,a,M);
    
    qrstc(a, M, P, ER, L); /* a = tridiagonal , M - order , P - transformation matrix , ER : eig vector , L = eig value */ 
      
    
    for (i=0;i<M;i++) 
       {
           mxFree(a[i]);
           mxFree(P[i]);
       }
       mxFree(a);
       mxFree(P);
        
 }

/*Householder function : To reduce original matrix to tridiagonal form...*/ 

int hholdc
(
   double  **A, /* input real symmetric Matrix  */
   double  **P, /* Output Transformation Matrix */
   double  **a,  /* Output Tridiagonal  Matrix */
   int nA       /* Input size of A Matrix */
) 

{
    
    
        int i,j,m,k;
        double *c,*b,*u,*w;
        double **Q,**mul,**res,**res1;
        int eFlag = 1;
        double sum = 0,q,v;
        int ir,jc,kr;
        
        c = (double *)mxCalloc(nA, sizeof(double));
        b = (double *)mxCalloc(nA, sizeof(double));
        u = (double *)mxCalloc(nA, sizeof(double));
        w = (double *)mxCalloc(nA, sizeof(double));
        
    Q = (double **)mxCalloc(nA, sizeof(double *)); 
    for (m = 0; m < nA; m++) Q[m] = (double *)mxCalloc(nA, sizeof(double));
    mul = (double **)mxCalloc(nA, sizeof(double *)); 
    for (m = 0; m < nA; m++) mul[m] = (double *)mxCalloc(nA, sizeof(double));
    res = (double **)mxCalloc(nA, sizeof(double *)); 
    for (m = 0; m < nA; m++) res[m] = (double *)mxCalloc(nA, sizeof(double));
    res1 = (double **)mxCalloc(nA, sizeof(double *)); 
    for (m = 0; m < nA; m++) res1[m] = (double *)mxCalloc(nA, sizeof(double));

        eFlag = 1;
        if ( nA <= 2 ) {eFlag = -1; return eFlag; }
        
      
        
        /* P = diag(diag(ones(n))); */
        for (i=0; i < nA; i++)                /*making identity matrix*/
        {
              for (j=0; j < nA; j++)    { a[i][j] = A[i][j]; P[i][j]=0; if( i==j )  P[i][j]=1; }
        }      
    
                for (m=0; m<nA-2; m++) 
        {
        
                       /* c =zeros(nA,1);  %% column-vector of zeros  */

                      for (i=0; i<nA ;i++) { c[i] = 0; }
                       
                      /* set up c
                      / c(i+1:n)=a(i+1:n,i); %removing first element of first row and first column */
                      i=m;  for (j=i+1; j<nA ;j++) {c[j] = a[j][m]; }
                      /* %q=norm(c); */
                      sum = 0;  for (j =i+1; j< nA ; j++) sum = sum+(c[j]*c[j]);
         
                      q = sqrt(sum);   
         
                     /* %b=zeros(n,1); */
                      for (i=0;i<nA;i++)  b[i] = 0; 
                    
                      i=m;  if ( a[i+1][i] >=0 )  b[i+1] = -q; else b[i+1]=q;
                    
                     /* %w=(c-b)/norm(c-b);  
                     // u = c-b ; norm(c-b) = v So, w = u/v */
                     /* updated after sending to prof */
        
                     for (i = 0; i<nA ;i++) u[i] = c[i] - b[i]; 
        
                     sum=0.0;  for (i=0; i<nA ; i++) sum = sum+(u[i]*u[i]); 
       
                     v = sqrt(sum);
                     /* mexPrintf("v = %f sum = %f\n",v,sum);  */
        
                    /* w = u/v ; changed after sending to prof... */
                      
                     for (i = 0; i <nA ; i++) w[i] = u[i]/v ; 
                    
                    /* mexPrintf("w =");
                    // for (i = 0; i <nA ; i++) mexPrintf("%f ",w[i]); mexPrintf("\n"); */
                            
                    /* Q=eye(n)-2*w*w'; */ 
                     for (k=0; k<nA ; k++) 
                     { 
                         for (j=0; j<nA; j++) 
                         {
                             if (k==j) Q[k][j] = 1-2*w[j]*w[k]; else Q[k][j] = -2*w[j]*w[k]; 
                         }
                     }
                    
                    /* mul = P*Q */
                    for (ir=0;ir < nA;ir++)
                    {
                        for (jc=0;jc < nA;jc++)
                        {
                            mul[ir][jc]=0;
                            for (kr=0; kr<nA; kr++) { mul[ir][jc]=mul[ir][jc] + P[ir][kr]*Q[kr][jc]; } 
                        }  
                    }
           
                    /* P = mul */  
                    for (ir = 0 ; ir <nA ; ir++) 
                    {
                        for (jc = 0 ; jc < nA ; jc++) P[ir][jc] = mul[ir][jc]; 
                    }    
        
      
      
                    /*   %a=Q*a*Q;  */
  
                    /* res = Q*a */
                    for (ir=0;ir < nA;ir++)
                    {
                        for (jc=0;jc < nA; jc++)
                        {
                            res[ir][jc]=0;
                            for (kr=0 ; kr < nA ; kr++) { res[ir][jc]=res[ir][jc] + Q[ir][kr]*a[kr][jc]; }
                        }
      
                    }
                            /* res1 = res*Q */
                    for (ir=0; ir< nA ;ir++)
                    {
                        for (jc=0; jc< nA ;jc++)
                        {
                            res1[ir][jc]=0;   /*changed third time final change */
                            for (kr=0 ; kr < nA ; kr++) { res1[ir][jc]=res1[ir][jc] + res[ir][kr]*Q[kr][jc]; }
                        }
                    }
  
                    /*a = res1 */
        
                    for (ir = 0 ; ir <nA ; ir++) 
                        {
                            for (jc = 0 ; jc < nA ; jc++)  a[ir][jc] = res1[ir][jc];
                        }    
  
                    /* changed second time after sending to prof */ 
     

                    for (k = m+2; k < nA ; k++) { a[k][m] = 0 ; }
          
		/*** resulting a is the tridiagonal matrix and P is the householder transformation matrix ****/
                    
        }            
                
       return eFlag; 
       
       for (i=0;i<nA;i++) 
       {
           mxFree(Q[i]);
           mxFree(mul[i]);
           mxFree(res[i]);
           mxFree(res1[i]);
       }
       mxFree(Q);
       mxFree(mul);
       mxFree(res);
       mxFree(res1);
      
       mxFree(c);
       mxFree(b);
       mxFree(u);
       mxFree(w);
     }
  
  
  int qrstc 
( 
    double **a, /* Tridiagonal matrix (output of hholdc function */
    int nA ,    /* order of input matrix */
    double **P, /* Transformation matrix */
    double **v, /* Eigenvector */
    double *lambda /* Eigenvalue */
)

{

/* 
 * 
 * Input  :
 * a = Tridiagonal matrix (result of hholdc function ) from which d and Of are extracted 
 *
 * d =  vector containing elements along the main diagonal of the symmetric tridiagonal matrix;
 
  Of =  vector containing elements along the off diagonal of the symmetric 
        tridiagonal matrix 
 
 *nA = size of input matrix 
  TOL = convergence tolerance
  Nmax =   maximum number of iterations
  P  = householder transformation
           matrix for the original real symmetric

 output:
 lambda = vector containing the eigenvalues of the symmetric
          tridiagonal matrix 
 v      = matrix containing the eigenvectors of the symmetric
          tridiagonal matrix determined
 *
 *
 *
 */
    
 int i, j, ir,jc, kr, irv, irn, togo,its, m;
 
 double *d,*Of, *vnew , *result1 , *result2, *col1 , *result3, *result4, *addres , *c ,*s ,*Oftemp;   
 
 double TOL = 1.0E-9, shift, trace, det , oldb, disc, r , temp1, temp2 , mu1, mu2 , sadd;
 double sc,ss,ss1,sc1;
 int Nmax = 10000;
 
         d = (double *)mxCalloc(nA, sizeof(double));
         Of = (double *)mxCalloc(nA, sizeof(double));
         vnew = (double *)mxCalloc(nA, sizeof(double));
         result1 = (double *)mxCalloc(nA, sizeof(double));
         result2 = (double *)mxCalloc(nA, sizeof(double));
         col1 = (double *)mxCalloc(nA, sizeof(double));
         result3 = (double *)mxCalloc(nA, sizeof(double));
         result4 = (double *)mxCalloc(nA, sizeof(double));
         addres = (double *)mxCalloc(nA, sizeof(double));
         c = (double *)mxCalloc(nA, sizeof(double));
         s = (double *)mxCalloc(nA, sizeof(double));
         Oftemp = (double *)mxCalloc(nA, sizeof(double));
    
        
   /* for (m = 0; m < nA; m++) v[m] = (double *)mxCalloc(nA, sizeof(double)); */   
  
         
            /*  d = diag(T)   %% diagonal elements of tridiagonal matrix   a */
            for (ir =0 ; ir <nA ; ir++)
                {
                    for (jc = 0; jc < nA ; jc++)
                    {
                        if ( ir ==jc ) { d[ir] = a[ir][jc]; }
                    }
                }
    
           /**** disp('off diagnol elements of tridiagnol form')  Of = diag(T,1); */

            for (ir =0 ; ir < nA-1 ; ir++)
            {
                for (jc =0 ; jc < nA-1 ; jc++)
                { 
                    if ( ir==jc ) { Of[ir] = a[ir+1][jc]; }
                }
            }
  
                     
           /* number of diagonal elements is nA   // to repeat the first element twice //  */ 
             
           /*Oftemp = Of;  Of(2:nA) = Of(1:nA-1) */
  
             for (i=0; i<nA; i++) { Oftemp[i] = Of[i]; }
             
             /*      // to repeat the first element twice //   */ 
             for (i=1 ; i <nA ; i++) { Of[i]= Oftemp[i-1]; }
           
                     
             /* mexPrintf("Of =");
                for (i = 0; i <nA ; i++) mexPrintf("%f ",Of[i]); mexPrintf("\n");  */

            /*  v = P; */
  
            for (ir = 0 ; ir <nA ; ir++) 
            {
                for (jc = 0 ; jc < nA ; jc++) 
                {
                    v[ir][jc] = P[ir][jc];
                }    
            }
          
             /* print v  for check !!
             mexPrintf("v = ");
            for (i = 0; i <nA ; i++)
            {
                 for (j = 0; j <nA ; j++)
                 {
                     mexPrintf("%f" , v[j][i]); 
                     mexPrintf("\n");
                     
                 }
            } */
             
            
            /*  %c = zeros ( 1, n )  % Row of zeros  */
            for (jc =0 ; jc<nA ; jc++) {  c[jc] = 0; }
  
            /*    % s = zeros ( 1, n ) */
  
            for (jc = 0; jc<nA; jc++)  {  s[jc] = 0; }
            
            /* mexPrintf("s =");
            for (i = 0; i <nA ; i++)  mexPrintf("%f ",s[i]); mexPrintf("\n"); */
  
            shift = 0.0;
            togo = nA-1;
            
                       
   /* for (its = 0 ; its <  Nmax ; its++) */
      for (its = 0; its < Nmax ; its++)      
    {

            if ( togo == 0 ) 
            { 
               /* mexPrintf("here togo is 0, to find first eigvalue ");*/
           
                  lambda[0] = d[0] + shift;    
                 
                  /* this is the final eigen values (lambda) and vectors (v) that is to be returned //
                  mexPrintf("The final eigen values are ");
            
                  for (m=0; m<nA ; m++) mexPrintf("%f \t" , lambda[m]); mexPrintf("\n");      
                  
                  mexPrintf("The eigen vecs are ");
            
                  for (i = 0; i <nA ; i++)
                    {
                        for (j = 0; j <nA ; j++)
                        {
                        mexPrintf("%f \n" , v[j][i]); 
                        }
                     }   
                  */
                  return;
             }        
                       
            /* mexPrintf("its loop");
               mexPrintf("%d",its);
               mexPrintf("\n"); */
                        
            trace = d[togo-1] + d[togo];
            /*
            mexPrintf("trace is: ");
            mexPrintf("%f" , trace); 
            */
            
            det   = d[togo-1]*d[togo] - Of[togo]*Of[togo];
            
            /*mexPrintf(" det is "); mexPrintf("\n");
            mexPrintf("%f", det); */
            
            disc  = sqrt ( trace*trace - 4*det );
            
            /*mexPrintf("disc is: ");
            mexPrintf("%f" , disc);   */
            
            mu1 =  ( trace + disc ) / 2;
            
            mu2 = ( trace - disc ) / 2;
            /*
            mexPrintf("mu1 is: ");
            mexPrintf("%f" , mu1);
            
            */
            
            /* if (fabs(mu1 - d[togo-1]) < fabs(mu2 - d[togo-1]) ) */
            if(fabs(mu1 - d[togo]) < fabs(mu2 - d[togo]))
            {
                sadd = mu1; 
                /*mexPrintf("\n sadd is .... :");
                mexPrintf("%f", sadd);*/
            }
            else
            {
                sadd = mu2;
            }
            
            /*mexPrintf("sadd is .... :");
            mexPrintf("%f", sadd);         */
            
            shift = shift + sadd;
            
            /*mexPrintf("shift is ... ");
            mexPrintf("%f", shift);
            mexPrintf("\n");*/
            
            for (i = 0; i<togo+1 ;i++) { d[i] = d[i] - sadd; }
            
            /* mexPrintf("d =");
            for (i = 0; i <nA ; i++)  mexPrintf("%f ",d[i]); mexPrintf("\n"); */
            
            oldb = Of[1];
            /* mexPrintf("oldb is %f", oldb); */
        
                /* 2 to 5(matlab) i.e 1 to 4*/
             for (i = 1; i< togo+1 ;i++)
             {   
                /*mexPrintf("\n");
                mexPrintf("loop i is %d \n" , i); */
                j = i-1;
                r = sqrt ( d[j]*d[j] + oldb*oldb );
                /* mexPrintf("r is ");
                mexPrintf("%f", r); */
                
                c[i] = d[j] / r;
                
                /* for checking.. */
                /*mexPrintf("\n");
                mexPrintf("c is ... ="); */
                /* for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",c[ir]); mexPrintf("\n"); */
                
               /* s[0] = sadd; */
                s[i] = oldb / r;
                 /* for checking.. 
                mexPrintf("\n");
                mexPrintf("s =");
                for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",s[ir]); mexPrintf("\n"); */
                
                d[j] = r;
                /* for checking 
                mexPrintf("d =");
                for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",d[ir]); mexPrintf("\n");  */
        
                temp1 = c[i]*Of[i] + s[i]*d[i];
                
                /*for checking...  mexPrintf("temp1 is %f",temp1);  */
                        
                temp2 = -s[i]*Of[i] + c[i]*d[i];
                /*for checking...  mexPrintf("temp2 is %f",temp2);  */
                
                Of[i] = temp1;
                
                d[i] = temp2;
                
                if ( i != togo )
                {
                    oldb = Of[i+1];
                    /* mexPrintf("oldb is %f",oldb); */
                    Of[i+1] = c[i]*Of[i+1];
                    /*checking... 
                    mexPrintf("Of =");
                    for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",Of[ir]); mexPrintf("\n");  */
                }
            }  /* i = 1 to togo ending */
  
             /*d[1] = c[2]*d[1] + s[2]*Of[2]; */
             d[0] = c[1]*d[0]+s[1]*Of[1];
            
             
             /* Of[2] = s[2]*d[2];*/
            
             Of[1]= s[1]*d[1];
             /* check
             mexPrintf("\n");
             mexPrintf("Of[1] is ");
             mexPrintf("%f" , Of[1]);
             */     
             /*  1 to 3  togo = 4*/
             for (i = 1; i< togo ; i++)
                {
                    d[i] = s[i+1]*Of[i+1] + c[i]*c[i+1]*d[i];
                    /*
                    mexPrintf("check d[i] is ");
                    mexPrintf("%f", d[i]); 
                    */
                    Of[i+1] = s[i+1]*d[i+1];
                    
                }
            
            d[togo] = c[togo]*d[togo];
            /*
            mexPrintf("d(togo-1) is ...................... ");
            mexPrintf("%f", d[togo-1]); */
  
            for (i = 1 ; i< togo+1 ; i++)
                {
                     /* %col1 = v(:,i-1) * c(i) + v(:,i) * s(i) */
                    
                    for (irv = 0; irv< nA ;irv++) {  /* j = i-1; */ vnew[irv] = v[irv][i-1]; }
                            
                    sc = c[i];
                    
                    /*mexPrintf("sc is");
                    mexPrintf("%f", sc); */
                    
                    for (ir=0; ir< nA ; ir++) 
                    {
                         result1[ir]=0;
                         for (kr=0; kr < 1 ; kr++) { result1[ir]=result1[ir] + vnew[ir]*sc; }
                            
                    }
                    
                    /*mexPrintf("result1 ========");
                    for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",result1[ir]); mexPrintf("\n"); */
                     
                    for (irv = 0 ; irv <nA ; irv++) { vnew[irv] = v[irv][i]; } 
                    
                    ss = s[i];
                         
                    for (ir=0; ir < nA ; ir++)
                    {
                        result2[ir]=0;
                        for (kr=0; kr< 1 ; kr++) { result2[ir]=result2[ir] + vnew[ir]*ss; }   
                    } 
                    
                    /* col1 = result1+result2;   addition of two nAx1 matrices  */
        
                    for (ir = 0 ; ir < nA ; ir++) { col1[ir] =  result1[ir] + result2[ir]; }
                    
                    /* mexPrintf("col1 ========");
                    for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",col1[ir]); mexPrintf("\n");   */
                    
   
                    /* -s(i) * v(:,i-1)*/
                    ss1 = -s[i];
                    for (irv = 0; irv<nA ; irv++)
                    {
                        for (irn = 0; irn < nA ; irn++) { /*j = i-1; */ vnew[irv] = v[irv][i-1]; }
                    }  
           
         
                    for (ir=0; ir < nA ; ir++)
                    {
                       result3[ir]=0;
                       for (kr=0; kr < 1 ; kr++) { result3[ir] = result3[ir] + vnew[ir]*ss1; }
                    }
                
                    /*               %c(i) * v(:,i)  */

                    for (irv = 0; irv< nA ; irv++) { vnew[irv] = v[irv][i]; }

                    sc1 = c[i];
           
                    for (ir=0; ir < nA ; ir++)
                    {
                        result4[ir]=0;
                        for (kr=0; kr < 1; kr++) { result4[ir]=result4[ir] + vnew[ir]*sc1; }
                    }
                /*
                mexPrintf("result4 ========");
                    for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",result4[ir]); mexPrintf("\n"); */
                
               /* addres = result3+result4 */ /* addition of two nAx1 matrices */

                    for (ir = 0 ; ir < nA ; ir++) { addres[ir] =  result3[ir] + result4[ir]; } 
                
                    for (ir = 0 ; ir <nA ; ir++)  { v[ir][i] = addres[ir]; }
                      
                
                    /*  %v(:,i) = -s(i) * v(:,i-1) + c(i) * v(:,i) */
                             
    
                    /* 	%  v(:,i-1) = col1 */
                    for (irv = 0 ; irv < nA ; irv++) { /* for j = i-1; */ v[irv][i-1] = col1[irv]; }
                
               /* mexPrintf("v = ");
                for (ir = 0; ir <nA ; ir++)
                {
                     for (kr = 0; kr <nA ; kr++)
                        {
                        mexPrintf("%f" , v[kr][ir]); 
                        }
                }*/ 
            
            
            }   /* i : 2 to togo end (that is 1 to togo-1) */   
          
              /* mexPrintf("d is ===");
                    for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",d[ir]); mexPrintf("\n"); */
            
              
                     
        if ( fabs(Of[togo]) < TOL )
        {
            lambda[togo] = d[togo] + shift;
  
            /* mexPrintf("LAMBDA in %d iterations IS ========" , its); */
          /* for (ir = 0; ir <nA ; ir++)  mexPrintf("%f ",lambda[ir]); mexPrintf("\n");  */
            
            /* %disp([lambda(togo) its]); */
            togo = togo - 1;
          /*  mexPrintf("togo is %d" , togo); */
        }
    
     } /* end of its loop */
           
            
  for (i=0;i<nA;i++) 
  {
      mxFree(P[i]);
      mxFree(v[i]);
  }
            
	  mxFree(P);              
      mxFree(v);
      
      mxFree(lambda);
      mxFree(d);
      mxFree(Of); 
      mxFree(vnew);
      mxFree(result1);
      mxFree(result2);
      mxFree(col1);
      mxFree(result3);
      mxFree(result4);
      mxFree(addres);
      mxFree(c);  
      mxFree(s);
      mxFree(Oftemp);
  }  /*Funtion end */

