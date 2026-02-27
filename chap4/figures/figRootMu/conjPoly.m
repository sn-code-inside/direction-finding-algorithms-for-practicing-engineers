function [P,rPhi,JrMu] = conjPoly(En)
%[P] = conjPoly(En) Summary of this function goes here
%   Detailed explanation goes here
sz = size(En); D = sz(2)-sz(1); N = sz(2);
k=1; 
P = complex(zeros(1,2*N-1));
for i = 1:sz(1)
    v = En(k,:); vStar = conj(flipud(v));
    P = P + conv(v,vStar);
end
dbl = 0.5;
rP = roots(P); rAbs = abs(rP)
rPvalid = rP( rAbs < 1.05); 
deltaR = abs( abs(rPvalid)-1 );
[deltR,indx] = sort(deltaR);
rS = rPvalid(indx);
rPhi(:,1) = deltR;
phi = angle(rS)*180/pi;
rPhi(:,2) = asind(phi/180);
JrMu = abs(freqz(real(P),1,180));

end