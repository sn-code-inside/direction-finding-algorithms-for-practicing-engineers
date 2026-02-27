// citeSeq.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "citeSeq.h"
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
int main(int argc, char* argv[])
{
    char* refIn,*refOut,*citeSeq;
	int flag;
	int maxFileName = 30;

    if (argc != 3) {
		printf("!. number of arguments %d\n", argc);
        printf("Usage: citeSeq refIn.tex citeseq.txt \n");
        return 1; // Indicate error
    }
	refOut = (char*)malloc(maxFileName * sizeof(char));
	strcpy_s(refOut, maxFileName, "refchapNew.tex");
	refIn = (char*)malloc(maxFileName * sizeof(char));

	strcpy_s(refIn, maxFileName, argv[1]);
	citeSeq = (char*)malloc(maxFileName * sizeof(char));

	strcpy_s(citeSeq, maxFileName, argv[2]);
	printf("1. citation sequence file %s\n", citeSeq);
	printf("2. reference file %s\n", refIn);
	printf("3. New Reference file refchapNew.tex\n");
	flag = citeOrder(refIn, refOut, citeSeq);
    return 0;
}



