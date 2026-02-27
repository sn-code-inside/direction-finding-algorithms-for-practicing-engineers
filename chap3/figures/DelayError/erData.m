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
function [] = erData(pmax)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
N = 5; Tau = 1; Cycles = 10.0; Nmax = 10;
nSize = 1000; SNR = 25.0; 
control = -1; flag = 1; % apf2 orthogonal  method
kmax=100;K=1:kmax;
Nk = linspace(N,Nmax,pmax);
for p=1:pmax
N = Nk(p);
for k=1:kmax    
[a,b,c,f,par,Jkr,rkdot]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
snr(k) = par(6); lead = par(7); detect = par(8:13);
ek = par(4) - par(1);
Ek(k) = ek*ek; 
%clear a b c f par Jkr rkdot; 
end;
d(p) = mean(Ek); sn(p) = mean(snr);
end;
save("snrfn01.mat","Nk","d","sn","N","Tau","Cycles","nSize","SNR","control","flag"); 
end