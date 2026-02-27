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
function [] = labelRootMuNew(phi,muSpk,rS,DOAS,D,SNR,dbyl,rcA)
%labelRootMuNew(phi,muSpk,rS,DOAS,D,SNR) Summary of this function goes here
%   Detailed explanation goes here
  twoPiDbyl = 360*dbyl;
  theta = asind(phi/twoPiDbyl);
  poleAngle = asin(angle(rS)/pi)*180/pi; % in degrees
  muSpk = muSpk/max(muSpk);

  polarplot(-theta*pi/180+pi/2,muSpk,'.-b');
  hold on;
  polarplot(-poleAngle*pi/180+pi/2,abs(rS),'ro','MarkerSize', 3,'MarkerFaceColor','r');
  hold off;

  hold on; 
  polarplot(-poleAngle(1:2)*pi/180+pi/2,abs(rS(1:2)),'ko','MarkerSize', 5,...
      'MarkerFaceColor','r'); 
  hold off;
  thetaticks([0 30 60 90 120 150 180]);
  thetaticklabels({'90^\circ','60^\circ','30^\circ','0^\circ',...
      '-30^\circ','-60^\circ','-90^\circ'});
  
  rticks([0.5 1]);
  smu =['$\theta^\circ_{R \mu}$ =[' num2str(poleAngle(1:2)',4) ']'];
  strue =['$\theta^\circ$ =[' num2str(DOAS(1:D),4) ']'];
  [maxMu indx] = max(muSpk);
  subtitle(['Root MUSIC ' smu ' ' strue],"Position",[270,maxMu*0.4],"HorizontalAlignment","center",...
      'color','blue','interpreter', 'latex');
  sA = [' Look Matrix [' num2str(rcA) '] $\theta^\circ=[$'];
  title([sA num2str(DOAS(1:D),3) '$]~\varphi^\circ=[$' ... 
      num2str(180*sind(DOAS(1:D)),3) '$]$ at SNR ' num2str(SNR,3) 'dB'],...
      'interpreter','latex');
  % J(theta) plot
  phiJ = -theta(indx) + 90;
  xa = [phiJ+10 phiJ]*pi/180;
  ya = [muSpk(indx) muSpk(indx)];
  [xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['MUSIC Spectrum $J(\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  % Root MUSIC 
  phiR = -poleAngle(1)+90;
  xa = [phiR+10 phiR]*pi/180;
  ya = [abs(rS(1)) abs(rS(1))];
  [xaf,yaf] = polarDS2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['Root MUSIC $\theta$ ' num2str(poleAngle(1)) '$^\circ$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
end