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
clc; clear all; close all;
for p=1:7
datafile =['A0166-0' num2str(p) '.txt'];
[config file] = initR(datafile,2); 
maxNumberOfBlocks = 3; 
numberOfTgts = 2;
kmax = 300; % number of chirps
rForMusic = 1;
numOfPhaseSpecSamples = 180;
config(15) = maxNumberOfBlocks;
rd = config(9); rds = config(8); config(5) = 3; config(7) = kmax; 
config(6) = numOfPhaseSpecSamples; config(5) = numberOfTgts;  
config(13) = 0.17; % thresold for limiting the target
%K=0:rds-1;
for blocks=1:maxNumberOfBlocks
  for k = 1:kmax  
    [bins,str,doas,muDoas,phiSpk,spk,muS,S,A,strAvg,rgMat,clouds,En] ...
    = getRgD(file,config');
    if (k == 15) 
      if (blocks == maxNumberOfBlocks) 
          if (p==7) 
              labelKmuAndMu(config,muS,phiSpk,p,k); 
          end;
      end
    end
  end
end
rg(:,p) = clouds(:,2); tHkMu(:,p) = clouds(:,4); thMu(:,p) = clouds(:,5);
% tHkMu is kMUSIC and thMu is standard MUSIC
pause(1);
end
K=1:kmax;
[rg1,doa1,rg2,doa2,doa1Mu,doa2Mu,table,theta,r] = makeTable(rg,tHkMu,thMu,kmax);
LatexFileMatrix('ExpTestBed.tex','FMCW Radar Experimental Data',table);
labelCalibrate(K,doa1,rg1);
labelFixedTgt(K,doa2,rg2);
labelTestBed(table);
labelLinearFit(table,doa2,rg2,doa1Mu);
%print -depsc -f1 figKmuCalSpk.eps
%print -depsc -f2 figCalibrate.eps
%print -depsc -f3 figFixedTgt.eps
%print -depsc -f4 figExpTestBed.eps
%print -depsc -f5 figKmuCal.eps
