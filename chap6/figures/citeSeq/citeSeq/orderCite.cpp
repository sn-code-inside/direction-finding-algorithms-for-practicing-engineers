#include "orderCite.h"
FILE* fpRefOut;
FILE* fpRef;
FILE* fpKey;
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

int citeOrder(char *refIn, char *refOut, char *citeseq)
{
	char* refFile, * citeSeqFile, * pt, * refOutFile;
	int k, flag, fEr;
	unsigned char val = 10, oldval = 13;
	int maxFileName = 30;
	int* lineBib, s, e, i,  matchFlag = 0;

	char** A, ** B;
	int r = 100; int c = 20;
	int rMax = 0, keyMax = 0, maxlines;

	refOutFile = (char*)malloc(maxFileName * sizeof(char));
	strcpy_s(refOutFile, maxFileName, refOut);
	fEr = fopen_s(&fpRefOut, refOutFile, "w");
	if (fpRefOut == NULL) {
		printf("!. Error opening file %s(%d)\n", refOutFile, fEr);
		fclose(fpRefOut);
		return -1;
	}
	printf("!. opened file %s for outputting\n", refOutFile);
	//  two dimensional charcters
	A = (char**)malloc(r * sizeof(char*));
	for (k = 0; k < r; k++)
	{
		A[k] = (char*)malloc(c * sizeof(char));
	}
	lineBib = (int*)malloc(r * sizeof(int));
	refFile = (char*)malloc(maxFileName * sizeof(char));
	strcpy_s(refFile, maxFileName, refIn);
	rMax = passA(refFile, A, lineBib, &maxlines);
	//	......... references
	for (k = 0; k < rMax; k++)
	{
		printf("[%d]%s\n", lineBib[k], A[k]);
	}


	B = (char**)malloc(r * sizeof(char*));
	for (k = 0; k < r; k++)
	{
		B[k] = (char*)malloc(c * sizeof(char));
	}
	//
	//.............. cite sequence .............
	citeSeqFile = (char*)malloc(maxFileName * sizeof(char));
	strcpy_s(citeSeqFile, maxFileName, citeseq);
	keyMax = getKey(citeSeqFile, B);
	//for (k = 0; k < keyMax; k++) 	printf("[%d]%s\n", k, B[k]);


	fprintf(fpRefOut, "\\begin{thebibliography}{99}\n");
	fprintf(fpRefOut, "%% Copy Right Dr Kaluri Venkata Ranga Rao email: kaluri@ieee.org\n");
	fprintf(fpRefOut, "%% Visiting Scholar, Department of Computer Science, ICDT\n");
	fprintf(fpRefOut, "%% Ohio State University, Ohio\n");
	fprintf(fpRefOut, "%% For my Book Direction Finding Algorithms Springer Nature NY\n");
	fprintf(fpRefOut, "%% 9th Jul 2025\n");
	for (i = 0; i < keyMax; i++)
	{
		//printf("%% trying to match %s  ", B[i]);
		for (k = 0; k < rMax; k++)
		{
			if (strlen(B[i]) > 0)
			{
				//printf("match %s with %s[%d]\n", A[k], B[i],strlen(B[i]));
				pt = strstr(A[k], B[i]);
				if (pt)
				{
					s = lineBib[k];
					if (k + 1 < rMax) e = lineBib[k + 1]; else e = maxlines - 1;
					//printf("%% [%d][%d][%d] match %s\n", k, s, e, A[k]);
					fprintf(fpRefOut, "\n%% [%d] match %s\n", k, A[k]);
					flag = lineA2B(refFile, s, e);
					//printf("%% -----------------------\n");
					matchFlag = 1; break;
				}
				else matchFlag = -1;
			}
		}
		if (matchFlag < 0) { fprintf(fpRefOut,"\n%% [%d] match failed %s\n",i, B[i]); }
	}
	fprintf(fpRefOut, "\\end{thebibliography}\n");
	fclose(fpRefOut);
	fclose(fpRef);
	fclose(fpKey);
	return 1;
}


int getLine(unsigned char* val, unsigned char* oldval, char* line, int* K)
{
	int k;
	int cr = 13, lf = 10;
	k = K[0];
	if (val[0] != cr)
	{
		if (val[0] != lf)
			line[k] = val[0];
		k = k + 1; K[0] = k;
	}
	if (oldval[0] == cr && val[0] == lf)
	{
		line[k - 1] = 0; k = 0; K[0] = k;
		return 1;
	}
	else
	{
		K[0] = k;
		return -1;
	}
}

