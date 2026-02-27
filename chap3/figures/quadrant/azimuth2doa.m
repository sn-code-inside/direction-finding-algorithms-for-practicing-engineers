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
function [thetaEst] = azimuth2doa(phi)
%[thetaEst] = azimuth2doa(phi) Summary of this function goes here
%   Detailed explanation goes here
N = 6; Tau = 8; Cycles = 10.0;
omega = 2*pi/N;
nSize = 1000; SNR = 25.0; 
control = -1; flag = 1; % apf2 orthogonal  method

kmax = length(phi);

maxTow = 8;
tauk =maxTow*sind(phi);
for k=1:kmax
Tau = tauk(k);
[a,b,c,f,par,Jkr,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
dly(k) = par(4); dlyEst(k) = par(1)/N;
val = dlyEst(k)/maxTow;
if (abs(val) > 1) val = sign(val); end;
thetaEst(k) = asind(val);
snr(k) = par(6);
end
