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
function [] = labelSubplot(muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR,NumOfElements,plotNum)
%labelSubplot(muSpk,theta,doa,DOAS,D) Summary of this function goes here
%   Detailed explanation goes here
  subplot(plotNum);
  plot(theta,muSpk(1,:),'.-r',theta,muSpk(2,:),'.-k',theta,muSpk(3,:),'.-b');grid;  
  [x,y] = plotPeaks(muSpk(1,:),theta,D,doa(1,:));
  hold on; plot(x',y','.-b','MarkerSize', 5,'MarkerFaceColor','b'); hold off;

  [x,y] = plotPeaks(muSpk(2,:),theta,D,doa(2,:));
  hold on; plot(x',y','.-k','MarkerSize', 2,'MarkerFaceColor','k'); hold off;

  [x,y] = plotPeaks(muSpk(3,:),theta,D,doa(3,:));
  hold on; plot(x',y','^-k','MarkerSize', 3,'MarkerFaceColor','r'); hold off;
  
  xticks([-90 -60 -30 0 30 60 90]);  
  xlabel('$\theta^\circ$','interpreter','latex');

  ylabel('$J(\theta)$','interpreter','latex');


end