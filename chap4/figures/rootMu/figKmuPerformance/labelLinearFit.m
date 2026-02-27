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
function [] = labelLinearFit(table,doa2,rg2,doa1Mu)
%[] = labelLinearFit(table) Summary of this function goes here
%   Detailed explanation goes here
doaS = mean(doa2); rgS = mean(rg2); % static object readings
rhat  = table(1:7,4); doaHat = table(1:7,5); % radar reading for 7 positions kMUSIC
r = table(1:7,1); doaO = table(1:7,2); % true values from geometry
doa1MuHat = mean(doa1Mu);
%%%%%%%%%%%%%%%%
Xm = cosd(doaHat).*rhat ; Xs = cosd(doaS).*rgS;
Ym = sind(doaHat).*rhat ; Ys = sind(doaS).*rgS;

pR = polyfit(rhat,r,1);
rsampl = linspace(min(rhat),max(rhat),100);
rest = pR(1)*rsampl + pR(2);

pA = polyfit(doaHat,doaO,1);
Asampl = linspace(min(doaHat)*1.2,max(doaHat)*1.2,100);
Aest = pA(1)*Asampl + pA(2);


doa1MuHat = doa1MuHat + 2.4; %% what is this 2.4 deg .. bias afterwards find out ??
pB = polyfit(doaHat,doa1MuHat,1);
AsamplMu = linspace(min(doaHat)*1.2,max(doaHat)*1.2,100);
AestMu = pB(1)*AsamplMu + pB(2);

s1 = ['$\theta_{ref} = \theta_\kappa \times$' num2str(pA(1)) ' - ' num2str( abs( pA(2) ) ) ];
figure(5);
subplot(321); plot(doaHat,doaO,'bo',Asampl,Aest,'k.');grid
title(' Calibration ','interpreter','latex');
subtitle(s1,'interpreter','latex');
xlabel(' $\kappa$Music $\theta_\kappa^\circ$ ','interpreter','latex'); 
ylabel(' Reference $\theta_{ref}^\circ$ ','interpreter','latex');

% 
s1 = ['$\theta_m = \theta_\kappa \times$' num2str(pB(1)) ' - ' num2str( abs( pB(2) ) ) ];
subplot(322); plot(doaHat,doa1MuHat,'rs',AsamplMu,AestMu,'k.');grid
title(' Verification ','interpreter','latex');
subtitle(s1,'interpreter','latex');
xlabel(' $\kappa$Music $\theta_\kappa^\circ$ ','interpreter','latex'); 
ylabel(' MUSIC $\theta_m^\circ$ ','interpreter','latex');
end