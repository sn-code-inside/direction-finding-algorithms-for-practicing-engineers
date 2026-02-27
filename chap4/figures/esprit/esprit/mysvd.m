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
end