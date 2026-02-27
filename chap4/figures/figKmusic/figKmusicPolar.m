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
      end
    end
  end
     if (blocks == 1) allClouds = clouds'; 
     else allClouds = [allClouds clouds']; end;
end


% post processing
for k=1:config(5)
indx = find(allClouds(1,:) == numberOfTgts-k+1);
theta = allClouds(4,indx); r = allClouds(2,indx);
thetaMu(k) = mean(theta); rMu(k) = mean(r);
stdTheta(k) = std(theta); stdR(k) = std(r);
if (k==1) polarplot((theta+90)*pi/180,r,'.');
else hold on; polarplot((theta+90)*pi/180,r,'.'); hold off; end;
end
thetaticks([0 30 60 90 120 150 180]);
thetaticklabels({'90^o','60^o','30^o','0^o','-30^o','-60^o','-90^o'});
rtik = sort(round(rMu,2));
rticks(rtik);
thetaX =[(thetaMu'+90)*pi/180 (thetaMu'+90)*pi/180];
rY = [0*rMu' rMu'];
hold on; polarplot(thetaX',rY','.-'); hold off;
hold on; polarplot((thetaMu+90)*pi/180,rMu,'o','MarkerSize',12); hold off;
title(['$\kappa$MUSIC $\sigma^\circ$=[' num2str(stdTheta,3) ']' ],...
    'color','blue','interpreter', 'latex');
subtitle(' Range in Meters ',"Position",[270,1.8],"HorizontalAlignment","center",...
    'color','black','interpreter', 'latex')

% label all angles
numberOfTgts = config(5);
for k=1:numberOfTgts
th = thetaMu(k) + 90;
tha = [th+sign(th)*20 th]; ra =[1.1*rMu(k) rMu(k)];       
[xaf,yaf] = polarDS2nfu(tha*pi/180,ra); % Convert to normalized figure units
hT = annotation('textarrow',xaf,yaf,'Interpreter','latex','String', ...
     ['$\theta_{bin=' num2str( bins(numberOfTgts-k+1) ) '}$= ' num2str(-thetaMu(k),3) '$^\circ$'],...
     'color','blue','LineStyle','-.');
hT.TextBackgroundColor = 'yellow';
end;

% insert image
axes('pos',[-0.23 0.14 1.5 0.35]); % [xb yb xt yt]
imshow('cr3.jpg');
