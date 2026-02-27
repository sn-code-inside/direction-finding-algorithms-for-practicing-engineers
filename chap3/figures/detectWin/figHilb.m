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
clc;
clear all; close all;

kmax = 1000; fn = 0.1;
K=1:kmax; 
x=ones(1,kmax); y = x; 
s = fix(0.4*kmax); e = fix(0.6*kmax);
y(1:s) = x(1:s)*0;
y(e:kmax) = x(e:kmax)*0;
y = y + 0.1*randn(size(x));
z = hilbert(y); yH = imag(z);
subplot(311); plot(K,y,'.-r',K,yH+ 4,'.-b');grid
xlabel('$k$','interpreter','latex'); 
ylabel('$x_k$ and $x^{\frac{\pi}{2}}_k$','interpreter','latex');
title('Concept of Orthogonal Detection via Hilbert Transform','interpreter','latex');
%....Hlbert Signal xk
[x1m ind] = max(yH); x1m = x1m + 4;
xa =[K(ind-170) K(ind)]; ya = [0.85*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['$x^{\frac{\pi}{2}}_k$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

%....Signal xk
x1m = max(y);
xa =[K(ind+100) K(ind)]; ya = [1.6*x1m y(ind)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['$x_k$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

    
    
