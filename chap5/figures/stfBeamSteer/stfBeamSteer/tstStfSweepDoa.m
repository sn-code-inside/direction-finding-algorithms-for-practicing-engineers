clc;
clear all; close All;
D = 3; % number of emitters
DOAS = [50, -45, -70]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 0.2;
 
Ns = 17; doa = linspace(-80,80,N);
for k=1:Ns
DOAS = [50, -45, -70];
DOAS(1) = doa(k);    
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise);
kmax = 80; se(1) = 5; se(2) = 85; r = 0.98;
[Jk theta doaA] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
a = doaA(1,:); b = doaA(3,:); c = doaA(5,:);
[psi ulaPks] = map3ula(a,b,c);
%%
subplot(311); plot(theta,Jk(1,:),'.-r');grid;
hold on; plot(doaA(1,:),doaA(2,:),'ko','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
title([' True Values  ' num2str(DOAS,3) ' Estimated ' num2str(psi,3)],'interpreter','latex');
%%
subplot(312); plot(theta,Jk(2,:),'.-b');grid;
hold on; plot(doaA(3,:),doaA(4,:),'ko','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
%%
subplot(313); plot(theta,Jk(3,:),'.-k');grid;
hold on; plot(doaA(5,:),doaA(6,:),'ko','MarkerSize', 4,'MarkerFaceColor','c'); hold off;
pause;
end


