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
function [s] = rootsInpolarVec(ar,ath,s,p)
%[s] = rootsInpolar(ar,ath,s,p) Summary of this function goes here
%   Detailed explanation goes here
n = length(ar);
si ='';
rEtheta = ['~~' num2str(ar(1),3) 'e^{{' si 'j' num2str(abs(ath(1)),3) '}^\circ} '];
for k=1:n-1
  if ( sign(ath(k)) < 0 ) si = '-'; else si =''; end; 
  rEtheta = ['~~' num2str(ar(k),3) 'e^{{' si 'j' num2str(abs(ath(k)),3) '}^\circ} '];

  if (k==1) 
  s =[s '$\varphi(' num2str(p,2)  ')$ & $' rEtheta ];
  else s =[s  rEtheta]; end;
end
if (n==1) s =[s '$\varphi(' num2str(p,2)  ')$ & $' rEtheta ]; end;
  s =[s  rEtheta '$  \\'];
  
end
