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

function [theta,muSpkClamp] = labelPolar(muSpk,fs,B,dbyl,doa)
%[theta,muSpkClamp] = labelPolar(muSpk,fs,B,dbyl,doa) Summary of this function goes here
%   Detailed explanation goes here
u = B(:,1);
delt = 1/fs; phimax = dbyl*360;
numberOfSamples = length(muSpk); 
phi = linspace(-180,180,numberOfSamples);
indA = find(phi > phimax); e1 = indA(1);
indB = find(phi > -phimax); s1 = indB(1);
phiL = max([phi(s1) phi(e1)]);
phiPeak = phimax*sind(doa);
X =[phiPeak phiPeak]; Y = [0 max(muSpk)];
phiClamp = phi(s1-1:e1+1); muSpkClamp = muSpk(s1-1:e1+1);
arg = phiClamp/phimax; ind = find(abs(arg) > 1.0);

arg(ind) = sign(arg(ind));
if (abs(arg) > 1.0) arg = 1.0; end;

theta = asind(arg);

end