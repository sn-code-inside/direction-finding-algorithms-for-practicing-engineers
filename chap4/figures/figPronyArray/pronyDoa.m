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
function [doas,pole,mPoles,azimuth,mag,lambda,m]= pronyDoa(B,D)
%[doas] = espritDoa(A,D) Summary of this function goes here
%   Detailed explanation goes here
sz = size(B);
deltaR = 0.2; 
NumOfElements =sz(2);
N = NumOfElements; m=round(N/2);

sk = B(1,:);
[S,y] = covSig(sk,m,NumOfElements);
H = S'*S; lambda = eig(H);
p = inv(H)*S'*y';
a =[1 p']; rt = roots(a);
%%%
indx = find(abs(rt) < 1+deltaR);
pole = abs(rt(indx));
phiRad = angle(rt(indx));
phi = phiRad*180/pi; 
doas = -asind(phi/180);
numberOfSamples = 720;
w = linspace(pi,-pi,numberOfSamples);
h = freqz(1,a,w); mag = abs(h);
hPoles = freqz(1,a,phiRad); mPoles = abs(hPoles);
azimuth = -asin(w/pi)*180/pi;
end