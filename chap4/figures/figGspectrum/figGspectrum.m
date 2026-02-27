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

  % plot 1
  figure(1)
  std = 1; 
  std = 0.8;
  NumOfElements = 8;  snapShots = 32; numberOfPhiSamples = 12;
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
  labelSubplot(muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR,NumOfElements,'321');
  text(-90,0.8,['$\theta_{g\mu}^\circ=$[' num2str(doa,3) ']' ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')


  % plot 2
  std = 1;
  NumOfElements = 8;   snapShots = 32; numberOfPhiSamples = 90; 
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
      SE(1) = -15; SE(2) = 45; NumberOfSamples = 60;
      delphi = round((180*sind(SE(2)) - 180*sind(SE(1)))/NumberOfSamples,0);
      [thetaZ muSpkZ gJk doaMu JkMu]=sweepFine(En,SE,NumberOfSamples);
  labelSubplot(muSpkZ,thetaZ,doaMu,DOAS(1:D),D,delphi,snapShots,SNR,NumOfElements,'322');
  text(1.2*min(thetaZ),1.1*max(muSpkZ),['$\theta_{g\mu}^\circ=$[' num2str(doa,3) ']' ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex');



  % plot 3
  figure(2)
  NumOfElements = 32; snapShots = 32; numberOfPhiSamples = 90;
  [En,muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR] = ...
      gMuSpec(numberOfPhiSamples,snapShots,NumOfElements,std);
  labelSubplot(muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR,NumOfElements,'311');
  text(-90,0.6,['$\theta_{g\mu}^\circ=$[' num2str(doa,3) ']' ],...
      'BackgroundColor','yellow','interpreter','latex')
  text(36,0.6,['$\theta^\circ=$[' num2str(DOAS(1:D),3) ']' ],...
      'BackgroundColor','yellow','interpreter','latex')












