clc;
clear all; close All;
D = 3; % number of emitters
DOAS = [40, -70, 50]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 1; m=2*M+1;
%% generate data
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise); snr = mean(SNR);
kmax = 30; se(1) = 5; se(2) = 85; r = 0.95;
[Jk theta doa] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
a = doa(1,:); b = doa(3,:); c = doa(5,:);
%% plot
ulaPlot( theta,Jka,a,doa(2,:),'421','3 Targets seen by ULA-A','.-r','b');
ylabel('$J_A(\theta)$','interpreter','latex');
text(45,7.5,['Targets $\theta=$ [' num2str(sort(DOAS)) ']$^\circ$ at SNR ' ...
    num2str(snr,3) 'dB ULA(' num2str(m) ')' ],'interpreter','latex','color','b');
ulaPlot( theta,Jkb,b,doa(4,:),'422','3 Targets seen by ULA-B','.-b','b');
ylabel('$J_B(\theta)$','interpreter','latex');
ulaPlot( theta,Jkc,c,doa(6,:),'423','3 Targets seen by ULA-C','.-k','b');
ylabel('$J_C(\theta)$','interpreter','latex');
%% merging
logicFor3('424',' permitted combinations $\theta_a,\theta_b,\theta_c$');
kmax = 60; se(1) = -85; se(2) = 85;
[JkX thetaX] = stfSweep(Ha,r,d_by_lambda,kmax,se);
y = doa(2,:); 
[doaX ulaPks] = map3ulaS(a,b,c);
ulaPlot( thetaX,JkX,doaX,y,'413','','.-k','c');
ylabel('$J(\theta)$','interpreter','latex');
xlabel(['A-B-C Combined Targets $\hat\theta=$ [' num2str(sort(doaX),3) ...
    ']$^\circ$' ],'interpreter','latex');



