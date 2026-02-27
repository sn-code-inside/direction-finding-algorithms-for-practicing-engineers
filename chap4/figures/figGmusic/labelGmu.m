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
function [] = labelGmu(numberOfPhiSamples,dbyl,muSpk,DOAS,D,doa,SNR,JkMu,thetaF,muSpkF)
%[] = labelStdMu(numberOfPhiSamples,dbyl,muSpk,DOAS,D,doa,SNR,thetaF,muSpkF)
% Summary of this function goes here
%   Detailed explanation goes here
  %% label plot
  phi = linspace(-180,180,numberOfPhiSamples);
  phimax = 360*dbyl; theta = asind(phi/phimax);
  delphi = mean(diff(phi)); delth = mean(diff(theta));
  maxMu = max(muSpk);
  [pn ln] = findpeaks(muSpk); [pnV indx]=sort(pn,'descend');
  doaIndx = ln(indx(1:D));
  doaMuStd = theta(doaIndx); doaMuPhi = phi(doaIndx);
  % gold start and end thetaA and B
  thetaA = theta(doaIndx(1)-1); thetaB = theta(doaIndx(1) + 1);
  muSpkA = muSpk(doaIndx(1)-1); muSpkB = muSpk(doaIndx(1) + 1);
  thetaSE =[thetaA thetaB]; muSpkSE =[muSpkA muSpkB];
  % gold ..........................
  doasPhi = 180*sind(DOAS(1:D));
  X =[doa' doa']; Y = [JkMu'*0 JkMu'];
  subplot(311); plot(theta,muSpk,'.-b',X',Y','o-r',thetaF,muSpkF,'-.k');grid;
  hold on; plot(thetaSE,muSpkSE,'o','MarkerSize',12); hold off;

  ticksV = [-90 -60  0  60 90 doa];
  ticksVec = round(ticksV,2);
  xticks(sort(ticksVec));
  hold on; plot(doaMuStd,pn(indx(1:D)),'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
  s = ['{\em gold} MUSIC $N_{mu}= ' num2str(numberOfPhiSamples,3) ...
      '~\Delta\varphi=~' num2str(delphi,3) ...
      '^\circ~\delta\theta=~' num2str(delth,3) '^\circ$ at SNR ' num2str(SNR)];
  title(s, 'interpreter','latex');
  xlabel('$\theta^\circ$','interpreter','latex');
  ylabel('$J(\theta)$','interpreter','latex');
  text(-90,2,['$\theta^\circ=$[' num2str(DOAS(1:D),3) ']' ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')

  smuphi =['$\varphi^\circ_\mu$ =[' num2str(doaMuPhi,4) ']'];
  struephi =['$\varphi^\circ$ =[' num2str(doasPhi,4) ']'];
  snew = [struephi '  ' smuphi '  SNR=' num2str(SNR,4) 'dB'];
  %subtitle(snew,"Position",[0,0],"HorizontalAlignment","center",...
  %    'color','blue','interpreter', 'latex')

  % Theta A
  xa = [thetaA thetaA];
  ya = [1.8 muSpkA+0.5];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$\theta_a$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';

  % Theta B
  xa = [thetaB thetaB];
  ya = [1.8 muSpkB+0.5];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$\theta_b$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';

  % ideal J(theta)
  ind = 123;
  xa = [thetaF(ind)+10 thetaF(ind)];
  ya = [muSpkF(ind) muSpkF(ind)];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['ideal $J(\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';



  