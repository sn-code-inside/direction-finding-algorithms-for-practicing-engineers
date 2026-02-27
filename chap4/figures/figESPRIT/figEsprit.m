% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
clear all; close all; clc;
ns = 4; %numb of signal sources
f=[18/360 72/360 108/360 162/360];
[z,snr] = timeData(f,ns);
Nt = length(z);
%...................................
% take a part of the original signal
% size of the covarince matrix (m by m)
m = 12;  N = 31; start=fix(Nt*0.6);
Kp = start:start+N-1; sk = z(Kp);
%%%
[phi lambda Sh omega pole] = espritUla(ns,sk,m);
szr = size(Sh);
%%%%%% plotting %%%%%%%%%%%
labelEsprit(z,sk,Kp,snr,N,f,omega,szr,lambda')
LatexFileMatrix('EigenValues.tex','Eigen Values $\bf{H}$',lambda);
Lst(1,1) = 1;   Lst(2,1)=2;
Lst(1,2:ns+1) = pole;
Lst(2,2:ns+1) = omega;

LatexFileMatrix('poles.tex','Eigen Values $\bf{\Phi}$',Lst);
figure(2)
polarplot(omega*pi/180,pole,'bo','MarkerSize', 4,'MarkerFaceColor','b');
%title(' Pole Positions using ESPRIT ','interpreter', 'latex');
tiks = omega;
thetaticks(round(tiks,2));
subtitle(['Estimated  $re^{j\varphi}$ of the ARMA using ESPRIT'],...
    "Position",[270,1.4],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');
% ...................................................................
%print -depsc -f1 figESPRIT.eps
%print -depsc -f2 figEspritPolar.eps
%print -depsc -f3 figEsprtReslts.eps

