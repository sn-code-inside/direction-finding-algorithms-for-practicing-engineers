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
function [] = labelPolarEsprit(DOAS,doas,allDoas,rcA,SNR)
%labelPolarEsprit(doas,rcA,SNR) Summary of this function goes here
%   Detailed explanation goes here
figure(1)
K=1:rcA(1);
subplot(311);plot(K,allDoas','.-');grid
title([' DOA using ESPRIT $\bf{S}=$ [' num2str(rcA) '] at SNR ' ...
    num2str(SNR,3),'dB'],'interpreter', 'latex');
xlabel(' Snap shot Number ','interpreter', 'latex');
ylabel(' $\hat\theta$ ','interpreter', 'latex');
figure(2)


rdoas = ones(size(doas));
polarplot(-doas*pi/180+pi/2,rdoas,'ro','MarkerSize', 4,'MarkerFaceColor','r');
hold on; polarplot(0,0,'bo','MarkerSize', 4,'MarkerFaceColor','b'); hold off;
title([' DOA using ESPRIT $\bf{S}=$ [' num2str(rcA) '] at SNR ' ...
    num2str(SNR,3),'dB'],'interpreter', 'latex');
sDOAS = sort(-DOAS);
thetaticks(90+sDOAS);
thetaticklabels({[num2str(-sDOAS(1),2) '$^\circ$'],...
    [num2str(-sDOAS(2),2) '$^\circ$'], [num2str(-sDOAS(3),2) '$^\circ$']});
rticks([0.5 0.9]);
subtitle(['Estimated  $\theta$ using ESPRIT [' num2str(doas,4) ']$^\circ$' ],...
    "Position",[270,1.2],"HorizontalAlignment",...
    "center",'color','black','interpreter', 'latex');
Ax = gca;
Ax.RAxis.TickLabelInterpreter = 'latex';
Ax.ThetaAxis.TickLabelInterpreter = 'latex';
end