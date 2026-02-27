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
clc; clear all
close all;
%[config, file] = initR('input-2cr-15M-N25deg-10M-N27deg.txt',2);
%[config file] = initR('input-2cr-9.6M-N25deg-10M-N13deg.txt',2);
[config file] = initR('A0803.txt',2);
maxNumberOfBlocks = 2;
rd = config(9); rds = config(8);
config(5) = 2.0;
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6);
kmax = config(7); config(15) = maxNumberOfBlocks;
K = 0:rds-1; phi = linspace(-180,180,numOfPhaseSpecSamples);
fn = K/(rds-1);
aspectRatio = 0.7;
for blocks=1:maxNumberOfBlocks
   for k = 1:kmax
        [bins,str,doas,muDoas,s,spk,muS,S,A,strAvg,rgMat,clouds,En] = getRgD(file,config'); 
        %   at snap shot k = 20 values are captured for analysys
     if (k == 20)  
        %   at block value of 2 specifically data is displayed        
       if (blocks == 2) 
            for p=1:numberOfTgts
                pks = spk(bins(p)+1); zr = 0; 
                pkX(:,p) =[bins(p) bins(p)]/(rds-1); pkY(:,p)=[zr pks];
            end
        %   wide band spectrum
        figure(1);
        wbSpk(fn,spk,pkX,pkY,bins);
        figure(2);
        % kMUSIC peaks at each antenna and phasors
        labelgFKpeaks(bins,str,rgMat,rds,aspectRatio,fn,spk);
        figure(3)
        % kMUSIC phasors
        labelPhasors(str)
       end;
    end;
   end
end

