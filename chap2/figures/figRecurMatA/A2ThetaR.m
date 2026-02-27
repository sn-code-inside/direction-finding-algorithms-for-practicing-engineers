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
function [Theta,R,p] = A2ThetaR(A,x_val,y_val,N)
%[Theta,R,p] = A2ThetaR(A,x_val,y_val,N) Summary of this function goes here
%   Detailed explanation goes here
sz = size(A); row_max = sz(1);
sigma_x=0.2; sigma_y=0.2;

x1=x_val-randn([1 row_max])*sigma_x;
c1=A(:,1); p1=c1.*x1';
x2=y_val-randn([1 row_max])*sigma_y;
c2=A(:,2); p2=c2.*x2';
p=fix(p1+p2);

b=  x_val - 0.5*abs(x_val);
e = x_val + 0.5*abs(x_val);
x =linspace(b,e,N);
%x=x_val-3:0.1:x_val+3;
    for i=1:row_max
        q=A(i,:);
        y=-q(1)/q(2)*x+p(i)/q(2);
        R(:,i) = sqrt(x.*x + y.*y);
        Theta(:,i) = atan2(y,x);
    end
end