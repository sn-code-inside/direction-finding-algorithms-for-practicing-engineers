clc; clear all;
close all;
%aspectRatio = 0.685;
DOAS =[20, -35, 30]; POWS=[1 1 1];
muSamples = 180;
std = 0.1; SamplesPerCycle = 8;
D = 2; snapShots = 512; NumOfElements = 4;
dbyl = 0.5;
% look matrix and gold-MUSIC
rcA =[snapShots NumOfElements];
[A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
x= A(:,1); p = x'*x/snapShots;
%[muSpk doa En eV] = gMusic(D,dbyl,muSamples,A);
%........... end of MUSIC

