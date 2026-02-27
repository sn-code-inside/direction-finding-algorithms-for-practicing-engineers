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
r = 0.95; fn = 0.1;
theta = fn*360;
p = 2*cosd(theta); g=(1-r*r)/2;
b =g*[1 0 -1]; a=[1 -r*p r*r]; 
w =linspace(0,pi,180); f = w/(2*pi);
h = freqz(b,a,w); m = abs(h);
[mp indx] = max(m);
X =[f(indx) f(indx)]; Y =[0 mp];
subplot(311);plot(f,m,'.-r');grid;hold on;
plot(X,Y,'ob','MarkerSize',3,...
    'MarkerFaceColor','b'); hold off;
ylabel('$|H(z)|$','interpreter','latex');
xlabel('$f_n$ Normalized Frequency $\frac{\omega}{2\pi}$','interpreter','latex');
title(['$r=$' num2str(r) ' $p=$' num2str(p) ' $g=$' num2str(g)],...
    'interpreter','latex');
% Frequency Response of H(z)
s =['Frequency Response of $H(z)=\frac{g(1-z^{-2})}{(1-rpz^{-1} + r^2z^{-2})}$'];
xa = [f(indx+20) f(indx+10)]; 
ya = [mp*0.5 m(indx+10)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    s,'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

