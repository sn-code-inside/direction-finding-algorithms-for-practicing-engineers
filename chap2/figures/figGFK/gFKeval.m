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
function [A B C Cu Fn] = gFKeval(ngs)
%[A B C] = gFKeval(ngs) Summary of this function goes here
%   Detailed explanation goes here
load gFKobj.csv;
sz = size(gFKobj);
m = 1;
for k=1:sz(1)
    i = mod(k-1,ngs) + 1;
    At(i,m) = gFKobj(k,1);
    Bt(i,m) = gFKobj(k,2);
    Cu(i,m) = gFKobj(k,3);
    if ( i == 20 ) m = m+1; end;
end
Ft = mean(Bt'); [Fn ind] = sort(Ft);
A = At(ind,:); B = Bt(ind,:); C = Cu(ind,:);
end