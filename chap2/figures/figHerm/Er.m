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
function [a,er] = Er(H,E,L)
%[a,er] = Er(H,E,L) Summary of this function goes here
%   Detailed explanation goes here
a = size(H);
sumE = H*0;
for i = 1:a(1)
    v = E(:,i);
    sumE = sumE + L(i)*(v*v');
end
ErE = sumE - H;
er = trace(ErE*ErE');
%er = mean(mean(abs(ErE)));
end