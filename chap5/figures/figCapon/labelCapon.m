function [] = labelCapon(theta,Jka,m,d_by_lambda,maxk,D,DOAS,SNR,thetaX,JkX)
%labelSweep(theta,Jka,m,r,d_by_lambda,maxk,D,DOAS) Summary of this function goes here
%   Detailed explanation goes here
subplot(311); plot(theta,Jka,'b',thetaX,JkX*2,'-.r');grid;
[pn ln] = findpeaks(Jka); [pnx indx] = sort(pn,'descend');
maxPeaks = 7;
pkI = ln(indx(4:maxPeaks)); JkApk = Jka(pkI); thetaPk = theta(pkI);
hold on; plot(thetaPk,JkApk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
tiks = sort([0 round(thetaPk)]);
xticks(tiks);
s1 = ['Capon Spectrum for $m=$ ' num2str(m) ];
title([s1 ' ULA $\frac{d}{\lambda}$ ' num2str(d_by_lambda)],'interpreter','latex');
s2 = ['Emitters at [' num2str(DOAS) ']$^\circ$'];
subtitle([s2 ' snap shots ' num2str(maxk) ' at SNR ' ...
    num2str(SNR(1),3) 'dB'],'interpreter','latex');
xlabel('$\theta^\circ$','interpreter','latex');
ylabel('$J(\theta)$','interpreter','latex');
legend('Capon Spectrum','STF (Kaluri Method)','Capon Peaks','location','best','interpreter','latex');
% peaks
num = 4;
xa = [thetaPk(num)+15 thetaPk(num)]; 
ya = [1.5*JkApk(num) JkApk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['Peaks ${\bf{a}}^{*T}(z){\bf H}{\bf{a}}(z)$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
end
