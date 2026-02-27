function [] = labelABC(theta,Jka,Jkb,Jkc,D,thetaHat,doaA,SNR,m)
%[] = labelABC(theta,Jka,Jkb,Jkc,D,thetaHat,SNR,m) Summary of this function goes here
%   Detailed explanation goes here
subplot(421); plot(theta,Jka,'-.r');grid
title([' DOA ULA(' num2str(m) ')-A at SNR ' num2str(SNR(1),3) 'dB'],...
    'interpreter','latex'); 
subtitle(['$\hat\theta = f(\theta_A,\theta_B,\theta_C)=$ ' ...
    num2str(thetaHat,3) '$^\circ$'],'interpreter','latex');
ylabel('$J_A(\theta)$','interpreter','latex');
[pn ln] = findpeaks(Jka); [pnx indx] = sort(pn,'descend');
maxPeaks = D;
pkI = ln(indx(1:maxPeaks)); JkApk = Jka(pkI); thetaPk = theta(pkI);
hold on; plot(thetaPk,JkApk,'ko','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
tiks = sort([30 60 90 round(thetaPk)]);
xticks(tiks);
% peaks
num = 1;
xa = [thetaPk(num)-10 thetaPk(num)]; 
ya = [0.7*JkApk(num) JkApk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['peak at $\theta_A=$ ' num2str(doaA(1),3) '$^\circ$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

%% plot B
subplot(423); plot(theta,Jkb,'-.b');grid
title(' DOA ULA-B','interpreter','latex'); 
ylabel('$J_B(\theta)$','interpreter','latex');
[pn ln] = findpeaks(Jkb); [pnx indx] = sort(pn,'descend');
pkI = ln(indx(1:maxPeaks)); JkApk = Jkb(pkI); thetaPk = theta(pkI);
hold on; plot(thetaPk,JkApk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
tiks = sort([30 60 90 round(thetaPk)]);
xticks(tiks);
% peaks
num = 1;
xa = [thetaPk(num)+10 thetaPk(num)]; 
ya = [0.7*JkApk(num) JkApk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['peak at $\theta_B=$ ' num2str(doaA(3),3) '$^\circ$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

%% plot C
subplot(425); plot(theta,Jkc,'-.k');grid
title(' DOA ULA-C','interpreter','latex'); 
ylabel('$J_C(\theta)$','interpreter','latex');
[pn ln] = findpeaks(Jkc); [pnx indx] = sort(pn,'descend');
pkI = ln(indx(1:maxPeaks)); JkApk = Jkc(pkI); thetaPk = theta(pkI);
hold on; plot(thetaPk,JkApk,'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
tiks = sort([30 60 90 round(thetaPk)]);
xticks(tiks);
xlabel(' Angle in Degrees ','interpreter', 'latex');
% peaks
num = 1;
xa = [thetaPk(num)+10 thetaPk(num)]; 
ya = [0.7*JkApk(num) JkApk(num)];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'String',...
    ['peak at $\theta_C=$ ' num2str(doaA(5),3) '$^\circ$'],'color',...
    'black','LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

end