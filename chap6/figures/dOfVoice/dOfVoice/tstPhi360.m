clc; clear all;
close all;
N = 511;
fn = 0.1; K=0:N;
u = sin(2*pi*fn*K);
for theta=-180:20:180
[y flag] = phiS360(u,theta,fn);
s = fix(0.1*N); e = fix(0.2*N);
Kz = K(s:e); uz = u(s:e); yz = y(s:e);
subplot(211); plot(K,u,'.-r',K,y,'.-b');grid;
subplot(212); plot(Kz,uz,'.-r',Kz,yz,'.-b');grid
title(num2str(theta));
pause(1);
end