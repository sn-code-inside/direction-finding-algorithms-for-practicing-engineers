function [cir,vec] = rgDoa(r,Phi)
%[cir,vec] = rgDoa(r,phi) Summary of this function goes here
%   Detailed explanation goes here
N = 90; phi = Phi;
th = linspace(0,2*pi,N); rg = ones(size(th))*r;
thr = ones(size(th))*phi*pi/180;
rv = linspace(0,r*1.2,N);
cir =[th' thr']; vec = [rg' rv'];
end