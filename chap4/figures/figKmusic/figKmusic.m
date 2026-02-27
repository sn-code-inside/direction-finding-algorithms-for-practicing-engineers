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
[config file] = initR('B0160.txt',2); maxNumberOfBlocks = 3; 
rForMusic = 1;
config(15) = maxNumberOfBlocks;
rd = config(9); rds = config(8); config(5) = 2.0; kmax = config(7);  
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6);  
 %aspectRatio = 0.685;
K=0:rds-1;
for blocks=1:maxNumberOfBlocks
  for k = 1:kmax
    config(5) = 3; config(6) = 180;  
    [bins,str,doas,muDoas,phiSpk,spk,muS,S,A,strAvg,rgMat,clouds,En] ...
    = getRgD(file,config');
    if (k == 10) 
      if (blocks == 2)
        [s e binsX binsY w tgtNum] = labelFig1(config,K,spk,bins,str,rgMat,doas,file,rds);  
        [r,phi,st bin] = labelFig2(config,s,e,tgtNum,K,spk,bins,w,binsX,binsY);
        labelFig3(phiSpk,doas,tgtNum,bin,muS,bins,config);
        labelFig4(config,muS,muDoas,bins)
      end
    end
  end
end

