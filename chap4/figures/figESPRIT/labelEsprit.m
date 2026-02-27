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
function [] = labelEsprit(z,sk,Kp,snr,N,f,omegaD,szr,lambda)
%labelEsprit(Xk,fn,z,sig,K,Kp,snr,N,f,omega,lambda) Summary of this function goes here
%   Detailed explanation goes here
figure(1)
Nt = length(z);
K = 0:Nt-1;
Xk = abs(fft(z)); Xk = Xk/max(Xk);
fn = linspace(0,1,Nt);
Ktiks =[K(1:128:length(K)) K(length(K))];
xk = real(z); sigxk = std(xk); yk = imag(z);
O = sigxk*3;
subplot(321); plot(K,xk,K,yk+O,Kp,real(sk),'.-r',Kp,imag(sk)+O,'.-r');grid
title(['Time Series $x_k$ with SNR ' num2str(snr,2) 'dB' ],'interpreter','latex');
xticks(Ktiks);
ylabel('Complex $x_k$','interpreter','latex');
Kticks =Kp(1:5:length(Kp));
text(Kp(1),min(xk)*1.2,['$s_k$'],'color',...
    'blue','interpreter', 'latex');
%............
subplot(322); plot(Kp,real(sk),'.-r',Kp,imag(sk)+O,'.-b');grid;
s = ['signal $s_k\subseteq x_k$ of ' num2str(N) ' samples'];
title(s,'interpreter','latex');
xticks(Kticks);
ylabel('Complex $s_k$','interpreter','latex');
% spectrum
%labelARMAspk(omegaD,fn,Xk,f,szr,lambda,'312');
figure(3)
labelARMAspk(omegaD,fn,Xk,f,szr,lambda,'311');
end