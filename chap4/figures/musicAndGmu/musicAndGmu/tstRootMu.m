  clc; clear all;
  close all;
  DOAS =[20, -35, 30]; POWS =[1 1 1];
  numberOfPhiSamples = 180;
  snapShots = 128; NumOfElements = 8;
  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  delr = 0.15; delth = 3; [B C Dr indx rDoa] = rootMusic(En,delr,delth);
  % rVn = B(:,2); rAn = B(:,1); rAmax = length(rAn);
  % X =[rAn rAn]'; Y =[rVn*0 rVn]';
  % Xdoa = asind(X/180);
  % polarplot(pi/2 - Xdoa*pi/180,Y,'-o','MarkerSize', 4,'MarkerFaceColor','blue');
  % thetaticks([0 30 60 90 120 150 180]);
  % thetaticklabels({'90^\circ','60^\circ','30^\circ',...
  %     '0^\circ','-30^\circ','-60^\circ','-90^\circ'});

