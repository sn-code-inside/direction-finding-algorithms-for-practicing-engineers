clc;
clear all; close All;

D = 1; % number of emitters
DOAS = [40, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
swpMax = 180;
doa = linspace(-85,85,swpMax);
%for k=1:swpMax
%DOAS = [doa(k), -70, 50];
%%%%%%%%%%%%%%%%%%%%%%%%%%%
doas = doa;
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.5);
kmax = 90; se(1) = 5; se(2) = 88;
Jk = stfSweep(Ha,r,d_by_lambda,kmax,se);
