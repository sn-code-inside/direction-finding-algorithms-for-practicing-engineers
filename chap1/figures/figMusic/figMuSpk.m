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
[config file] = initR('closeDoa.txt',2);
maxNumberOfBlocks = 5;
rd = config(9); rds = config(8);
config(5) = 2.0;
numberOfTgts = config(5); numOfPhaseSpecSamples = config(6);
kmax = config(7); config(15) = maxNumberOfBlocks;

for blocks=1:maxNumberOfBlocks
    for k = 1:kmax
        [bins,str,doas,muDoas,s,spk,muS,S,A,strAvg,rgMat,clouds] = getRgD(file,config'); 
%   at snap shot k = 20 values are captured for analysys
    if (k == 20)  
        phi = linspace(-180,180,numOfPhaseSpecSamples);
        mu1 = muS(1,:); mu2 = muS(2,:); max1 = max(mu1); max2 = max(mu2);
        ek = mu1 - mu2; mu11 = mu1; mu22 = mu2;
        ind = find(ek <= 0); mu1(ind) = mu1(ind)*0;
        inda = find(ek > 0); mu2(inda) = mu2(inda)*0;
        mu = mu1+mu2;
%       at block value of 4 specifically data is displayed        
        if (blocks == 4) 
            phase = 180*sind(muDoas);
            X1 =[phase(1) phase(1)]; Y1 =[0 max1];
            X2 =[phase(2) phase(2)]; Y2 =[0 max2];

            subplot(211);plot(phi,mu,'.-b',X1,Y1,'s-r',X2,Y2,'^-r');grid;
            title(['DOA values $\theta_1$ = ' ...
                num2str(muDoas(1),4) '$^o~~\theta_2$ = ' ...
                num2str(muDoas(2),4) '$^o$'], ...
                'interpreter', 'latex'); 
            xlabel(' Phase Angle ($\varphi^o$) ','interpreter', 'latex'); 
            ylabel(' $J(\varphi)$ ','interpreter', 'latex');
            labelMu211(muDoas,mu,phi,max1,max2,phase)
        end;
    end;
    end
end

