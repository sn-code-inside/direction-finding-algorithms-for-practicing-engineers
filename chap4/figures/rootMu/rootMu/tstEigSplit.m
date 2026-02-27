   %updated on 11th Jan 2025 @ 9:00am Hyderabad TG
  clc; clear all;
  close all;
  DOAS =[20, -35, 30]; POWS =[1 1 1];
  numberOfPhiSamples = 180;
  snapShots = 128; NumOfElements = 30;
  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  delr = 0.15; delth = 3; [C B] = rootMusic(En,delr,delth);
  a=clusterLin(eV,3)