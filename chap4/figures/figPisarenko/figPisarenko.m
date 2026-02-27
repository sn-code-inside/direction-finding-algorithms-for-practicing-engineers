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
DOAS = [20, -35, 45];

POWS = [1, 1, 1];
std = 1;
D = 2; %m = 2*D;
snapShots = 4;
NumOfElements = 8;
dbyl = 0.5;
SamplesPerCycle = 8;
rcA = [snapShots NumOfElements];
[A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
N = NumOfElements; m=round(N/2);
sk = A(1,:); R = covSig(sk,m,N);
[u,lambda] = mysvd(R);
Emin = u(:,4); rt = roots(Emin);
w = linspace(pi,-pi,180);
h = freqz(1,Emin,w); mag = abs(h);
phi = w*180/pi; theta = asind(phi/180);
pole = abs(rt); 
polephi = angle(rt)*180/pi;
doa=asind(polephi/180);
subplot(311); %plot(theta,mag);grid
%hold on; 
stem(doa,pole,'o'); 
%hold off;
