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
  DOAS =[20, -35, 30]; POWS =[1 1 1];
  numberOfPhiSamples = 180;
  phi = linspace(-180, 180, numberOfPhiSamples);
  snapShots = 128; NumOfElements = 5;
  std = 1; SamplesPerCycle = 8;
  D = 2;  dbyl = 0.5;
  rcA =[snapShots NumOfElements];
  [A SNR] = IQmatrix(DOAS,std,D,rcA,dbyl,SamplesPerCycle,POWS);
  [muSpk doa En eV] = gMusic(D,dbyl,numberOfPhiSamples,A);
  delr = 0.2; delth = 3; [C B Dr] = rootMusic(En,delr,delth);

  %doas =[sort(DOAS(1:D))' sort(doa)']';
  %%%
  
  [Jn Jt] = phiSpek(En,numberOfPhiSamples,eV);
  labelPlot(phi,Jn,B,delr,DOAS,D,SNR);
  [sp sr se] = labelPoly(En,NumOfElements,D,eV);

% Output Strings and .eps file  
  sp =[ '\begin{center}${\bf{E}}_n$~~=~~' sp '\end{center}'];
  fid = fopen('figJphiPoly.tex','wt');
  fprintf(fid,'%s',sp); fclose(fid);

  sr =['\begin{center}' sr '\end{center}'];
  fid = fopen('figJphiRoots.tex','wt');
  fprintf(fid,'%s',sr); fclose(fid);

  fid = fopen('figJphiEigen.tex','wt');
  fprintf(fid,'%s',se); fclose(fid);
  print -f1 -depsc figJphi.eps
  figure(2)
  subplot(311); plot(phi,Jt,'o',phi,1./muSpk,'.r');grid;
  title('$\sum^p \|h_p(z)\|$ = $\sum^p h_p(\varphi)$','interpreter','latex');
  xlabel('$\varphi^\circ$','interpreter','latex');
  ylabel('$H(\varphi)$','interpreter','latex');
  legend('MATLAB','C-Code');


  
