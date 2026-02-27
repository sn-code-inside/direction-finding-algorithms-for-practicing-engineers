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
clear all; close all;

N = 30; f = 1/N; zoom = 30;
skipk = 2000; maxk = skipk+zoom;
% choose the phase angle
n = 5.6; nI = fix(n);
phi = n * 360/N; % desired phase-shift in degrees as 5.6 samples
k=1:maxk;

u1 = sin(2*pi*f*k); u2 = sin(2*pi*f*k-2*pi*nI/N);
[y r]=apf(u1, phi, 1, 1/N);
K = skipk:maxk;
labelApf(K,u1,u2,y,n,nI,phi,N,r);


