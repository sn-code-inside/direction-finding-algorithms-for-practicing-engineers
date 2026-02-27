clc;
clear all; close All;
D = 3; % number of emitters
DOAS = [-70  45   35]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 0.5;
%phi = 0; 
loop =80;
doa = linspace(-80,80,loop);
i=1; 
for k=1:loop    
%DOAS(1) = doa(k);
doaIn= sort(DOAS);
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise);
kmax = 80; se(1) = 5; se(2) = 85; r = 0.98;
[Jk theta doaA] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
a = doaA(1,:); b = doaA(3,:); c = doaA(5,:); 
[phi ulaPks] = map3ulaR(a,b,c);
doaOut = sort(phi);
[doaIn doaOut]
A(:,k) = phi;
end
plot(doa,A','.r');grid;


