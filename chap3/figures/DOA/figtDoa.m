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
N = 6; Tau = 8; Cycles = 10.0;
omega = 2*pi/N;
nSize = 1000; SNR = 25.0; 
control = -1; flag = 1; % apf2 orthogonal  method
thetaMax = 85;
kmax = thetaMax-1;
theta = linspace(-thetaMax,thetaMax,kmax);
maxTow = 8;
tauk =maxTow*sind(theta);
for k=1:kmax
Tau = tauk(k);
[a,b,c,f,par,Jkr,rkdot]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
dly(k) = par(4); dlyEst(k) = par(1)/N;
val = dlyEst(k)/maxTow;
thetaEst(k) = asind(val);
snr(k) = par(6);
if (k==20)
    t = a(1,:); x1 = a(2,:); x2 = a(3,:);
    snrk = snr(k); towk = tauk(k);
    thetak = theta(k); thetaEstk = thetaEst(k);
end
end
labelDoa(theta,thetaEst,snrk,N,maxTow);
labelDelaySigDoa(x1,x2,t,towk,snrk,N,thetak,thetaEstk,Cycles);

