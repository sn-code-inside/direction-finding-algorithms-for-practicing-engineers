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
function [] = labelKmuAndMu(config,muS,phiSpk,p,k)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
numOfPhaseSpecSamples = config(6);
sz = size(muS);
phi = linspace(-180,180,numOfPhaseSpecSamples); theta = asind(phi/180);
mycolors =['r' 'b' 'k'];
figure(1);
subplot(311); 
plot(theta,phiSpk);grid
for k=1:sz(1)
    hold on; plot(theta,muS(k,:),['-.' mycolors(k)]); hold off;
    [pn ln] = findpeaks(muS(k,:));
    hold on; plot(theta(ln),pn,[mycolors(k) 'o'],'MarkerSize', 3,...
    'MarkerFaceColor',[mycolors(k)]); hold off;
end
s=['$\kappa$MUSIC and MUSIC Spectrum for Matrix ${\bf{A}}_' num2str(k) ...
    '$ chirp ' num2str(k) ' station ' num2str(p)];
title(s,'interpreter','latex');
xlabel(' DOA $\theta^\circ$','interpreter','latex');
ylabel([' $J_m(\theta)$ and $J_\kappa(\theta)$' ],'interpreter','latex');
% label graph MUSIC
p = 123;
xa = [theta(p+15) theta(p)]; 
ya = [muS(2,p) muS(2,p)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
      ['MUSIC Spectrum $J_m(\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

% label graph kMUSIC
p = 64;
xa = [theta(p-15) theta(p)]; 
ya = [phiSpk(1,p) phiSpk(1,p)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
      ['$\kappa$MUSIC Spectrum $J_\kappa(\theta)$'],'color',...
      'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


end