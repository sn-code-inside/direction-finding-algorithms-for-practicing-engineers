clc; clear all;
close all;
N = 17; 
theta = linspace(-80,80,N);
for k=1:N
   pkC(k)  = rotUla(1,theta(k));
end
subplot(311); plot(theta,pkC,'.-r');grid;