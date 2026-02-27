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
function [] = labelFig4(config,muS,muDoas,bins)
%[] = labelFig4(config,muS) Summary of this function goes here
%   Detailed explanation goes here
        numberOfTgts = config(5);
        lenMuS =  length(muS);
        phi = linspace(-180,180,lenMuS); theta = asind(phi/180);
        mxMuS = max(muS')';
        doasX =[muDoas muDoas]; doasY =[0*mxMuS mxMuS];
        figure(4)
        subplot(311); plot(theta,muS(1,:),'r',theta,muS(2,:),'b',...
            theta,muS(3,:),'k');grid
        xlabel('$\theta^\circ$','interpreter', 'latex');
        ylabel('$\|J(\theta)\|$','interpreter', 'latex');
        title(['MUSIC spectrum at peaks at ' num2str(bins')],'interpreter', 'latex');
        hold on; plot(doasX',doasY','s-b','MarkerSize', 3,'MarkerFaceColor','b'); hold off;
        facecol=['r' 'b' 'k'];
        for k=1:numberOfTgts
        [pn ln] = findpeaks(muS(k,:));
        hold on; plot(theta(ln),pn,'ko','MarkerSize', 4,'MarkerFaceColor',facecol(k)); hold off;
        end
end