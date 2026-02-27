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
function [sp] = labelRootMu(B,DOAS,D,parts,rDoa,muSpk,SNR,snapShots,NumOfElements)
%labelPolar(B,DOAS,D,parts,rDoa,muSpk,SNR,snapShots,NumOfElements) 
% Summary of this function goes here
%   Detailed explanation goes here
 
  numberOfPhiSamples = length(muSpk);
  maxV = max(muSpk);
  phi = linspace(-180, 180, numberOfPhiSamples);
  theta = asind(phi/180);
  rVn = B(:,2); rAn = B(:,1);
  X =asind([rAn rAn]'/180); Y =[rVn*0 rVn]';
  subplot(311); plot(theta,muSpk,'.-r',X(2,:),Y(2,:),'s',...
      X,Y,'-.','MarkerSize', 4,'MarkerFaceColor','blue');grid;
  sA = ['$\frac{d}{\lambda}=0.5~\|h_p(z)\|=\|{\bf{v}}^T_p {\bf{a}}(z)\|~\theta^\circ=[$'];
  title([sA num2str(DOAS(1:D),3) '$]~\varphi^\circ=[$' ... 
      num2str(180*sind(DOAS(1:D)),3) '$]$ at SNR ' num2str(SNR,3) 'dB'],...
      'interpreter','latex');
  xlabel('$\theta^\circ$','interpreter', 'latex');
  ylabel(' root Clusters ','interpreter', 'latex');

  sz = size(parts); parts = parts + 1;
  sp= ' ';
  for k=1:sz(1)
      s = parts(k,1); e = parts(k,2);
      ar = B(s:e,1)
      ath =B(s:e,2)
      sp = rootsInpolarVec(ath,ar,sp,k)
  end
  sp =['\framebox{\begin{tabular}{ll}' sp ' \end{tabular}}'];
  text(-80,-0.8*maxV,sp,'Color','blue','interpreter','latex');
  text(-90,0.5*maxV,['$m=$ ' num2str(NumOfElements,3) ' and N=' num2str(snapShots,3)],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')
  text(40,0.5*maxV,['$root$-Music [' num2str(rDoa',3) ']$^\circ$' ],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')
  % J(theta) plot
  k = 125;
  xa = [theta(k)+10 theta(k)];
  ya = [muSpk(k) muSpk(k)];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['MUSIC Spectrum $J(\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';



end