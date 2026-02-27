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
function [u,lambda] = mysvd(R)
%[u,lambda] = mysvd(R) = mysvd(R) Summary of this function goes here
%   Detailed explanation goes here
[V D] = eig(R'*R);
[L,ind] = sort(diag(D),'descend');
Vs = V(:,ind); Ds = D(ind,ind);
S = sqrt(Ds);
lambda = diag(S);
u = R*Vs*inv(S);
end