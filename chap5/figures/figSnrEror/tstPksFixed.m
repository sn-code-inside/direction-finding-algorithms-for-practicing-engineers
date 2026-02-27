clc; clear all;
close all;
clc;
clear all; close All;
D = 3; % number of emitters
DOAS = [-70,-35, 65]; % angles for ULA A
POWS = [4.0, 4.0, 4.0]; PHIS = [0, 0,0];
M = 10; maxk = 256; d_by_lambda = 0.5; r_by_lambda = 15.2;
N = 10; fn = 1/N; stdNoise = 1; m=2*M+1;
%% generate data
swpNum = 160;
doaTst = linspace(-88,88,swpNum);
for k=1:swpNum
%D=1; DOAS(1) = doaTst(k);
%a1 = round((rand-0.5)*180); a2 = round((rand-0.5)*180); a3 = round((rand-0.5)*180);
%DOAS =[a1 a2 a3];
D = 3; DOAS(1) = round((rand-0.5)*180);
[sA, sB, sC,Ha,Hb,Hc,SNR] = abcUla(D, DOAS, POWS, PHIS, M, maxk, ...
    d_by_lambda, r_by_lambda, fn,stdNoise); snr = mean(SNR);
kmax = 160; se(1) = 5; se(2) = 85; r = 0.98;
swpAng = linspace(se(1),se(2),kmax);
[Jk theta doa] = stfSweepDoa(Ha,Hb,Hc,r,d_by_lambda,kmax,se,D);
Jka = Jk(1,:); Jkb = Jk(2,:); Jkc = Jk(3,:);
a = doa(1,:); b = doa(3,:); c = doa(5,:);
pka = doa(2,:); pkb = doa(4,:); 
%Pka(k) = a(1); Pkb(k) = b(1);  Pkc(k) = c(1);
%%
p = 1;
for i=1:D
    for k=1:D
        for j=1:D
            pkA = rotUla(60,a(i))-30;
            pkB = rotUla(-60,b(k)) - 90;
            pkC = rotUla(60,c(j)) + 30;
            if (a(i) > 60) pkBb(p) = -pkB+120; else pkBb(p) = pkB; end;
            if (a(i) > 60) pkCc(p) = -pkC+120; else pkCc(p) = pkC; end;
            aA(p) = a(i);
            X(p) = p; Z(p) = DOAS(j);
            p = p + 1;
        end
    end
end
plot(0,120,27,0);
%ytik = sort([abs(DOAS) -90 0 90]);
yticks([-90 -60 -30 0 30 60 90 120]);
%xtik = sort([DOAS -90 0 90]);
%xticks(xtik);

hold on; plot(X,pkBb,'sb','MarkerSize', 6,'MarkerFaceColor','b');hold off; grid
hold on; plot(X,pkCc,'^c','MarkerSize', 5,'MarkerFaceColor','c'); hold off;
hold on; plot(X,aA,'or','MarkerSize', 4,'MarkerFaceColor','r'); hold off;
hold on; plot(X,Z,'*r','MarkerSize', 3,'MarkerFaceColor','r'); hold off;
pause;
end
