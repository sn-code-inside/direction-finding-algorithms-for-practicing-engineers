clc;
clear all; close All;
D = 3; % number of emitters
DOAS = [40, 60, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 1; 
%% generate data STF
M = 30; m=2*M+1;
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise); snr = mean(SNR);
kmax = 180; se(1) = 12; se(2) = 85; r = 0.95;
[Jk thetaX doa] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);

%% Capon Spectrum
kmax = 180;
omega = linspace(se(1)*2*pi/180,se(2)*2*pi/180,kmax);
phi = omega*180/pi; theta = asind(phi/180);
Jk = zeros([1 kmax]);
K=1:m;
w =1 + 0.5*sin(2*pi*K/m);
%w = hanning(m);
for k=1:m
b = Ha(k,:);  
h = freqz(b.*w,1,omega); mag = abs(h);
mag = mag/max(mag);
Jk = Jk + mag;
end; 
labelCapon(theta,Jk,m,d_by_lambda,maxk,D,DOAS,SNR,thetaX,Jka);
add_signature();



