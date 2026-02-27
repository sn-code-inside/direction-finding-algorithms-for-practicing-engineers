function [a,er] = Er(H,E,L)
%[a,er] = Er(H,E,L) Summary of this function goes here
%   Detailed explanation goes here
a = size(H);
sumE = H*0;
for i = 1:a(1)
    v = E(:,i);
    sumE = sumE + L(i)*(v*v');
end
ErE = sumE - H;
er = mean(mean(abs(ErE)));
end