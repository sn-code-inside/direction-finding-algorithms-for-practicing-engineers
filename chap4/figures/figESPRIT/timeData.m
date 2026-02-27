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
function [z,snr] = timeData(f,ns)
%[z,snr] = timeData(f,ns) Summary of this function goes here
%   Detailed explanation goes here
Nt = 512; % original shifted data length
K = 0:Nt-1;
% init conditions
z = complex(zeros(1,Nt));
for p=1:ns
y = [cos(2*pi*f(p)*K) + j*sin(2*pi*f(p)*K)];   
x(p,:) = y;
z = z + x(p,:);
end
noise = rand(size(z))+j*rand(size(z));
sp = std(real(z)); np = std(real(noise));
snr = 10*log10(sp/np);
z = z + noise;
end