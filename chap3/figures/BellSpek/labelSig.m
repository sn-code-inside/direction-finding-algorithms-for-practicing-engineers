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
function [] = labelSig(N,n,y,Delt,delt)
%[] = labelSig(N,n,y,Delt) Summary of this function goes here
%   Detailed explanation goes here
T =1:N; ind = 14;
s =round(0.1*n); e = s + 2^ind-1;
x = y(s:e); M = length(x); K=1:M; t=K*Delt;
subplot(211);plot(t,x);grid;
title(['Periodic Bell Signal $y(t)$ with $\delta t=$ ' ...
    num2str(1000*Delt,3) 'mSec or $y_k$'],'interpreter','latex');
xlabel(' $t=k\times\delta t$ in Seconds ','interpreter','latex'); 
ylabel(' $y(t)$ or $y_k$','interpreter','latex');
rectangle('Position',[s*delt -0.2 (e-s)*delt 0.4],...
    'Curvature',0.5,'EdgeColor','r','LineWidth',1,'LineStyle','-.');
% Signal Detection
xa = [(e-s)*delt*3.2 (e-s)*delt]; 
ya = [0.38 0.2];
s1 =['Detected Signal $h(t)$ or $h_k$'];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',s1,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end