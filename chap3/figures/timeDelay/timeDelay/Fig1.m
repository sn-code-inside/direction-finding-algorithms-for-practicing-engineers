% Figure 1

clear all;

N = 30; f = 1/N; zoom = 30;
skipk = 2000; maxk = skipk+zoom;
% choose the phase angle
phi = 5.6 * 360/N; % desired phase-shift in degrees as 5.6 samples
k=1:maxk;

u1 = sin(2*pi*f*k); u2 = sin(2*pi*f*k-2*pi*5/N);
[y r]=apf(u1, phi, 1, 1/N);
K = skipk:maxk;
subplot(211);
plot(K, u1(K),'o-b', K, u1(K), '.-b', K, u2(K), 'o-k', K, y(K), '+-r');grid;
title('Phase-shift using APF','interpreter','latex');
xlabel('Samples','interpreter','latex');
ylabel('Amplitude','interpreter','latex');
