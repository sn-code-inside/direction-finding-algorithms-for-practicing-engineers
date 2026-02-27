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
numberOfSamples = 180; 
phi(1,:) = linspace(180,-180,numberOfSamples);
phi(2,:) = phi(1,:);
% linear regression for dbyl = 0.5
dbyl = 0.5; A = (2*pi*dbyl);
x = phi(1,:)/(360*dbyl);
theta(1,:) = asind(x);
s = 41; e = 140; s2 = s; e2 = e;
phix1 = phi(1,s:e); thetay1 = theta(1,s:e);
p = polyfit(phix1,thetay1,1);
thetayHat1 = polyval(p,phix1);
% linear regression for dbyl = 0.3
dbyl1 = 0.3; A = (2*pi*dbyl1);
arg = phi(2,:)/(360*dbyl1);
ki = find(abs(arg) > 1); arg(ki) = sign(arg(ki));
kr = find(abs(arg) <= 1);
theta(2,:) = asind(arg);
s1 = 90-round(0.5*(e-s)*(dbyl1/dbyl)); e1 = 90+round(0.5*(e-s)*(dbyl1/dbyl));
s = s1; e = e1;
phix2 = phi(2,s:e); thetay2 = theta(2,s:e);
p1 = polyfit(phix2,thetay2,1);
thetayHat2 = polyval(p1,phix2);


subplot(311); plot(phi(1,:),theta(1,:),'.b',phix1,thetayHat1,'.r');grid;
label311(phi,theta,s2,e2,p,dbyl);

subplot(312); plot(phi(2,kr),theta(2,kr),'.k',phix2,thetayHat2,'.g', ...
    phi(2,ki),theta(2,ki),'+k');grid;
label312(phi,theta,s1,e1,p1,dbyl1)

