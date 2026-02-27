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
clc; clear all;
% Dr Kaluri V Ranga Rao life senior member IEEE princeton kaluri@ieee.org
close all;
theta = linspace(0,360,180);
max = 1;
r = linspace(max,0.2,180);
s = 60; e = 20;
ra = [r(s) r(e)];
th = [theta(s) theta(e)];
h = polarplot(theta*pi/180,r,'.-r',th*pi/180,ra,'ob');
for k=1:180
[xaf,yaf] = polarDS2nfu([theta(k) theta(k)]*pi/180,[r(k)*0.5 r(k)]);
hT = annotation('arrow',xaf,yaf);
pause(0.5);
end




