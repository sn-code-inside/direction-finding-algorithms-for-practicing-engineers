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
function [se] = eigenV(eV,s,D)
%[sE] = eigenV(eV) Summary of this function goes here
%   Detailed explanation goes here
  sn=' ';
  m = length(eV);
  for k=1:m-D
  if (k==1) sn =[sn '\underbrace{'  num2str(eV(k),4) ];
  else sn =[sn '~' num2str(eV(k),4) ]; 
  end;
  end
  sn =[sn '}'];

  sn =['{' sn '\atop (m-D)}'];

  ss=' ';
  for k=m-D+1:m
  if (k==m-D+1) ss =[ss '\underbrace{'  num2str(eV(k),4) ];
  else ss =[ss '~' num2str(eV(k),4) ]; 
  end;
  end
  ss =[ss '}'];
  ss =['{' ss '\atop D}'];
  se =['\[ {\bf{L}}^T =\left[' sn ss '\right] =[\lambda_1\dots\lambda_m] \]'];

end