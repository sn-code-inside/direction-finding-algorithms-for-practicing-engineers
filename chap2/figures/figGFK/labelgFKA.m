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
function [] = labelgFKA(fn,peak,rcA,S,A)
%labelgFKA(fn,peak,rcA,S,A) Summary of this function goes here
%   Detailed explanation goes here
fpk = mean(fn'); fPk =[fpk' fpk'];
Pks =[peak 0*peak];
t = 0:rcA(1)-1; 
X = S(:,1); m = abs(X); f = linspace(0,1,rcA(1)); 

% In put Signals
s = fix(0.45*rcA(1)); e = fix(0.55*rcA(1));
subplot(211); plot(t(s:e),real( A(s:e,:) )+3,'.-',t(s:e),...
    imag( A(s:e,:) ),'.-');grid;
ylabel(' I and Q signals ','interpreter', 'latex');
xlabel(' ${\bf{A}}$ row number ','interpreter', 'latex');
title(' Complex ${\bf{A}}$ of $128\times 4$','interpreter', 'latex');
yticks([-1 0 1 2 3 4]);
yticklabels({'-1','0','1','-1','0','1'});
% In phase
xa = [t(s+5) t(s+5)]; 
ya = [real(A(s+10,1))+1 real(A(s+5,1))+3];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','In-Phase ${\bf{A}}$','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% Quadrature
xa = [t(s+5) t(s+5)]; 
ya = [imag(A(s+10,1))-1 imag(A(s+5,1))];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','Quadrature ${\bf{A}}$','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% x Channel 1 imag
xa = [t(s+12) t(s+10)]; 
ya = [imag(A(s+12,1))-1 imag(A(s+10,1))];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String','col 1 ${\bf{x}}$','color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
% x Channel 1 real
xa = [t(s+12) t(s+9)]; 
ya = [imag(A(s+12,1))-1 real(A(s+9,1))+3];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('arrow',xaf,yaf,'color','black','LineStyle','-.');



end