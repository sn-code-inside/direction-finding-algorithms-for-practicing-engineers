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
N = 6; Tau = -5.1; Cycles = 10.0;
nSize = 1000; SNR = 25.0;
[a tow snr] = synthData(N,Tau,Cycles,nSize,SNR,-90);SNR = snr;
[wData rkdot dir det] = DetectSigWin(N,a); 
temp=sort(det); wD = temp(3:6); loopGain = temp(1:2);
dw1 = rkdot(1,:); dw2 = rkdot(2,:); rk = rkdot(4,:);
t = a(1,:); x1 = a(2,:); x2 = a(3,:); 
figure(1);
labelOrthoDet(t,x2,dw2,dw1,wD,N,SNR);
figure(2);
subplot(311);plot(t,rk,'.-b',t,0.5*x2);grid
s =['APF Pole Adaptation for $x_k$ at $f_n$ = ' ...
    num2str(1/N,3) ' with loop gain $g=$ ' num2str(loopGain(1),3) ...
    ' $i_w$= ',num2str(loopGain(2),3)];
title(s,'interpreter','latex');
ylabel('pole $r_k$','interpreter','latex');
xticks([100 200   wD(1) wD(2) wD(4)  700 800 900]);
xticklabels({'k=100','200',num2str(wD(1)),['k=' num2str(wD(2))],num2str(wD(4)),...
    '700','800','k=900'});
%.... Detected Signal
ind = wD(3); x1m = rk(ind);
xa =[t(ind+100) t(ind)]; ya = [-rk(700)*0.95 x1m];
[xaf,yaf] = ds2nfu(xa,ya); % Convert to normalized figure units
s =['$r_k$ pole of APF ' ];
hT = annotation('textarrow',xaf,yaf,'String',s,'color','red',...
    'LineStyle','-.','interpreter', 'latex');
hT.TextBackgroundColor = 'yellow';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
phiTan = (-rk*sin(2*pi/N))./(1-rk*cos(2*pi/N));
phi = 360/N - 2*atan(phiTan)*180/pi;
% %polarplot(phi*pi/180,rk,'.');
