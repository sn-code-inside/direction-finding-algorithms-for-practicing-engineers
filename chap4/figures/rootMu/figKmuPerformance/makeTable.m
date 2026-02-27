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
function [rg1,doa1,rg2,doa2,doa1Mu,doa2Mu,table,theta,r] = makeTable(rg,thkMu,thMu,kmax)
%[rg1,doa1,rg2,doa2,table] = makeTable(rg,thkMu,kmax) Summary of this function goes here
%   Detailed explanation goes here
sz = size(rg);
rg1 = rg(1:kmax,:); rg2 = rg(kmax+1:sz(1),:);
doa1 =thkMu(1:kmax,:);   doa2 = thkMu(kmax+1:sz(1),:);
doa1Mu = thMu(1:kmax,:); doa2Mu = thMu(kmax+1:sz(1),:);
% make table
for p=1:7
rhat(p) = mean(rg1(:,p));
thetaHat(p) = mean(doa1(:,p));
end

sigTh(1:p) = std(doa1);
rhat(p+1) = mean(mean(rg2));
thetaHat(p+1) = mean(mean(doa2));
sigTh(p+1) = mean(std(doa2));

[theta r] = TrueRgDoa;

station = 1:p+1;
table(:,1) = r'; % in centemeters
table(:,2) = theta';
table(:,3) = station';
table(:,4) = rhat'*100; % in centemeters
table(:,5) = thetaHat';
table(:,6) = sigTh';


end