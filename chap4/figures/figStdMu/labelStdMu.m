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
function [] = labelStdMu(numberOfPhiSamples,dbyl,muSpk,DOAS,D,SNR)
%[] = labelStdMu(numberOfPhiSamples,dbyl,muSpk,DOAS,D) Summary of this function goes here
%   Detailed explanation goes here
  %% label plot
  phi = linspace(-180,180,numberOfPhiSamples);
  phimax = 360*dbyl; theta = asind(phi/phimax);
  delphi = mean(diff(phi)); delth = mean(diff(theta));
  maxMu = max(muSpk);
  [pn ln] = findpeaks(muSpk); [pnV indx]=sort(pn,'descend');
  doaIndx = ln(indx(1:D)); 
  doaMuStd = theta(doaIndx); doaMuPhi = phi(doaIndx);
  doasPhi = 180*sind(DOAS(1:D));
  subplot(211); plot(phi,muSpk,'.-b');grid;
  ticksV = [-180  -45 0  30 90  135 180 doaMuPhi];
  ticksVec = round(ticksV,2);
  xticks(sort(ticksVec));
  hold on; plot(doaMuPhi,pn(indx(1:D)),'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
  s = ['Standard MUSIC $N_{mu}= ' num2str(numberOfPhiSamples,3) ...
      '~\delta\varphi=~' num2str(delphi,3) ...
      '^\circ~\delta\theta=~' num2str(delth,3) '^\circ$'];
  title(s, 'interpreter','latex');
  xlabel('$\varphi^\circ$','interpreter','latex');
  ylabel('$J(\varphi)$','interpreter','latex');


  smuphi =['$\varphi^\circ_\mu$ =[' num2str(doaMuPhi,4) ']'];
  struephi =['$\varphi^\circ$ =[' num2str(doasPhi,4) ']'];
  snew = [struephi '  ' smuphi '  SNR=' num2str(SNR,4) 'dB'];
  %subtitle(snew,"Position",[0,0],"HorizontalAlignment","center",...
  %    'color','blue','interpreter', 'latex')

  subplot(212); plot(phi,theta,'.-r');grid;
  title(snew,'color','blue','interpreter', 'latex');
  xlabel('$\varphi^\circ$','interpreter','latex');
  ylabel('$\theta^\circ$','interpreter','latex');
  ytik = [-90 -60 -30 0 30 60 90];
  yticks(ytik); xtik = round(180*sind(ytik));
  xticks(xtik);
  hold on; plot(doaMuPhi,doaMuStd,'ko','MarkerSize', ...
      4,'MarkerFaceColor','b'); hold off;

  figure(2);
  unt = 1-min(muSpk);
  rad = ones(size(phi));
  polarplot(-theta*pi/180+pi/2,muSpk+unt,'.-k',phi*pi/180,rad,'.-r');
  rticks([2 3 4]);
  thetaticks([0 30 60 90 120 150 180]);
  thetaticklabels({'90^\circ','60^\circ','30^\circ','0^\circ',...
      '-30^\circ','-60^\circ','-90^\circ'});
  hold on; 
  %% polar plot of J(theta)
  rp = pn(indx(1:D)) + unt;
  muDoa = -doaMuStd*pi/180+pi/2;
  smu =['$\theta^\circ_\mu$ =[' num2str(-muDoa*180/pi+90,4) ']'];
  strue =['$\theta^\circ$ =[' num2str(DOAS(1:D),4) ']'];
  polarplot(muDoa ,rp ,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
  subtitle([strue '  ' smu],"Position",[270,maxMu],"HorizontalAlignment","center",...
      'color','red','interpreter', 'latex')
end