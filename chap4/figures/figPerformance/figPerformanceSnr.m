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

  snapShots(1) = 16; kmax = 50;
  stdx = linspace(0.33,1.5,kmax);
  for k=1:kmax
  [SDE16(k),sNr16(k),p16A(:,k),thetak,doa,delPhi,NumOfElements,SamplesPerCycle] = gMuStd(stdx(k),snapShots(1));
  end;
  p16(1) = mean(p16A(1,:)); p16(2) = mean(p16A(2,:));

  
  snapShots(2) = 256; kmax = 50;
  stdx = linspace(0.33,1.5,kmax);
  for k=1:kmax
  [SDE256(k),sNr256(k),p256A(:,k),thetak,doa,delPhi,NumOfElements,SamplesPerCycle] = gMuStd(stdx(k),snapShots(2));
  end;
  p256(1) = mean(p256A(1,:)); p256(2) = mean(p256A(2,:));
  muSig(1) = mean(SDE16); muSig(2) = mean(SDE256);
  subplot(311); plot(sNr16,SDE16,'.-r',sNr256,SDE256,'.-b');grid
    numSc = ['ULA ' num2str(NumOfElements) ' $\mu_{\sigma_g}$= [' ...
        num2str(muSig,3) ']$^\circ$  $f_n= $'...
      num2str(1/SamplesPerCycle,3) ' Hz ' ];
  numS = [numSc ' $\Delta\varphi$ =' num2str(delPhi) ...
      '$^\circ$ Snap Shots [' num2str(snapShots) ']'];
  title(numS,'interpreter','latex');

  xlabel('SNR in dB','interpreter','latex');
  ytik = sort([round(muSig(2),2) round(muSig(1),2) 3 4 5]);
  yticks(ytik);  ylabel('$\sigma_g$','interpreter','latex');
  legend('Snap Shots 16','Snap Shots 256','Location','northeast');
  if (p16(2) < 0) si ='-'; else si='+'; end;
  text(-4,3,[ '$\theta^\circ$ = ' num2str(p16(1),5) '$\hat\theta^\circ$ ' si ' ' num2str(abs(p16(2)),3)],...
      'BackgroundColor','yellow','EdgeColor','r','Fontsize',8,'interpreter','latex')

  if (p256(2) < 0) si ='-'; else si='+'; end;
  text(-0.5,3,[ '$\theta^\circ$ = ' num2str(p256(1),5) '$\hat\theta^\circ$ ' si ' ' num2str(abs(p256(2)),3)],...
      'BackgroundColor','yellow','EdgeColor','b','Fontsize',8,'interpreter','latex')

