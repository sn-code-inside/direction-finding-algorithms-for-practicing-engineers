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
    dbylambda = 0.5;
    N = 180; m = 5; aspectRatio = 0.685;
    K=1:m; thetaQ = 2; A = 2*pi*dbylambda;
    phiQ = A*sin((thetaQ*pi/180));
    b1 = exp(i*K*phiQ);  b2 = exp(-i*K*phiQ);
    Phi = linspace(-pi,pi,N);
    theta = asin(Phi/A)*180/pi; % rehash phase to doa
    location = 80; std = 0.1;
%   phase sepctrum    
    h1 = freqz(b1,1,Phi); m1 = abs(h1); noise1 = std*randn(size(m1)); 
    m1 = m1 + noise1;
    snr1 = 10*log10( var(abs(h1))/var(noise1) );
    J1 = m1/max(m1);
    h2 = freqz(b2,1,Phi); m2 = abs(h2); noise2 = std*randn(size(m2));
    m2 = m2 + noise2;
    snr2 = 10*log10( var(abs(h2))/var(noise2) );
    J2 = m2/max(m2);
    snr = (snr1 + snr2)*0.5;
    h = polarplot(theta*pi/180+pi/2,J1,'.-r', ...
        theta*pi/180+pi/2,J2,'.-b', ...
        (90-theta(location))*pi/180,J2(location),'or', ...
        (90-theta(location))*pi/180,J1(location),'or');
    set(h, {'MarkerFaceColor'}, get(h,'Color'));
    labelFxBm(location,theta,thetaQ,J1,J2,m,snr);
    




