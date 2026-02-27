function [Lphi] = eigFun(phi)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
phiA = (phi' + phi)/2;
x =[real(phiA) imag(phiA)
    -imag(phiA) real(phiA)];
sz = size(x);
lphi = eig(x); Lphi(:,1) = lphi;

phiA = (phi' - phi)/2;
x =[imag(phiA) real(phiA)
    -real(phiA) imag(phiA)];
lphi = eig(x); Lphi(:,2) = lphi;
end