function [] = logicFor3(s,annotation)
%[] = logicFor3 Summary of this function goes here
%   Detailed explanation goes here
D = 1; % number of emitters
DOAS = [-40, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
swpMax = 180;
doa = linspace(-85,85,swpMax);
%%
for k=1:swpMax
DOAS = [doa(k), -70, 50];
%%%%%%% ULA output %%%%%%%%
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,0.5);
kmax = 90; se(1) = 5; se(2) = 88;
%%%%%%% sweep beam %%%%%%%%
[Jk theta doax] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
thetaA(k) = doax(1); thetaB(k) = doax(3); thetaC(k) = doax(5);
end
%%
%%%%%%%%% plot %%%%%%%%%%%%
subplot(s); plot(doa,thetaA,'-.r',doa,thetaB,'-.b',doa,thetaC,'-.k',0,90);grid;
title(annotation,'interpreter','latex')
xticks([-100 -75 -45 -15 15 45 75]);
yticks([30 60 90]);
% latex x-ticks
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
Ax.XAxis.TickLabels = {'stat','32','24','18','20','28','34'};
Ax.YAxis.TickLabelInterpreter = 'latex';
Ax.YAxis.TickLabels = {'30$^\circ$','60$^\circ$','90$^\circ$'};
text(-80,80,'$\theta_a$','interpreter','latex','color','r');
text(-80,45,'$\theta_c$','interpreter','latex','color','k');
text(-80,12,'$\theta_b$','interpreter','latex','color','b');
end