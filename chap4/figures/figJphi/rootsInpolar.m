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
function [s] = rootsInpolar(a,s,p)
%[s] = rootsInpolar(a,s,p) Summary of this function goes here
%   Detailed explanation goes here
  ar = abs(a); ath = -angle(a)*180/pi; %% this is for sign fix
  n = length(ar);
for k=1:n-1
  if ( sign(ath(k)) < 0 ) si = '-'; else si =''; end; 

  if (k==1) s =[s '$h_' num2str(p,2)  '(z)=$ & $(1 - ' ...
          num2str(ar(k),2) 'e^{' si 'j' num2str(abs(ath(k)),3) '}z^{-1})'];
  else s =[s '(1 - ' num2str(ar(k),2) 'e^{' si 'j' num2str(abs(ath(k)),3) '}z^{-1})']; end;

end
  s =[s '(1 - ' num2str(ar(n),2) 'e^{' si 'j' num2str(abs(ath(n)),3) '} z^{-1}$) \\'];
end
%  s =[s '(1 - ' num2str(ar(k),2) '$e^{' si 'j' num2str(abs(ath(k)),3) '}$ ) &'];
