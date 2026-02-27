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
fnMax = 100; phiDmax = 360;
rmin = 0.1; rmax = 0.95;
fN = linspace(0.01,0.5,fnMax);
for k=1:fnMax
fn = fN(k);    
phiD = linspace(0,360,phiDmax);
% modified APF
for i=1:phiDmax
[type rV]=newAPF(fn,phiD(i),rmin,rmax);
r(i) = rV;
end;

clear ind;
ind = find(abs(r) > rmax | abs(r) < rmin );
indLen(k) = length(ind);
phiV(k,:) = phiD*0; Fn(k,:) = phiD*0;
phiV(k,ind) = phiD(ind); 
Fn(k,ind) = phiD(ind)*0 +fn;
end
invalid = sum(indLen)/(phiDmax*fnMax)*100;
labelNewPhiFn(phiV,Fn,rmin,rmax,invalid);
