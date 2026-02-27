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
function [s] = strMat(A)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
sz = size(A); sold ='';
for i = 1: sz(1)
    if (sz(2) > 1) s1 = [sold  num2str(A(i,1),2) '&' num2str(A(i,2),2) '\cr']; end;
    if (sz(2) == 1) s1 = [sold  num2str(A(i,1),2)  '\cr']; end;
    sold = s1;
end
s =['$\pmatrix{' s1 '}$'];