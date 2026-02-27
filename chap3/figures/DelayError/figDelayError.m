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
close all; clear all;
%kmax = 483; [error N SNR]= dlyErData(kmax);
load dlyEr;
dly = error(:,5); del = error(:,4); dlyEst = error(:,1);
ek = (dlyEst-dly);
p = polyfit(dlyEst,dly,1);
dlyHat = p(1)*dlyEst + p(2);
ek = (dlyHat-dly)*360/N;
muek = mean(ek); sigek = std(ek);
if (abs(muek) < 1e-5) muek = 0; end;
[z,x,y]=pdf_y(ek,40);
subplot(311);plot(dlyEst/N,dly/N,'ob','markersize',3);grid; hold on;
plot(dlyHat/N,dly/N,'.-r');hold off;
xlabel('delay $\hat{\tau}$ cycles','interpreter','latex');
ylabel('True delay ${\tau}$','interpreter','latex');
legend('$\tau$','$\tilde{\tau}$','Location','west','interpreter','latex');
s = [' ${\tilde\tau}=$ ' num2str(p(1),5) '$\hat{\tau}-$ ' ...
    num2str(abs(p(2)),3) 'at SNR ' num2str(SNR,3) ...
    'dB ' num2str(N,3) ' samples/cycle'];
title(s,'interpreter','latex');
dlyHatCycl = dlyHat/N;
subplot(323);plot(dlyHatCycl,ek);grid;
ylabel('$\varphi$ Error $e=\tau - \tilde{\tau}$','interpreter','latex');
xlabel('delay $\hat{\tau}$ cycles','interpreter','latex');
yticks([-25 -sigek sigek 25]);
yticklabels({'-25', '-\sigma', '\sigma', '25'});
%.... Outlier
[ekm ind] = max(ek);
xa =[dlyHatCycl(ind-60) dlyHatCycl(ind)]; ya = [0.8*ekm ekm];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['One Sample Oulier'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';

subplot(324);plot(x,y,'.-r',x,z,'-.b');grid;
ylabel('probability of $e$','interpreter','latex');
xlabel('phase $\varphi$ error','interpreter','latex');
s=['PDF $\mu$ ' num2str(muek,3) ' and $\sigma$ ' num2str(0.5*sigek,3) '$^\circ$'];
title(s,'interpreter','latex');
xticks([-25 -sigek 0 sigek 25]);
xticklabels({'-25','-\sigma','','\sigma','25'});
%.... Normal Distribution
ind=19; x1m = z(ind);
xa =[x(ind+8) x(ind)]; ya = [0.8*x1m x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s = ['$N(\mu,\sigma^2)$'];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','blue',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
