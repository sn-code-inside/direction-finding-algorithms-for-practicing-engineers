// rootMu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
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

#include "rootMu.h"
FILE* fp;
int main()
{
	int kmax = 8,k, i,p,er;
	double **clouds, closenessFactor=0.2;
//	double* inputData{};
	int rcClouds[2] = { 2,6 };
/*	double inputData[48] =
	{79.6653,  103.4811,  165.5205, -156.0946,   28.0138, -60.4103, -87.8431,  104.7930,   63.8262, -9.9015, -145.4510,
 -92.4728, -73.7320, -57.4124,  152.6081, -88.7792, -60.8933, -28.8155,  103.4346,   58.7873, -85.4747, -63.3946,
-166.2461,   26.9978,  105.3336,   71.4566,   67.7149,  123.6763,  101.9591,   10.4767, -165.9199, -49.4479, -91.9647,
-71.4737, -91.7269, -60.2723, -11.6805,   28.6251,  172.3661,  106.6102,  132.1983,  105.1105,  169.8990,  147.9384,
-130.3352, -92.8033, -61.3741,    6.0882 };*/
	double inputData[11] = { 0.3206, 0.3106 ,   0.3321  ,  0.3653  ,  0.4032  ,  0.4445  ,  0.4731  ,  0.5204  ,  0.6797  ,  2.4644  ,  3.0612 };
	int lenD = 11;
	er = fopen_s(&fp, "clusterLog.txt", "w");
//	int lenD = 100;
	int maxNumberOfPartitions = 6;
//	inputData = myAlloc(lenD);
	//for (p = 0; p < 100; p++)
	{
		//myNoise(lenD, 0.5, inputData); for (k = 0; k < lenD; k++) inputData[k] = fabs(inputData[k]);
		clouds = segment(inputData, rcClouds, lenD, maxNumberOfPartitions, closenessFactor);
		for (k = 0; k < rcClouds[0]; k++)
		{
			for (i = 0; i < 4; i++) printf("%3.4f ", clouds[k][i]); printf("\n");
		}
	}

	return 1;
}

