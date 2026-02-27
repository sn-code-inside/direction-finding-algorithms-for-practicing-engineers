% Prony in time Domain
% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
clear all; close all; clc;
DOAS = [20, -35, 45];

POWS = [1, 1, 1];
std = 0.05;
D = 2; %m = 2*D;
snapShots = 4;
NumOfElements = 9;
dbyl = 0.5;
SamplesPerCycle = 8;
rcA = [snapShots NumOfElements];
[B SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
[doa,pole,mPoles,azimuth,mag,lambda,m]= pronyDoa(B,D);
labelProny(azimuth,mag,doa,mPoles,DOAS,D,pole,SNR,rcA,m);

