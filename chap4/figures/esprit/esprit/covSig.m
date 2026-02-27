function [R,Hnkl] = covSig(sig,m,N)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
%build autocorrelation matrix m by m
R = complex(zeros(m,m)); % initilize with zero
kt = 1;
for i = m:N;   
  indx = i-m+1:i;
  Hnkl(:,kt) = sig(indx);
  R  = R + sig(indx)'*sig(indx);
  kt=kt+1;
end
R = R/(N-m); 

end