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
clc; clear all
close all;
thetaMax = 180; kmax = 360;
[Phi phi] = evalDoaData(thetaMax, kmax);
%clear all;
%load thetadata;
%kmax = length(phi);
labelAzimDoa(Phi,phi);
for k=1:kmax
    thetav = Phi(k,:);
    [thetaA(k) thetaB(k) obj(k)]= doaVector2doa(thetav);
end
figure(2)
subplot(221);plot(phi,thetaA,'.-r');grid
xlabel('Azimuth Angle $\theta^\circ$','interpreter','latex');
ylabel('Output $\hat\theta_{ab}^\circ$','interpreter','latex');
title(' $360^\circ$ Coverage $(\theta_a,\theta_b)$','interpreter','latex');
yticks([-180 -120 -60 0 60 120 180]);
xticks([-180 -120 -60 0 60 120 180]);
subplot(222);plot(phi,thetaB,'.-r');grid
xlabel('Azimuth Angle $\theta^\circ$','interpreter','latex');
ylabel('Output $\hat\theta_{ac}^\circ$','interpreter','latex');
title(' $360^\circ$ Coverage $(\theta_a,\theta_c)$','interpreter','latex');
yticks([-180 -120 -60 0 60 120 180]);
xticks([-180 -120 -60 0 60 120 180]);




