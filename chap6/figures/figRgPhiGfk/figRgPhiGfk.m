% ... copyright protected Dr Kaluri V Ranga Rao
% ... kaluri@ieee.org
clc; clear all; close all;
load closeDoa.txt;
rawData = closeDoa(1000:1006,:); clear closeDoa;
[config file] = initR('closeDoa.txt',2); 
 
maxNumberOfBlocks = 4; rForMusic = 1; config(15) = maxNumberOfBlocks;
rd = config(9); rds = config(8); config(5) = 2.0; kmax = config(7);  
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6); 
rg = config(12);
K=0:rds-1;
for blocks=1:maxNumberOfBlocks
  for k = 1:kmax
    config(5) = 3; config(6) = 180; 
    [bins,str,doas,muDoas,phiSpk,spk,muS,S,A,strAvg,rgMat,clouds,En,data] ...
    = getRgDcLuster(file,config');
    if (k == 10) 
      if (blocks == 2)
        figure(1);  
        label211(A,rd);
        label223(rd,spk,rg);
        label224(spk,rd,clouds,rg);
        gfkdata(:,1:4) = data(:,1:4);
        gfkdata(:,5:6) = data(:,6:7);
      end
    end
  end
end

s =['$\Theta$'];
LatexFileMatrix('rgPhiTable.tex',s,gfkdata);
s1 =['$\left\{{\bf{A}}_1 \ldots  {\bf{A}}_k \right\}$'];
LatexFileMatrix('rawDataTable.tex',s1,rawData);
labelPolarClouds(gfkdata,clouds);
%print -depsc -f1 figRgPhiGfk.eps