int passA(char* refFile, char** A, int* lineBib, int* maxlines)
{
	int k, indxA;
	unsigned char val = 10, oldval = 13;
	int flag = 0, endOfLine = -1, lineMax = 500;
	size_t lineLength;
	char* line;
	int maxLine = 600, fEr;
	int linekt = 1;

	line = (char*)malloc(maxLine * sizeof(char));

	fEr = fopen_s(&fpRef, refFile, "rb");
	if (fpRef == NULL) {
		printf("!. Error opening file %s(%d)\n", refFile, fEr);
		return -1;
	}
	printf("!. opened file %s for reading\n", refFile);

	k = 0; indxA = 0;
	while (!(feof(fpRef)))
	{
		oldval = val;
		val = fgetc(fpRef);
		endOfLine = getLine(&val, &oldval, line, &k);
		if (k > lineMax)
		{
			printf(".\n.\n---------------------------------------------------------------------\n");
			printf(" FATAL ERROR CONDITION\n");
			printf(" could not find CR LF in the line .. file check the input file--> %s\n", refFile);
			printf("---------------------------------------------------------------------\n.\n.\n");
			fclose(fpRef);
			return -1;
		}
		if (endOfLine > 0)
		{
			lineLength = strlen(line);
			if (lineLength > 0)
			{
				flag = processLineForMatch(line, A, lineBib, indxA, linekt);
				if (flag > 0) indxA = indxA + 1;
				printf("[%d][%d]%s\n", (int)(lineLength), linekt, line);
				linekt = linekt + 1;
			}
		}
	}
	maxlines[0] = linekt;
	fclose(fpRef);
	printf("!. closed file %s after reading reading\n", refFile);

	return indxA;
}

int lineA2B(char* refFile, int s, int e)
{

	int k, indxA;
	unsigned char val = 10, oldval = 13;
	int percentage = 37;
	int flag = 0, endOfLine = -1, lineMax = 500;
	int startFlag = -1, endFlag = -1, printFlag = 0;
	char* line;
	int maxLine = 600, fEr;
	int linekt = 1;

	line = (char*)malloc(maxLine * sizeof(char));

	fEr = fopen_s(&fpRef, refFile, "rb");
	if (fpRef == NULL) {
		printf("!. Error opening file %s(%d)\n", refFile, fEr);
		return -1;
	}
	printf("!. opened file %s for reading\n", refFile);
	k = 0; indxA = 0;
	while (!(feof(fpRef)))
	{
		oldval = val;
		val = fgetc(fpRef);
		endOfLine = getLine(&val, &oldval, line, &k);
		if (k > lineMax)
		{
			printf(".\n.\n---------------------------------------------------------------------\n");
			printf(" FATAL ERROR CONDITION\n");
			printf(" could not find CR LF in the line .. file check the input file--> %s\n", refFile);
			printf("---------------------------------------------------------------------\n.\n.\n");
			fclose(fpRef);
			return -1;
		}
		if (endOfLine > 0)
		{
			if (strlen(line) > 0)
			{
				if (line[0] != percentage)
				{
					if (s - linekt <= 0)  startFlag = 1;
					if (e - linekt <= 0)  endFlag = 1;
					printFlag = startFlag + endFlag;
					if (printFlag == 0)
						fprintf(fpRefOut, "%s\n", line);  

				}
				linekt = linekt + 1;
			}
		}
	}
	fclose(fpRef);
	printf("!. closed file %s after reading reading\n", refFile);
	return 1;

}

int processLineForMatch(char* line, char** A, int* lineBib, int indxA, int linekt)
{
	int percentage = 37, flag = 0, k;
	char* pt;
	size_t lengthPt;
	char strbib[] = "\\bibitem{";
	if (strlen(line) > 0)
	{
		if (line[0] != percentage)
		{
			pt = strstr(line, strbib);
			if (pt)
			{
				lengthPt = strlen(pt);
				for (k = 0; k < 30; k++) A[indxA][k] = pt[k];
				A[indxA][k] = 0;
				lineBib[indxA] = linekt;
				flag = 1;
			}
			else flag = -1;
		}
	}
	return flag;
}

int getKey(char* citeSeqFile, char** A)
{
	int k, indxA, i, p;
	unsigned char val = 10, oldval = 13;
	int flag = 0, endOfLine = -1, lineMax = 500;
	char* line;
	int maxLine = 600, fEr;
	int linekt = 1;

	line = (char*)malloc(maxLine * sizeof(char));

	fEr = fopen_s(&fpKey, citeSeqFile, "rb");
	if (fpRef == NULL) {
		printf("!. Error opening file %s(%d)\n", citeSeqFile, fEr);
		return -1;
	}
	printf("!. opened file %s for reading cite sequence\n", citeSeqFile);
	k = 0; indxA = 0;
	while (!(feof(fpKey)))
	{
		oldval = val;
		val = fgetc(fpKey);
		endOfLine = getLine(&val, &oldval, line, &k);
		if (k > lineMax)
		{
			printf(".\n.\n---------------------------------------------------------------------\n");
			printf(" FATAL ERROR CONDITION\n");
			printf(" could not find CR LF in the line .. file check the input file--> %s\n", citeSeqFile);
			printf("---------------------------------------------------------------------\n.\n.\n");
			fclose(fpRef);
			return -1;
		}
		if (endOfLine > 0)
		{
			if (strlen(line) > 0)
			{
				p = 0;
				for (i = 0; i < 10; i++)
				{
					if (line[i] != 32) // remove blanks
					{
						A[indxA][p] = line[i];
						p = p + 1;
					}
				}
				A[indxA][p] = 0;
				indxA = indxA + 1;
				linekt = linekt + 1;
			}
		}
	}
	fclose(fpRef);
	printf("!. closed file %s  cite sequence\n", citeSeqFile);

	return indxA;
}
