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
labelSig(N,n,y,Delt,delt);

