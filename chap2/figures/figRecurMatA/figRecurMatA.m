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
clear all;close all;
% recursive solution of simultaneous equations
%row_max=10; 
%A=fix((rand([row_max 2])-0.5)*20);
load adata;
N = 20; x_val=-5;y_val=7;
Ek = recurA(A,x_val,y_val,N);
