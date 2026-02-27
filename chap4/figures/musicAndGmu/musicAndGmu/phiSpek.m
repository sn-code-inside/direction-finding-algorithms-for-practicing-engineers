function [Jn,Jt] = phiSpek(H,En,numberOfPhiSamples,eV)
%[J,Jt] = phiSpek(H,En,numberOfPhiSamples) Summary of this function goes here
%   Detailed explanation goes here
rcA = size(H); rcEn = size(En);
NumOfElements = rcA(1);
phi = linspace(-180,180,numberOfPhiSamples);

Hn = En'*En; 
%%%%%%%%%%
for n=1:rcEn(1)
a = En(n,:); 
for p=1:numberOfPhiSamples

    for k=1:NumOfElements
        z(k) = exp(-i*(k-1)*phi(p)*pi/180);
    end
    Jn(n,p) = abs(z*Hn*a');
    Jt(n,p) = abs(z*H*a');
end;
end;
%%%%%%%%%%


end

