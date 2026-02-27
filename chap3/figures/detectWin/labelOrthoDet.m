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
function [] = labelOrthoDet(t,x1,dw1,dw2,wD,N,SNR)
%[] = labelDetSig(t,x1,dw1,wD,N,SNR) Summary of this function goes here
%   Detailed explanation goes here
subplot(311);plot(t,x1,'.-b',t,dw1+0.5,'.-r',t,dw2+0.5,'-.k');grid
s =[' Orthogonal Detection of $x_k$ at $f_n$ = ' ...
    num2str(1/N,3) ' Cycles/Sample and $N=$ ' num2str(N,3) '$=\frac{1}{f_n}$'];
title(s,'interpreter','latex');
ylabel('$x_k,p_k$','interpreter','latex');

xticks([100 200   wD(1) wD(2) wD(3) wD(4)  700 800 900]);
xticklabels({'k=100','200',num2str(wD(1)),['n=' num2str(wD(3)-wD(2))],'',num2str(wD(4)),...
    '700','800','k=900'});

%....Signal xk
[x1m ind] = min(x1); Ni = fix(N);
xa =[t(ind+100) t(ind+Ni)]; ya = [0.6*x1m x1(ind+Ni)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['Gaussian Pulse $x_k$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


%.... Detected Signal A
x1m = max(dw1)+0.5; ind = wD(2);
xa =[t(ind-100) t(ind)]; ya = [0.8*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['$p_k$ detection at ' num2str(wD(2),3)];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

%.... Detected Signal B
[x2m ind] = max(dw2); x2m = x2m + 0.5; %ind = wD(3);
xa =[t(ind+50) t(ind)]; ya = [0.8*x2m x2m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['Delayed ' num2str(wD(3)-wD(2),3)];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','black',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


%.... SNR
x1m = 0; ind=700;
xa =[t(ind+100) t(ind)]; ya = [0.9 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['SNR ' num2str(SNR,3) 'dB'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end