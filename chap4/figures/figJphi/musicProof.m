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
function [H,En,E,eV] = musicProof(A,D)
%[H,En,E,eV] = musicProof(A,D) Summary of this function goes here
%   Detailed explanation goes here
rcA = size(A); numberOfElements = rcA(2);
noiseEn = numberOfElements - D;
H = A'*A; H = H/(max(max(H)));
[E L] = eig(H); eV = diag(L);
En = E(1:noiseEn,:);
st = H*0;
w = E(:,2);
for k=1:rcA(2)
    v = E(:,k);    
    st = st+eV(k)*v*v'
end
sum(sum(abs(st - H)))
w'*H
eV(2)*w'

end