function [u,lambda,R,Vs] = mysvd(R)
%[u,lambda] = mysvd(R) = mysvd(R) Summary of this function goes here
%   Detailed explanation goes here
[V D] = eig(R'*R);
[L,ind] = sort(diag(D),'descend');
Vs = V(:,ind); Ds = D(ind,ind);
S = sqrt(Ds);
lambda = diag(S);
RV = R*Vs;
u = RV*inv(S);
end