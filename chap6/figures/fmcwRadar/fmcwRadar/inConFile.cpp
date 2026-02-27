#include "stdafx.h" // THIS IS A MUST
#include "inConFile.h"
//#include "mex.h"
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

//int rdRcon(int* rc, char* datafile, double* config, double** tgt, int* RC)
int rdRcon(int* rc, char* datafile, double* config)
{
	double alpha, Fs, Rgain;
	char *cwd;
//	char *date;
	unsigned int seed;
//	int len, Len;
	int flag, c;
	int maxLengthOfFileName = 60;
	int numOfPhaseSpecSamples = 30;
	int adcSamples = 512, i7Ti=0;
	int control, synthetic, numberOfTgts, kmax, FFTsamples, FrqGoldRows,cby2;
	int Control;
	flag = 1;
	rc[0] = 512; rc[1] = 8; // default values
	FFTsamples = rc[0];
	c = rc[1];
	cwd = _getcwd(NULL, 0);
	printf("!. %s\n", cwd);
	seed = (unsigned int)(time(NULL)); 	srand(seed);


	alpha = config[0]; Fs = config[1]; control = (int)(config[2]);
	synthetic = (int)(config[3]); numberOfTgts = (int)(config[4]); 
	numOfPhaseSpecSamples = (int)(config[5]);
	kmax = (int)(config[6]);
	synthetic = 0;
	printf("!. int rdRcon(..)\n");
	printf("!. 3rd value in rcon.txt file is [%d]\n",control);
	printf("   if -1 single stepping \n");
	printf("   and if -2 you get some documentation and exit out\n");
//	date = getDate();
//	....... create a log file here ......

	fprintf(fpLog,"!. current working directory %s\n", cwd);
	fprintf(fpLog,"!. int rdRcon(..)\n");
	fprintf(fpLog,"!. 3rd value in rcon.txt file is [%d]\n", control);
	fprintf(fpLog,"   if -1 single stepping \n");
	fprintf(fpLog,"   and if -2 you get some documentation and exit out\n");
//	.....................................

/*	switch (synthetic)
	{
	case 0:
		break;
	case 1:
		strcpy_s(confile, 20, "tdata.txt");
		printf("!. Reading Target Data from %s\n", confile);
		flag = rdTgtFile(tgt, RC, confile);
		config[4] = RC[0];
		FFTsamples = 512;
		rc[0] = 512; rc[1] = 8;
		cby2 = rc[1] / 2; 	FrqGoldRows = cby2*RC[0];
		config[7] = FFTsamples; config[8] = config[7]; config[9] = 0; config[10] = FrqGoldRows;
		return flag;
	case 2:
		break;
	default:
		printf("!. Synthetic value is not in limits[0 1 2] %d\n", synthetic);
		return -10;
	}*/


	printf("!. data file name %s\n", datafile);
	adcSamples = CheckrdRadar(c, datafile);
	if (adcSamples < 0) 
	{ 
		printf("!. issue with file %s[%d]\n", datafile, adcSamples); 
		flag = -2; return flag; 
	}
	Control = control + 3;
	switch (Control)
	{ 
		case 1: break; case 2: break; case 3: break; case 4: break;
		default:
		config[2] = -1;  control = (int)(config[2]);
		printf("!. invalid control code set to %d[%d]\n", control, Control);
	}

	switch (adcSamples)
	{
	case 225:
		printf("!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		printf("!. I will Fix it for you probably data is from TI processor\n");
		fprintf(fpLog,"!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		fprintf(fpLog,"!. I will Fix it for you probably data is from TI processor\n");
		FFTsamples = 128;
		rc[0] = 128; rc[1] = 8;
		i7Ti = 0;
		break;
	case 128:
		printf("!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		printf("!. I will Fix it for you probably the data i7 and bridge\n");
		fprintf(fpLog,"!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		fprintf(fpLog,"!. I will Fix it for you probably the data i7 and bridge\n");
		FFTsamples = 128; i7Ti = 1;
		rc[0] = 128; rc[1] = 8;
		break;
	case 512:
		printf("!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		printf("!. I will Fix it for you probably data is from TI processor\n");
		fprintf(fpLog,"!. Fix comptability issue adc %d fft %d i7Ti %d\n", adcSamples, FFTsamples, i7Ti);
		fprintf(fpLog,"!. I will Fix it for you probably data is from TI processor\n");
		FFTsamples = 512;
		rc[0] = 512; rc[1] = 8;
		break;
	default:
		printf("!. currently I don't support this adc samples %d\n", adcSamples);
		fprintf(fpLog,"!. currently I don't support this adc samples %d\n", adcSamples);
		flag = -3;  return flag;
	}
	cby2 = rc[1] / 2; 	FrqGoldRows = cby2*numberOfTgts;
	config[7] = FFTsamples; config[8] = adcSamples; config[9] = i7Ti; config[10] = FrqGoldRows;
	printf("!. number of targets from config file %d\n", numberOfTgts); 

	Rgain = getRgain(alpha, Fs); config[11] = Rgain;
//	config[12] = 0.25;
	return flag;
}

int rdConfig(double *rdCon, char *datafile)
{
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	float val = 0.0F; // must be float
	int k, flag=1, rKt;
	int fEr;
	int numOfValinConfile;
	int maxLengthOfFileName = 60;
	char *confile;
	confile = (char *)malloc(maxLengthOfFileName * sizeof(char));
	FILE *fpConfig;
	printf("!. reading rcon.txt file\n");
	strcpy_s(confile, 20, "rcon.txt");

	fEr = fopen_s(&fpConfig, confile, "r");
	numOfValinConfile = 7; // added two more number of targets 27.5.2018 .. 3.6.2018 @ Princeton NJ
	if (fpConfig == NULL) {
		printf("!. Error opening file %s(%d)\n", confile, fEr); flag = -fEr; return flag;
	}
	else
	{
		rKt = 0;
		while (feof(fpConfig) == 0)
		{
			for (k = 0; k < numOfValinConfile; k++)
			{
				fscanf_s(fpConfig, "%f", &val); rdCon[k] = val;
			}
			fscanf_s(fpConfig, "%s", datafile, maxLengthOfFileName);

			break;
		}
	}

//	if (feof(fpConfig) != 0)
//	{
//		printf("!. End of Configuration File  %s[%d]\n", confile, k);
//		flag = 2;
//	}
//	else flag = 1;

	if (fpConfig != NULL) fclose(fpConfig);
	else flag = -1;

	fclose(fpConfig);



	return flag;
}

char * fileDetails(char * fName, int *size)
{
	struct stat bufA;
	struct tm buf;
	time_t t;
	int er=0,flag=0;
	char* dtNtime;
	dtNtime = (char*)malloc(100 * sizeof(char));

	printf("filedetails %s\n",fName);
	if (!stat(fName, &bufA))
	{
		t = bufA.st_mtime; size[0] = bufA.st_size;
		er = localtime_s(&buf, &t);

		er = asctime_s(dtNtime, 100, &buf);
		printf("file details %s\n", dtNtime);
//		getchar();
	}
	else
	{
		printf("!. Error getting modified time in File %s\n",fName);
		return NULL;
//		flag = -6;
	}
//	fclose(fpLogTime);
	return dtNtime;
}

int CheckrdRadar(int c, char * fname)
{
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	float val = 0.0F, Val = 0.0F;
	double rowk;
	int valueCount = 0, noOfBlocks = 0;
	int newBlockSize = 128;
	int k, r, i, flag = 1, rKt;
	int s, iMax, fEr,er=0;
	int *pks, indx = 0, *col, dif;
	double *Ak{};
	double oldVal;

	FILE *fpCheck;
	flag = 1; rKt = 0; 	iMax = 1024; r = iMax;
	col = (int*)malloc(r * sizeof(int));
	pks = (int*)malloc(r * sizeof(int));
	s = 0;
	Ak = (double*)malloc(c * sizeof(double));
	printf("\n!. scanning the file %s for details by reading %d lines\n", fname, iMax);
	fprintf(fpLog,"\n!. scanning the file %s for details by reading %d lines\n", fname, iMax);
	fEr = fopen_s(&fpCheck, fname, "r");



	if (fpCheck == NULL) printf("!.. Error opening file %s(%d)\n", fname, fEr);
	else
	{
		rKt = 0;
		while (feof(fpCheck) == 0)
		{
			for (i = 0; i < iMax; i++)
			{
				for (k = 0; k < c; k++)
				{
					fscanf_s(fpCheck, "%f", &val); valueCount++;
					if (i >= s) { if (rKt < r) { Ak[k] = (double)(val); rowk = (double)(val); } }
				}
//				for (k = 0; k < c; k++) printf("%3.4f ", Ak[k]); printf("\n"); getchar();
				if (i >= s) { if (rKt < r) rKt = rKt + 1; }
				oldVal = Val;
				fscanf_s(fpCheck, "%f", &val); valueCount++; // one more time stamp .. 31st May 2017
				Val = val;				  //				fscanf_s(fp, "%f", &val); // one more time stamp .. 31st May 2017
				dif = (int)(val - oldVal);
				er = er + abs(dif);
				if (i > 0)
				{
//					printf("%d %d\n",i,dif);
					if (dif > 0) 
					{ 
						er = 0;
						pks[indx] = i; col[indx] = dif;  
						indx = indx + 1;
					}
				}
			}
			break;
		}
	}
	if (feof(fpCheck) != 0)
	{
		printf("!. End of File %s[%d.%d]\n", fname, rKt, k);
		fprintf(fpLog, "!. End of File %s[%d.%d]\n", fname, rKt, k);
		flag = -1;
	}
	printf("!. closing the file %s\n", fname);
	printf("!. collected data in col[%d] is analysed \n",indx);
	fclose(fpCheck);

	if (indx != 0)
	{
//		printf("!. ADC samples ");
//		for (k = 0; k < indx; k++)
//			printf("%d[%d] ", pks[k], col[k]); printf("\n");
		iMax = pks[0];
	}else printf("!. [%d] run away sequence\n", indx);
	printf("!. Block Markers ");
	fprintf(fpLog,"!. Block Markers ");
	for (k = 0; k < indx; k++)
	{
		printf("%d ", col[k]);
		fprintf(fpLog,"%d ", col[k]);
	}
	printf("\n");
	fprintf(fpLog,"\n");
	noOfBlocks = r/iMax;
	switch (iMax)
	{
		case 128: flag = 1; break;
		case 225: flag = 1; er = 0; break;
		case 256: flag = 1; break;
		case 512: flag = 1; break;
		default: printf("!. improper block size %d\n",iMax);  flag = -1; break;
	}


	printf("!. Number of Blocks Read %d size %d error %d\n", noOfBlocks, iMax, er);
	if (er > 0)
	{
		flag = -1;
		if (er > 10)
		{
			printf("!. I will reconstruct the file assuming last column is missing\n");
			printf("!. DO NOT TRUST OPEN AND SEE THE FILE\n");
			fprintf(fpLog,"!. I will reconstruct the file assuming last column is missing\n");
			fprintf(fpLog,"!. DO NOT TRUST OPEN AND SEE THE FILE\n");
			fEr = CreatNewDataFile(c, fname, newBlockSize);
		}
		else printf("!. I DONOT KNOW HOW TO CLASIFY CHECK INPUT FILE ODD BLOCK SIZE %d\n",iMax);
	}
	else {
		printf("   int CheckrdRadar( scan the file %s)\n", fname);
		printf("!. ADC Samples %d\n", flag * iMax);
		printf("!. File %s[%d.%d]\n", fname, rKt, k);
		fprintf(fpLog,"   int CheckrdRadar( scan the file %s)\n", fname);
		fprintf(fpLog, "!. ADC Samples %d\n", flag * iMax);
		fprintf(fpLog, "!. File %s[%d.%d]\n", fname, rKt, k);
	}
	free(col); free(pks); free(Ak);
	return flag*iMax;
}

int CreatNewDataFile(int c, char* fname, int blockSize)
{
	int k, valueCount = 0,fEr,er;
	float val;
	double * Ak;
	int lineCount = 0, blockCount = 0;
	int len,Len,flag=0;
	char *fileNew;
	FILE* fp, *fpNewData;
	len = (int)(strnlen_s(fname, 40)); Len = len + 10;
	fileNew = (char*) malloc(Len * sizeof(char));
	er = stripNaddFile(fname, fileNew, ".txt",".txt");
	if (er < 0) { printf("!. missing extension\n"); flag = er; }
//	printf("%d New File %s\n", len, fileNew); getchar();

	fEr = fopen_s(&fp, fname, "r");
	er = fopen_s(&fpNewData, fileNew, "w");
	printf("!. CREATING NEW DATA FILE %s block size %d\n",fileNew, blockSize);
	Ak = (double*)malloc(c * sizeof(double));

	if (fp == NULL) { printf("!.. Error opening file %s(%d)\n", fname, fEr); flag = -1; }
	else
	{
		while (feof(fp) == 0)
		{
			for (k = 0; k < c; k++)
			{
				fscanf_s(fp, "%f", &val); valueCount++;
				Ak[k] = (double)(val);
			}
			blockCount = (lineCount/blockSize);
			lineCount++;
//				for (k = 0; k < c; k++) printf("%3.4f ", Ak[k]); printf("\n");
			for (k = 0; k < c; k++) fprintf(fpNewData, "%3.4f ", Ak[k]); 
			fprintf(fpNewData, "% 3.4f\n",(double)(blockCount));
		}
	}
	printf("!. No of Lines in the FILE %d\n",lineCount);
	fclose(fp); fclose(fpNewData);
	return flag;
}

int stripNaddFile(char* inFile, char * outFile, const char* inExt, const char *outExt)
{
	char* part;
	int len, Len = 0,flag =1,k,er=0;
	int maxLengthOfFileName = 80;
	if (strnlen_s(inExt, maxLengthOfFileName) == strnlen_s(outExt, 30))
	{
//		printf("same length %s %s\n", inExt, outExt);
		len = (int)(strnlen_s(inExt, 30));
		flag = 1;
		for (k = 0; k < len; k++)
		{
			if (inExt[k] != outExt[k]) { flag = -1;  break; }
		}
	}
	else flag = -1;
//	if (flag < 0) printf("extensions don't match %d\n", flag);
//	else printf("same type of extensions %d\n", flag);

	len = (int)(strnlen_s(inFile, maxLengthOfFileName));  Len = len + 10;

	part = (char*)malloc(maxLengthOfFileName * sizeof(char));
	part = strstr(inFile, inExt);
//	printf("part %s\n", part);
	if (part == NULL) { printf("!. missing %s extension\n", inExt); return -1; }

	strcpy_s(outFile, 80, inFile); 
//	printf("outFile %s\n", outFile);
	outFile[len - 4] = '\0';
//	printf("stripped extension %s\n", outFile);
	if (flag > 0) strcat_s(outFile, Len, "New");
	strcat_s(outFile, Len, outExt);
//	printf("%s\n", outFile);
//	getchar();
	return er;
}

double getRgain(double alpha, double Fs)
{
	/************************Radar Configuration Parameters************************/
	double Rgain, cM;
	//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	//	Ts = 1 / Fs;
	cM = 299.792458;
	Rgain = (cM / alpha)*(Fs / 1000.0)*(0.5);
	printf("!. Range Gain %3.4f\n", Rgain);
	return Rgain;
	/*****************************************************************************/
}

int rdTgtFile(double **rdCon, int * rc, char * fname)
{
	float val = 0.0F;
	int i, k, r, c, flag, rKt;
	int fEr;
//  Copy Right Protected Dr Kaluri Reserach House written by Prof Kaluri
	FILE *fpTgt;
	printf("int rdTgtFile(read %s for hardware information)\n", fname);
	r = rc[0];  c = rc[1];
	fEr = fopen_s(&fpTgt, fname, "r");
	if (fpTgt == NULL) printf("!.. Error opening file %s(%d)\n", fname, fEr);
	else
	{
		rKt = 0;
		while (feof(fpTgt) == 0)
		{
			for (i = 0; i < r; i++)
			{
				for (k = 0; k < c; k++)
				{
					fscanf_s(fpTgt, "%f", &val); rdCon[i][k] = val;
					printf("[%d]-> %3.4f ", rKt, val);
				}  printf("\n");
				rKt = rKt + 1;
				if (feof(fpTgt) != 0) break;
			}
			break;
		}
	}
	if (feof(fpTgt) != 0)
	{
		printf("!. End of Target File  %s[%d] .. number of rows %d\n", fname, i, rKt);
		fclose(fpTgt);
		rc[0] = rKt;
		flag = 1;
	}
	else flag = -1;
	return flag;
}

void usage(double* rdCon, char* datafile)
{
	double alpha, Fs, Rgain;
	int control, synthetic, numberOfTgts, N, kmax;
	int size;
	int FFTsamples, adcSamples, i7Ti, FrqGoldRows;
	char* date{}, * dateFile{};
	char* rdrImgFile, * dateUpdate{};
	rdrImgFile = (char*)malloc(20 * sizeof(char));

	alpha = rdCon[0]; Fs = rdCon[1]; control = (int)(rdCon[2]);
	synthetic = (int)(rdCon[3]); numberOfTgts = (int)(rdCon[4]); N = (int)(rdCon[5]);
	kmax = (int)(rdCon[6]);
	FFTsamples = (int)(rdCon[7]); adcSamples = (int)(rdCon[8]);
	i7Ti = (int)(rdCon[9]); FrqGoldRows = (int)(rdCon[10]);
	Rgain = rdCon[11];
	date = getDate();
	strcpy_s(rdrImgFile, 20, "rdrImg.exe");
	dateUpdate = fileDetails(rdrImgFile, &size);
	if (dateUpdate == NULL)
	{
		strcpy_s(rdrImgFile, 20, "rcon.txt");
		dateUpdate = fileDetails(rdrImgFile, &size);
	}
	//printf("!. Date of Update %s\n", dateUpdate);

	printf(".............. simple documentation .........updated %s\n\n",dateUpdate);
	printf("!. %s\n", date);
	dateFile = fileDetails(datafile, &size);
	printf("!. %s of size [%d] %s\n", datafile, size, dateFile);
	printf("!. myRdr %s\n", datafile);
	printf("!. if NO argument it will take from rcon.txt\n");
	printf("!. I try to provide some doumentaion \n");
	printf("!. I will be reading two files -> ");
	printf(" [rcon.txt and tdata.txt]\n");
	//	printf("!. myLog01.csv contains log information when ever you execute this\n");
	printf("!. rcon file contains only one row giving configuration details\n");
	printf("!. there are 7 numerical entries and last is a file string = [%s]\n", datafile);
	printf("!. 1. rcon[0] alpha slope in MhZ per micro second [%3.4f]\n", alpha);
	printf("!. 2. rcon[1] Fs sampling frequency in KhZ [%3.4f]\n", Fs);
	printf("!. 3. rcon[2] control program control 1  0 -1 -2 [%d]\n", control);
	printf("!. 4. rcon[3] synthetic data 0 or 1 [%d]\n", synthetic);
	printf("!. 5. rcon[4] numberOfTgts [%d]\n", numberOfTgts);
	printf("!. 6. rcon[5] N number of samples in the phase sepctrum kMUSIC [%d]\n", N);
	printf("!. 7. rcon[6] kmax is the number of time A matrix is read from file %s [%d]\n", datafile, kmax);
	printf("!. 8. rcon[7] numberOfTgts [%d]\n", numberOfTgts);
	printf("!. 9. rcon[8] samples for FFT [%d]\n", FFTsamples);
	printf("!. 0. rcon[9] acquired ADC samples [%d]\n", adcSamples);
	printf("!. 1. rcon[10] a flag needed [%d]\n", i7Ti);
	printf("!. 2. rcon[11] range gain [%3.4f]\n", Rgain);
	printf("!. 3. rcon[12] amplitude threshold in double** sortCluster(..) [%3.4f]\n", rdCon[12]);
	printf("!. 4. rcon[13] number of real columns of matrix [%d]\n", (int)(rdCon[13]));
	printf("!. 5. rcon[14] maximum number blocks to be iterated [%d]\n", (int)(rdCon[14]));
	printf("!. if control is -2 only documentation is displayed and returned back\n");
	printf("!. if control is 0 file name taken from rcon file %s if -1 single stepping is performed\n", datafile);
	printf("!. if control is 1 file name taken from rcon file %s and output range is multiplied by Rgain %3.4f\n", datafile, Rgain);
	printf("!. if synthetic = 1 tdata.txt data is used and a file synth.txt is created for future use\n");
	printf("!. tdata.txt is organised as a matrix each row describes the target\n");
	printf("!. first entry normalised frequency 2nd signal strength 3rd DOA in degrees\n");
	printf("!. number of rows are taken as number of targets\n");
	printf("!. You may contact Prof Kaluri V Ranga Rao at kaluri@ieee.org\n");
	printf("!. You may locate the source at or myGanesh\n");
	printf("!. D:\\Edu-Institutions\\JNTU-H\\myResearch\\IEEEtrans\\ICSP2018\\dataNfig\\backup4Jun2018\n");
	printf("!. 11th Jun 2018 at Princeton NJ on my visit to see my daughter\n");
	printf("!. 30th Oct 2022 at Dublin OH on my visit to see my daughter\n");
	printf("!. 30th Jun 2023 at Dublin OH on my visit to see my daughter\n");
	printf("!. 6th  Aug 2023 at Dublin OH on my visit to see my daughter\n");
	printf("!. 6th  Oct 2023 at Belle Mead NJ on my visit to see my daughter in partioning\n");
	printf("\n\n.............. simple documentation .........updated %s\n",dateUpdate);

	//	.......... log into file .....................................................



	fprintf(fpLog, ".............. simple documentaion .........updated on 16th Sep 2022\n\n");
	fprintf(fpLog, "!. reading datafile on %s\n", date);
	fprintf(fpLog, "!. %s of size [%d] %s\n", datafile, size, dateFile);
	fprintf(fpLog, "!. if NO argument it will take from rcon.txt\n");
	fprintf(fpLog, "!. I try to provide some doumentaion \n");
	fprintf(fpLog, "!. I will be reading two files -> ");
	fprintf(fpLog, " [rcon.txt and tdata.txt]\n");
	fprintf(fpLog, "!. Contains log information when ever you execute this in *.log\n");
	fprintf(fpLog, "!. rcon file contains only one row giving configuration details\n");
	fprintf(fpLog, "!. there are 7 numerical entries and last is a file string = [%s]\n", datafile);
	fprintf(fpLog, "!. 1. rcon[0] alpha slope in MhZ per micro second [%3.4f]\n", alpha);
	fprintf(fpLog, "!. 2. rcon[1] Fs sampling frequency in KhZ [%3.4f]\n", Fs);
	fprintf(fpLog, "!. 3. rcon[2] control program control 1  0 -1 -2 [%d]\n", control);
	fprintf(fpLog, "!. 4. rcon[3] synthetic data 0 or 1 [%d]\n", synthetic);
	fprintf(fpLog, "!. 5. rcon[4] numberOfTgts [%d]\n", numberOfTgts);
	fprintf(fpLog, "!. 6. rcon[5] N number of samples in the phase sepctrum kMUSIC [%d]\n", N);
	fprintf(fpLog, "!. 7. rcon[6] kmax is the number of time A matrix is read from file %s [%d]\n", datafile, kmax);
	fprintf(fpLog, "!. 8. rcon[7] numberOfTgts [%d]\n", numberOfTgts);
	fprintf(fpLog, "!. 9. rcon[8] samples for FFT [%d]\n", FFTsamples);
	fprintf(fpLog, "!. 0. rcon[9] acquired ADC samples [%d]\n", adcSamples);
	fprintf(fpLog, "!. 1. rcon[10] a flag needed 225 samples [%d]\n", i7Ti);
	fprintf(fpLog, "!. 2. rcon[11] range gain [%3.4f]\n", Rgain);
	fprintf(fpLog, "!. 3. rcon[12] amplitude threshold in double** sortCluster(..) [%3.4f]\n", rdCon[12]);
	fprintf(fpLog, "!. 4. rcon[13] number of real columns of matrix [%d]\n", (int)(rdCon[13]));
	fprintf(fpLog, "!. 5. rcon[14] maximum number blocks to be iterated [%d]\n", (int)(rdCon[14]));	fprintf(fpLog, "!. if control is -2 only documentation is displayed and returned back\n");
	fprintf(fpLog, "!. if control is 0 file name taken from rcon file %s if -1 single stepping is performed\n", datafile);
	fprintf(fpLog, "!. if control is 1 file name taken from rcon file %s and output range is multiplied by Rgain %3.4f\n", datafile, Rgain);
	fprintf(fpLog, "!. if synthetic = 1 tdata.txt data is used and a file synth.txt is created for future use\n");
	fprintf(fpLog, "!. tdata.txt is organised as a matrix each row describes the target\n");
	fprintf(fpLog, "!. first entry normalised frequency 2nd signal strength 3rd DOA in degrees\n");
	fprintf(fpLog, "!. number of rows are taken as number of targets\n");
	fprintf(fpLog, "!. You may contact Prof Kaluri V Ranga Rao at kaluri@ieee.org\n");
	fprintf(fpLog, "!. You may locate the source at or myGanesh\n");
	fprintf(fpLog, "!. D:\\Edu-Institutions\\JNTU-H\\myResearch\\IEEEtrans\\ICSP2018\\dataNfig\\backup4Jun2018\n");
	fprintf(fpLog, "!. 11th Jun 2018 at Princeton NJ on my visit to see my daughter\n");
	fprintf(fpLog, "!. 30th Oct 2022 at Dublin OH on my visit to see my daughter\n");
	fprintf(fpLog, "!. 30th Oct 2022 at Dublin OH on my visit to see my daughter\n");
	fprintf(fpLog, "!. 30th Jun 2023 at Dublin OH on my visit to see my daughter\n");
	fprintf(fpLog, "!. 6th  Aug 2023 at Dublin OH on my visit to see my daughter\n");
	fprintf(fpLog, "!. 6th  Oct 2023 at Belle Mead NJ on my visit to see my daughter - partioning algo\n");
	fprintf(fpLog, "\n\n.............. simple documentaion .........updated on 6th Oct 2023\n");
	//	fclose(fpLog);


	return;
}

char* getDate()
{
	//	......... local time ...................................
	int er;
	time_t now;
	struct tm bufT {};
	char* dtNtime;
	dtNtime = (char*)malloc(60 * sizeof(char));

	now = time(NULL);
	er = localtime_s(&bufT, &now);
	er = asctime_s(dtNtime, 60, &bufT);
	return dtNtime;
}

