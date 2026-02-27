clear all; close all;
clc;
phiD = 10;
N = 10; Tau = -8.2; Cycles = 10.0;
nSize = 1000; SNR = 20.0; control = -1;

[data tow snr]=synthData(N,Tau,Cycles,nSize,SNR,phiD); SNR = snr;
t = data(1,:); x1 = data(2,:); 
x2 = data(3,:)*1.0; data(3,:) = x2; % this check exchange with sign
x3 = data(4,:);

[wData rkDot dir detect] = DetectSigWin(N,data);
T = wData(1,:); w1 = wData(2,:); w2 = wData(3,:); 
rk1 = rkDot(1,:); rk2 = rkDot(2,:);
subplot(321);plot(t,rk1,'.-r',t,x1,'-.k');grid;
title(['col 1 amp 1 delay ' num2str(Tau*N,3)],'interpreter','latex');
subplot(322);plot(t,rk2,'.-b',t,x2,'-.k');grid;
title('col 2 is 0.5 amp','interpreter','latex');
subplot(312);plot(T,w1,'.-r',T,w2+2,'.-b');grid;
title(['detection window dir ' num2str(dir)],'interpreter','latex');
[tow shift Jk] = intDelay(N,wData,detect,control);
subplot(313);plot(T,w1-1,'.-r',T,w2+1,'.-b',T,shift+2,'.-k');grid;



