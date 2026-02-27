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
  % DOAS =[20]; POWS =[1 1 1];
  % numberOfPhiSamples = 18; delPhi = 360/numberOfPhiSamples;
  % snapShots = 128; NumOfElements = 5;
  % stdx = 1; SamplesPerCycle = 8;
  % D = 1;  dbyl = 0.5;
  % rcA =[snapShots NumOfElements];
  % k=1;
  % for theta=-70:1:70
  % DOAS(1) = theta;   
  % [A SNR(k)] = IQmatrix(DOAS,stdx,D,rcA,dbyl,SamplesPerCycle,POWS);
  % [muSpk doa(k) En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  % thetak(k) = theta;
  % k=k+1;
  % end
  % p = polyfit(doa,thetak,1);
  % er = thetak - doa;
  % sNr = mean(SNR);
  % SDE = std(er);
  stdx = 1;snapShots = 128;
  [SDE,sNr,p,thetak,doa,delPhi,NumOfElements,SamplesPerCycle] = gMuStd(stdx,snapShots);
  numSc = ['ULA ' num2str(NumOfElements) ' SNR ' num2str(sNr,3) ' dB at $f_n= $'...
      num2str(1/SamplesPerCycle,3) ' Hz ' ];
  numS = [numSc ' $\Delta\varphi$ =' num2str(delPhi)  '$^\circ$ Snap Shots ' num2str(snapShots)];
  subplot(311); plot(thetak, thetak, 'o', thetak, doa, '.-r'); grid;
  title(numS,'interpreter','latex');
  xlabel(' DOA in Degrees $\theta^\circ$','interpreter','latex');
  ylabel(' Estimated DOA $\hat\theta^\circ$','interpreter','latex')
  legend([' True DOA '], [ ' Estimated DOA \sigma_g ' num2str(SDE,3) '^\circ'],'Location','northwest');
  if (p(2) < 0) si ='-'; else si='+'; end;
  text(20,-50,[ '$\theta^\circ$ = ' num2str(p(1),5) '$\hat\theta^\circ$ ' si ' ' num2str(abs(p(2)),3)],...
      'BackgroundColor','yellow','Fontsize',8,'interpreter','latex')

  


  
