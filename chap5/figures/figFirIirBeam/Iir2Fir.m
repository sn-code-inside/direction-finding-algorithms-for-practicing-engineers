function [phi,mFir,mIir] = Iir2Fir(theta,dbyl,r,m)
%[phi,mFir,mIir] = Iir2Fir(theta,dbyl,r,m) Summary of this function goes here
%   Detailed explanation goes here
nSamples = 180; 
phiPeak = 360*dbyl*sind(theta);
w = coef(r,theta,dbyl,m);
[hFir wrad] = freqz(w,1,nSamples); mFir = abs(hFir);

p = cosd(phiPeak);
a = [1 -2*r*p r*r];
g = (1-r*r)*0.5; b = g*[1 0 -1];
[hIir wrad] = freqz(b,a,nSamples); mIir =abs(hIir);
phi = wrad*180/pi;
end