clc;
clear all; close All;

D = 3; % number of emitters
DOAS = [30, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
%%%%%%%%%%%%%%%%%%%%%%%%%%%
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.5);
sz = size(Ha); m = sz(1);

kmax = 180; SE(1) = -88; SE(2) = 88;
%%%%%%% sweep beam %%%%%%%%
[Jka theta] = stfSweep(Ha,r,d_by_lambda,kmax,SE);
%%%%%%%%% plot %%%%%%%%%%%%
labelSweep(theta,Jka,m,r,d_by_lambda,maxk,D,DOAS,SNR);
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.01);
labelUla(sA,maxk,SNR,d_by_lambda,fn,D);
