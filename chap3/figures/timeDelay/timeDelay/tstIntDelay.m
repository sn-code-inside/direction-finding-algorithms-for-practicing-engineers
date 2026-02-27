clc; clear all;
close all;
N = 6; Tau = -8.4; Cycles = 10.0;
nSize = 1000; SNR = 25.0;
control = 2;
[x,y,tw,Jk,t,x1,x2,rkdot,detect] = intWaves(N,Tau,Cycles,nSize,SNR,control);
[touF z JkR rFine] = fineDelay(N,x,dir,y);
dw1 = rkdot(1,:); dw2= rkdot(2,:);
r1 = rkdot(3,:); r2 = rkdot(4,:);
rSweep = linspace(-0.95,0.95,length(JkR));
K=1:length(Jk);
subplot(311);plot(t,x1,'.-b',t,x2,'.-r',t,dw1,'.-b',t,dw2,'.-r');grid
%subplot(311);plot(t,dw1,'.-b',t,dw2,'.-r');grid
subplot(312);plot(t,r1,'.-r',t,r2,'.-b');grid;
subplot(313);plot(rSweep,JkR,'.-k');grid



