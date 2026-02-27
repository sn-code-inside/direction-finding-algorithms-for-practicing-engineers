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
clc; clear all; close all;
r = 512; c = 30;
x = randn([r c]); y = randn([r c]);
A = x + sqrt(-1)*y;

[Eh,Lh,Jk] = HEIGmH(A); 
[Ej,Lj,JkJ]= HEIGmJ(A); 

H = A'*A; big = max(max(abs(H))); H = H/big;
[Em l] = eig(H); Lm = diag(l)'; 
[a,erM] = Er(H,Em,Lm); [a,erH] = Er(H,Eh,Lh);
[a,erJ] = Er(H,Ej,Lj);
Er =[erM erH erJ];
lableFig(Lj,Lh,Lm,JkJ,Er,a);
