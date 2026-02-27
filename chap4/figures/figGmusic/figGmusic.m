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
  numberOfPhiSamples = 12;
  snapShots = 128; NumOfElements = 5;
  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  SE =[-90 90]; NumberOfSamples = 12;
  [thetaF muSpkF gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples);

  SE =[-90 90]; NumberOfSamples = 180;
  [thetaF muSpkF gJk1 doaMu1 JkMu1]=sweepFine(En,SE,NumberOfSamples);


  labelGmu(numberOfPhiSamples,dbyl,muSpk,DOAS,D,doa,SNR,JkMu,thetaF,muSpkF);
  gJkA = gJk(1,:); gJkB = gJk(2,:); sz = size(gJk); K =1:sz(2);
  figure(2);
  subplot(321); plot(K,gJkA,'.-b');grid
  mid = (max(gJkA) - min(gJkA))/2 + min(gJkA);
  ytik = round([min(gJkA) max(gJkA) mid],0);
  ytikV =sort([ytik round(gJkA(sz(2)),2)]);
  yticks(ytikV);
  title('GSU Convergence','interpreter','latex');
  xlabel('gold iteration','interpreter','latex');
  ylabel('$\theta_1$','interpreter','latex')

  subplot(322); plot(K,gJkB,'.-k');grid
  mid = (max(gJkB) - min(gJkB))/2 + min(gJkB);
  ytik = round([min(gJkB) max(gJkB) mid],0);
  ytikV =sort([ytik round(gJkB(sz(2)),2)]);
  yticks(ytikV);
  title('GSU Convergence','interpreter','latex');
  xlabel('gold iteration','interpreter','latex');
  ylabel('$\theta_2$','interpreter','latex')

