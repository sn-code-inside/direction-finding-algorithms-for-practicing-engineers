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
  std = 1; 

  % plot 1
  snapShots = 10; NumOfElements = 32;  numberOfPhiSamples = 90;
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR(1)] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
      muSpkA(1,:) = muSpk; doaX(1,:) = doa;
      SE(1) = 15; SE(2) = 45; NumberOfSamples = 120;
      [thetaZ muSpkZ gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples);
      muSpkB(1,:) = muSpkZ; doaY(1,:) = doaMu;
  % plot 2
  snapShots = 32; %NumOfElements = 32; numberOfPhiSamples = 90;
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR(2)] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
      muSpkA(2,:) = muSpk; doaX(2,:) =doa;
      [thetaZ muSpkZ gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples);
      muSpkB(2,:) = muSpkZ; doaY(2,:) = doaMu;
  % plot 3
  snapShots = 128; %NumOfElements = 32;  numberOfPhiSamples = 90;
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR(3)] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
      muSpkA(3,:) = muSpk; doaX(3,:) = doa;
      [thetaZ muSpkZ gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples);
      muSpkB(3,:) = muSpkZ; doaY(3,:) = doaMu;

  figure(1)
  g = max(max(muSpkB'));
  labelSubplotZoom(muSpkB/g,thetaZ,doaY,DOAS,2,delphi,snapShots,SNR,NumOfElements,'311');
  sA = ['SNR =' num2str(mean(SNR),3) 'dB  m=' num2str(NumOfElements,3)]; 
  title(['Zoom between ' num2str(SE(1),2) '$^\circ$ and ' ... 
      num2str(SE(2),2) '$^\circ$' sA ... 
      ' $\theta^\circ =[$' num2str(DOAS,3) ']'],...
      'Fontsize',8,'interpreter','latex');
  legend('N=10','N=32','N=128');
  text(16,0.6,[ num2str(doaY(:,1:2),3) ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')

  figure(2)    
  labelSubplot(muSpkA,theta,doaX,DOAS,D,delphi,snapShots,SNR,NumOfElements,'311');
  sA = ['$\Delta\varphi$ =' num2str(delphi) '$^\circ$ N = [' ... 
      num2str([10 32 128]) ']'];
  title([sA '  m=' num2str(NumOfElements,3) ],'Fontsize',8,...
      'interpreter','latex');
  text(-95,1,[ num2str(doaX,3) ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')








