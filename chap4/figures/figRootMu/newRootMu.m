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
function [rS,P,rP] = newRootMu(En)
%[rS,P] = newRootMu(En) Summary of this function goes here
%   Detailed explanation goes here
  sz = size(En); NumOfElements = sz(2);
  Hn = En'*En;
  k = 1;
  % sum off diagonals
  for p=-NumOfElements-1:1:NumOfElements-1
  P(k) = sum(diag(Hn,p));
  k = k+1;
  end
  rT = roots(P); [x indx] = sort(abs(rT));
  rP = rT(indx); rAbs = abs(rP);

  rPvalid = rP( rAbs < 1.05); 
  deltaR = abs( abs(rPvalid)-1 );
  [deltR,indx] = sort(deltaR);
  rS = rPvalid(indx);

  rPhi(:,1) = deltR;
  phiA = angle(rS)*180/pi;
  rPhi(:,2) = asind(phiA/180);
end