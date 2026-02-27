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
[a tow snr] = synthData(N,Tau,Cycles,nSize,SNR,-90);
SNR = snr;
t = a(1,:); x1 = a(2,:); x2 = a(3,:); xf = a(4,:);
labelDelaySig(x1,x2,t,xf,Tau,SNR,N);
