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
function [] = labelApf(K,u1,u2,y,n,nI,phi,N,r)
%labelApf(K,u1,u2,y,n,nI) Summary of this function goes here
%   Detailed explanation goes here
subplot(211);
plot(K, u1(K),'o-b', K, u1(K), '.-b', K, u2(K), 'o-k', K, u2(K), '.-k',...
    K, y(K), '.-r');grid; hold on;
plot(2010+n,0,'.r','MarkerSize',14); hold off
title(['Fractional Sampling using APF for $N=$' num2str(N,3) ...
    ' Samples/Cycle' ],'interpreter','latex');
xlabel('$k$ Sample Number','interpreter','latex');
ylabel('$x^A_k,x^B_k,x^C_k$','interpreter','latex');
xticks([2010 2011 2012 2013 2014 2010+nI 2010+n 2010+nI+1]);
xticklabels({'0','1','2','3','4','5','','6'});
ind = K(11);
yticks([-0.5 u1(ind)  0.5]);
yticklabels({'-0.5','0','0.5'});
%.... xA
xa =[ind-2 ind]; ya = [0.2 u1(ind)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['input $x^A_k$ '],'color','blue',...
     'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... xC
xa =[ind+nI ind+nI]; ya = [0.4 u2(ind+nI)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['$x^A_{k-' num2str(nI) '}$'],...
    'color','blue','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%.... xB
xa =[ind+n+2 2010+n]; ya = [-0.2 0];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',['$x^A_{k-' num2str(n,3)...
    '}~\varphi$=' num2str(phi,4) '$^o$ and $r$=' num2str(r,4)],'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end