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
function [thetaHat, Theta]= espritDoa(A,D)
%[thetaHat, Theta]= espritDoa(A,D) Summary of this function goes here
%   Detailed explanation goes here
sz = size(A); snapShots=sz(1); 
numberOfRows = 10; 
for k=1:snapShots
    sk = A(k,:);
    [phi L Sh omega pole] = espritUla(D,sk,numberOfRows);
    theta = asind(-omega/180);
    Theta(:,k) = theta;
end
    thetaHat = mean(Theta');
end