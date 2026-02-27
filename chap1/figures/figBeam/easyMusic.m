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

function J = easyMusic(En,muS,phi,config)
%   J = easyMusic(En,muS,config) Summary of this function goes here
%   MUSIC Spectrum from En
    
    numberOfTgts = config(5); 
    numOfPhaseSpecSamples = config(6)
    a1 = En(1,:); a2 = En(2,:); b1 = En(3,:); b2 = En(4,:);
    
    
    h1 = freqz(a1,1,phi*pi/180); h2 = freqz(a2,1,phi*pi/180);
    h3 = freqz(b1,1,phi*pi/180); h4 = freqz(b2,1,phi*pi/180);
    m1 = abs(h1)'; m2 = abs(h2)'; m3 = abs(h3)'; m4 = abs(h4)'
    mu1 = 1./(m1+m2); mu2 = 1./(m3+m4)
    muS1 = muS(1,:); muS2 = muS(2,:);
    figure(2);
    subplot(311);plot(phi,muS1,'.-r',phi,mu1,'ob');grid;
    subplot(312);plot(phi,muS2,'.-r',phi,mu2,'ob');grid;
end