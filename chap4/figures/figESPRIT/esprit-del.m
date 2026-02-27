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
function [omegas,lambda,Ls,A] = esprit(Hnkl,ns,m)
%[omegas,lambda] = esprit(R,ns,m) Summary of this function goes here
%   Detailed explanation goes here
%eigendecomposition
[U,lambda] = mysvd(Hnkl);
%select signal subspace corresponding to ns largest eigenvalues/eigenvectors
S = U(:,1:ns); A = S(1:m-1,:); b = S(2:m,:);

%solve for LSQ phi
%B = real(A'*A);
B = (A'*A);
Ap = inv(B)*A';
for p=1:ns
a = b(:,p);   
phi(:,p) =Ap*a;
end
%solve for frequencies
%omega = -angle(eig(phi))/(2*pi); %Eigenvalues of eigendecomposition
Lphi = eig(phi);
omega = angle(Lphi)*180/pi; %Eigenvalues of eigendecomposition
[omegas ind] = sort(omega);
Ls = Lphi(ind);
end