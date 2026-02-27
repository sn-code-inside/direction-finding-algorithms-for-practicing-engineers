// ula.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ula.h"
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

int main(int argc, char** argv)
{
    int maxLengthOfFileName = 20;
    int fEr, flag = 0;
    int N = 128, Ni, Nby2, M, k, i,j;
//    int pkI;
    int ula = 4;
//    int data;

    int er = 0;

    char* wavfile, * datafile;

    double* uwav{}, * s{}, * un{}, *yTemp{}, fn[2], fsD;
    double* p;
    int* Data;
    double angle = 20.0,dbyl,decimate = 2.0;
    double config[30];
    int* bins;
    complex** A, * z{};
    double** At;
    double* sz{};
    //  .......... for music .............
    complex** En,**B;
    int rcA[2],D=1,r,rc[2];
    int numOfPhaseSpecSamples = 180;
    int numberOfPeaksInBins = 15;
    double* muSpk;
    double* doaInDeg, d_by_lambda = 0.5;
    double Bpf[2];
    doaInDeg = myAlloc(D);
    muSpk = myAlloc(numOfPhaseSpecSamples);
    //  ...............................


    wavfile = (char*)malloc(50 * sizeof(char));
    datafile = (char*)malloc(50 * sizeof(char));

    FILE* fpAudio;

    //M = 9;   
    strcpy_s(wavfile, 50, "sr2T.wav");
//    strcpy_s(wavfile, 50, "bell.wav");
    //strcpy_s(wavfile, 50, "file01.wav");
    //strcpy_s(wavfile, 50, "sapa8k.wav");
/*    for (k = 0; k < 2000; k++)
   
    {
        er = audioBlock(k, &au, &data, wavfile, 1);
        printf("Data[%d] from %s - %3.4f %x\n",k,wavfile,au,data);
        getchar();
    }
        return 1;*/


    strcpy_s(datafile, 50, "data.csv");

    fEr = fopen_s(&fpAudio, datafile, "w");
    if (fpAudio == NULL)
    {
        printf("!.. Error opening file %s(%d)\n", datafile, fEr);
        return flag;
    }
    M = 10;
    if (M > 14) { printf("N=2^M value of M is limited to 11 max of N = 4096\n"); M = 14; }
    Ni = (int)(pow(2, M));
//  ... allocate memory
    un = myAlloc(Ni);
    uwav = myAlloc(Ni);
    s = myAlloc(Ni);
    Data = myAllocI(Ni);
    angle = -85;
    Bpf[0] = 100.0; Bpf[1] = 1100.0; // Energy bounds in Hz
    for (k = 0; k < 500; k++)
    {
 //  ........................................................................
        N = VoiceChunk(k, wavfile, un, uwav, Data, Ni, &fsD, Bpf);
        if (N == -100) { printf("!. CANNOT RECOVER EXITING\n"); break; }

        if (N > 0)
        {
            Nby2 = N / 2; M = (int)(log(N) / log(2.0));
            bins = wavBins(numberOfPeaksInBins, N, un, config);
            for (i = 0; i < N; i++) s[i] = un[i];
            p = anf(s, N,fsD);
            printf("[k=%d]   N(%d) = VoiceChunk(k, %s, un, uwav,Data, %d, %3.4f); \n", k,N, wavfile, Ni,fsD);
            //s = findFn(un, N, &fn);
            decimate = (double)(Ni) / double(N);
            fn[1] = 800.0 / (fsD);
            At = myAlloc2(ula, N);
            A = ulaMatrix(angle, s, fn, fsD, &dbyl, N,  ula,rc,At);
            myFree2(At, ula);
            printf("size of A %d by %d\n", rc[0], rc[1]);

            printf("[%3.4f][%3.4f]MUSIC NB Freq %3.4f Hz Peak Energy Freq %3.4f\n", fn[1],fn[0], fsD * fn[1],fsD*fn[0]);

//  ................ gold MUSIC starts ...........................
            rcA[0] = rc[1]; rcA[1] = ula;
            r = rcA[1] - D; if (r < 1) { printf("issue with number of sources %d %d\n", rcA[1], D); r = 1; }
            En = myAlloc2Complex(r, rcA[1]);
            B = myAlloc2Complex(rcA[0], rcA[1]);
            for (j = 0; j < ula; j++)
            {
                for (i = 0; i < rcA[0]; i++) B[i][j] = A[j][i]; // B = A'
            }
            myFree2Complex(A, ula);
            printf(" size of data matrix %d by %d\n", rcA[0], rcA[1]);
            //	................... new ....
            if (ula - D < 1)
            { printf("--->No Solution %d %d\n", ula, D); return NULL;}

            doaInDeg = Hermit(B, rcA, rcA[0], muSpk, numOfPhaseSpecSamples, D, En, dbyl);
            if (doaInDeg != NULL)
            {
                printf(" DOA values by gold MUSIC  ");
                for (i = 0; i < D; i++) printf(" %3.4f ", doaInDeg[i]); printf(" (%3.4f)\n", angle);
//                if (doaInDeg == NULL) break;
                printf(" Normalised Freq %3.4f D by Lambda %3.4f\n", fn[1], dbyl);
                fprintf(fpAudio, "%3.4f,%3.4f", angle, doaInDeg[0]); fprintf(fpAudio, "\n");
            }
            else {printf(" COULD NOT COMPUTE DOA\n"); getchar();}
            angle = angle + 1;
            if (angle > 85.0) angle = -85.0;
            getchar();
        }

    }
    //for (i = 0; i < N; i++) fprintf(fpAudio, "%3.4f,", un[i]); fprintf(fpAudio, "\n");
    fclose(fpAudio);
    free(un); 
    

    return 1;
}






