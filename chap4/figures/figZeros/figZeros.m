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
omega = 30; omg = omega*pi/180; r = 0.95; 
b =[1 -(r+1/r)*exp(i*omg) exp(2*i*omg)];
w = linspace(-pi,pi,180); phi = w*180/pi;
h = freqz(b,1,w); m = abs(h); 
X =[omega omega]; Y=[0 r]; Y1 =[0 1/r];
hi = freqz(1,b,w); mi = abs(hi);
Yi=[0 max(mi)];
subplot(321);plot(phi,m,'k');grid;
hold on; plot(X,Y,'-.o','MarkerSize', 2,'MarkerFaceColor','r'); hold off;
hold on; plot(X,Y1,'-.o','MarkerSize', 5,'MarkerFaceColor','b'); hold off;
s =['$h(z) = (1-re^{j\varphi_c}z^{-1})(1-\frac{1}{r}e^{j\varphi_c}z^{-1})$'];
s1 =['$J(\varphi)=\frac{1}{|h(z)|}~r=$' num2str(r,2)...
    ' and $\varphi_c=$' num2str(omega,2) '$^\circ$'];
title(s,'interpreter','latex');
ylabel('$|h(z)|$','interpreter','latex');
yticks([0 1 2 3]);
xlabel('$\varphi^\circ$','interpreter','latex');
xticks([-180 -90 0 omega 90 180]);
subplot(322);plot(phi,mi,'.-r');grid;
title(s1,'interpreter','latex');
ylabel('$J(\varphi)$','interpreter','latex');
xlabel('$\varphi^\circ$','interpreter','latex');
xticks([-180 -90 0 omega 90 180]);
% J(w) peak
xa = [omega-40 omega]; 
ya = [0.7*max(mi) max(mi)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['$J(\varphi)$ peak ' num2str(omega,3) '$^\circ$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
