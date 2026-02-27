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
function [SDE,sNr,p,thetak,doa,delPhi,NumOfElements,SamplesPerCycle] = gMuStd(stdx,snapShots)
%[SDE,sNr,p,thetak,doa,delPhi,NumOfElements,SamplesPerCycle] = gMuStd(stdx) Summary of this function goes here
%   Detailed explanation goes here
  DOAS =[20]; POWS =[1 1 1];
  numberOfPhiSamples = 18; delPhi = 360/numberOfPhiSamples;
   NumOfElements = 5;
  SamplesPerCycle = 8;
  D = 1;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  k=1;
  for theta=-60:1:60
  DOAS(1) = theta;   
  [A SNR(k)] = IQmatrix(DOAS,stdx,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa(k) En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  thetak(k) = theta;
  k=k+1;
  end
  p = polyfit(doa,thetak,1);
  er = thetak - doa;
  sNr = mean(SNR);
  SDE = std(er);
end