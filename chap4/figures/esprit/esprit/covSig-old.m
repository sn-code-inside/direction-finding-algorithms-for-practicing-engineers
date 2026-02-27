function [R] = covSig(sig,m,N)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
%build autocorrelation matrix m by m
R = complex(zeros(m,m)); % initilize with zero
for i = m:N;   
  indx = i-m+1:i;
  R  = R + sig(indx)'*sig(indx);
end
R = R/(N-m); 

end