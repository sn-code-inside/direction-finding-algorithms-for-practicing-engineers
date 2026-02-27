/*... reads wav file Library Functions .....
  ... by Prof Kaluri V Ranga Rao, Dr Kaluri Research House ... 20th Sep 2017 .. */
#include "stdafx.h"
#include "rdwav.h"
//#include "mex.h"   /* This one is required */
//#define MATLAB 1
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
int VoiceChunk(int k, char * wavfile, double *un, double *uwav,int * data, int Ni, double *fsD, double *Bpf)
{
    static int maxDataValues,HeaderSize;
    static double *audio;
    int er, decimate,M,Nby2,N;
	double fs = 8000;
    if (k == 0) 
    {
		audio = myAlloc(30);
		er = wavHeader(wavfile, audio, &HeaderSize);

		if (er < 0)
		{
			printf("!. Error in opening the .wav file\n");
			return -100;
		}
        maxDataValues = (int)(audio[8]/2);
		fs = audio[4]; //Fs[0] = fs;
//		printf(" Sampling Frequency in %s file %3.4f\n", wavfile, fs);
    }
    decimate = 2; M = (int)(log(Ni)/log(2));
    er = pitchParts(k,Ni, un,uwav,data,wavfile,audio,decimate,Bpf);
	if (er == -100) return -100;
	fsD[0] = fs / (double)(decimate);
//	printf(" Decimated frequency %3.4f\n", fsD[0]);

//    printf("!. Original array %d= 2^%d  ",Ni,M); 
    N = abs(er); Nby2 = N/2; M = (int)(log(N)/log(2));
//    printf(" Decimated array %d= 2^%d length of un[%d]\n",N,M,er);
	if (er < 0)
	{
//		printf("!. NO Energy in Time Series[%d]\n", er);
		return er;
	}
    
    return N;
}


int wavHeader
(
	char *file,
	double *audio,
	int *dP
)
{
	unsigned char val;
	int byte4[4],indx;
	int temp, k, flag = -1;
	int word = 0, nSize = 0, Channels, Block, bits;
	long rec, skip, skipN, KompresionCode;
	long fs, ByteRate, Data, i, skipC, maxWord = 0, capture = -1;
	int dataCount = 0;
//	int dump[400]; char id[5]; int m = 0;
	char id[5]; int m = 0;
	int fEr;

	flag = -1; capture = -1;
	printf("     Analysing the Header of %s \n", file);
	k = 0; word = 0; nSize = 0; flag = -1;
	fEr = fopen_s(&fpWav, file, "rb");
	if (fpWav == NULL) 
    {
        printf("!.. Error opening file %s(%d)\n", file, fEr);
        return flag;
    }
//	if (fEr == NULL) // fEr = fopen_s(&fp, fname, "r");
//		printf(" Error: Could not open the wave file ");
	dP[0] = 44;
	word = 0; indx = 0;
	while (!(feof(fpWav)))
	{
		k = indx % 4;
		val = fgetc(fpWav); temp = val & 0x00ff; // dump[nSize] = temp & 0x00ff;
		byte4[k] = temp;
		if (k == 3) 
		{
			word = word + 1;
			switch (word)
			{
			case 1:
				printf("p[%d]\t%c%c%c%c is first word \n", word,byte4[0], byte4[1], byte4[2], byte4[3]);
				break;
			case 2:
				rec = byte4[0] + (byte4[1] + (byte4[2] + byte4[3] * 256) * 256) * 256;
				audio[0] = rec;
				printf("p[%d]\tData + Header %ld bytes \n", word,rec);
				break;
			case 3:
				printf("p[%d]\t%c%c%c%c is word \n", word, byte4[0], byte4[1], byte4[2], byte4[3]);
				break;
			case 4:
				printf("p[%d]\t%c%c%c%c is word \n", word, byte4[0], byte4[1], byte4[2], byte4[3]);
				break;
			case 5:
				skip = byte4[0] + (byte4[1] + (byte4[2] + byte4[3] * 256) * 256) * 256;
				skipN = skip - 16;
				audio[1] = skip;
				printf("p[%d]\tExtended bytes 16 + %d = %ld  \n", word,skipN, skip);
				break;
			case 6:
				KompresionCode = byte4[0] + 256 * byte4[1]; audio[2] = KompresionCode;
				Channels = byte4[2] + 256 * byte4[3]; audio[3] = Channels;
				printf("p[%d.1]\tCompression Code %ld  \n", word,KompresionCode);
				printf("p[%d.2]\tNumber of Channels %d \n", word,Channels);
				break;
			case 7:
				fs = byte4[0] + (byte4[1] + (byte4[2] + byte4[3] * 256) * 256) * 256;
				printf("p[%d]\tSampling Rate %d\n", word,fs);
				audio[4] = fs;
				break;
			case 8:
				ByteRate = byte4[0] + (byte4[1] + (byte4[2] + byte4[3] * 256) * 256) * 256;
				printf("p[%d]\tByte Rate %d\n", word,ByteRate);
				audio[5] = ByteRate;
				break;
			case 9:
				Block = byte4[0] + 256 * byte4[1]; audio[6] = Block;
				bits = byte4[2] + 256 * byte4[3]; audio[7] = bits;
				printf("p[%d.1]\tBlock Alignment %d  \n", word,Block);
				printf("p[%d.2]\tNumber of Bits  %d \n", word,bits);
				for (i = 0; i < skipN; i++)
				{
					val = fgetc(fpWav); temp = val; skipC = temp & 0x00ff; nSize = nSize + 1;
					printf("     bytes are being skipped %d value %d\n", nSize, skipC);
				}
				break;
			default:
				if (byte4[0] == 0x64 && byte4[1] == 0x61 && byte4[2] == 0x74 && byte4[3] == 0x61)
				{
					flag = 1; capture = 1; for (m = 0; m < 4; m++) id[m] = byte4[m]; id[4] = 0;
					printf("p[%d]\t%c%c%c%c is word \n", word, byte4[0], byte4[1], byte4[2], byte4[3]);
					printf("\tFirst Occurence '%s' at %d\n", id, word);
				}
				if (capture == 1) {  capture = 0; maxWord = word; }
				if (flag == 1) { dataCount = dataCount + 1; }
				if (word == maxWord + 1)
				{
					Data = byte4[0] + (byte4[1] + (byte4[2] + byte4[3] * 256) * 256) * 256;
					printf("p[%d]\tData Bytes %d \n", word,Data);
					audio[8] = Data;
					printf("%d Data\t(%x.%x.%x.%x) \n", word, byte4[0], byte4[1], byte4[2], byte4[3]);
				}
				break;
			}

			if (dataCount > 1) break;
		}
		indx = indx + 1;
	}
	if (flag == 1) printf("\tMachine recognised the word data in the header at (%d)\n", maxWord);
	else   printf("\n\n !! FAILED TO RECOGNISE DATA STRING !!\n");
	fclose(fpWav);
	dP[0] = indx; audio[9] = indx;
    printf("flag %d word %d k %d[%d]\n",flag,word,k,indx);
	return flag;
}

