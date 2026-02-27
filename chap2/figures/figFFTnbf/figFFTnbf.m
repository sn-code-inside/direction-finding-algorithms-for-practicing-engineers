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
N = 128;
b = zeros([1 N]); 
w = linspace(-pi,pi,N); delw = w(2)-w(1);
j = 30; k = fix(w(j)/delw);    
wk = cos(2*pi*k/N) + sqrt(-1)*sin(2*pi*k/N);

a=[1 -wk]; b(1)=1/N; b(N) = -1/N;
h = freqz(b,a,w); m = abs(h);
[mV ind] = max(m);
subplot(311); plot(w,m,'.-r');grid;
xticks([-pi -3*pi/4 -pi/2 -pi/4 0 pi/4 pi/2 3*pi/4 pi]);
xticklabels({'-\pi', '-3\pi/4', '-\pi/2', '-\pi/4', '0', '\pi/4',...
    '\pi/2', '3\pi/4', '\pi'})
xlabel('$n\times \delta\omega$','interpreter','latex');
ylabel('$|H_n(\omega)|$','interpreter','latex');
title('Frequency Response of $H_n(z)$','interpreter','latex');
% FFT sliding peak
xa = [w(ind+10) w(ind)]; 
ya = [mV*0.5 mV];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['sliding DFT for $n=$ ' num2str(k,3)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';


