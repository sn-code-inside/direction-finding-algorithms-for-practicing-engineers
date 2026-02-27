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
  [pk ind] = findpeaks(muSpk);
  [pks indx] = sort(pk,'descend'); 
  Pk = pks(1:D); pksInd = ind(indx(1:D));
  X =[doa' doa']; Y =[Pk'*0 1.2*Pk'];
  subplot(plotNum);plot(theta,muSpk,'.-r');grid;  
  hold on; plot(X',Y','o-b','MarkerSize', 5,'MarkerFaceColor','b'); hold off;
  hold on; plot(theta(pksInd),Pk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
  tik = round(linspace(min(theta),max(theta),7),0);
%  xticks([-90 -60 -30 0 30 60 90]);  
  xticks(tik);  
  xlabel('$\theta^\circ$','interpreter','latex');
  sA = ['$\Delta\varphi$ =' num2str(delphi) '$^\circ$ N = ' ... 
      num2str(snapShots) ];
  title([sA '  m=' num2str(NumOfElements,3) ' at SNR ' num2str(SNR,3)],'Fontsize',8,...
      'interpreter','latex');
  ylabel('$J(\theta)$','interpreter','latex');


end