int wavData
(
	char *file,
	double *audio,
	int skip,  // skip the header length
	double *uk,// converted data
	int *DataI,// integer data
	int *nSmp,
    int kt
)
{
	unsigned char val;
	int byte4[4], temp, k, flag = -1, i;
	static int indx;
	static int word, nSize, Channels, Block, bits, sign = 0;
	int Data,scaleA, scaleB, tData;
	static int s, e, m, subS, block, skipN;
	static double data, fs, frac,scale;
	static int maxDataBytes = 128;
    int N;
	int fEr;

    printf("!. Reading the block %d -  %d bytes of data read\n",kt,indx);
    if (kt == 0)
    {
	    Block = (int)(audio[6]); 	
        bits = (int)(audio[7]); Channels = (int)(audio[3]); fs = audio[4];
	    maxDataBytes = (int)(audio[8]);
	    block = Block / Channels;
    }
	s = nSmp[0]; e = nSmp[1]; 	if (e - s < 0) return -1;
    N = e-s; s=0; e=N;
//	printf("\tResolution %d bits Read data[%d to %d]\n", bits,s,e);
    frac = (fs / 8000.0) - (int)(fs / 8000.0);
	if (frac > 0.5) skipN = (int)(fs / 8000.0) + 1; else skipN = (int)(fs / 8000.0);

	scaleA = (int)(pow(2, bits));
	scaleB = (int)(pow(2, bits - 1));
//	printf("\tGetting the data of %s [%d]samples starting from %d\n", file, e - s, s);
	k = 0; word = 0;  
    m = 0;
    if (kt == 0)
    {
	    fEr = fopen_s(&fpWav, file, "rb");
	    if (fpWav == NULL) 
	    {
		    printf("!.. Error opening file %s(%d)\n", file, fEr); return -1;
	    }
	    indx = 0;
	    printf("\tskip header %d Block bytes %d max %d %d\n", skip, Block, scaleA, scaleB);
		for (i = 0; i < skip+2; i++) val = fgetc(fpWav); 
    }
	while (feof(fpWav) == 0)
	{
		k = indx % Block;
		val = fgetc(fpWav); 
		temp = val & 0x00ff;
		byte4[k] = temp;
		if (k == Block - 1)
		{
			word = word + 1; Data = byte4[Block - 1]; sign = 1;
			for (i = 0; i < block - 1; i++) Data = byte4[block - i - 2] * 256 + Data;
			tData = Data;
			if (Data > scaleB - 1) { Data = scaleA - Data; sign = -1; }
			if (Data == scaleB) Data = Data - 1;
			data = (double)(Data) * (double)(sign);
			scale = (double)(scaleB - 1);
			data = (data / scale);
			if (word >= 0)
			{
				subS = word % skipN;
				if (subS == 0)
				{
					DataI[m] = Data;
					if (bits == 16) uk[m] = data;
					if (bits == 8)  uk[m] = (tData - 128) / 128.0;
					m = m + 1;
				}
			}
			if (word == N+1)  { indx = indx + 1; break; }
		}
		indx = indx + 1;
		if (indx >= maxDataBytes - 1) 
        { 
			fclose(fpWav); 
            printf("!. End of Data  bytes ---> file closed\n");
			return -100;
//            exit(-1);
	
		}
   
	}
	return indx;
}

