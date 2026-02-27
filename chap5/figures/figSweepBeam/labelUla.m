function [] = labelUla(sA,maxk,SNR,d_by_lambda,fn,D)
%[] = labelUla(sA,maxk,SNR,d_by_lambda,fn) Summary of this function goes here
%   Detailed explanation goes here
figure(2);
K =1:maxk; sk1 = sA(1,:); sk2 = sA(2,:);
m = abs(fft(sk1))/maxk;
f = linspace(0,1,maxk);
subplot(321); plot(K,sk1,K,sk2);grid;
s1 = ['$s_k^{(1)}$ and $s_k^{(2)}$ at SNR ' num2str(SNR(1),3) 'dB'];
title([s1 ' $\frac{d}{\lambda}$ ' num2str(d_by_lambda)],'interpreter','latex');
subtitle([' Number of Signals ' num2str(D)],'interpreter','latex');
ylabel('$s_k$','interpreter','latex');

xticks([0  32 64 128 256])
subplot(323); plot(f,m);grid;
xlabel('Normalized Frequency $f_n$','interpreter','latex');
ylabel('FFT($s_k$)','interpreter','latex');
title('Narrow Band Signal', 'interpreter','latex');
[pn ln] = findpeaks(m); [pnx indx] = sort(pn,'descend');
maxPeaks = 2;
pkI = ln(indx(1:maxPeaks)); mPk = m(pkI); fPk = f(pkI);
hold on; plot(fPk,mPk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
tiks = sort([0 0.2 0.5 0.8 round(fPk,1)]);
xticks(tiks);
% peaks
num = 1;
xa = [fPk(num)+0.2 fPk(num)]; 
ya = [0.8*mPk(num) mPk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['NB at $f_p=$ ' num2str(fn,2)],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end