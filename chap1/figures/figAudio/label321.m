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

function [] = label321(samples,fs,B,dbyl)
%[] = label321(samples,fs,B,dbyl) 
%   Summary of this function goes here
%   Detailed explanation goes here
u = B(:,1); delt = 1/fs; 


figure(1);
% spectrum and time series
f = linspace(0,1,samples); su = abs(fft(u)); t = 0:samples-1;
subplot(321); plot(t*delt*1000,real(B));grid;
xticks([5 10 15]); xticklabels({'5mS','10','15mS'});
%xlabel(' milli-seconds ','interpreter','latex');
ylabel(' Amplitude ','interpreter','latex');
title(' NB filtered audio @ 1khz ','interpreter','latex');
%text(4,.015,' NB filtered audio @ 1khz ','interpreter','latex');
% arrow for Audio
xa(2) = 2;   xa(1) = 5;
ya(2) = 0; ya(1) = 0.011;
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String', ... 
[' 6 ULA Time Series '],...
'Interpreter','latex','color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';

% .... spectrum ........
subplot(322); plot(f*fs/1000,su);grid;
%xlabel(' KhZ ','interpreter','latex');
ylabel(' Amplitude ','interpreter','latex');
title(' Fourier Spectrum ','interpreter','latex');
xticks([1 5 10 15 20]);
xticklabels({'1khz','5','15','20khz'});
text(14,2.7,[' $\frac{d}{\lambda}$ = ' num2str(dbyl,2)],'interpreter','latex');
% .. position image 
axes('pos',[.01 .72 1.48 .16]); %lower left corner (0.065 0.65) and width and height (1.4,0.27)
imshow('ulaAu6.jpg');
end