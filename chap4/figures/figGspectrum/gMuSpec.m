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
function [En,muSpk,theta,doaMu,DOAS,D,delphi,snapShots,SNR] = ...
    gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std)
%[muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR] = 
%               gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std) 
%Summary of this function goes here
%   Detailed explanation goes here
  DOAS =[30, 27 -10]; POWS =[1 1 1];
    
  delphi = 360/numberOfPhiSamples;
  SamplesPerCycle = 5;
  D = 3;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doaMu En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  muSpk = muSpk/max(muSpk);
  phi = linspace(-180, 180, numberOfPhiSamples);
  phimax = 360*dbyl; theta = asind(phi/phimax);
end