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
%erData(100);
%load allVar;
load snrfn;
N = Nk(30); muek = mean(d)*100; mud = d*0+muek; fn = 1./Nk;
dpercentage = d*100;
sigek = std(dpercentage);
[a,b,c,f,par,Jkr,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
t = a(1,:); x1 = a(2,:); x2 = a(3,:);
%labelDelaySig(x1,x2,t,Tau,par(6),N);
[z,x,y] =pdf_y(dpercentage,15);
subplot(321); plot(fn,dpercentage,'.-r');grid;
title(['delay of  ' num2str(Tau,3) ' cycle at SNR '...
    num2str(par(6),3)],'interpreter','latex')
ylabel('\% error $E(e^2_k)$','interpreter','latex');
xlabel('Normalized Frequency $f_n$','interpreter','latex');
yticks([muek  6 12]);
yticklabels({'\mu','6','12'});
subplot(322); 
plot(x,z,'-.k',x,y,'.-b');grid; %,[muek muek],[0 0.5*max(y)],'^-k'
xlabel('\% error $e_{f_n}$','interpreter','latex');
ylabel('probability $p(e_{f_n})$','interpreter','latex');
title(['$e_{f_n}$ with $\sigma$ ' num2str(sigek,3) ...
    '\% and $\mu$ ' num2str(muek,3) '\%'],'interpreter','latex');
xticks([muek muek+sigek 8 12]);
xticklabels({'\mu','\sigma','8','12'});
