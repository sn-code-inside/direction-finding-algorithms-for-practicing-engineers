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
clc; clear all;
close all;
X = [100/6 100/6 100/6 100/6 100/6 100/6];
labels = {'b=2','b=0','b=4','b=5','b=7','b=3'};
explode=[1 0 0 0 0 1];
pie(X,explode,labels);