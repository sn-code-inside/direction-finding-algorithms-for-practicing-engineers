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
function [] = labelUla(sA,maxk,SNR,d_by_lambda,fn,DOAS)
%[] = labelUla(sA,maxk,SNR,d_by_lambda,fn) Summary of this function goes here
%   Detailed explanation goes here
K =1:maxk; sk1 = sA(1,:); sk2 = sA(2,:);
theta = atan2(sk1,sk2); r = sqrt(sk1.*sk1 + sk2.*sk2);
snr = round(SNR(1));
%% spectrum
m = abs(fft(sk1))/maxk;
f = linspace(0,1,maxk);
subplot(321); plot(f,m);grid;
xlabel('Normalized Frequency $f_n$','interpreter','latex');
ylabel('FFT($s_k$)','interpreter','latex');
title(['Narrow Band Signal $s_k$ (' num2str(maxk,3) ')'], 'interpreter','latex');
[pn ln] = findpeaks(m); [pnx indx] = sort(pn,'descend');
maxPeaks = 2;
pkI = ln(indx(1:maxPeaks)); mPk = m(pkI); fPk = f(pkI);
hold on; plot(fPk,mPk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
tiks = sort([0 0.2 0.5 0.8 round(fPk,1)]);
xticks(tiks);
text(0.2,-0.34,'Phase Shift between','interpreter','latex');
% peaks
num = 1;
xa = [fPk(num)+0.2 fPk(num)]; 
ya = [0.8*mPk(num) mPk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['NB at $f_p=$ ' num2str(fn,2)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%% polar figure
subplot(223);
polarplot(theta+pi/2,r,'-.b');
s1 = ['$s_k^{(1)}$ and $s_k^{(2)}$ at SNR ' num2str(snr,3) 'dB'];
title([s1 ' $\frac{d}{\lambda}$ ' num2str(d_by_lambda)],...
    'interpreter','latex');
subtitle([ 'Emitters at [' num2str(DOAS) ']$^\circ$' ],...
    "Position",[270,1.4],"HorizontalAlignment","center",...
    'color','blue','interpreter', 'latex')
thetaticks([0 30 60 90 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','0^o','-30^o','-60^o','-90^o'});
rticks([0.5 1]);


end