clc;
clear all; close All;
D = 1; % number of emitters
DOAS = [-72, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; r = 0.95; theta = 62;
m = 2*M + 1; stdNoise = 1; ten = 10;
swpMax = 93;
low = -88; hi = 88;
doa = linspace(low,hi,swpMax);
%%
for k=1:swpMax
DOAS =[doa(k) -70 50];
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise);
kmax = 80; se(1) = 5; se(2) = 85;
[Jk theta doaA] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
%% sweep beam 
thetaA = doaA(1); thetaB = doaA(3); thetaC = doaA(5);
v =[thetaA thetaB thetaC];
[thetaHat(k) ulaPks] = map3ulaS(thetaA, thetaB, thetaC);
%% plot A
    if (k==ten) 
        labelABC(theta,Jka,Jkb,Jkc,D,thetaHat(k),doaA,SNR,m); 
        doaAatK = [doaA(1) doaA(3) doaA(5)];
    end;
end
%%
p = polyfit(thetaHat,doa,1); sig = std(doa-thetaHat);
if (p(2) < 0 ) si ='- '; 
else si ='+ '; end
s1 = ['$\theta^\circ$ = ' num2str(p(1),3) '$\hat\theta^\circ$ ' si num2str(abs(p(2)),3)];
doaSampl = doa(1:5:swpMax);
subplot(427); plot(doa,thetaHat,'-.r');grid
hold on; plot(doaSampl,doaSampl,'sb','MarkerSize', 3); hold off;
hold on; plot(doa(ten),doa(ten),'ob','MarkerSize', 4,'MarkerFaceColor','k'); hold off;
title(s1,'interpreter', 'latex');
xlabel('$\theta^\circ$ degrees ','interpreter', 'latex');
ylabel(' $\hat\theta^\circ$ ','interpreter', 'latex');
xticks([round(doa(ten),1) -30 0 30 60 hi])
yticks([low 0 hi]);
%text(-70,-250,, 'interpreter', 'latex');
text(30,-60,['$\sigma=$' num2str(sig,3) '$^\circ$'], 'interpreter', 'latex');
%text(-60,-270,['$\theta=$[' num2str(doaAatK,3) ']$^\circ$'], 'interpreter', 'latex');
