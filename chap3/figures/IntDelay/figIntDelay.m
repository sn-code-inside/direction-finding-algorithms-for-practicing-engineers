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
%control = -2; flag = 1; % apf2 correlation method
control = -1; flag = 1; % apf2 orthogonal  method
%control = -2; flag = 2; % newAPF correlation method
%control = -1; flag = 2; % newAPF orthogonal  method
[a,wData,shift,z,par,JkR,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
SNR = par(6); %lead = par(7); detect = par(8:13);
t = a(1,:); x1 = a(2,:); x2 = a(3,:);
labelDelaySig(x1,x2,t,Tau,SNR,N);
labelIntFineDelay(wData,N,flag,shift,z,JkR,par);
figure(4);
K=1:length(Jkx);
[mJ ind] = max(Jkx);
subplot(311); plot(K,Jkx,'.-b');grid;
hold on; plot(ind,mJ,'-or','MarkerFaceColor','r','markersize',3); hold off
ylabel('$\tau_{x^Ax^B}$','interpreter','latex');
xlabel('sample number','interpreter','latex');
s =['Cross Correlation Function $\tau_{x^Ax^B}=$' ...
    'xcross($x^A_k,x^B_k$) integer delay ' num2str(ind,3)];
title(s,'interpreter','latex');
xticks([ ind  60 80 100 120]);
xticklabels({[ 'max(\tau_{x^Ax^B})= ' num2str(ind,3)], '60', '80', '100', '120'});
