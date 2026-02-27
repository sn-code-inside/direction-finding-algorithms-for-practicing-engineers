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
fac = 0.01;
noise = fac*rand(size(z))+j*fac*rand(size(z));
sp = std(real(z)); np = std(real(noise));
snr = 10*log10(sp/np);
z = z + noise;
end