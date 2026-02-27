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
function [] = labelPlot(phi,Jn,B,delr,DOAS,D,SNR)
%[] = labelPlot(phi,Jn,X,Y) Summary of this function goes here
%   Detailed explanation goes here
  rVn = B(:,2); rAn = B(:,1);
  X =[rAn rAn]'; Y =[rVn*0 rVn]';

  rcJn = size(Jn);
  subplot(311); plot(phi,Jn,X(2,:),Y(2,:),'s',X,Y,'-.','MarkerSize', 4,'MarkerFaceColor','blue');grid;
  for k=1:rcJn(1);
  [pn ln] = findpeaks(-Jn(k,:));
  hold on; plot(phi(ln),-pn,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
  end
  xlabel('$\varphi^\circ$','interpreter','latex');
  ylabel('$\|h_p(z)\|$','interpreter','latex');
  sA = ['$\frac{d}{\lambda}=0.5~\|h_p(z)\|=\|{\bf{v}}^T_p {\bf{a}}(z)\|~\theta^\circ=[$'];
  title([sA num2str(DOAS(1:D),3) '$]~\varphi^\circ=[$' ... 
      num2str(180*sind(DOAS(1:D)),3) '$]$ at SNR ' num2str(SNR,3) 'dB'],...
      'interpreter','latex');
  ytk = sort([0 1-delr  1+delr ceil(max(max(Jn)))]);
  yticks(ytk);
  xticks([-180 -135 -90 -45 0 45 90 135 180]);
  % Fan Beam
  [Jm indx] = max(Jn(2,:));
  xa = [phi(indx)-30 phi(indx)];
  ya = [0.7*Jm Jm];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$h(\varphi)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
end