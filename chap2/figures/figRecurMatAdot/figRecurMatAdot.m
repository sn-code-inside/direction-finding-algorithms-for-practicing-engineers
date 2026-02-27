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
% Multivariate Approach
% for more iterations 50
row_max=50; x_val=-5;y_val=7; N = 20;
A=fix((rand([row_max 2])-0.5)*20);
[Theta,R,yp] = A2ThetaR(A,x_val,y_val,N);

[Pk Ek A1 A2,pk0]=recurEq(A,yp);
label311xDot(Ek);
label311grad(Ek);
