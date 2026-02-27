clc;
clear all; close All;

D = 1; % number of emitters
DOAS = [-40, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
swpMax = 92;
doa = linspace(-80,80,swpMax);
for k=1:swpMax
DOAS = [doa(k), -70, 50];
%%%%%%%%%%%%%%%%%%%%%%%%%%%
doas = doa;
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.5);
kmax = 80; se(1) = 5; se(2) = 85;
%%%%%%% sweep beam %%%%%%%%
[Jka theta] = stfSweep(Ha,r,d_by_lambda,kmax,se);
[Jkb theta] = stfSweep(Hb,r,d_by_lambda,kmax,se);
[Jkc theta] = stfSweep(Hc,r,d_by_lambda,kmax,se);
%%%%%%%%% plot %%%%%%%%%%%%
[Jkm ia] = max(Jka); [Jkm ib] = max(Jkb); [Jkm ic] = max(Jkc);
thetaA(k) = theta(ia); thetaB(k) = theta(ib); thetaC(k) = theta(ic);
v =[thetaA(k) thetaB(k) thetaC(k)];
[phi(k) zone(k)] = map3ula(v); 
end

subplot(311); plot(doa,thetaA,'-.r',doa,thetaB,'-.b',doa,thetaC,'-.k',doa,zone,'.-c');grid;
xlabel('zones','interpreter','latex');
xticks([-75 -45 -15 15 45 75]);
xticklabels({'32','24','18','20','28','34'});
subplot(312); plot(doa,phi,'.-r');grid;
