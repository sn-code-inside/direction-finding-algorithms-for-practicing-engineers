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
  clc; clear all;
  close all;
  DOAS =[20, -35, 30]; POWS =[1 1 1];
  numberOfPhiSamples = 360;
  phi = linspace(-180, 180, numberOfPhiSamples);
  snapShots = 128; NumOfElements = 8;

  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  [rS P rP] = newRootMu(En);
  labelRootMuNew(phi,muSpk,rS,DOAS,D,SNR,dbyl,rcA);
  rphi(:,1) = abs(rP); rphi(:,2) = angle(rP)*180/pi;
  LatexFileMatrix('roots.tex','roots of $P(z)$ Eq \ref{eq:4_30a}',rphi);



  
