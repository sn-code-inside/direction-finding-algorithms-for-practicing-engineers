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
function [theta,r] = TrueRgDoa()
%[theta,r] = TrueRgDoa() Summary of this function goes here
%   Detailed explanation goes here

a = 185; b = 104; c = 193;
r = [185 182 181 182 185 188 193];
lenr = length(r);
x1 = 84; x2 = 102; % fixed target at 84 cm
cs = (a*a + b*b - c*c)/(2*a*b);
cs1 = (x1*x1 + a*a - x2*x2)/(2*x1*a);
fixed = acosd(cs1);
C = acosd(cs);
sb = b*sind(C)/c; B = asind(sb);
sa = a*sind(C)/c; A = asind(sa);
h = a*sind(C); thet = 90 - c;
for k = 1:lenr
val = h/r(k); 
 if abs(val) > 1.0 val = 1.0; end
th(k) = asind(val);
end
theta = 90 - th; 
theta(1:2) = -theta(1:2);
theta(lenr+1) = theta(1) + fixed;
r(lenr+1) = x1;
end