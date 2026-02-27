clc; clear all;
close all;
N = 128;
t=0:N-1; fn = 0.2; f = linspace(0,1,N);
x = sin(2*pi*fn*t)*cosd(30) - sqrt(-1)*cos(2*pi*fn*t)*sind(30);
X = fft(x);
xr = real(X); xi = imag(x);
subplot(311); plot(f,xr,f,xi);grid
