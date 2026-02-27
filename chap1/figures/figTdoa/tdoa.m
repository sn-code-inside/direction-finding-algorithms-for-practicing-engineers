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
  close all;
  % .... Input Parameters ..
  N = 6; Tau = 4; Cycles = 10.0;  nSize = 1000; SNR = 25.0;
  % .... Matlab callable C code ..
  [a,b,c,f,tou]=delayT(N,Tau,Cycles,nSize,SNR);
  t = a(1,:); x1 = a(2,:); x2 = a(3,:);
  T = b(1,:); y1 = b(2,:); y2 = b(3,:);
  % .... detection window ..
  X = [t(1) T(1) T(1) T(length(T)) T(length(T)) t(length(t))];
  Y = [0     0    1       1           0  0];
  % .... data plot with detection window ..
  subplot(211); plot(t,x1,'.-r',t,x2,'.-b',X,Y,'-.k');grid;
  title([' Data Window with $\tilde{N} =$ ' num2str(N) ...
  ' samples per cycle. $\tau$ = ',...
  num2str(tou(5)) ' Cycles'],'interpreter', 'latex'); 
  ylabel(' Amplitude ','interpreter', 'latex');
  tiks =sort([0:20:60 round(T(1),1) round(T(length(T)),1) 110:20:170]);
  xticks(tiks);
  label211(x1,x2,T,t,SNR);
  % .... Waveforms and Delay Estimation ..
  subplot(212); plot(T,y1,'r',T,y2,'-.b',T,c,'-.k',T,f,'.-b');
  grid;
  xlabel(' Cycles ','interpreter', 'latex'); 
  ylabel(' Amplitude ','interpreter', 'latex');
  title('Detection Window','interpreter', 'latex');
  tiks =sort([70:5:90 round(T(1),1) round(T(length(T)),1)]);
  xticks(tiks);
  label212(f,T,y1,c,tou,N);




