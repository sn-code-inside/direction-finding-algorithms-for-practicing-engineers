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
function [] = labelCalibrate(K,doa2,rg2)
%labelCalibrate(K,rg2,doa2) Summary of this function goes here
%   Detailed explanation goes here
sigDoa = std(doa2); minMaxSigDoa = [min(sigDoa) max(sigDoa)];
sigR = std(rg2); minMaxSigR =[min(sigR) max(sigR)]*1000;
% Calibrate
figure(2)
s1 =['$\sigma_{\theta_\kappa}$ = [' num2str(minMaxSigDoa) ']$^\circ$'];
subplot(321); plot(K,doa2);grid
title(' Calibration Tgt DOA $\theta_\kappa$','interpreter','latex'); 
subtitle(s1,'interpreter','latex');
ylabel(' $\theta^\circ_\kappa$ ','interpreter','latex');
xlabel(' Radar Chirps ','interpreter','latex');

% subplot
s1 =['$\sigma_r$ = [' num2str(minMaxSigR) '] mm'];
subplot(322); plot(K,rg2*100);grid
title(' Calibration Tgt Range $r$','interpreter','latex');
subtitle(s1,'interpreter','latex');
ylabel(' $r_{i=1,7}$ in cm ','interpreter','latex');
xlabel(' Radar Chirps ','interpreter','latex');

end