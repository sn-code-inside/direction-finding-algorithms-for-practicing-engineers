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
function [] = labelSubplotZoom(muSpk,theta,doa,DOAS,D,delphi,snapShots,SNR,NumOfElements,plotNum)
%labelSubplot(muSpk,theta,doa,DOAS,D) Summary of this function goes here
%   Detailed explanation goes here
  subplot(plotNum);
  plot(theta,muSpk(1,:),'r',theta,muSpk(2,:),'k',theta,muSpk(3,:),'b');grid;  
  [x,y] = plotPeaks(muSpk(1,:),theta,D,doa(1,1:D));
  hold on; plot(x',y','o-r','MarkerSize', 5,'MarkerFaceColor','r'); hold off;

  [x,y] = plotPeaks(muSpk(2,:),theta,D,doa(2,1:D));
  hold on; plot(x',y','s-k','MarkerSize', 5,'MarkerFaceColor','k'); hold off;

  [x,y] = plotPeaks(muSpk(3,:),theta,D,doa(3,1:D));
  hold on; plot(x',y','^-b','MarkerSize', 5,'MarkerFaceColor','b'); hold off;
  
  xticks([10 15 20 25 30 35 40 45]);  
  xlabel('$\theta^\circ$','interpreter','latex');
  %sA = ['$\Delta\varphi$ =' num2str(delphi) '$^\circ$ N = ' ... 
  %    num2str(snapShots) ];
  %title([sA '  m=' num2str(NumOfElements,3) ],'Fontsize',8,...
  %    'interpreter','latex');
  ylabel('$J(\theta)$','interpreter','latex');


end