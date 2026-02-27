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
function [Pk Ek A1 A2 pk0]=recur(Ak,Yk)
N = max(size(Ak));
a1 = 0.1; a2=0.1; pk0 = [a1 a2]';
I0 = diag(ones(2,1))*1e-1;
Pk = I0; pk = pk0;
for k = 1:N
xk = [Ak(k,1) Ak(k,2)]; 
xkhat = Pk*xk'; ykhat = xk*pk; % Equation 10
g = 1/(1 + xk*xkhat); yk = Yk(k); % Equation 11
ek = yk - ykhat; pknew = pk + g*xkhat*ek; % Equation 12
gradJk = 2*xkhat*ek;

A1(k) = pknew(1); A2(k) = pknew(2); 
Ek(1,k) = ek; Ek(2,k) = gradJk'*gradJk; Ek(3,k) = xk*xkhat;
Pknew = Pk - g*xkhat*xkhat'; % Equation 13
pk = pknew; Pk = Pknew;
end
return;
    
