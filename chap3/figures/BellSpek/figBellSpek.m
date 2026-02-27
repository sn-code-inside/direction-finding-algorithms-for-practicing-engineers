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
[ z,Fs ] = audioread( 'bell.wav' );
delt = 1/Fs; N = length(z);
decimate = 20; Delt = delt*decimate;
y = z(1:decimate:N); n = length(y);
ind = 14; s =round(0.1*n); e = s + 2^ind-1;
x = y(s:e); M = length(x); K=1:M;
[Pk fp t xz]=labelBell(K,Delt,x);

