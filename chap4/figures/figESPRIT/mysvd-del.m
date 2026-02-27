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
function [u,lambda] = mysvd(Hnkl)
%[u,lambda] = mysvd(R) = mysvd(R) Summary of this function goes here
%   Detailed explanation goes here
display(['size of Hankel ' num2str(size(Hnkl))]);
H = Hnkl'*Hnkl; sz = size(H); H = H/sz(1);
display(['size of H ',num2str(sz)]);
[V D] = eig(H);
[L,ind] = sort(diag(D),'descend');
Vs = V(:,ind); Ds = D(ind,ind);
display(['size of V ' num2str(size(Vs))]);
S = sqrt(Ds);
lambda = diag(S);
u = Hnkl*Vs*inv(S);
display(['size of U ' num2str(size(u))]);
[u,D,V] = svd(Hnkl,'econ'); % this is for testing
end