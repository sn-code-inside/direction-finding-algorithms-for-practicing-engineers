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
clc; clear all;
close all;
%aspectRatio = 0.685;
DOAS =[20, -35, 30];
std = 1; fn = 0.1; N = 1/fn;
D = 2; snapShots = 64; NumOfElements = 4;
% look matrix and gold-MUSIC
rcA =[snapShots NumOfElements];
[muSpk doa En SNR] = gMusic(DOAS,std,N,D,rcA);
muSpk = muSpk/max(muSpk);
numberOfSamples = length(muSpk);
phi = linspace(180,-180,numberOfSamples);
theta = asind(phi/180);
[Jk ind] = findpeaks(muSpk);
if (Jk(1) < Jk(2)) temp = Jk(1);  Jk(1)   = Jk(2); Jk(2)  = temp; 
                   temp = ind(1); ind(1) = ind(2); ind(2) = temp; end;
%........... end of MUSIC
% this part took lot of time to arrive at this 20th May 2024
% 18:30 Belle Mead NJ new function polarDS2nfu.m was written
% Transforms polar Data Space to normalized figure units 22nd May 2024
% peak 1
thPk1 = [theta(ind(1)) theta(ind(1))] + 90;
Pk1 = [0 Jk(1)];
% peak 2
thPk2 = [theta(ind(2)) theta(ind(2))] + 90;
Pk2 = [0 Jk(2)];
% polar plot of beams
h = polarplot(theta*pi/180+pi/2,muSpk,'.-b',...
    thPk1*pi/180,Pk1,'-.or',thPk2*pi/180,Pk2,'-.^k');
set(h, {'MarkerFaceColor'}, get(h,'Color'));
labelFigBeam(doa,theta,muSpk,ind,En,SNR);

