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
function [omegas,Ls,szr] = esprit(Sh,phi)
%[omegas,Ls,szr] = esprit(Sh,phi) Summary of this function goes here
%   Detailed explanation goes here
szr = size(Sh);
Lphi = eig(phi);
omega = angle(Lphi)*180/pi; %Eigenvalues of eigendecomposition
[omegas ind] = sort(omega);
Ls = Lphi(ind);
end