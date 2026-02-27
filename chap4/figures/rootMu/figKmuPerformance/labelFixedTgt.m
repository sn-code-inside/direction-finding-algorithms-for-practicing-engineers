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
function [] = labelFixedTgt(K,doa1,rg1)
%labelFixedTgt(K,doa1,rg1) Summary of this function goes here
%   Detailed explanation goes here
figure(3)
doaS = mean(doa1); d2 = [min(doaS) max(doaS)];
rgS  = mean(rg1)*100; r2 = [min(rgS) max(rgS)];
s1 =['$\Delta\theta$ = [' num2str(d2(2)-d2(1)) ']$^\circ$'];
subplot(321); plot(K,doa1);grid
title(' Reference Tgt DOA $\theta$','interpreter','latex'); 
subtitle(s1,'interpreter','latex');
ylabel(' $\theta^\circ$ ','interpreter','latex');
xlabel(' Radar Chirps ','interpreter','latex');

% fixed range
s1 =['$\Delta r$ = [' num2str((r2(2)-r2(1))*10) '] mm'];
subplot(322); plot(K,rg1*100,200,90.25);grid
title(' Reference Tgt Range $r$','interpreter','latex');
subtitle(s1,'interpreter','latex');
ylabel(' Centimeters ','interpreter','latex');
xlabel(' Radar Chirps ','interpreter','latex');;

end