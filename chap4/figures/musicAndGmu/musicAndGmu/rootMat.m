function [muSpk,En,doa,A,eV] = rootMat(D ,NumOfElements,DOAS,muSamples)
% Summary of this function goes here
% [muSpk,En] = rootMat(D ,NumOfElements,DOAS)  Detailed explanation goes here
std = 1; SamplesPerCycle = 8;
snapShots = 128;
dbyl = 0.5;
% look matrix and gold-MUSIC
rcA =[snapShots NumOfElements];
[A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle);
[muSpk doa En SNR eV] = gMusic(D,dbyl,muSamples,A);
end