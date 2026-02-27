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
function [s e binsX binsY w tgtNum] = labelFig1(config,K,spk,bins,str,rgMat,doas,file,rds)
%[s e] = labelFig1(config,K,spk,bins,str,rgMat,doas,file,rds) Summary of this function goes here
%   Detailed explanation goes here
        numberOfTgts = config(5); 
        tgtNum = numberOfTgts - 1;
        figure(1);
        subplot(311);plot(K,spk,'.-b');grid; hold on; %,pkX,pkY,'s-r');grid;
        title([' FMCW Radar Range Spectrum bins [' ...
            num2str(bins') '] ' file],...
            'color','blue','interpreter', 'latex'); 
        ylabel(' $\|FFT(s_k)\|$ ','interpreter', 'latex');
        xlabel(' bin number ', 'interpreter', 'latex');
        xticks([0 bins' 32 64 128]); 
        label211(bins,spk,doas,numberOfTgts)
        % zoom at tgtNum peak
        %pkIndx = bins(numberOfTgts);
        pkIndx = bins(tgtNum);
        s = pkIndx-3; e = pkIndx+3;
        w = str(tgtNum,:);
        binsX(1,:) = rgMat(tgtNum,:)*rds; binsX(2,:) = rgMat(tgtNum,:)*rds;
        binsY(1,:) = abs(w)*0; binsY(2,:) = abs(w);
end