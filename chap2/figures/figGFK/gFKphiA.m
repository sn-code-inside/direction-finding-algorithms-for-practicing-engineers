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
config = zeros([1 20]);
rcA(1) = 128; rcA(2) = 4; f = 0.2; phiD = 20;
config(5) = 10; config(6) = 180.0; config(7) = rcA(1);
config(8) = config(7); config(14) = rcA(2)*2;
[S A b fn bins peak config]=gFKtst(config,[f phiD]);
load gFKobj.csv;
ngs = fix(config(15)); [A1 B1 C1 Cu Fn] = gFKeval(ngs);
labelgFKfn(fn,peak,rcA,S,b,A1,Fn);
f = gFKobj(1:ngs,2); J = gFKobj(1:ngs,1);
theta = f*2*pi;
K=1:ngs;
figure(2)
polarplot(theta*50+pi/2,J-0.8,'o-r', 'MarkerSize',4,'MarkerFaceColor','b');
rticks([0 0.2]); rticklabels({'',''});
thetaticks([0 90 180]); thetaticklabels({'f','J','-f'})





