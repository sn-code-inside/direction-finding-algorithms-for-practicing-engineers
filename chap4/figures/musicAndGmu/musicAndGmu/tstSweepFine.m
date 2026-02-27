
  clc; clear all;
  close all;
  DOAS =[20, -35, 30]; POWS=[1 1 1];
  muSamples = 90;
  snapShots = 128; NumOfElements =6;
  std = 0.1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,muSamples,A);
  phi = linspace(-180,180,length(muSpk));
  Theta = asind(phi/180);
  [theta Jk gJk doamu JkMu] = sweepFine(En,[-90 90],30);
  X =[doamu' doamu']'; Y =[JkMu'*0 JkMu']';
  subplot(211); plot(Theta,muSpk,theta,Jk,'.-r',X,Y,'o-');grid;

