%print -depsc -f1 figRgPhiGfk.eps


% ... copyright protected Dr Kaluri V Ranga Rao
% ... kaluri@ieee.org
clc; clear all; close all;
[config file] = initR('car-car-bike.txt',2); 
maxNumberOfBlocks = 1; rForMusic = 1; config(15) = maxNumberOfBlocks;
rd = config(9); rds = config(8); config(5) = 2.0; kmax = config(7);  
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6); 
rg = config(12); config(5) = 5; numberOfTgts = 5;
K=0:rds-1;
for blocks=1:maxNumberOfBlocks
  for k = 1:kmax
    config(5) = 3; config(6) = 180; config(7)=kmax; 
    [bins,str,doas,muDoas,phiSpk,spk,muS,S,A,strAvg,rgMat,clouds,En,data] ...
    = getRgDcLuster(file,config');
    k
    pause
    if (k == 10) 
      if (blocks == 3)
        labelCloseDoa(A,spk,rd,clouds,rg);
      end
    end
  end
end
