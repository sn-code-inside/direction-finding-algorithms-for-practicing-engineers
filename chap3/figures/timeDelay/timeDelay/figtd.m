clc; clear all;
close all;
N = 6; Tau = -8.4; Cycles = 10.0;
nSize = 1000; SNR = 25.0; control = -1;
[data tow snr]=synthData(N,Tau,Cycles,nSize,SNR,10);
SNR = snr;
t = data(1,:); x1 = data(2,:); x2 = data(3,:); x3 = data(4,:);
subplot(311); plot(t,x1,'.-r',t,x2,'.-b',t,x3,'.-k');grid;
title(' Delayed Signals $x_A$ and $x_B$','interpreter','latex');
[wData rkDot dir detect] = DetectSigWin(N,data);
tw = wData(1,:); x1w = wData(2,:); x2w = wData(3,:); x3w = wData(4,:);
subplot(323); plot(tw,x1w,'.-r',tw,x2w,'ob',tw,x3w,'.');grid;
title(' Detection Window $x_A$ and $x_B$','interpreter','latex');
[tow shift Jk] = intDelay(N,wData,detect,control);
subplot(324); plot(tw,x1w,'.-r',tw,x3w,'.-b',tw,shift,'.-k');grid;
[touF shiftF JkR rFine] = fineDelay(N,x2w,dir,shift);
%subplot(313); plot(tw,x3w,'.-b',tw,shift,'.-r',tw,shiftF,'ok');grid;
n = length(JkR);
r = linspace(-0.95,0.95,n);
subplot(313); plot(r,JkR,'.-r');grid;
[tow touF]
% figure(2);
% for k=1:n
% a=[1 -r(k)]; b=[-r(k) 1];
% z = filter(b,a,x3w); y = filter(b,a,z);
% ek = y - shift; JK(k) = ek*ek'/n;
% num =-r(k)*sin(2*pi/N); den = 1-r(k)*cos(2*pi/N);
% theta = 2*atan(num/den);
% phi(k) = 2*(2*pi/N - theta)*180/pi;
% plot(tw,y,'.-r',tw,shift,'.-b',tw,shiftF,'ok');grid;
% title([num2str(r(k)) '  ' num2str(Jk(k))]);
% pause;
% end

