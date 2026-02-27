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
  numberOfPhiSamples = 180;
  phi = linspace(-180, 180, numberOfPhiSamples);
  snapShots = 128; NumOfElements = 8;
  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  [Jn Jt] = phiSpek(En,numberOfPhiSamples,eV);
  [P rMu,JrMu] = conjPoly(En);
  delr = 0.1; delth = 3; [B C Dr indx rDoa] = rootMusic(En,delr,delth);
  figure(1);
  labelPlot(phi,Jn,Dr,delr,DOAS,D,SNR,'311');
  text(-135,2.1,['$m=$ ' num2str(NumOfElements,3) ' and N=' num2str(snapShots,3)],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')
  figure(2);
  labelPlot(phi,Jn,C,delr,DOAS,D,SNR,'311');

  figure(3);
  sp = labelRootMu(B,DOAS,D,indx,rDoa,muSpk,SNR,snapShots,NumOfElements);

  %%%%%%%%%%% root Music %%%%%%%%%%%%%%


