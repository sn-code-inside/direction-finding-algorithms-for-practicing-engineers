% Prony in time Domain
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
clear all; close all; clc;
ns = 2; %numb of signal sources
f=[18/360 72/360 108/360 162/360];
f=[-162/360 72/360];
[z,snr] = timeData(f,ns);
Nt = length(z);
%...................................
% take a part of the original signal
% size of the covarince matrix (m by m)
m = 2*ns;
N = 2*m-1; 
start=fix(Nt*0.6);
Kp = start:start+N-1; sk = z(Kp); 
[S,y] = covSig(sk,m,N);
H = S'*S;
p = inv(H)*S'*y';
a =[1 p']; rt = roots(a);
A(:,1) = angle(rt)*180/pi; A(:,2) = abs(rt);
w = linspace(pi,-pi,180);
h = freqz(1,a,w); m = abs(h);
f=w*180/pi;;
subplot(311); plot(f,m);grid;
