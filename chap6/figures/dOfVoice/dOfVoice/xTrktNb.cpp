#include "ula.h"
#include "mex.h"   /* This one is required */

void Usage();

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double *inputK, *inputM, *inputN,*inputAngle,*inputBpf; 
	int ula, M,Ni,N,Nby2;

    double fn[2],fsD;
    double *un,*s,*uwav,*pitch;
    int *data;
	int k,r,c,i,sLen,m,rc[2];
 
    int status;
    double *sPtr,*yPtr,*flagPtr,*freqPtr,*dbylPtr,*uwPtr,*pitchPtr;
    double *ArPtr, *AiPtr;
    double* AtPtr;
    char* wavfile;
    double angle,DbyL=0.5,decimate = 2.0;
    double Bpf[2];
    double rem;
    complex **A;
    double** At{};
    wavfile = (char*)malloc(50 * sizeof(char));
    if ( (nlhs != 9) || (nrhs != 6) )
    {
       printf(" Usage Error Parameters Left Hand Side = %d(9) .. Right Hand Side = %d(6) \n",nlhs,nrhs);
       Usage(); 
       return;
    }

    if (!(mxIsChar(prhs[0]))) mexErrMsgTxt("Input must be of type string.");
    wavfile = mxArrayToString(prhs[0]);

    r = (int)(mxGetM(prhs[1]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[1] must be scalar\n");
    inputK = mxGetPr(prhs[1]); k = (int)(inputK[0]);

    r = (int)(mxGetM(prhs[2]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[2] must be scalar\n");
    inputM = mxGetPr(prhs[2]); M = (int)(inputM[0]);

    r = (int)(mxGetM(prhs[3]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[3] must be scalar\n");
    inputN = mxGetPr(prhs[3]); ula = (int)(inputN[0]);

    r = (int)(mxGetM(prhs[4]));
    if ( r != 1 ) mexErrMsgTxt("!. RHS[4] must be scalar\n");
    inputAngle = mxGetPr(prhs[4]); angle = inputAngle[0];
    if ( fabs(angle) > 90.0 )
    {
       rem = fabs(angle)/90.0 - (int)(fabs(angle)/90.0);
       angle = rem*90.0*(fabs(angle)/angle);  
    }
    c = (int)(mxGetN(prhs[5]));
    if ( c != 2 ) mexErrMsgTxt("!. RHS[5] must be a two vector\n");
    inputBpf = mxGetPr(prhs[5]);
    Bpf[0] = inputBpf[0]; Bpf[1] = inputBpf[1];
    printf("Band Pass Filter Bound %3.4f %3.4f\n",Bpf[0],Bpf[1]);


//  ............... process inputs ................ 
    if (M > 14) { printf("N=2^M value of M is limited to 11 max of N = 4096\n"); M = 14; }
    Ni = (int)(pow(2, M));
    un = myAlloc(Ni); uwav = myAlloc(Ni); data = myAllocI(Ni);
    s = myAlloc(Ni); 
    //Bpf[0] = 100.0; Bpf[1] = 1000.0;
    N = VoiceChunk(k, wavfile, un, uwav, data, Ni,&fsD,Bpf);
    fn[1] = 800.0 / fsD;
    decimate = (double)(Ni)/(double)(N);
    printf("N=%d and Ni %d decimated freq %3.4f\n",N,Ni,decimate);
    if (N == -100) mexErrMsgTxt(" Cannot Recover End File or a Fatal Error ");

        if (N > 0)
        {
            At = myAlloc2(ula, N);
            printf("wavefile %s indx %d samples %d ULA %d Decimated %3.4f\n",wavfile,k,N,ula,fsD);
            printf("target angle %3.4f\n",angle);
            printf("[k=%d]   N(%d) = VoiceChunk(k, %s, un, data, %d); \n", k,N, wavfile, Ni);
            Nby2 = N / 2; M = (int)(log(N) / log(2));

            for (i = 0; i < N; i++) s[i] = un[i];
//            pitch = anf(s, N,fsD);
            A = ulaMatrix(angle, s, fn, fsD, &DbyL,N,ula,rc,At);
            printf("MUSIC dbyl %3.4f\n",DbyL);
            printf("Normalised Freq [%3.4f][%3.4f]\n", fn[1],fn[0]);
            printf("MUSIC NB Freq %3.4f Hz Peak Energy Freq %3.4f\n",fsD * fn[1],fsD*fn[0]);
        }
//  ............... end processing ................   
    if (N < 0)
    {
        mxDestroyArray(plhs[0]);
        plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
        yPtr = mxGetPr(plhs[0]); yPtr[0] = N;

        mxDestroyArray(plhs[1]);
        plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
        sPtr = mxGetPr(plhs[1]); sPtr[0] = Ni;

        mxDestroyArray(plhs[4]);
        plhs[4] = mxCreateDoubleMatrix(1, 1, mxCOMPLEX);
        ArPtr = mxGetPr(plhs[4]);  AiPtr = mxGetPi(plhs[4]);
        ArPtr[0] = N; AiPtr[0] = N;

        mxDestroyArray(plhs[6]);
        plhs[6] = mxCreateDoubleMatrix(1, 1, mxREAL);
        uwPtr = mxGetPr(plhs[6]); uwPtr[0] = Ni;

        mxDestroyArray(plhs[7]);
        plhs[7] = mxCreateDoubleMatrix(1, 1, mxREAL);
        pitchPtr = mxGetPr(plhs[7]); pitchPtr[0] = Ni;

        mxDestroyArray(plhs[8]);
        plhs[8] = mxCreateDoubleMatrix(1, 1, mxREAL);
        AtPtr = mxGetPr(plhs[8]); AtPtr[0] = angle;
    } else
    {
        mxDestroyArray(plhs[0]);
        plhs[0] = mxCreateDoubleMatrix(1, N, mxREAL);
	    yPtr = mxGetPr(plhs[0]);  for(i=0; i<N; i++) yPtr[i] =un[i];

        mxDestroyArray(plhs[1]);
        plhs[1] = mxCreateDoubleMatrix(1, N, mxREAL);
        sPtr = mxGetPr(plhs[1]);  for(i=0; i<N; i++) sPtr[i] =s[i];

        mxDestroyArray(plhs[4]);
        plhs[4] = mxCreateDoubleMatrix(ula, rc[1], mxCOMPLEX);
        ArPtr = mxGetPr(plhs[4]);  AiPtr = mxGetPi(plhs[4]);
        for (m = 0; m < ula; m++)
        {
            for (i = 0; i < rc[1]; i++)
            {
                ArPtr[i*ula+m] = A[m][i].r;
                AiPtr[i*ula+m] = A[m][i].i;
            }
        }

        mxDestroyArray(plhs[8]);
        plhs[8] = mxCreateDoubleMatrix(ula, N, mxREAL);
        AtPtr = mxGetPr(plhs[8]); 
        for (m = 0; m < ula; m++)
        {
            for (i = 0; i < N; i++)
            {
                AtPtr[i * ula + m] = At[m][i];
            }
        }

        mxDestroyArray(plhs[6]);
        plhs[6] = mxCreateDoubleMatrix(1, Ni, mxREAL);
        uwPtr = mxGetPr(plhs[6]);
        for(i=0; i<Ni; i++) uwPtr[i] =uwav[i];

        mxDestroyArray(plhs[7]);
        plhs[7] = mxCreateDoubleMatrix(1, N, mxREAL);
        pitchPtr = mxGetPr(plhs[7]);
        for(i=0; i<N; i++) pitchPtr[i] =pitch[i];

     }
    plhs[2] = mxCreateDoubleMatrix(1, 1, mxREAL);
    flagPtr = mxGetPr(plhs[2]); flagPtr[0] = N;

    plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
    freqPtr = mxGetPr(plhs[3]); freqPtr[0] = fsD;

    plhs[5] = mxCreateDoubleMatrix(1, 1, mxREAL);
    dbylPtr = mxGetPr(plhs[5]); dbylPtr[0] = DbyL;




    free(un); free(data); //myFree2(At, ula);
    return;
}

void Usage()
{
   printf(" updated on 19th Jul 2024 4pm Dublin Ohio\n"); 
   printf(" [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,MintwoPowerM,ula,doa2,bpf);\n");
   printf(" [u,s,flag,fs,A,dbyL,uwav,pitch,At] = xTrktNb(wavfile,k,10,5,20,[100 1000]);\n"); 
   printf(" Inputs: 6\n");
   printf(" 1. Name of the wavefile 'nh3.wav'\n");
   printf(" 2. k running index must start from 0\n");
   printf(" 3. N = 2^M is the voice chunk\n");
   printf(" 4. ula is ULA size\n"); 
   printf(" 5. doa angle in Degrees\n"); 
   printf(" 6. bpf[0] bpf[1] filter freqencies 100 - 1000 Hz\n");
   printf(" Outputs: 9\n");
   printf(" 1. Decimated Sequence u\n"); 
   printf(" 2. Narrow Band Signal with Max Energy s\n");
   printf(" 3. Error flag flag\n");
   printf(" 4. sampling rate of the decimated sequence\n"); 
   printf(" 5. A complex Matrix for MUSIC doa\n"); 
   printf(" 6. d by Lambda value\n");
   printf(" 7. uwav is actual undecimated voice\n");
   printf(" 8. p formant frequency variation with time a complex matrix\n");
   printf(" 9. At ula out put a real matrix\n");
}


    