  % ... copyright protected Dr Kaluri V Ranga Rao
  % ... kaluri@ieee.org
  clc; clear all;
  close all;
  % .... Input Parameters ..
  N = 6; Tau = -5.1; Cycles = 10.0;
  nSize = 1000; SNR = 25.0; 
  % .... Matlab callable C code ..
  [a,b,shift,f,tou]=delayT(N,Tau,Cycles,nSize,SNR);
  t = b(1,:); x1 = b(2,:); x2 = b(3,:); 
  % .... Waveforms and Delay Estimation ..
  subplot(311); plot(t,f,'.-r',t,shift,'-.b');  grid;




 



