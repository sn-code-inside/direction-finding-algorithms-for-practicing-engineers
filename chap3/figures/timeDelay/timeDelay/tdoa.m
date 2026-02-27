  % ... copyright protected Dr Kaluri V Ranga Rao
  % ... kaluri@ieee.org
  clc; clear all;
  close all;
  % .... Input Parameters ..
  control = -1; flag = 1; % apf2 orthogonal  method
  N = 6; Tau = -5.1; Cycles = 10.0;
  nSize = 1000; SNR = 25.0; 
  % .... Matlab callable C code ..
  [a,b,c,f,par,Jkr,rkdot,Jkx]=delayT(N,Tau,Cycles,nSize,SNR,control,flag);
  t = a(1,:); x1 = a(2,:); x2 = a(3,:);
  T = b(1,:); y1 = b(2,:); y2 = b(3,:);
  % .... detection window ..
  X = [t(1) T(1) T(1) T(length(T)) T(length(T)) t(length(t))];
  Y = [0     0    1       1           0  0];
  % .... data plot with detection window ..
  %subplot(211); plot(t,x1,'.-r',t,x2,'.-b',X,Y,'-.k');grid;
  title([' Data Window with $\tilde{N} =$ ' num2str(N) ...
  ' samples per cycle. $\tau$ = ',...
  num2str(par(5)) ' Cycles'],'interpreter', 'latex'); 
  ylabel(' Amplitude ','interpreter', 'latex');
  %label211(x1,x2,T,t,SNR);
  % .... Waveforms and Delay Estimation ..
  plot(T,y2,'.-r',T,c,'.-b');
  grid;
  xlabel(' Cycles ','interpreter', 'latex'); 
  ylabel(' Amplitude ','interpreter', 'latex');
  title('Detection Window','interpreter', 'latex');
  %label212(f,T,y1,c,tou,N);




