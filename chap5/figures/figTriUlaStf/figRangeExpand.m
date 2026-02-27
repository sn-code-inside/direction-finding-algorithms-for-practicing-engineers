clc;
clear all; close All;

D = 1; % number of emitters
DOAS = [-40, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
swpMax = 180;
doa = linspace(-85,85,swpMax);
for k=1:swpMax
DOAS = [doa(k), -70, 50];
%%%%%%%%%%%%%%%%%%%%%%%%%%%
doas = doa;
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.5);
kmax = 90; se(1) = 5; se(2) = 88;
%%%%%%% sweep beam %%%%%%%%
%[Jka theta] = stfSweep(Ha,r,d_by_lambda,kmax,se);
%[Jkb theta] = stfSweep(Hb,r,d_by_lambda,kmax,se);
%[Jkc theta] = stfSweep(Hc,r,d_by_lambda,kmax,se);
[Jk theta doaA] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
%%%%%%%%% plot %%%%%%%%%%%%
[Jkm ia] = max(Jka); [Jkm ib] = max(Jkb); [Jkm ic] = max(Jkc);
%thetaA(k) = theta(ia); thetaB(k) = theta(ib); thetaC(k) = theta(ic);
thetaA(k) = doaA(1); thetaB(k) = doaA(3); thetaC(k) = doaA(5);
end
subplot(311); plot(doa,thetaA,'-.r',doa,thetaB-60,'-.b',doa,thetaC+60,'-.k');grid;
xticks([-75 -45 -15 15 45 75]);
xticklabels({'312(32)','213(24)','123(18)','132(20)','231(28)','321(34)'});
yticks([30 60 90]);
text(-80,90,'$\theta_a$','interpreter','latex','color','r');
text(-80,40,'$\theta_c$','interpreter','latex','color','k');
text(-80,20,'$\theta_b$','interpreter','latex','color','b');
