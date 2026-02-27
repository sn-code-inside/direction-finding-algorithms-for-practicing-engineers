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
function [error,N,snrk] = dlyErData(kmax)
%[] = dlyErData(kmax) Summary of this function goes here
%   Detailed explanation goes here
N = 6; Tau = 8; Cycles = 10.0;
omega = 2*pi/N;
nSize = 1000; SNR = 25.0; 
control = -1; flag = 1; % apf2 orthogonal  method
%kmax = 100;
tauk=linspace(-Tau,Tau,kmax);
j = 1;
for k=1:kmax
Tau = tauk(k);
[a,b,c,f,par,Jkr,rkdot]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
%dly(k) = par(4); dlyEst(k) = par(1);
%if ( abs(par(1) - par(4)) > 1 ) 
%    display(par(2)); 
    angleC = (rem(par(2),N)/N)*360-180;
    error(j,:) =[par(1) par(2) par(3) angleC par(4)];
    j= j+1;
%    pause; 
%end;
snr(k) = par(6);
end
snrk = mean(snr);

end