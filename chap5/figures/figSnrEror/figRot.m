clc; clear all;
close all;
clc;
clear all; close All;
D = 1; % number of emitters
DOAS = [-70,-35, 65]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 1; m=2*M+1;
%a1 = round((rand-0.5)*180); a2 = round((rand-0.5)*180); a3 = round((rand-0.5)*180);
%DOAS =[a1 a2 a3];
%% generate data
swpNum = 160;
doaTst = linspace(-88,88,swpNum);
for k=1:swpNum
DOAS(1) = doaTst(k);
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise); snr = mean(SNR);
kmax = 160; se(1) = 5; se(2) = 85; r = 0.98;
swpAng = linspace(se(1),se(2),kmax);
[Jk theta doa] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
a = doa(1,:); b = doa(3,:); c = doa(5,:);
pka = doa(2,:); pkb = doa(4,:); 
Pka(k) = a(1); Pkb(k) = b(1);  Pkc(k) = c(1);
%%
pkB(k) = rotUla(-60,b(1)) - 90;
pkC(k) = rotUla(60,c(1))  + 30;
end
subplot(311);plot(doaTst,Pka,'sr','MarkerSize', 4,'MarkerFaceColor','r');grid;
hold on; plot(doaTst,pkB,'^b','MarkerSize', 3,'MarkerFaceColor','b'); hold off;
hold on; plot(doaTst,pkC,'oc','MarkerSize', 2,'MarkerFaceColor','c'); hold off;
hold on; plot(0,0,'ok','MarkerSize', 20); hold off;
hold on; plot(60,60,'ok','MarkerSize', 20); hold off;
hold on; plot(-60,60,'ok','MarkerSize', 20); hold off;
xticks([-90 -60 -30 0 30 60 90])
tiks = [-90 -60 -30 0 30 60 90];
yticks(tiks)
legend('$\theta_a$','$\theta_{b2a}$','$\theta_{c2a}$','Location','best',...
    'interpreter', 'latex');
ylabel('[$\theta_a^\circ~\theta_{b2a}^\circ~\theta_{c2a}^\circ$]','interpreter', 'latex');
xlabel('Target Angle','interpreter', 'latex');
title('Rotation Logic','interpreter', 'latex');
%%
Ax = gca;
Ax.XAxis.TickLabelInterpreter = 'latex';
Ax.XAxis.TickLabels = {[num2str(tiks(1)) '$^\circ$'],[num2str(tiks(2)) '$^\circ$'],...
    [num2str(tiks(3)) '$^\circ$'], [num2str(tiks(4)) '$^\circ$'],[num2str(tiks(5)) '$^\circ$']... 
[num2str(tiks(6)) '$^\circ$'], [num2str(tiks(7)) '$^\circ$']};
Ax.YAxis.TickLabelInterpreter = 'latex';
