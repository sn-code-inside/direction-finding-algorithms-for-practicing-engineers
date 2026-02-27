% Author: Kaluri V. Ranga Rao
% Visiting Scholar, Department of Computer Science,
% The Ohio State University
%
% Copyright (c) 2025 Kaluri V. Ranga Rao
% All rights reserved.
%
% This code is part of the material for the book:
% "Direction Finding Algorithms for Practicing Engineers,"
% published by Springer Nature.
%
% This material is intended for academic and research purposes only.
function [mE,m] = phiSpek(En,numberOfPhiSamples,eV)
%[J,Jt] = phiSpek(H,En,numberOfPhiSamples) Summary of this function goes here
%   Detailed explanation goes here
rcEn = size(En);
NumOfElements = rcEn(2); 
D = NumOfElements - rcEn(1);
%phi = linspace(-180,180,numberOfPhiSamples);
omega = linspace(-pi,pi,numberOfPhiSamples);

%%%%%%%%%%
% Hn = En'*En; 
% for n=1:rcEn(1)
% a = En(n,:); 
% 
% for p=1:numberOfPhiSamples
% 
%     for k=1:NumOfElements
%         z(k) = exp(i*(k-1)*omega(p));
%     end
%     Jn(n,p) = abs(z*Hn*a');
% end;
% end;
% Jn = Jn  /  (max( max(Jn) ))*1.5; 

%%%%%%%%%%
for k=1:rcEn(1)
    e = En(k,:); 
    if (k==1)
    m = abs(freqz(e,1,omega)); mE(k,:) = m;else
    m = m + abs(freqz(e,1,omega));
    mE(k,:) = m; 
    end;
end
mE = mE /  (max( max(mE) ))*1.5;

end

