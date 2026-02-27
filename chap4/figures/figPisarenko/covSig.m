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
function [R] = covSig(sig,m,N)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
%build autocorrelation matrix m by m
R = complex(zeros(m,m)); % initilize with zero
for i = m:N;   
  indx = i-m+1:i;
  R  = R + sig(indx)'*sig(indx);
end
R = R/(N-m); 

end