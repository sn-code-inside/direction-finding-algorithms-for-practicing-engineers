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
phiSamples = 180;
a =[(3 - 2i) 2i (1 - i)  1]; 
rT = roots(a); [x indx] = sort(abs(rT));
rA = rT(indx);

aStar = conj(flip(a));
P = conv(aStar,a); rP = roots(P);
rT = roots(P); [x indx] = sort(abs(rT));
rP = rT(indx);

  k=1;
  A = a'*a;
  for p=-3:1:3
  R(k) = sum(diag(A,p));
  k = k+1;
  end
  rT = roots(R); [x indx] = sort(abs(rT));
  rR = rT(indx);

  table = zeros([6 7]);
  table(:,1)=1:6;
  table(1:3,2) = abs(rA); table(1:3,3) = angle(rA)*180/pi;
  table(:,4) = abs(rP); table(:,5) = angle(rP)*180/pi;
  table(:,6) = abs(rR); table(:,7) = angle(rR)*180/pi;

  omega = linspace(-pi,pi,phiSamples); phi = omega*180/pi;
  mR = abs(freqz(R,1,omega)); mR = mR/max(mR);
  ma = abs(freqz(a,1,omega)); ma = ma/max(ma);
  mP = abs(freqz(P,1,omega)); mP = mP/max(mP);
  %%%%% start plotting
  subplot(211); plot(phi,ma,'.-r',phi,mR,'-+b',phi,mP,'-.k');grid;
  title(' Polynomial $Q_p(z)~R_p(z)~P_p(z)$ Evaluated over Unit Circle ','interpreter','latex');
  xlabel('$\varphi^\circ$','interpreter','latex');
  legend('$Q_p(z)$','$R_p(z)$','$P_p(z)$','Location','best','interpreter','latex');
  ylabel('$|f(z)|$','interpreter','latex');
  % Qp(phi) plot
  indx = round(0.03*length(phi));
  phiQ = phi(indx); maV = ma(indx);
  xa = [phiQ+30 phiQ];
  ya = [maV maV];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$\mathbf{v}_p^T \mathbf{a}(z)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';
  % Rp(phi) plot
  indx = round(0.8*length(phi));
  phiQ = phi(indx); maV = mR(indx);
  xa = [phiQ-30 phiQ];
  ya = [maV maV];
  [xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
  hT = annotation('textarrow',xaf,yaf,'String',...
      ['$R_p(z)$ and $P_p(z)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
  hT.TextBackgroundColor = 'yellow';



